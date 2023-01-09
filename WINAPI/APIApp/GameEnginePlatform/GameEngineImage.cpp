#include "GameEngineImage.h"
#include <GameEngineBase/GameEnginePath.h>
#include <GameEngineBase/GameEngineDebug.h>

GameEngineImage::GameEngineImage()
{
}

GameEngineImage::~GameEngineImage()
{
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
	// ����� ��Ʈ���� ������ Info ������ ä���ش�. 
	GetObject(BitMap, sizeof(BITMAP), &Info);
}

// Copy
void GameEngineImage::BitCopy(GameEngineImage* _OtherImage, float4 _Pos, float4 _Scale)
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