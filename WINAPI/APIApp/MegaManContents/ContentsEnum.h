#pragma once

// ������ ������Ʈ���� ����� enum class ����

// Z���� 
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

// Ÿ��Ʋ�޴� 
enum class ETitleMenu
{
	GAMESTART,
	CONTINUE,
	OPTION,

	END
};