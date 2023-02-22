#pragma once
#include <GameEngineBase/GameEngineMath.h>
#include <GameEngineCore/GameEngineActor.h>
#include <vector>

// �긦 ��ӹ޴� ��׶��� Ŭ�������� ����� ���� ������ 
// �ϴ� �������� �����Բ� ���� �غ���
// ��׶���� ���� � �����̳Ŀ� ���� enum class �� ���� 
// ���� �̸��� �ο��ϰ�, ������ �� ������ � Ÿ���̳Ŀ� ���� �ٸ��� ����Ѵ�. 

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
	void Update(float _DeltaTime) override;

private:
	// ������ �ʹ�ȣ�� �� �� �����ϱ�.
	std::vector<GameEngineRender*> m_vecRender;
	GameEngineRender* m_DebugRender = nullptr;
	float4 m_FinalImageScale = { 19200 , 7200 };
	float4 m_SettingImageScale = { 4800 , 1800 };
	float4 m_ImageScaleX = { 4800 , 0 }; 
};

