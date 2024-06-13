#pragma once
#include "afxdialogex.h"
#include "MFCTest1Doc.h"


// CDlgPointThre 对话框

class CDlgPointThre : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgPointThre)

public:
	CDlgPointThre(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CDlgPointThre();
	BYTE temp;
	int		m_AMode;
	

	//当前鼠标拖动状态，TRUE表示正在拖动
	BOOL m_bIsDraging;

	//相应鼠标事件的矩形区域
	CRect m_MouseRect;

	CMFCTest1Doc* pDoc;
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_PointThre };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	BYTE m_bThre;
	virtual BOOL OnInitDialog();
	afx_msg void OnEnKillfocusEditThre();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
	afx_msg void OnBnClickedRadio1();
	
	afx_msg void OnBnClickedRadio2();
	
	afx_msg void OnBnClickedRadio3();
	
	afx_msg void OnBnClickedRadio4();
	
	afx_msg void OnBnClickedPreviewImg();
	afx_msg void OnBnClickedRestoreImg();
	afx_msg void OnBnClickedCalcuthre();
	
	afx_msg void OnBnClickedAddcolor();
};