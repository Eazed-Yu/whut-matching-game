// CVersionDlg.cpp : implementation file
//

#include "pch.h"
#include "LLK.h"
#include "CVersionDlg.h"
#include "afxdialogex.h"

// CVersionDlg dialog

IMPLEMENT_DYNAMIC(CVersionDlg, CDialogEx)

CVersionDlg::CVersionDlg(CWnd *pParent /*=nullptr*/)
	: CDialogEx(IDD_ABOUTBOX, pParent)
{
}

CVersionDlg::~CVersionDlg()
{
}

void CVersionDlg::DoDataExchange(CDataExchange *pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CVersionDlg, CDialogEx)
END_MESSAGE_MAP()

// CVersionDlg message handlers

BOOL CVersionDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	// ���öԻ���ͼ��
	m_vIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	SetIcon(m_vIcon, TRUE);	 // ���ô�ͼ��
	SetIcon(m_vIcon, FALSE); // ����Сͼ��

	return TRUE; // return TRUE unless you set the focus to a control
				 // EXCEPTION: OCX Property Pages should return FALSE
}
