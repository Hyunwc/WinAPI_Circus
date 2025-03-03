#pragma once
#include "Mecro.h"
#include "BitMapManager.h"
//골대가 보이는 순간 캐릭터가 왔다갔다해야되는데
//화면에서 벗어나면
//배경이 밀리니 테스트부터

class BackGround
{
private:
	//std::vector<BitMap*> m_background;
	HDC dc;
	BitMap* audience;
	BitMap* elephant;
	BitMap* grass;
	wstring goalstr;
	bool isScrollStopped;
	float g_nX; //백그라운드의 x좌표
	float goalX;
	float totalDistance; 
	SPEED m_speed;
	LINE m_line;
	//BitMap* goal;
public:
	BackGround();
	void Init(HDC hdc);
	void Draw(HDC hdc);
	void Update(float deltaTime);
	void Render(HDC hdc);
	bool IsGoal();
	bool IsStartLine();
	void SetState(LINE state) { m_line = state; }
	LINE GetLine() { return m_line; }
	~BackGround();
};