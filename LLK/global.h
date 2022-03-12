#pragma once

//���嶥��ṹ��
typedef struct tagVertex
{
	int row;   //��
	int col;   //��
	int info;   //��Ϣ��
}Vertex;

#define BLANK -1
#define MAX_VERTEX_NUM 120   //����ĸ���
#define MAX_ROW 10	  //��ʼ����
#define MAX_COL 12	  //��ʼ����
#define MAX_PIC_NUM 10 //ͼƬ��ɫ
#define REPEAT_NUM 12  //ÿ�ֻ�ɫͼƬ����
#define MAP_TOP 50   //��Ϸ��ͼ���Ͻ�������
#define MAP_LEFT 50   //��Ϸ��ͼ���ϽǺ�����
#define PIC_WIDTH 40  //��ϷͼƬ���
#define PIC_HEIGHT 40  //��ϷͼƬ�߶�

#define PLAY_TIMER_ID 1 //��ʱ���ı��

#define GAME_LOSE -1 //ʧ��
#define GAME_SUCCESS 0 //��ʤ
#define GAME_PLAY 1 //��Ϸ��������


 