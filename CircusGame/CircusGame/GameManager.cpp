#include "GameManager.h"

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

	audience = BitMapManager::GetInstance()->GetImage(IMAGE_AUDIENCE);
	elephant = BitMapManager::GetInstance()->GetImage(IMAGE_ELEPHANT);
	grass = BitMapManager::GetInstance()->GetImage(IMAGE_GRASS);
}

void GameManager::Update(float deltaTime)
{
	g_nX -= 100 * deltaTime;

	//포지션이 -몇까지 도달시 800으로
	if (g_nX <= -800) g_nX += 800;
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

	HDC memDC = CreateCompatibleDC(m_hdc);
	HBITMAP oldBitmap = (HBITMAP)SelectObject(memDC, audience);

	//StretchBlt(backDC, g_nX + 1 * 100, 100, 230, 300, memDC, 0, 0, 145, 245, SRCCOPY);
	//관객부터
	for (int i = 0; i < 7; i++)
	{
		StretchBlt(backDC, g_nX + i * 100, 100, 230, 300, memDC, 0, 0, 145, 245, SRCCOPY);
	}
	//코끼리로 변경
	oldBitmap = (HBITMAP)SelectObject(memDC, elephant);
	StretchBlt(backDC, g_nX + 7 * 100, 100, 230, 300, memDC, 0, 0, 145, 245, SRCCOPY);

	oldBitmap = (HBITMAP)SelectObject(memDC, audience);
	for (int i = 0; i < 7; i++)
	{
		StretchBlt(backDC, g_nX + (i + 8) * 100, 100, 230, 300, memDC, 0, 0, 145, 245, SRCCOPY);
	}

	oldBitmap = (HBITMAP)SelectObject(memDC, elephant);
	StretchBlt(backDC, g_nX + (7 + 8) * 100, 100, 230, 300, memDC, 0, 0, 145, 245, SRCCOPY);

	oldBitmap = (HBITMAP)SelectObject(memDC, grass);
	StretchBlt(backDC, 0, 180, 1700, 510, memDC, 0, 0, 145, 245, SRCCOPY);

	SelectObject(memDC, oldBitmap);
	DeleteDC(memDC);

	BitBlt(m_hdc, 0, 0, width, height, backDC, 0, 0, SRCCOPY);

	DeleteObject(backBitmap);
}

GameManager::~GameManager()
{
	DeleteDC(backDC);
}