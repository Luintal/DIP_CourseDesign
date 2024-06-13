#if !defined(AFX_DLGSMOOTH_H__DA1CA811_9B09_49C3_9598_E62B2757D073__INCLUDED_)
#define AFX_DLGSMOOTH_H__DA1CA811_9B09_49C3_9598_E62B2757D073__INCLUDED_


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "afxdialogex.h"


// CDlgSmooth 对话框

class CDlgSmooth : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgSmooth)

public:
	CDlgSmooth(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CDlgSmooth();
	void UpdateEdit();

	// 模板元素数组指针
	DOUBLE* m_fpArray;
	// 模板类型
	int		m_intType;

	// 模板高度
	int		m_iTempH;

	// 模板宽度
	int		m_iTempW;

	// 模板中心元素X坐标
	int		m_iTempMX;

	// 模板中心元素Y坐标
	int		m_iTempMY;

	// 模板系数
	float	m_fTempC;


// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DlgSmooth };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	afx_msg void OnRad1();
	afx_msg void OnRad2();
	afx_msg void OnRad3();
	//afx_msg void OnChangeEditTempw();
	virtual void OnOK();
	afx_msg void OnKillfocusEditTemph();
	afx_msg void OnKillfocusEditTempw();
	DECLARE_MESSAGE_MAP()
};
#endif // !defined(AFX_DLGSMOOTH_H__DA1CA811_9B09_49C3_9598_E62B2757D073__INCLUDED_)
