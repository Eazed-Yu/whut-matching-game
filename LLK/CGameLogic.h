#pragma once
#include"global.h"

class CGameLogic
{
public:
	void InitMap(int anMap[][4]);
	bool IsLink(int anMap[][4], Vertex v1, Vertex v2);  //�ж϶���v1��v2�Ƿ���ͨ
	void Clear(int anMap[][4], Vertex v1, Vertex v2);   //��V1��v2��ͨʱ�����䶥���ֵ��Ϊ��
	bool LinkInRow(int anMap[][4], Vertex v1, Vertex v2);   //�к���ͬ���жϺ����Ƿ���ͨ
	bool LinkInCol(int anMap[][4], Vertex v1, Vertex v2);
	bool LineX(int anMap[][4], int nRow, int nCol1, int nCol2);
	bool LineY(int anMap[][4], int nRow1, int nRow2, int nCol);
	bool OneCornerLink(int anMap[][4], Vertex v1, Vertex v2);
	bool TwoCornerLink(int anMap[][4], Vertex v1, Vertex v2);
	CGameLogic::CGameLogic(void);   //���캯��
	int GetVexPath(Vertex avPath[4]);   //ͨ����������·��
protected:
	Vertex m_avPath[4];   //�����ڽ��������ж�ʱ�������Ķ���
	int m_nVexNum;   //������

	void AddVertex(Vertex v);   //���һ��·������
	void DeleteVertex();   //ȡ��һ������

};

