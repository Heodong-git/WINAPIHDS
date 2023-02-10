#include "GameEngineSound.h"
#include <GameEngineBase/GameEngineDebug.h>

// lib를 통해서 dll을 사용한다고 하는건 fmod.dll 을 쓰겠다 라는거, 내가 실행하려는 곳에 
// 그대로 들어있어야 한다는 뜻임
// fmod.dll , fmodl.dll 모두 속성에서 빌드에서제외 -> 아니오 , 파일복사로 변경
#ifdef _DEBUG
#pragma comment(lib, "GameEnginePlatform\\ThirdParty\\FMOD\\lib\\x64\\fmodL_vc.lib")
#else
#pragma comment(lib, "GameEnginePlatform\\ThirdParty\\FMOD\\lib\\x64\\fmod_vc.lib")
#endif

// FMOD는 자신들의 기능을 이용할수 있게 해주는 클래스의 포인터를 주고
FMOD::System* SoundSystem = nullptr;

// fmod 이니셜라이즈 호출을 까먹을 수 있기 때문에 cpp에 구현해두고
// 전역변수를 하나 만들어준다. 
class SoundSystemCreator
{
public:
	// 프로그램이 실행되는 순간 실행된다. 
	SoundSystemCreator()
	{
		FMOD::System_Create(&SoundSystem);

		if (nullptr == SoundSystem)
		{
			MsgAssert("사운드 초기화가 제대로 되지 않았습니다.");
		}

		if (FMOD_OK != SoundSystem->init(32, FMOD_DEFAULT, nullptr))
		{
			MsgAssert("사운드 시스템 이니셜라이즈에 실패했습니다.");
		}

	}

	~SoundSystemCreator()
	{
		SoundSystem->release();
	}
};

SoundSystemCreator SoundInitObject = SoundSystemCreator();

void GameEngineSound::SoundUpdate()
{
	if (nullptr == SoundSystem)
	{
		MsgAssert("사운드 업데이트가 불가능합니다.");
		return;
	}

	SoundSystem->update();
}

GameEngineSound::GameEngineSound()
{
}

GameEngineSound::~GameEngineSound()
{
}

void GameEngineSound::SoundLoad(const std::string_view& _Path)
{
	if (FMOD_OK != SoundSystem->createSound(_Path.data(), FMOD_LOOP_NORMAL, nullptr, &FMODSound))
	{
		MsgAssert(std::string("사운드 로드에 실패했습니다.\n 경로 : ") + _Path.data());
	}

	return;
}

FMOD::Channel* GameEngineSound::Play()
{
	if (nullptr == FMODSound)
	{
		MsgAssert(std::string("FMODSound가 nullptr 입니다 "));
	}

	FMOD::Channel* Return;

	SoundSystem->playSound(FMODSound, nullptr, false, &Return);

	return Return;
}