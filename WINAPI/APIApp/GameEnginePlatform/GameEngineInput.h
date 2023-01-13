#pragma once
#include <Windows.h>
#include <map>
#include <string>

class GameEngineInput
{
public:
	class GameEngineKey
	{
		friend GameEngineInput;

		bool Down = false;		// 키를 누른 순간 
		bool Press = false;     // 키가 눌려 있는지 
		bool Up = false;        // 키를 뗀 순간
		bool Free = true;       // 아무 상태도 아님

		float PressTime;	    // 키가 몇초간 눌렸는지

		int Key = -1;			// 입력된 키 저장

		bool KeyCheck()
		{
			return 0 != GetAsyncKeyState(Key);
		}

		void Update(float _DeltaTime);
	};

public:

	// delete Function
	GameEngineInput(const GameEngineInput& _Other) = delete;
	GameEngineInput(GameEngineInput&& _Other) noexcept = delete;
	GameEngineInput& operator=(const GameEngineInput& _Other) = delete;
	GameEngineInput& operator=(GameEngineInput&& _Other) noexcept = delete;

	static void Update(float _DeltaTime);
	static void CreateKey(const std::string_view& _Name, int _Key);

	// 키가 저장되어 있는지?
	static bool IsKey(const std::string_view& _Name);

	static bool IsDown(const std::string_view& _Name);
	static bool IsUp(const std::string_view& _Name);
	static bool IsPress(const std::string_view& _Name);
	static bool IsFree(const std::string_view& _Name);
	static float GetPressTime(const std::string_view& _Name);

protected:

private:
	// constrcuter destructer
	GameEngineInput();
	~GameEngineInput();

	//      PlayerJump       A
	static std::map<std::string, GameEngineKey> Keys;

};


