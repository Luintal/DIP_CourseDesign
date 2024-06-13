// CDlgFilter.cpp: 实现文件
//

#include "pch.h"
#include "MFCTest1.h"
#include "CDlgFilter.h"
#include "afxdialogex.h"
#include "DIBAPI.h"

// CDlgFilter 对话框

IMPLEMENT_DYNAMIC(CDlgFilter, CDialogEx)

CDlgFilter::CDlgFilter(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DLG_Filter, pParent)
	, m_operator1(0)
	, m_operator2(0)
	, m_operator3(0)
	, m_operator4(0)
	, m_operator5(0)
	, m_operator6(0)
	, m_operator7(0)
	, m_operator8(0)
	, m_operator9(0)
	, m_coefficient(0)
	, m_constant(0)
	, m_filter_species(-1)
	, m_edge_direction(-1)
{

}

CDlgFilter::~CDlgFilter()
{
}

void CDlgFilter::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_m1, m_operator1);
	DDX_Text(pDX, IDC_EDIT_m2, m_operator2);
	DDX_Text(pDX, IDC_EDIT_m3, m_operator3);
	DDX_Text(pDX, IDC_EDIT_m4, m_operator4);
	DDX_Text(pDX, IDC_EDIT_m5, m_operator5);
	DDX_Text(pDX, IDC_EDIT_m6, m_operator6);
	DDX_Text(pDX, IDC_EDIT_m7, m_operator7);
	DDX_Text(pDX, IDC_EDIT_m8, m_operator8);
	DDX_Text(pDX, IDC_EDIT_m9, m_operator9);
	DDX_Text(pDX, IDC_EDIT_mCoe, m_coefficient);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                             
	DDX_Text(pDX, IDC_EDIT_mThre, m_constant);

	DDX_Control(pDX, IDC_RADIO2, m_filter1_Control);
	DDX_Radio(pDX, IDC_RADIO2, m_filter_species);
	DDX_Control(pDX, IDC_RADIO15, m_filter15_Control);
	DDX_Radio(pDX, IDC_RADIO12, m_edge_direction);
	DDX_Control(pDX, IDC_RADIO12, m_filter12_Control);
	DDX_Control(pDX, IDC_RADIO13, m_filter13_Control);
	DDX_Control(pDX, IDC_RADIO14, m_filter14_Control);
	_CrtSetReportMode(_CRT_ASSERT, 0);
}


BEGIN_MESSAGE_MAP(CDlgFilter, CDialogEx)
	ON_BN_CLICKED(IDC_RADIO2, &CDlgFilter::OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_RADIO3, &CDlgFilter::OnBnClickedRadio3)
	ON_BN_CLICKED(IDC_RADIO4, &CDlgFilter::OnBnClickedRadio4)
	ON_BN_CLICKED(IDC_RADIO5, &CDlgFilter::OnBnClickedRadio5)
	ON_BN_CLICKED(IDC_RADIO6, &CDlgFilter::OnBnClickedRadio6)
	ON_BN_CLICKED(IDC_RADIO7, &CDlgFilter::OnBnClickedRadio7)
	ON_BN_CLICKED(IDC_RADIO8, &CDlgFilter::OnBnClickedRadio8)
	ON_BN_CLICKED(IDC_RADIO9, &CDlgFilter::OnBnClickedRadio9)
	ON_BN_CLICKED(IDC_RADIO10, &CDlgFilter::OnBnClickedRadio10)
	ON_BN_CLICKED(IDC_RADIO11, &CDlgFilter::OnBnClickedRadio11)
	ON_BN_CLICKED(IDC_RADIO12, &CDlgFilter::OnBnClickedRadio12)
	ON_BN_CLICKED(IDC_Save, &CDlgFilter::OnBnClickedSave)
	ON_BN_CLICKED(IDC_BUTTON4, &CDlgFilter::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CDlgFilter::OnBnClickedButton5)
	ON_BN_CLICKED(IDLoad, &CDlgFilter::OnBnClickedLoad)
	
	ON_BN_CLICKED(IDC_RADIO13, &CDlgFilter::OnBnClickedRadio13)
	ON_BN_CLICKED(IDC_RADIO14, &CDlgFilter::OnBnClickedRadio14)
	ON_BN_CLICKED(IDC_RADIO15, &CDlgFilter::OnBnClickedRadio15)
END_MESSAGE_MAP()


// CDlgFilter 消息处理程序

int with_edge = -1;//边缘方向，0为垂直，1为水平	
BOOL CDlgFilter::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_filter1_Control.SetCheck(BST_UNCHECKED);  // 设置为未选中状态
	m_filter15_Control.SetCheck(BST_UNCHECKED);  // 设置为未选中状态
	m_filter12_Control.SetCheck(BST_UNCHECKED);  // 设置为未选中状态
	m_filter13_Control.SetCheck(BST_UNCHECKED);  // 设置为未选中状态
	m_filter14_Control.SetCheck(BST_UNCHECKED);  // 设置为未选中状态
	with_edge = -1;
	m_filter_species = -1;
	m_edge_direction = -1;
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}



