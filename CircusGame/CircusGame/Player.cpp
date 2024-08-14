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
	playerstr = L"��";
	initX = x;
}

void Player::Draw(HDC hdc)
{
	//HDC memDC = CreateCompatibleDC(hdc);
	//HBITMAP oldBitmap = (HBITMAP)SelectObject(memDC);
	//��ũ���� �������� �÷��̾��� x��ǥ�� ++, --�Ǿ����.
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
	
		//����Ű �Է¿� ���� �÷��̾��� x��ǥ ������Ʈ
		if (GetAsyncKeyState(VK_LEFT))
		{
			x -= 150 * deltaTime;
		}
		if (GetAsyncKeyState(VK_RIGHT))
		{
			x += 150 * deltaTime;
		}


		//x ���� 0~600
		//if (x < 0) x = 0;
		if (x >= 600) x = 600;

	
	
	
	//ó���� �÷��̾�� ��ũ���� ���� ������ ���߿� �����ӿ����� -500�������� ���� ��Ʈ�� ��ġ�ؾ��ҵ�
}

Player::~Player()
{
}
