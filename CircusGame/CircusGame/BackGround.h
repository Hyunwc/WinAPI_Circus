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
	bool isFinal;
	//BitMap* goal;
public:
	BackGround();
	void Init(HDC hdc);
	void Draw(HDC hdc, float g_nX);
	bool IsFinal() { return isFinal; }
	~BackGround();
};