// CDlgApplication2.cpp: 实现文件
//

#include "pch.h"
#include "MFCTest1.h"
#include "afxdialogex.h"
#include "CDlgApplication2.h"


// CDlgApplication2 对话框

IMPLEMENT_DYNAMIC(CDlgApplication2, CDialogEx)

CDlgApplication2::CDlgApplication2(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DLG_Apply2, pParent)
	, m_Num(0)
	, m_mS(0)
	, m_mC(0)
	, m_mRound(0)
	, m_mRectangle(0)
	, m_x(0)
	, m_y(0)
{

}

CDlgApplication2::~CDlgApplication2()
{
}

void CDlgApplication2::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_Number, m_Num);
	DDX_Text(pDX, IDC_S, m_mS);
	DDX_Text(pDX, IDC_C, m_mC);
	DDX_Text(pDX, IDC_RectangularDegree, m_mRectangle);
	DDX_Text(pDX, IDC_Roundness, m_mRound);
	DDX_Text(pDX, IDC_X, m_x);
	DDX_Text(pDX, IDC_Y, m_y);
}


BEGIN_MESSAGE_MAP(CDlgApplication2, CDialogEx)
END_MESSAGE_MAP()


// CDlgApplication2 消息处理程序
