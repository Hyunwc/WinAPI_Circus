#include "BackGround.h"
#include "GameManager.h"

BackGround::BackGround()
{
	isScrollStopped = false;
}

void BackGround::Init(HDC hdc)
{
	dc = hdc;
	goalstr = L"Goal!";
	audience = BitMapManager::GetInstance()->GetImage(IMAGE_AUDIENCE);
	elephant = BitMapManager::GetInstance()->GetImage(IMAGE_ELEPHANT);
	grass = BitMapManager::GetInstance()->GetImage(IMAGE_GRASS);
	m_line = RUNLINE;
	//goal = BitMapManager::GetInstance()->GetImage(IMAGE_GRASS);
}

void BackGround::Draw(HDC hdc, float g_nX)
{
	//true일시 스크롤 멈춤
	//if (isScrollStopped) g_nX = 0;

	HDC memDC = CreateCompatibleDC(hdc);
	HBITMAP oldBitmap = (HBITMAP)SelectObject(memDC, audience);

	
	//m_background.Draw(backDC);
	
	//관객부터
	for (int i = 0; i < 7; i++)
	{
		audience->Draw(hdc, g_nX + i * 100, 100, 230, 300);
	}
	SelectObject(memDC, elephant);
	//코끼리로 변경
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
	//실험용 골인지점 텍스트
	TextOut(hdc, g_nX + 1350.0f, 500, goalstr.c_str(), goalstr.length());
	
	goalX = g_nX + 1350.0f;
	/*if (g_nX + 1350.0f <= 600)
	{
		goalX = g_nX + 1350.0f;
	}*/

	SelectObject(memDC, oldBitmap);
	DeleteDC(memDC);
}

bool BackGround::IsGoal()
{
	if (goalX <= 600)
	{
		return true;
	}
	return false;
}



BackGround::~BackGround()
{
}
