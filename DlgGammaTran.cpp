// DlgGammaTran.cpp: 实现文件
//

#include "pch.h"
#include "MFCTest1.h"
#include "afxdialogex.h"
#include "DlgGammaTran.h"


// DlgGammaTran 对话框

IMPLEMENT_DYNAMIC(DlgGammaTran, CDialogEx)

DlgGammaTran::DlgGammaTran(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_Gamma, pParent)
	, m_fValGamma(0)
{

}

DlgGammaTran::~DlgGammaTran()
{
}

void DlgGammaTran::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_Gamma, m_fValGamma);
}


BEGIN_MESSAGE_MAP(DlgGammaTran, CDialogEx)
END_MESSAGE_MAP()


// DlgGammaTran 消息处理程序
