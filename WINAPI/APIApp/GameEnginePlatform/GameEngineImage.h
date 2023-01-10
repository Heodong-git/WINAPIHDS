#pragma once
#include <Windows.h>
#include <string_view>
#include <GameEngineBase/GameEngineMath.h>

// 전방선언
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

	// 이미지 생성
	bool ImageCreate(HDC _Hdc);

	// 인자로 크기를 받게 되면 새로운 이미지를 생성하는 것이다. 
	bool ImageCreate(const float4& _Scale);

	// 이미지 로드
	bool ImageLoad(const GameEnginePath& _Path);
	bool ImageLoad(const std::string_view& _Path);

	// 이미지 클리어
	void ImageClear();

	// 이미지에 그릴 수 있는 권한을 반환, HDC 반환
	HDC GetImageDC() const
	{
		return ImageDC;
	}

	// 현재 이미지의 크기를 반환한다. 
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
	// HDC : 이미지 = 2차원배열이라고 볼 수 있고, 그 2차원배열을 컨트롤(수정)
	// 할 수 있는 권한을 의미한다. 
	HDC ImageDC = nullptr;

	HBITMAP BitMap = nullptr;
	HBITMAP OldBitMap = nullptr;
	// 이미지의 정보를 저장
	BITMAP Info = BITMAP();

	// 이미지 크기 체크
	void ImageScaleCheck();
};

