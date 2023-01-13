#pragma once
#include <GameEnginePlatform/GameEngineImage.h>
#include <GameEngineCore/GameEngineObject.h>
// �������� ���õ� ����� ��� ����

// ���� :
class GameEngineActor;
class GameEngineLevel;
class GameEngineRender : public GameEngineObject
{
	friend GameEngineActor;
	friend GameEngineLevel;

public:
	// constrcuter destructer
	GameEngineRender();
	~GameEngineRender();

	// delete Function
	GameEngineRender(const GameEngineRender& _Other) = delete;
	GameEngineRender(GameEngineRender&& _Other) noexcept = delete;
	GameEngineRender& operator=(const GameEngineRender& _Other) = delete;
	GameEngineRender& operator=(GameEngineRender&& _Other) noexcept = delete;

	void SetImage(const std::string_view& _ImageName);

	inline void SetPosition(float4 _Position)
	{
		Position = _Position;
	}

	inline void SetScale(float4 _Scale)
	{
		Scale = _Scale;
	}

	void SetFrame(int _Frame);

	inline int GetFrame()
	{
		return Frame;
	}

	inline GameEngineImage* GetImage()	
	{
		return Image;
	}

	inline int GetOrder()
	{
		return Order;
	}

protected:

private:
	// �� Render�� ������ ���͸� ����
	GameEngineActor* Owner = nullptr;

	// Zorder �� 
	int Order = 0;
	// Owner�� ���� ��ŭ ���������� ������
	float4 Position = float4::Zero;
	// ��µ� ũ��
	float4 Scale = float4::Zero;
	// ��½� ����� �̹���
	GameEngineImage* Image = nullptr;

	int Frame = 0;

	void SetOrder(int _Order);
	void Render(float _DeltaTime);
};

