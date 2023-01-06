#pragma once
#include <map>
#include <string>
#include "GameEngineImage.h"

// 싱글톤으로 작성
// 게임내의 사운드, 이미지를 모두 관리한다. 
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

protected:

	// 이미지 로드 함수
	void ImageLoad(const std::string_view& _Path);

private:
	static GameEngineResources Inst;
	
	// constrcuter destructer
	GameEngineResources();
	~GameEngineResources();

	// 문자열 키값, GameEngineImage*  
	std::map<std::string, GameEngineImage*> AllImage;
};

