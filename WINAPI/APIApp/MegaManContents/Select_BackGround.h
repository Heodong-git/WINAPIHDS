#pragma once
#include <GameEngineCore/GameEngineActor.h>

// 얘를 상속받는 백그라운드 클래스들을 만들면 되지 않을까 
// 일단 수업들어보고 선생님꺼 보고 해보자
// 백그라운드는 현재 어떤 레벨이냐에 따라서 enum class 를 통해 
// 값에 이름을 부여하고, 렌더링 할 때에는 어떤 타입이냐에 따라서 다르게 출력한다. 
class Select_BackGround : public GameEngineActor
{
public:
	// constrcuter destructer
	Select_BackGround();
	~Select_BackGround();

	// delete Function
	Select_BackGround(const Select_BackGround& _Other) = delete;
	Select_BackGround(Select_BackGround&& _Other) noexcept = delete;
	Select_BackGround& operator=(const Select_BackGround& _Other) = delete;
	Select_BackGround& operator=(Select_BackGround&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	GameEngineRender* m_Render = nullptr;
};

