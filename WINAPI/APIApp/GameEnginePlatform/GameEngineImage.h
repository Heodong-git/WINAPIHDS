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

	// ���ڷ� ũ�⸦ �ް� �Ǹ� ���ο� �̹����� �����ϴ� ���̴�. 
	bool ImageCreate(const float4& _Scale);

	// �̹��� �ε�
	bool ImageLoad(const GameEnginePath& _Path);
	bool ImageLoad(const std::string_view& _Path);

	// �̹��� Ŭ����
	void ImageClear();

	// �̹����� �׸� �� �ִ� ������ ��ȯ, HDC ��ȯ
	HDC GetImageDC() const
	{
		return ImageDC;
	}

	// ���� �̹����� ũ�⸦ ��ȯ�Ѵ�. 
	float4 GetImageScale() const
	{
		return float4{ static_cast<float>(Info.bmWidth), static_cast<float>(Info.bmHeight) };
	}

	// BitBlt 
	void BitCopy(const GameEngineImage* _OtherImage, float4 _Pos, float4 _Scale);

	// TransparentBlt.
	void TransCopy(const GameEngineImage* _OtherImage, float4 _CopyPos, float4 _CopySize, 
		           float4 _OtherImagePos, float4 _OtherImageSize, int _Color = RGB(255, 0, 255));

protected:

private:
	// HDC : �̹��� = 2�����迭�̶�� �� �� �ְ�, �� 2�����迭�� ��Ʈ��(����)
	// �� �� �ִ� ������ �ǹ��Ѵ�. 
	HDC ImageDC = nullptr;

	HBITMAP BitMap = nullptr;
	HBITMAP OldBitMap = nullptr;
	// �̹����� ������ ����
	BITMAP Info = BITMAP();

	// �̹��� ũ�� üũ
	void ImageScaleCheck();
};

