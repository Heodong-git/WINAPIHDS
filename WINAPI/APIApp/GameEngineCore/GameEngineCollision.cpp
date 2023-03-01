#include "GameEngineCollision.h"
#include "GameEngineActor.h"
#include "GameEngineLevel.h"

#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineImage.h>

// 함수포인터, 충돌을 실행할 함수들의 주소를 2차원배열로 저장
static bool(*ColFunctionPtr[CT_Max][CT_Max])(const CollisionData& _Left, const CollisionData& _Right);

// 음. 이걸 뭐라고하지. 좀 재치있게 사용하는 법..?
// cpp 에만 클래스를 구현한 후 , 전역으로 한번만 생성해주면 생성자가 호출되어
// 함수포인터에 함수의주소를 저장해둔다. 
class CollisionFunctionInit
{
public:
	CollisionFunctionInit()
	{
		ColFunctionPtr[CT_CirCle][CT_CirCle] = GameEngineCollision::CollisionCirCleToCirCle;
		ColFunctionPtr[CT_CirCle][CT_Point] = GameEngineCollision::CollisionCirCleToPoint;
		ColFunctionPtr[CT_Rect][CT_Rect] = GameEngineCollision::CollisionRectToRect;
		ColFunctionPtr[CT_Rect][CT_Point] = GameEngineCollision::CollisionRectToPoint;
	}
	~CollisionFunctionInit()
	{

	}
};

CollisionFunctionInit Init = CollisionFunctionInit();

GameEngineCollision::GameEngineCollision()
{
}

GameEngineCollision::~GameEngineCollision()
{
}

// 원 픽셀 충돌
bool GameEngineCollision::CollisionCirCleToPoint(const CollisionData& _Left, const CollisionData& _Right)
{
	float4 Len = _Left.Position - _Right.Position;
	float Size = Len.Size();
	float RadiusSum = _Left.Scale.hx();
	return RadiusSum > Size;
}

// 원 대 원 충돌
bool GameEngineCollision::CollisionCirCleToCirCle(const CollisionData& _Left, const CollisionData& _Right)
{
	// 거리를 구한다. 
	float4 Len = _Left.Position - _Right.Position;
	float Size = Len.Size();
	// 서로의 반지름을 더 한 값 
	float RadiusSum = _Left.Scale.hx() + _Right.Scale.hx();

	// 대상에서 대상까지의 거리가
	// 서로의 반지름을 더한 값보다 작다면 충돌한 것이다.  
	return RadiusSum > Size;
}

bool GameEngineCollision::CollisionRectToRect(const CollisionData& _Left, const CollisionData& _Right)
{
	if (_Left.Bot() <= _Right.Top())
	{
		return false;
	}

	if (_Left.Top() >= _Right.Bot())
	{
		return false;
	}

	if (_Left.Left() >= _Right.Right())
	{
		return false;
	}

	if (_Left.Right() <= _Right.Left())
	{
		return false;
	}

	return true;
}

bool GameEngineCollision::CollisionRectToPoint(const CollisionData& _Left, const CollisionData& _Right)
{
	if (_Left.Bot() <= _Right.Position.y)
	{
		return false;
	}

	if (_Left.Top() >= _Right.Position.y)
	{
		return false;
	}

	if (_Left.Left() >= _Right.Position.x)
	{
		return false;
	}

	if (_Left.Right() <= _Right.Position.x)
	{
		return false;
	}

	return true;
}


void GameEngineCollision::SetOrder(int _Order)
{
	GetActor()->GetLevel()->PushCollision(this, _Order);
}

bool GameEngineCollision::Collision(const CollisionCheckParameter& _Parameter)
{
	// 업데이트가 false 일 경우에는 false 반환 
	if (false == IsUpdate())
	{
		return false;
	}

	// 충돌검사를 실행할 그룹을 받아온다.
	std::list<GameEngineCollision*>& _TargetGroup = GetActor()->GetLevel()->Collisions[_Parameter.TargetGroup];

	// 받아온 그룹을 순회하며 
	for (GameEngineCollision* OtherCollision : _TargetGroup)
	{
		// 그룹에 속한 충돌체가 update가 false 상태라면 continue; 
		if (false == OtherCollision->IsUpdate())
		{
			continue;
		}

		CollisionType Type = _Parameter.ThisColType;
		CollisionType OtherType = _Parameter.TargetColType;

		if (nullptr == ColFunctionPtr[Type][OtherType])
		{
			MsgAssert("아직 충돌함수를 만들지 않은 충돌 타입입니다");
		}

		// 충돌함수를 호출하여 충돌여부를 확인한다. 
		// CircletoCircle 등 함수포인터로 받아둔 함수를 호출하여 검사. 
		if (true == ColFunctionPtr[Type][OtherType](GetCollisionData(), OtherCollision->GetCollisionData()))
		{
			return true;
		}
	}
	return false;
}

bool GameEngineCollision::Collision(const CollisionCheckParameter& _Parameter, std::vector<GameEngineCollision*>& _Collision)
{
	if (false == IsUpdate())
	{
		return false;
	}

	// 데이터를 저장하기 전에 벡터 초기화
	_Collision.clear();

	std::list<GameEngineCollision*>& _TargetGroup = GetActor()->GetLevel()->Collisions[_Parameter.TargetGroup];

	SetDebugRenderType(_Parameter.ThisColType);

	for (GameEngineCollision* OtherCollision : _TargetGroup)
	{
		if (false == OtherCollision->IsUpdate())
		{
			continue;
		}

		CollisionType Type = _Parameter.ThisColType;
		CollisionType OtherType = _Parameter.TargetColType;

		OtherCollision->SetDebugRenderType(OtherType);

		if (nullptr == ColFunctionPtr[Type][OtherType])
		{
			MsgAssert("아직 충돌함수를 만들지 않은 충돌 타입입니다");
		}

		if (true == ColFunctionPtr[Type][OtherType](GetCollisionData(), OtherCollision->GetCollisionData()))
		{
			_Collision.push_back(OtherCollision);
		}
	}

	// 저장된 데이터가 하나라도 있다면 충돌을 했다는 것이다. true 반환
	return _Collision.size() != 0;
}

// 
CollisionData GameEngineCollision::GetCollisionData()
{
	// 충돌데이터를 반환한다.
	// CollisionDate 타입 변수에 각각
	// 액터의 위치, 크기를 담아서 반환한다. 
	return { GetActorPlusPos(), GetScale() };
}

// 디버그용 렌더링함수 
void GameEngineCollision::DebugRender()
{
	HDC BackBufferDc = GameEngineWindow::GetDoubleBufferImage()->GetImageDC();
	float4 DebugRenderPos = GetActorPlusPos() - GetActor()->GetLevel()->GetCameraPos();
	switch (DebugRenderType)
	{
	case CT_Point:
		break;
	case CT_CirCle:
	{
		int Radius = GetScale().hix();
		Ellipse(BackBufferDc,
			DebugRenderPos.ix() - Radius,
			DebugRenderPos.iy() - Radius,
			DebugRenderPos.ix() + Radius,
			DebugRenderPos.iy() + Radius);
		break;
	}
	case CT_Rect:
	{
		Rectangle(BackBufferDc,
			DebugRenderPos.ix() - GetScale().hix(),
			DebugRenderPos.iy() - GetScale().hiy(),
			DebugRenderPos.ix() + GetScale().hix(),
			DebugRenderPos.iy() + GetScale().hiy());
		break;
	}
	case CT_Max:
		break;
	default:
		break;
	}
}