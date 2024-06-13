// CDlgPointThre.cpp: 实现文件
//

#include "pch.h"
#include "MFCTest1.h"
#include "afxdialogex.h"
#include "CDlgPointThre.h"
#include "DIBAPI.h"
#include <vector>
#include "MFCTest1View.h"

// CDlgPointThre 对话框

IMPLEMENT_DYNAMIC(CDlgPointThre, CDialogEx)

CDlgPointThre::CDlgPointThre(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DLG_PointThre, pParent)
	, m_bThre(0)
{
	m_AMode = -1;
	
}

CDlgPointThre::~CDlgPointThre()
{
}

void CDlgPointThre::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_Thre, m_bThre);
	DDV_MinMaxByte(pDX, m_bThre, 0, 255);
	
}


BEGIN_MESSAGE_MAP(CDlgPointThre, CDialogEx)
	ON_EN_KILLFOCUS(IDC_EDIT_Thre, &CDlgPointThre::OnEnKillfocusEditThre)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_RADIO1, &CDlgPointThre::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &CDlgPointThre::OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_RADIO3, &CDlgPointThre::OnBnClickedRadio3)
	ON_BN_CLICKED(IDC_RADIO4, &CDlgPointThre::OnBnClickedRadio4)
	ON_BN_CLICKED(IDC_PreviewImg, &CDlgPointThre::OnBnClickedPreviewImg)
	ON_BN_CLICKED(IDC_RestoreImg, &CDlgPointThre::OnBnClickedRestoreImg)
	
	ON_BN_CLICKED(IDC_CalcuThre, &CDlgPointThre::OnBnClickedCalcuthre)
	
	ON_BN_CLICKED(IDC_AddColor, &CDlgPointThre::OnBnClickedAddcolor)
END_MESSAGE_MAP()


// CDlgPointThre 消息处理程序
BOOL CDlgPointThre::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	//获取绘制直方图的标签
	CWnd* pWnd = GetDlgItem(IDC_COORD);

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
	m_bIsDraging = FALSE;

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CDlgPointThre::OnEnKillfocusEditThre()
{
	// TODO: 在此添加控件通知处理程序代码
	//更新
	UpdateData(TRUE);

	//重绘
	InvalidateRect(m_MouseRect, TRUE);
}



void CDlgPointThre::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//当用户单击鼠标左键开始拖动

	//判断是否在有效区域中
	if (m_MouseRect.PtInRect(point))
	{
		if (point.x == (m_MouseRect.left + m_bThre))
		{
			//设置拖动状态
			m_bIsDraging = TRUE;

			//更改光标
			::SetCursor(::LoadCursor(NULL, IDC_SIZEWE));
		}
	}

	CDialogEx::OnLButtonDown(nFlags, point);
}


void CDlgPointThre::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//当用户释放鼠标左键停止拖动
	if (m_bIsDraging)
	{
		//重置拖动状态
		m_bIsDraging = FALSE;
	}

	CDialogEx::OnLButtonUp(nFlags, point);
}


void CDlgPointThre::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//判断当前光标是否在绘制区域
	if (m_MouseRect.PtInRect(point))
	{
		//判断是否正在拖动
		if (m_bIsDraging)
		{
			//更改阈值
			m_bThre = (BYTE)(point.x - m_MouseRect.left);

			//更改光标
			::SetCursor(::LoadCursor(NULL, IDC_SIZEWE));

			//更新
			UpdateData(FALSE);

			//重绘
			InvalidateRect(m_MouseRect, TRUE);
		}
		else if (point.x == (m_MouseRect.left + m_bThre))
		{
			//更改光标
			::SetCursor(::LoadCursor(NULL, IDC_SIZEWE));
		}
	}
	CDialogEx::OnMouseMove(nFlags, point);
}


