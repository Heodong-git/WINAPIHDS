#include "SelectLevel.h"
#include <GameEngineBase/GameEngineDirectory.h>

SelectLevel::SelectLevel()
{
}

SelectLevel::~SelectLevel()
{
}

// 1. �÷����� ĳ���� 
// 2. ���ȭ��
// 3. UI 
// 4. Sound 
void SelectLevel::Loading()
{
	GameEngineDirectory Directory;
	// ���������� �ش� ���͸��� �ִ��� Ȯ��
	Directory.MoveParentToDirectory("ContentsResources");

	// ���͸��� �ִٸ� ��θ� �������ش�.  
	Directory.Move("ContentsResources");
	Directory.Move("Image");
}

void SelectLevel::Update()
{
}
