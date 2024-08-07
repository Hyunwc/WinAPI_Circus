#include "BitMapManager.h"

BitMapManager* BitMapManager::m_hThis = NULL;

BitMapManager::BitMapManager()
{
	m_back = new BitMap[IMAGE_END];
}

void BitMapManager::Init(HDC hdc)
{
	char buf[256];
	for (int i = IMAGE_START; i < IMAGE_END; i++)
	{
		sprintf_s(buf, "RES//back_%d.bmp", i);
		m_back[i].Init(hdc, buf);
	}
}

BitMapManager::~BitMapManager()
{
	delete[] m_back;
}
