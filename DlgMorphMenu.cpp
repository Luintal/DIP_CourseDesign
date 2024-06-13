// DlgMorphMenu.cpp: 实现文件
//

#include "pch.h"
#include "MFCTest1.h"
#include "afxdialogex.h"
#include "DlgMorphMenu.h"


// DlgMorphMenu 对话框

IMPLEMENT_DYNAMIC(DlgMorphMenu, CDialogEx)

DlgMorphMenu::DlgMorphMenu(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DlgMorphMenu, pParent)
{
	p1 = 0;
	p2 = 0;
	p3 = 0;
	p4 = 0;
	p5 = 0;
	p6 = 0;
	p7 = 0;
	p8 = 0;
	p9 = 0;
	pAll = 0;
	m_morphmenu = -1;
	m_ForeMode = -1;
	m_nMode = -1;
	m_nStructure1 = -1;
	m_nStructure2 = -1;
	m_nStructure3 = -1;
	m_nStructure4 = -1;
	m_nStructure5 = -1;
	m_nStructure6 = -1;
	m_nStructure7 = -1;
	m_nStructure8 = -1;
	m_nStructure9 = -1;
	m_nStructureAll = -1;
}

DlgMorphMenu::~DlgMorphMenu()
{
}

void DlgMorphMenu::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	
	DDX_Radio(pDX, IDC_Erosion, m_morphmenu);
	DDX_Radio(pDX, IDC_ForeWhite, m_ForeMode);
	DDX_Control(pDX, IDC_Structure9, m_Control9);
	DDX_Control(pDX, IDC_Structure8, m_Control8);
	DDX_Control(pDX, IDC_Structure7, m_Control7);
	DDX_Control(pDX, IDC_Structure6, m_Control6);
	DDX_Control(pDX, IDC_Structure5, m_Control5);
	DDX_Control(pDX, IDC_Structure4, m_Control4);
	DDX_Control(pDX, IDC_Structure3, m_Control3);
	DDX_Control(pDX, IDC_Structure2, m_Control2);
	DDX_Control(pDX, IDC_Structure1, m_Control1);
	DDX_Control(pDX, IDC_SelectAll, m_ControlAll);
	DDX_Radio(pDX, IDC_Hori, m_nMode);
	DDX_Radio(pDX, IDC_Structure1, m_nStructure1);
	DDX_Radio(pDX, IDC_Structure2, m_nStructure2);
	DDX_Radio(pDX, IDC_Structure3, m_nStructure3);
	DDX_Radio(pDX, IDC_Structure4, m_nStructure4);
	DDX_Radio(pDX, IDC_Structure5, m_nStructure5);
	DDX_Radio(pDX, IDC_Structure6, m_nStructure6);
	DDX_Radio(pDX, IDC_Structure7, m_nStructure7);
	DDX_Radio(pDX, IDC_Structure8, m_nStructure8);
	DDX_Radio(pDX, IDC_Structure9, m_nStructure9);
	DDX_Radio(pDX, IDC_SelectAll, m_nStructureAll);
}

BEGIN_MESSAGE_MAP(DlgMorphMenu, CDialogEx)
	ON_BN_CLICKED(IDC_Structure1, &DlgMorphMenu::OnBnClickedStructure1)
	ON_BN_CLICKED(IDC_Structure2, &DlgMorphMenu::OnBnClickedStructure2)
	ON_BN_CLICKED(IDC_Structure3, &DlgMorphMenu::OnBnClickedStructure3)
	ON_BN_CLICKED(IDC_Structure4, &DlgMorphMenu::OnBnClickedStructure4)
	ON_BN_CLICKED(IDC_Structure5, &DlgMorphMenu::OnBnClickedStructure5)
	ON_BN_CLICKED(IDC_Structure6, &DlgMorphMenu::OnBnClickedStructure6)
	ON_BN_CLICKED(IDC_Structure7, &DlgMorphMenu::OnBnClickedStructure7)
	ON_BN_CLICKED(IDC_Structure8, &DlgMorphMenu::OnBnClickedStructure8)
	ON_BN_CLICKED(IDC_Structure9, &DlgMorphMenu::OnBnClickedStructure9)
	ON_BN_CLICKED(IDC_SelectAll, &DlgMorphMenu::OnBnClickedStructureAll)
	ON_BN_CLICKED(IDC_custom, &DlgMorphMenu::Oncustom)
	ON_BN_CLICKED(IDC_Vert, &DlgMorphMenu::OnVert)
	ON_BN_CLICKED(IDC_Hori, &DlgMorphMenu::OnHori)
	ON_BN_CLICKED(IDC_Erosion, &DlgMorphMenu::OnErosion)
	
	ON_BN_CLICKED(IDC_Dilation, &DlgMorphMenu::OnDilation)
	ON_BN_CLICKED(IDC_Open, &DlgMorphMenu::OnOpen)
	ON_BN_CLICKED(IDC_Close, &DlgMorphMenu::OnClose)
	ON_BN_CLICKED(IDC_InsiderEdge, &DlgMorphMenu::OnInsiderEdge)
	ON_BN_CLICKED(IDC_OuterEdge, &DlgMorphMenu::OnOuterEdge)
	ON_BN_CLICKED(IDC_ForeBlack, &DlgMorphMenu::OnForeBlack)
	ON_BN_CLICKED(IDC_ForeWhite, &DlgMorphMenu::OnForeWhite)