void CDlgPointThre::OnPaint()
{
	//字符串
	CString str;

	//设备上下文
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialogEx::OnPaint()

//获取绘制坐标的文本框
	CWnd* pWnd = GetDlgItem(IDC_COORD);

	//指针
	CDC* pDC = pWnd->GetDC();
	pWnd->Invalidate();
	pWnd->UpdateWindow();

	pDC->Rectangle(0, 0, 330, 300);

	//创建画笔对象
	CPen* pPenRed = new CPen;

	//红色画笔
	pPenRed->CreatePen(PS_SOLID, 2, RGB(255, 0, 0));

	//创建画笔对象
	CPen* pPenBlue = new CPen;

	//蓝色画笔
	pPenBlue->CreatePen(PS_SOLID, 2, RGB(0, 0, 255));

	//创建画笔对象
	CPen* pPenGreen = new CPen;

	//绿色画笔
	pPenGreen->CreatePen(PS_DOT, 1, RGB(0, 255, 0));

	//选中当前红色画笔，并保存以前的画笔
	CGdiObject* pOldPen = pDC->SelectObject(pPenRed);

	//绘制坐标轴
	pDC->MoveTo(10, 10);

	//垂直轴
	pDC->LineTo(10, 280);

	//水平轴
	pDC->LineTo(320, 280);

	//写坐标
	str.Format(L"0");
	pDC->TextOut(10, 281, str);
	str.Format(L"255");
	pDC->TextOut(265, 281, str);
	pDC->TextOut(11, 25, str);

	//绘制x轴箭头
	pDC->LineTo(315, 275);
	pDC->MoveTo(320, 280);
	pDC->LineTo(315, 285);

	//绘制Y轴箭头
	pDC->MoveTo(10, 10);
	pDC->LineTo(5, 15);
	pDC->MoveTo(10, 10);
	pDC->LineTo(15, 15);

	//更改成绿色画笔
	pDC->SelectObject(pPenGreen);

	//绘制窗口阈值线
	pDC->MoveTo(m_bThre + 10, 25);
	pDC->LineTo(m_bThre + 10, 280);

	//更改成蓝色画笔
	pDC->SelectObject(pPenBlue);

	str.Format(L"%d", m_bThre);
	pDC->TextOut(m_bThre + 10, 281, str);

	pDC->MoveTo(10, 280);
	pDC->LineTo(m_bThre + 10, 280);
	pDC->LineTo(m_bThre + 10, 25);
	pDC->LineTo(265, 25);

	pDC->SelectObject(pOldPen);

	pDC->MoveTo(10, 25);
	pDC->LineTo(265, 25);
	pDC->LineTo(265, 280);

	delete pPenRed;
	delete pPenBlue;
	delete pPenGreen;

}

//迭代法
void CDlgPointThre::OnBnClickedRadio1()
{
	// TODO: 在此添加控件通知处理程序代码
	m_AMode = 0;

}

