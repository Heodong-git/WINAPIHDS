#include "GameEngineRender.h"
#include <GameEngineBase/GameEngineString.h>	
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineResources.h>
#include "GameEngineActor.h"
#include "GameEngineLevel.h"

GameEngineRender::GameEngineRender()
{
}

GameEngineRender::~GameEngineRender()
{
}

// 출력시 사용할 이미지 세팅
void GameEngineRender::SetImage(const std::string_view& _ImageName)
{
	// 게임엔진 리소스 클래스에서 이미지를 찾아서 대입
	Image = GameEngineResources::GetInst().ImageFind(_ImageName);
	SetScaleToImage();
}

// 인자로 들어온 값으로 order 세팅
void GameEngineRender::SetOrder(int _Order)
{
	GameEngineObject::SetOrder(_Order);
	// 값을 넣어준 후에 렌더러를 소유한 오너의 Level 이 소유한 map 에 추가
	GetActor()->GetLevel()->PushRender(this);
}

void GameEngineRender::SetScaleToImage()
{
	if (nullptr == Image)
	{
		MsgAssert("이미지를 세팅하지 않았는데 이미지의 크기로 변경하려고 했습니다.");
	}

	SetScale(Image->GetImageScale());
}

// 프레임값 세팅
void GameEngineRender::SetFrame(int _Frame)
{
	// 이미지가 없다면
	if (nullptr == Image)
	{
		MsgAssert("이미지가 존재하지 않는 랜더러에 프레임을 지정하려고 했습니다.");
	}

	// Cut 이미지가 아니라면 
	if (false == Image->IsImageCutting())
	{
		MsgAssert("잘려있는 이미지만 프레임을 지정해줄 수 있습니다.");
	}

	// Index 범위를 넘어섰다면 
	if (false == Image->IsCutIndexValid(_Frame))
	{
		MsgAssert("유요하지 않은 이미지인덱스 입니다.");
	}

	Frame = _Frame;
}


bool GameEngineRender::FrameAnimation::IsEnd()
{
	// 애니메이션이 종료되었는지
	int Value = (static_cast<int>(FrameIndex.size()) - 1);
	return CurrentIndex == Value;
}

void GameEngineRender::FrameAnimation::Render(float _DeltaTime)
{
	// 현재시간에서 델타타임을 누적하여 빼주어 
	// 출력되는 시간을 넘어섰는지 확인
	CurrentTime -= _DeltaTime;

	// 출력시간을 넘어섰다면 
	if (CurrentTime <= 0.0f)
	{
		// 다음인덱스로 ++하여 다음 이미지를 출력
		++CurrentIndex;
		// 만약, 현재인덱스가 저장된 Index 의 개수보다 크거나 같다면 
		if (FrameIndex.size() <= CurrentIndex)
		{
			// 루프 애니메이션일 경우 첫번째 인덱스부터 다시시작.
			if (true == Loop)
			{
				CurrentIndex = 0;
			}

			// 루프 애니메이션이 아닐 경우 인덱스를 마지막 인덱스로 고정한다.  
			else
			{
				CurrentIndex = static_cast<int>(FrameIndex.size()) - 1;
			}
		}

		CurrentTime = FrameTime[CurrentIndex];
	}
}

void GameEngineRender::SetText(const std::string_view& _Text, const int _TextHeight, const std::string_view& _TextType, const TextAlign _TextAlign, const COLORREF _TextColor)
{
	RenderText = _Text;
	TextHeight = _TextHeight;
	TextType = _TextType;
	Align = _TextAlign;
	TextColor = _TextColor;
}

// 렌더링
void GameEngineRender::Render(float _DeltaTime)
{
	if (RenderText != "")
	{
		TextRender(_DeltaTime);
	}
	else
	{
		ImageRender(_DeltaTime);
	}
}

