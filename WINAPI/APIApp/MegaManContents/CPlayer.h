#pragma once

// 설명 :
class CPlayer
{
public:
	// constrcuter destructer
	CPlayer();
	~CPlayer();

	// delete Function
	// 복사생성자 
	CPlayer(const CPlayer& _Other) = delete;
	// RValue 생성자, 이동생성자
	CPlayer(CPlayer&& _Other) noexcept = delete;
	// 대입연산자 
	CPlayer& operator=(const CPlayer& _Other) = delete;
	// 이동대입연산자 
	CPlayer& operator=(CPlayer&& _Other) noexcept = delete;

protected:

private:

};

