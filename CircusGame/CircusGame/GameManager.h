#pragma once

#include "Mecro.h"
#include "BitMapManager.h"
#include "BackGround.h"

class GameManager
{
private:
	static GameManager* instance;
	HWND m_hWnd;
	HDC m_hdc;
	HDC backDC;
	int width, height;
	//되는지 테스트부터
	BitMap* audience;
	BitMap* elephant;
	BitMap* grass;
	//RECT backRect;
	float g_nX = 0;
	bool isFinal;

	BackGround m_background;
	GameManager() : isFinal(false) {}
public:
	~GameManager();
	static GameManager* Instance()
	{
		if (instance == nullptr) instance = new GameManager;
		return instance;
	}
	static void Release()
	{
		BitMapManager::Release();
		if (instance)
		{
			delete instance;
			instance = nullptr;
		}
	}

	void Init(HWND hWnd, HDC hdc);
	void Update(float deltaTime);
	void TestDraw();
	void Draw();
	HBITMAP MyCreateDIBSection(HDC hdc, int w, int h);
};
