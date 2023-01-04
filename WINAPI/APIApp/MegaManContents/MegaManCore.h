#pragma once
#include <GameEngineCore/GameEngineCore.h>
 
// ������ ���� �����ڷ� �� �� �ִ�. 
class MegaManCore : public GameEngineCore
{
private:
	MegaManCore();
	~MegaManCore();

public:
	// delete Function
	MegaManCore(const MegaManCore& _Other) = delete;
	MegaManCore(MegaManCore&& _Other) noexcept = delete;
	MegaManCore& operator=(const MegaManCore& _Other) = delete;
	MegaManCore& operator=(MegaManCore&& _Other) noexcept = delete;

	// �̱���
	// ������ ���α׷����� ��ü�� ���ϳ��� �����ϴ� ������ ������ �̱����̶�� �Ѵ�.
	// Ŭ������ ����,�Ҹ��ڸ� private: �� �ۼ��Ͽ� �������� ���ϰ� �ϰ�
	// Ŭ���� ���ο� �ڱ��ڽ��� static ���� �����Ͽ�, �� �ϳ��� ��ü�� ������ �� �ְ� �����Ѵ�. 
	static MegaManCore& GetInst()
	{
		return Core;
	}

protected:
	// �θ�Ŭ������ ���������Լ��� ����Ǿ� �ֱ� ������
	// �ݵ�� �Լ��� �������־�� ��ü�� ������ �� �ִ�. 
	void Start() override;
	void Update() override;
	void End() override;

private:
	static MegaManCore Core;
};

