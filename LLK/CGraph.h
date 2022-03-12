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

	void InitGraph(void);   //��ʼ��ͼ�Ķ���͹�ϵ
public:
	int AddVertex(int nInfo);   //������info���뵽����������
	int GetVertex(int ninfo);   //��ȡ��i��������������ΪnIndex�Ķ���
	void AddArc(int nV1Index, int nV2Index);  //���nV1Index��nV2Index�Ĺ�ϵ
	void UpdateVertex(int nIndex, int Info);   //��ͼ����������������ΪnIndex�Ķ����ֵ����Ϊinfo 
	bool GetArc(int nV1Index, int nV2Index);   //�����������Ļ���Ϣ
	int GetVexnum(void);   //��ȡ���������еĶ�����
};

 