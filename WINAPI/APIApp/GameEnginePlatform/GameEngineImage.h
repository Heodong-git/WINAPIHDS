#pragma once
#include <Windows.h>
#include <string_view>
#include <GameEngineBase/GameEngineMath.h>

// ���漱��
class GameEnginePath;
class GameEngineImage
{
public:
	// constrcuter destructer
	GameEngineImage();
	~GameEngineImage();

	// delete Function
	GameEngineImage(const GameEngineImage& _Other) = delete;
	GameEngineImage(GameEngineImage&& _Other) noexcept = delete;
	GameEngineImage& operator=(const GameEngineImage& _Other) = delete;
	GameEngineImage& operator=(GameEngineImage&& _Other) noexcept = delete;

	// �̹��� ����
	bool ImageCreate(HDC _Hdc);

	// �̹��� �ε�
	bool ImageLoad(const GameEnginePath& _Path);
	bool ImageLoad(const std::string_view& _Path);

	HDC GetImageDC() const
	{
		return ImageDC;
	}

	float4 GetImageScale() const
	{
		return float4{ static_cast<float>(Info.bmWidth), static_cast<float>(Info.bmHeight) };
	}

	// ����ۿ� ���ڷ� ���� �̹����� �����Ѵ�. 
	void BitCopy(GameEngineImage* _OtherImage, float4 _Pos, float4 _Scale);

protected:

private:
	// HDC : �̹��� = 2�����迭�̶�� �� �� �ְ�, �� 2�����迭�� ��Ʈ��(����)
	// �� �� �ִ� ������ �ǹ��Ѵ�. 
	HDC ImageDC = nullptr;

	HBITMAP BitMap = nullptr;
	HBITMAP OldBitMap = nullptr;
	// �̹����� ������ ����
	BITMAP Info = BITMAP();

	void ImageScaleCheck();
};

