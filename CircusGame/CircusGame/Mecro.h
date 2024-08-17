#pragma once

#include <time.h>
#include <vector>
#include <Windows.h>
#include <string>
#include <cmath>
#include <algorithm>

#pragma comment(lib, "msimg32.lib")

using namespace std;

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

};
