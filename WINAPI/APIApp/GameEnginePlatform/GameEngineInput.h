#pragma once
#include <Windows.h>
#include <map>
#include <string>

class GameEngineWindow;
class GameEngineInput
{
	// window Ŭ���������� private �� ����� 
	// �ƹ�Ű�� ������ �� ���� ����� ����ϰ� �ϱ� ���� ������� �ۼ�
	friend GameEngineWindow;
public:
	class GameEngineKey
	{
		friend GameEngineInput;

		bool Down = false;		// Ű�� ���� ���� 
		bool Press = false;     // Ű�� ���� �ִ��� 
		bool Up = false;        // Ű�� �� ����
		bool Free = true;       // �ƹ� ���µ� �ƴ�

		float PressTime;	    // Ű�� ���ʰ� ���ȴ���

		int Key = -1;			// �Էµ� Ű ����

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

	// Ű�� ����Ǿ� �ִ���?
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
	
	// �ƹ�Ű�� ���ȴ��� Ȯ���ϱ� ���� ���� 
	// �̱���� �ϴ� �� ������Ʈ���� �ʿ� ���� �� ����. 
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


