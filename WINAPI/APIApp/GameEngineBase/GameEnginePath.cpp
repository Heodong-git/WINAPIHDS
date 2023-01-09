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

// 경로가 가진 파일명 반환
std::string GameEnginePath::GetFileName() const
{
	return Path.filename().string();
}

// Path 가 가진 문자열 반환
std::string GameEnginePath::GetPathToString() const
{
	return Path.string();
}

// 현재 경로중 가장 마지막폴더를 잘라낸다. 
// 숙제임. 경로잘라내기 
void GameEnginePath::MoveParent()
{
	// Path = 상위폴더의 경로가 된다. 즉, 현재경로중 마지막폴더 잘라내기
	Path = Path.parent_path();
}

// 인자로 들어온 경로를 이어붙여서 경로가 존재하는지 확인한다. 
void GameEnginePath::MoveParentToChildPath(const std::string_view& _String)
{
	// 경로가 마지막에 도달할때 까지 반복수행
	while (false == IsRoot())
	{
		// 이어붙여진 경로가 존재한다면 반복종료 
		if (true == IsExistsToPlusString(_String))
		{
			return;
		}

		// 존재하지 않는다면 계속해서 상위폴더로 
		MoveParent();
	}

	// 반복종료까지 경로를 찾지 못했다면 assert 
	MsgAssert("이런 경로를 자식으로 가진 부모는 존재하지 않습니다.");
}

// 인자로 들어온 경로를 이어붙인다. 
bool GameEnginePath::Move(const std::string_view& _Path)
{
	Path += _Path;

	// 이어붙인 경로가 만약 존재하지 않는 경로라면 assert 
	if (false == IsExists())
	{
		MsgAssert("존재하지 않는 경로로 이동하려고 했습니다.");
		return false;
	}

	return true;
}

bool GameEnginePath::IsRoot()
{
	// 현재경로가 마지막 경로라면 true, 아니라면 false 를 반환
	return Path.root_path() == Path;
}

// 경로가 존재하는지 확인
bool GameEnginePath::IsExists()
{
	return 0 == _access(Path.string().c_str(), 0);
}

// 인자로 경로(문자열)를 추가해주고 
// 그 경로를 포함한 경로가 존재하는지 확인 
bool GameEnginePath::IsExistsToPlusString(const std::string_view& _String)
{
	// 현재소유한 Path + 인자로 들어온 문자열
	std::string Str = GetPathToString() + _String.data();
	
	// 경로가 있다면 true 반환 없다면 false 반환
	return 0 == _access(Str.c_str(), 0);
}