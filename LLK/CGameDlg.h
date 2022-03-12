#pragma once
#include"global.h"
#include"CGameControl.h"

// CGameDlg dialog

class CGameDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CGameDlg)

public:
	CGameDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CGameDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD__GAME_DIALOG };
#endif

protected:
	HICON m_icon;
	CDC m_dcMem;        //�ڴ�DC
	CDC m_dcElement;    //Ԫ���ڴ�DC
	CDC m_dcMask;      //�����ڴ�DC
	CDC m_dcBG;        //����DC

	CPoint m_ptGameTop;   //��Ϸ��ʼ����
	CSize m_sizeElem;     //ͼƬԪ�ش�С
	CRect m_rtGameRect;

	CGameControl m_GameC;

	bool m_bFirstPoint;   //ѡ�е�ͼƬ�ǲ��ǵ�һ��ѡ�У�Ĭ��Ϊ��

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	DECLARE_MESSAGE_MAP()
public:
	void InitBackground();          //��ʼ������
	void InitElement();             //��ʼ��Ԫ��
	void DrawTipFrame(int nRow, int nCol);   //������ʾ��
	void UpdateWindow();            //�������ڴ�С
	void UpdateMap();               //������Ϸ��ͼ
	void DrawTipLine(Vertex asvPath[4], int nVexnum);             //����ʾ��

	virtual BOOL OnInitDialog();    //��ʼ���Ի���

	afx_msg void OnPaint();
	afx_msg void OnClickedBtnStart();      //��ʼ��Ϸ��ť
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);    //��Ϸ��ͼ��������¼�
};