//底片反色
void CDlgFilter::OnBnClickedRadio2()
{
	//m_filter11_Control.EnableWindow(false);
	m_filter15_Control.EnableWindow(false);
	m_filter12_Control.EnableWindow(false);
	m_filter13_Control.EnableWindow(false);
	m_filter14_Control.EnableWindow(false);
	m_filter15_Control.SetCheck(BST_UNCHECKED);  // 设置为未选中状态
	
	m_filter12_Control.SetCheck(BST_UNCHECKED);  // 设置为未选中状态
	m_filter13_Control.SetCheck(BST_UNCHECKED);  // 设置为未选中状态
	m_filter14_Control.SetCheck(BST_UNCHECKED);  // 设置为未选中状态
	m_operator1 = 0;
	m_operator2 = 0;
	m_operator3 = 0;
	m_operator4 = 0;
	m_operator5 = 1;
	m_operator6 = 0;
	m_operator7 = 0;
	m_operator8 = 0;
	m_operator9 = 0;
	m_coefficient = -1;
	m_constant = 255;
	m_filter_species = 0;
	with_edge = -1;
	//设置文本框不可用
	(CEdit*)GetDlgItem(IDC_EDIT_m1)->EnableWindow(FALSE);
	(CEdit*)GetDlgItem(IDC_EDIT_m2)->EnableWindow(FALSE);
	(CEdit*)GetDlgItem(IDC_EDIT_m3)->EnableWindow(FALSE);
	(CEdit*)GetDlgItem(IDC_EDIT_m4)->EnableWindow(FALSE);
	(CEdit*)GetDlgItem(IDC_EDIT_m5)->EnableWindow(FALSE);
	(CEdit*)GetDlgItem(IDC_EDIT_m6)->EnableWindow(FALSE);
	(CEdit*)GetDlgItem(IDC_EDIT_m7)->EnableWindow(FALSE);
	(CEdit*)GetDlgItem(IDC_EDIT_m8)->EnableWindow(FALSE);
	(CEdit*)GetDlgItem(IDC_EDIT_m9)->EnableWindow(FALSE);
	(CEdit*)GetDlgItem(IDC_EDIT_mCoe)->EnableWindow(FALSE);
	(CEdit*)GetDlgItem(IDC_EDIT_mThre)->EnableWindow(FALSE);

	//更新
	UpdateData(FALSE);
}


//均值模糊
void CDlgFilter::OnBnClickedRadio3()
{
	//m_filter11_Control.EnableWindow(false);
	m_filter15_Control.EnableWindow(false);
	m_filter12_Control.EnableWindow(false);
	m_filter13_Control.EnableWindow(false);
	m_filter14_Control.EnableWindow(false);
	m_filter15_Control.SetCheck(BST_UNCHECKED);  // 设置为未选中状态
	m_filter12_Control.SetCheck(BST_UNCHECKED);  // 设置为未选中状态
	m_filter13_Control.SetCheck(BST_UNCHECKED);  // 设置为未选中状态
	m_filter14_Control.SetCheck(BST_UNCHECKED);  // 设置为未选中状态
	m_operator1 = 1;
	m_operator2 = 1;
	m_operator3 = 1;
	m_operator4 = 1;
	m_operator5 = 1;
	m_operator6 = 1;
	m_operator7 = 1;
	m_operator8 = 1;
	m_operator9 = 1;
	m_coefficient = 1.0 / 9.0;
	m_constant = 0;
	m_filter_species = 1;
	with_edge = -1;
	//设置文本框不可用
	(CEdit*)GetDlgItem(IDC_EDIT_m1)->EnableWindow(FALSE);
	(CEdit*)GetDlgItem(IDC_EDIT_m2)->EnableWindow(FALSE);
	(CEdit*)GetDlgItem(IDC_EDIT_m3)->EnableWindow(FALSE);
	(CEdit*)GetDlgItem(IDC_EDIT_m4)->EnableWindow(FALSE);
	(CEdit*)GetDlgItem(IDC_EDIT_m5)->EnableWindow(FALSE);
	(CEdit*)GetDlgItem(IDC_EDIT_m6)->EnableWindow(FALSE);
	(CEdit*)GetDlgItem(IDC_EDIT_m7)->EnableWindow(FALSE);
	(CEdit*)GetDlgItem(IDC_EDIT_m8)->EnableWindow(FALSE);
	(CEdit*)GetDlgItem(IDC_EDIT_m9)->EnableWindow(FALSE);
	(CEdit*)GetDlgItem(IDC_EDIT_mCoe)->EnableWindow(FALSE);
	(CEdit*)GetDlgItem(IDC_EDIT_mThre)->EnableWindow(FALSE);

	//更新
	UpdateData(FALSE);
}


