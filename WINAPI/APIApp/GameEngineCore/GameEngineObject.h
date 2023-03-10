#pragma once
#include <string>
#include <string_view>

class GameEngineObject
{
public:
	// constrcuter destructer
	GameEngineObject();
	// 부모클래스에 소멸자를 가상함수로 정의해줌으로써
	// 자식클래스들의 소멸자가 호출될 수 있도록 한다. 
	virtual ~GameEngineObject();

	// delete Function
	GameEngineObject(const GameEngineObject& _Other) = delete;
	GameEngineObject(GameEngineObject&& _Other) noexcept = delete;
	GameEngineObject& operator=(const GameEngineObject& _Other) = delete;
	GameEngineObject& operator=(GameEngineObject&& _Other) noexcept = delete;

	// 업데이트체크 
	bool IsUpdate()
	{
		// 삼항연산자
		// 오브젝트의 부모가 존재한다면 왼쪽, 아니면 오른쪽 반환	
		return nullptr != Parent ? ((true == ObjectUpdate && false == IsDeath()) && true == Parent->IsUpdate()) : (ObjectUpdate && false == IsDeath());
	}

	// 데스체크 
	bool IsDeath()
	{
		// 오브젝트의 부모가 존재한다면 왼쪽, 아니면 오른쪽 반환
		return nullptr != Parent ? (true == ObjectDeath || Parent->IsDeath()) : (true == ObjectDeath);
	}

	void Death()
	{
		ObjectDeath = true;
	}

	// 오브젝트의 업데이트를 온,오프시킬 경우 해당 오브젝트에서 해야할 일이 있을 경우에 자식클래스에서 구현하기 위함이다. 
	// 업데이트 온오프 
	virtual void On()
	{
		ObjectUpdate = true;
	}
	virtual void Off()
	{
		ObjectUpdate = false;
	}

	// 온오프스위치
	virtual void OnOffSwtich()
	{
		ObjectUpdate = !ObjectUpdate;
	}

	virtual void SetOrder(int _Order)
	{
		Order = _Order;
	}

	int GetOrder()
	{
		return Order;
	}

	// 부모클래스에 virtual 함수가 있다면 
	// 자식클래스에서는 그 함수를 재정의 하지 않으면 부모 클래스의 함수로, 재정의한다면 
	// 자식에서 재정의한 함수로 호출되게 된다. 
	virtual void SetOwner(GameEngineObject* _Parent)
	{
		Parent = _Parent;
	}

	template<typename ConvertType>
	ConvertType* GetOwner()
	{
		return dynamic_cast<ConvertType*>(Parent);
	}

	GameEngineObject* GetOwner()
	{
		return Parent;
	}

	// 오브젝트의 이름 세팅
	void SetName(const std::string_view& _View)
	{
		Name = _View;
	}

	// 이름반환
	const std::string& GetName()
	{
		return Name;
	}
	
	std::string GetNameCopy()
	{
		return Name;
	}

protected:

private:
	int Order = 0;

	GameEngineObject* Parent = nullptr;

	bool ObjectDeath = false;
	bool ObjectUpdate = true;

	std::string Name;

};

