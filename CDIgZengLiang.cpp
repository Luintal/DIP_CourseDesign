// CDIgZengLiang.cpp: 实现文件
//

#include "pch.h"
#include "MFCTest1.h"
#include "afxdialogex.h"
#include "CDIgZengLiang.h"


// CDIgZengLiang 对话框

IMPLEMENT_DYNAMIC(CDIgZengLiang, CDialogEx)

CDIgZengLiang::CDIgZengLiang(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIglight, pParent)
	, m_offset(0)
{

}

CDIgZengLiang::~CDIgZengLiang()
{
}

void CDIgZengLiang::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_offset, m_offset);
	DDV_MinMaxInt(pDX, m_offset, -255, 255);
}


BEGIN_MESSAGE_MAP(CDIgZengLiang, CDialogEx)
	ON_EN_CHANGE(IDC_offset, &CDIgZengLiang::OnEnChangeoffset)
END_MESSAGE_MAP()


// CDIgZengLiang 消息处理程序
// CDlgZengLiang 消息处理程序
BOOL CDIgZengLiang::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	//m_Palette = false;
	//m_HSI = false;
	//UpdateData(false);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CDIgZengLiang::OnEnChangeoffset()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}
