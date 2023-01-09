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

	// 이미지 로드
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

	// 백버퍼에 인자로 들어온 이미지를 복사한다. 
	void BitCopy(GameEngineImage* _OtherImage, float4 _Pos, float4 _Scale);

protected:

private:
	// HDC : 이미지 = 2차원배열이라고 볼 수 있고, 그 2차원배열을 컨트롤(수정)
	// 할 수 있는 권한을 의미한다. 
	HDC ImageDC = nullptr;

	HBITMAP BitMap = nullptr;
	HBITMAP OldBitMap = nullptr;
	// 이미지의 정보를 저장
	BITMAP Info = BITMAP();

	void ImageScaleCheck();
};