//高斯模糊
void CDlgFilter::OnBnClickedRadio4()
{
	//m_filter11_Control.EnableWindow(false);
	m_filter15_Control.EnableWindow(false);
	m_filter12_Control.EnableWindow(false);
	m_filter13_Control.EnableWindow(false);
	m_filter14_Control.EnableWindow(false);
	m_filter15_Control.SetCheck(BST_UNCHECKED);  // 设置为未选中状态
	m_filter12_Control.SetCheck(BST_UNCHECKED);  // 设置为未选中状态
	m_filter13_Control.SetCheck(BST_UNCHECKED);  // 设置为未选中状态
	m_filter14_Control.SetCheck(BST_UNCHECKED);  // 设置为未选中状态
	m_operator1 = 1;
	m_operator2 = 2;
	m_operator3 = 1;
	m_operator4 = 2;
	m_operator5 = 4;
	m_operator6 = 2;
	m_operator7 = 1;
	m_operator8 = 2;
	m_operator9 = 1;
	m_coefficient = 1.0 / 16.0;
	m_constant = 0;
	m_filter_species = 2;
	with_edge = -1;
	//设置文本框不可用
	(CEdit*)GetDlgItem(IDC_EDIT_m1)->EnableWindow(FALSE);
	(CEdit*)GetDlgItem(IDC_EDIT_m2)->EnableWindow(FALSE);
	(CEdit*)GetDlgItem(IDC_EDIT_m3)->EnableWindow(FALSE);
	(CEdit*)GetDlgItem(IDC_EDIT_m4)->EnableWindow(FALSE);
	(CEdit*)GetDlgItem(IDC_EDIT_m5)->EnableWindow(FALSE);
	(CEdit*)GetDlgItem(IDC_EDIT_m6)->EnableWindow(FALSE);
	(CEdit*)GetDlgItem(IDC_EDIT_m7)->EnableWindow(FALSE);
	(CEdit*)GetDlgItem(IDC_EDIT_m8)->EnableWindow(FALSE);
	(CEdit*)GetDlgItem(IDC_EDIT_m9)->EnableWindow(FALSE);
	(CEdit*)GetDlgItem(IDC_EDIT_mCoe)->EnableWindow(FALSE);
	(CEdit*)GetDlgItem(IDC_EDIT_mThre)->EnableWindow(FALSE);

	//更新
	UpdateData(FALSE);
}


//锐化
void CDlgFilter::OnBnClickedRadio5()
{
	//m_filter11_Control.EnableWindow(false);
	m_filter15_Control.EnableWindow(false);
	m_filter12_Control.EnableWindow(false);
	m_filter13_Control.EnableWindow(false);
	m_filter14_Control.EnableWindow(false);
	m_filter15_Control.SetCheck(BST_UNCHECKED);  // 设置为未选中状态
	m_filter12_Control.SetCheck(BST_UNCHECKED);  // 设置为未选中状态
	m_filter13_Control.SetCheck(BST_UNCHECKED);  // 设置为未选中状态
	m_filter14_Control.SetCheck(BST_UNCHECKED);  // 设置为未选中状态
	m_operator1 = -1;
	m_operator2 = -1;
	m_operator3 = -1;
	m_operator4 = -1;
	m_operator5 = 9;
	m_operator6 = -1;
	m_operator7 = -1;
	m_operator8 = -1;
	m_operator9 = -1;
	m_coefficient = 1.0;///9.0;   
	m_constant = 0;
	m_filter_species = 3;
	with_edge = -1;
	//设置文本框不可用
	(CEdit*)GetDlgItem(IDC_EDIT_m1)->EnableWindow(FALSE);
	(CEdit*)GetDlgItem(IDC_EDIT_m2)->EnableWindow(FALSE);
	(CEdit*)GetDlgItem(IDC_EDIT_m3)->EnableWindow(FALSE);
	(CEdit*)GetDlgItem(IDC_EDIT_m4)->EnableWindow(FALSE);
	(CEdit*)GetDlgItem(IDC_EDIT_m5)->EnableWindow(FALSE);
	(CEdit*)GetDlgItem(IDC_EDIT_m6)->EnableWindow(FALSE);
	(CEdit*)GetDlgItem(IDC_EDIT_m7)->EnableWindow(FALSE);
	(CEdit*)GetDlgItem(IDC_EDIT_m8)->EnableWindow(FALSE);
	(CEdit*)GetDlgItem(IDC_EDIT_m9)->EnableWindow(FALSE);
	(CEdit*)GetDlgItem(IDC_EDIT_mCoe)->EnableWindow(FALSE);
	(CEdit*)GetDlgItem(IDC_EDIT_mThre)->EnableWindow(FALSE);

	//更新
	UpdateData(FALSE);
}


