#pragma once
#include "afxdialogex.h"


// DlgGammaTran 对话框

class DlgGammaTran : public CDialogEx
{
	DECLARE_DYNAMIC(DlgGammaTran)

public:
	DlgGammaTran(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~DlgGammaTran();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_Gamma };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	float m_fValGamma;
};
