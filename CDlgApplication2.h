#pragma once
#include "afxdialogex.h"


// CDlgApplication2 对话框

class CDlgApplication2 : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgApplication2)

public:
	CDlgApplication2(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CDlgApplication2();
	int m_Num;
	int m_mS;
	int m_mC;
	double m_mRound;
	double m_mRectangle;
	int m_x;
	int m_y;
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_Apply2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