//浮雕
void CDlgFilter::OnBnClickedRadio6()
{
	//m_filter11_Control.EnableWindow(false);
	m_filter15_Control.EnableWindow(false);
	m_filter12_Control.EnableWindow(false);
	m_filter13_Control.EnableWindow(false);
	m_filter14_Control.EnableWindow(false);
	m_filter15_Control.SetCheck(BST_UNCHECKED);  // 设置为未选中状态
	m_filter12_Control.SetCheck(BST_UNCHECKED);  // 设置为未选中状态
	m_filter13_Control.SetCheck(BST_UNCHECKED);  // 设置为未选中状态
	m_filter14_Control.SetCheck(BST_UNCHECKED);  // 设置为未选中状态
	m_operator1 = 1;
	m_operator2 = 0;
	m_operator3 = 0;
	m_operator4 = 0;
	m_operator5 = 0;
	m_operator6 = 0;
	m_operator7 = 0;
	m_operator8 = 0;
	m_operator9 = -1;
	m_coefficient = 1.0;
	m_constant = 128;
	m_filter_species = 4;
	with_edge = -1;
	//设置文本框不可用
	(CEdit*)GetDlgItem(IDC_EDIT_m1)->EnableWindow(FALSE);
	(CEdit*)GetDlgItem(IDC_EDIT_m2)->EnableWindow(FALSE);
	(CEdit*)GetDlgItem(IDC_EDIT_m3)->EnableWindow(FALSE);
	(CEdit*)GetDlgItem(IDC_EDIT_m4)->EnableWindow(FALSE);
	(CEdit*)GetDlgItem(IDC_EDIT_m5)->EnableWindow(FALSE);
	(CEdit*)GetDlgItem(IDC_EDIT_m6)->EnableWindow(FALSE);
	(CEdit*)GetDlgItem(IDC_EDIT_m7)->EnableWindow(FALSE);
	(CEdit*)GetDlgItem(IDC_EDIT_m8)->EnableWindow(FALSE);
	(CEdit*)GetDlgItem(IDC_EDIT_m9)->EnableWindow(FALSE);
	(CEdit*)GetDlgItem(IDC_EDIT_mCoe)->EnableWindow(FALSE);
	(CEdit*)GetDlgItem(IDC_EDIT_mThre)->EnableWindow(FALSE);

	//更新
	UpdateData(FALSE);
}


//改变亮度
void CDlgFilter::OnBnClickedRadio7()
{
	//m_filter11_Control.EnableWindow(false);
	m_filter15_Control.EnableWindow(false);
	m_filter12_Control.EnableWindow(false);
	m_filter13_Control.EnableWindow(false);
	m_filter14_Control.EnableWindow(false);
	m_filter15_Control.SetCheck(BST_UNCHECKED);  // 设置为未选中状态
	m_filter12_Control.SetCheck(BST_UNCHECKED);  // 设置为未选中状态
	m_filter13_Control.SetCheck(BST_UNCHECKED);  // 设置为未选中状态
	m_filter14_Control.SetCheck(BST_UNCHECKED);  // 设置为未选中状态
	m_operator1 = 0;
	m_operator2 = 0;
	m_operator3 = 0;
	m_operator4 = 0;
	m_operator5 = 1;
	m_operator6 = 0;
	m_operator7 = 0;
	m_operator8 = 0;
	m_operator9 = 0;
	m_coefficient = 1.0;
	m_filter_species = 5;
	m_constant = 50;
	with_edge = -1;
	//设置文本框不可用
	(CEdit*)GetDlgItem(IDC_EDIT_m1)->EnableWindow(FALSE);
	(CEdit*)GetDlgItem(IDC_EDIT_m2)->EnableWindow(FALSE);
	(CEdit*)GetDlgItem(IDC_EDIT_m3)->EnableWindow(FALSE);
	(CEdit*)GetDlgItem(IDC_EDIT_m4)->EnableWindow(FALSE);
	(CEdit*)GetDlgItem(IDC_EDIT_m5)->EnableWindow(FALSE);
	(CEdit*)GetDlgItem(IDC_EDIT_m6)->EnableWindow(FALSE);
	(CEdit*)GetDlgItem(IDC_EDIT_m7)->EnableWindow(FALSE);
	(CEdit*)GetDlgItem(IDC_EDIT_m8)->EnableWindow(FALSE);
	(CEdit*)GetDlgItem(IDC_EDIT_m9)->EnableWindow(FALSE);
	(CEdit*)GetDlgItem(IDC_EDIT_mCoe)->EnableWindow(FALSE);
	(CEdit*)GetDlgItem(IDC_EDIT_mThre)->EnableWindow(TRUE);

	//更新
	UpdateData(FALSE);
}


//自选滤镜
void CDlgFilter::OnBnClickedRadio8()
{
	m_filter15_Control.EnableWindow(false);
	m_filter12_Control.EnableWindow(false);
	m_filter13_Control.EnableWindow(false);
	m_filter14_Control.EnableWindow(false);
	m_filter15_Control.SetCheck(BST_UNCHECKED);  // 设置为未选中状态
	m_filter12_Control.SetCheck(BST_UNCHECKED);  // 设置为未选中状态
	m_filter13_Control.SetCheck(BST_UNCHECKED);  // 设置为未选中状态
	m_filter14_Control.SetCheck(BST_UNCHECKED);  // 设置为未选中状态

	m_filter_species = 6;
	with_edge = -1;
	//设置文本框可用
	(CEdit*)GetDlgItem(IDC_EDIT_m1)->EnableWindow(TRUE);
	(CEdit*)GetDlgItem(IDC_EDIT_m2)->EnableWindow(TRUE);
	(CEdit*)GetDlgItem(IDC_EDIT_m3)->EnableWindow(TRUE);
	(CEdit*)GetDlgItem(IDC_EDIT_m4)->EnableWindow(TRUE);
	(CEdit*)GetDlgItem(IDC_EDIT_m5)->EnableWindow(TRUE);
	(CEdit*)GetDlgItem(IDC_EDIT_m6)->EnableWindow(TRUE);
	(CEdit*)GetDlgItem(IDC_EDIT_m7)->EnableWindow(TRUE);
	(CEdit*)GetDlgItem(IDC_EDIT_m8)->EnableWindow(TRUE);
	(CEdit*)GetDlgItem(IDC_EDIT_m9)->EnableWindow(TRUE);
	(CEdit*)GetDlgItem(IDC_EDIT_mCoe)->EnableWindow(TRUE);
	(CEdit*)GetDlgItem(IDC_EDIT_mThre)->EnableWindow(TRUE);

	//更新
	UpdateData(TRUE);
}


