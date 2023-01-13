#include "GameEngineInput.h"
#include <GameEngineBase/GameEngineString.h>
#include <GameEngineBase/GameEngineDebug.h>

// 편하게 사용하기 위해 static 
std::map<std::string, GameEngineInput::GameEngineKey> GameEngineInput::Keys;

void GameEngineInput::GameEngineKey::Update(float _DeltaTime)
{
	// 현재 키가 눌렸다면 
	// 키체크함수 내부에서 어싱크키스테이트 함수로 확인
	if (true == KeyCheck())
	{
		// 만약 키가 아무런 상태가 아니라면 ( 눌리지도, 눌려져 있지도 않음 ) 
		if (true == Free)
		{
			// 아무상태가 아닐 때 눌렸다면 이제 눌린 것
			Down = true;
			// 눌렸다면 눌린 상태인 것
			Press = true;
			// 키를 떼지 않았기 때문에 false 
			Up = false;
			// 현재 눌린상태이기 때문에 false 
			Free = false;
			PressTime = _DeltaTime;
		}
		// 키가 눌렸을 때 Down 상태가 true 라면 이전 프레임에서도 눌려 있던 것이다. 
		else if (true == Down)
		{
			// 이번 프레임에서 눌린 것이 아니기 때문에 false
			Down = false;
			// 현재 눌린상태이기 때문에 true 
			Press = true;
			// 뗀 상태가 아니기 때문에 false 
			Up = false;
			// 눌린 상태이기 때문에 false 
			Free = false;
			// 눌려있는 상태이기 때문에 델타타임 누적
			PressTime += _DeltaTime;
		}
	}

	// 키가 눌린 상태가 아니라면 
	else
	{
		// 눌린 시간 초기화
		PressTime = 0.0f;

		// 이전 프레임에 키가 눌려있던 상태라면 
		if (true == Press)
		{
			// 현재 키가 눌린 상태가 아니기 때문에 false 
			Down = false;
			// 마찬가지 
			Press = false;
			// 이전 프레임에 키가 눌려있었고 현재 눌린상태가 아니라면 키를 뗐다는 의미
			Up = true;
			Free = false;
		}

		// 키가 눌린 상태가 아닐때 현재 UP 이 true라면 
		else if (true == Up)
		{
			// 원래 아무런 상태도 아니었다는 의미 
			Down = false;
			Press = false;
			Up = false;
			Free = true;
		}
	}
}

bool GameEngineInput::IsDown(const std::string_view& _Name)
{
	std::string UpperName = GameEngineString::ToUpper(_Name);

	if (Keys.end() == Keys.find(UpperName))
	{
		MsgAssert("존재하지 않는 키를 사용하려고 했습니다." + UpperName);
	}

	// 문자열 키값에 해당 하는 GameEngineKey 클래스 의 변수의 값을 반환한다. 
	return Keys[UpperName].Down;
}
bool GameEngineInput::IsUp(const std::string_view& _Name)
{
	std::string UpperName = GameEngineString::ToUpper(_Name);

	if (Keys.end() == Keys.find(UpperName))
	{
		MsgAssert("존재하지 않는 키를 사용하려고 했습니다." + UpperName);
	}


	return Keys[UpperName].Up;
}
bool GameEngineInput::IsPress(const std::string_view& _Name)
{
	std::string UpperName = GameEngineString::ToUpper(_Name);

	if (Keys.end() == Keys.find(UpperName))
	{
		MsgAssert("존재하지 않는 키를 사용하려고 했습니다." + UpperName);
	}


	return Keys[UpperName].Press;
}
bool GameEngineInput::IsFree(const std::string_view& _Name)
{
	std::string UpperName = GameEngineString::ToUpper(_Name);

	if (Keys.end() == Keys.find(UpperName))
	{
		MsgAssert("존재하지 않는 키를 사용하려고 했습니다." + UpperName);
	}

	return Keys[UpperName].Free;
}

float GameEngineInput::GetPressTime(const std::string_view& _Name)
{
	std::string UpperName = GameEngineString::ToUpper(_Name);

	if (Keys.end() == Keys.find(UpperName))
	{
		MsgAssert("존재하지 않는 키를 사용하려고 했습니다." + UpperName);
	}

	return Keys[UpperName].PressTime;
}

bool GameEngineInput::IsKey(const std::string_view& _Name)
{
	std::string UpperName = GameEngineString::ToUpper(_Name);
	
	// 키가 end 가 아니라면 문자열 키값으로 저장되어 있는 것
	return Keys.end() != Keys.find(UpperName);
}


void GameEngineInput::CreateKey(const std::string_view& _Name, int _Key)
{
	// 모든 문자를 대문자로 변경하여 저장
	std::string UpperName = GameEngineString::ToUpper(_Name);

	// 인자로 들어온 키와 같은 키로 저장된 데이터가 있다면
	// nullptr 이 아니라면 이미 저장되었다는 의미
	if (Keys.end() != Keys.find(UpperName))
	{
		// assert
		MsgAssert("이미 존재하는 이름의 키를 또 만들려고 했습니다.");
	}

	// 소문자를 대문자로 변환하여 반환 , 다른 문자는 그대로 반환
	_Key = toupper(_Key);

	// 맵에 저장해준다.

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
	//현재 키가 저장되어 있는 맵을 순회
	std::map<std::string, GameEngineKey>::iterator StartKeyIter = Keys.begin();
	std::map<std::string, GameEngineKey>::iterator EndKeyIter = Keys.end();

	// 키 업데이트
	for (; StartKeyIter != EndKeyIter; ++StartKeyIter)
	{
		StartKeyIter->second.Update(_DeltaTime);
	}
}