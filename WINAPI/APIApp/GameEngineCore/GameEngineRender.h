#pragma once
#include <GameEnginePlatform/GameEngineImage.h>
#include <GameEngineCore/GameEngineObject.h>
// 랜더링에 관련된 기능을 모두 집약

// 설명 :
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
	// 이 Render를 소유한 액터를 저장
	GameEngineActor* Owner = nullptr;

	// Zorder 값 
	int Order = 0;
	// Owner로 부터 얼만큼 떨어져있을 것인지
	float4 Position = float4::Zero;
	// 출력될 크기
	float4 Scale = float4::Zero;
	// 출력시 사용할 이미지
	GameEngineImage* Image = nullptr;

	int Frame = 0;

	void SetOrder(int _Order);
	void Render(float _DeltaTime);
};

