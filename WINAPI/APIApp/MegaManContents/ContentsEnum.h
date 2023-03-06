#pragma once

// 컨텐츠 프로젝트에서 사용할 enum class 집합

// Z오더 
enum class ZORDER
{
	BACKGROUND,
	MAP,
	OBJECT,
	MONSTER,
	BOSS,
	UI,
	PLAYER,
	PLAYER_EFFECT,
	EFFECT,
	UI_Text
};

enum class COLORDER
{
	PLAYER,
	PLAYERATTACK,
	MONSTER,
	MONSTERATTACK,
	OBJECT_LADDER,
	OBJECT_DOOR,
	OBJECT_BULLET,
};

// 타이틀메뉴 
enum class ETitleMenu
{
	GAMESTART,
	CONTINUE,
	OPTION,

	END
};