
#pragma once

#include "afxdialogex.h"


// Dlg_EnhaSharp 对话框

class Dlg_EnhaSharp : public CDialogEx
{
	DECLARE_DYNAMIC(Dlg_EnhaSharp)

public:
	//enum { IDD = IDD_Dlg_ENHASHARP };
	Dlg_EnhaSharp(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~Dlg_EnhaSharp();
	int m_neighborhoodType;//邻域类型

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_Dlg_ENHASHARP };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	afx_msg void OnRADlap4();
	afx_msg void OnRADlap8();
	virtual void OnOK();
	DECLARE_MESSAGE_MAP()
};
