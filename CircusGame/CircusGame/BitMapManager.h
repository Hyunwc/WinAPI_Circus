#pragma once
#include "BitMap.h"

class BitMapManager
{
private:
	static BitMapManager* m_hThis;
	BitMap m_back;

	BitMapManager();
public:
	static BitMapManager* GetInstance()
	{
		if (m_hThis == NULL)
		{
			m_hThis = new BitMapManager;
		}
		return m_hThis;
	}
	static void Release()
	{
		if (m_hThis)
		{
			delete m_hThis;
			m_hThis = nullptr;
		}
	}
	void Init(HDC hdc);
	~BitMapManager();
};