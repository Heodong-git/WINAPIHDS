#pragma once
#include <GameEngineCore/GameEngineActor.h>

// �긦 ��ӹ޴� ��׶��� Ŭ�������� ����� ���� ������ 
// �ϴ� �������� �����Բ� ���� �غ���
// ��׶���� ���� � �����̳Ŀ� ���� enum class �� ���� 
// ���� �̸��� �ο��ϰ�, ������ �� ������ � Ÿ���̳Ŀ� ���� �ٸ��� ����Ѵ�. 
class Select_BackGround : public GameEngineActor
{
public:
	// constrcuter destructer
	Select_BackGround();
	~Select_BackGround();

	// delete Function
	Select_BackGround(const Select_BackGround& _Other) = delete;
	Select_BackGround(Select_BackGround&& _Other) noexcept = delete;
	Select_BackGround& operator=(const Select_BackGround& _Other) = delete;
	Select_BackGround& operator=(Select_BackGround&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	GameEngineRender* m_Render = nullptr;
};

