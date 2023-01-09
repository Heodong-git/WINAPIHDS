#include "GameEngineDirectory.h"
#include <GameEngineBase/GameEngineDebug.h>

GameEngineDirectory::GameEngineDirectory()
{
}

GameEngineDirectory::~GameEngineDirectory()
{
}
 
// ���� ������ �ش� ���͸��� �ִ��� Ȯ��
void GameEngineDirectory::MoveParentToDirectory(const std::string_view& _String)
{
	std::string MovePath = "\\";
	MovePath += _String;

	Path.MoveParentToChildPath(MovePath.c_str());
}

// ���͸��̵� ( �̵��� ��θ� �ϼ���Ų��. ) 
bool GameEngineDirectory::Move(const std::string_view& _String)
{
	// ���ڷ� ���� ���ڿ��� �տ� \\ �� �ٿ��ְ� 
	std::string MovePath = "\\";
	MovePath += _String;

	// �̾�ٿ��� ��θ� ���ڷ� �־� Path �� Move �Լ��� ȣ���Ͽ� �̵��Ѵ�. 
	return Path.Move(MovePath.c_str());
}

// ���ϸ��� ��ο� �̾�ٿ��ش�. 
GameEnginePath GameEngineDirectory::GetPlusFileName(const std::string_view& _String)
{
	std::string PathString = Path.GetPathToString();
	PathString += "\\";
	PathString += _String;

	// �̾���� ���ϸ��� ��ȯ�Ѵ�. 
	return GameEnginePath(PathString);	
}

// ���������� 
bool GameEngineDirectory::MoveParent()
{
	// ���� ���� ���͸��� ��Ʈ��� �̵��� �� ����. 
	if (true == Path.IsRoot())
	{
		MsgAssert("��Ʈ ���丮�� �θ���丮�� �̵��Ҽ� �����ϴ�.");
		return false;
	}
	
	// ���ܿ� �ɸ��� �ʾҴٸ� ���� ����� ������ ��θ� �߶󳽴�. 
	Path.MoveParent();

	// �̵��߱� ������ true ��ȯ
	return true;
}