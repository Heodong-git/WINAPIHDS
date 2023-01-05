#pragma once
#include <GameEngineCore/GameEngineActor.h>

class Monster_Sigma : public GameEngineActor
{
public:
	// constrcuter destructer
	Monster_Sigma();
	~Monster_Sigma();

	// delete Function
	Monster_Sigma(const Monster_Sigma& _Other) = delete;
	Monster_Sigma(Monster_Sigma&& _Other) noexcept = delete;
	Monster_Sigma& operator=(const Monster_Sigma& _Other) = delete;
	Monster_Sigma& operator=(Monster_Sigma&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update() override;
	void Render() override;

private:

};

