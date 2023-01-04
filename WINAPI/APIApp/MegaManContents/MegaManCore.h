#pragma once
#include <GameEngineCore/GameEngineCore.h>
 
// 게임의 메인 관리자로 볼 수 있다. 
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

	// 싱글톤
	// 실행할 프로그램에서 객체를 단하나만 생성하는 디자인 패턴을 싱글톤이라고 한다.
	// 클래스의 생성,소멸자를 private: 로 작성하여 생성하지 못하게 하고
	// 클래스 내부에 자기자신을 static 으로 선언하여, 단 하나의 객체만 존재할 수 있게 설계한다. 
	static MegaManCore& GetInst()
	{
		return Core;
	}

protected:
	// 부모클래스에 순수가상함수로 선언되어 있기 때문에
	// 반드시 함수를 구현해주어야 객체를 생성할 수 있다. 
	void Start() override;
	void Update() override;
	void End() override;

private:
	static MegaManCore Core;
};

