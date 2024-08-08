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

	InvalidateRect(m_hWnd, NULL, FALSE);
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
	//HBITMAP backBitmap = MyCreateDIBSection(m_hdc, width, height);
	SelectObject(backDC, backBitmap);

	HDC memDC = CreateCompatibleDC(m_hdc);
	HBITMAP oldBitmap = (HBITMAP)SelectObject(memDC, audience);

	//StretchBlt(backDC, g_nX + 1 * 100, 100, 230, 300, memDC, 0, 0, 145, 245, SRCCOPY);
	//관객부터
	for (int i = 0; i < 7; i++)
	{
		audience->Draw(backDC, g_nX + i * 100, 100, 230, 300);
		//StretchBlt(backDC, g_nX + i * 100, 100, 230, 300, memDC, 0, 0, 145, 245, SRCCOPY);
	}
	SelectObject(memDC, elephant);
	//코끼리로 변경
	//oldBitmap = (HBITMAP)SelectObject(memDC, elephant);
	//StretchBlt(backDC, g_nX + 7 * 100, 100, 230, 300, memDC, 0, 0, 145, 245, SRCCOPY);
	elephant->Draw(backDC, g_nX + 7 * 100, 100, 230, 300);
	SelectObject(memDC, audience);
	//oldBitmap = (HBITMAP)SelectObject(memDC, audience);
	for (int i = 0; i < 7; i++)
	{
		audience->Draw(backDC, g_nX + (i + 8) * 100, 100, 230, 300);
		//StretchBlt(backDC, g_nX + (i + 8) * 100, 100, 230, 300, memDC, 0, 0, 145, 245, SRCCOPY);
	}
	SelectObject(memDC, elephant);
	//oldBitmap = (HBITMAP)SelectObject(memDC, elephant);
	elephant->Draw(backDC, g_nX + (7 + 8) * 100, 100, 230, 300);
	//StretchBlt(backDC, g_nX + (7 + 8) * 100, 100, 230, 300, memDC, 0, 0, 145, 245, SRCCOPY);
	SelectObject(memDC, grass);
	//oldBitmap = (HBITMAP)SelectObject(memDC, grass);
	//StretchBlt(backDC, 0, 180, 1700, 510, memDC, 0, 0, 145, 245, SRCCOPY);
	grass->Draw(backDC, 0, 180, 1700, 510);

	SelectObject(memDC, oldBitmap);
	DeleteDC(memDC);

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