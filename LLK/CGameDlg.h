#pragma once


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
	CPoint m_ptSelFirst;   //��һ��ѡ�еĵ�(x��ʾ��)
	CPoint m_ptSelSec;     //�ڶ���ѡ�еĵ�
	CRect m_rtGameRect;

	int m_anMap[4][4];   //��Ϸ��ͼ
	bool m_bFirstPoint;   //ѡ�е�ͼƬ�ǲ��ǵ�һ��ѡ�У�Ĭ��Ϊ��

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();    //��ʼ���Ի���
	void InitBackground();          //��ʼ������
	void InitElement();             //��ʼ��Ԫ��
	void DrawTipFrame(int nRow, int nCol);   //������ʾ��
	void UpdateWindow();            //�������ڴ�С
	void UpdateMap();               //������Ϸ��ͼ
	bool IsLink(void);              //�ж��Ƿ��һ��ѡ��ͼƬ
	void DrawTipLine();             //����ʾ��

	afx_msg void OnPaint();
	afx_msg void OnClickedBtnStart();      //��ʼ��Ϸ��ť
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);    //��Ϸ��ͼ��������¼�
	
};
