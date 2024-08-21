#include "Player.h"

Player::Player()
{
	posX = 50.0f;
	posY = 500.0f;
	m_speed = NORMAL;
	isJumping = false;
}

void Player::Init()
{
	player = BitMapManager::GetInstance()->GetImage(PLAYER_MOVE1);
	playerstr = L"웃";
	initX = posX;
}

void Player::Draw(HDC hdc)
{
	//HDC memDC = CreateCompatibleDC(hdc);
	//HBITMAP oldBitmap = (HBITMAP)SelectObject(memDC);
	//스크롤이 멈췄을때 플레이어의 x좌표가 ++, --되어야함.
	//
	player->Draw(hdc, posX, posY, 125, 125);
	//TextOut(hdc, posX, posY, playerstr.c_str(), playerstr.length());
	wstring positionText = L"Player X: " + to_wstring(posX);
	//TextOut(hdc, 10, 10, positionText.c_str(), positionText.length());
	TextOut(hdc, 0, 10, positionText.c_str(), positionText.length());
}

void Player::Jump()
{

	
}

void Player::Update(float deltaTime)
{
	//방향키 입력에 따라 플레이어의 x좌표 업데이트
	//속도값 상수로 계산한거 나중에 수정
	if (GetAsyncKeyState(VK_LEFT))
	{
		posX -= m_speed * deltaTime;
	}
	if (GetAsyncKeyState(VK_RIGHT))
	{
		posX += m_speed * deltaTime;
	}
	//x 제한 0~600
	//if (x < 0) x = 0;
	//if (x < initX) x = initX;
	if (posX >= 600) posX = 600;
	//처음에 플레이어는 스크롤이 되지 않으니 나중에 눈속임용으로 -500정도까지 관객 비트맵 설치해야할듯
}

Player::~Player()
{
}
