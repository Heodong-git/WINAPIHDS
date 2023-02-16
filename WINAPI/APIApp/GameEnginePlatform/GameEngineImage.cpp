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
	// �̹��� Ŭ������ �޸𸮿��� ���ŵ� ��, �ڽ��� ������ ��Ʈ��, ������Ʈ��, DC�� ��� ����
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

// �̹�������ȭ
void GameEngineImage::ImageClear()
{
	// �ʱ�ȭ�� ��� �̹��� ũ��� ������ ũ��� ��� �簢���� �ѹ� �׷��ִ� ��!
	Rectangle(ImageDC, 0, 0, Info.bmWidth, Info.bmHeight);
}

bool GameEngineImage::ImageCreate(const float4& _Scale)
{
	// Scale �� 0 �̶�� �̹����� ������ �� ����.
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
void GameEngineImage::BitCopy(const GameEngineImage* _OtherImage, float4 _CenterPos, float4 _Scale)
{
	BitBlt(
		ImageDC, // ���� ���� �̹���
		_CenterPos.ix() - _Scale.hix(), // ��ġ 
		_CenterPos.iy() - _Scale.hiy(),
		_Scale.ix(),
		_Scale.iy(),
		_OtherImage->GetImageDC(), // ������ �̹���
		0,
		0,
		SRCCOPY
	);
}

// ����Ʈ������ ��� �����ʿ����� �����Ͽ� ������Ÿ�԰� ������ ���־���Ѵ�. 
// 1������ : ����� �̹���
// 2������ : ���° �ε����� ������
// 3������ : �׷��� ��ġ�� �߽���
// 4������ : ����� ũ�� 
// 5������ : ������ �÷� 
void GameEngineImage::TransCopy(const GameEngineImage* _OtherImage, int _CutIndex, float4 _CopyCenterPos, float4 _CopySize, int _Color/* = RGB(255, 0, 255)*/)
{
	// ���� �ƻ����� �̹����� �ƴ϶�� assert 
	if (false == _OtherImage->IsCut)
	{
		MsgAssert(" �߸��� ���� �̹����� cut��� �Լ��� ����Ϸ��� �߽��ϴ�.");
		return;
	}

	// �ƻ����� �̹������ ���Ϳ� ����Ǿ��ִ� �ε����� �ش��ϴ� �Ƶ����͸� ��ȯ�Ѵ�. 
	ImageCutData Data = _OtherImage->GetCutData(_CutIndex);

	// Transparentsblt 
	TransCopy(_OtherImage, _CopyCenterPos, _CopySize, Data.GetStartPos(), Data.GetScale(), _Color);
}

// 1������ : ������̹���
// 2������ : ��µ� ��ǥ�� �߽���
// 3������ : ������ ũ��
// 4������ : ��µ� �̹����� ��ǥ
// 5������ : ��µ� �̹����� ũ�� 
// 6������ : ��½� ������ �÷� 
void GameEngineImage::TransCopy(const GameEngineImage* _OtherImage, float4 _CopyCenterPos, float4 _CopySize, float4 _OtherImagePos, float4 _OtherImageSize, int _Color)
{
	TransparentBlt(ImageDC, // ���⿡ �׷���.
		_CopyCenterPos.ix() - _CopySize.hix(), // ���⸦ ��������
		_CopyCenterPos.iy() - _CopySize.hiy(),
		_CopySize.ix(), // �� ũ���
		_CopySize.iy(),
		_OtherImage->GetImageDC(), // ������ �̹��� DC 
		_OtherImagePos.ix(),// �̹����� x y��������
		_OtherImagePos.iy(),
		_OtherImageSize.ix(), // �̹����� x y������ ��ġ��
		_OtherImageSize.iy(),
		_Color);
}

void GameEngineImage::AlphaCopy(const GameEngineImage* _OtherImage, int _CutIndex, float4 _CopyCenterPos, float4 _CopySize, int _Color)
{
	if (false == _OtherImage->IsCut)
	{
		MsgAssert(" �߸��� ���� �̹����� cut��� �Լ��� ����Ϸ��� �߽��ϴ�.");
		return;
	}

	ImageCutData Data = _OtherImage->GetCutData(_CutIndex);

	AlphaCopy(_OtherImage, _CopyCenterPos, _CopySize, Data.GetStartPos(), Data.GetScale(), _Color);
}

void GameEngineImage::AlphaCopy(const GameEngineImage* _OtherImage, float4 _CopyCenterPos, float4 _CopySize, float4 _OtherImagePos, float4 _OtherImageSize, int _Alpha)
{
	BLENDFUNCTION BF;

	BF.BlendOp = AC_SRC_OVER;
	BF.BlendFlags = 0;
	BF.SourceConstantAlpha = _Alpha;
	BF.AlphaFormat = AC_SRC_ALPHA;

	AlphaBlend(ImageDC, // ���⿡ �׷���.
		_CopyCenterPos.ix() - _CopySize.hix(), // ���⸦ ��������
		_CopyCenterPos.iy() - _CopySize.hiy(),
		_CopySize.ix(), // �� ũ���
		_CopySize.iy(),
		_OtherImage->GetImageDC(),
		_OtherImagePos.ix(),// �̹����� x y��������
		_OtherImagePos.iy(),
		_OtherImageSize.ix(), // �̹����� x y������ ��ġ��
		_OtherImageSize.iy(),
		BF);
}

// �̹����� �߶� �� �����͸� ������ vector�� ���� 
void GameEngineImage::Cut(int _X, int _Y)
{
	// ImageCutData Ŭ���� ����
	ImageCutData Data;

	// �̹��� ũ������
	Data.SizeX = static_cast<float>(GetImageScale().ix() / _X);
	Data.SizeY = static_cast<float>(GetImageScale().iy() / _Y);

	// X,Y ������ ���� �����ġ���� ����� ������ for���� Ȱ���Ͽ� �����Ѵ�. 
	for (size_t i = 0; i < _Y; i++)
	{
		for (size_t i = 0; i < _X; i++)
		{
			// �⺻������ġ 0,0 ���� ����Ǿ� �ְ�
			// ���ʿ��� ������ ������� �����߱� ������
			// ù��° �����ʹ� �ٷ� �������� �� 
			// X���� ���� �����ش�. 
			ImageCutDatas.push_back(Data);
			Data.StartX += Data.SizeX;
		}

		// X�� �۾��� ��οϷ� �Ǿ��ٸ�
		// ���� Y���۾��� ����Ǿ�� �ϱ� ������ ������ġ�� X���� ���� 0���� �ʱ�ȭ �ϰ�
		// Y���� ���� �߰����ش�. 
		Data.StartX = 0.0f;
		Data.StartY += Data.SizeY;
	}

	// ��� �۾��� �Ϸ� �Ǿ��ٸ� Cut ���°� �Ǳ� ������ true �� ����
	IsCut = true;
}


void GameEngineImage::Cut(float4 _Start, float4 _End, int _X, int _Y)
{
	// �Ƶ�����(����ü) ����
	ImageCutData Data;

	// �Ƶ������� X, Y ������ (ũ�⼳��) 
	// �� X , Y ��ǥ���� ���� X, Y ��ǥ�� ���� �Ǹ� ������ �Ÿ��� �������� �ǰ�
	// �� �Ÿ��� �� X �� ũ��, Y�� ũ���̴�. �� ���� static_cast ( ���밪 ����ȯ ) �� ���� �����Ѵ�. 
	Data.SizeX = static_cast<float>((_End.x - _Start.x) / _X);
	Data.SizeY = static_cast<float>((_End.y - _Start.y) / _Y);

	// �ƽ�����ġ ����
	Data.StartX = _Start.x;
	Data.StartY = _Start.y;

	// ��ݺ� (y��)
	for (size_t i = 0; i < _Y; i++)
	{
		// ���ݺ� (x��)
		for (size_t i = 0; i < _X; i++)
		{
			// ������ǥ, X Y ���� ũ�Ⱑ ����� ����ü�� push_back
			ImageCutDatas.push_back(Data);
			// ù��° X�� ������ǥ�� �����߱� ������ �� ����ŭ �����ش�. 
			Data.StartX += Data.SizeX;
		}

		// X�� �۾��� �Ϸ�Ǹ� ���� X���� ũ�⸦ ó�� ������ ����
		// ���� �� (���� Y��) ���� �̵��ؼ� �۾��ؾ��ϱ� ����
		Data.StartX = _Start.x;
		Data.StartY += Data.SizeY;
	}

	// �Ϸ�Ǿ��ٸ� true 
	IsCut = true;
}

// �ش� ��ġ�� �ȼ� ���� ��ȯ�Ѵ�. 
DWORD GameEngineImage::GetPixelColor(float4 _Pos, DWORD _OutColor)
{
	return GetPixelColor(_Pos.ix(), _Pos.iy(), _OutColor);
}


DWORD GameEngineImage::GetPixelColor(int _X, int _Y, DWORD _OutColor)
{
	if (_X < 0)
	{
		return _OutColor;
	}
	if (_X >= GetImageScale().ix())
	{
		return _OutColor;
	}
	if (_Y < 0)
	{
		return _OutColor;
	}
	if (_Y >= GetImageScale().iy())
	{
		return _OutColor;
	}

	return GetPixel(ImageDC, _X, _Y);
}