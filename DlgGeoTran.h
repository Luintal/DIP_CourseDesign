#pragma once
#include "afxdialogex.h"
#include"MFCTest1Doc.h"
#include"MFCTest1View.h"
// DlgGeoTran 对话框

class DlgGeoTran : public CDialogEx
{
	DECLARE_DYNAMIC(DlgGeoTran)

public:
	DlgGeoTran(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~DlgGeoTran();
	long	m_XOffset;
	long	m_YOffset;
	CMFCTest1Doc* pDoc;
	BOOL m_bPreviewed;
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_GEOTrans };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedImagepreview();
	afx_msg void OnBnClickedImagerestore();
};


