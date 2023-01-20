#pragma once
#include <GameEngineCore/GameEngineActor.h>

// �긦 ��ӹ޴� ��׶��� Ŭ�������� ����� ���� ������ 
// �ϴ� �������� �����Բ� ���� �غ���
// ��׶���� ���� � �����̳Ŀ� ���� enum class �� ���� 
// ���� �̸��� �ο��ϰ�, ������ �� ������ � Ÿ���̳Ŀ� ���� �ٸ��� ����Ѵ�. 
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
};

