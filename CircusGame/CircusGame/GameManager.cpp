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
}

void GameManager::Update(float deltaTime)
{
	/*timer += deltaTime;
	TextOutA(m_hdc, 0, 0, std::to_string(timer).c_str(), std::to_string(timer).length());*/

	//RUNLINE�� ��潺ũ���� �Ǿ����.
	if (m_line == STARTLINE)
	{
		if (GetAsyncKeyState(VK_RIGHT))
		{
			g_nX -= 150 * deltaTime;
			totalDistance += 150 * deltaTime;
		}

		if (totalDistance > 50)
		{
			SetLine(RUNLINE);
		}
	}
	else if (m_line == RUNLINE) //���ζ��� ���� ��
	{
		if (GetAsyncKeyState(VK_LEFT))
		{
			g_nX += 150 * deltaTime;
			totalDistance -= 150 * deltaTime;
		}
		if (GetAsyncKeyState(VK_RIGHT))
		{
			g_nX -= 150 * deltaTime;
			totalDistance += 150 * deltaTime;
		}

		//TextOutA(m_hdc, 0, 20, std::to_string(totalDistance).c_str(), std::to_string(totalDistance).length());

		//�������� -����� ���޽� 800����
		if (g_nX <= -800) g_nX += 800;

		//��׶����� ����� ���޽� EndLine���� 
		if (m_background.IsGoal())
		{
			SetLine(ENDLINE);
		}

		if (totalDistance <= 50)
		{
			SetLine(STARTLINE);
		}
	}
	else if (m_line == ENDLINE)
	{
		m_player.Update(deltaTime);

		//�÷��̾��� �������� 50���ϰ� �ɽ� RunLine����
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


	//m_background.Draw(backDC,g_nX);

	m_player.Draw(backDC);
	BitBlt(m_hdc, 0, 0, width, height, backDC, 0, 0, SRCCOPY);

	DeleteObject(backBitmap);
}


GameManager::~GameManager()
{
	DeleteDC(backDC);
}