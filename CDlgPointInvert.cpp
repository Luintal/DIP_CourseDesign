// CDlgPointInvert.cpp: 实现文件
//

#include "pch.h"
#include "MFCTest1.h"
#include "afxdialogex.h"
#include "CDlgPointInvert.h"


// CDlgPointInvert 对话框

IMPLEMENT_DYNAMIC(CDlgPointInvert, CDialogEx)

CDlgPointInvert::CDlgPointInvert(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DlgPointInvert, pParent)
{

}

CDlgPointInvert::~CDlgPointInvert()
{
}

void CDlgPointInvert::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgPointInvert, CDialogEx)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CDlgPointInvert 消息处理程序

void CDlgPointInvert::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialogEx::OnPaint()

//获取绘制坐标的文本框
	CWnd* pWnd = GetDlgItem(IDC_STATIC);
	//字符串
	CString str;
	CPoint pLeft, pRight, pCenterTop, pCenterBottom;
	//指针
	CDC* pDC = pWnd->GetDC();
	pWnd->Invalidate();
	pWnd->UpdateWindow();
	//x1(left),y1(top),x2(right),y2(bottom)
	pDC->Rectangle(0, 0, 330, 300);
	//创建画笔对象
	CPen* pPenRed = new CPen;
	//红色画笔，红蓝
	pPenRed->CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
	//创建画笔对象
	CPen* pPenBlue = new CPen;
	//蓝色画笔，红蓝
	pPenBlue->CreatePen(PS_SOLID, 2, RGB(0, 0, 255));
	//选中当前红色画笔，并保存以前的画笔
	CGdiObject* pOldPen = pDC->SelectObject(pPenRed);
	//绘制坐标轴
	pDC->MoveTo(10, 5);
	//垂直轴
	pDC->LineTo(10, 275);
	//水平轴
	pDC->LineTo(320, 275);
	//写坐标
	str.Format(L"0");
	pDC->TextOut(10, 276, str);
	str.Format(L"255");
	pDC->TextOut(265, 276, str);
	pDC->TextOutW(11, 20, str);
	//绘制X箭头
	pDC->LineTo(315, 270);
	pDC->MoveTo(320, 275);
	pDC->LineTo(315, 280);
	//绘制Y箭头
	pDC->MoveTo(10, 5);
	pDC->LineTo(5, 10);
	pDC->MoveTo(10, 5);
	pDC->LineTo(15, 10);
	////更改成绿色画笔,画垂直线

	//pDC->SelectObject(pPenGreen);
	//pCenterTop.x = 10 + m_threshold;//128;
	//pCenterTop.y = 25;

	//pCenterBottom.x = 10 + m_threshold;//128;
	//pCenterBottom.y = 280;
	//pDC->MoveTo(pCenterTop);
	//pDC->LineTo(pCenterBottom);

	//更改成蓝色画笔
	pDC->SelectObject(pPenBlue);
	//画两条变换线，没有计算斜率,没有交互
	pLeft.x = 10;
	pLeft.y = 10;
	//pDC->MoveTo(10,280);
	pDC->MoveTo(pLeft);
	//pCenterTop.x = 10 + m_threshold;//128;
	//pCenterTop.y = 25;
	////pDC->LineTo(138,25);
	//pDC->LineTo(pCenterTop);
	pRight.x = 260;
	pRight.y = 275;
	//pDC->LineTo(265,280);
	pDC->LineTo(pRight);

}


BOOL CDlgPointInvert::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
