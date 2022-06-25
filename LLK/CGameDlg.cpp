// CGameDlg.cpp : implementation file

#include "pch.h"
#include "LLK.h"
#include "CGameDlg.h"
#include "afxdialogex.h"
#include"CGameControl.h"
#include"CGameLogic.h"
#include"CHelpDialog.h"
#include"CVersionDlg.h"
#include"CSettingDialog.h"

// CGameDlg dialog

IMPLEMENT_DYNAMIC(CGameDlg, CDialogEx)

CGameDlg::CGameDlg(CWnd* pParent /*=nullptr*/): CDialogEx(IDD__GAME_DIALOG, pParent)
{
	//��ʼ����ʼ������
	m_ptGameTop.x = MAP_LEFT;
	m_ptGameTop.y = MAP_TOP;

	//��ʼ��ͼƬԪ�ش�С
	m_sizeElem.cx = PIC_WIDTH;
	m_sizeElem.cy = PIC_HEIGHT;

	//��ʼ��ͼ��ѡ��״̬
	m_bFirstPoint = true;
	m_bPlaying = false;

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
	DDX_Control(pDX, IDC_GAME_TIME, m_GameProgress);
}

BEGIN_MESSAGE_MAP(CGameDlg, CDialogEx)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BTN_START, &CGameDlg::OnClickedBtnStart)
	ON_WM_LBUTTONUP()
	ON_BN_CLICKED(IDC_BTN_NOTICE, &CGameDlg::OnBnClickedBtnNotice)
	ON_BN_CLICKED(IDC_BTN_RESET, &CGameDlg::OnBnClickedBtnReset)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BTN_PAUSE, &CGameDlg::OnBnClickedBtnPause)
	ON_BN_CLICKED(IDC_BTN_HELP, &CGameDlg::OnBnClickedBtnHelp)
	ON_BN_CLICKED(IDC_BTN_ABOUT, &CGameDlg::OnBnClickedBtnAbout)
	ON_BN_CLICKED(IDC_BTN_SETTING, &CGameDlg::OnBnClickedBtnSetting)
	ON_BN_CLICKED(IDC_BTN_GAMEOVER, &CGameDlg::OnBnClickedBtnGameover)
END_MESSAGE_MAP()

