#pragma once
#include "afxdialogex.h"


// CDlgImgInfo 对话框

class CDlgImgInfo : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgImgInfo)

public:
	CDlgImgInfo(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CDlgImgInfo();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DlgImgInfo};
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	long m_Height;
	long m_Width;
	afx_msg void OnStnClickedEditHeight();
	afx_msg void OnEnChangeEditHeight();
	afx_msg void OnEnChangeEditWidth();
	long m_bitCount;
	virtual BOOL OnInitDialog();
};
