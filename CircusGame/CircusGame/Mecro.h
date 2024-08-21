#pragma once

#include <time.h>
#include <vector>
#include <Windows.h>
#include <string>
#include <cmath>
#include <algorithm>

#pragma comment(lib, "msimg32.lib")

using namespace std;

enum IMG
{
	START,

	BACK_GRASS,
	BACK_ELEPHANT,
	BACK_AUDIENCE0,
	BACK_AUDIENCE1,

	PLAYER_MOVE0, //뒤로
	PLAYER_MOVE1,
	PLAYER_MOVE2, //앞으로
	PLAYER_WIN0,
	PLAYER_WIN1,
	PLAYER_DIE,

	FIRE_NORMAL0,
	FIRE_NORMAL1,
	FIRE_SMALLRING0,
	FIRE_SMALLRING1,
	FIRE_RINGLEFT0,
	FIRE_RINGLEFT1,
	FIRE_RINGRIGHT0,
	FIRE_RINGRIGHT1,

	STAR_B,
	STAR_R,
	STAR_Y,

	CASH,
	GOAL,

	END
};

enum IMAGE
{
	IMAGE_START,

	IMAGE_GRASS = 1,
	IMAGE_ELEPHANT,
	IMAGE_AUDIENCE,
	//IMAGE_GOAL,

	IMAGE_END
};

enum LINE
{
	STARTLINE = 1,
	RUNLINE,
	ENDLINE
};

enum SPEED
{
	SLOW = 100,
	NORMAL = 150,
	HIGH = 200
};
