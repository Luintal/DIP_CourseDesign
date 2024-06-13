#pragma once
#include "afxdialogex.h"


// DIg_Tran_V 对话框

class DIg_Tran_V : public CDialogEx
{
	DECLARE_DYNAMIC(DIg_Tran_V)

public:
	DIg_Tran_V(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~DIg_Tran_V();

	int temp;
	//响应鼠标的区域
	CRect m_MouseRect;
	//标识是否拖动
	BOOL m_bIsDrawing;

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIg_Tran_V };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	int m_thresholdV;
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnEnKillfocusThresholdV();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};
