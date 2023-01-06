#include "GameEngineDirectory.h"
#include <GameEngineBase/GameEngineDebug.h>

GameEngineDirectory::GameEngineDirectory()
{
}

GameEngineDirectory::~GameEngineDirectory()
{
}
 
// 상위 폴더에 해당 디렉터리가 있는지 확인
void GameEngineDirectory::MoveParentToDirectory(const std::string_view& _String)
{
	std::string MovePath = "\\";
	MovePath += _String;

	Path.MoveParentToChildPath(MovePath.c_str());
}

// 디렉터리이동 ( 이동할 경로를 완성시킨다. ) 
bool GameEngineDirectory::Move(const std::string_view& _String)
{
	// 인자로 들어온 문자열의 앞에 \\ 를 붙여주고 
	std::string MovePath = "\\";
	MovePath += _String;

	// 이어붙여준 경로를 인자로 넣어 Path 의 Move 함수를 호출하여 이동한다. 
	return Path.Move(MovePath.c_str());
}

//GameEnginePath GameEngineDirectory::GetPlusFileName(const std::string_view& _String)
//{
//	/*std::string PathString = Path.GetPathToString();
//	PathString += "\\";
//	PathString += _String;
//	GameEnginePath NewPath = PathString;
//
//	return NewPath;*/	
//}

// 상위폴더로 
bool GameEngineDirectory::MoveParent()
{
	// 만약 현재 디렉터리가 루트라면 이동할 수 없다. 
	if (true == Path.IsRoot())
	{
		MsgAssert("루트 디렉토리는 부모디렉토리로 이동할수 없습니다.");
		return false;
	}
	
	// 예외에 걸리지 않았다면 현재 경로중 마지막 경로를 잘라낸다. 
	Path.MoveParent();

	// 이동했기 때문에 true 반환
	return true;
}