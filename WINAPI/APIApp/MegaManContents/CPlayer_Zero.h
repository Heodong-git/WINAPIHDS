#pragma once

// ���� :
class CPlayer_Zero
{
public:
	// constrcuter destructer
	CPlayer_Zero();
	~CPlayer_Zero();

	// delete Function
	CPlayer_Zero(const CPlayer_Zero& _Other) = delete;
	CPlayer_Zero(CPlayer_Zero&& _Other) noexcept = delete;
	CPlayer_Zero& operator=(const CPlayer_Zero& _Other) = delete;
	CPlayer_Zero& operator=(CPlayer_Zero&& _Other) noexcept = delete;

protected:

private:

};

