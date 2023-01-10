#pragma once
#include <GameEngineCore/GameEngineActor.h>

// 얘를 상속받는 백그라운드 클래스들을 만들면 되지 않을까 
// 일단 수업들어보고 선생님꺼 보고 해보자
class Map_BackGround : public GameEngineActor
{
public:
	// constrcuter destructer
	Map_BackGround();
	~Map_BackGround();

	// delete Function
	Map_BackGround(const Map_BackGround& _Other) = delete;
	Map_BackGround(Map_BackGround&& _Other) noexcept = delete;
	Map_BackGround& operator=(const Map_BackGround& _Other) = delete;
	Map_BackGround& operator=(Map_BackGround&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update() override;
	void Render() override;

private:

};

