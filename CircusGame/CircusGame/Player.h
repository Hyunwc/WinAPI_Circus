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
	int initX; //초기 x위치
	bool isJumping; //점프중인지?
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