#pragma once
#include "global.h"
#include "CGameLogic.h"
#include "CGraph.h"
class CGameControl
{
public:
	CGraph m_graph;	   // ��Ϸ��ͼ
	Vertex m_svSelFst; // ��һ��ѡ�еĵ�(x��ʾ��)
	Vertex m_svSelSec; // �ڶ���ѡ�еĵ�(y��ʾ�У�
public:
	void StartGame(void);									// ��ʼ��Ϸ
	int GetElement(int nRow, int nCol);						/// ���ĳ��ĳ�е�ͼƬ���
	void SetFirstPoint(int nRow, int nCol);					// ���õ�һ���������
	void SetSecPoint(int nRow, int nCol);					// ���õڶ����������
	bool Link(Vertex avPath[MAX_VERTEX_NUM], int &nVexnum); // �����жϺ���
	BOOL IsWin(int nTime);									// �ж��Ƿ�ʤ��
	bool Help(Vertex avPath[MAX_VERTEX_NUM], int &nVexnum); // �ڵ�ͼ�в��ҿ���������һ����Ƭ����������·����·���ϵĶ�����
	void Resert();											// ���ú����������ݳ�Աm_graph�е����ݽ�������
};
