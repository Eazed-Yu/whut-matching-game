#include "pch.h"
#include "CGameControl.h"

//��ʼ��Ϸ
void CGameControl::StartGame(void)
{
	CGameLogic gameLogic;
	gameLogic.InitMap(m_graph);
}

//����Ԫ����Ϣ
int CGameControl::GetElement(int nRow, int nCol)
{
	return m_graph.GetVertex(nRow * MAX_COL + nCol);
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


//�����ж�
bool CGameControl::Link(Vertex avPath[MAX_VERTEX_NUM], int& nVexnum)
{
	//�ж�����ѡ�е��Ƿ���ͬһ����
	if (m_svSelFst.row == m_svSelSec.row && m_svSelFst.col == m_svSelSec.col)
	{
		return false;
	}

	//�ж�ͼƬ�Ƿ���ͬ�������ͬ������ͨ
	int	nInfo1 = m_graph.GetVertex(m_svSelFst.row * MAX_COL + m_svSelFst.col);
	int	nInfo2 = m_graph.GetVertex(m_svSelSec.row * MAX_COL + m_svSelSec.col);

	if (nInfo1 != nInfo2 || nInfo1 == BLANK || nInfo2 == BLANK)
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

//�ж��Ƿ��ʤ
BOOL CGameControl::IsWin(int nTime)
{
	//�����߼�������
	CGameLogic logic;

	//�ж���Ϸʱ��
	if (nTime <= 0)
	{
		//���ͼ
		m_graph.ClearGraph();
		return GAME_LOSE;
	}

	//�ж��Ƿ�ͼ�����е�Ϊ��
	if (logic.IsBlank(m_graph) == true)
	{
		//���ͼ
		m_graph.ClearGraph();
		return GAME_SUCCESS;
	}
	return GAME_PLAY;
}

//�ڵ�ͼ�в��ҿ���������һ����Ƭ����������·����·���ϵĶ�����
bool CGameControl::Help(Vertex avPath[MAX_VERTEX_NUM], int& nVexnum)
{
	CGameLogic logic;

	//�ж��Ƿ�Ϊ��
	if (logic.IsBlank(m_graph) == true)
	{
		return false;
	}

	//����һ����Ч����ʾ·��
	if (logic.SearchValidPath(m_graph))
	{
		//����·������
		nVexnum = logic.GetVexPath(avPath);
		return true;
	}
	return false;

}

//ʵ������
void CGameControl::Resert(void)
{
	//����ͼ�ж���
	CGameLogic logic;
	logic.ResertGraph(m_graph);
}