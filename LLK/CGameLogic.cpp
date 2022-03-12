#include "pch.h"
#include "CGameLogic.h"
#include"CGameDlg.h"

//��ʼ����Ϸ��ͼ
void CGameLogic::InitMap(int anMap[][4])
{
	int anTemp[4][4] = { 2,0,1,3, 2,2,1,3,2,1,0,0,1,3,0,3 };
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			anMap[i][j] = anTemp[i][j];
		}
	}
}

//�ж��Ƿ�����
bool CGameLogic::IsLink(int anMap[][4], Vertex v1, Vertex v2)
{
	int nCol1 = v1.col;
	int nCol2 = v2.col;
	int nRow1 = v1.row;
	int nRow2 = v2.row;

	//һ��ֱ�ߺ�����ͨ
	if (nRow1 == nRow2)
	{
		if (LinkInRow(anMap, v1, v2) == true)
		{
			return true;
		}
	}

	//һ��ֱ��������ͨ
	if (nCol1 == nCol2)
	{
		if (LinkInCol(anMap, v1, v2))
		{
			return true;
		}
	}

	//����ֱ����ͨ
	if (OneCornerLink(anMap, v1, v2))
	{
		return true;
	}

	//����ֱ����ͨ
	if (TwoCornerLink(anMap, v1, v2))
	{
		return true;
	}
	return false;
}

//����
void CGameLogic::Clear(int anMap[][4], Vertex v1, Vertex v2)
{
	anMap[v1.row][v1.col] = BLANK;
	anMap[v2.row][v2.col] = BLANK;
}


//�к���ͬ���жϺ����Ƿ���ͨ
bool CGameLogic::LinkInRow(int anMap[][4], Vertex v1, Vertex v2)
{
	int nCol1 = v1.col;
	int nCol2 = v2.col;
	int nRow = v1.row;

	//ֱͨ
	for (int i = nCol1 + 1; i <= nCol2; i++)
	{
		if (i == nCol2)
			return true;
		if (anMap[nRow][i] != BLANK)
			break;
	}
	return false;
}

//�к���ͬ���ж������Ƿ���ͨ
bool CGameLogic::LinkInCol(int anMap[][4], Vertex v1, Vertex v2)
{
	int nRow1 = v1.row;
	int nRow2 = v2.row;
	int nCol = v1.col;

	for (int i = nRow1 + 1; i <= nRow2; i++)
	{
		if (i == nRow2)
			return true;
		if (anMap[i][nCol] != BLANK)
			break;
	}
	return false;
}

//�ж�ͬ�в�ͬ�е��������Ƿ���ͨ
bool CGameLogic::LineX(int anMap[][4], int nRow, int nCol1, int nCol2)
{
	//�жϣ�nRow,nCol1)��(nRow,nCol2)�ܷ���ͨ
	for (int nCol = nCol1; nCol <= nCol2; nCol++)
	{
		if (anMap[nRow][nCol] != BLANK)
			break;
		if (nCol == nCol2)
			return true;
	}
	return false;
}

//�ж�ͬ�в�ͬ�е��������ܹ���ͨ
bool CGameLogic::LineY(int anMap[][4], int nRow1, int nRow2, int nCol)
{
	//�ж�(nRow1,nCol)��(nRow2,nCol)�Ƿ���ͨ
	for (int nRow = nRow1; nRow <= nRow2; nRow++)
	{
		if (anMap[nRow][nCol] != BLANK)
			break;
		if (nRow == nRow2)
			return true;
	}
}

//�ж�һ���ս��Ƿ���ͨ
bool CGameLogic::OneCornerLink(int anMap[][4], Vertex v1, Vertex v2)
{
	int nCol1 = v1.col;
	int nCol2 = v2.col;
	int nRow1 = v1.row;
	int nRow2 = v2.row;

	if (nRow1 > nRow2)   //ȷ��nRow1<nRow2,��֤(nRow1,nCon1)ʼ����(nRow2,nCon2)���Ϸ�
	{
		int nTemp;
		nTemp = nRow1;
		nRow1 = nRow2;
		nRow2 = nTemp;

		nTemp = nCol1;
		nCol1 = nCol2;
		nCol2 = nTemp;
	}

	if (nCol2 < nCol1)
	{
		//�ж�(nRow+1,nCon1)��(nRow2,nCol2+1)�ܷ���ͨ(���º���)
		if (LineY(anMap, nRow1 + 1, nRow2, nCol1) && LineX(anMap, nRow2, nCol2 + 1, nCol1))
		{
			return true;
		}
		//�ж�(nRow2-1,nCon2)��(nRow1,nCol1-1)�ܷ���ͨ(���Ϻ���)
		if (LineY(anMap, nRow2 - 1, nRow1, nCol2) && LineX(anMap, nRow1, nCol2, nCol1 - 1))
		{
			return true;
		}
	}
	else
	{
		//�ж�(nRow1+1,nCon1)��(nRow2,nCol2-1�ܷ���ͨ(���º���)
		if (LineY(anMap, nRow1 + 1, nRow2, nCol1) && LineX(anMap, nRow2, nCol1, nCol2 - 1))
		{
			return true;
		}
		//�ж�(nRow2-1,nCon2)��(nRow1,nCol1+1)�ܷ���ͨ(���Ϻ���)
		if (LineY(anMap, nRow2 - 1, nRow1, nCol2) && LineX(anMap, nRow1, nCol2, nCol1 + 1))
		{
			return true;
		}
	}
	return false;
}

