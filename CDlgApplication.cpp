// CDlgApplication.cpp: 实现文件
//

#include "pch.h"
#include "MFCTest1.h"
#include "afxdialogex.h"
#include "CDlgApplication.h"


// CDlgApplication 对话框

IMPLEMENT_DYNAMIC(CDlgApplication, CDialogEx)

CDlgApplication::CDlgApplication(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DLG_Apply, pParent)
	, m_forecolor(0)
	, m_foreground(0)
	, m_link(0)
{

}

CDlgApplication::~CDlgApplication()
{
}

void CDlgApplication::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_AddColor, m_forecolor);     // 绑定加色复选框
	
}


BEGIN_MESSAGE_MAP(CDlgApplication, CDialogEx)
	ON_BN_CLICKED(IDC_FBlack, &CDlgApplication::OnBnClickedFblack)
	ON_BN_CLICKED(IDC_FWhite, &CDlgApplication::OnBnClickedFwhite)
	ON_BN_CLICKED(IDC_Auto, &CDlgApplication::OnBnClickedAuto)
	ON_BN_CLICKED(IDC_EightConnect, &CDlgApplication::OnBnClickedEightconnect)
	ON_BN_CLICKED(IDC_FourConnect, &CDlgApplication::OnBnClickedFourconnect)
	ON_BN_CLICKED(IDC_AddColor, &CDlgApplication::OnBnClickedAddcolor)
END_MESSAGE_MAP()


// CDlgApplication 消息处理程序


void CDlgApplication::OnBnClickedFblack()
{
	// TODO: 在此添加控件通知处理程序代码
	//前景色为黑色
	m_foreground = 0;
}


void CDlgApplication::OnBnClickedFwhite()
{
	// TODO: 在此添加控件通知处理程序代码
	//前景色为白色
	m_foreground = 1;
}


void CDlgApplication::OnBnClickedAuto()
{
	// TODO: 在此添加控件通知处理程序代码
	//自动选择前景色
	m_foreground = 2;
}


void CDlgApplication::OnBnClickedEightconnect()
{
	// TODO: 在此添加控件通知处理程序代码
	//选择八连通
	m_link = 1;
}


void CDlgApplication::OnBnClickedFourconnect()
{
	// TODO: 在此添加控件通知处理程序代码
	//选择四连通
	m_link = 0;
}


void CDlgApplication::OnBnClickedAddcolor()
{
	// TODO: 在此添加控件通知处理程序代码
	//前景加色
	m_forecolor = 1;
}
