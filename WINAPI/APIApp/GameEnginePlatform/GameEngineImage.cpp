#include "GameEngineImage.h"
#include <GameEngineBase/GameEnginePath.h>
#include <GameEngineBase/GameEngineDebug.h>
#include "GameEngineWindow.h"

// �ٸ� lib ������ ����ϰڴ�, ��������, ���ϸ�
#pragma comment(lib, "msimg32.lib")

GameEngineImage::GameEngineImage()
{
}

GameEngineImage::~GameEngineImage()
{
	// �̹����� �Ҹ��ڿ�����
	// ��������ϰ� �ִ� ��Ʈ��, �õ��Ʈ��, DC�� ��� �������ش�. 
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

// �̹�������
bool GameEngineImage::ImageCreate(HDC _Hdc)
{
	// ���� hdc�� nullptr �̶�� ������ ������ ���̴�.
	if (nullptr == _Hdc)
	{
		MsgAssert("�̹��� ������ �����߽��ϴ� nullptr �� HDC�� �־�����ϴ�.");
		return false;
	}

	// ���ڷ� ���� DC �� ����	
	ImageDC = _Hdc;

	// �̹���������üũ
	ImageScaleCheck();
	// ���������� �����Ǿ��� ������ true ��ȯ
	return true;
}

void GameEngineImage::ImageClear()
{
	// �ʱ�ȭ�� ��� �̹��� ũ��� ������ ũ��� ��� �簢���� �ѹ� �׷��ִ� ��!
	Rectangle(ImageDC, 0, 0, Info.bmWidth, Info.bmHeight);
}

// ���ڷ� ũ�⸦ �޴� ImaggeCreate
bool GameEngineImage::ImageCreate(const float4& _Scale)
{
	if (true == _Scale.IsZero())
	{
		MsgAssert("ũ�Ⱑ 0�� �̹����� ���� ���� �����ϴ�");
		return false;
	}
	
	// ���ڷ� ���� ũ��� ���ο� ��Ʈ���� �����Ѵ�.
	// window ���� �����Ҵ��� �϶�� ����� �� �� ����, �̹����� �Ҹ��ڿ��� �����Ѵ�.
	BitMap = CreateCompatibleBitmap(GameEngineWindow::GetWindowBackBufferHdc(), _Scale.ix(), _Scale.iy());

	if (nullptr == BitMap)
	{
		MsgAssert("�̹��� ������ �����߽��ϴ�.");
		return false;
	}

	// ��Ʈ�� ������ DC�� ����Ǿ� ���� �ʱ� ������
	// ���ο� DC�� ������ְ�, DC �����ÿ��� 1,1, ��Ʈ�ʰ� ����Ǿ� �ֱ� ������ 
	// �Ʒ����� ���� ������ ��Ʈ�ʰ� �������ְ� ���� ��Ʈ���� �޾Ƶд�. ( ���� �Ҹ��ڿ��� ���� )
	ImageDC = CreateCompatibleDC(nullptr);

	if (nullptr == ImageDC)
	{
		MsgAssert("�̹��� HDC ������ �����߽��ϴ�.");
		return false;
	}

	// ImageDC 1,1 �迭�̶� ����Ǿ� �ִ�. 

	// 1, 1
	OldBitMap = static_cast<HBITMAP>(SelectObject(ImageDC, BitMap));

	// �̹��� üũ 
	ImageScaleCheck();

	// �̹����� �����ߴٸ� �ѹ� �ʱ�ȭ���ش�. 
	ImageClear();

	return true;
}
// ���ڷ� ���� ��ο� �ִ� �̹��� �ε� 
bool GameEngineImage::ImageLoad(const GameEnginePath& _Path)
{
	return ImageLoad(_Path.GetPathToString().c_str());
}

bool GameEngineImage::ImageLoad(const std::string_view& _Path)
{
	
	// 0�� �־��ָ� �̹��� ��ü�� �ε� �Ѵٴ� �ǹ�, �Ϻθ� �ε��� �� �� �ִ�.
	// LR_LOADFROMFILE : ���Ͽ������� �ε� �ϰڴٴ� �ǹ�
	BitMap = static_cast<HBITMAP>(LoadImageA(nullptr, _Path.data(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));

	// ��Ʈ���� nullptr �̶�� �̹��� �ε忡 ������ ���̴�. 
	if (nullptr == BitMap)
	{
		std::string Path = _Path.data();
		MsgAssert(Path + " �̹��� �ε忡 �����߽��ϴ�.");
		return false;
	}

	// ���������� �̹��� �ε忡 �����ߴٸ� 
	// ��Ʈ�ʰ� �������� DC�� ����
	// �̶� ������ DC �� 1,1 �迭 ( ��� ��Ʈ�ʰ� ����Ǿ� ���� )
	ImageDC = CreateCompatibleDC(nullptr);

	// DC������ �����ߴٸ� assert 
	if (nullptr == ImageDC)
	{
		std::string Path = _Path.data();
		MsgAssert(Path + " �̹��� HDC ������ �����߽��ϴ�.");
		return false;
	}

	
	// ������ ��Ʈ���� SeclectObject �Լ��� ����Ͽ� ������ �̹����� �������ش�. 
	OldBitMap = static_cast<HBITMAP>(SelectObject(ImageDC, BitMap));

	// �̹��� ������ üũ
	ImageScaleCheck();

	return true;
}

// �̹���������üũ
void GameEngineImage::ImageScaleCheck()
{
	HBITMAP CurrentBitMap = static_cast<HBITMAP>(GetCurrentObject(ImageDC, OBJ_BITMAP));
	// ����� ��Ʈ���� ������ Info ������ ä���ش�. 
	GetObject(CurrentBitMap, sizeof(BITMAP), &Info);
}

// Copy
void GameEngineImage::BitCopy(const GameEngineImage* _OtherImage, float4 _Pos, float4 _Scale)
{
	// Ư���� HDC�� �ٸ� HDC�� �����ϴ� �Լ�
	// �������� �������� ���� ������â�� DC �� 
	// ���ڷ� ���� ����� �̹����� �����Ѵ�. 
	// ��, ������ â�� Ư�� ��ġ�� 
	// ���ڷ� ���� �̹����� x , y �� ũ��� ����
	BitBlt(
		ImageDC, // ���� ���� �̹���
		_Pos.ix(), // ��ġ 
		_Pos.iy(),
		_Scale.ix(),
		_Scale.iy(),
		_OtherImage->GetImageDC(), // ������ �̹���
		0,
		0,
		SRCCOPY
	);
}

// TransCopy(�̹���, ����� ��ġ, ����� ũ��, �̹����� �����ġ���� �����Ұ���, �� ��ġ���� ��ŭ�� ũ��� ����ɰ���) 
void GameEngineImage::TransCopy(const GameEngineImage* _OtherImage, float4 _CopyPos, float4 _CopySize, 
	                                         float4 _OtherImagePos, float4 _OtherImageSize, int _Color)
{
	// 1������ : ����� DC
	// 2������ : ����� ������� x ��ġ
	// 3������ : ����� ������� y ��ġ 
	// 4������ : ����� x ������
	// 5������ : ����� y ������
	// 6������ : ������ �̹����� DC
	// 7������ : �̹����� ��� x��ǥ���� �����Ұ���
	// 8������ : �̹����� ��� y��ǥ���� �����Ұ��� 
	// 9������ : �� �̹����� x��ǥ���� ������ �����Ұ���
	// 10������ : �� �̹����� y��ǥ���� ������ �����Ұ��� 
	// 11������ : ȭ�鿡 �������� ���� ����
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