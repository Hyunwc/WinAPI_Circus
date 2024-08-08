#include "BackGround.h"

BackGround::BackGround()
{
	isFinal = false;
}

void BackGround::Init(HDC hdc)
{
	dc = hdc;
	goalstr = L"Goal!";
	audience = BitMapManager::GetInstance()->GetImage(IMAGE_AUDIENCE);
	elephant = BitMapManager::GetInstance()->GetImage(IMAGE_ELEPHANT);
	grass = BitMapManager::GetInstance()->GetImage(IMAGE_GRASS);
	//goal = BitMapManager::GetInstance()->GetImage(IMAGE_GRASS);
}

void BackGround::Draw(HDC hdc, float g_nX)
{
	HDC memDC = CreateCompatibleDC(hdc);
	HBITMAP oldBitmap = (HBITMAP)SelectObject(memDC, audience);

	//m_background.Draw(backDC);

	//包按何磐
	for (int i = 0; i < 7; i++)
	{
		audience->Draw(hdc, g_nX + i * 100, 100, 230, 300);
	}
	SelectObject(memDC, elephant);
	//内尝府肺 函版
	elephant->Draw(hdc, g_nX + 7 * 100, 100, 230, 300);
	SelectObject(memDC, audience);

	for (int i = 0; i < 7; i++)
	{
		audience->Draw(hdc, g_nX + (i + 8) * 100, 100, 230, 300);
	}
	SelectObject(memDC, elephant);
	elephant->Draw(hdc, g_nX + (7 + 8) * 100, 100, 230, 300);

	SelectObject(memDC, grass);

	grass->Draw(hdc, 0, 180, 1700, 510);
	TextOut(hdc, g_nX + 1350, 500, goalstr.c_str(), goalstr.length());
	
	SelectObject(memDC, oldBitmap);
	DeleteDC(memDC);
}



BackGround::~BackGround()
{
}
