#pragma once
#include <Windows.h>
#include <string_view>
#include <GameEngineBase/GameEngineMath.h>
#include <vector>
#include <GameEngineBase/GameEngineDebug.h>

// �̹����� �ڸ� ��� ��� ���·� ������ �������� ���� ����ü
struct ImageCutData
{
	float StartX = 0.0f;
	float StartY = 0.0f;
	float SizeX = 0.0f;
	float SizeY = 0.0f;

	float4 GetStartPos()
	{
		return { StartX, StartY };
	}

	float4 GetScale()
	{
		return { SizeX, SizeY };
	}
};

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

	// ���ڷ� Scale �� �ް� �Ǹ�, ���ο��� ���ο� �̹����� ���� 
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

	// ���� �̹����� ũ�⸦ float4 Ÿ������ ��ȯ�Ѵ�.  
	float4 GetImageScale() const
	{

		return float4{ static_cast<float>(Info.bmWidth), static_cast<float>(Info.bmHeight) };
	}

	// �ƿ��� ��ȯ
	bool IsImageCutting()
	{
		return IsCut;
	}

	// �ƻ��� �̹����� �ε����� ��ȿ���� Ȯ���Ͽ� �װ��� ��ȯ 
	bool IsCutIndexValid(int _Index) const
	{
		// ���� �ε����� 0���� �۴ٸ� false
		if (0 > _Index)
		{
			return false;
		}

		// �ε����� ����� �������� �������� ũ�ų� ���ٸ� false 
		if (ImageCutDatas.size() <= _Index)
		{
			return false;
		}

		// �������� ���¶�� true ��ȯ
		return true;
	}

	// �ε����� �־��ָ� �� ���� �ش��ϴ� �Ƶ����͸� ��ȯ�Ѵ�. 
	ImageCutData GetCutData(int _Index) const
	{
		// �ε����� ��ȿ���� �ʴٸ� assert
		if (false == IsCutIndexValid(_Index))
		{
			MsgAssert("��ȿ���� ���� �� �ε��� �Դϴ�.");
		}

		// ��ȿ�� �ε������ �ε����� �ش��ϴ� �Ƶ����� ��ȯ 
		return ImageCutDatas[_Index];
	}

	// �������� ��� �ױ������� �������� �ϴ� CUT
	void Cut(float4 _Start, float4 _End, int _X, int _Y);
	
	// �̹����� ũ�⸦ �������� �ϴ� Cut
	void Cut(int _X, int _Y);

	// BitBlt
	void BitCopy(const GameEngineImage* _OtherImage, float4 _Pos, float4 _Scale);

	// TransparentBlt
	void TransCopy(const GameEngineImage* _OtherImage, float4 _CopyCenterPos, float4 _CopySize, float4 _OtherImagePos, float4 _OtherImageSize, int _Color = RGB(255, 0, 255));
	void TransCopy(const GameEngineImage* _OtherImage, int _CutIndex, float4 _CopyCenterPos, float4 _CopySize, int _Color = RGB(255, 0, 255));
protected:

private:
	// HDC : �̹��� = 2�����迭�̶�� �� �� �ְ�, �� 2�����迭�� ��Ʈ��(����) �� �� �ִ� ������ �ǹ��Ѵ�.
	HDC ImageDC = nullptr;
	HBITMAP BitMap = nullptr;
	HBITMAP OldBitMap = nullptr;
	// �̹����� ������ ����
	BITMAP Info = BITMAP();
	
	// �̹����� �ƻ��������� ǥ���� ����
	bool IsCut = false;

	// �̹��� �Ƶ����͸� �����ϴ� vector 
	std::vector<ImageCutData> ImageCutDatas;

	// �̹��� ũ�� üũ
	void ImageScaleCheck();
};

