#pragma once

// ���� :
class CPlayer
{
public:
	// constrcuter destructer
	CPlayer();
	// �Ҹ��ڸ� ���� �����Լ��� �����������ν� 
	// �ش� Ŭ������ ��ӹ޴� �ڽ� Ŭ������ �ݵ�� �Ҹ��ڸ� �������־�� �ϸ�
	// �������� ���� ��� �߻�Ŭ������ �Ǿ� ��ü ������ �Ұ���
	virtual ~CPlayer() = 0;

	// delete Function
	// ��������� 
	CPlayer(const CPlayer& _Other) = delete;
	// RValue ������, �̵�������
	CPlayer(CPlayer&& _Other) noexcept = delete;
	// ���Կ����� 
	CPlayer& operator=(const CPlayer& _Other) = delete;
	// �̵����Կ����� 
	CPlayer& operator=(CPlayer&& _Other) noexcept = delete;

protected:



private:

};

