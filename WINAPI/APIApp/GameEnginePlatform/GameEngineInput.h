#pragma once
#include <Windows.h>
#include <map>
#include <string>

class GameEngineWindow;
class GameEngineInput
{
	// window 클래스에서만 private 의 기능인 
	// 아무키나 눌렀을 때 종료 기능을 사용하게 하기 위해 프렌드로 작성
	friend GameEngineWindow;
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

	static bool IsAnyKey()
	{
		return IsAnyKeyValue;
	}

protected:

private:
	// constrcuter destructer
	GameEngineInput();
	~GameEngineInput();

	static std::map<std::string, GameEngineKey> Keys;
	
	// 아무키가 눌렸는지 확인하기 위한 변수 
	// 이기능은 일단 내 프로젝트에선 필요 없는 것 같음. 
	static bool IsAnyKeyValue;

	static void IsAnyKeyOn()
	{
		IsAnyKeyValue = true;
	}

	static void IsAnyKeyOff()
	{
		IsAnyKeyValue = false;
	}

};