//sobel算子
void CDlgFilter::OnBnClickedRadio9()
{
	m_filter12_Control.EnableWindow(true);
	m_filter13_Control.EnableWindow(true);
	m_filter14_Control.EnableWindow(false);
	m_filter15_Control.EnableWindow(false);


	m_filter15_Control.SetCheck(BST_UNCHECKED);  // 设置为未选中状态
	m_filter12_Control.SetCheck(BST_UNCHECKED);  // 设置为未选中状态
	m_filter13_Control.SetCheck(BST_UNCHECKED);  // 设置为未选中状态
	m_filter14_Control.SetCheck(BST_UNCHECKED);  // 设置为未选中状态
	

	with_edge = 0;

	//设置文本框不可用
	(CEdit*)GetDlgItem(IDC_EDIT_m1)->EnableWindow(FALSE);
	(CEdit*)GetDlgItem(IDC_EDIT_m2)->EnableWindow(FALSE);
	(CEdit*)GetDlgItem(IDC_EDIT_m3)->EnableWindow(FALSE);
	(CEdit*)GetDlgItem(IDC_EDIT_m4)->EnableWindow(FALSE);
	(CEdit*)GetDlgItem(IDC_EDIT_m5)->EnableWindow(FALSE);
	(CEdit*)GetDlgItem(IDC_EDIT_m6)->EnableWindow(FALSE);
	(CEdit*)GetDlgItem(IDC_EDIT_m7)->EnableWindow(FALSE);
	(CEdit*)GetDlgItem(IDC_EDIT_m8)->EnableWindow(FALSE);
	(CEdit*)GetDlgItem(IDC_EDIT_m9)->EnableWindow(FALSE);
	(CEdit*)GetDlgItem(IDC_EDIT_mCoe)->EnableWindow(FALSE);
	(CEdit*)GetDlgItem(IDC_EDIT_mThre)->EnableWindow(FALSE);
}


//prewitt算子
void CDlgFilter::OnBnClickedRadio10()
{
	
	m_filter12_Control.EnableWindow(true);
	m_filter13_Control.EnableWindow(true);
	m_filter14_Control.EnableWindow(false);
	m_filter15_Control.EnableWindow(false);
	m_filter12_Control.SetCheck(BST_UNCHECKED);  // 设置为未选中状态
	m_filter13_Control.SetCheck(BST_UNCHECKED);  // 设置为未选中状态
	m_filter14_Control.SetCheck(BST_UNCHECKED);  // 设置为未选中状态
	m_filter15_Control.SetCheck(BST_UNCHECKED);  // 设置为未选中状态
	with_edge = 1;
	
	//设置文本框不可用
	(CEdit*)GetDlgItem(IDC_EDIT_m1)->EnableWindow(FALSE);
	(CEdit*)GetDlgItem(IDC_EDIT_m2)->EnableWindow(FALSE);
	(CEdit*)GetDlgItem(IDC_EDIT_m3)->EnableWindow(FALSE);
	(CEdit*)GetDlgItem(IDC_EDIT_m4)->EnableWindow(FALSE);
	(CEdit*)GetDlgItem(IDC_EDIT_m5)->EnableWindow(FALSE);
	(CEdit*)GetDlgItem(IDC_EDIT_m6)->EnableWindow(FALSE);
	(CEdit*)GetDlgItem(IDC_EDIT_m7)->EnableWindow(FALSE);
	(CEdit*)GetDlgItem(IDC_EDIT_m8)->EnableWindow(FALSE);
	(CEdit*)GetDlgItem(IDC_EDIT_m9)->EnableWindow(FALSE);
	(CEdit*)GetDlgItem(IDC_EDIT_mCoe)->EnableWindow(FALSE);
	(CEdit*)GetDlgItem(IDC_EDIT_mThre)->EnableWindow(FALSE);
}


