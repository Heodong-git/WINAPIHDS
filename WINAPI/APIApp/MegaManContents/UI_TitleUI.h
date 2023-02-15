#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/GameEngineResources.h>
#include <vector>
#include "ContentsEnum.h"


class UI_TitleUI : public GameEngineActor
{
	// 타이틀레벨에서는 프렌드로 설정하여
	// private 에 접근 가능하도록. 
	// 타이틀에서는 엔터키를 사용하여 레벨체인지를 할 경우에 
	// 어떤 값이 선택되어있느냐에 따라서 분기처리한다. 
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

