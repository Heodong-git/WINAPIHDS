#pragma once
#include <string_view>
#include <vector>
#include "GameEnginePath.h"

class GameEngineFile;
class GameEngineDirectory
{
public:
	// constrcuter destructer
	GameEngineDirectory();
	~GameEngineDirectory();

	// delete Function
	GameEngineDirectory(const GameEngineDirectory& _Other) = delete;
	GameEngineDirectory(GameEngineDirectory&& _Other) noexcept = delete;
	GameEngineDirectory& operator=(const GameEngineDirectory& _Other) = delete;
	GameEngineDirectory& operator=(GameEngineDirectory&& _Other) noexcept = delete;

	// 디렉터리에 파일이 있는지 확인
	bool IsFile(const std::string_view& _FileName);

	// 상위폴더이동
	bool MoveParent();

	// 
	void MoveParentToDirectory(const std::string_view& _String);

	bool Move(const std::string_view& _String);

	GameEnginePath GetPlusFileName(const std::string_view& _String);

protected:

private:
	// "D:\Project\AR45\WINAPI\APIApp\ContentsResources\Iamge\";
	GameEnginePath Path;
};

