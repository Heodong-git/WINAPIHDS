#include "GameEngineImage.h"
#include <GameEngineBase/GameEnginePath.h>
#include <GameEngineBase/GameEngineDebug.h>
#include "GameEngineWindow.h"

// 다른 lib 파일을 사용하겠다, 파일형식, 파일명
#pragma comment(lib, "msimg32.lib")

GameEngineImage::GameEngineImage()
{
}

GameEngineImage::~GameEngineImage()
{
	// 이미지의 소멸자에서는
	// 현재소유하고 있는 비트맵, 올드비트맵, DC를 모두 제거해준다. 
	if (nullptr != BitMap)
	{
		DeleteObject(BitMap);
		BitMap = nullptr;
	}

	if (nullptr != OldBitMap)
	{
		DeleteObject(OldBitMap);
		OldBitMap = nullptr;
	}

	if (nullptr != ImageDC)
	{
		DeleteDC(ImageDC);
		ImageDC = nullptr;
	}
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

void GameEngineImage::ImageClear()
{
	// 초기화의 경우 이미지 크기와 동일한 크기로 흰색 사각형을 한번 그려주는 것!
	Rectangle(ImageDC, 0, 0, Info.bmWidth, Info.bmHeight);
}

// 인자로 크기를 받는 ImaggeCreate
bool GameEngineImage::ImageCreate(const float4& _Scale)
{
	if (true == _Scale.IsZero())
	{
		MsgAssert("크기가 0인 이미지를 만들 수는 없습니다");
		return false;
	}
	
	// 인자로 들어온 크기로 새로운 비트맵을 생성한다.
	// window 에게 동적할당을 하라고 명령한 것 과 같음, 이미지의 소멸자에서 제거한다.
	BitMap = CreateCompatibleBitmap(GameEngineWindow::GetWindowBackBufferHdc(), _Scale.ix(), _Scale.iy());

	if (nullptr == BitMap)
	{
		MsgAssert("이미지 생성에 실패했습니다.");
		return false;
	}

	// 비트맵 생성시 DC는 연결되어 있지 않기 때문에
	// 새로운 DC를 만들어주고, DC 생성시에는 1,1, 비트맵과 연결되어 있기 때문에 
	// 아래에서 새로 생성한 비트맵과 연결해주고 이전 비트맵을 받아둔다. ( 이후 소멸자에서 제거 )
	ImageDC = CreateCompatibleDC(nullptr);

	if (nullptr == ImageDC)
	{
		MsgAssert("이미지 HDC 생성에 실패했습니다.");
		return false;
	}

	// ImageDC 1,1 배열이랑 연결되어 있다. 

	// 1, 1
	OldBitMap = static_cast<HBITMAP>(SelectObject(ImageDC, BitMap));

	// 이미지 체크 
	ImageScaleCheck();

	// 이미지를 생성했다면 한번 초기화해준다. 
	ImageClear();

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
	HBITMAP CurrentBitMap = static_cast<HBITMAP>(GetCurrentObject(ImageDC, OBJ_BITMAP));
	// 저장된 비트맵의 정보를 Info 변수에 채워준다. 
	GetObject(CurrentBitMap, sizeof(BITMAP), &Info);
}

// Copy
void GameEngineImage::BitCopy(const GameEngineImage* _OtherImage, float4 _Pos, float4 _Scale)
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

// TransCopy(이미지, 복사될 위치, 복사될 크기, 이미지의 어느위치부터 복사할건지, 그 위치부터 얼만큼의 크기로 복사될건지) 
void GameEngineImage::TransCopy(const GameEngineImage* _OtherImage, float4 _CopyPos, float4 _CopySize, 
	                                         float4 _OtherImagePos, float4 _OtherImageSize, int _Color)
{
	// 1번인자 : 복사될 DC
	// 2번인자 : 복사될 백버퍼의 x 위치
	// 3번인자 : 복사될 백버퍼의 y 위치 
	// 4번인자 : 복사될 x 사이즈
	// 5번인자 : 복사될 y 사이즈
	// 6번인자 : 복사할 이미지의 DC
	// 7번인자 : 이미지의 어느 x좌표부터 복사할건지
	// 8번인자 : 이미지의 어느 y좌표부터 복사할건지 
	// 9번인자 : 그 이미지의 x좌표부터 어디까지 복사할건지
	// 10번인자 : 그 이미지의 y좌표부터 어디까지 복사할건지 
	// 11번인자 : 화면에 보여주지 않을 색상
	TransparentBlt(ImageDC,
		_CopyPos.ix(),
		_CopyPos.iy(),
		_CopySize.ix(),
		_CopySize.iy(),
		_OtherImage->GetImageDC(),
		_OtherImagePos.ix(),
		_OtherImagePos.iy(),
		_OtherImageSize.ix(),
		_OtherImageSize.iy(),
		_Color);
}