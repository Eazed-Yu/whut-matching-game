// CGameDlg.cpp : implementation file

#include "pch.h"
#include "LLK.h"
#include "CGameDlg.h"
#include "afxdialogex.h"
#include"CGameControl.h"
#include"CGameLogic.h"


// CGameDlg dialog

IMPLEMENT_DYNAMIC(CGameDlg, CDialogEx)

CGameDlg::CGameDlg(CWnd* pParent /*=nullptr*/): CDialogEx(IDD__GAME_DIALOG, pParent)
{
	//��ʼ����ʼ������
	m_ptGameTop.x = 50;
	m_ptGameTop.y = 50;

	//��ʼ��ͼƬԪ�ش�С
	m_sizeElem.cx = 40;
	m_sizeElem.cy = 40;

	//��ʼ��ͼ��ѡ��״̬
	m_bFirstPoint = true;

	//��ʼ����Ϸ��������
	m_rtGameRect.top = m_ptGameTop.y;
	m_rtGameRect.left = m_ptGameTop.x;
	m_rtGameRect.right = m_rtGameRect.left + m_sizeElem.cx * MAX_COL;
	m_rtGameRect.bottom = m_rtGameRect.top + m_sizeElem.cy * MAX_ROW;
}

CGameDlg::~CGameDlg()
{
}

void CGameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CGameDlg, CDialogEx)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BTN_START, &CGameDlg::OnClickedBtnStart)
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()

// CGameDlg message handlers

//��ʼ�����ڱ����ʹ�С
void CGameDlg::InitBackground()
{	
	//����BMP�ļ���Դ
	HANDLE hBmpBG = ::LoadImage(NULL, _T("theme\\picture\\fruit_bg.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	//��õ�ǰ�Ի������Ƶ����
	CClientDC dc(this);

	//��������Ƶ���ݼ��ݵ��ڴ�DC
	m_dcBG.CreateCompatibleDC(&dc);

	//��λͼ��Դѡ��DC
	m_dcBG.SelectObject(hBmpBG);

	//��ʼ���ڴ�DC
	m_dcMem.CreateCompatibleDC(&dc);
	CBitmap bmpMem;
	bmpMem.CreateCompatibleBitmap(&dc, 800, 600);
	m_dcMem.SelectObject(&bmpMem);

	//���Ʊ������ڴ�DC��
	m_dcMem.BitBlt(0, 0, 800, 600, &m_dcBG, 0, 0, SRCCOPY);

	//�������ڴ�С
	UpdateWindow();
}

//��ʼ���Ի���
BOOL CGameDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	//���öԻ���ͼ��
	m_icon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	SetIcon(m_icon, TRUE);    //���ô�ͼ��
	SetIcon(m_icon, FALSE);   //����Сͼ��

	//��ʼ������
	InitBackground();

	//��ʼ��Ԫ��
	InitElement();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}

void CGameDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: Add your message handler code here
					   // Do not call CDialogEx::OnPaint() for painting messages
					   // 
	//��λͼ�ڴ濽����Ƶ�ڴ�
	dc.BitBlt(0, 0, 800, 600, &m_dcMem, 0, 0, SRCCOPY);
}

