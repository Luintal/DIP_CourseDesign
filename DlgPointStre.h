#pragma once


#include "afxdialogex.h"
#include "MFCTest1Doc.h"
// DlgPointStre 对话框

class DlgPointStre : public CDialogEx
{
	DECLARE_DYNAMIC(DlgPointStre)

public:
	DlgPointStre(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~DlgPointStre();
	// 当前鼠标拖动状态，0表示未拖动，1表示正在拖动第一点，2表示正在拖动第二点。
	int		m_iIsDraging;

	// 相应鼠标事件的矩形区域
	CRect	m_MouseRect;

	// 标识是否已经绘制橡皮筋线
	BOOL	m_bDrawed;

	// 保存鼠标左键单击时的位置
	CPoint	m_p1;

	// 保存鼠标拖动时的位置
	CPoint	m_p2;

	// 两个转折点坐标
	BYTE	m_bX1;
	BYTE	m_bY1;
	BYTE	m_bX2;
	BYTE	m_bY2;
	
	CMFCTest1Doc* pDoc;
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_PointStre };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
	afx_msg void OnKillfocusEditX1();
	afx_msg void OnKillfocusEditX2();
	afx_msg void OnKillfocusEditY1();
	afx_msg void OnKillfocusEditY2();
	virtual void OnOK();

	
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnBnClickedPreview();
	afx_msg void OnBnClickedRecover();
};
