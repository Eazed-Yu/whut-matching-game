#pragma once
//ͼ���ݽṹ��
class CGraph
{
public:
	CGraph();
protected:
#define MAX_VERTEX_NUM 16   //����Ԫ�صĸ���
    //�������������
	typedef int Vertices[MAX_VERTEX_NUM];
	//�ߵ���������
	typedef bool AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];

	Vertices m_Vertices;   //��������
	AdjMatrix m_AdjMatrix;   //��ϵ����
	int m_nVexnum;   //��������
	int m_nArcnum;   //�ߵ�����
public:
	void InitGraph(void);   //��ʼ��ͼ�Ķ���͹�ϵ
};

 