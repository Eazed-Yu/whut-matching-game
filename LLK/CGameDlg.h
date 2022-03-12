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
	CDC m_dcCache;     //������ڴ�DC

	CPoint m_ptGameTop;   //��Ϸ��ʼ����
	CSize m_sizeElem;     //ͼƬԪ�ش�С
	CRect m_rtGameRect;   //��Ϸ�����С

	bool m_bFirstPoint;   //ѡ�е�ͼƬ�ǲ��ǵ�һ��ѡ�У�Ĭ��Ϊ��
	bool m_bPlaying;   //��ʾ��Ϸ�Ƿ����ڽ���
	bool m_bPause;   //��Ϸ��ͣ���
	int timeCount;    //��ʱ

	CGameControl m_GameC;    //��Ϸ������


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	DECLARE_MESSAGE_MAP()

public:
	void InitBackground();          //��ʼ������
	void InitElement();             //��ʼ��Ԫ��
	void UpdateWindow();            //�������ڴ�С
	void UpdateMap();               //������Ϸ��ͼ
	void DrawTipFrame(int nRow, int nCol);   //������ʾ��
	void DrawTipLine(Vertex asvPath[MAX_VERTEX_NUM], int nVexnum);             //����ʾ��
	void JudgeWin(void);   //�ж�ʤ��
	
	CProgressCtrl m_GameProgress;
	virtual BOOL OnInitDialog();    //��ʼ���Ի���
	afx_msg void OnPaint();
	afx_msg void OnClickedBtnStart();      //��ʼ��Ϸ��ť
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);    //��Ϸ��ͼ��������¼�
	afx_msg void OnBnClickedBtnNotice();
	afx_msg void OnBnClickedBtnReset();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedBtnPause();
	afx_msg void OnChangeEditTime();
	afx_msg void OnBnClickedBtnHelp();
};
