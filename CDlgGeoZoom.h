#pragma once
#include "afxdialogex.h"
#include"MFCTest1Doc.h"
#include"MFCTest1View.h"

// CDlgGeoZoom 对话框

class CDlgGeoZoom : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgGeoZoom)

public:
	CDlgGeoZoom(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CDlgGeoZoom();
	float	m_XZoom;
	float	m_YZoom;
	CMFCTest1Doc* pDoc;
	BOOL m_bPreviewed;
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DlgGeoZoom };
	
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedPriimg();
	afx_msg void OnBnClickedResimg();
};
