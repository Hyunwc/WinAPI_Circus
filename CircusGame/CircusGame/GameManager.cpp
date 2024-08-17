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

	//deltaTime = std::clamp(deltaTime, 0.01f, 0.1f);
	
	if (m_line == STARTLINE)
	{
		if (GetAsyncKeyState(VK_RIGHT))
		{
			m_background.Update(deltaTime);
		}

		if (!m_background.IsStartLine())
		{
			SetLine(RUNLINE);
		}
	}
	else if (m_line == RUNLINE) //���ζ��� ���� ��
	{
		m_background.Update(deltaTime);
		
		//��뿡 ���� �� ENDLINE���� ��ȯ
		if (m_background.IsGoal())
		{
			SetLine(ENDLINE);
		}

		//TextOutA(m_hdc, 0, 20, std::to_string(totalDistance).c_str(), std::to_string(totalDistance).length());


		if (m_background.IsStartLine())
		{
			SetLine(STARTLINE);
		}
	}
	else if (m_line == ENDLINE)
	{
		//ENDLINE�� �÷��̾�� ��ǥ ���� ����
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


	m_background.Draw(backDC);

	m_player.Draw(backDC);
	BitBlt(m_hdc, 0, 0, width, height, backDC, 0, 0, SRCCOPY);

	DeleteObject(backBitmap);
}

void GameManager::Render()
{
}


GameManager::~GameManager()
{
	DeleteDC(backDC);
}