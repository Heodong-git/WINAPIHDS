#include "Map_SpacePort.h"
#include <vector>

#include <GameEnginePlatform/GameEngineInput.h>
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
	GameEngineInput::CreateKey("Map_Debug", '2');

	// 충돌맵 확인용 이미지
	{
		// 현재 디버그용 큰이미지 
		m_DebugRender = CreateRender(ZORDER::MAP);
		m_DebugRender->SetImage("ColMap_SpacePort.Bmp");
		m_DebugRender->SetPosition(m_FinalImageScale.half());
		m_DebugRender->Off();
	}


	m_vecRender.reserve(static_cast<size_t>(IMAGENUMBER::MAX) - 1);
	//// 실제 이미지 
	{
		GameEngineRender* AnimationRender = CreateRender(ZORDER::MAP);
		AnimationRender->SetImage("Map_SpacePort_0.Bmp");
		// 얘는 다시 설정해줘야하고. 
		AnimationRender->SetPosition(float4 { 2400 , 6300});
		m_vecRender.push_back(AnimationRender);
	}

	 //분할된 이미지 
	{
		GameEngineRender* AnimationRender = CreateRender(ZORDER::MAP);
		AnimationRender->SetImage("Map_SpacePort_1.Bmp");
		// 얘는 다시 설정해줘야하고. 
		AnimationRender->SetPosition(float4 { 7200 , 6300 });
		m_vecRender.push_back(AnimationRender);
	}
	{
		GameEngineRender* AnimationRender = CreateRender(ZORDER::MAP);
		AnimationRender->SetImage("Map_SpacePort_2.Bmp");
		// 얘는 다시 설정해줘야하고. 
		AnimationRender->SetPosition(float4 { 12000 , 6300 });
		m_vecRender.push_back(AnimationRender);
	}
	{
		GameEngineRender* AnimationRender = CreateRender(ZORDER::MAP);
		AnimationRender->SetImage("Map_SpacePort_3.Bmp");
		// 얘는 다시 설정해줘야하고. 
		AnimationRender->SetPosition(float4{ 16800 , 6300 });
		m_vecRender.push_back(AnimationRender);
	}
	{
		GameEngineRender* AnimationRender = CreateRender(ZORDER::MAP);
		AnimationRender->SetImage("Map_SpacePort_4.Bmp");
		// 얘는 다시 설정해줘야하고. 
		AnimationRender->SetPosition(float4 { 16800, 4500 });
		m_vecRender.push_back(AnimationRender);
	}
	{
		GameEngineRender* AnimationRender = CreateRender(ZORDER::MAP);
		AnimationRender->SetImage("Map_SpacePort_5.Bmp");
		// 얘는 다시 설정해줘야하고. 
		AnimationRender->SetPosition(float4 { 16800, 2700});
		m_vecRender.push_back(AnimationRender);
	}
	{
		GameEngineRender* AnimationRender = CreateRender(ZORDER::MAP);
		AnimationRender->SetImage("Map_SpacePort_6.Bmp");
		// 얘는 다시 설정해줘야하고. 
		AnimationRender->SetPosition(float4 { 16800, 900 } );
		m_vecRender.push_back(AnimationRender);
	}
}

void Map_SpacePort::Update(float _DeltaTime)
{
	if (true == GameEngineInput::IsDown("Map_Debug"))
	{
		for (size_t i = 0; i < m_vecRender.size(); i++)
		{
			m_vecRender[i]->OnOffSwtich();
		}
		
		m_DebugRender->OnOffSwtich();
	}
}
