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
	//true�Ͻ� ��ũ�� ����
	//if (isScrollStopped) g_nX = 0;

	HDC memDC = CreateCompatibleDC(hdc);
	HBITMAP oldBitmap = (HBITMAP)SelectObject(memDC, audience);

	wstring positionText = L"Back_X: " + to_wstring(g_nX);
	TextOut(hdc, 0, 40, positionText.c_str(), positionText.length());
	//m_background.Draw(backDC);
	
	//��������
	for (int i = 0; i < 7; i++)
	{
		audience->Draw(hdc, g_nX + i * 100, 100, 230, 300);
	}
	SelectObject(memDC, elephant);
	//�ڳ����� ����
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
	//����� �������� �ؽ�Ʈ
	TextOut(hdc, g_nX + 1350.0f, 500, goalstr.c_str(), goalstr.length());

	SelectObject(memDC, oldBitmap);
	DeleteDC(memDC);
}

void BackGround::Update(float deltaTime)
{
	//������ �϶� ��ũ��
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

		//�������� -800 ���Ϸ� �����ϸ� 800�� ���� ��ũ�� �ݺ�
		if (g_nX <= -800.0f) g_nX += 800.0f;

		//��� ������ ������Ʈ
		goalX = g_nX + 1350.0f;

		if (IsGoal()) g_nX = -750.0f;  // Ư�� ��ġ�� �ʱ�ȭ
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
