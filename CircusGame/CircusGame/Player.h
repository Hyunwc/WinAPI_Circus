#pragma once
#include "Mecro.h"
#include "BitMapManager.h"
#include "BackGround.h"

class Player
{
private:
	wstring playerstr;
	float posX;
	float posY;
	int initX; //�ʱ� x��ġ
	bool isJumping; //����������?
	SPEED m_speed;
	LINE m_line;
	BitMap* player;
public:
	Player();
	void Init();
	void Draw(HDC hdc);
	void Jump();
	void Update(float deltaTime);
	float GetPosX() { return posX; }
	void SetState(LINE state) { m_line = state; }
	void SetPosX() { posX = initX; }
	~Player();
};