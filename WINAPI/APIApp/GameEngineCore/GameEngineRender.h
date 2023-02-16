#pragma once
#include <GameEnginePlatform/GameEngineImage.h>
#include <GameEngineCore/GameEngineComponent.h>
#include <map>


// �ؽ�Ʈ������
enum class TextAlign
{
	Left = TA_LEFT,
	Right = TA_RIGHT,
	Center = TA_CENTER
};


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
class GameEngineRender : public GameEngineComponent
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
	void SetScaleToImage();
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

	// ī�޶� ����Ʈ �¿��� 
	inline void EffectCameraOn()
	{
		SetEffectCamera(true);
	}

	inline void EffectCameraOff()
	{
		SetEffectCamera(false);
	}

	inline void SetEffectCamera(bool _Effect)
	{
		IsEffectCamera = _Effect;
	}
	
	

	// ���� �ִϸ��̼��� ��� ����Ǿ����� üũ 
	bool IsAnimationEnd();
	// �ִϸ��̼� ����
	void CreateAnimation(const FrameAnimationParameter& _Paramter);
	// �ִϸ��̼� ü����
	void ChangeAnimation(const std::string_view& _AnimationName, bool _ForceChange = false);

	void SetOrder(int _Order) override;

	// ���İ� ����
	void SetAlpha(int _Alpha)
	{
		Alpha = _Alpha;
	}

	void SetText(const std::string_view& _Text, const int _TextHeight = 20, const std::string_view& _TextType = "����", const TextAlign _TextAlign = TextAlign::Center, const COLORREF _TextColor = RGB(0, 0, 0));

protected:

private:
	// ��½� ����� �̹���
	GameEngineImage* Image = nullptr;
	// ī�޶��� ������ ���� ���� ���ʹ� EffectCameraOff() �� Start ���� ȣ��.
	bool IsEffectCamera = true;
	// ������� ���� �̹����� RGB�� 
	int TransColor = RGB(255, 0, 255);
	int Alpha = 255;
	int Frame = 0;
	void Render(float _DeltaTime);

	// �ؽ�Ʈ����
	void TextRender(float _DeltaTime);
	void ImageRender(float _DeltaTime);

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

		bool IsEnd();

		void Render(float _DeltaTime);

		// �ִϸ��̼� ������ ��� 
		// ���� �ε��� = 0 , ����ð� = 0 ���� �����Ͽ� ���� 
		void Reset()
		{
			CurrentIndex = 0;
			CurrentTime = 0.0f;
		}
	};

public:
	// �ӽ÷� �ۺ�. ��� 	
	std::map<std::string, FrameAnimation> Animation;
	FrameAnimation* CurrentAnimation = nullptr;

	std::string RenderText = std::string();
	int TextHeight = 0;
	std::string TextType = std::string();
	TextAlign Align = TextAlign::Left;
	COLORREF TextColor = RGB(0, 0, 0);
};

