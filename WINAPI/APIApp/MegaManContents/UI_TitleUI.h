#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/GameEngineResources.h>
#include <vector>
#include "ContentsEnum.h"


class UI_TitleUI : public GameEngineActor
{
	// Ÿ��Ʋ���������� ������� �����Ͽ�
	// private �� ���� �����ϵ���. 
	// Ÿ��Ʋ������ ����Ű�� ����Ͽ� ����ü������ �� ��쿡 
	// � ���� ���õǾ��ִ��Ŀ� ���� �б�ó���Ѵ�. 
	friend class TitleLevel;
public:
	// constrcuter destructer
	UI_TitleUI();
	~UI_TitleUI();

	// delete Function
	UI_TitleUI(const UI_TitleUI& _Other) = delete;
	UI_TitleUI(UI_TitleUI&& _Other) noexcept = delete;
	UI_TitleUI& operator=(const UI_TitleUI& _Other) = delete;
	UI_TitleUI& operator=(UI_TitleUI&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

	ETitleMenu GetCurMenuType()
	{
		return m_CurMenu;
	}
private:
	GameEngineRender* m_MenuRender = nullptr;
	GameEngineRender* m_TextRender = nullptr;

	GameEngineSoundPlayer m_UISoundPlayer;

	ETitleMenu		  m_CurMenu = ETitleMenu::END;
	int				  m_CurIdx = 0;
	std::vector<ETitleMenu> m_vecMenu;
};

