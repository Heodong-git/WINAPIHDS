#include "Map_SpacePort.h"
#include <vector>

#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRender.h>
#include "ContentsEnum.h"

Map_SpacePort::Map_SpacePort()
{

}

Map_SpacePort::~Map_SpacePort()
{
}

void Map_SpacePort::Start()
{
	m_vecRender.reserve(static_cast<size_t>(IMAGENUMBER::MAX) - 1);
	{
		 // ���� ����׿� ū�̹��� 
		 GameEngineRender* AnimationRender = CreateRender(ZORDER::MAP);
		 AnimationRender->SetImage("ColMap_SpacePort.Bmp");
		 AnimationRender->SetPosition(m_FinalImageScale.half());
	}

	// ���߿��� �Ʒ� �����̹����� ����
	//{
	//	GameEngineRender* AnimationRender = CreateRender(ZORDER::MAP);
	//	AnimationRender->SetImage("Map_SpacePort_0.Bmp");
	//	// ��� �ٽ� ����������ϰ�. 
	//	AnimationRender->SetPosition(float4 { 2400 , 6300});
	//	m_vecRender.push_back(AnimationRender);
	//}

	// ���ҵ� �̹��� 
	//{
	//	GameEngineRender* AnimationRender = CreateRender(ZORDER::MAP);
	//	AnimationRender->SetImage("Map_SpacePort_1.Bmp");
	//	// ��� �ٽ� ����������ϰ�. 
	//	AnimationRender->SetPosition(float4 { 7200 , 6300 });
	//	m_vecRender.push_back(AnimationRender);
	//}
	//{
	//	GameEngineRender* AnimationRender = CreateRender(ZORDER::MAP);
	//	AnimationRender->SetImage("Map_SpacePort_2.Bmp");
	//	// ��� �ٽ� ����������ϰ�. 
	//	AnimationRender->SetPosition(float4 { 12000 , 6300 });
	//	m_vecRender.push_back(AnimationRender);
	//}
	//{
	//	GameEngineRender* AnimationRender = CreateRender(ZORDER::MAP);
	//	AnimationRender->SetImage("Map_SpacePort_3.Bmp");
	//	// ��� �ٽ� ����������ϰ�. 
	//	AnimationRender->SetPosition(float4{ 16800 , 6300 });
	//	m_vecRender.push_back(AnimationRender);
	//}
	//{
	//	GameEngineRender* AnimationRender = CreateRender(ZORDER::MAP);
	//	AnimationRender->SetImage("Map_SpacePort_4.Bmp");
	//	// ��� �ٽ� ����������ϰ�. 
	//	AnimationRender->SetPosition(float4 { 16800, 4500 });
	//	m_vecRender.push_back(AnimationRender);
	//}
	//{
	//	GameEngineRender* AnimationRender = CreateRender(ZORDER::MAP);
	//	AnimationRender->SetImage("Map_SpacePort_5.Bmp");
	//	// ��� �ٽ� ����������ϰ�. 
	//	AnimationRender->SetPosition(float4 { 16800, 2700});
	//	m_vecRender.push_back(AnimationRender);
	//}
	//{
	//	GameEngineRender* AnimationRender = CreateRender(ZORDER::MAP);
	//	AnimationRender->SetImage("Map_SpacePort_6.Bmp");
	//	// ��� �ٽ� ����������ϰ�. 
	//	AnimationRender->SetPosition(float4 { 16800, 900 } );
	//	m_vecRender.push_back(AnimationRender);
	//}
}
