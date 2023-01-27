#pragma once

// 컨텐츠 프로젝트에서 사용할 enum class 집합

// Z오더 
enum class RENDERORDER
{
	BACKGROUND,
	MAP,
	MONSTER,
	UI,
	PLAYER,
	UI_Text
};

// 타이틀메뉴 
enum class ETitleMenu
{
	GAMESTART,
	CONTINUE,
	OPTION,

	END
};