//大津法
int WINAPI OTSUDIB(LPSTR lpDIBBits, LONG lWidth, LONG lHeight)
{
	// 指向源图像的指针
	LPSTR	lpSrc;

	//循环变量
	long i, j, t;
	//用于计算区域灰度平均值的中间变量
	long lP1, lP2, lS1, lS2;

	//像素值
	unsigned char pixel;

	//直方图数组
	long lHistogram[256];

	//阈值，最大灰度值与最小灰度值，两个区域的平均灰度值
	unsigned char iThreshold, iNewThreshold, iMaxGrayValue, iMinGrayValue, iMean1GrayValue, iMean2GrayValue;

	//前景点数占图像比例，背景点数占图像比例
	double w0, w1;
	//方差
	double G = 0, tempG = 0;

	// 图像每行的字节数
	LONG lLineBytes;

	// 计算图像每行的字节数
	lLineBytes = WIDTHBYTES(lWidth * 8);

	for (i = 0; i < 256; i++)
	{
		lHistogram[i] = 0;
	}
	//获得直方图
	iMaxGrayValue = 0;
	iMinGrayValue = 255;
	for (i = 0; i < lWidth; i++)
	{
		for (j = 0; j < lHeight; j++)
		{
			// 指向源图像倒数第j行，第i个象素的指针			
			lpSrc = (char*)lpDIBBits + lLineBytes * j + i;

			pixel = (unsigned char)*lpSrc;

			lHistogram[pixel]++;
			//修改最大，最小灰度值
			if (iMinGrayValue > pixel)
			{
				iMinGrayValue = pixel;
			}
			if (iMaxGrayValue < pixel)
			{
				iMaxGrayValue = pixel;
			}
		}
	}

	for (t = iMinGrayValue; t < iMaxGrayValue; t++)
	{
		iNewThreshold = t;
		lP1 = 0;
		lP2 = 0;
		lS1 = 0;
		lS2 = 0;
		//求两个区域的灰度平均值
		for (i = iMinGrayValue; i <= iNewThreshold; i++)
		{
			lP1 += lHistogram[i] * i;
			lS1 += lHistogram[i];
		}

		iMean1GrayValue = (unsigned char)(lP1 / lS1);
		w0 = (double)(lS1) / (lWidth * lHeight);

		for (i = iNewThreshold + 1; i <= iMaxGrayValue; i++)
		{
			lP2 += lHistogram[i] * i;
			lS2 += lHistogram[i];
		}
		iMean2GrayValue = (unsigned char)(lP2 / lS2);
		w1 = 1 - w0;

		G = (double)w0 * w1 * (iMean1GrayValue - iMean2GrayValue) * (iMean1GrayValue - iMean2GrayValue);
		if (G > tempG)
		{
			tempG = G;
			iThreshold = iNewThreshold;
		}
	}
	return iThreshold;
}

void CDlgPointThre::OnBnClickedRadio2()
{
	
	m_AMode = 1;
	
}

//最大熵阈值分割法
void CDlgPointThre::OnBnClickedRadio3()
{
	// TODO: 在此添加控件通知处理程序代码
	
	m_AMode = 2;
	
}

// 自适应阈值分割法
void RegionSegAdaptive(LPSTR lpDIBBits, LONG lWidth, LONG lHeight) {
	const int NUM_ROWS = 2;  // 子图像的行数
	const int NUM_COLS = 2;  // 子图像的列数
	LONG lLineBytes = WIDTHBYTES(lWidth * 8);  // 每行的字节数
	int subImageWidth = lWidth / NUM_COLS;    // 子图像的宽度
	int subImageHeight = lHeight / NUM_ROWS;  // 子图像的高度

	// 遍历每个子图像
	for (int row = 0; row < NUM_ROWS; ++row) {
		for (int col = 0; col < NUM_COLS; ++col) {
			int startX = col * subImageWidth;
			int startY = row * subImageHeight;
			int endX = startX + subImageWidth;
			int endY = startY + subImageHeight;

			unsigned char minPixel = 255;
			unsigned char maxPixel = 0;

			// 遍历子图像计算最大值和最小值
			for (int y = startY; y < endY; ++y) {
				for (int x = startX; x < endX; ++x) {
					unsigned char* pixel = (unsigned char*)(lpDIBBits + y * lLineBytes + x);
					if (*pixel < minPixel) minPixel = *pixel;
					if (*pixel > maxPixel) maxPixel = *pixel;
				}
			}

			// 计算阈值：最大值和最小值的平均
			unsigned char threshold = (minPixel + maxPixel) / 2;

			// 应用阈值分割子图像
			for (int y = startY; y < endY; ++y) {
				for (int x = startX; x < endX; ++x) {
					unsigned char* pixel = (unsigned char*)(lpDIBBits + y * lLineBytes + x);
					*pixel = (*pixel < threshold) ? 0 : 255;
				}
			}
		}
	}
}


void CDlgPointThre::OnBnClickedRadio4()
{
	
	m_AMode = 3;
	m_bThre = 0;
	InvalidateRect(m_MouseRect, TRUE);
}

