#include "GameEngineInput.h"
#include <GameEngineBase/GameEngineString.h>
#include <GameEngineBase/GameEngineDebug.h>

// ���ϰ� ����ϱ� ���� static 
std::map<std::string, GameEngineInput::GameEngineKey> GameEngineInput::Keys;
bool GameEngineInput::IsAnyKeyValue = false;

void GameEngineInput::GameEngineKey::Update(float _DeltaTime)
{
	if (true == KeyCheck())
	{
		// ���ȱ� ������ �ð� ����
		PressTime += _DeltaTime;

		// ���� Ű�� �ƹ��� ���°� �ƴ϶�� ( ��������, ������ ������ ���� ) 
		if (true == Free)
		{
			// �ƹ����°� �ƴ� �� ���ȴٸ� ���� ���� ��
			Down = true;
			// ���ȴٸ� ���� ������ ��
			Press = true;
			// Ű�� ���� �ʾұ� ������ false 
			Up = false;
			// ���� ���������̱� ������ false 
			Free = false;
		}
		// Ű�� ������ �� Down ���°� true ��� ���� �����ӿ����� ���� �ִ� ���̴�. 
		else if (true == Down)
		{
			// �̹� �����ӿ��� ���� ���� �ƴϱ� ������ false
			Down = false;
			// ���� ���������̱� ������ true 
			Press = true;
			// �� ���°� �ƴϱ� ������ false 
			Up = false;
			// ���� �����̱� ������ false 
			Free = false;
		}
	}

	// Ű�� ���� ���°� �ƴ϶�� 
	else
	{
		// ���� �ð� �ʱ�ȭ
		PressTime = 0.0f;

		// ���� �����ӿ� Ű�� �����ִ� ���¶�� 
		if (true == Press)
		{
			// ���� Ű�� ���� ���°� �ƴϱ� ������ false 
			Down = false;
			// �������� 
			Press = false;
			// ���� �����ӿ� Ű�� �����־��� ���� �������°� �ƴ϶�� Ű�� �ôٴ� �ǹ�
			Up = true;
			Free = true;
		}

		// Ű�� ���� ���°� �ƴҶ� ���� UP �� true��� 
		else if (true == Up)
		{
			// ���� �ƹ��� ���µ� �ƴϾ��ٴ� �ǹ� 
			Down = false;
			Press = false;
			Up = false;
			Free = true;
		}
	}
}

// ���ڿ��� Ű������ �Ͽ� Ű�� �����߱� ������
// Ű�� ���ȴٸ� �� Ű�� �ش��ϴ� ���ڿ��� Ȯ���Ͽ� 
// ������ ���ڿ��� ���� Ű�� ���¸� ��ȯ�Ѵ�. 
bool GameEngineInput::IsDown(const std::string_view& _Name)
{
	std::string UpperName = GameEngineString::ToUpper(_Name);

	if (Keys.end() == Keys.find(UpperName))
	{
		MsgAssert("�������� �ʴ� Ű�� ����Ϸ��� �߽��ϴ�." + UpperName);
	}

	// ���ڿ� Ű���� �ش� �ϴ� GameEngineKey Ŭ���� �� ������ ���� ��ȯ�Ѵ�. 
	return Keys[UpperName].Down;
}
bool GameEngineInput::IsUp(const std::string_view& _Name)
{
	std::string UpperName = GameEngineString::ToUpper(_Name);

	if (Keys.end() == Keys.find(UpperName))
	{
		MsgAssert("�������� �ʴ� Ű�� ����Ϸ��� �߽��ϴ�." + UpperName);
	}


	return Keys[UpperName].Up;
}
bool GameEngineInput::IsPress(const std::string_view& _Name)
{
	std::string UpperName = GameEngineString::ToUpper(_Name);

	if (Keys.end() == Keys.find(UpperName))
	{
		MsgAssert("�������� �ʴ� Ű�� ����Ϸ��� �߽��ϴ�." + UpperName);
	}


	return Keys[UpperName].Press;
}
bool GameEngineInput::IsFree(const std::string_view& _Name)
{
	std::string UpperName = GameEngineString::ToUpper(_Name);

	if (Keys.end() == Keys.find(UpperName))
	{
		MsgAssert("�������� �ʴ� Ű�� ����Ϸ��� �߽��ϴ�." + UpperName);
	}

	return Keys[UpperName].Free;
}

float GameEngineInput::GetPressTime(const std::string_view& _Name)
{
	std::string UpperName = GameEngineString::ToUpper(_Name);

	if (Keys.end() == Keys.find(UpperName))
	{
		MsgAssert("�������� �ʴ� Ű�� ����Ϸ��� �߽��ϴ�." + UpperName);
	}

	return Keys[UpperName].PressTime;
}

bool GameEngineInput::IsKey(const std::string_view& _Name)
{
	std::string UpperName = GameEngineString::ToUpper(_Name);
	
	// Ű�� end �� �ƴ϶�� ���ڿ� Ű������ ����Ǿ� �ִ� ��
	return Keys.end() != Keys.find(UpperName);
}

// ���ڿ��� Ű������ �Ͽ� ���ϴ� Ű ����
void GameEngineInput::CreateKey(const std::string_view& _Name, int _Key)
{
	// Ű���� �빮�ڷ� ��ȯ
	std::string UpperName = GameEngineString::ToUpper(_Name);

	// ������ Ű������ �̹� ����Ǿ��ִٸ�
	if (Keys.end() != Keys.find(UpperName))
	{
		// assert
		MsgAssert("�̹� �����ϴ� �̸��� Ű�� �� ������� �߽��ϴ�.");
	}

	// �ҹ��ڸ� �빮�ڷ� ��ȯ�Ͽ� ��ȯ , �ٸ� ���ڴ� �״�� ��ȯ
	_Key = toupper(_Key);

	// ���ڷ� ���� ���ڿ��� Ű������ �Ͽ� � Ű�� �����Ѵ�.
	Keys[UpperName].Key = _Key;
}

/// GameEngineInput
GameEngineInput::GameEngineInput()
{
}

GameEngineInput::~GameEngineInput()
{
}

void GameEngineInput::Update(float _DeltaTime)
{
	// ���� map�� ����Ǿ� �ִ� Ű�� ��ȸ�ϸ� ������Ʈ ����
	// 
	std::map<std::string, GameEngineKey>::iterator StartKeyIter = Keys.begin();
	std::map<std::string, GameEngineKey>::iterator EndKeyIter = Keys.end();

	for (; StartKeyIter != EndKeyIter; ++StartKeyIter)
	{
		StartKeyIter->second.Update(_DeltaTime);
	}
}