#pragma once

// 설명 :
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
		return nullptr != Parent ? ((ObjectUpdate && false == IsDeath()) || Parent->IsUpdate()) : (ObjectUpdate && false == IsDeath());
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

	// 업데이트 온오프 
	void On()
	{
		ObjectUpdate = true;
	}
	void Off()
	{
		ObjectUpdate = false;
	}

	// 온오프스위치 (임시?) 
	void OnOffSwtich()
	{
		ObjectUpdate = !ObjectUpdate;
	}

	void SetParent(GameEngineObject* _Parent)
	{
		Parent = _Parent;
	}

protected:

private:
	GameEngineObject* Parent = nullptr;

	bool ObjectDeath = false;
	bool ObjectUpdate = true;

};