//预览图像
void CDlgPointThre::OnBnClickedPreviewImg()
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

	//循环变量
	LONG i, j;

	//指向源图像的指针
	unsigned char* lpSrc;

	//进行阈值变换
	if (m_AMode != 3) {
		//每行
		for (i = 0; i < lSrcHeight; i++)
		{
			//每列
			for (j = 0; j < lSrcWidth; j++)
			{
				//指向DIB第i行，第j个像素的指针
				lpSrc = (unsigned char*)lpSrcStartBits + lSrcLineBytes * (lSrcHeight - 1 - i) + j;

				//判断是否小于阈值
				if ((*lpSrc) < m_bThre)
				{
					//直接赋值为0
					*lpSrc = 0;
				}
				else
				{
					//直接赋值为255
					*lpSrc = 255;
				}
			}
		}
	}
	

	//设置脏标记
	pDoc->SetModifiedFlag(TRUE);

	//更新视图
	pDoc->UpdateAllViews(NULL);
}

//恢复图像
void CDlgPointThre::OnBnClickedRestoreImg()
{
	// TODO: 在此添加控件通知处理程序代码
	CEdit* edit = (CEdit*)GetDlgItem(IDC_EDIT_Thre);
	edit->ShowWindow(true); //显示该控件
	pDoc->OnImgrestore();
	//将4个radio失选
	CButton* pButton = (CButton*)GetDlgItem(IDC_RADIO1);
	pButton->SetCheck(0);
	pButton = (CButton*)GetDlgItem(IDC_RADIO2);
	pButton->SetCheck(0);
	pButton = (CButton*)GetDlgItem(IDC_RADIO3);
	pButton->SetCheck(0);
	pButton = (CButton*)GetDlgItem(IDC_RADIO4);
	pButton->SetCheck(0);
	m_bThre = 128; // 更新 m_bThre 为128
	UpdateData(FALSE);

	//重绘
	InvalidateRect(m_MouseRect, TRUE);
}





