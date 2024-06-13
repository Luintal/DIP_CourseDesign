// CDlgLinerPara.cpp: 实现文件
//

#include "pch.h"
#include "MFCTest1.h"
#include "afxdialogex.h"
#include "CDlgLinerPara.h"


// CDlgLinerPara 对话框

IMPLEMENT_DYNAMIC(CDlgLinerPara, CDialogEx)

CDlgLinerPara::CDlgLinerPara(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_Dlg_LinerPara, pParent)
	, m_fA(0)
	, m_fB(0)
{

}

CDlgLinerPara::~CDlgLinerPara()
{
}

void CDlgLinerPara::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_A, m_fA);
	DDX_Text(pDX, IDC_EDIT_B, m_fB);
}


BEGIN_MESSAGE_MAP(CDlgLinerPara, CDialogEx)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_EN_KILLFOCUS(IDC_EDIT_A, &CDlgLinerPara::OnKillfocusEditA)
	ON_EN_KILLFOCUS(IDC_EDIT_B, &CDlgLinerPara::OnKillfocusEditB)
END_MESSAGE_MAP()


// CDlgLinerPara 消息处理程序
BOOL CDlgLinerPara::OnInitDialog()
{
	// 调用默认OnInitDialog函数
	CDialog::OnInitDialog();
	// 获取绘制参数曲线的标签
	CWnd* pWnd = GetDlgItem(IDC_COORD);
	// 计算接受鼠标事件的有效区域
	pWnd->GetClientRect(m_MouseRect);
	pWnd->ClientToScreen(&m_MouseRect);

	CRect rect;
	GetClientRect(rect);
	ClientToScreen(&rect);

	m_MouseRect.top -= rect.top;
	m_MouseRect.left -= rect.left;

	// 设置接受鼠标事件的有效区域
	m_MouseRect.top += 25;
	m_MouseRect.left += 10;
	m_MouseRect.bottom = m_MouseRect.top + 255;
	m_MouseRect.right = m_MouseRect.left + 256;

	// 初始化拖动状态
	m_bIsDraging = FALSE;

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CDlgLinerPara::OnKillfocusEditA()
{
	// 保存用户设置
	UpdateData(TRUE);

	// 重绘
	InvalidateRect(m_MouseRect, TRUE);

}


void CDlgLinerPara::OnKillfocusEditB()
{
	// 保存用户设置
	UpdateData(TRUE);

	// 重绘
	InvalidateRect(m_MouseRect, TRUE);

}


void CDlgLinerPara::OnLButtonDown(UINT nFlags, CPoint point)
{
	// 当用户单击鼠标左键开始拖动
	if (m_MouseRect.PtInRect(point))
	{
		// 保存当前鼠标位置
		m_p1 = point;

		// 转换坐标系
		m_p1.x = m_p1.x - m_MouseRect.left + 10;
		m_p1.y = m_p1.y - m_MouseRect.top + 25;

		// 设置拖动状态
		m_bIsDraging = TRUE;

		// 设置m_bDrawed为FALSE
		m_bDrawed = FALSE;

		// 更改光标
		::SetCursor(::LoadCursor(NULL, IDC_CROSS));

		// 开始跟踪鼠标事件（保证当鼠标移动到窗体外时也可以接收到鼠标释放事件）
		SetCapture();
	}

	// 默认单击鼠标左键处理事件
	//CDialog::OnLButtonDown(nFlags, point);

}


void CDlgLinerPara::OnMouseMove(UINT nFlags, CPoint point)
{
	// 判断当前光标是否在绘制区域
	if (m_MouseRect.PtInRect(point))
	{
		// 更改光标
		::SetCursor(::LoadCursor(NULL, IDC_CROSS));

		// 判断是否正在拖动
		if (m_bIsDraging)
		{
			// 获取绘图的标签
			CWnd* pWnd = GetDlgItem(IDC_COORD);

			// 获取设备上下文
			CDC* pDC = pWnd->GetDC();

			// 设置绘制方式为异或模式
			int nOldDrawMode = pDC->SetROP2(R2_XORPEN);

			// 创建新的画笔
			CPen* pPen = new CPen;
			pPen->CreatePen(PS_DOT, 1, RGB(0, 0, 0));

			// 选中新画笔
			CGdiObject* pOldPen = pDC->SelectObject(pPen);

			// 判断是否已经画过橡皮筋线
			if (m_bDrawed)
			{
				// 擦去以前的橡皮筋线
				pDC->MoveTo(m_p1);
				pDC->LineTo(m_p2);
			}

			// 保存当前的坐标
			m_p2 = point;

			// 转换坐标系
			m_p2.x = m_p2.x - m_MouseRect.left + 10;
			m_p2.y = m_p2.y - m_MouseRect.top + 25;

			// 绘制一条新橡皮筋线
			pDC->MoveTo(m_p1);
			pDC->LineTo(m_p2);

			// 设置m_bDrawed为TRUE
			m_bDrawed = TRUE;

			// 选回以前的画笔
			pDC->SelectObject(pOldPen);

			// 恢复成以前的绘制模式
			pDC->SetROP2(nOldDrawMode);

			delete pPen;
			ReleaseDC(pDC);
		}
	}
	else
	{
		// 判断是否正在拖动
		if (m_bIsDraging)
		{
			// 更改光标
			::SetCursor(::LoadCursor(NULL, IDC_NO));
		}
	}

	// 默认鼠标移动处理事件
	//CDialog::OnMouseMove(nFlags, point);

}


void CDlgLinerPara::OnLButtonUp(UINT nFlags, CPoint point)
{
	// 当用户释放鼠标左键停止拖动
	if (m_bIsDraging)
	{
		// 判断当前光标是否在绘制区域
		if (m_MouseRect.PtInRect(point))
		{
			// 保存当前鼠标位置
			m_p2 = point;

			// 转换坐标系
			m_p2.x = m_p2.x - m_MouseRect.left + 10;
			m_p2.y = m_p2.y - m_MouseRect.top + 25;

			if ((m_p1 != m_p2) && (m_p1.x != m_p2.x))
			{
				// 转换坐标系
				m_p1.x = m_p1.x - 10;
				m_p1.y = 280 - m_p1.y;
				m_p2.x = m_p2.x - 10;
				m_p2.y = 280 - m_p2.y;

				// 计算斜率和截距
				m_fA = (float)(m_p2.y - m_p1.y) / (m_p2.x - m_p1.x);
				m_fB = m_p1.y - m_fA * m_p1.x;

				// 保存变动
				UpdateData(FALSE);
			}

			// 重绘
			InvalidateRect(m_MouseRect, TRUE);
		}
		else
		{
			// 用户在绘制区域外放开鼠标左键

			// 获取绘图的标签
			CWnd* pWnd = GetDlgItem(IDC_COORD);

			// 获取设备上下文
			CDC* pDC = pWnd->GetDC();

			// 设置绘制方式为异或模式
			int nOldDrawMode = pDC->SetROP2(R2_XORPEN);

			// 创建新的画笔
			CPen* pPen = new CPen;
			pPen->CreatePen(PS_DOT, 1, RGB(0, 0, 0));

			// 选中新画笔
			CGdiObject* pOldPen = pDC->SelectObject(pPen);

			// 判断是否已经画过橡皮筋线
			if (m_bDrawed)
			{
				// 擦去以前的橡皮筋线
				pDC->MoveTo(m_p1);
				pDC->LineTo(m_p2);
			}

			// 选回以前的画笔
			pDC->SelectObject(pOldPen);

			// 恢复成以前的绘制模式
			pDC->SetROP2(nOldDrawMode);

			delete pPen;
			ReleaseDC(pDC);

		}

		// 解除对鼠标事件的跟踪
		::ReleaseCapture();

		// 重置拖动状态
		m_bIsDraging = FALSE;
	}

	// 默认释放鼠标左键处理事件
	//CDialog::OnLButtonUp(nFlags, point);

}


void CDlgLinerPara::OnPaint()
{
	// 字符串
	CString str;

	// 直线和坐标轴二个交点坐标
	int x1, y1, x2, y2;

	// 设备上下文
	CPaintDC dc(this);

	// 获取绘制坐标的文本框
	CWnd* pWnd = GetDlgItem(IDC_COORD);

	// 指针
	CDC* pDC = pWnd->GetDC();
	pWnd->Invalidate();
	pWnd->UpdateWindow();

	pDC->Rectangle(0, 0, 330, 300);

	// 创建画笔对象
	CPen* pPenRed = new CPen;

	// 红色画笔
	pPenRed->CreatePen(PS_SOLID, 2, RGB(255, 0, 0));

	// 创建画笔对象
	CPen* pPenBlue = new CPen;

	// 蓝色画笔
	pPenBlue->CreatePen(PS_SOLID, 2, RGB(0, 0, 255));

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
	pDC->TextOut(11, 25, str);

	// 绘制X轴箭头
	pDC->LineTo(315, 275);
	pDC->MoveTo(320, 280);
	pDC->LineTo(315, 285);

	// 绘制Y轴箭头
	pDC->MoveTo(10, 10);
	pDC->LineTo(5, 15);
	pDC->MoveTo(10, 10);
	pDC->LineTo(15, 15);

	// 更改成蓝色画笔
	pDC->SelectObject(pPenBlue);

	// 计算直线和坐标轴二个交点坐标
	if (m_fA >= 0)
	{
		if (((m_fA * 255 + m_fB) >= 0) && (m_fB < 255))
		{
			// 计算(x1, y1)坐标
			if (m_fB < 0)
			{
				x1 = (int)(-m_fB / m_fA + 0.5);
				y1 = 0;
			}
			else
			{
				x1 = 0;
				y1 = (int)(m_fB + 0.5);
			}

			// 计算(x2, y2)坐标
			if ((m_fA * 255 + m_fB) > 255)
			{
				x2 = (int)((255 - m_fB) / m_fA + 0.5);
				y2 = 255;
			}
			else
			{
				x2 = 255;
				y2 = (int)(255 * m_fA + m_fB + 0.5);
			}
		}
		else if (((m_fA * 255 + m_fB) < 0))
		{
			// 转换后所有象素值都小于0，直接设置为0
			x1 = 0;
			y1 = 0;
			x2 = 255;
			y2 = 0;
		}
		else
		{
			// 转换后所有象素值都大于255，直接设置为255
			x1 = 0;
			y1 = 255;
			x2 = 255;
			y2 = 255;
		}
	}
	else  // 斜率小于0
	{
		if ((m_fB > 0) && (255 * m_fA + m_fB < 255))
		{
			// 计算(x1, y1)坐标
			if (m_fB > 255)
			{
				x1 = (int)((255 - m_fB) / m_fA + 0.5);
				y1 = 255;
			}
			else
			{
				x1 = 0;
				y1 = (int)(m_fB + 0.5);
			}

			// 计算(x2, y2)坐标
			if ((m_fA * 255 + m_fB) < 0)
			{
				x2 = (int)(-m_fB / m_fA + 0.5);
				y2 = 0;
			}
			else
			{
				x2 = 255;
				y2 = (int)(255 * m_fA + m_fB + 0.5);
			}
		}
		else if (m_fB <= 0)
		{
			// 转换后所有象素值都小于0，直接设置为0
			x1 = 0;
			y1 = 0;
			x2 = 255;
			y2 = 0;
		}
		else
		{
			// 转换后所有象素值都大于255，直接设置为255
			x1 = 0;
			y1 = 255;
			x2 = 255;
			y2 = 255;
		}
	}

	// 绘制坐标值
	str.Format(L"(%d, %d)", x1, y1);
	pDC->TextOut(x1 + 10, 280 - y1 + 1, str);
	str.Format(L"(%d, %d)", x2, y2);
	pDC->TextOut(x2 + 10, 280 - y2 + 1, str);

	// 绘制用户指定的线性变换直线（注意转换坐标系）
	pDC->MoveTo(x1 + 10, 280 - y1);
	pDC->LineTo(x2 + 10, 280 - y2);

	// 恢复以前的画笔
	pDC->SelectObject(pOldPen);

	// 绘制边缘
	pDC->MoveTo(10, 25);
	pDC->LineTo(265, 25);
	pDC->LineTo(265, 280);

	// 删除新的画笔
	delete pPenRed;
	delete pPenBlue;

	// 不为绘图消息调用 CDialogEx::OnPaint()
}