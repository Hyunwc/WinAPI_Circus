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
public:
	Player();
	void Init();
	void Draw(HDC hdc);
	void Jump();
	void Update(float deltaTime);
	float GetPosX() { return posX; }
	void SetPosX() { posX = initX; }
	~Player();
};