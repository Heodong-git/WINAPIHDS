#pragma once
#include <map>
#include <string>
#include <GameEnginePlatform/GameEngineImage.h>

// 싱글톤으로 작성
// 게임내의 사운드, 이미지를 모두 관리한다. 
class GameEnginePath;
class GameEngineResources
{
public:
	// delete Function
	GameEngineResources(const GameEngineResources& _Other) = delete;
	GameEngineResources(GameEngineResources&& _Other) noexcept = delete;
	GameEngineResources& operator=(const GameEngineResources& _Other) = delete;
	GameEngineResources& operator=(GameEngineResources&& _Other) noexcept = delete;

	static GameEngineResources& GetInst()
	{
		return Inst;
	}

	bool ImageLoad(const GameEnginePath& _Path);

	bool ImageLoad(const std::string_view& _Path, const std::string_view& _Name);

	GameEngineImage* ImageFind(const std::string_view& _Name);

	void Relase();

protected:

private:
	static GameEngineResources Inst;
	
	// constrcuter destructer
	GameEngineResources();
	~GameEngineResources();

	// 문자열 키값, GameEngineImage*  
	std::map<std::string, GameEngineImage*> AllImage;
};

