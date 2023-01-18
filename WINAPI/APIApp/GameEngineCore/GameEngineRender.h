#pragma once
#include <GameEnginePlatform/GameEngineImage.h>
#include <GameEngineCore/GameEngineObject.h>
#include <map>
// �������� ���õ� ����� ��� ����

// �����Ӿִϸ��̼��Ķ����
class FrameAnimationParameter
{
public:
	std::string_view AnimationName = "";
	std::string_view ImageName = "";
	int Start = 0;
	int End = 0;
	// �����ε���
	int CurrentIndex = 0;
	// �����Ӵ� ��µǴ� �ð� 
	float InterTime = 0.1f;
	// �ݺ����� 
	bool Loop = true;
	std::vector<int> FrameIndex = std::vector<int>();
	std::vector<float> FrameTime = std::vector<float>();
};



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

	// �ӽ÷� ���� �Լ�
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

	GameEngineActor* GetActor();

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

	inline void EffectCameraOff()
	{
		IsEffectCamera = false;
	}

	// �ִϸ��̼� ����
	void CreateAnimation(const FrameAnimationParameter& _Paramter);
	// �ִϸ��̼� ü����
	void ChangeAnimation(const std::string_view& _AnimationName);

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

	// ī�޶��� ������ ���� ���� ���ʹ� EffectCameraOff() �� Start ���� ȣ��.
	bool IsEffectCamera = true;

	int TransColor = RGB(255, 0, 255);

	int Frame = 0;

	void SetOrder(int _Order);
	void Render(float _DeltaTime);

	// �����Ӿִϸ��̼� Ŭ������ ���������� ���������� ����ϱ� ������ private �������������ڿ� �ΰ� ����Ѵ�. 
	class FrameAnimation
	{
	public:
		// �ִϸ��̼��� ������ �������� ��Ƶд�. 
		GameEngineRender* Parent = nullptr;
		
		// Cut �Ǿ� �ִ� �̹��� ����
		GameEngineImage* Image = nullptr;
		std::vector<int> FrameIndex;
		std::vector<float> FrameTime;

		// ���� �ε��� 
		int CurrentIndex = 0;
		float CurrentTime = 0.0f;
		// �ݺ�����
		bool Loop = true;

		void Render(float _DeltaTime);

		// �ִϸ��̼� ������ ��� 
		// ���� �ε��� = 0 , ����ð� = 0 ���� �����Ͽ� ���� 
		void Reset()
		{
			CurrentIndex = 0;
			CurrentTime = 0.0f;
		}
	};

	std::map<std::string, FrameAnimation> Animation;
	FrameAnimation* CurrentAnimation = nullptr;
};

