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

		int Key = -1;			// 입력된 키값이 무엇인지 저장

		bool KeyCheck()
		{
			// 저장된 키값을 넣고 그 키가 눌렸다면
			// 0이 아닌 비트값을 반환하게 되기 때문에 true 를 반환하게 되어 눌렸다는 의미가 된다.
			// ex) 현재 ENTER 에 해당하는 값을 넣어주고 해당하는 키가 지금 눌렸다면 0 이 아닌값을
			// 반환하기 때문에 ENTER 키가 눌렸다는 의미가 되고, 해당하는 키의 상태값을 변경한다. 
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

// 키 클래스는 왜 모두 staitc 으로 구성되어 있는지?
// 별다른 의미는 없고, 객체를 호출하지 않고 전역함수처럼 사용이 가능하기 때문에 편리해서 이렇게 만듦. 
// 문자열을 키값으로 하여 사용할 키들을 저장하고 map에 저장되어 있는
// 데이터들을 모두 순회하며 Update 에서, 자신이 눌렸는지 체크한다. 

