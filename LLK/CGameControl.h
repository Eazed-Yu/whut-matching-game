#pragma once
#include"global.h"
#include"CGameLogic.h"
#include"CGraph.h"
class CGameControl
{
public:
	CGraph m_graph;   //��Ϸ��ͼ
	Vertex m_svSelFst;   //��һ��ѡ�еĵ�(x��ʾ��)
	Vertex m_svSelSec;   //�ڶ���ѡ�еĵ�(y��ʾ�У�
public:
	void StartGame(void);   //��ʼ��Ϸ
	void SetFirstPoint(int nRow, int nCol);   //���õ�һ���������
	void SetSecPoint(int nRow, int nCol);	  //���õڶ����������
	int GetElement(int nRow, int nCol);   ///���ĳ��ĳ�е�ͼƬ���
	bool Link(Vertex avPath[4], int &nVexnum);   //�����жϺ���
};

