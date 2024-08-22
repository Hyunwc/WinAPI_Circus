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
	//player = BitMapManager::GetInstance()->GetImage(PLAYER_MOVE1);
	playerstr = L"웃";
	initX = posX;
	m_line = RUNLINE;
}

void Player::Draw(HDC hdc)
{
	//HDC memDC = CreateCompatibleDC(hdc);
	//HBITMAP oldBitmap = (HBITMAP)SelectObject(memDC);
	//스크롤이 멈췄을때 플레이어의 x좌표가 ++, --되어야함.
	//
	//player->Draw(hdc, posX, posY, 125, 125);
	TextOut(hdc, posX, posY, playerstr.c_str(), playerstr.length());
	wstring positionText = L"Player X: " + to_wstring(posX);
	
    TextOut(hdc, 0, 10, positionText.c_str(), positionText.length());
}

void Player::Jump()
{
	//점프상태일때 
	if (isJumping)
	{
		
	}
	
}

void Player::Update(float deltaTime)
{
	Jump();
	//방향키 입력에 따라 플레이어의 x좌표 업데이트
	//속도값 상수로 계산한거 나중에 수정
	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		//점프인지 아닌지 체크할 코드 작성
	}
	
	if (m_line == ENDLINE)
	{
		if (GetAsyncKeyState(VK_LEFT))
		{
			posX -= m_speed * deltaTime;
		}
		if (GetAsyncKeyState(VK_RIGHT))
		{
			posX += m_speed * deltaTime;
		}
	}
	if (posX >= 600.0f) posX = 600.0f;
	//x 제한 0~600
	//if (x < 0) x = 0;
	//if (x < initX) x = initX;
	
}

Player::~Player()
{
}
