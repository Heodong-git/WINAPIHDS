#pragma once
#include <GameEngineCore/GameEngineActor.h>

class Monster_NightMareVirus : public GameEngineActor
{
public:
	// constrcuter destructer
	Monster_NightMareVirus();
	~Monster_NightMareVirus();

	// delete Function
	Monster_NightMareVirus(const Monster_NightMareVirus& _Other) = delete;
	Monster_NightMareVirus(Monster_NightMareVirus&& _Other) noexcept = delete;
	Monster_NightMareVirus& operator=(const Monster_NightMareVirus& _Other) = delete;
	Monster_NightMareVirus& operator=(Monster_NightMareVirus&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update() override;
	void Render() override;

private:

};
