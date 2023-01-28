#pragma once
#include <GameEngineCore/GameEngineLevel.h>

// Ό³Έν :
class ImageTestLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	ImageTestLevel();
	~ImageTestLevel();

	// delete Function
	ImageTestLevel(const ImageTestLevel& _Other) = delete;
	ImageTestLevel(ImageTestLevel&& _Other) noexcept = delete;
	ImageTestLevel& operator=(const ImageTestLevel& _Other) = delete;
	ImageTestLevel& operator=(ImageTestLevel&& _Other) noexcept = delete;

protected:
	virtual void Loading() override;
	virtual void Update(float _DeltaTime) override;

	void LevelChangeEnd(GameEngineLevel* _NextLevel) override {}
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override {}

private:

};

