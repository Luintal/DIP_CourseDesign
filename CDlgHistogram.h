#pragma once
#include "afxdialogex.h"


// CDlgHistogram 对话框

class CDlgHistogram : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgHistogram)

public:
	CDlgHistogram(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CDlgHistogram();
	// 当前鼠标拖动状态，0表示未拖动，1表示正在拖动下限，2表示正在拖动上限。
	int		m_iIsDraging;

	// 相应鼠标事件的矩形区域
	CRect	m_MouseRect;

	// DIB的高度
	LONG	m_lHeight;

	// DIB的宽度
	LONG	m_lWidth;
	LONG    m_lLineBytes;

	// 指向当前DIB象素的指针
	char* m_lpDIBBits;

	// 各个灰度值的计数
	LONG	m_lCount[256];

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DlgHistogram };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int m_iLowGray;
	int m_iHighGray;
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnEnKillfocusEditLow();
	afx_msg void OnEnKillfocusEditHigh();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnStnClickedCoord();
};
