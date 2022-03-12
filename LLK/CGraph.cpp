#include "pch.h"
#include "CGraph.h"

//���캯��
CGraph::CGraph()
{
	InitGraph();   //��ʼ��ͼ
}

//ͼ�ṹ�ĳ�ʼ����-1��û��ͼƬ 0��û�й�ϵ
void CGraph::InitGraph()
{
	m_nArcnum = 0;
	m_nVexnum = 0;

	//��ʼ��������ߵ���Ϣ
	for (int i = 0; i < MAX_VERTEX_NUM; i++)
	{
		//��ʼ������
		m_Vertices[i] = -1;
		
		for (int j = 0; j < MAX_VERTEX_NUM; j++)
		{
			//��ʼ����
			m_AdjMatrix[i][j] = 0;
		}
	}
}