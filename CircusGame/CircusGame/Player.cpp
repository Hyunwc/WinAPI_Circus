#include "Player.h"
#include "GameManager.h"
Player::Player()
{
	x = 50;
	y = 500;
	isJumping = false;
}

void Player::Init()
{
	playerstr = L"웃";
	initX = x;
}

void Player::Draw(HDC hdc)
{
	//HDC memDC = CreateCompatibleDC(hdc);
	//HBITMAP oldBitmap = (HBITMAP)SelectObject(memDC);
	//스크롤이 멈췄을때 플레이어의 x좌표가 ++, --되어야함.
	//
	TextOut(hdc, x, y, playerstr.c_str(), playerstr.length());
	std::wstring positionText = L"Player X: " + std::to_wstring(x);
	TextOut(hdc, 10, 10, positionText.c_str(), positionText.length());
}

void Player::Jump()
{

	
}

void Player::Update(float deltaTime)
{
	
		//방향키 입력에 따라 플레이어의 x좌표 업데이트
		if (GetAsyncKeyState(VK_LEFT))
		{
			x -= 150 * deltaTime;
		}
		if (GetAsyncKeyState(VK_RIGHT))
		{
			x += 150 * deltaTime;
		}


		//x 제한 0~600
		//if (x < 0) x = 0;
		if (x >= 600) x = 600;

	
	
	
	//처음에 플레이어는 스크롤이 되지 않으니 나중에 눈속임용으로 -500정도까지 관객 비트맵 설치해야할듯
}

Player::~Player()
{
}
