

// Dlg_EnhaSharp.cpp: 实现文件
//

#include "pch.h"
#include "MFCTest1.h"
#include "afxdialogex.h"
#include "Dlg_EnhaSharp.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
// DlgMidFilter 对话框


IMPLEMENT_DYNAMIC(Dlg_EnhaSharp, CDialogEx)

Dlg_EnhaSharp::Dlg_EnhaSharp(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_Dlg_ENHASHARP, pParent)
	, m_neighborhoodType(0)
{
	m_neighborhoodType = 0;
}

Dlg_EnhaSharp::~Dlg_EnhaSharp()
{
}

void Dlg_EnhaSharp::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RADlap4, m_neighborhoodType);
}


BEGIN_MESSAGE_MAP(Dlg_EnhaSharp, CDialogEx)
	ON_BN_CLICKED(IDC_RADlap4, &Dlg_EnhaSharp::OnRADlap4)
	ON_BN_CLICKED(IDC_RADlap8, &Dlg_EnhaSharp::OnRADlap8)
END_MESSAGE_MAP()


// Dlg_EnhaSharp 消息处理程序

void Dlg_EnhaSharp::OnRADlap4()
{
	//lap4模板
	m_neighborhoodType = 0;

	//更新
	UpdateData(FALSE);
}

void Dlg_EnhaSharp::OnRADlap8()
{
	//lap8模板
	m_neighborhoodType = 1;

	//更新
	UpdateData(FALSE);
}

void Dlg_EnhaSharp::OnOK()
{
	// 获取用户设置（更新）
	UpdateData(TRUE);

	// 调用父类的OnOK函数
	// 退出
	CDialog::OnOK();

}
