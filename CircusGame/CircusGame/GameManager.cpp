#include "GameManager.h"

GameManager* GameManager::instance = nullptr;

GameManager::~GameManager()
{
}

void GameManager::Init(HWND hWnd, HDC hdc)
{
	m_hWnd = hWnd;
	m_hdc = hdc;
	
}

void GameManager::Update(float deltaTime)
{
}

void GameManager::Draw()
{
}
