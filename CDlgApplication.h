#pragma once
#include "afxdialogex.h"


// CDlgApplication 对话框

class CDlgApplication : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgApplication)

public:
	CDlgApplication(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CDlgApplication();
	int m_forecolor=0;//前景加色
	int m_foreground;//前景色选择
	int m_link;//连通数选择
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_Apply };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedFblack();
	afx_msg void OnBnClickedFwhite();
	afx_msg void OnBnClickedAuto();
	afx_msg void OnBnClickedEightconnect();
	afx_msg void OnBnClickedFourconnect();
	afx_msg void OnBnClickedAddcolor();
};
