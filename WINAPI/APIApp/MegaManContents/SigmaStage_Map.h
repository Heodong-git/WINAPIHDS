#pragma once
#include <GameEngineCore/GameEngineActor.h>

// 얘를 상속받는 백그라운드 클래스들을 만들면 되지 않을까 
// 일단 수업들어보고 선생님꺼 보고 해보자
// 백그라운드는 현재 어떤 레벨이냐에 따라서 enum class 를 통해 
// 값에 이름을 부여하고, 렌더링 할 때에는 어떤 타입이냐에 따라서 다르게 출력한다. 
class SigmaStage_Map : public GameEngineActor
{
public:
	// constrcuter destructer
	SigmaStage_Map();
	~SigmaStage_Map();

	// delete Function
	SigmaStage_Map(const SigmaStage_Map& _Other) = delete;
	SigmaStage_Map(SigmaStage_Map&& _Other) noexcept = delete;
	SigmaStage_Map& operator=(const SigmaStage_Map& _Other) = delete;
	SigmaStage_Map& operator=(SigmaStage_Map&& _Other) noexcept = delete;

protected:
	void Start() override;
private:
};

