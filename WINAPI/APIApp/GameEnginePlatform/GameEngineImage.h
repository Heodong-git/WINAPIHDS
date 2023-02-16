#pragma once
#include <Windows.h>
#include <string_view>
#include <GameEngineBase/GameEngineMath.h>
#include <vector>
#include <GameEngineBase/GameEngineDebug.h>

// 이미지를 자를 경우 어떠한 형태로 저장할 것인지에 대한 구조체
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

union ColorCheck
{
	int Color;
	struct 
	{
		char r;
		char g;
		char b;
		char a;
	};
};

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

	// 인자로 Scale 을 받게 되면, 내부에서 새로운 이미지를 생성 
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

	// 현재 이미지의 크기를 float4 타입으로 반환한다.  
	float4 GetImageScale() const
	{

		return float4{ static_cast<float>(Info.bmWidth), static_cast<float>(Info.bmHeight) };
	}

	// 컷여부 반환
	bool IsImageCutting()
	{
		return IsCut;
	}

	bool GetImageCuttingCount()
	{
		return ImageCutDatas.size();
	}

	// 컷상태 이미지의 인덱스가 유효한지 확인하여 그값을 반환 
	bool IsCutIndexValid(int _Index) const
	{
		// 현재 인덱스가 0보다 작다면 false
		if (0 > _Index)
		{
			return false;
		}

		// 인덱스가 저장된 데이터의 개수보다 크거나 같다면 false 
		if (ImageCutDatas.size() <= _Index)
		{
			return false;
		}

		// 정상적인 상태라면 true 반환
		return true;
	}

	// 인덱스를 넣어주면 그 값에 해당하는 컷데이터를 반환한다. 
	ImageCutData GetCutData(int _Index) const
	{
		// 인덱스가 유효하지 않다면 assert
		if (false == IsCutIndexValid(_Index))
		{
			MsgAssert("유효하지 않은 컷 인덱스 입니다.");
		}

		// 유효한 인덱스라면 인덱스에 해당하는 컷데이터 반환 
		return ImageCutDatas[_Index];
	}

	// 기준점을 잡고 그기준점을 기준으로 하는 CUT
	void Cut(float4 _Start, float4 _End, int _X, int _Y);
	
	// 이미지의 크기를 기준으로 하는 Cut
	void Cut(int _X, int _Y);

	// BitBlt
	void BitCopy(const GameEngineImage* _OtherImage, float4 _Pos, float4 _Scale);

	// TransparentBlt
	void TransCopy(const GameEngineImage* _OtherImage, float4 _CopyCenterPos, float4 _CopySize, float4 _OtherImagePos, float4 _OtherImageSize, int _Color = RGB(255, 0, 255));
	void TransCopy(const GameEngineImage* _OtherImage, int _CutIndex, float4 _CopyCenterPos, float4 _CopySize, int _Color = RGB(255, 0, 255));

	// Alphabland
	void AlphaCopy(const GameEngineImage* _OtherImage, float4 _CopyCenterPos, float4 _CopySize, float4 _OtherImagePos, float4 _OtherImageSize, int _Alpha);
	void AlphaCopy(const GameEngineImage* _OtherImage, int _CutIndex, float4 _CopyCenterPos, float4 _CopySize, int _Color);


	DWORD GetPixelColor(float4 _Pos, DWORD _OutColor);

	DWORD GetPixelColor(int _X, int _Y, DWORD _OutColor);

protected:

private:
	// HDC : 이미지 = 2차원배열이라고 볼 수 있고, 그 2차원배열을 컨트롤(수정) 할 수 있는 권한을 의미한다.
	HDC ImageDC = nullptr;
	HBITMAP BitMap = nullptr;
	HBITMAP OldBitMap = nullptr;
	// 이미지의 정보를 저장
	BITMAP Info = BITMAP();
	
	// 이미지가 컷상태인지를 표현할 변수
	bool IsCut = false;

	// 이미지 컷데이터를 저장하는 vector 
	std::vector<ImageCutData> ImageCutDatas;

	// 이미지 크기 체크
	void ImageScaleCheck();
};

