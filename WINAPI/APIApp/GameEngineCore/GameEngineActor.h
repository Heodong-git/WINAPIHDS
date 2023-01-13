#pragma once
#include <list>
#include <string_view>
#include <Windows.h>
#include <GameEngineBase/GameEngineMath.h>
#include <GameEngineCore/GameEngineObject.h>

// ��� Level�� �����ִ� ȭ�鿡 ǥ���Ǵ� ���� --- Actor
class GameEngineLevel;
class GameEngineRender;
class GameEngineActor : public GameEngineObject
{
	// GameEngineLevl ���� GameEngineActor Ŭ���� ���ο� ���� ����
	friend GameEngineLevel;

public:
	// constrcuter destructer
	GameEngineActor();
	~GameEngineActor();

	// delete Function
	GameEngineActor(const GameEngineActor& _Other) = delete;
	GameEngineActor(GameEngineActor&& _Other) noexcept = delete;
	GameEngineActor& operator=(const GameEngineActor& _Other) = delete;
	GameEngineActor& operator=(GameEngineActor&& _Other) noexcept = delete;

	// ��ġ��ȯ
	inline float4 GetPos()
	{
		return Pos;
	}

	// ��ġ����
	inline void SetPos(const float4& _MovePos)
	{
		Pos = _MovePos;
	}

	// ��ġ�̵�, ������ �ڽ��� ��ǥ + ���ڷ� ���� �� 
	inline void SetMove(const float4& _MovePos)
	{
		Pos += _MovePos;
	}

	// ���� ������ Level ��ȯ
	inline GameEngineLevel* GetLevel()
	{
		return Level;
	}

#pragma region CreateRenderEnumOverLoadings

	template<typename EnumType>
	GameEngineRender* CreateRender(const std::string_view& _Image, EnumType _Order)
	{
		return CreateRender(_Image, static_cast<int>(_Order));
	}

	template<typename EnumType>
	GameEngineRender* CreateRender(EnumType _Order)
	{
		return CreateRender(static_cast<int>(_Order));
	}

#pragma endregion

	// ������ ����, ������̹���, RenderOrder ���� �־��ش�. 
	GameEngineRender* CreateRender(const std::string_view& _Image, int _Order = 0);
	GameEngineRender* CreateRender(int _Order = 0);

protected:
	// Ŭ���� ���� �� �ٷ� ���־���� ��
	// �������� �ʿ��ϴٸ� GameEngineRender ���� �� ����� �̹���, Order üũ
	virtual void Start() {}

	// Ű�Է� + ������ ���� ����
	virtual void Update(float _DeltaTime) {}

	// �����������, ����ϱ� �� �̰� �� ����ϳ�? ��� �����غ�����.
	virtual void LateUpdate(float _DeltaTime) {}

	// ���� ���� �� ȭ�鿡 ��µǴ� �κ��� ���� 
	virtual void Render(float _DeltaTime) {}

	// ���� ���Ͱ� ȭ�鿡 ����ִ� �ð� ��ȯ
	inline float GetLiveTime()
	{
		return LiveTime;
	}

private:
	GameEngineLevel* Level = nullptr;

	int		Order = 0;						 // ������Ʈ, ������ ���� ���� ���� ���� ���� ���� 
	float	LiveTime = 0.0;					 // ���Ͱ� ȭ�鿡 ����ִ� �ð� 
	float4  Pos = { 0.0f, 0.0f };			 // ��ġ�� ������ ����
	std::list<GameEngineRender*> RenderList; // ���ʹ� �ڽ��� ����ؾ��� Render ����Ʈ�� ������. 

	void SetOrder(int _Order)
	{
		Order = _Order;
	}
};

