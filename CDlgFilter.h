#pragma once
#include"MFCTest1.h"
#include"MFCTest1Doc.h"
#include"MFCTest1View.h"

// CDlgFilter 对话框

class CDlgFilter : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgFilter)

public:
	CDlgFilter(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CDlgFilter();

	CMFCTest1Doc* pDoc;
	float m_operator1;
	float m_operator2;
	float m_operator3;
	float m_operator4;
	float m_operator5;
	float m_operator6;
	float m_operator7;
	float m_operator8;
	float m_operator9;

	CButton m_filter1_Control;
	int m_filter_species;
	
	int m_edge_direction;
	CButton m_filter12_Control;
	CButton m_filter13_Control;
	CButton m_filter14_Control;
	CButton m_filter15_Control;
	BOOL m_bPreviewed;

	// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_Filter };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	unsigned char* beginBits;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnBnClickedRadio3();
	afx_msg void OnBnClickedRadio4();
	afx_msg void OnBnClickedRadio5();
	afx_msg void OnBnClickedRadio6();
	float m_coefficient;
	int m_constant;
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedRadio7();
	afx_msg void OnBnClickedRadio8();
	afx_msg void OnBnClickedRadio9();
	afx_msg void OnBnClickedRadio10();
	afx_msg void OnBnClickedRadio11();
	afx_msg void OnBnClickedRadio12();
	afx_msg void OnBnClickedSave();
	afx_msg void OnBnClickedLoad();

	
	afx_msg void OnBnClickedRadio13();
	afx_msg void OnBnClickedRadio14();
	afx_msg void OnBnClickedRadio15();
};
