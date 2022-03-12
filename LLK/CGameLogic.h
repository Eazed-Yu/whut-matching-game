#pragma once
#include"global.h"
#include"CGraph.h"

class CGameLogic
{
public:
	CGameLogic::CGameLogic(void);   //���캯��

	void InitMap(CGraph& g);
	void Clear(CGraph& g, Vertex v1, Vertex v2);   //��V1��v2��ͨʱ�����䶥���ֵ��Ϊ��
	bool IsLink(CGraph& g, Vertex v1, Vertex v2);  //�ж϶���v1��v2�Ƿ���ͨ
	int GetVexPath(Vertex avPath[4]);   //ͨ����������·��
	void PushVertex(Vertex v);
	void PopVertex();

protected:
	Vertex m_avPath[4];   //�����ڽ��������ж�ʱ�������Ķ���
	int m_nVexNum;   //������

	void UpdateArc(CGraph& g, int nRow, int nCol);   //�ж���Ϸ��ͼ��nRow�У�nCol�еĶ��������������ҵĶ����Ƿ��бߣ�����бߣ������ͼ�ṹ��������
	void AddVertex(Vertex v);   //���һ��·������
	void DeleteVertex();   //ȡ��һ������

};

