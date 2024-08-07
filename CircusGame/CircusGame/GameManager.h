#pragma once

#include "Mecro.h"
#include "BitMapManager.h"

class GameManager
{
private:
	static GameManager* instance;
	HWND m_hWnd;
	HDC m_hdc;
	float g_nX = 0;
	GameManager(){}
public:
	~GameManager();
	static GameManager* Instance()
	{
		if (instance == nullptr) instance = new GameManager;
		return instance;
	}
	static void Release()
	{
		if (instance)
		{
			delete instance;
			instance = nullptr;
		}
	}
	void Init(HWND hWnd, HDC hdc);
	void Update(float deltaTime);
	void Draw();
};