void CDlgPointThre::OnBnClickedCalcuthre()
{
	// TODO: 在此添加控件通知处理程序代码
	long	lSrcLineBytes;		//图象每行的字节数
	long	lSrcWidth;      //图象的宽度和高度
	long	lSrcHeight;
	int     lpSrcBitCount;       //图像的位深
	LPSTR	lpSrcDib;		//指向源图象的指针	
	LPSTR	lpSrcStartBits;	//指向源像素的指针

	//锁定DIB
	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());

	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);			// 找到DIB图象像素起始位置	
	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);					// 获取图象的宽度		
	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);					// 获取图象的高度	
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);                    //获取图像位深
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount);		// 计算图象每行的字节数

	CEdit* edit = (CEdit*)GetDlgItem(IDC_EDIT_Thre);

	
	if (m_AMode == 0) {
		//迭代法
		edit->ShowWindow(true); //显示该控件
		//阈值，最大灰度值与最小灰度值，两个区域的平均灰度值
		unsigned char iThreshold, iNewThreshold, iMaxGrayValue, iMinGrayValue, iMean1GrayValue, iMean2GrayValue;

		//迭代次数
		int iIterationTimes;

		//用于计算区域灰度平均值的中间变量
		long lP1, lP2, lS1, lS2;

		//直方图数组
		long lHistogram[256];

		//循环变量
		long i;
		long j;

		//像素值
		unsigned char pixel;

		// 指向源图像的指针
		LPSTR	lpSrc;

		// 指向缓存图像的指针
		LPSTR	lpDst;

		for (i = 0; i < 256; i++)
		{
			lHistogram[i] = 0;
		}

		//获得直方图
		iMaxGrayValue = 0;
		iMinGrayValue = 255;
		for (i = 0; i < lSrcWidth; i++)
		{
			for (j = 0; j < lSrcHeight; j++)
			{
				// 指向源图像倒数第j行，第i个象素的指针			
				lpSrc = (char*)lpSrcDib + lSrcLineBytes * j + i;

				pixel = (unsigned char)*lpSrc;

				lHistogram[pixel]++;
				//修改最大，最小灰度值
				if (iMinGrayValue > pixel)
				{
					iMinGrayValue = pixel;
				}
				if (iMaxGrayValue < pixel)
				{
					iMaxGrayValue = pixel;
				}
			}
		}

		//迭代求最佳阈值
		iNewThreshold = (iMinGrayValue + iMaxGrayValue) / 2;
		iThreshold = 0;

		for (iIterationTimes = 0; iThreshold != iNewThreshold && iIterationTimes < 100; iIterationTimes++)
		{
			iThreshold = iNewThreshold;
			lP1 = 0;
			lP2 = 0;
			lS1 = 0;
			lS2 = 0;
			//求两个区域的灰度平均值
			for (i = iMinGrayValue; i < iThreshold; i++)
			{
				lP1 += lHistogram[i] * i;
				lS1 += lHistogram[i];
			}
			iMean1GrayValue = (unsigned char)(lP1 / lS1);
			for (i = iThreshold + 1; i < iMaxGrayValue; i++)
			{
				lP2 += lHistogram[i] * i;
				lS2 += lHistogram[i];
			}
			iMean2GrayValue = (unsigned char)(lP2 / lS2);
			iNewThreshold = (iMean1GrayValue + iMean2GrayValue) / 2;
		}

		m_bThre = iThreshold;
		UpdateData(FALSE);
		//重绘
		InvalidateRect(m_MouseRect, TRUE);
	}
	else if (m_AMode == 1) {
		//大津法
	
		edit->ShowWindow(true); //显示该控件
		m_bThre = OTSUDIB(lpSrcStartBits, lSrcWidth, lSrcHeight);
		UpdateData(FALSE);
		//重绘
		InvalidateRect(m_MouseRect, TRUE);
	}
	else if (m_AMode == 2) {
		//最大熵阈值分割法
		edit->ShowWindow(true); //显示该控件
		//直方图数组
		long lHistogram[256];

		//循环变量
		long i;
		long j;

		//像素值
		unsigned char pixel;

		// 指向源图像的指针
		LPSTR	lpSrc;

		// 指向缓存图像的指针
		LPSTR	lpDst;

		for (i = 0; i < 256; i++)
		{
			lHistogram[i] = 0;
		}

		//获得直方图
		for (i = 0; i < lSrcWidth; i++)
		{
			for (j = 0; j < lSrcHeight; j++)
			{
				// 指向源图像倒数第j行，第i个象素的指针			
				lpSrc = (char*)lpSrcDib + lSrcLineBytes * j + i;

				pixel = (unsigned char)*lpSrc;

				lHistogram[pixel]++;
			}
		}
		int x, q, HistSize = 256, qMax = -1;
		double NormalizeHist[256] = { 0 }, H01 = 0, H0 = 0, H1 = 0, P1 = 0, P0 = 0, Hmax = -9999;
		double S1[256] = { 0 }, S2[256] = { 0 };

		for (x = 0; x < HistSize; x++)
			NormalizeHist[x] = lHistogram[x] / (double)(lSrcWidth * lSrcHeight);

		int y;

		double s0 = 0, s1;
		for (y = 0; y < HistSize; y++)
		{
			if (NormalizeHist[y] > 0)
			{
				s0 = s0 + NormalizeHist[y] * log(NormalizeHist[y]);
			}
			S1[y] = s0;
		}

		s1 = 0;
		for (y = HistSize - 1; y >= 0; y--)
		{
			S2[y] = s1;
			if (NormalizeHist[y] > 0)
			{
				s1 = s1 + NormalizeHist[y] * log(NormalizeHist[y]);
			}
		}

		for (q = 0; q < HistSize - 1; q++)
		{
			P0 += NormalizeHist[q];
			P1 = 1 - P0;

			if (P0 > 0)
				H0 = -(1 * S1[q]) / P0 + log(P0);
			else
				P0 = 0;

			if (P1 > 0)
				H1 = -(1 * S2[q]) / P1 + log(P1);
			else
				H1 = 0;

			H01 = H0 + H1;

			if (H01 > Hmax)
			{
				Hmax = H01;
				qMax = q;
			}

		}
		m_bThre = qMax;
		UpdateData(FALSE);

		//重绘
		InvalidateRect(m_MouseRect, TRUE);
	}
	else if (m_AMode == 3) {
		//自适应阈值分割法
		
		edit->ShowWindow(FALSE); //禁用该控件
		RegionSegAdaptive(lpSrcStartBits, lSrcWidth, lSrcHeight);
		UpdateData(FALSE);
		InvalidateRect(m_MouseRect, TRUE);
	}
	else if (m_AMode == -1) {
		//重绘
		edit->ShowWindow(TRUE); //该控件
		InvalidateRect(m_MouseRect, TRUE);
	}
}




