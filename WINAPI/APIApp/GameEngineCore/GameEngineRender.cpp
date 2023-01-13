#include "GameEngineRender.h"
#include <GameEngineCore/GameEngineResources.h>
#include "GameEngineActor.h"
#include "GameEngineLevel.h"
#include <GameEnginePlatform/GameEngineWindow.h>

GameEngineRender::GameEngineRender()
{
}

GameEngineRender::~GameEngineRender()
{
}

// ��½� ����� �̹��� ����
void GameEngineRender::SetImage(const std::string_view& _ImageName)
{
	// ���ӿ��� ���ҽ� Ŭ�������� �̹����� ã�Ƽ� ����
	Image = GameEngineResources::GetInst().ImageFind(_ImageName);
}

// ���ڷ� ���� ������ order ����
void GameEngineRender::SetOrder(int _Order)
{
	Order = _Order;
	// ���� �־��� �Ŀ� �������� ������ ������ Level �� ������ map �� �߰�
	Owner->GetLevel()->PushRender(this);
}

// �����Ӱ� ����
void GameEngineRender::SetFrame(int _Frame)
{
	// �̹����� ���ٸ�
	if (nullptr == Image)
	{
		MsgAssert("�̹����� �������� �ʴ� �������� �������� �����Ϸ��� �߽��ϴ�.");
	}

	// Cut �̹����� �ƴ϶�� 
	if (false == Image->IsImageCutting())
	{
		MsgAssert("�߷��ִ� �̹����� �������� �������� �� �ֽ��ϴ�.");
	}

	// Index ������ �Ѿ�ٸ� 
	if (false == Image->IsCutIndexValid(_Frame))
	{
		MsgAssert("�������� ���� �̹����ε��� �Դϴ�.");
	}

	Frame = _Frame;
}
// ������
void GameEngineRender::Render(float _DeltaTime)
{
	// ��µ� ��ǥ�� �������� ������ ������ ��ġ + �߰� �����ǰ�
	float4 RenderPos = Owner->GetPos() + Position;

	// Ŀ�õ� �̹������
	if (true == Image->IsImageCutting())
	{
		// �����Ӵ� Ʈ����ī�� ���
		GameEngineWindow::GetDoubleBufferImage()->TransCopy(Image, Frame, RenderPos, Scale);
	}
	// Ŀ�õ� �̹����� �ƴ϶��
	else
	{
		// �׳� �̹��� ��ü�� �Էµ� ũ��� ����Ѵ�. 
		GameEngineWindow::GetDoubleBufferImage()->TransCopy(Image, RenderPos, Scale, { 0, 0 }, Image->GetImageScale());
	}
}