//��ʼ��Ԫ��
void CGameDlg::InitElement()
{
	//����BMPͼƬ��Դ
	HANDLE hBmpBG = ::LoadImage(NULL, _T("theme\\picture\\fruit_element.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	//��ȡ��ǰ�Ի������Ƶ�ڴ�
	CClientDC dc(this);

	//��������Ƶ�ڴ���ݵ��ڴ�DC
	m_dcElement.CreateCompatibleDC(&dc);

	//��λͼ��Դѡ��DC
	m_dcElement.SelectObject(hBmpBG);

	//����BMPͼƬ��Դ
	HANDLE hMask = ::LoadImage(NULL, _T("theme\\picture\\fruit_mask.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	//��������Ƶ�ڴ���ݵ��ڴ�DC
	m_dcMask.CreateCompatibleDC(&dc);

	//��λͼ��Դѡ��DC
	m_dcMask.SelectObject(hMask);
}

//�������ڴ�С
void CGameDlg::UpdateWindow()
{
	//�������ڴ�С
	CRect rtWin;
	CRect rtClient;
	this->GetWindowRect(rtWin);   //��ô��ڴ�С
	this->GetWindowRect(rtClient);   //��ÿͻ�����С

	//����������߿�Ĵ�С
	int nSpanWidth = rtWin.Width() - rtClient.Width();
	int nSpanHeight = rtWin.Width() - rtClient.Width();

	//���ô��ڴ�С
	MoveWindow(0, 0, 800 + nSpanWidth, 600 + nSpanHeight);

	CenterWindow();
}

//���µ�ͼ
void CGameDlg::UpdateMap()
{
	//����ͼƬ�Ķ���������ͼƬ��С
	int nTop = m_ptGameTop.y;
	int nLeft = m_ptGameTop.x;
	int nElemW = m_sizeElem.cx;
	int nElemH = m_sizeElem.cy;

	m_dcMem.BitBlt(m_rtGameRect.left, m_rtGameRect.top, m_rtGameRect.Width(), m_rtGameRect.Height(),&m_dcBG, m_rtGameRect.left, m_rtGameRect.top, SRCCOPY);

	for (int i = 0; i < MAX_ROW; i++) {
		for (int j = 0; j < MAX_COL; j++) {
			int nElemVal = m_GameC.GetElement(i, j);
			if (nElemVal == BLANK) continue;
			
			//���������������룬�߱�����ͼ������Ϊ1
			m_dcMem.BitBlt(nLeft + j * nElemW, nTop + i * nElemH, nElemH, nElemW, &m_dcMask, 0, nElemVal * nElemH, SRCPAINT);
			
			//��Ԫ��ͼƬ��򣬱߱�����ͼƬ����ΪԪ��ͼƬ
			m_dcMem.BitBlt(nLeft + j * nElemW, nTop + i * nElemH, nElemH, nElemW, &m_dcElement, 0, nElemVal * nElemH, SRCAND);
		}
	}
	Invalidate(false);
}

//������ʾ��
void CGameDlg::DrawTipFrame(int nRow, int nCol)
{
	CClientDC dc(this);
	CBrush brush(RGB(233, 43, 43));
	CRect rtTipFrame;

	rtTipFrame.left = m_ptGameTop.x + nCol * m_sizeElem.cx;
	rtTipFrame.top = m_ptGameTop.y + nRow * m_sizeElem.cy;
	rtTipFrame.right = rtTipFrame.left + m_sizeElem.cx;
	rtTipFrame.bottom = rtTipFrame.top + m_sizeElem.cy;

	dc.FrameRect(rtTipFrame, &brush);
}

//������ʾ��
void CGameDlg::DrawTipLine(Vertex avPath[MAX_VERTEX_NUM], int nVexnum)
{
	//��ȡDC
	CClientDC dc(this);

	//���û���
	CPen penLine(PS_SOLID, 2, RGB(0, 255, 0));

	//������ѡ��DC
	CPen* pOldPen = dc.SelectObject(&penLine);

	dc.MoveTo(m_ptGameTop.x + avPath[0].col * m_sizeElem.cx + m_sizeElem.cx / 2,
		m_ptGameTop.y + avPath[0].row * m_sizeElem.cy + m_sizeElem.cy / 2);
	//����������
	for (int i = 0; i < nVexnum - 1; i++)
	{

		dc.LineTo(m_ptGameTop.x + avPath[i + 1].col * m_sizeElem.cx + m_sizeElem.cx / 2,
			m_ptGameTop.y + avPath[i + 1].row * m_sizeElem.cy + m_sizeElem.cy / 2);
	}

	dc.SelectObject(pOldPen);
}


/*
//������ʾ��
void CGameDlg::DrawTipLine(Vertex asvPath[4], int nVexnum)
{
	//��ȡDC
	CClientDC dc(this);
	//���û���
	CPen penLine(PS_SOLID, 2, RGB(0, 255, 0));
	//������ѡ��DC
	CPen* pOldPen = dc.SelectObject(&penLine);

	//����������
	dc.MoveTo(m_ptGameTop.x + asvPath[0].col * m_sizeElem.cx + m_sizeElem.cx / 2,m_ptGameTop.y + asvPath[0].row * m_sizeElem.cy + m_sizeElem.cy / 2);
	//����������
	for (int i = 0; i < nVexnum - 1; i++)
	{
		dc.LineTo(m_ptGameTop.x + asvPath[i + 1].col * m_sizeElem.cx + m_sizeElem.cx / 2,m_ptGameTop.y + asvPath[i + 1].row * m_sizeElem.cy + m_sizeElem.cy / 2);
	}
	dc.SelectObject(pOldPen);
}
*/
//��ʼ��Ϸ��ť
void CGameDlg::OnClickedBtnStart()
{
	//��ʼ����Ϸ��ͼ
	m_GameC.StartGame();
	//���½���
	UpdateMap();
	//���´���
	InvalidateRect(m_rtGameRect, false);
}

//��Ϸ��ͼ�¼���Ӧ
void CGameDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	//ȥ��С��0��״̬
	if (point.x < m_ptGameTop.x || point.y < m_ptGameTop.y)
	{
		return CDialogEx::OnLButtonUp(nFlags, point);
	}

	//�������������
	int nRow = (point.y - m_ptGameTop.y) / m_sizeElem.cy;
	int nCol = (point.x - m_ptGameTop.x) / m_sizeElem.cx;

	//�ж��������Ч��
	if (nRow > 3 || nCol > 3)
	{
		return CDialogEx::OnLButtonUp(nFlags, point);
	}

	
	if (m_bFirstPoint)   //��һ����
	{
		//������ʾ��
		DrawTipFrame(nRow, nCol);
		m_GameC.SetFirstPoint(nRow, nCol);
	}
	else {
		//������ʾ��
		DrawTipFrame(nRow, nCol);
		m_GameC.SetSecPoint(nRow, nCol);

		Vertex avPath[MAX_VERTEX_NUM];     //���·��   16Ϊ·��������ᵽ16��·���ģ�
		int nVexnum = 0;      //�������

		//�����ж�
		if (m_GameC.Link(avPath, nVexnum))
		{
			//����ʾ��
			DrawTipLine(avPath, nVexnum);
			//���µ�ͼ
			UpdateMap();
		}

		Sleep(200);
		InvalidateRect(m_rtGameRect, false);
	}
	m_bFirstPoint = !m_bFirstPoint;
}
