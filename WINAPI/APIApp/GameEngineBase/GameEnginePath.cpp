#include "GameEnginePath.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <Windows.h>
#include <io.h>

GameEnginePath::GameEnginePath()
	: Path(std::filesystem::current_path())
{
}

GameEnginePath::GameEnginePath(std::filesystem::path _Path) 
	: Path(_Path)
{
}

GameEnginePath::GameEnginePath(const std::string& _Path)
	: Path(_Path)
{
}


GameEnginePath::GameEnginePath(const GameEnginePath& _Other)
{
}

GameEnginePath::GameEnginePath(GameEnginePath&& _Other)
	: Path(_Other.Path)
{

}

GameEnginePath::~GameEnginePath()
{
}

// Path �� ���� ���ڿ� ��ȯ
std::string GameEnginePath::GetPathToString() const
{
	return Path.string();
}

// ���� ����� ���� ������������ �߶󳽴�. 
// ������. ����߶󳻱� 
void GameEnginePath::MoveParent()
{
	// Path = ���������� ��ΰ� �ȴ�. ��, �������� ���������� �߶󳻱�
	Path = Path.parent_path();
}

// ���ڷ� ���� ��θ� �̾�ٿ��� ��ΰ� �����ϴ��� Ȯ���Ѵ�. 
void GameEnginePath::MoveParentToChildPath(const std::string_view& _String)
{
	// ��ΰ� �������� �����Ҷ� ���� �ݺ�����
	while (false == IsRoot())
	{
		// �̾�ٿ��� ��ΰ� �����Ѵٸ� �ݺ����� 
		if (true == IsExistsToPlusString(_String))
		{
			return;
		}

		// �������� �ʴ´ٸ� ����ؼ� ���������� 
		MoveParent();
	}

	// �ݺ�������� ��θ� ã�� ���ߴٸ� assert 
	MsgAssert("�̷� ��θ� �ڽ����� ���� �θ�� �������� �ʽ��ϴ�.");
}

// ���ڷ� ���� ��θ� �̾���δ�. 
bool GameEnginePath::Move(const std::string_view& _Path)
{
	Path += _Path;

	// �̾���� ��ΰ� ���� �������� �ʴ� ��ζ�� assert 
	if (false == IsExists())
	{
		MsgAssert("�������� �ʴ� ��η� �̵��Ϸ��� �߽��ϴ�.");
		return false;
	}

	return true;
}

bool GameEnginePath::IsRoot()
{
	// �����ΰ� ������ ��ζ�� true, �ƴ϶�� false �� ��ȯ
	return Path.root_path() == Path;
}

// ��ΰ� �����ϴ��� Ȯ��
bool GameEnginePath::IsExists()
{
	return 0 == _access(Path.string().c_str(), 0);
}

// ���ڷ� ���(���ڿ�)�� �߰����ְ� 
// �� ��θ� ������ ��ΰ� �����ϴ��� Ȯ�� 
bool GameEnginePath::IsExistsToPlusString(const std::string_view& _String)
{
	// ��������� Path + ���ڷ� ���� ���ڿ�
	std::string Str = GetPathToString() + _String.data();
	
	// ��ΰ� �ִٸ� true ��ȯ ���ٸ� false ��ȯ
	return 0 == _access(Str.c_str(), 0);
}