END_MESSAGE_MAP()


// DlgMorphMenu 消息处理程序

void DlgMorphMenu::Oncustom()
{
	m_nMode = 2;
	m_Control1.EnableWindow(TRUE);//使能
	m_Control2.EnableWindow(TRUE);
	m_Control3.EnableWindow(TRUE);
	m_Control4.EnableWindow(TRUE);
	m_Control5.EnableWindow(TRUE);
	m_Control6.EnableWindow(TRUE);
	m_Control7.EnableWindow(TRUE);
	m_Control8.EnableWindow(TRUE);
	m_Control9.EnableWindow(TRUE);
	m_ControlAll.EnableWindow(TRUE);

}

void DlgMorphMenu::OnVert()
{
	m_nMode=1;
	m_Control1.EnableWindow(FALSE);//失能
	m_Control2.EnableWindow(FALSE);
	m_Control3.EnableWindow(FALSE);
	m_Control4.EnableWindow(FALSE);
	m_Control5.EnableWindow(FALSE);
	m_Control6.EnableWindow(FALSE);
	m_Control7.EnableWindow(FALSE);
	m_Control8.EnableWindow(FALSE);
	m_Control9.EnableWindow(FALSE);
	m_ControlAll.EnableWindow(FALSE);
	//清空所有的单选钮
	m_Control1.SetCheck(0);
	m_Control2.SetCheck(0);
	m_Control3.SetCheck(0);
	m_Control4.SetCheck(0);
	m_Control5.SetCheck(0);
	m_Control6.SetCheck(0);
	m_Control7.SetCheck(0);
	m_Control8.SetCheck(0);
	m_Control9.SetCheck(0);
	m_ControlAll.SetCheck(0);
	//选中垂直模板2、5、8
	m_Control2.SetCheck(1);
	m_Control5.SetCheck(1);
	m_Control8.SetCheck(1);
}

void DlgMorphMenu::OnHori()
{
	m_nMode=0;
	m_Control1.EnableWindow(FALSE);
	m_Control2.EnableWindow(FALSE);
	m_Control3.EnableWindow(FALSE);
	m_Control4.EnableWindow(FALSE);
	m_Control5.EnableWindow(FALSE);
	m_Control6.EnableWindow(FALSE);
	m_Control7.EnableWindow(FALSE);
	m_Control8.EnableWindow(FALSE);
	m_Control9.EnableWindow(FALSE);
	m_ControlAll.EnableWindow(FALSE);
	//清空所有的单选钮
	m_Control1.SetCheck(0);
	m_Control2.SetCheck(0);
	m_Control3.SetCheck(0);
	m_Control4.SetCheck(0);
	m_Control5.SetCheck(0);
	m_Control6.SetCheck(0);
	m_Control7.SetCheck(0);
	m_Control8.SetCheck(0);
	m_Control9.SetCheck(0);
	m_ControlAll.SetCheck(0);
	//选中水平模板4、5、6
	m_Control4.SetCheck(1);
	m_Control5.SetCheck(1);
	m_Control6.SetCheck(1);
}	

void DlgMorphMenu::OnErosion()
{
	m_morphmenu=0;
}



void DlgMorphMenu::OnDilation()
{
	m_morphmenu=1;
}

void DlgMorphMenu::OnOpen()
{
	m_morphmenu=2;
}

void DlgMorphMenu::OnClose()
{
	m_morphmenu=3;
}

