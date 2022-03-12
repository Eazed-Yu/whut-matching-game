#include "pch.h"
#include "CGameControl.h"

//��ʼ��Ϸ
void CGameControl::StartGame(void)
{
	CGameLogic gameLogic;
	gameLogic.InitMap(m_anMap);
}

//����Ԫ����Ϣ
int CGameControl::GetElement(int nRow, int nCol)
{
	return m_anMap[nRow][nCol];
}

//���õ�һ����
void CGameControl::SetFirstPoint(int nRow, int nCol)
{
	m_svSelFirst.row = nRow;
	m_svSelFirst.col = nCol;
}

//���õڶ�����
void CGameControl::SetSecPoint(int nRow, int nCol)
{
	m_svSelSec.row = nRow;
	m_svSelSec.col = nCol;
}

//����
bool CGameControl::Link(Vertex avPath[2])
{
	//�ж�����ѡ�е��Ƿ���ͬһ����
	if (m_svSelFirst.row == m_svSelSec.row && m_svSelFirst.col == m_svSelSec.col)
	{
		return false;
	}

	//�ж�����ѡ���ͼƬ�Ƿ���ͬͼƬ
	if (m_anMap[m_svSelFirst.row][m_svSelFirst.col] != m_anMap[m_svSelSec.row][m_svSelSec.col])
	{
		return false;
	}

	//�ж��Ƿ���ͨ
	CGameLogic logic;
	if (logic.IsLink(m_anMap, m_svSelFirst, m_svSelSec))
	{
		//����
		logic.Clear(m_anMap, m_svSelFirst, m_svSelSec);

		//����·������
		avPath[0] = m_svSelFirst;
		avPath[1] = m_svSelSec;
		return true;
	} 
	return false;
}