#pragma once
#include"global.h"
#include"CGameLogic.h"
class CGameControl
{
public:
	int m_anMap[4][4];   //��Ϸ��ͼ
	//x->col,y->row
	Vertex m_svSelFst;   //��һ��ѡ�еĵ�(x��ʾ��)
	Vertex m_svSelSec;
public:
	void StartGame(void);   //��ʼ��Ϸ
	int GetElement(int nRow, int nCol);   ///���ĳ��ĳ�е�ͼƬ���
	void SetFirstPoint(int nRow, int nCol);   //���õ�һ���������
	void SetSecPoint(int nRow, int nCol);	  //���õڶ����������									
	bool Link(Vertex avPath[2]);   //�����жϺ���
};

