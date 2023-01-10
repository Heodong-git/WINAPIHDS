#pragma once
#include <GameEngineCore/GameEngineActor.h>

// �긦 ��ӹ޴� ��׶��� Ŭ�������� ����� ���� ������ 
// �ϴ� �������� �����Բ� ���� �غ���
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

