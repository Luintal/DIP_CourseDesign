// CDlgImgInfo.cpp: 实现文件
//

#include "pch.h"
#include "MFCTest1.h"
#include "afxdialogex.h"
#include "CDlgImgInfo.h"


// CDlgImgInfo 对话框

IMPLEMENT_DYNAMIC(CDlgImgInfo, CDialogEx)

CDlgImgInfo::CDlgImgInfo(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DlgImgInfo, pParent)
	, m_Height(0)
	, m_Width(0)
	, m_bitCount(0)
{

}

CDlgImgInfo::~CDlgImgInfo()
{
}

void CDlgImgInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, ID_EDIT_Height, m_Height);
	DDX_Text(pDX, IDC_EDIT_Width, m_Width);
	DDX_Text(pDX, IDC_EDIT_BitCount, m_bitCount);
}


BEGIN_MESSAGE_MAP(CDlgImgInfo, CDialogEx)
	ON_STN_CLICKED(ID_EDIT_Height, &CDlgImgInfo::OnStnClickedEditHeight)
	ON_EN_CHANGE(ID_EDIT_Height, &CDlgImgInfo::OnEnChangeEditHeight)
	ON_EN_CHANGE(IDC_EDIT_Width, &CDlgImgInfo::OnEnChangeEditWidth)
END_MESSAGE_MAP()


// CDlgImgInfo 消息处理程序


void CDlgImgInfo::OnStnClickedEditHeight()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CDlgImgInfo::OnEnChangeEditHeight()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CDlgImgInfo::OnEnChangeEditWidth()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


BOOL CDlgImgInfo::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	UpdateData(false);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