void GameEngineRender::TextRender(float _DeltaTime)
{

	float4 CameraPos = float4::Zero;

	if (true == IsEffectCamera)
	{
		CameraPos = GetActor()->GetLevel()->GetCameraPos();
	}

	float4 RenderPos = GetActorPlusPos() - CameraPos;

	HDC hdc = GameEngineWindow::GetDoubleBufferImage()->GetImageDC();
	HFONT hFont, OldFont;
	LOGFONTA lf;
	lf.lfHeight = TextHeight;
	lf.lfWidth = 0;
	lf.lfEscapement = 0;
	lf.lfOrientation = 0;
	lf.lfWeight = 0;
	lf.lfItalic = 0;
	lf.lfUnderline = 0;
	lf.lfStrikeOut = 0;
	lf.lfCharSet = HANGEUL_CHARSET;
	lf.lfOutPrecision = 0;
	lf.lfClipPrecision = 0;
	lf.lfQuality = 0;
	lf.lfPitchAndFamily = VARIABLE_PITCH | FF_ROMAN;
	lstrcpy(lf.lfFaceName, TEXT(TextType.c_str()));
	hFont = CreateFontIndirect(&lf);
	OldFont = static_cast<HFONT>(SelectObject(hdc, hFont));

	//SetTextAlign(hdc, static_cast<UINT>(Align));
	SetTextColor(hdc, TextColor);
	SetBkMode(hdc, TRANSPARENT);

	RECT Rect;
	Rect.left = RenderPos.ix();
	Rect.top = RenderPos.iy();
	Rect.right = RenderPos.ix() + TextBoxScale.ix();
	Rect.bottom = RenderPos.iy() + TextBoxScale.iy();

	if (GameEngineCore::GetInst()->IsDebug())
	{
		HDC DoubleDC = GameEngineWindow::GetDoubleBufferImage()->GetImageDC();
		HBRUSH myBrush = static_cast<HBRUSH>(GetStockObject(NULL_BRUSH));
		HBRUSH oldBrush = static_cast<HBRUSH>(SelectObject(DoubleDC, myBrush));
		HPEN myPen = CreatePen(PS_DASH, 0, RGB(0, 0, 0));
		HPEN oldPen = static_cast<HPEN>(SelectObject(DoubleDC, myPen));
		Rectangle(GameEngineWindow::GetDoubleBufferImage()->GetImageDC(), Rect.left, Rect.top, Rect.right, Rect.bottom);

		SelectObject(DoubleDC, oldBrush);
		DeleteObject(myBrush);
		SelectObject(DoubleDC, oldPen);
		DeleteObject(myPen);
	}

	DrawTextA(GameEngineWindow::GetDoubleBufferImage()->GetImageDC(), RenderText.c_str(), static_cast<int>(RenderText.size()), &Rect, static_cast<UINT>(Align));


	// TextOutA(GameEngineWindow::GetDoubleBufferImage()->GetImageDC(), RenderPos.ix(), RenderPos.iy(), RenderText.c_str(), static_cast<int>(RenderText.size()));

	SelectObject(hdc, OldFont);
	DeleteObject(hFont);

	return;
}


void GameEngineRender::ImageRender(float _DeltaTime)
{
	// 현재 애니메이션이 nullptr 이 아니라면
	// 애니메이션으로 출력해야한다. 
	if (nullptr != CurrentAnimation)
	{
		// 현재 소유한 애니메이션의 렌더호출
		CurrentAnimation->Render(_DeltaTime);
		// 프레임은 현재 애니메이션에 저장되어 있는 현재 인덱스값
		Frame = CurrentAnimation->FrameIndex[CurrentAnimation->CurrentIndex];
		// 이미지는 현재애니메이션의 이미지가 된다. 
		Image = CurrentAnimation->Image;
	}

	// 이미지가 nullptr 일 경우 assert 메세지 출력.
	if (nullptr == Image)
	{
		MsgAssert("이미지를 세팅해주지 않았습니다.");
	}

	float4 CameraPos = float4::Zero;

	if (true == IsEffectCamera)
	{
		CameraPos = GetActor()->GetLevel()->GetCameraPos();
	}

	// 출력될 좌표는 렌더러를 소유한 액터의 위치 + 추가 포지션값
	float4 RenderPos = GetActorPlusPos() - CameraPos;

	// 커팅된 이미지라면
	if (true == Image->IsImageCutting())
	{
		if (255 == Alpha)
		{
			GameEngineWindow::GetDoubleBufferImage()->TransCopy(Image, Frame, RenderPos, GetScale(), TransColor);
		}
		else if (255 > Alpha)
		{
			GameEngineWindow::GetDoubleBufferImage()->AlphaCopy(Image, Frame, RenderPos, GetScale(), Alpha);
		}
	}
	else
	{
		if (255 == Alpha)
		{
			GameEngineWindow::GetDoubleBufferImage()->TransCopy(Image, RenderPos, GetScale(), { 0, 0 }, Image->GetImageScale(), TransColor);
		}
		else if (255 > Alpha)
		{
			GameEngineWindow::GetDoubleBufferImage()->AlphaCopy(Image, RenderPos, GetScale(), { 0, 0 }, Image->GetImageScale(), Alpha);
		}
	}
}

