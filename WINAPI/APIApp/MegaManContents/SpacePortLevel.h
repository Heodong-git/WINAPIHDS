#pragma once
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineResources.h>

class Player_Zero;
class Boss_Colonel;
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

	inline Boss_Colonel* GetBoss()
	{
		return m_Boss;
	}

	inline float4 GetStartCameraPos()
	{
		return m_StartCameraPos;
	}

	inline bool IsHeightSection()
	{
		return m_HeightSection;
	}

	inline bool IsSectionClear()
	{
		return m_SectionClear;
	}

	inline float4 GetBossSectionPos() const
	{
		return m_BossSectionPos;
	}

	inline bool IsStageClear()
	{
		return m_StageClearBGM;
	}

protected:
	virtual void Loading() override;
	virtual void Update(float _DeltaTime) override;

	void LevelChangeEnd(GameEngineLevel* _NextLevel) override {}
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;


private:
	// 사운드재생용 
	GameEngineSoundPlayer BGMPlayer;
	GameEngineSoundPlayer m_ClearBGM;
	Player_Zero* m_Player = nullptr;
	Boss_Colonel* m_Boss = nullptr;
	// 시작카메라좌표
	float4	     m_StartCameraPos = float4::Zero;
	float4		 m_FirstSectionPos = float4{ 14800, 6240 };
	float4		 m_SecondSectionPos = float4{ 14800, 5280 } ;
	float4		 m_ThirdSectionPos = float4{ 14800, 4800 };
	float4		 m_FourthSectionPos = float4{ 14800, 3840 };
	float4	     m_FifthSectionPos = float4{ 14800, 3360 };
	float4		 m_SixthSectionPos = float4{ 14800, 2400 };
	float4		 m_SeventhSectionPos = float4{ 14800, 1580 };
	float4		 m_EighthSectionPos = float4{ 14800, 960 };
	float4		 m_NinthSectionPos = float4{ 14800, 150 };
	float4		 m_BossSectionPos = float4{ 17750 , 150 };

	float		 m_SectionClearXPos = 14800.0f;
	float		 m_BossContactXPos = 17775.0f;

	float		 m_CameraMoveSpeed = 500.0f;
	float        m_BossRoomSpeed = 100.0f;

	bool		 m_StageClearBGM = false;
	float		 m_LevelChangeCount = 7.0f;

	void SoundLoad();
	void ImageLoad();
	void ActorLoad();
	void CameraLoad();

	// 후... 
	bool				m_HeightSection = false;
	bool				m_FirstSection = false;
	bool				m_SecondSection = false;
	bool				m_ThirdSection = false;
	bool				m_FourthSection = false;
	bool				m_FifthSection = false;
	bool				m_SixthSection = false;
	bool			    m_SeventhSection = false;
	bool				m_EightSection = false;
	bool				m_NinthSection = false;
	bool				m_SectionClear = false;

	// 보스룸 진입시 사용
	bool				m_BossSection = false;
	bool				m_BossRoomSound = false;
};

