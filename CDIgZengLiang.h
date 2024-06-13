#pragma once
#include "afxdialogex.h"


// CDIgZengLiang 对话框

class CDIgZengLiang : public CDialogEx
{
	DECLARE_DYNAMIC(CDIgZengLiang)

public:
	CDIgZengLiang(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CDIgZengLiang();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIglight };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int m_offset;
	virtual BOOL OnInitDialog();
	afx_msg void OnEnChangeoffset();
};