//�ж������ս��ܷ���ͨ
bool CGameLogic::TwoCornerLink(int anMap[][4], Vertex v1, Vertex v2)
{
	int nCol1 = v1.col;
	int nCol2 = v2.col;
	int nRow1 = v1.row;
	int nRow2 = v2.row;

	if (nRow1 > nRow2)   //ȷ��nRow1<nRow2,��֤(nRow1,nCon1)ʼ����(nRow2,nCon2)���Ϸ�
	{
		int nTemp;
		nTemp = nRow1;
		nRow1 = nRow2;
		nRow2 = nTemp;

		nTemp = nCol1;
		nCol1 = nCol2;
		nCol2 = nTemp;
	}

	if (nCol2 < nCol1)
	{
		//�ҵ�һ����Y��ƽ�е���ֱͨ�߶�
		for (int nCol = 0; nCol < 4; nCol++)
		{
			if (anMap[nRow1][nCol] == BLANK && anMap[nRow2][nCol] == BLANK)
			{
				//�жϸ���y��ֱ���Ƿ���ͨ
				if (LineY(anMap, nRow1, nRow2, nCol))
				{
					if (nCol2 > nCol && LineX(anMap, nRow1, nCol - 1, nCol) && LineX(anMap, nRow2, nCol, nCol2 - 1))
					{
						return true;
					}
					//��ͨ��ֱ����ѡ�е���������м�
					if (nCol1 > nCol && nCol > nCol2 && LineX(anMap, nRow1, nCol, nCol1 - 1) && LineX(anMap, nRow2, nCol2 + 1, nCol))
					{
						return true;
					}
					//��ͨ��ֱ����ѡ�е���������ұ�
					if (nCol > nCol1 && LineX(anMap, nRow1, nCol1 + 1, nCol) && LineX(anMap, nRow2, nCol, nCol2 + 1))
					{
						return true;
					}
				}
			}
		}
	
		//�ҵ�һ����X��ƽ�е���ֱͨ�߶�
		for (int nRow = 0; nRow < 4; nRow++)
		{
			if (anMap[nRow][nCol1] == BLANK && anMap[nRow][nCol2] == BLANK)
			{
				if (LineX(anMap, nRow, nCol1, nCol2)) //�жϸ���Y��ֱ���Ƿ���ͨ
				{
					//��ͨ��ֱ����ѡ�е������������
					if (nRow1 > nRow && LineY(anMap, nRow1 - 1, nRow, nCol1) && LineY(anMap, nRow, nRow2 - 1, nCol2))
					{
						return true;
					}
					//��ͨ��ֱ����ѡ�е���������м�
					if (nRow2 > nRow && nRow > nRow1 && LineY(anMap, nRow1 + 1, nRow, nCol1) && LineY(anMap, nRow, nRow2 - 1, nCol2))
					{
						return true;
					}
					//��ͨ��ֱ����ѡ�е������������
					if (nRow > nRow2 && LineY(anMap, nRow1 + 1, nRow, nCol1) && LineY(anMap, nRow, nRow2 + 1, nCol2))
					{
						return true;
					}
				}
			}
		}
	}
	else
	{
		//�ҵ�һ����Y��ƽ�е���ֱͨ�߶�
		for (int nCol = 0; nCol < 4; nCol++)
		{
			if (anMap[nRow1][nCol] == BLANK && anMap[nRow2][nCol] == BLANK)
			{
				if (LineY(anMap, nRow1, nRow2, nCol)) //�жϸ���Y��ֱ���Ƿ���ͨ
				{
					//��ͨ��ֱ����ѡ�е��������
					if (nCol1 > nCol && LineX(anMap, nRow1, nCol1 - 1, nCol) && LineX(anMap, nRow2, nCol, nCol2 - 1))
					{
						return true;
					}
					//��ͨ��ֱ����ѡ�е�������֮��
					if (nCol2 > nCol && nCol > nCol1 && LineX(anMap, nRow1, nCol1 + 1, nCol) && LineX(anMap, nRow2, nCol, nCol2 - 1))
					{
						return true;
					}
					//��ͨ��ֱ����ѡ�е��������ұ�
					if (nCol > nCol2 && LineX(anMap, nRow1, nCol1 + 1, nCol) && LineX(anMap, nRow2, nCol, nCol2 + 1))
					{
						return true;
					}
				}
			}
		}

		//�ҵ�һ����X��ƽ�е���ֱͨ�߶�
		for (int nRow = 0; nRow < 4; nRow++)
		{
			if (anMap[nRow][nCol1] == BLANK && anMap[nRow][nCol2] == BLANK)
			{
				if (LineX(anMap, nRow, nCol1, nCol2)) //�жϸ���Y��ֱ���Ƿ���ͨ
				{
					//��ֱͨ��������������
					if (nRow1 > nRow && LineY(anMap, nRow1 - 1, nRow, nCol1) && LineY(anMap, nRow, nRow2 - 1, nCol2))
					{
						return true;
					}
					//��ֱͨ����������֮��
					if (nRow2 > nRow && nRow > nRow1 && LineY(anMap, nRow1 + 1, nRow, nCol1) && LineY(anMap, nRow, nRow2 - 1, nCol2))
					{
						return true;
					}
					//��ֱͨ��������������
					if (nRow > nRow2 && LineY(anMap, nRow1 + 1, nRow, nCol1) && LineY(anMap, nRow, nRow2 + 1, nCol2))
					{
						return true;
					}
				}
			}
		}
	}
	return false;
}