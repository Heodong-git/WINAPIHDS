#include "EndTitleLevel.h"
#include <GameEngineBase/GameEngineDirectory.h>

EndTitleLevel::EndTitleLevel()
{
}

EndTitleLevel::~EndTitleLevel()
{
}

// 
void EndTitleLevel::Loading()
{
	// �̹����ε�
	// ���͸� ��ü���� , ���͸��� ��θ� ������ ����.
	GameEngineDirectory Directory;

	// 1. ���������� �ش� ���͸��� �ִ��� Ȯ��
	Directory.MoveParentToDirectory("ContentsResources");
	// 2. ���͸��� �ִٸ� ��θ� �������ش�.  
	Directory.Move("ContentsResources");
	Directory.Move("Image");
}

void EndTitleLevel::Update()
{
}
