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
	playerstr = L"��";
	initX = posX;
}

void Player::Draw(HDC hdc)
{
	//HDC memDC = CreateCompatibleDC(hdc);
	//HBITMAP oldBitmap = (HBITMAP)SelectObject(memDC);
	//��ũ���� �������� �÷��̾��� x��ǥ�� ++, --�Ǿ����.
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
	//����Ű �Է¿� ���� �÷��̾��� x��ǥ ������Ʈ
	//�ӵ��� ����� ����Ѱ� ���߿� ����
	if (GetAsyncKeyState(VK_LEFT))
	{
		posX -= m_speed * deltaTime;
	}
	if (GetAsyncKeyState(VK_RIGHT))
	{
		posX += m_speed * deltaTime;
	}
	//x ���� 0~600
	//if (x < 0) x = 0;
	//if (x < initX) x = initX;
	if (posX >= 600) posX = 600;
	//ó���� �÷��̾�� ��ũ���� ���� ������ ���߿� �����ӿ����� -500�������� ���� ��Ʈ�� ��ġ�ؾ��ҵ�
}

Player::~Player()
{
}
