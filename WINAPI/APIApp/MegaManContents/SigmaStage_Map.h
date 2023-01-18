#pragma once
#include <GameEngineCore/GameEngineActor.h>

// �긦 ��ӹ޴� ��׶��� Ŭ�������� ����� ���� ������ 
// �ϴ� �������� �����Բ� ���� �غ���
// ��׶���� ���� � �����̳Ŀ� ���� enum class �� ���� 
// ���� �̸��� �ο��ϰ�, ������ �� ������ � Ÿ���̳Ŀ� ���� �ٸ��� ����Ѵ�. 
class SigmaStage_Map : public GameEngineActor
{
public:
	// constrcuter destructer
	SigmaStage_Map();
	~SigmaStage_Map();

	// delete Function
	SigmaStage_Map(const SigmaStage_Map& _Other) = delete;
	SigmaStage_Map(SigmaStage_Map&& _Other) noexcept = delete;
	SigmaStage_Map& operator=(const SigmaStage_Map& _Other) = delete;
	SigmaStage_Map& operator=(SigmaStage_Map&& _Other) noexcept = delete;

protected:
	void Start() override;
private:
};

