#pragma once
#include "afxdialogex.h"


// DlgMorphMenu 对话框

class DlgMorphMenu : public CDialogEx
{
	DECLARE_DYNAMIC(DlgMorphMenu)

public:
	DlgMorphMenu(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~DlgMorphMenu();
	int m_morphmenu;
	int m_ForeMode;
	CButton	m_Control9;
	CButton	m_Control8;
	CButton	m_Control7;
	CButton	m_Control6;
	CButton	m_Control5;
	CButton	m_Control4;
	CButton	m_Control3;
	CButton	m_Control2;
	CButton	m_Control1;
	CButton m_ControlAll;
	int		m_nMode;
	int		m_nStructure1;
	int		m_nStructure2;
	int		m_nStructure3;
	int		m_nStructure4;
	int		m_nStructure5;
	int		m_nStructure6;
	int		m_nStructure7;
	int		m_nStructure8;
	int		m_nStructure9;
	int     m_nStructureAll;
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DlgMorphMenu };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	afx_msg void Oncustom();
	afx_msg void OnVert();
	afx_msg void OnHori();
	afx_msg void OnErosion();
	afx_msg void OnDilation();
	afx_msg void OnOpen();
	afx_msg void OnClose();
	afx_msg void OnInsiderEdge();
	afx_msg void OnOuterEdge();
	afx_msg void OnForeBlack();
	afx_msg void OnForeWhite();
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnBnClickedStructure1();
	int p1;//1点击次数
	afx_msg void OnBnClickedStructure2();
	int p2;//2点击次数
	afx_msg void OnBnClickedStructure3();
	int p3;//3点击次数
	afx_msg void OnBnClickedStructure4();
	int p4;//4点击次数
	afx_msg void OnBnClickedStructure5();
	int p5;//5点击次数
	afx_msg void OnBnClickedStructure6();
	int p6;//6点击次数
	afx_msg void OnBnClickedStructure7();
	int p7;//7点击次数
	afx_msg void OnBnClickedStructure8();
	int p8;//8点击次数
	afx_msg void OnBnClickedStructure9();
	int p9;//9点击次数
	afx_msg void OnBnClickedStructureAll();
	int pAll;//全选点击次数
};
