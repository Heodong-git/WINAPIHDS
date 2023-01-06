#pragma once
#include <map>
#include <string>
#include "GameEngineImage.h"

// �̱������� �ۼ�
// ���ӳ��� ����, �̹����� ��� �����Ѵ�. 
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

	// �̹��� �ε� �Լ�
	void ImageLoad(const std::string_view& _Path);

private:
	static GameEngineResources Inst;
	
	// constrcuter destructer
	GameEngineResources();
	~GameEngineResources();

	// ���ڿ� Ű��, GameEngineImage*  
	std::map<std::string, GameEngineImage*> AllImage;
};

