#include "pch.h"
#include "CGameControl.h"

//��ʼ��Ϸ
void CGameControl::StartGame(void)
{
	CGameLogic gameLogic;
	gameLogic.InitMap(m_graph);
}

//���õ�һ����
void CGameControl::SetFirstPoint(int nRow, int nCol)
{
	m_svSelFst.row = nRow;
	m_svSelFst.col = nCol;
}

//���õڶ�����
void CGameControl::SetSecPoint(int nRow, int nCol)
{
	m_svSelSec.row = nRow;
	m_svSelSec.col = nCol;
}

//����Ԫ����Ϣ
int CGameControl::GetElement(int nRow, int nCol)
{
	return m_graph.GetVertex(nRow * 4 + nCol);
}

//�����ж�
bool CGameControl::Link(Vertex avPath[4], int& nVexnum)
{
	//�ж�����ѡ�е��Ƿ���ͬһ����
	if (m_svSelFst.row == m_svSelSec.row && m_svSelFst.col == m_svSelSec.col)
	{
		return false;
	}

	//�ж�ͼƬ�Ƿ���ͬ
	if (m_graph.GetVertex(m_svSelFst.row * 4 + m_svSelFst.col) != m_graph.GetVertex(m_svSelSec.row * 4 + m_svSelSec.col))
	{
		return false;
	}

	//�ж��Ƿ���ͨ
	CGameLogic logic;
	if (logic.IsLink(m_graph, m_svSelFst, m_svSelSec))
	{
		//����
		logic.Clear(m_graph, m_svSelFst, m_svSelSec);

		//����·������
		nVexnum = logic.GetVexPath(avPath);
		return true;
	} 
	return false;
}