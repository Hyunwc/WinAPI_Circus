
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
	
	m_background.SetState(RUNLINE);
	m_player.SetState(RUNLINE); 
}

void GameManager::Update(float deltaTime)
{
	//��밡 ��Ÿ������
	if (m_background.IsGoal())
	{
		m_player.SetState(ENDLINE); //�̻����϶� �¿�� �̵��� �����ϰ�
		m_background.SetState(ENDLINE); //�̻����϶� ��ũ���� �ߴܵǰ�
	}
	//�÷��̾��� �������� 50���� ������
	//������ 50���� �ʱ�ȭ.�¿��̵� ����, 
	if (m_player.GetPosX() < 50.0f)
	{
		m_player.SetPosX(); //�÷��̾������� 50.0����
		m_player.SetState(RUNLINE); //�÷��̾� �¿� �̵� ����
		m_background.SetState(RUNLINE); //��ũ�� �ٽ� ����.
	}

	m_player.Update(deltaTime);
	m_background.Update(deltaTime);
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