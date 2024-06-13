#pragma once
#include "afxdialogex.h"
#include "MFCTest1Doc.h"
#include"MFCTest1View.h"
#include "DIBAPI.H"
#include "geotrans.h"
#include "afxwin.h"
#include <algorithm> 

// DlgGeoRota 对话框

class DlgGeoRota : public CDialogEx
{
	DECLARE_DYNAMIC(DlgGeoRota)

public:
	DlgGeoRota(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~DlgGeoRota();
	int		m_iRotateAngle;
	bool m_bPreviewed = false;
	CMFCTest1Doc* pDoc;

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_GEORota };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedImagepre();
	afx_msg void OnBnClickedImageres();
};
