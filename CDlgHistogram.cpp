// CDlgHistogram.cpp: 实现文件
//

#include "pch.h"
#include "MFCTest1.h"
#include "afxdialogex.h"
#include "CDlgHistogram.h"


// CDlgHistogram 对话框

IMPLEMENT_DYNAMIC(CDlgHistogram, CDialogEx)

CDlgHistogram::CDlgHistogram(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DlgHistogram, pParent)
	, m_iLowGray(0)
	, m_iHighGray(0)
{

}

CDlgHistogram::~CDlgHistogram()
{
}

void CDlgHistogram::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_Low, m_iLowGray); 
	DDV_MinMaxInt(pDX, m_iLowGray, 0, 255);
	DDX_Text(pDX, IDC_EDIT_High, m_iHighGray);
	DDV_MinMaxInt(pDX, m_iHighGray, 0, 255);
}


BEGIN_MESSAGE_MAP(CDlgHistogram, CDialogEx)
	ON_WM_PAINT()
	ON_EN_KILLFOCUS(IDC_EDIT_Low, &CDlgHistogram::OnEnKillfocusEditLow)
	ON_EN_KILLFOCUS(IDC_EDIT_High, &CDlgHistogram::OnEnKillfocusEditHigh)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_STN_CLICKED(IDC_COORD, &CDlgHistogram::OnStnClickedCoord)
END_MESSAGE_MAP()


// CDlgHistogram 消息处理程序
BOOL CDlgHistogram::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	// 指向源图像象素的指针
	unsigned char* lpSrc;

	// 循环变量
	LONG i;
	LONG j;

	// 调用默认OnInitDialog函数
	CDialog::OnInitDialog();

	// 获取绘制直方图的标签
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

	// 重置计数为0
	for (i = 0; i < 256; i++)
	{
		// 清零
		m_lCount[i] = 0;
	}

	// 图像每行的字节数
	//LONG m_lLineBytes;

	// 计算图像每行的字节数
	//lLineBytes = WIDTHBYTES(m_lWidth * 8);

	// 计算各个灰度值的计数
	for (i = 0; i < m_lHeight; i++)
	{
		for (j = 0; j < m_lWidth; j++)
		{
			lpSrc = (unsigned char*)m_lpDIBBits + m_lLineBytes * i + j;

			// 计数加1
			m_lCount[*(lpSrc)]++;
		}
	}

	// 初始化拖动状态
	m_iIsDraging = 0;

	// 返回TRUE


	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CDlgHistogram::OnPaint()
{
	//CPaintDC dc(this); // device context for painting
					   // TODO: 在此处添加消息处理程序代码
					   // 不为绘图消息调用 CDialogEx::OnPaint()
	// 字符串
	CString str;

	// 循环变量
	LONG i;

	// 最大计数
	LONG lMaxCount = 0;

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
	pPenRed->CreatePen(PS_SOLID, 1, RGB(255, 0, 0));

	// 创建画笔对象
	CPen* pPenBlue = new CPen;

	// 蓝色画笔
	pPenBlue->CreatePen(PS_SOLID, 1, RGB(0, 0, 255));

	// 创建画笔对象
	CPen* pPenGreen = new CPen;

	// 绿色画笔
	pPenGreen->CreatePen(PS_DOT, 1, RGB(0, 255, 0));

	// 选中当前红色画笔，并保存以前的画笔
	CGdiObject* pOldPen = pDC->SelectObject(pPenRed);

	// 绘制坐标轴
	pDC->MoveTo(10, 10);

	// 垂直轴
	pDC->LineTo(10, 280);

	// 水平轴
	pDC->LineTo(320, 280);

	// 写X轴刻度值
	str.Format(L"0");
	pDC->TextOut(10, 283, str);
	str.Format(L"50");
	pDC->TextOut(60, 283, str);
	str.Format(L"100");
	pDC->TextOut(110, 283, str);
	str.Format(L"150");
	pDC->TextOut(160, 283, str);
	str.Format(L"200");
	pDC->TextOut(210, 283, str);
	str.Format(L"255");
	pDC->TextOut(265, 283, str);

	// 绘制X轴刻度
	for (i = 0; i < 256; i += 5)
	{
		if ((i & 1) == 0)
		{
			// 10的倍数
			pDC->MoveTo(i + 10, 280);
			pDC->LineTo(i + 10, 284);
		}
		else
		{
			// 10的倍数
			pDC->MoveTo(i + 10, 280);
			pDC->LineTo(i + 10, 282);
		}
	}

	// 绘制X轴箭头
	pDC->MoveTo(315, 275);
	pDC->LineTo(320, 280);
	pDC->LineTo(315, 285);

	// 绘制X轴箭头
	pDC->MoveTo(10, 10);
	pDC->LineTo(5, 15);
	pDC->MoveTo(10, 10);
	pDC->LineTo(15, 15);

	// 计算最大计数值
	for (i = m_iLowGray; i <= m_iHighGray; i++)
	{
		// 判断是否大于当前最大值
		if (m_lCount[i] > lMaxCount)
		{
			// 更新最大值
			lMaxCount = m_lCount[i];
		}
	}

	// 输出最大计数值
	pDC->MoveTo(10, 25);
	pDC->LineTo(14, 25);
	str.Format(L"%d", lMaxCount);
	pDC->TextOut(11, 26, str);

	// 更改成绿色画笔
	pDC->SelectObject(pPenGreen);

	// 绘制窗口上下限
	pDC->MoveTo(m_iLowGray + 10, 25);
	pDC->LineTo(m_iLowGray + 10, 280);

	pDC->MoveTo(m_iHighGray + 10, 25);
	pDC->LineTo(m_iHighGray + 10, 280);

	// 更改成蓝色画笔
	pDC->SelectObject(pPenBlue);

	// 判断是否有计数
	if (lMaxCount > 0)
	{
		// 绘制直方图
		for (i = m_iLowGray; i <= m_iHighGray; i++)
		{
			pDC->MoveTo(i + 10, 280);
			pDC->LineTo(i + 10, 281 - (int)(m_lCount[i] * 256 / lMaxCount));
		}
	}

	// 恢复以前的画笔
	pDC->SelectObject(pOldPen);

	// 删除新的画笔
	delete pPenRed;
	delete pPenBlue;
	delete pPenGreen;

}


