#pragma once
#include <GameEnginePlatform/GameEngineImage.h>
#include <GameEngineCore/GameEngineObject.h>
#include <map>
// 랜더링에 관련된 기능을 모두 집약

// 프레임애니메이션파라미터
class FrameAnimationParameter
{
public:
	std::string_view AnimationName = "";
	std::string_view ImageName = "";
	int Start = 0;
	int End = 0;
	// 현재인덱스
	int CurrentIndex = 0;
	// 프레임당 출력되는 시간 
	float InterTime = 0.1f;
	// 반복여부 
	bool Loop = true;
	std::vector<int> FrameIndex = std::vector<int>();
	std::vector<float> FrameTime = std::vector<float>();
};



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

	// 임시로 만든 함수
	inline float4 GetPosition()
	{
		return Position;
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

	void SetTransColor(int _Color)
	{
		TransColor = _Color;
	}

	inline GameEngineImage* GetImage()	
	{
		return Image;
	}

	inline int GetOrder()
	{
		return Order;
	}

	// 애니메이션 생성
	void CreateAnimation(const FrameAnimationParameter& _Paramter);
	// 애니메이션 체인지
	void ChangeAnimation(const std::string_view& _AnimationName);

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

	int TransColor = RGB(255, 0, 255);

	int Frame = 0;

	void SetOrder(int _Order);
	void Render(float _DeltaTime);

	// 프레임애니메이션 클래스는 렌더에서만 내부적으로 사용하기 때문에 private 접근제한지정자에 두고 사용한다. 
	class FrameAnimation
	{
	public:
		// 애니메이션을 소유한 렌더러를 담아둔다. 
		GameEngineRender* Parent = nullptr;
		
		// Cut 되어 있는 이미지 저장
		GameEngineImage* Image = nullptr;
		std::vector<int> FrameIndex;
		std::vector<float> FrameTime;

		// 현재 인덱스 
		int CurrentIndex = 0;
		float CurrentTime = 0.0f;
		// 반복여부
		bool Loop = true;

		void Render(float _DeltaTime);

		// 애니메이션 리셋의 경우 
		// 현재 인덱스 = 0 , 현재시간 = 0 으로 변경하여 리셋 
		void Reset()
		{
			CurrentIndex = 0;
			CurrentTime = 0.0f;
		}
	};

	std::map<std::string, FrameAnimation> Animation;
	FrameAnimation* CurrentAnimation = nullptr;
};

