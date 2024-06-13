#pragma once
#include "afxdialogex.h"
#include"MFCTest1Doc.h"

// CDlgPointWin 对话框

class CDlgPointWin : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgPointWin)

public:
	CDlgPointWin(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CDlgPointWin();

	//当前鼠标拖动状态，0表示未拖动，1表示正在拖动下限，2表示正在拖动上限
	int m_iIsDraging;

	//相应鼠标事件的矩形区域
	CRect m_MouseRect;

	CMFCTest1Doc* pDoc;

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DlgPointWin };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	BYTE m_bLow;
	BYTE m_bUp;
	virtual BOOL OnInitDialog();
	afx_msg void OnKillfocusEDITLow();
	afx_msg void OnKillfocusEDITUp();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
	virtual void OnOK();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
};