void CDlgHistogram::OnEnKillfocusEditLow()
{
	// TODO: 在此添加控件通知处理程序代码
	// 保存变动（控件中数值保存到成员变量中）
	UpdateData(TRUE);

	// 判断是否下限超过上限
	if (m_iLowGray > m_iHighGray)
	{
		// 互换
		int iTemp = m_iLowGray;
		m_iLowGray = m_iHighGray;
		m_iHighGray = iTemp;

		// 更新（成员变量中数值保存到控件中）
		UpdateData(FALSE);
	}

	// 重绘直方图
	InvalidateRect(m_MouseRect, TRUE);
}


void CDlgHistogram::OnEnKillfocusEditHigh()
{
	// TODO: 在此添加控件通知处理程序代码
	// 保存变动
	UpdateData(TRUE);

	// 判断是否下限超过上限
	if (m_iLowGray > m_iHighGray)
	{
		// 互换
		int iTemp = m_iLowGray;
		m_iLowGray = m_iHighGray;
		m_iHighGray = iTemp;

		// 更新
		UpdateData(FALSE);
	}

	// 重绘直方图
	InvalidateRect(m_MouseRect, TRUE);
}


void CDlgHistogram::OnLButtonDown(UINT nFlags, CPoint point)
{
	// // 当用户单击鼠标左键开始拖动

	// 判断是否在接受鼠标事件的有效区域中
	if (m_MouseRect.PtInRect(point))
	{
		if (point.x == (m_MouseRect.left + m_iLowGray))
		{

			// 设置拖动状态1，拖动下限
			m_iIsDraging = 1;

			// 更改光标
			::SetCursor(::LoadCursor(NULL, IDC_SIZEWE));
		}
		else if (point.x == (m_MouseRect.left + m_iHighGray))
		{

			// 设置拖动状态为2，拖动上限
			m_iIsDraging = 2;

			// 更改光标
			::SetCursor(::LoadCursor(NULL, IDC_SIZEWE));
		}
	}

	// 默认单击鼠标左键处理事件
	CDialog::OnLButtonDown(nFlags, point);


}


void CDlgHistogram::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	// 当用户释放鼠标左键停止拖动
	if (m_iIsDraging != 0)
	{
		// 重置拖动状态
		m_iIsDraging = 0;
	}

	// 默认释放鼠标左键处理事件
	CDialog::OnLButtonUp(nFlags, point);

}


void CDlgHistogram::OnMouseMove(UINT nFlags, CPoint point)
{
	// // 判断是否在接受鼠标事件的有效区域中
	if (m_MouseRect.PtInRect(point))
	{
		// 判断是否正在拖动
		if (m_iIsDraging != 0)
		{
			// 判断正在拖动上限还是下限
			if (m_iIsDraging == 1)
			{
				// 判断是否下限<上限
				if (point.x - m_MouseRect.left < m_iHighGray)
				{
					// 更改下限
					m_iLowGray = point.x - m_MouseRect.left;
				}
				else
				{
					// 下限拖过上限，设置为上限-1
					m_iLowGray = m_iHighGray - 1;

					// 重设鼠标位置
					point.x = m_MouseRect.left + m_iHighGray - 1;
				}
			}
			else
			{
				// 正在拖动上限

				// 判断是否上限>下限
				if (point.x - m_MouseRect.left > m_iLowGray)
				{
					// 更改下限
					m_iHighGray = point.x - m_MouseRect.left;
				}
				else
				{
					// 下限拖过上限，设置为下限＋1
					m_iHighGray = m_iLowGray + 1;

					// 重设鼠标位置
					point.x = m_MouseRect.left + m_iLowGray + 1;
				}
			}

			// 更改光标
			::SetCursor(::LoadCursor(NULL, IDC_SIZEWE));

			// 更新
			UpdateData(FALSE);

			// 重绘直方图
			InvalidateRect(m_MouseRect, TRUE);
		}
		else if (point.x == (m_MouseRect.left + m_iLowGray) || point.x == (m_MouseRect.left + m_iHighGray))
		{
			// 更改光标
			::SetCursor(::LoadCursor(NULL, IDC_SIZEWE));
		}
	}

	// 默认鼠标移动处理事件
	CDialog::OnMouseMove(nFlags, point);


}


void CDlgHistogram::OnStnClickedCoord()
{
	// TODO: 在此添加控件通知处理程序代码

}
