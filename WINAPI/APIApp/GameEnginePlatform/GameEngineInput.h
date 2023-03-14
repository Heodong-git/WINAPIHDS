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

private:
	class GameEngineKey
	{
		friend GameEngineInput;

		bool Down = false;		// Ű�� ���� ���� 
		bool Press = false;     // Ű�� ���� �ִ��� 
		bool Up = false;        // Ű�� �� ����
		bool Free = true;       // �ƹ� ���µ� �ƴ�

		float PressTime = 0.0f;	    // Ű�� ���ʰ� ���ȴ���

		int Key = -1;			// �Էµ� Ű���� �������� ����

		bool KeyCheck()
		{
			// ����� Ű���� �ְ� �� Ű�� ���ȴٸ�
			// 0�� �ƴ� ��Ʈ���� ��ȯ�ϰ� �Ǳ� ������ true �� ��ȯ�ϰ� �Ǿ� ���ȴٴ� �ǹ̰� �ȴ�.
			// ex) ���� ENTER �� �ش��ϴ� ���� �־��ְ� �ش��ϴ� Ű�� ���� ���ȴٸ� 0 �� �ƴѰ���
			// ��ȯ�ϱ� ������ ENTER Ű�� ���ȴٴ� �ǹ̰� �ǰ�, �ش��ϴ� Ű�� ���°��� �����Ѵ�. 
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

// Ű Ŭ������ �� ��� staitc ���� �����Ǿ� �ִ���?
// ���ٸ� �ǹ̴� ����, ��ü�� ȣ������ �ʰ� �����Լ�ó�� ����� �����ϱ� ������ ���ؼ�
// ���ڿ��� Ű������ �Ͽ� ����� Ű���� �����ϰ� map�� ����Ǿ� �ִ�
// �����͵��� ��� ��ȸ�ϸ� Update ����, �ڽ��� ���ȴ��� üũ�Ѵ�. 

