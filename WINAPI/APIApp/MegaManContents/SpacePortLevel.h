#pragma once
#include <GameEngineCore/GameEngineLevel.h>

// Select Level ���� ĳ���͸� �����ߴٸ�
// �����Ͽ� ���������� ������ �����ϴ� Level 
class Player_Zero;
class SpacePortLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	SpacePortLevel();
	~SpacePortLevel();

	// delete Function
	SpacePortLevel(const SpacePortLevel& _Other) = delete;
	SpacePortLevel(SpacePortLevel&& _Other) noexcept = delete;
	SpacePortLevel& operator=(const SpacePortLevel& _Other) = delete;
	SpacePortLevel& operator=(SpacePortLevel&& _Other) noexcept = delete;

	Player_Zero* GetPlayer()
	{
		return Player;
	}

protected:
	virtual void Loading() override;
	virtual void Update(float _DeltaTime) override;

	void LevelChangeEnd(GameEngineLevel* _NextLevel) override {}
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;

private:
	Player_Zero* Player = nullptr;
	
	// ���͵��� ������ġ�� �����صδ� �� �´°ǰ�..? 
	// ��.. �ϴ� �÷��̾� �ִϸ��̼Ǻ��� 
};

