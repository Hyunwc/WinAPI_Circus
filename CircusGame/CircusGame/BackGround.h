#pragma once
#include "Mecro.h"
#include "BitMapManager.h"
//��밡 ���̴� ���� ĳ���Ͱ� �Դٰ����ؾߵǴµ�
//ȭ�鿡�� �����
//����� �и��� �׽�Ʈ����

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
	float g_nX; //��׶����� x��ǥ
	float speed; //��ũ�� �ӵ�
	float goalX;
	float totalDistance; 
	float scrollError;
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
	LINE GetLine() { return m_line; }
	~BackGround();
};