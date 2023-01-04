#include "MegaManCore.h"
#include <MegaManContents/TitleLevel.h>
#include <MegaManContents/SelectLevel.h>
#include <MegaManContents/SigmaStageLevel.h>
#include <MegaManContents/EndTitleLevel.h>

// static ���� ����
MegaManCore MegaManCore::Core;

MegaManCore::MegaManCore()
{
}

MegaManCore::~MegaManCore()
{
}

void MegaManCore::Start()
{
	// ������ ����� ���� �ʿ��� ������ ���� Core Ŭ������ �ʿ� ��� �����صд�. 
	CreateLevel<TitleLevel>("TitleLevel");
	CreateLevel<SelectLevel>("SelectLevel");
	CreateLevel<SigmaStageLevel>("SigmaStageLevel");
	CreateLevel<EndTitleLevel>("EndTitleLevel");
	
	// ���� �ÿ� �ݵ�� � ������ ������ ������ �����Ѵ�. 
	ChangeLevel("TitleLevel");
}


void MegaManCore::Update()
{


}
void MegaManCore::End()
{

}