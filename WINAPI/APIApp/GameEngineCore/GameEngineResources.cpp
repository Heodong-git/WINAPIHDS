#include "GameEngineResources.h"
#include <GameEngineBase/GameEngineString.h>
#include <GameEngineBase/GameEnginePath.h>
#include <GameEngineBase/GameEngineDebug.h>

// static 변수이기 때문에 cpp 최상단에 구현해야 사용가능
GameEngineResources GameEngineResources::Inst;

GameEngineResources::GameEngineResources()
{
}

GameEngineResources::~GameEngineResources()
{
}

// 어디서 릴리즈했더라? 확인할것
void GameEngineResources::Release()
{
	// 내가 원하는 시점에 원하는 순간 정확하게 
	for (std::pair<std::string, GameEngineImage*> Pair : AllImage)
	{
		if (nullptr == Pair.second)
		{
			continue;
		}
		delete Pair.second;
	}

	AllImage.clear();
}

// 경로를 인자로 받아서 경로, 경로에 있는 파일명을
// 오버로딩된 함수의 인자로 넣어 호출하여 이미지를 로드. 
GameEngineImage* GameEngineResources::ImageLoad(const GameEnginePath& _Path)
{
	return ImageLoad(_Path.GetPathToString().c_str(), _Path.GetFileName().c_str());
}

GameEngineImage* GameEngineResources::ImageLoad(const std::string_view& _Path, const std::string_view& _Name)
{
	// GameEngineString 클래스의 함수를 호출하여
	// 인자로 들어온 파일이름을 대문자로 변경한다. 
	std::string UpperName = GameEngineString::ToUpper(_Name);

	// 중복이미지를 로드하려고 한다면 assert 
	if (AllImage.end() != AllImage.find(UpperName))
	{
		MsgAssert("이미 로드한 이미지를 또 로드하려고 했습니다." + UpperName);
		return nullptr;
	}

	// 이미지 클래스 동적할당
	GameEngineImage* NewImage = new GameEngineImage();
	// 생성한 이미지에 이미지로드
	NewImage->ImageLoad(_Path);
	// GameEngineResources가 관리하는 map 에 저장
	AllImage.insert(std::make_pair(UpperName, NewImage));

	// 정상적으로 이미지로드가 완료 되었기 때문에 true 반환
	return NewImage;
}

GameEngineImage* GameEngineResources::ImageFind(const std::string_view& _Name)
{
	// 대문자로 저장되어 있기 때문에 파일이름을 대문자로 변환 
	std::string UpperName = GameEngineString::ToUpper(_Name);

	// 이미지를 저장하고 있는 맵에서 문자열키값을 통해 데이터를 찾는다. 
	std::map<std::string, GameEngineImage*>::iterator FindIter = AllImage.find(UpperName);

	// 현재 맵에 데이터가 저장되어 있지 않다면 저장되지 않은 이미지를 사용하려고 한 것.
	if (AllImage.end() == FindIter)
	{
		MsgAssert("로드하지 않은 이미지를 사용하려고 했습니다" + UpperName);
		return nullptr;
	}

	// 정상적으로 이미지를 찾았다면 데이터를 반환한다. 
	return FindIter->second;
}
