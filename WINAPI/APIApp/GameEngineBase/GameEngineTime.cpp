#include "GameEngineTime.h"

// static ���� ����
GameEngineTime GameEngineTime::GlobalTime;

GameEngineTime::GameEngineTime()
{
	// �����Ҷ� 1���� ���ϸ� �ȴ�.
	QueryPerformanceFrequency(&Second);

	QueryPerformanceCounter(&Prev);
}

GameEngineTime::~GameEngineTime()
{
}

void GameEngineTime::Reset()
{
	QueryPerformanceCounter(&Prev);
}

float GameEngineTime::TimeCheck()
{
	// ��������� ���� �޾ƿ´�. 
	QueryPerformanceCounter(&Current);

	// ����ð��� - �����ð���
	// ƽ�� �ɸ��� �ð� 
	Tick = Current.QuadPart - Prev.QuadPart;
                               
	// ��ŸŸ�� = ����ð� - �����ð� / ���ؽð�
	DoubleDeltaTime = (static_cast<double>(Current.QuadPart) - static_cast<double>(Prev.QuadPart)) / static_cast<double>(Second.QuadPart);

	// ��ŸŸ���� �����־��� ������ 
	// ���� �ð��� = ����ð� ���� �ǰ�
	// ���� �����ӿ��� ����������� ����ϰ� �ȴ�.
	Prev.QuadPart = Current.QuadPart;

	// �뼼�� ������ ��ŸŸ���� float Ÿ�Ի��. 
	floatDeltaTime = static_cast<float>(DoubleDeltaTime);

	return floatDeltaTime;
}
