#pragma once

// 설명 :
class CPlayer
{
public:
	// constrcuter destructer
	CPlayer();
	// 소멸자를 순수 가상함수로 선언해줌으로써 
	// 해당 클래스를 상속받는 자식 클래스는 반드시 소멸자를 구현해주어야 하며
	// 구현하지 않을 경우 추상클래스가 되어 객체 생성이 불가능
	virtual ~CPlayer() = 0;

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