void CDlgPointThre::OnBnClickedAddcolor()
{
	// 打开颜色选择对话框
	CColorDialog colorDlg;
	if (colorDlg.DoModal() == IDOK)
	{
		// 获取选择的颜色
		COLORREF color = colorDlg.GetColor();

		// 锁定全局内存对象以获取图像
		LPSTR lpSrcDib = (LPSTR)::GlobalLock((HGLOBAL)pDoc->GetHObject());
		if (!lpSrcDib)
		{
			return;
		}

		// 获取图像信息
		LPSTR lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);
		long lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);
		long lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);
		int lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);
		long lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount);

		// 计算前景和背景像素数量
		int foregroundCount = 0;
		int backgroundCount = 0;
		for (int i = 0; i < lSrcHeight; i++)
		{
			for (int j = 0; j < lSrcWidth; j++)
			{
				unsigned char* pixel = (unsigned char*)(lpSrcStartBits + lSrcLineBytes * i + j);
				if (*pixel == 0)
				{
					foregroundCount++;
				}
				else
				{
					backgroundCount++;
				}
			}
		}

		// 判断前景面积是否小于背景面积
		bool isForegroundSmaller = foregroundCount < backgroundCount;

		// 创建一个带有颜色表的新DIB
		BITMAPINFOHEADER bmiHeader = {};
		bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
		bmiHeader.biWidth = lSrcWidth;
		bmiHeader.biHeight = lSrcHeight;
		bmiHeader.biPlanes = 1;
		bmiHeader.biBitCount = 8;
		bmiHeader.biCompression = BI_RGB;
		bmiHeader.biSizeImage = lSrcLineBytes * lSrcHeight;

		RGBQUAD bmiColors[256];
		for (int i = 0; i < 256; i++)
		{
			bmiColors[i].rgbBlue = i;
			bmiColors[i].rgbGreen = i;
			bmiColors[i].rgbRed = i;
			bmiColors[i].rgbReserved = 0;
		}

		// 设置较小区域的颜色
		if (isForegroundSmaller)
		{
			bmiColors[0].rgbBlue = GetBValue(color);
			bmiColors[0].rgbGreen = GetGValue(color);
			bmiColors[0].rgbRed = GetRValue(color);
		}
		else
		{
			bmiColors[255].rgbBlue = GetBValue(color);
			bmiColors[255].rgbGreen = GetGValue(color);
			bmiColors[255].rgbRed = GetRValue(color);
		}

		// 创建一个新的DIB节
		void* pBits = nullptr;
		HBITMAP hDib = CreateDIBSection(NULL, (BITMAPINFO*)&bmiHeader, DIB_RGB_COLORS, &pBits, NULL, 0);
		if (hDib && pBits)
		{
			// 复制原始图像数据
			memcpy(pBits, lpSrcStartBits, lSrcLineBytes * lSrcHeight);

			// 更新文档以使用新的DIB
			pDoc->SetDIB(hDib, &bmiHeader, bmiColors, pBits);
			pDoc->SetModifiedFlag(TRUE);
			pDoc->UpdateAllViews(NULL);
		}

		// 解锁全局内存对象
		::GlobalUnlock((HGLOBAL)pDoc->GetHObject());
	}
}

