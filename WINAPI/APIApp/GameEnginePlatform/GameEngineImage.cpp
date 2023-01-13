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
void GameEngineImage::BitCopy(const GameEngineImage* _OtherImage, float4 _CenterPos, float4 _Scale)
{
	BitBlt(
		ImageDC, // 복사 당할 이미지
		_CenterPos.ix() - _Scale.hix(), // 위치 
		_CenterPos.iy() - _Scale.hiy(),
		_Scale.ix(),
		_Scale.iy(),
		_OtherImage->GetImageDC(), // 복사할 이미지
		0,
		0,
		SRCCOPY
	);
}

// 디폴트인자의 경우 구현쪽에서는 생략하여 인자의타입과 변수명만 써주어야한다. 
// 1번인자 : 출력할 이미지
// 2번인자 : 몇번째 인덱스의 컷인지
// 3번인자 : 그려질 위치의 중심점
// 4번인자 : 복사될 크기 
// 5번인자 : 제외할 컬러 
void GameEngineImage::TransCopy(const GameEngineImage* _OtherImage, int _CutIndex, float4 _CopyCenterPos, float4 _CopySize, int _Color/* = RGB(255, 0, 255)*/)
{
	// 현재 컷상태인 이미지가 아니라면 assert 
	if (false == _OtherImage->IsCut)
	{
		MsgAssert(" 잘리지 않은 이미지로 cut출력 함수를 사용하려고 했습니다.");
		return;
	}

	// 컷상태인 이미지라면 벡터에 저장되어있는 인덱스에 해당하는 컷데이터를 반환한다. 
	ImageCutData Data = _OtherImage->GetCutData(_CutIndex);

	// Transparentsblt 
	TransCopy(_OtherImage, _CopyCenterPos, _CopySize, Data.GetStartPos(), Data.GetScale(), _Color);
}

// 1번인자 : 출력할이미지
// 2번인자 : 출력될 좌표의 중심점
// 3번인자 : 복사할 크기
// 4번인자 : 출력될 이미지의 좌표
// 5번인자 : 출력될 이미지의 크기 
// 6번인자 : 출력시 제외할 컬러 
void GameEngineImage::TransCopy(const GameEngineImage* _OtherImage, float4 _CopyCenterPos, float4 _CopySize, float4 _OtherImagePos, float4 _OtherImageSize, int _Color)
{
	TransparentBlt(ImageDC, // 여기에 그려라.
		_CopyCenterPos.ix() - _CopySize.hix(), // 여기를 시작으로
		_CopyCenterPos.iy() - _CopySize.hiy(),
		_CopySize.ix(), // 이 크기로
		_CopySize.iy(),
		_OtherImage->GetImageDC(), // 복사할 이미지 DC 
		_OtherImagePos.ix(),// 이미지의 x y에서부터
		_OtherImagePos.iy(),
		_OtherImageSize.ix(), // 이미지의 x y까지의 위치를
		_OtherImageSize.iy(),
		_Color);
}

// 이미지를 잘라서 그 데이터를 소유한 vector에 저장 
void GameEngineImage::Cut(int _X, int _Y)
{
	// ImageCutData 클래스 생성
	ImageCutData Data;

	// 이미지 크기저장
	Data.SizeX = static_cast<float>(GetImageScale().ix() / _X);
	Data.SizeY = static_cast<float>(GetImageScale().iy() / _Y);

	// X,Y 축으로 각각 어느위치까지 출력할 것인지 for문을 활용하여 저장한다. 
	for (size_t i = 0; i < _Y; i++)
	{
		for (size_t i = 0; i < _X; i++)
		{
			// 기본시작위치 0,0 으로 저장되어 있고
			// 위쪽에서 어디까지 출력할지 저장했기 때문에
			// 첫번째 데이터는 바로 저장해준 후 
			// X축의 값을 더해준다. 
			ImageCutDatas.push_back(Data);
			Data.StartX += Data.SizeX;
		}

		// X축 작업이 모두완료 되었다면
		// 다음 Y축작업이 진행되어야 하기 때문에 시작위치의 X축의 값을 0으로 초기화 하고
		// Y축의 값을 추가해준다. 
		Data.StartX = 0.0f;
		Data.StartY += Data.SizeY;
	}

	// 모든 작업이 완료 되었다면 Cut 상태가 되기 때문에 true 로 변경
	IsCut = true;
}


void GameEngineImage::Cut(float4 _Start, float4 _End, int _X, int _Y)
{
	// 컷데이터(구조체) 생성
	ImageCutData Data;

	// 컷데이터의 X, Y 사이즈 (크기설정) 
	// 끝 X , Y 좌표에서 시작 X, Y 좌표를 빼게 되면 사이의 거리가 구해지게 되고
	// 이 거리가 곧 X 의 크기, Y의 크기이다. 그 값을 static_cast ( 값대값 형변환 ) 을 통해 저장한다. 
	Data.SizeX = static_cast<float>((_End.x - _Start.x) / _X);
	Data.SizeY = static_cast<float>((_End.y - _Start.y) / _Y);

	// 컷시작위치 저장
	Data.StartX = _Start.x;
	Data.StartY = _Start.y;

	// 행반복 (y축)
	for (size_t i = 0; i < _Y; i++)
	{
		// 열반복 (x축)
		for (size_t i = 0; i < _X; i++)
		{
			// 시작좌표, X Y 축의 크기가 저장된 구조체를 push_back
			ImageCutDatas.push_back(Data);
			// 첫번째 X축 시작좌표를 저장했기 때문에 그 값만큼 더해준다. 
			Data.StartX += Data.SizeX;
		}

		// X축 작업이 완료되면 시작 X축의 크기를 처음 값으로 변경
		// 다음 행 (다음 Y축) 으로 이동해서 작업해야하기 때문
		Data.StartX = _Start.x;
		Data.StartY += Data.SizeY;
	}

	// 완료되었다면 true 
	IsCut = true;
}