// 애니메이션 종료됐니? 
bool GameEngineRender::IsAnimationEnd()
{
	return CurrentAnimation->IsEnd();
}

// 애니메이션 생성
void GameEngineRender::CreateAnimation(const FrameAnimationParameter& _Paramter)
{
	// 인자로 들어온 키값의 이미지를 찾아서 받아온다. 
	GameEngineImage* Image = GameEngineResources::GetInst().ImageFind(_Paramter.ImageName);

	if (nullptr == Image)
	{
		MsgAssert("존재하지 않는 이미지로 애니메이션을 만들려고 했습니다.");
	}

	// 이미지가 커팅되어있지 않다면 프레임지정이 불가능하다. 
	if (false == Image->IsImageCutting())
	{
		MsgAssert("잘려있는 이미지만 프레임을 지정해줄 수 있습니다.");
	}

	// 올대문자로 변경
	std::string UpperName = GameEngineString::ToUpper(_Paramter.AnimationName);

	// 같은 이름의 애니메이션이 이미 존재한다면 assert 
	if (Animation.end() != Animation.find(UpperName))
	{
		MsgAssert("이미 존재하는 이름의 애니메이션 입니다." + UpperName);
	}

	// 맵에서 인자로들어온 키값의 데이터를 받아온다. 
	// 맵의 문법, 키값으로 데이터가 존재한다면 그녀석을 반환
	// 존재하지 않는다면 그 키값으로 데이터를 추가한다. (?) 확인필요 
	FrameAnimation& NewAnimation = Animation[UpperName];

	NewAnimation.Image = Image;

	// 인자로들어온 구조체의 프레임인덱스 배열의 크기가 0 이 아니라면
	if (0 != _Paramter.FrameIndex.size())
	{
		// 인덱스 값을 그대로 대입
		NewAnimation.FrameIndex = _Paramter.FrameIndex;
	}
	else
	{
		// 프레임인덱스 배열의 크기가 0 이라면
		for (int i = _Paramter.Start; i <= _Paramter.End; ++i)
		{
			NewAnimation.FrameIndex.push_back(i);
		}
	}

	// 각 프레임별 시간을 계산한다.
	if (0 != _Paramter.FrameTime.size())
	{
		NewAnimation.FrameTime = _Paramter.FrameTime;
	}
	else
	{
		for (int i = 0; i < NewAnimation.FrameIndex.size(); ++i)
		{
			NewAnimation.FrameTime.push_back(_Paramter.InterTime);
		}
	}

	// Loop 여부
	NewAnimation.Loop = _Paramter.Loop;
	// this 를 애니메이션의 부모로 지정
	NewAnimation.Parent = this;
}

// 체인지애니메이션
// 렌더러의 애니메이션을 인자로 넣어준 키값에 해당하는 애니메이션으로 교체한다. 
void GameEngineRender::ChangeAnimation(const std::string_view& _AnimationName, bool _ForceChange /*= false*/)
{
	// 대문자 변환
	std::string UpperName = GameEngineString::ToUpper(_AnimationName);

	// 인자로 들어온 키값으로 동일한 키값이 존재하지 않는다면 저장된 애니메이션이 없다는 의미. 
	if (Animation.end() == Animation.find(UpperName))
	{
		MsgAssert("존재하지 않는 애니메이션으로 바꾸려고 했습니다." + UpperName);
	}

	// 애니메이션을 강제로 변경하지 않고, 애니메이션이 같다면 return 
	if (false == _ForceChange && CurrentAnimation == &Animation[UpperName])
	{
		return;
	}

	// 현재 애니메이션을 변경될 애니메이션으로 교체
	CurrentAnimation = &Animation[UpperName];

	// 애니메이션이 교체 되었기 때문에 인덱스를 0으로 변경
	CurrentAnimation->CurrentIndex = 0;
	
	// 애니메이션의 현재시간은 변경된 애니메이션의 프레임타임으로 변경
	CurrentAnimation->CurrentTime = CurrentAnimation->FrameTime[CurrentAnimation->CurrentIndex];
}