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
	int initX; //�ʱ� x��ġ
	bool isJumping; //����������?
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