void DlgMorphMenu::OnInsiderEdge()
{
	m_morphmenu=4;
}

void DlgMorphMenu::OnOuterEdge()
{
	m_morphmenu=5;
}

void DlgMorphMenu::OnForeBlack()
{
	m_ForeMode=1;
}

void DlgMorphMenu::OnForeWhite()
{
	m_ForeMode=0;
}
void DlgMorphMenu::OnBnClickedStructure1()
{
	// 单选钮可以取消
	if (p1 % 2 == 0) { p1++; return; }
	else p1++;
	if (m_Control1.GetCheck() == 1) 
	{ m_Control1.SetCheck(0); }
	else
		if (m_Control1.GetCheck() == 0) { m_Control1.SetCheck(1); }
}

void DlgMorphMenu::OnBnClickedStructure2()
{
	// 单选钮可以取消
	if (p2 % 2 == 0) { p2++; return; }
	else p2++;
	if (m_Control2.GetCheck() == 1) { m_Control2.SetCheck(0); }
	else
		if (m_Control2.GetCheck() == 0) { m_Control2.SetCheck(1); }
}

void DlgMorphMenu::OnBnClickedStructure3()
{
	// 单选钮可以取消
	if (p3 % 2 == 0) { p3++; return; }
	else p3++;
	if (m_Control3.GetCheck() == 1) { m_Control3.SetCheck(0); }
	else
		if (m_Control3.GetCheck() == 0) { m_Control3.SetCheck(1); }
}


void DlgMorphMenu::OnBnClickedStructure4()
{
	// 单选钮可以取消
	if (p4 % 2 == 0) { p4++; return; }
	else p4++;
	if (m_Control4.GetCheck() == 1) { m_Control4.SetCheck(0); }
	else
		if (m_Control4.GetCheck() == 0) { m_Control4.SetCheck(1); }
}

void DlgMorphMenu::OnBnClickedStructure5()
{
	// 单选钮可以取消
	if (p5 % 2 == 0) { p5++; return; }
	else p5++;
	if (m_Control5.GetCheck() == 1) { m_Control5.SetCheck(0); }
	else
		if (m_Control5.GetCheck() == 0) { m_Control5.SetCheck(1); }
}

void DlgMorphMenu::OnBnClickedStructure6()
{
	// 单选钮可以取消
	if (p6 % 2 == 0) { p6++; return; }
	else p6++;
	if (m_Control6.GetCheck() == 1) { m_Control6.SetCheck(0); }
	else
		if (m_Control6.GetCheck() == 0) { m_Control6.SetCheck(1); }
}

void DlgMorphMenu::OnBnClickedStructure7()
{
	// 单选钮可以取消
	if (p7 % 2 == 0) { p7++; return; }
	else p7++;
	if (m_Control7.GetCheck() == 1) { m_Control7.SetCheck(0); }
	else
		if (m_Control7.GetCheck() == 0) { m_Control7.SetCheck(1); }
}


void DlgMorphMenu::OnBnClickedStructure8()
{
	// 单选钮可以取消
	if (p8 % 2 == 0) { p8++; return; }
	else p8++;
	if (m_Control8.GetCheck() == 1) { m_Control8.SetCheck(0); }
	else
		if (m_Control8.GetCheck() == 0) { m_Control8.SetCheck(1); }
}

void DlgMorphMenu::OnBnClickedStructure9()
{
	// 单选钮可以取消
	if (p9 % 2 == 0) { p9++; return; }
	else p9++;
	if (m_Control9.GetCheck() == 1) { m_Control9.SetCheck(0); }
	else
		if (m_Control9.GetCheck() == 0) { m_Control9.SetCheck(1); }
}

void DlgMorphMenu::OnBnClickedStructureAll()
{
	// 点击次数加一
	pAll++;

	// 检查点击次数的奇偶性来确定是全选还是全不选
	int checkState = (pAll % 2 == 1) ? 1 : 0;

	// 设置全选按钮的状态
	m_ControlAll.SetCheck(checkState);

	// 将所有相关控件设置为与全选按钮相同的状态
	m_Control1.SetCheck(checkState);
	m_Control2.SetCheck(checkState);
	m_Control3.SetCheck(checkState);
	m_Control4.SetCheck(checkState);
	m_Control5.SetCheck(checkState);
	m_Control6.SetCheck(checkState);
	m_Control7.SetCheck(checkState);
	m_Control8.SetCheck(checkState);
	m_Control9.SetCheck(checkState);
}
