// DIg_Tran_L.cpp: 实现文件
//

#include "pch.h"
#include "MFCTest1.h"
#include "afxdialogex.h"
#include "DIg_Tran_L.h"


// DIg_Tran_L 对话框

IMPLEMENT_DYNAMIC(DIg_Tran_L, CDialogEx)

DIg_Tran_L::DIg_Tran_L(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIg_Tran_L, pParent)
	, m_thresholdL(127)
{

}

DIg_Tran_L::~DIg_Tran_L()
{
}

void DIg_Tran_L::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_ThresholdL, m_thresholdL);
}


BEGIN_MESSAGE_MAP(DIg_Tran_L, CDialogEx)
	ON_WM_PAINT()
	ON_EN_KILLFOCUS(IDC_ThresholdL, &DIg_Tran_L::OnEnKillfocusThresholdL)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()


// DIg_Tran_L 消息处理程序

BOOL DIg_Tran_L::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	//获取绘制图形的标签
	CWnd* pWnd = GetDlgItem(IDC_COORDL);
	//计算接受鼠标事件的有效区域
	pWnd->GetClientRect(m_MouseRect);
	pWnd->ClientToScreen(&m_MouseRect);

	CRect rect;
	GetClientRect(rect);
	ClientToScreen(&rect);

	m_MouseRect.top -= rect.top;
	m_MouseRect.left -= rect.left;
	//设置接受鼠标事件的有效区域
	m_MouseRect.top += 25;
	m_MouseRect.left += 10;
	m_MouseRect.bottom = m_MouseRect.top + 255;
	m_MouseRect.right = m_MouseRect.left + 256;
	//初始化拖动状态
	m_bIsDrawing = FALSE;

	return true;
}

void DIg_Tran_L::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	// 获取绘制坐标的文本框
	CWnd* pWnd = GetDlgItem(IDC_COORDL);
	// 字符串
	CString str;
	CPoint pLeftTop, pRightTop, pCenterBottom, pTopCenter;
	// 指针
	CDC* pDC = pWnd->GetDC();
	pWnd->Invalidate();
	pWnd->UpdateWindow();
	// x1(left),y1(top),x2(right),y2(bottom)
	pDC->Rectangle(0, 0, 330, 300);
	// 创建画笔对象
	CPen* pPenRed = new CPen;
	// 红色画笔，红绿蓝
	pPenRed->CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
	// 创建画笔对象
	CPen* pPenBlue = new CPen;
	// 蓝色画笔，红绿蓝
	pPenBlue->CreatePen(PS_SOLID, 2, RGB(0, 0, 255));
	// 创建画笔对象
	CPen* pPenGreen = new CPen;
	// 绿色画笔，红绿蓝
	pPenGreen->CreatePen(PS_DOT, 1, RGB(0, 255, 0));
	// 选中当前红色画笔，并保存以前的画笔
	CGdiObject* pOldPen = pDC->SelectObject(pPenRed);
	// 绘制坐标轴
	pDC->MoveTo(10, 10);
	// 垂直轴
	pDC->LineTo(10, 280);
	// 水平轴
	pDC->LineTo(320, 280);
	// 写坐标
	str.Format(L"0");
	pDC->TextOut(10, 281, str);
	str.Format(L"255");
	pDC->TextOut(265, 281, str);
	pDC->TextOutW(11, 25, str);
	// 绘制X箭头
	pDC->LineTo(315, 275);
	pDC->MoveTo(320, 280);
	pDC->LineTo(315, 285);
	// 绘制Y箭头
	pDC->MoveTo(10, 10);
	pDC->LineTo(5, 15);
	pDC->MoveTo(10, 10);
	pDC->LineTo(15, 15);

	// 更改成蓝色画笔
	pDC->SelectObject(pPenBlue);
	// 画两条变换线，形成L型
	pLeftTop.x = 10;
	pLeftTop.y = 25;
	pRightTop.x = 266;
	pRightTop.y = 280;
	pCenterBottom.x = 10 + m_thresholdL; // 底部中心点的 X 坐标
	pCenterBottom.y = 280; // 底部中心点的 Y 坐标
	pDC->MoveTo(pLeftTop);
	pDC->LineTo(pCenterBottom); // 从左上角到底部中心点
	pDC->MoveTo(pRightTop);
	pDC->LineTo(pCenterBottom); // 从右上角到底部中心点

	// 更改成绿色画笔
	pDC->SelectObject(pPenGreen);
	// 画一条从底部中心点到最上面的虚线
	pTopCenter.x = pCenterBottom.x; // 最上面的中心点的 X 坐标与底部中心点相同
	pTopCenter.y = 35; // 最上面的中心点的 Y 坐标
	pDC->MoveTo(pCenterBottom);
	pDC->LineTo(pTopCenter); // 从底部中心点到最上面的中心点
}


void DIg_Tran_L::OnEnKillfocusThresholdL()
{
	// TODO: 在此添加控件通知处理程序代码
	//保存用户设置
	UpdateData(TRUE);
	//重绘
	InvalidateRect(m_MouseRect, TRUE);
}

void DIg_Tran_L::OnLButtonDown(UINT nFlags, CPoint point)
{
	// 当用户单击鼠标左键开始拖动
	//判断是否在有效区域
	if (m_MouseRect.PtInRect(point))
	{
		if (point.x == (m_MouseRect.left + m_thresholdL))
		{
			//设置拖动状态
			m_bIsDrawing = TRUE;
			//更改光标
			::SetCursor(::LoadCursor(NULL, IDC_SIZEWE));
		}
	}

	//默认
	CDialogEx::OnLButtonDown(nFlags, point);
}

void DIg_Tran_L::OnLButtonUp(UINT nFlags, CPoint point)
{
	// 当用户释放鼠标左键停止拖动
	if (m_bIsDrawing)
	{
		//重新设置拖动状态
		m_bIsDrawing = FALSE;
	}
	//默认
	CDialogEx::OnLButtonUp(nFlags, point);
}

void DIg_Tran_L::OnMouseMove(UINT nFlags, CPoint point)
{
	// 判断当前光标是否在绘制区域
	if (m_MouseRect.PtInRect(point))
	{
		//判断是否在拖动
		if (m_bIsDrawing)
		{
			//更改阈值
			m_thresholdL = (BYTE)(point.x - m_MouseRect.left);
			//更改光标
			::SetCursor(::LoadCursor(NULL, IDC_SIZEWE));
			//更新
			UpdateData(FALSE);
			//重绘
			InvalidateRect(m_MouseRect, TRUE);
		}
		else if (point.x == (m_MouseRect.left + m_thresholdL))
		{
			//更改光标
			::SetCursor(::LoadCursor(NULL, IDC_SIZEWE));
		}
	}
	//默认
	CDialogEx::OnMouseMove(nFlags, point);
}


