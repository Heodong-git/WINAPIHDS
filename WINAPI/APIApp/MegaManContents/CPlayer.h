#pragma once

// ���� :
class CPlayer
{
public:
	// constrcuter destructer
	CPlayer();
	~CPlayer();

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

