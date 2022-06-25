// CHelpDialog.cpp : implementation file
//

#include "pch.h"
#include "LLK.h"
#include "CHelpDialog.h"
#include "afxdialogex.h"


// CHelpDialog dialog

IMPLEMENT_DYNAMIC(CHelpDialog, CDialogEx)

CHelpDialog::CHelpDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_HELP, pParent)
{

}

CHelpDialog::~CHelpDialog()
{
}

void CHelpDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SCROLLBAR_HELP, m_ScrollBar);
}


BEGIN_MESSAGE_MAP(CHelpDialog, CDialogEx)
	ON_WM_PAINT()
	ON_WM_VSCROLL()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CHelpDialog message handlers

//��ʼ���Ի���
BOOL CHelpDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	//���öԻ���ͼ��
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	SetIcon(m_hIcon, TRUE);    //���ô�ͼ��
	SetIcon(m_hIcon, FALSE);   //����Сͼ��

	GetClientRect(&m_rtHelp);   //��ȡ�Ի����С
	InitHelpPicture();//���ذ���ͼƬ
	InitSrcollBar();//���ع�����

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}

//���ƽ���
void CHelpDialog::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: Add your message handler code here
					   // Do not call CDialogEx::OnPaint() for painting messages
	//����ͼƬ
	dc.BitBlt(0, 0, m_rtHelp.Width(), m_rtHelp.Height(), &m_dcMem, 0, 0, SRCCOPY);
}

//��Ӧ�������Ĳ���
void CHelpDialog::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	int pos = m_ScrollBar.GetScrollPos();

	switch (nSBCode)
	{
	case SB_LINEUP:
		pos--;
		break;
	case SB_LINEDOWN:
		pos++;
		break;
	case SB_PAGEUP:
		pos -= m_rtHelp.bottom - m_rtHelp.top;
		break;
	case SB_PAGEDOWN:
		pos += m_rtHelp.bottom - m_rtHelp.top;
		break;
	case SB_TOP:
		pos = 0;
		break;
	case SB_BOTTOM:
		pos = bmpMes.bmHeight - m_rtHelp.bottom + m_rtHelp.top;
		break;
	case SB_THUMBTRACK:
		pos = nPos;
		break;
	case SB_THUMBPOSITION:
		pos = nPos;
		break;
	default:
		break;
	}

	//���û���λ��
	m_ScrollBar.SetScrollPos(pos);
	//�ػ�ͼƬ
	UpdateHelp();

	CDialogEx::OnVScroll(nSBCode, nPos, pScrollBar);
}

//���߹�������λ�ø��°���ͼƬ��ʾ
void CHelpDialog::UpdateHelp()
{
	//��ǰ������λ��
	int nScrollPos = m_ScrollBar.GetScrollPos();
	
	//���ػ������Ƴɰ�ɫ
	m_dcMem.BitBlt(m_rtHelp.left, m_rtHelp.top, m_rtHelp.Width(), m_rtHelp.Height(), NULL, 0, 0, WHITENESS);
	//��ȡͼƬ���л���
	m_dcMem.BitBlt(0, 0, m_rtHelp.Width(), m_rtHelp.Height(), &m_dcHelp, 0, nScrollPos, SRCCOPY);
	//���½���
	InvalidateRect(m_rtHelp, FALSE);
}

//��ʼ������ͼƬ
void CHelpDialog::InitHelpPicture()
{
	HANDLE helpBmp;

	//����ͼƬ��Դ
	helpBmp = ::LoadImage(NULL, _T("res\\basic_help.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	//��ȡ��ǰ�豸����
	CClientDC dc(this);
	//��������DC
	m_dcHelp.CreateCompatibleDC(&dc);
	m_dcMem.CreateCompatibleDC(&dc);
	//��λͼ��Դѡ���豸����
	m_dcHelp.SelectObject(helpBmp);
	//��ȡλͼ��Ϣ
	GetObject(helpBmp, sizeof(BITMAP), &bmpMes);

	//��ʼ�������ڴ�
	CBitmap bmpMem;
	bmpMem.CreateDiscardableBitmap(&dc, m_rtHelp.Width(), m_rtHelp.Height());
	m_dcMem.SelectObject(&bmpMem);

	//���ư�ɫ����
	m_dcMem.BitBlt(0, 0, m_rtHelp.Width(), m_rtHelp.Height(), NULL, 0, 0, WHITENESS);
	//���ư���ͼƬ��������
	m_dcMem.BitBlt(0, 0, m_rtHelp.Width(), m_rtHelp.Height(), &m_dcHelp, 0, 0, SRCCOPY);
}

//��ʼ��������
void CHelpDialog::InitSrcollBar()
{
	m_ScrollBar.SetScrollRange(0, bmpMes.bmHeight - m_rtHelp.bottom + m_rtHelp.top);
	m_ScrollBar.SetScrollPos(0);
}

//�����Ȩ��Ϣ���������л�ɫ�ı�������Ϣ��Ӧ����
HBRUSH CHelpDialog::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  Change any attributes of the DC here
	
	// TODO:  Return a different brush if the default is not desired
	return hbr;
}