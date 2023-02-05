#pragma once
#include <GameEngineBase/GameEngineMath.h>
#include <GameEngineCore/GameEngineActor.h>
#include <vector>

// 얘를 상속받는 백그라운드 클래스들을 만들면 되지 않을까 
// 일단 수업들어보고 선생님꺼 보고 해보자
// 백그라운드는 현재 어떤 레벨이냐에 따라서 enum class 를 통해 
// 값에 이름을 부여하고, 렌더링 할 때에는 어떤 타입이냐에 따라서 다르게 출력한다. 

enum class IMAGENUMBER
{
	ZERO,
	ONE,
	TWO,
	THREE,
	FOUR,
	FIVE,
	SIX,
	MAX
};

class GameEngineRender;
class Map_SpacePort : public GameEngineActor
{
public:
	// constrcuter destructer
	Map_SpacePort();
	~Map_SpacePort();

	// delete Function
	Map_SpacePort(const Map_SpacePort& _Other) = delete;
	Map_SpacePort(Map_SpacePort&& _Other) noexcept = delete;
	Map_SpacePort& operator=(const Map_SpacePort& _Other) = delete;
	Map_SpacePort& operator=(Map_SpacePort&& _Other) noexcept = delete;

	

protected:
	void Start() override;

private:
	// 어차피 맵번호로 알 수 있으니까.
	std::vector<GameEngineRender*> m_vecRender;
	float4 m_FinalImageScale = { 19200 , 7200 };
	float4 m_SettingImageScale = { 4800 , 1800 };
	float4 m_ImageScaleX = { 4800 , 0 }; 
};