//线检测算子
void CDlgFilter::OnBnClickedRadio11()
{
	m_filter15_Control.EnableWindow(true);
	m_filter12_Control.EnableWindow(true);
	m_filter13_Control.EnableWindow(true);
	m_filter14_Control.EnableWindow(true);
	m_filter12_Control.SetCheck(BST_UNCHECKED);  // 设置为未选中状态
	m_filter13_Control.SetCheck(BST_UNCHECKED);  // 设置为未选中状态
	m_filter14_Control.SetCheck(BST_UNCHECKED);  // 设置为未选中状态
	m_filter15_Control.SetCheck(BST_UNCHECKED);  // 设置为未选中状态
	with_edge = 2;

	//设置文本框不可用
	(CEdit*)GetDlgItem(IDC_EDIT_m1)->EnableWindow(FALSE);
	(CEdit*)GetDlgItem(IDC_EDIT_m2)->EnableWindow(FALSE);
	(CEdit*)GetDlgItem(IDC_EDIT_m3)->EnableWindow(FALSE);
	(CEdit*)GetDlgItem(IDC_EDIT_m4)->EnableWindow(FALSE);
	(CEdit*)GetDlgItem(IDC_EDIT_m5)->EnableWindow(FALSE);
	(CEdit*)GetDlgItem(IDC_EDIT_m6)->EnableWindow(FALSE);
	(CEdit*)GetDlgItem(IDC_EDIT_m7)->EnableWindow(FALSE);
	(CEdit*)GetDlgItem(IDC_EDIT_m8)->EnableWindow(FALSE);
	(CEdit*)GetDlgItem(IDC_EDIT_m9)->EnableWindow(FALSE);
	(CEdit*)GetDlgItem(IDC_EDIT_mCoe)->EnableWindow(FALSE);
	(CEdit*)GetDlgItem(IDC_EDIT_mThre)->EnableWindow(FALSE);
}


//垂直方向
void CDlgFilter::OnBnClickedRadio12()
{
	if (with_edge == 0)//sobel
	{
		//m_filter1_Control.SetCheck(BST_UNCHECKED);  // 设置为未选中状态
		m_operator1 = -1;
		m_operator2 = -2;
		m_operator3 = -1;
		m_operator4 = 0;
		m_operator5 = 0;
		m_operator6 = 0;
		m_operator7 = 1;
		m_operator8 = 2;
		m_operator9 = 1;
		m_coefficient = 1.0;
		m_constant = 0;

		m_filter_species = 7;
		m_edge_direction = 0;//
	}
	else if (with_edge == 1)//prewitt
	{
		//m_filter1_Control.SetCheck(BST_UNCHECKED);  // 设置为未选中状态
		m_operator1 = -1;
		m_operator2 = -1;
		m_operator3 = -1;
		m_operator4 = 0;
		m_operator5 = 0;
		m_operator6 = 0;
		m_operator7 = 1;
		m_operator8 = 1;
		m_operator9 = 1;
		m_coefficient = 1.0;
		m_constant = 0;

		m_filter_species = 8;
		m_edge_direction = 0;
	}
	else if (with_edge == 2) {

		m_operator1 = -1;
		m_operator2 = 2;
		m_operator3 = -1;
		m_operator4 = -1;
		m_operator5 = 2;
		m_operator6 = -1;
		m_operator7 = -1;
		m_operator8 = 2;
		m_operator9 = -1;
		m_coefficient = 1.0;
		m_constant = 0;

		m_filter_species = 9;
		m_edge_direction = 0;
	}
	//更新
	UpdateData(FALSE);
}


BOOL WINAPI Template_Filter(LPSTR lpDIBBits, LONG lWidth, LONG lHeight,
	int iTempH, int iTempW,
	int iTempMX, int iTempMY,
	FLOAT* fpArray, FLOAT fCoef, float threshold)
{
	// 指向复制图像的指针
	LPSTR	lpNewDIBBits;
	HLOCAL	hNewDIBBits;
	// 指向源图像的指针
	unsigned char* lpSrc;

	// 指向要复制区域的指针
	unsigned char* lpDst;

	// 循环变量
	LONG	i;
	LONG	j;
	LONG	k;
	LONG	l;

	// 计算结果
	FLOAT	fResult;
	// 图像每行的字节数
	LONG lLineBytes;
	// 计算图像每行的字节数
	lLineBytes = (lWidth + 3) / 4 * 4;
	// 暂时分配内存，以保存新图像
	hNewDIBBits = LocalAlloc(LHND, lLineBytes * lHeight);
	// 判断是否内存分配失败
	if (hNewDIBBits == NULL)
	{
		// 分配内存失败
		return FALSE;
	}
	// 锁定内存
	lpNewDIBBits = (char*)LocalLock(hNewDIBBits);
	// 初始化图像为原始图像
	memcpy(lpNewDIBBits, lpDIBBits, lLineBytes * lHeight);
	// 行(除去边缘几行)
	for (i = iTempMY; i < lHeight - iTempH + iTempMY + 1; i++)
	{
		// 列(除去边缘几列)
		for (j = iTempMX; j < lWidth - iTempW + iTempMX + 1; j++)
		{
			// 指向新DIB第i行，第j个象素的指针
			lpDst = (unsigned char*)lpNewDIBBits + lLineBytes * (lHeight - 1 - i) + j;

			fResult = 0;

			// 计算
			for (k = 0; k < iTempH; k++)
			{
				for (l = 0; l < iTempW; l++)
				{
					// 指向DIB第i - iTempMY + k行，第j - iTempMX + l个象素的指针
					lpSrc = (unsigned char*)lpDIBBits + lLineBytes * (lHeight - 1 - i + iTempMY - k)
						+ j - iTempMX + l;
					// 保存象素值
					fResult += (*lpSrc) * fpArray[k * iTempW + l];
				}
			}
			// 乘上系数
			fResult *= fCoef;
			//加上常数
			fResult += threshold;
			//取绝对值
			fResult = (FLOAT)fabs(fResult);

			if (fResult > 255)
			{
				*lpDst = 255;
			}
			else
			{
				*lpDst = (unsigned char)(fResult + 0.5);
			}
		}
	}
	// 复制变换后的图像
	memcpy(lpDIBBits, lpNewDIBBits, lLineBytes * lHeight);

	// 释放内存
	LocalUnlock(hNewDIBBits);
	LocalFree(hNewDIBBits);

	// 返回
	return TRUE;

}

