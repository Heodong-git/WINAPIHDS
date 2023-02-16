#pragma once
#include <string>
#include <string_view>

class GameEngineObject
{
public:
	// constrcuter destructer
	GameEngineObject();
	// �θ�Ŭ������ �Ҹ��ڸ� �����Լ��� �����������ν�
	// �ڽ�Ŭ�������� �Ҹ��ڰ� ȣ��� �� �ֵ��� �Ѵ�. 
	virtual ~GameEngineObject();

	// delete Function
	GameEngineObject(const GameEngineObject& _Other) = delete;
	GameEngineObject(GameEngineObject&& _Other) noexcept = delete;
	GameEngineObject& operator=(const GameEngineObject& _Other) = delete;
	GameEngineObject& operator=(GameEngineObject&& _Other) noexcept = delete;

	// ������Ʈüũ 
	bool IsUpdate()
	{
		// ���׿�����
		// ������Ʈ�� �θ� �����Ѵٸ� ����, �ƴϸ� ������ ��ȯ	
		return nullptr != Parent ? ((true == ObjectUpdate && false == IsDeath()) && true == Parent->IsUpdate()) : (ObjectUpdate && false == IsDeath());
	}

	// ����üũ 
	bool IsDeath()
	{
		// ������Ʈ�� �θ� �����Ѵٸ� ����, �ƴϸ� ������ ��ȯ
		return nullptr != Parent ? (true == ObjectDeath || Parent->IsDeath()) : (true == ObjectDeath);
	}

	void Death()
	{
		ObjectDeath = true;
	}

	// ������Ʈ�� ������Ʈ�� ��,������ų ��� �ش� ������Ʈ���� �ؾ��� ���� ���� ��쿡 �ڽ�Ŭ�������� �����ϱ� �����̴�. 
	// ������Ʈ �¿��� 
	virtual void On()
	{
		ObjectUpdate = true;
	}
	virtual void Off()
	{
		ObjectUpdate = false;
	}

	// �¿�������ġ
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

	// �θ�Ŭ������ virtual �Լ��� �ִٸ� 
	// �ڽ�Ŭ���������� �� �Լ��� ������ ���� ������ �θ� Ŭ������ �Լ���, �������Ѵٸ� 
	// �ڽĿ��� �������� �Լ��� ȣ��ǰ� �ȴ�. 
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

	// ������Ʈ�� �̸� ����
	void SetName(const std::string_view& _View)
	{
		Name = _View;
	}

	// �̸���ȯ
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

