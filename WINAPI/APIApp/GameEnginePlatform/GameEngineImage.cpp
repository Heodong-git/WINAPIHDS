#include "GameEngineImage.h"
#include <GameEngineBase/GameEnginePath.h>
#include <GameEngineBase/GameEngineDebug.h>

GameEngineImage::GameEngineImage()
{
}

GameEngineImage::~GameEngineImage()
{
}

// 이미지생성
bool GameEngineImage::ImageCreate(HDC _Hdc)
{
	// 현재 hdc가 nullptr 이라면 생성에 실패한 것이다.
	if (nullptr == _Hdc)
	{
		MsgAssert("이미지 생성에 실패했습니다 nullptr 인 HDC를 넣어줬습니다.");
		return false;
	}

	// 인자로 들어온 DC 를 저장
	ImageDC = _Hdc;

	// 이미지스케일체크
	ImageScaleCheck();
	// 정상적으로 생성되었기 때문에 true 반환
	return true;
}

// 인자로 들어온 경로에 있는 이미지 로드 
bool GameEngineImage::ImageLoad(const GameEnginePath& _Path)
{
	return ImageLoad(_Path.GetPathToString().c_str());
}

bool GameEngineImage::ImageLoad(const std::string_view& _Path)
{
	
	// 0을 넣어주면 이미지 전체를 로드 한다는 의미, 일부만 로드할 수 도 있다.
	// LR_LOADFROMFILE : 파일에서부터 로드 하겠다는 의미
	BitMap = static_cast<HBITMAP>(LoadImageA(nullptr, _Path.data(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));

	// 비트맵이 nullptr 이라면 이미지 로드에 실패한 것이다. 
	if (nullptr == BitMap)
	{
		std::string Path = _Path.data();
		MsgAssert(Path + " 이미지 로드에 실패했습니다.");
		return false;
	}

	// 정상적으로 이미지 로드에 성공했다면 
	// 비트맵과 연결해줄 DC를 생성
	// 이때 생성된 DC 는 1,1 배열 ( 어떠한 비트맵과 연결되어 있음 )
	ImageDC = CreateCompatibleDC(nullptr);

	// DC생성에 실패했다면 assert 
	if (nullptr == ImageDC)
	{
		std::string Path = _Path.data();
		MsgAssert(Path + " 이미지 HDC 생성에 실패했습니다.");
		return false;
	}

	
	// 생성된 비트맵을 SeclectObject 함수를 사용하여 생성한 이미지와 연결해준다. 
	OldBitMap = static_cast<HBITMAP>(SelectObject(ImageDC, BitMap));

	// 이미지 스케일 체크
	ImageScaleCheck();

	return true;
}

// 이미지스케일체크
void GameEngineImage::ImageScaleCheck()
{
	// 저장된 비트맵의 정보를 Info 변수에 채워준다. 
	GetObject(BitMap, sizeof(BITMAP), &Info);
}

// Copy
void GameEngineImage::BitCopy(GameEngineImage* _OtherImage, float4 _Pos, float4 _Scale)
{
	// 특정한 HDC를 다른 HDC에 복사하는 함수
	// 현시점을 기준으로 현재 윈도우창의 DC 에 
	// 인자로 들어온 복사될 이미지를 복사한다. 
	// 즉, 윈도우 창의 특정 위치에 
	// 인자로 들어온 이미지를 x , y 의 크기로 복사
	BitBlt(
		ImageDC, // 복사 당할 이미지
		_Pos.ix(), // 위치 
		_Pos.iy(),
		_Scale.ix(),
		_Scale.iy(),
		_OtherImage->GetImageDC(), // 복사할 이미지
		0,
		0,
		SRCCOPY
	);
}