//预览图像
void CDlgFilter::OnBnClickedButton4()
{

	// TODO: 在此添加控件通知处理程序代码
	long	lSrcLineBytes;		//图象每行的字节数
	long	lSrcWidth;      //图象的宽度和高度
	long	lSrcHeight;
	int     lpSrcBitCount;       //图像的位深
	LPSTR	lpSrcDib;		//指向源图象的指针	
	LPSTR	lpSrcStartBits;	//指向源像素的指针

	//锁定DIB
	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// 锁定DIB

	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);			// 找到DIB图象像素起始位置	

	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);			// 找到DIB图象像素起始位置	
	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);					// 获取图象的宽度		
	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);					// 获取图象的高度	
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);                    //获取图像位深
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount);		// 计算图象每行的字节数
	
	
	
	// 模板高度
	int iTempH;
	// 模板宽度
	int iTempW;
	// 模板中心元素X坐标
	int iTempMX;
	// 模板中心元素Y坐标
	int iTempMY;
	// 模板元素数组
	FLOAT aValue[9];
	float coefficient;
	int constant;

	// 设定平移量（3*3）
	iTempH = 3;
	iTempW = 3;
	iTempMX = 1;
	iTempMY = 1;

	UpdateData(TRUE);
	aValue[0] = m_operator1;
	aValue[1] = m_operator2;
	aValue[2] = m_operator3;
	aValue[3] = m_operator4;
	aValue[4] = m_operator5;
	aValue[5] = m_operator6;
	aValue[6] = m_operator7;
	aValue[7] = m_operator8;
	aValue[8] = m_operator9;
	coefficient = m_coefficient;
	constant = m_constant;
	Template_Filter(lpSrcStartBits, lSrcWidth, lSrcHeight,
		iTempH, iTempW, iTempMX, iTempMY, aValue, coefficient, constant);

	// 设置脏标记
	pDoc->SetModifiedFlag(TRUE);

	// 更新视图
	pDoc->UpdateAllViews(NULL);

	m_bPreviewed = TRUE;
}

//恢复图像
void CDlgFilter::OnBnClickedButton5()
{
	
	pDoc->OnImgrestore();
	OnInitDialog();
	// 设置脏标记
	pDoc->SetModifiedFlag(FALSE);

	// 更新视图
	pDoc->UpdateAllViews(NULL);
}



void CDlgFilter::OnBnClickedSave()
{
	CString gReadFilePathName1;
	CFileDialog fileDlg(false, _T("txt"), _T("*.txt"), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		_T("txt Files (*.txt)|*.txt|All File (*.*)|*.*||"), NULL);
	if (fileDlg.DoModal() == IDOK)    //弹出对话框
	{
		//char* pOldLocale = _strdup(setlocale(LC_CTYPE, NULL));
		//setlocale(LC_CTYPE, "chs");
		gReadFilePathName1 = fileDlg.GetPathName(); //得到完整的文件名和目录名拓展名
	}
	else
	{
		// 如果用户取消了保存操作，直接返回
		return;
	}

	CStdioFile file;
	CString a = L"\n";
	CString strText(_T(""));
	file.Open(gReadFilePathName1, CFile::modeCreate | CFile::modeWrite | CFile::typeText);

	GetDlgItemText(IDC_EDIT_m1, strText);
	strText += a;
	file.WriteString(strText);
	GetDlgItemText(IDC_EDIT_m2, strText);
	strText += a;
	file.WriteString(strText);
	GetDlgItemText(IDC_EDIT_m3, strText);
	strText += a;
	file.WriteString(strText);
	GetDlgItemText(IDC_EDIT_m4, strText);
	strText += a;
	file.WriteString(strText);
	GetDlgItemText(IDC_EDIT_m5, strText);
	strText += a;
	file.WriteString(strText);
	GetDlgItemText(IDC_EDIT_m6, strText);
	strText += a;
	file.WriteString(strText);
	GetDlgItemText(IDC_EDIT_m7, strText);
	strText += a;
	file.WriteString(strText);
	GetDlgItemText(IDC_EDIT_m8, strText);
	strText += a;
	file.WriteString(strText);
	GetDlgItemText(IDC_EDIT_m9, strText);
	strText += a;
	file.WriteString(strText);
	GetDlgItemText(IDC_EDIT_mCoe, strText);
	strText += a;
	file.WriteString(strText);
	GetDlgItemText(IDC_EDIT_mThre, strText);
	file.WriteString(strText);
	file.Close();
}


