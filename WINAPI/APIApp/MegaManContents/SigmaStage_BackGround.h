#pragma once
#include <GameEngineCore/GameEngineActor.h>

// �긦 ��ӹ޴� ��׶��� Ŭ�������� ����� ���� ������ 
// �ϴ� �������� �����Բ� ���� �غ���
// ��׶���� ���� � �����̳Ŀ� ���� enum class �� ���� 
// ���� �̸��� �ο��ϰ�, ������ �� ������ � Ÿ���̳Ŀ� ���� �ٸ��� ����Ѵ�. 
class SigmaStage_BackGround : public GameEngineActor
{
public:
	// constrcuter destructer
	SigmaStage_BackGround();
	~SigmaStage_BackGround();

	// delete Function
	SigmaStage_BackGround(const SigmaStage_BackGround& _Other) = delete;
	SigmaStage_BackGround(SigmaStage_BackGround&& _Other) noexcept = delete;
	SigmaStage_BackGround& operator=(const SigmaStage_BackGround& _Other) = delete;
	SigmaStage_BackGround& operator=(SigmaStage_BackGround&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
};

