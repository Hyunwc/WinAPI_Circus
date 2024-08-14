#pragma once
#include "Mecro.h"
#include "BitMapManager.h"
#include "BackGround.h"

class Player
{
private:
	wstring playerstr;
	int x;
	int y;
	int initX; //초기 x위치
	bool isJumping; //점프중인지?
	BackGround* m_background;
public:
	Player();
	void Init();
	void Draw(HDC hdc);
	void Jump();
	void Update(float deltaTime);
	int GetPosX() { return x; }
	void SetPosX() { x = initX; }
	~Player();
};