//��ʼ�����ڱ����ʹ�С
void CGameDlg::InitBackground()
{	
	//����BMP�ļ���Դ
	HANDLE hBmpBG = ::LoadImage(NULL, _T("res\\fruit_bg.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
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

	//���ý��������غ�ʣ��ʱ��ؼ�
	this->GetDlgItem(IDC_GAME_TIME)->ShowWindow(FALSE);
	this->GetDlgItem(IDC_EDIT_TIME)->ShowWindow(FALSE);

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
	//��ȡ��ǰ�Ի������Ƶ�ڴ�
	CClientDC dc(this);

	//����BMPͼƬ��Դ
	HANDLE hBmpBG = ::LoadImage(NULL, _T("res\\fruit_element.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	//��������Ƶ�ڴ���ݵ��ڴ�DC
	m_dcElement.CreateCompatibleDC(&dc);

	//��λͼ��Դѡ��DC
	m_dcElement.SelectObject(hBmpBG);

	//����BMPͼƬ��Դ
	HANDLE hMask = ::LoadImage(NULL, _T("res\\fruit_mask.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	//��������Ƶ�ڴ���ݵ��ڴ�DC
	m_dcMask.CreateCompatibleDC(&dc);

	//��λͼ��Դѡ��DC
	m_dcMask.SelectObject(hMask);

	//������Ϸ��ͣBMPͼƬ��Դ
	HANDLE hCache = ::LoadImage(NULL, _T("res\\fruit_pause.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	//��������Ƶ�ڴ���ݵ��ڴ�DC
	m_dcCache.CreateCompatibleDC(&dc);

	//��λͼ��Դѡ��DC
	m_dcCache.SelectObject(hCache);
}

//��ʼ��Ϸ��ť
void CGameDlg::OnClickedBtnStart()
{
	//��ͣʱ����Ӧ
	if (m_bPause == true)
	{
		return;
	}

	//��ʼ����Ϸ��ͼ
	m_GameC.StartGame();

	//��ʼʱ����300
	timeCount = 300;

	//�Ƿ���Ϸ��ʶ��Ϊtrue
	m_bPlaying = true;
	//��ֹ�������
	this->GetDlgItem(IDC_BTN_START)->EnableWindow(FALSE);

	//��ʼ��������
	m_GameProgress.SetRange(0, 300);   //��ʼ��Χ
	m_GameProgress.SetStep(-1);           //��ʼ����ֵ
	m_GameProgress.SetPos(300);        //���ó�ʼֵ

	//������ʱ��
	this->SetTimer(PLAY_TIMER_ID, 1000, NULL);
	
	//���½���
	UpdateMap();
	//���´���
	InvalidateRect(m_rtGameRect, false);

	//���ý��������غ�ʣ��ʱ��ؼ�
	this->GetDlgItem(IDC_GAME_TIME)->ShowWindow(TRUE);
	this->GetDlgItem(IDC_EDIT_TIME)->ShowWindow(TRUE);
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
	if (nRow > MAX_ROW - 1 || nCol > MAX_COL - 1)
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

		//�ж�ʤ��
		JudgeWin();
	}
	m_bFirstPoint = !m_bFirstPoint;

	CDialogEx::OnLButtonUp(nFlags, point);
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

//��ʾ��ťʱ����Ӧ
void CGameDlg::OnBnClickedBtnNotice()
{
	//���û�н�����Ϸ����Ż�
	if (m_bPlaying == false)
	{
		return;
	}

	//����ܹ���ͨ��������ʾ��������߲�������Ϸ��ͼ
	Vertex avPath[MAX_VERTEX_NUM];   //���·��
	int nVexnum = 0;   //�������

	if (m_GameC.Help(avPath, nVexnum))
	{
		//����һ�������ʾ��
		DrawTipFrame(avPath[0].row, avPath[0].col);
		DrawTipFrame(avPath[nVexnum - 1].row, avPath[nVexnum - 1].col); 

		//����ʾ��
		DrawTipLine(avPath, nVexnum);

		//Ϊ��ʹ�ڶ�����ʾ����Կ�������ͣ200ms����ˢ��ҳ��
		Sleep(1000);   

		UpdateMap();  //���µ�ͼ

		//�ֲ����θ���
		InvalidateRect(m_rtGameRect, FALSE);
	}

}

//���Ű�ť
void CGameDlg::OnBnClickedBtnReset()
{
	//����ResertGraph()
	m_GameC.Resert();

	//���µ�ͼ������UpdateMap(),���½�����ʾ
	UpdateMap();

	//֪ͨ�����ػ�
	InvalidateRect(m_rtGameRect, FALSE);   //�ֲ����θ���

}

//��ʱ��
void CGameDlg::OnTimer(UINT_PTR nIDEvent)
{
	//���ý�����λ��֮ǰ����Ҫ�жϼ�ʱ������Ƿ�Ϊ��ǰ��ʱ��
	if (nIDEvent == PLAY_TIMER_ID && m_bPlaying && m_bPause == false)
	{
		//��Ϸʱ���һ��
		if (timeCount > 0)
		{
			CString str;
			str.Format(_T("%d"), timeCount);
			timeCount--;
			SetDlgItemText(IDC_EDIT_TIME, str);

			UpdateData(false);

			//ˢ�½�����λ��
			m_GameProgress.StepIt();
		}
	 }

	//�ж�ʤ��
	JudgeWin();
	CDialogEx::OnTimer(nIDEvent);
}

//�ж�ʤ��
void CGameDlg::JudgeWin()
{
	//��Ϸʤ���ж�
	BOOL bGameStatus = m_GameC.IsWin(m_GameProgress.GetPos());

	//�ж��Ƿ������Ϸ
	if (bGameStatus == GAME_PLAY)
	{
		return;
	}
	else
	{
		//����Ϸ��ʾ��Ϊfalse
		m_bPlaying = false;

		//�رն�ʱ��
		KillTimer(PLAY_TIMER_ID);

		//��ʾ��ʤ
		CString  strTitle;
		
		this->GetWindowTextW(strTitle);

		if (bGameStatus == GAME_SUCCESS)
		{
			MessageBox(_T("Congratulation!"), strTitle);
		}
		else if (bGameStatus == GAME_LOSE)
		{
			MessageBox(_T("Time Out!\nGame Over!"), strTitle);
		}

		//��ԭ��Ϸ��ť�ɵ��
		this->GetDlgItem(IDC_BTN_START)->EnableWindow(TRUE);
	}
}

//��Ϸ��ͣ��ťʱ����Ӧ
void CGameDlg::OnBnClickedBtnPause()
{
	//��õ�ǰ�Ի������Ƶ����
	CClientDC dc(this);

	//��Ϸδ���ڽ��У�ֱ�ӷ���
	if (m_bPlaying == false)
	{
		return;
	}

	//�����Ϸ������ͣ״̬
	if (m_bPause == false)
	{
		//���Ʊ������ڴ�DC��
		m_dcMem.BitBlt(MAP_LEFT, MAP_TOP, 640, 400, &m_dcCache, 0, 0, SRCCOPY);

		GetDlgItem(IDC_BTN_NOTICE)->EnableWindow(false);
		GetDlgItem(IDC_BTN_RESET)->EnableWindow(false);
		InvalidateRect(m_rtGameRect, false);   //���½���
		this->GetDlgItem(IDC_BTN_PAUSE)->SetWindowTextW(_T("������Ϸ"));
	}

	//�����Ϸ��ͣ
	if (m_bPause == true)
	{
		UpdateMap();
		GetDlgItem(IDC_BTN_NOTICE)->EnableWindow(1);
		GetDlgItem(IDC_BTN_RESET)->EnableWindow(1);
		InvalidateRect(m_rtGameRect, FALSE);    //�ֲ����θ���

		this->GetDlgItem(IDC_BTN_PAUSE)->SetWindowTextW(_T("��ͣ��Ϸ"));
	}
	m_bPause = !m_bPause;
}

void CGameDlg::OnChangeEditTime()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}

//������ť
void CGameDlg::OnBnClickedBtnHelp()
{
	// TODO: Add your control notification handler code here
	CHelpDialog chd;
	chd.DoModal();
}


void CGameDlg::OnBnClickedBtnAbout()
{
	// TODO: Add your control notification handler code here
	CVersionDlg cvd;
	cvd.DoModal();
}


void CGameDlg::OnBnClickedBtnSetting()
{
	// TODO: Add your control notification handler code here
	CSettingDialog csd;
	csd.DoModal();
}


void CGameDlg::OnBnClickedBtnGameover()
{
	// TODO: Add your control notification handler code here

	CDialogEx::OnCancel();
}
