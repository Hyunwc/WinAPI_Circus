#include "GameManager.h"
#include <iostream>

GameManager* GameManager::instance = nullptr;

void GameManager::Init(HWND hWnd, HDC hdc)
{
	m_hWnd = hWnd;
	m_hdc = hdc;
	g_nX = 0;

	RECT clientRect;
	GetClientRect(m_hWnd, &clientRect);
	width = clientRect.right + 1;
	height = clientRect.bottom + 1;
	
	backDC = CreateCompatibleDC(m_hdc);
	BitMapManager::GetInstance()->Init(m_hdc);

	m_line = RUNLINE;
	m_background.Init(m_hdc);
	m_player.Init();
	/*audience = BitMapManager::GetInstance()->GetImage(IMAGE_AUDIENCE);
	elephant = BitMapManager::GetInstance()->GetImage(IMAGE_ELEPHANT);
	grass = BitMapManager::GetInstance()->GetImage(IMAGE_GRASS);*/
}

void GameManager::Update(float deltaTime)
{
	/*timer += deltaTime;
	TextOutA(m_hdc, 0, 0, std::to_string(timer).c_str(), std::to_string(timer).length());*/

	//m_line = m_background.GetLine();

	//RUNLINE이 배경스크롤이 되어야함.
	if (m_line == RUNLINE) //골인라인 도착 전
	{
		if (GetAsyncKeyState(VK_LEFT))
		{
			g_nX += 150 * deltaTime;
		}
		if (GetAsyncKeyState(VK_RIGHT))
		{
			g_nX -= 150 * deltaTime;
		}

		//포지션이 -몇까지 도달시 800으로
		if (g_nX <= -800) g_nX += 800;

		//백그라운드의 골대쪽 도달시 EndLine으로 
		if (m_background.IsGoal())
		{
			SetLine(ENDLINE);
		}
	}
	else if (m_line == ENDLINE)
	{
		m_player.Update(deltaTime);

		//플레이어의 포지션이 50이하가 될시 RunLine으로
		if (m_player.GetPosX() <= 50)
		{
			SetLine(RUNLINE);
			m_player.SetPosX();
		}
	}
}

void GameManager::TestDraw()
{
	//audience->Draw(m_hdc, 10, 10);
	//elephant->Draw(m_hdc, 50, 100);
	//grass->Draw(m_hdc, 50, 100);
}

void GameManager::Draw()
{
	HBITMAP backBitmap = CreateCompatibleBitmap(m_hdc, width, height);
	SelectObject(backDC, backBitmap);

	m_background.Draw(backDC, g_nX);

	m_player.Draw(backDC);
	BitBlt(m_hdc, 0, 0, width, height, backDC, 0, 0, SRCCOPY);

	DeleteObject(backBitmap);
}

HBITMAP GameManager::MyCreateDIBSection(HDC hdc, int w, int h)
{
	BITMAPINFO bm_info;
	ZeroMemory(&bm_info.bmiHeader, sizeof(BITMAPINFOHEADER));

	bm_info.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);

	bm_info.bmiHeader.biBitCount = 24;
	bm_info.bmiHeader.biWidth = w;
	bm_info.bmiHeader.biHeight = h;
	bm_info.bmiHeader.biPlanes = 1;

	LPVOID pBits;
	return CreateDIBSection(hdc, &bm_info, DIB_RGB_COLORS, (void**)&pBits, NULL, 0);
}

GameManager::~GameManager()
{
	DeleteDC(backDC);
}