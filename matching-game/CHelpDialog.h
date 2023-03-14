#pragma once

// CHelpDialog dialog

class CHelpDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CHelpDialog)

public:
	CHelpDialog(CWnd *pParent = nullptr); // standard constructor
	virtual ~CHelpDialog();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum
	{
		IDD = IDD_DIALOG_HELP
	};
#endif

protected:
	virtual void DoDataExchange(CDataExchange *pDX); // DDX/DDV support

	DECLARE_MESSAGE_MAP()

protected:
	HICON m_hIcon;	// �Ի���ͼ��
	CDC m_dcHelp;	// ����ͼƬDC
	CDC m_dcMem;	// �ڴ�DC
	CRect m_rtHelp; // ����ͼƬ��ʾ����
	BITMAP bmpMes;	// ͼƬ��Ϣ

public:
	virtual BOOL OnInitDialog();											 // ��ʼ���Ի���
	afx_msg void OnPaint();													 // ���ƽ���
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar); // ��Ӧ�������Ĳ���
	afx_msg HBRUSH OnCtlColor(CDC *pDC, CWnd *pWnd, UINT nCtlColor);		 // ��Ϣ��Ӧ����
	CScrollBar m_ScrollBar;
	void UpdateHelp();		// ���ݹ�������λ�ã����ð���ͼƬ��ʾ������
	void InitHelpPicture(); // ���ذ���ͼƬ
	void InitSrcollBar();	// ��ʼ��������
};