//装载算子
void CDlgFilter::OnBnClickedLoad()
{
	CString gReadFilePathName1;
	CString szFileName;

	CFileDialog dlg(true, _T(".txt"), _T("*.txt"), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, _T("文本文件 (*.txt)|*.txt||"), NULL);
	if (dlg.DoModal() == IDOK)
	{
		//获得文件名
		szFileName = dlg.GetPathName();
		//下面添加对文件的操作代码
	}
	///////////
	CString strLine, strTemp, result;
	int row = 0;
	//CString filename = L"算子.txt";
	CStdioFile file(szFileName, CFile::modeRead);
	CString a[12];
	while (file.ReadString(strLine))
	{
		char* str = (char*)strLine.GetBufferSetLength(strLine.GetLength());
		char* p;
		if (strLine != "")
		{
			a[row] = strLine;
			row++;
		}
	}
	GetDlgItem(IDC_EDIT_m1)->SetWindowText(a[0]);
	GetDlgItem(IDC_EDIT_m2)->SetWindowText(a[1]);
	GetDlgItem(IDC_EDIT_m3)->SetWindowText(a[2]);
	GetDlgItem(IDC_EDIT_m4)->SetWindowText(a[3]);
	GetDlgItem(IDC_EDIT_m5)->SetWindowText(a[4]);
	GetDlgItem(IDC_EDIT_m6)->SetWindowText(a[5]);
	GetDlgItem(IDC_EDIT_m7)->SetWindowText(a[6]);
	GetDlgItem(IDC_EDIT_m8)->SetWindowText(a[7]);
	GetDlgItem(IDC_EDIT_m9)->SetWindowText(a[8]);
	GetDlgItem(IDC_EDIT_mCoe)->SetWindowText(a[9]);
	GetDlgItem(IDC_EDIT_mThre)->SetWindowText(a[10]);
	file.Close();
}






//水平方向
void CDlgFilter::OnBnClickedRadio13()
{
	// TODO: 在此添加控件通知处理程序代码
	if (with_edge == 0)//sobel
	{
		//m_filter1_Control.SetCheck(BST_UNCHECKED);  // 设置为未选中状态
		m_operator1 = -1;
		m_operator2 = 0;
		m_operator3 = 1;
		m_operator4 = -2;
		m_operator5 = 0;
		m_operator6 = 2;
		m_operator7 = -1;
		m_operator8 = 0;
		m_operator9 = 1;
		m_coefficient = 1.0;
		m_constant = 0;

		m_filter_species = 7;//
		m_edge_direction = 1;
	}
	else if (with_edge == 1)//prewitt
	{
		//m_filter1_Control.SetCheck(BST_UNCHECKED);  // 设置为未选中状态
		m_operator1 = -1;
		m_operator2 = 0;
		m_operator3 = 1;
		m_operator4 = -1;
		m_operator5 = 0;
		m_operator6 = 1;
		m_operator7 = -1;
		m_operator8 = 0;
		m_operator9 = 1;
		m_coefficient = 1.0;
		m_constant = 0;

		m_filter_species = 8;
		m_edge_direction = 1;
	}
	else if (with_edge == 2) {
		m_operator1 = -1;
		m_operator2 = -1;
		m_operator3 = -1;
		m_operator4 = 2;
		m_operator5 = 2;
		m_operator6 = 2;
		m_operator7 = -1;
		m_operator8 = -1;
		m_operator9 = -1;
		m_coefficient = 1.0;
		m_constant = 0;

		m_filter_species = 9;
		m_edge_direction = 1;
	}
	//更新
	UpdateData(FALSE);
}

//45度
void CDlgFilter::OnBnClickedRadio14()
{
	// TODO: 在此添加控件通知处理程序代码
	if (with_edge == 2) {
		m_operator1 = -1;
		m_operator2 =-1;
		m_operator3 = 2;
		m_operator4 = -1;
		m_operator5 = 2;
		m_operator6 = -1;
		m_operator7 = 2;
		m_operator8 = -1;
		m_operator9 = -1;
		m_coefficient = 1.0;
		m_constant = 0;

		m_filter_species = 9;
		m_edge_direction = 2;
	}
	//更新
	UpdateData(FALSE);
}

//-45度
void CDlgFilter::OnBnClickedRadio15()
{
	// TODO: 在此添加控件通知处理程序代码
	if (with_edge == 2) {
		m_operator1 = 2;
		m_operator2 = -1;
		m_operator3 = -1;
		m_operator4 = -1;
		m_operator5 = 2;
		m_operator6 = -1;
		m_operator7 = -1;
		m_operator8 = -1;
		m_operator9 = 2;
		m_coefficient = 1.0;
		m_constant = 0;

		m_filter_species = 9;
		m_edge_direction = 3;
	}
	//更新
	UpdateData(FALSE);
}
