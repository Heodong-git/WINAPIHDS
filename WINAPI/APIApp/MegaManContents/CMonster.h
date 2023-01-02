#pragma once

// Ό³Έν :
class CMonster
{
public:
	// constrcuter destructer
	CMonster();
	virtual ~CMonster() = 0;

	// delete Function
	CMonster(const CMonster& _Other) = delete;
	CMonster(CMonster&& _Other) noexcept = delete;
	CMonster& operator=(const CMonster& _Other) = delete;
	CMonster& operator=(CMonster&& _Other) noexcept = delete;

protected:

private:

};

