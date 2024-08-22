
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
	//골대가 나타났을때
	if (m_background.IsGoal())
	{
		m_player.SetState(ENDLINE); //이상태일때 좌우로 이동이 가능하게
		m_background.SetState(ENDLINE); //이상태일때 스크롤이 중단되게
	}
	//플레이어의 포지션이 50보다 낮으면
	//포지션 50으로 초기화.좌우이동 중지, 
	if (m_player.GetPosX() < 50.0f)
	{
		m_player.SetPosX(); //플레이어포지션 50.0으로
		m_player.SetState(RUNLINE); //플레이어 좌우 이동 중지
		m_background.SetState(RUNLINE); //스크롤 다시 시작.
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