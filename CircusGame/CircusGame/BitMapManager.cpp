#include "BitMapManager.h"

BitMapManager* BitMapManager::m_hThis = NULL;

BitMapManager::BitMapManager()
{
	m_back = new BitMap[END];
}

void BitMapManager::Init(HDC hdc)
{
	BackLoad(hdc);
	PlayerLoad(hdc);
	FireLoad(hdc);
	EtcLoad(hdc);
}

void BitMapManager::BackLoad(HDC hdc)
{
	for (int i = BACK_GRASS; i <= BACK_AUDIENCE1; i++)
	{
		sprintf_s(buf, "RES//back_%d.bmp", i);
		m_back[i].Init(hdc, buf);
	}
}

void BitMapManager::PlayerLoad(HDC hdc)
{
	for (int i = PLAYER_MOVE0; i <= PLAYER_DIE; i++)
	{
		sprintf_s(buf, "RES//player_%d.bmp", i);
		m_back[i].Init(hdc, buf);
	}
}

void BitMapManager::FireLoad(HDC hdc)
{
	for (int i = FIRE_NORMAL0; i <= FIRE_RINGRIGHT1; i++)
	{
		sprintf_s(buf, "RES//fire_%d.bmp", i);
		m_back[i].Init(hdc, buf);
	}
}

void BitMapManager::EtcLoad(HDC hdc)
{
	for (int i = STAR_B; i <= STAR_Y; i++)
	{
		sprintf_s(buf, "RES//star_%d.bmp", i);
		m_back[i].Init(hdc, buf);
	}

	sprintf_s(buf, "RES//cash.bmp");
	m_back[CASH].Init(hdc, buf);
	sprintf_s(buf, "RES//goal.bmp");
	m_back[GOAL].Init(hdc, buf);
}



BitMapManager::~BitMapManager()
{
	delete[] m_back;
}
