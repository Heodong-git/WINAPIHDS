#pragma once
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineResources.h>

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

	inline Player_Zero* GetPlayer()
	{
		return m_Player;
	}

	inline float4 GetStartCameraPos()
	{
		return m_StartCameraPos;
	}

protected:
	virtual void Loading() override;
	virtual void Update(float _DeltaTime) override;

	void LevelChangeEnd(GameEngineLevel* _NextLevel) override {}
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;

	GameEngineSoundPlayer BGMPlayer;

private:
	Player_Zero* m_Player = nullptr;
	// 시작카메라좌표
	float4	     m_StartCameraPos = float4::Zero;

	void SoundLoad();
	void ImageLoad();
};

