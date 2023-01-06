#include "GameEngineResources.h"

// static 변수이기 때문에 cpp 최상단에 구현해야 사용가능
GameEngineResources GameEngineResources::Inst;


GameEngineResources::GameEngineResources()
{
}

GameEngineResources::~GameEngineResources()
{
}


void GameEngineResources::ImageLoad(const std::string_view& _Path)
{
}