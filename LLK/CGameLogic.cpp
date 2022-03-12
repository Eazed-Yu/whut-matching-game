#include "pch.h"
#include "CGameLogic.h"
#include"CGameDlg.h"

CGameLogic::CGameLogic(void)
{
	m_nVexNum = 0;
}

//��ʼ����Ϸ��ͼ
void CGameLogic::InitMap(CGraph &g)
{
	int anTemp[4][4] = { 2,0,1,3, 2,2,1,3,2,1,0,0,1,3,0,3 };
	
	//��ʼ������
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			g.AddVertex(anTemp[i][j]);
		}
	}

	//��ʼ����
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			UpdateArc(g, i, j);
		}
	}
}

//�ж��Ƿ�����
bool CGameLogic::IsLink(CGraph& g, Vertex v1, Vertex v2)
{
	return false;
}

//����
void CGameLogic::Clear(CGraph &g, Vertex v1, Vertex v2)
{

}

int CGameLogic::GetVexPath(Vertex avPath[4])
{
	for (int i = 0; i < m_nVexNum; i++)
	{
		avPath[i] = m_avPath[i];
	}
	return m_nVexNum;
}

void CGameLogic::AddVertex(Vertex v)
{
	m_avPath[m_nVexNum] = v;
	m_nVexNum++;
}

void CGameLogic::DeleteVertex()
{
	m_nVexNum--;
}

//����ͼ������
void CGameLogic::UpdateArc(CGraph& g, int nRow, int nCol)
{
	int nV1Index = nRow * 4 + nCol;

	if (nCol > 0)
	{
		int nV2Index = nV1Index - 1;
		//�ж���������ڵ��Ƿ��й�ϵ
		int nV1Info = g.GetVertex(nV1Index);
		int nV2Info = g.GetVertex(nV2Index);

		//�ж���������ڵ��Ƿ��й�ϵ
		if (nV1Info == nV2Info || nV1Info == BLANK || nV2Info == BLANK)
		{
			g.AddArc(nV1Index, nV2Index);
		}
	}
	if (nCol < 3)
	{
		int nV2Index = nV1Index + 1;
		//�ж����ұ����ڵ��Ƿ��й�ϵ
		int nV1Info = g.GetVertex(nV1Index);
		int nV2Info = g.GetVertex(nV2Index);

		//�ж����ұ����ڵ��Ƿ��й�ϵ
		if (nV1Info == nV2Info || nV1Info == BLANK || nV2Info == BLANK)
		{
			g.AddArc(nV1Index, nV2Index);
		}
	}
	if (nRow > 0)
	{
		int nV2Index = nV1Index - 4;
		//�ж������Ϸ����Ƿ��й�ϵ
		int nV1Info = g.GetVertex(nV1Index);
		int nV2Info = g.GetVertex(nV2Index);

		//�ж������Ϸ����Ƿ��й�ϵ
		if (nV1Info == nV2Info || nV1Info == BLANK || nV2Info == BLANK)
		{
			g.AddArc(nV1Index, nV2Index);
		}
	}
	if (nRow < 3)
	{
		int nV2Index = nV1Index + 4;
		//�ж������·����Ƿ��й�ϵ
		int nV1Info = g.GetVertex(nV1Index);
		int nV2Info = g.GetVertex(nV2Index);

		//�ж������·����Ƿ��й�ϵ
		if (nV1Info == nV2Info || nV1Info == BLANK || nV2Info == BLANK)
		{
			g.AddArc(nV1Index, nV2Index);
		}
	}
}