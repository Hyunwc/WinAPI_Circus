#include "BackGround.h"

BackGround::BackGround() : g_nX(0.0f), goalX(0.0f)
{
	m_speed = NORMAL;
	isScrollStopped = false;
}

void BackGround::Init(HDC hdc)
{
	dc = hdc;
	goalstr = L"Goal!";
	audience = BitMapManager::GetInstance()->GetImage(BACK_AUDIENCE0);
	elephant = BitMapManager::GetInstance()->GetImage(BACK_ELEPHANT);
	grass = BitMapManager::GetInstance()->GetImage(BACK_GRASS);
	m_line = RUNLINE;
	//goal = BitMapManager::GetInstance()->GetImage(IMAGE_GRASS);
}

void BackGround::Draw(HDC hdc)
{
	//true일시 스크롤 멈춤
	//if (isScrollStopped) g_nX = 0;

	HDC memDC = CreateCompatibleDC(hdc);
	HBITMAP oldBitmap = (HBITMAP)SelectObject(memDC, audience);

	wstring positionText = L"Back_X: " + to_wstring(g_nX);
	TextOut(hdc, 0, 40, positionText.c_str(), positionText.length());
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

	SelectObject(memDC, oldBitmap);
	DeleteDC(memDC);
}

void BackGround::Update(float deltaTime)
{
	//런라인 일때 스크롤
	if (m_line == RUNLINE)
	{
		if (GetAsyncKeyState(VK_LEFT))
		{
			g_nX += m_speed * deltaTime;
			totalDistance -= m_speed * deltaTime;
		}
		if (GetAsyncKeyState(VK_RIGHT))
		{
			g_nX -= m_speed * deltaTime;
			totalDistance += m_speed * deltaTime;
		}

		//포지션이 -800 이하로 도달하면 800을 더해 스크롤 반복
		if (g_nX <= -800.0f) g_nX += 800.0f;

		//골대 포지션 업데이트
		goalX = g_nX + 1350.0f;

		if (IsGoal()) g_nX = -750.0f;  // 특정 위치로 초기화
		else if (IsStartLine()) g_nX = 0.0f;
	}

	
}


void BackGround::Render(HDC hdc)
{
}

bool BackGround::IsGoal()
{
	//g_nX = -750.0f;
	return (goalX <= 600.0f);
}

bool BackGround::IsStartLine()
{
	return (totalDistance <= 50.0f);
}



BackGround::~BackGround()
{
}
