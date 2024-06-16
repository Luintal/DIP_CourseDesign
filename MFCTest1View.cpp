
// MFCTest1View.cpp: CMFCTest1View 类的实现
//
#include "stdafx.h"
#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "MFCTest1.h"
#endif

#include "MFCTest1Doc.h"
#include "MFCTest1View.h"
#include "PointTrans.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include "CDlgImgInfo.h"
#include "CDIgZengLiang.h"
#include "CDlgHistogram.h"
#include "DIBAPI.H"
#include "CDlgPointInvert.h"
#include "CDlgInverse_V.h"
#include "DIg_Tran_V.h"
#include "DIg_Tran_Reverse_L.h"
#include "DIg_Tran_L.h"
#include "CDlgLinerPara.h"
#include "DlgPointStre.h"
#include "DlgBitPlaneSlicing.h"
#include "function.h"
#include "DlgGammaTran.h"
#include "CDlgSmooth.h"
#include "DlgMidFilter.h"
#include "Dlg_EnhaSharp.h"
#include <vector>
#include <algorithm> 
#include "DlgMorphMenu.h"
#include "CDlgPointThre.h"
#include "CDlgPointWin.h"
#include "CDlgFilter.h"
#include "GeoTrans.h"
#include "DlgGeoTran.h"
#include "DlgGeoRota.h"
#include "CDlgGeoZoom.h"
#include "CDlgApplication.h"
#include "CDlgApplication2.h"
#include <queue>

// CMFCTest1View

IMPLEMENT_DYNCREATE(CMFCTest1View, CView)

BEGIN_MESSAGE_MAP(CMFCTest1View, CScrollView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(ID_DispImgInfo, &CMFCTest1View::OnDispimginfo)
	ON_COMMAND(ID_ChangeImgLight, &CMFCTest1View::OnChangeimglight)
	ON_COMMAND(ID_View_Histogram, &CMFCTest1View::OnViewHistyogram)
	ON_COMMAND(ID_24ColTo8Col, &CMFCTest1View::On24colto8col)
	ON_COMMAND(ID_24ColTo8Gray, &CMFCTest1View::On24colto8gray)
	ON_COMMAND(ID_CvtGray, &CMFCTest1View::OnCvtgray)
	ON_COMMAND(ID_CvtHalftone, &CMFCTest1View::OnCvthalftone)
	ON_COMMAND(ID_CvtBinary, &CMFCTest1View::OnCvtbinary)
	ON_COMMAND(ID_PointInvert, &CMFCTest1View::OnPointinvert)
	ON_COMMAND(ID_Tran_Reverse_V, &CMFCTest1View::OnTranReverseV)
	ON_COMMAND(ID_Tran_V, &CMFCTest1View::OnTranV)
	ON_COMMAND(ID_Tran_Reverse_L, &CMFCTest1View::OnTranReverseL)
	ON_COMMAND(ID_Tran_L, &CMFCTest1View::OnTranL)
	ON_COMMAND(ID_LinerPara, &CMFCTest1View::OnLinerpara)
	ON_COMMAND(ID_POINT_STRE, &CMFCTest1View::OnPointStre)
	ON_COMMAND(ID_BitPlaneSlicing, &CMFCTest1View::OnBitplaneslicing)
	ON_COMMAND(ID_LOGTran, &CMFCTest1View::OnLogtran)
	ON_COMMAND(ID_GammaTran, &CMFCTest1View::OnGammatran)
	ON_COMMAND(ID_EnhaSmooth, &CMFCTest1View::OnEnhasmooth)
	ON_COMMAND(ID_ENHA_MidianF, &CMFCTest1View::OnEnhaMidianf)
	ON_COMMAND(ID_Noise, &CMFCTest1View::OnNoise)
	ON_COMMAND(ID_ENHA_SHARP, &CMFCTest1View::OnEnhaSharp)
	ON_COMMAND(ID_MaxFilter, &CMFCTest1View::OnMaxfilter)
	ON_COMMAND(ID_MinFilter, &CMFCTest1View::OnMinfilter)
	ON_COMMAND(ID_MidPointFilter, &CMFCTest1View::OnMidpointfilter)
	ON_COMMAND(ID_AdapMedFilter, &CMFCTest1View::OnAdapmedfilter)
	ON_COMMAND(ID_EDGE_ROBERT, &CMFCTest1View::OnEdgeRobert)
	ON_COMMAND(ID_EDGE_SOBEL, &CMFCTest1View::OnEdgeSobel)
	ON_COMMAND(ID_RESTORE_SALTNOISE, &CMFCTest1View::OnRestoreSaltnoise)
	ON_COMMAND(ID_Morphology_MainMenu, &CMFCTest1View::OnMorphologyMainmenu)
	ON_COMMAND(ID_POINT_THRE, &CMFCTest1View::OnPointThre)
	ON_COMMAND(ID_PointWind, &CMFCTest1View::OnPointwind)
	ON_COMMAND(ID_PointEqua, &CMFCTest1View::OnPointequa)
	ON_COMMAND(ID_Filter, &CMFCTest1View::OnFilter)
	ON_COMMAND(ID_GEOM_TRAN, &CMFCTest1View::OnGeomTran)
	ON_COMMAND(ID_GEOM_ROTA, &CMFCTest1View::OnGeomRota)
	ON_COMMAND(ID_GEOM_ZOOM, &CMFCTest1View::OnGeomZoom)
	ON_COMMAND(ID_GEOM_MIRH, &CMFCTest1View::OnGeomMirh)
	ON_COMMAND(ID_GEOM_MIRV, &CMFCTest1View::OnGeomMirv)
	ON_COMMAND(ID_GEOM_TRPOs, &CMFCTest1View::OnGeomTrpos)
	ON_COMMAND(ID_Mosaic, &CMFCTest1View::OnMosaic)
	ON_COMMAND(ID_OilPaint, &CMFCTest1View::OnOilpaint)
	ON_COMMAND(ID_RetroStyle, &CMFCTest1View::OnRetrostyle)
	ON_COMMAND(ID_PencilDraw, &CMFCTest1View::OnPencildraw)
	ON_COMMAND(ID_Application, &CMFCTest1View::OnApplication)
	ON_COMMAND(ID_Canny, &CMFCTest1View::OnCanny)
	ON_COMMAND(ID_USM, &CMFCTest1View::OnUsm)
END_MESSAGE_MAP()

// CMFCTest1View 构造/析构

CMFCTest1View::CMFCTest1View() noexcept
{
	// TODO: 在此处添加构造代码

}

CMFCTest1View::~CMFCTest1View()
{
}

BOOL CMFCTest1View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CMFCTest1View 绘图

void CMFCTest1View::OnDraw(CDC* pDC)
{
	CMFCTest1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
	HGLOBAL hDIB = pDoc->GetHObject();

	// 判断DIB是否为空
	if (hDIB != NULL)
	{
		LPSTR lpDibSection = (LPSTR) ::GlobalLock((HGLOBAL)hDIB);

		// 获取DIB宽度
		int cxDIB = (int)pDoc->m_dib.GetWidth(lpDibSection);

		// 获取DIB高度
		int cyDIB = (int)pDoc->m_dib.GetHeight(lpDibSection);
		::GlobalUnlock((HGLOBAL)hDIB);
		CRect rcDIB;
		rcDIB.top = rcDIB.left = 0;
		rcDIB.right = cxDIB;
		rcDIB.bottom = cyDIB;
		CRect rcDest = rcDIB;
		// 输出DIB
		pDoc->m_dib.DrawDib(pDC->m_hDC, &rcDest, pDoc->GetHObject(),
			&rcDIB, pDoc->GetDocPal());
	}
}


// CMFCTest1View 打印

BOOL CMFCTest1View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CMFCTest1View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CMFCTest1View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CMFCTest1View 诊断

#ifdef _DEBUG
void CMFCTest1View::AssertValid() const
{
	CView::AssertValid();
}

void CMFCTest1View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCTest1Doc* CMFCTest1View::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCTest1Doc)));
	return (CMFCTest1Doc*)m_pDocument;
}
#endif //_DEBUG


// CMFCTest1View 消息处理程序


void CMFCTest1View::OnDispimginfo()
{
	// TODO: 在此添加命令处理程序代码
	// 显示图像基本信息
	CMFCTest1Doc* pDoc = GetDocument();// 获取文档	
	////////////////////////////////////////////////////////////////////////////////////////////////	
	long	lSrcLineBytes;		//图象每行的字节数
	long	lSrcWidth;      //图象的宽度和高度
	long	lSrcHeight;
	int     lpSrcBitCount;       //图像的位深
	LPSTR	lpSrcDib;		//指向源图象的指针	
	LPSTR	lpSrcStartBits;	//指向源像素的指针
	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// 锁定DIB
	if (!lpSrcDib) return;
	/*
	if (pDoc->m_dib.GetColorNum(lpSrcDib) != 256)// 判断是否是8-bpp位图
	{
		   AfxMessageBox(L"对不起，不是256色位图！");// 警告
		   ::GlobalUnlock((HGLOBAL) pDoc->GetHObject());// 解除锁定
		   return;									//返回
	 }										//判断是否是8-bpp位图,不是则返回
	 */
	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);			// 找到DIB图象像素起始位置	
	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);					// 获取图象的宽度		
	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);					// 获取图象的高度	
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);                    //获取图像位深
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount);		// 计算图象每行的字节数
	/////////////////////////////////////////////////////////////////////////////////////////////////	
	CDlgImgInfo dlgPara;// 创建对话框		
	dlgPara.m_Width = lSrcWidth;
	dlgPara.m_Height = lSrcHeight;
	dlgPara.m_bitCount = lpSrcBitCount;

	if (dlgPara.DoModal() != IDOK)// 显示对话框， 
	{
		return;
	}
}


void CMFCTest1View::OnChangeimglight()
{
	// TODO: 在此添加命令处理程序代码
	// 增亮/减淡图像
	CMFCTest1Doc* pDoc = GetDocument();// 获取文档    
	//////////////////////////////////////////////////////////////////////////////////////////////////  
	long lSrcLineBytes;        //图象每行的字节数
	long    lSrcWidth;      //图象的宽度和高度
	long    lSrcHeight;
	int     lpSrcBitCount;       //图像的位深
	LPSTR    lpSrcDib;        //指向源图象的指针    
	LPSTR    lpSrcStartBits;    //指向源像素的指针
	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// 锁定DIB
	if (!lpSrcDib) return;

	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);            // 找到DIB图象像素起始位置    
	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);                    // 获取图象的宽度        
	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);                    // 获取图象的高度    
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);                    //获取图像位深
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount);        // 计算图象每行的字节数

	// 指向源图像的指针
	unsigned char* lpSrc;

	int offset;
	CDIgZengLiang dlgPara;// 创建对话框            
	if (dlgPara.DoModal() != IDOK)// 显示对话框，设定平移量
	{
		return;
	}
	offset = dlgPara.m_offset;
	int temp,k;
	if (lpSrcBitCount == 8) {
		// 修改颜色表
		RGBQUAD* pColorTable = (RGBQUAD*)(lpSrcDib + sizeof(BITMAPINFOHEADER)); // 获取调色板指针
		for (int i = 0; i < 256; i++) {
			int red = pColorTable[i].rgbRed + offset;
			int green = pColorTable[i].rgbGreen + offset;
			int blue = pColorTable[i].rgbBlue + offset;

			pColorTable[i].rgbRed = red > 255 ? 255 : (red < 0 ? 0 : red);
			pColorTable[i].rgbGreen = green > 255 ? 255 : (green < 0 ? 0 : green);
			pColorTable[i].rgbBlue = blue > 255 ? 255 : (blue < 0 ? 0 : blue);
		}
	}
	else if (lpSrcBitCount == 24) {
		// 修改像素数据
			//逐行扫描
		for (int i = 0; i < lSrcHeight; i++)
		{
			//逐列扫描
			for (int j = 0; j < lSrcWidth; j++)
			{
				// 指向DIB第i行，第j个象素的指针
				for (k = 0; k < 3; k++)
				{
					lpSrc = (unsigned char*)lpSrcStartBits + lSrcLineBytes * (lSrcHeight - 1 - i) + j * 3 + k;
					// 变换
					temp = *lpSrc + offset;
					if (temp > 255)
					{
						// 直接赋值为255
						*lpSrc = 255;
					}
					else if (temp < 0)
					{
						// 直接赋值为0
						*lpSrc = 0;
					}
					else
					{
						// 四舍五入
						*lpSrc = (unsigned char)(temp + 0.5);
					}

				}
			}
		}
	}

	//设置文档修改标志
	pDoc->SetModifiedFlag(true);
	//更新视图
	pDoc->UpdateAllViews(NULL);
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// 解除锁定
}

void CMFCTest1View::OnViewHistyogram()
{
	// 显示图像直方图
	CMFCTest1Doc* pDoc = GetDocument();// 获取文档	
	////////////////////////////////////////////////////////////////////////////////////////////////	
	long	lSrcLineBytes;		//图象每行的字节数
	long	lSrcWidth;      //图象的宽度和高度
	long	lSrcHeight;
	int     lpSrcBitCount;       //图像的位深
	LPSTR	lpSrcDib;		//指向源图象的指针	
	LPSTR	lpSrcStartBits;	//指向源像素的指针
	unsigned char* lpSrc = nullptr;
	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// 锁定DIB
	if (!lpSrcDib) return;

	if (pDoc->m_dib.GetBitCount(lpSrcDib) != 8)// 判断是否是8-bpp位图
	{
		AfxMessageBox(L"对不起，不是8位图！");// 警告				
		::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// 解除锁定		
		return;									//返回
	}

	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);			// 找到DIB图象像素起始位置	
	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);					// 获取图象的宽度		
	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);					// 获取图象的高度	
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);                    //获取图像位深
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount);		// 计算图象每行的字节数

	CDlgHistogram dlgPara;
	//显示直方图
	// 初始化变量值
	dlgPara.m_lpDIBBits = lpSrcStartBits;
	dlgPara.m_lWidth = lSrcWidth;
	dlgPara.m_lHeight = lSrcHeight;
	dlgPara.m_iLowGray = 0;
	dlgPara.m_iHighGray = 255;
	dlgPara.m_lLineBytes = lSrcLineBytes;

	if (dlgPara.DoModal() != IDOK) // 显示对话框 
	{
		return;
	}

	//////////////////////////
	delete dlgPara;
	EndWaitCursor();
	//设置文档修改标志
	//  pDoc->SetModifiedFlag(true);
	//更新视图
	pDoc->UpdateAllViews(NULL);
	// 解除锁定
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());
}


void CMFCTest1View::On24colto8col()
{
	// TODO: 在此添加命令处理程序代码
	// 24位彩色转8位彩色
	CMFCTest1Doc* pDoc = GetDocument();// 获取文档	
	////////////////////////////////////////////////////////////////////////////////////////////////	
	long lSrcLineBytes;		//图象每行的字节数
	long	lSrcWidth;      //图象的宽度和高度
	long	lSrcHeight;
	int     lpSrcBitCount;       //图像的位深
	LPSTR	lpSrcDib;		//指向源图象的指针	
	LPSTR	lpSrcStartBits;	//指向源像素的指针
	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// 锁定DIB
	if (!lpSrcDib) return;
	if (pDoc->m_dib.GetBitCount(lpSrcDib) != 24)// 判断是否是24-bpp位图
	{
		AfxMessageBox(L"对不起，不是24位图！");// 警告				
		::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// 解除锁定		
		return;									//返回
	}
	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);			// 找到DIB图象像素起始位置	
	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);					// 获取图象的宽度		
	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);					// 获取图象的高度	
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);                    //获取图像位深
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount);		// 计算图象每行的字节数
	/////////////////////////////////////////////////////////////////////////////////////////////////

	Tran24ColTo8Col(lpSrcDib, lpSrcStartBits, lSrcWidth, lSrcHeight);// 24位彩色转8位彩色	 


	//设置文档修改标志
	pDoc->SetModifiedFlag(true);
	//更新视图
	pDoc->UpdateAllViews(NULL);
	//解除锁定
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());
}


void CMFCTest1View::On24colto8gray()
{
	// TODO: 在此添加命令处理程序代码
	// 24位彩色转8位灰度
	CMFCTest1Doc* pDoc = GetDocument();// 获取文档	
	////////////////////////////////////////////////////////////////////////////////////////////////	
	long lSrcLineBytes;		//图象每行的字节数
	long	lSrcWidth;      //图象的宽度和高度
	long	lSrcHeight;
	int     lpSrcBitCount;       //图像的位深
	LPSTR	lpSrcDib;		//指向源图象的指针	
	LPSTR	lpSrcStartBits;	//指向源像素的指针
	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// 锁定DIB
	if (!lpSrcDib) return;
	if (pDoc->m_dib.GetBitCount(lpSrcDib) != 24)// 判断是否是24-bpp位图
	{
		AfxMessageBox(L"对不起，不是24位图！");// 警告				
		::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// 解除锁定		
		return;									//返回
	}
	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);			// 找到DIB图象像素起始位置	
	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);					// 获取图象的宽度		
	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);					// 获取图象的高度	
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);                    //获取图像位深
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount);		// 计算图象每行的字节数
	/////////////////////////////////////////////////////////////////////////////////////////////////

	Tran24ColTo8Gray(lpSrcDib, lpSrcStartBits, lSrcWidth, lSrcHeight);// 24位彩色转8位灰度	 


	//设置文档修改标志
	pDoc->SetModifiedFlag(true);
	//更新视图
	pDoc->UpdateAllViews(NULL);
	//解除锁定
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());
}

// 8/24位彩色转8/24位灰度
void CMFCTest1View::OnCvtgray()
{
	CMFCTest1Doc* pDoc = GetDocument();// 获取文档	
	////////////////////////////////////////////////////////////////////////////////////////////////	
	long lSrcLineBytes;		//图象每行的字节数
	long	lSrcWidth;      //图象的宽度和高度
	long	lSrcHeight;
	int     lpSrcBitCount;       //图像的位深
	LPSTR	lpSrcDib;		//指向源图象的指针	
	LPSTR	lpSrcStartBits;	//指向源像素的指针
	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// 锁定DIB
	if (!lpSrcDib) return;

	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);			// 找到DIB图象像素起始位置	
	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);					// 获取图象的宽度		
	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);					// 获取图象的高度	
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);                    //获取图像位深
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount);		// 计算图象每行的字节数
	/////////////////////////////////////////////////////////////////////////////////////////////////
	if (pDoc->m_dib.GetBitCount(lpSrcDib) == 24)
	{
		// 指向源图像的指针
		unsigned char* lpSrc;
		// 循环变量
		LONG	i;
		LONG	j;
		// 图像每行的字节数
		LONG	lLineBytes;

		// 计算图像每行的字节数
		lLineBytes = WIDTHBYTES(lSrcWidth * 24);

		int R, G, B, Gray;
		for (i = 0; i < lSrcHeight; i++)
		{
			for (j = 0; j < lSrcWidth; j++)
			{
				lpSrc = (unsigned char*)lpSrcStartBits + i * lLineBytes + j * 3;
				B = *lpSrc;
				lpSrc = (unsigned char*)lpSrcStartBits + i * lLineBytes + j * 3 + 1;
				G = *lpSrc;
				lpSrc = (unsigned char*)lpSrcStartBits + i * lLineBytes + j * 3 + 2;
				R = *lpSrc;
				Gray = ((R + G + B) / 3.0 + 0.5);

				lpSrc = (unsigned char*)lpSrcStartBits + i * lLineBytes + j * 3;
				*lpSrc = Gray;
				lpSrc = (unsigned char*)lpSrcStartBits + i * lLineBytes + j * 3 + 1;
				*lpSrc = Gray;
				lpSrc = (unsigned char*)lpSrcStartBits + i * lLineBytes + j * 3 + 2;
				*lpSrc = Gray;

			}
		}
	}

	if (pDoc->m_dib.GetBitCount(lpSrcDib) == 8)
	{
		// 指向源图像的指针
		unsigned char* lpSrc;
		// 循环变量
		LONG	i;
		LONG	j;
		// 图像每行的字节数
		LONG	lLineBytes;

		// 计算图像每行的字节数
		lLineBytes = WIDTHBYTES(lSrcWidth * 8);

		// 灰度映射表
		BYTE bMap[256];
		RGBQUAD* pTable, * pTable1;//颜色表指针

		pTable = (RGBQUAD*)(lpSrcDib + sizeof(BITMAPINFOHEADER));
		for (i = 0; i < 256; i++)//生成新的调色板,并转换灰度
		{
			// 计算该颜色对应的灰度值g=0.299*r+0.587*g+0.114*b	
			bMap[i] = (BYTE)(0.299 * pTable->rgbRed + 0.587 * pTable->rgbGreen + 0.114 * pTable->rgbBlue + 0.5);
			pTable->rgbRed = (BYTE)i;
			pTable->rgbGreen = (BYTE)i;
			pTable->rgbBlue = (BYTE)i;
			pTable->rgbReserved = (BYTE)0;
			pTable++;
		}
		// 更换每个象素的颜色索引（即按照灰度映射表换成灰度值）
		//逐行扫描
		for (i = 0; i < lSrcHeight; i++)
		{
			//逐列扫描
			for (j = 0; j < lSrcWidth; j++)
			{
				// 指向DIB第i行，第j个象素的指针
				lpSrc = (unsigned char*)lpSrcStartBits + lLineBytes * (lSrcHeight - 1 - i) + j;
				// 变换
				*lpSrc = bMap[*lpSrc];
			}
		}
	}

	//设置文档修改标志
	pDoc->SetModifiedFlag(true);
	//更新视图
	pDoc->UpdateAllViews(NULL);
	//解除锁定
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());

}

// 灰度图像的半影调化（图案法）
void CMFCTest1View::OnCvthalftone()
{
	CMFCTest1Doc* pDoc = GetDocument();	// 获取文档
	long lSrcLineBytes;		// 图像每行的字节数
	long lSrcWidth;			// 图像的宽度和高度
	long lSrcHeight;
	int lpSrcBitCount;		// 图像的位深
	LPSTR lpSrcDib;			// 指向源图像的指针
	LPSTR lpSrcStartBits;	// 指向源像素的指针
	lpSrcDib = (LPSTR)::GlobalLock((HGLOBAL)pDoc->GetHObject());	// 锁定DIB
	if (!lpSrcDib) return;
	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);						// 找到DIB图像像素起始位置
	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);							// 获取图像的宽度
	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);						// 获取图像的高度
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);						// 获取图像的位深
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount);	// 计算图像每行的字节数
	// 定义8x8阈值矩阵
	int thresholdMatrix[8][8] = { 0,32,8,40,2,34,10,42,
					 48,16,56,24,50,18,58,26,
					 12,44,4,36,14,46,6,38,
					 60,28,52,20,62,30,54,22,
					 3,35,11,43,1,33,9,41,
					 51,19,59,27,49,17,57,25,
					 15,47,7,39,13,45,5,37,
					 63,31,55,23,61,29,53,21 };

	// 每行
	for (LONG i = 0; i < lSrcHeight; i++)
	{
		// 每列
		for (LONG j = 0; j < lSrcWidth; j++)
		{
			// 获取像素指针
			unsigned char* lpPixel = (unsigned char*)lpSrcStartBits + lSrcLineBytes * (lSrcHeight - 1 - i) + j;
			// 计算在阈值矩阵中的位置
			int x = j % 8;
			int y = i % 8;
			int threshold = thresholdMatrix[y][x];
			// 根据阈值进行二值化
			if (*lpPixel / 255.0 > threshold / 64.0)
			{
				*lpPixel = 255;
			}
			else
			{
				*lpPixel = 0;
			}
		}
	}
	// 设置文档修改标志
	pDoc->SetModifiedFlag(true);
	// 更新视图
	pDoc->UpdateAllViews(NULL);
	// 解除锁定
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());
}


// 灰度图转二值图
void CMFCTest1View::OnCvtbinary()
{
	CMFCTest1Doc* pDoc = GetDocument();// 获取文档	
	////////////////////////////////////////////////////////////////////////////////////////////////	
	long lSrcLineBytes;		//图象每行的字节数
	long	lSrcWidth;      //图象的宽度和高度
	long	lSrcHeight;
	int     lpSrcBitCount;       //图像的位深
	LPSTR	lpSrcDib;		//指向源图象的指针	
	LPSTR	lpSrcStartBits;	//指向源像素的指针
	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// 锁定DIB
	if (!lpSrcDib) return;

	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);			// 找到DIB图象像素起始位置	
	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);					// 获取图象的宽度		
	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);					// 获取图象的高度	
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);                    //获取图像位深
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount);		// 计算图象每行的字节数
	/////////////////////////////////////////////////////////////////////////////////////////////////

		// 指向源图像的指针
	unsigned char* lpSrc;

	// 循环变量
	LONG	i;
	LONG	j;

	// 图像每行的字节数
	LONG	lLineBytes;

	// 计算图像每行的字节数
	lLineBytes = WIDTHBYTES(lSrcWidth * 8);

	// 每行
	for (i = 0; i < lSrcHeight; i++)
	{
		// 每列
		for (j = 0; j < lSrcWidth; j++)
		{
			// 指向DIB第i行，第j个象素的指针
			lpSrc = (unsigned char*)lpSrcStartBits + lLineBytes * (lSrcHeight - 1 - i) + j;

			// 判断是否小于阈值
			if ((*lpSrc) < 123)
			{
				// 直接赋值为0
				*lpSrc = 0;
			}
			else
			{
				// 直接赋值为255
				*lpSrc = 255;
			}
		}
	}


	//设置文档修改标志
	pDoc->SetModifiedFlag(true);
	//更新视图
	pDoc->UpdateAllViews(NULL);
	//解除锁定
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());

}

// 灰度图反色
void CMFCTest1View::OnPointinvert()
{
	CMFCTest1Doc* pDoc = GetDocument();// 获取文档	
	////////////////////////////////////////////////////////////////////////////////////////////////	
	long lSrcLineBytes;		//图象每行的字节数
	long	lSrcWidth;      //图象的宽度和高度
	long	lSrcHeight;
	int     lpSrcBitCount;       //图像的位深
	LPSTR	lpSrcDib;		//指向源图象的指针	
	LPSTR	lpSrcStartBits;	//指向源像素的指针
	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// 锁定DIB
	if (!lpSrcDib) return;
	if (pDoc->m_dib.GetColorNum(lpSrcDib) != 256)	//判断是否是8位位图
	{
		AfxMessageBox(L"对不起，不是256色位图！");
		::GlobalUnlock((HGLOBAL)pDoc->GetHObject());  // 解除锁定
		return;
	}
	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);			// 找到DIB图象像素起始位置	
	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);					// 获取图象的宽度		
	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);					// 获取图象的高度	
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);                    //获取图像位深
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount);		// 计算图象每行的字节数
	/////////////////////////////////////////////////////////////////////////////////////////////////
	CDlgPointInvert dlgPara;// 创建对话框	
	if (dlgPara.DoModal() != IDOK)// 显示对话框 
	{
		return;
	}

	// 调用函数
	FLOAT fA = -1.0;
	FLOAT fB = 255.0;
	LinerTrans(lpSrcStartBits, lSrcWidth, lSrcHeight, fA, fB);

	// 设置文档修改标志
	pDoc->SetModifiedFlag(true);
	// 更新视图
	pDoc->UpdateAllViews(NULL);
	// 解除锁定
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());
}

//倒V型变换
void CMFCTest1View::OnTranReverseV()
{
	// TODO: 在此添加命令处理程序代码
	

	CMFCTest1Doc* pDoc = GetDocument();// 获取文档	
	////////////////////////////////////////////////////////////////////////////////////////////////	
	long lSrcLineBytes;		//图象每行的字节数
	long	lSrcWidth;      //图象的宽度和高度
	long	lSrcHeight;
	int     lpSrcBitCount;       //图像的位深
	LPSTR	lpSrcDib;		//指向源图象的指针	
	LPSTR	lpSrcStartBits;	//指向源像素的指针
	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// 锁定DIB
	if (!lpSrcDib) return;
	if (pDoc->m_dib.GetColorNum(lpSrcDib) != 256)// 判断是否是8-bip位图
	{
		AfxMessageBox(L"对不起，不是256色位图！");// 警告				
		::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// 解除锁定		
		return;									//返回
	}
	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);			// 找到DIB图象像素起始位置	
	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);					// 获取图象的宽度		
	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);					// 获取图象的高度	
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);                    //获取图像位深
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount);		// 计算图象每行的字节数
	/////////////////////////////////////////////////////////////////////////////////////////////////
	CDlgInverse_V dlgPara;// 创建对话框	
	dlgPara.m_threshold = 127;
	if (dlgPara.DoModal() != IDOK)// 显示对话框，设定平移量
	{
		return;
	}

	int type, threshold;
	threshold = dlgPara.m_threshold;
	type = 1;
	Segmental2_Linear_Tran(lpSrcStartBits, lSrcWidth, lSrcHeight, type, threshold);

	//设置文档修改标志
	pDoc->SetModifiedFlag(true);
	//更新视图
	pDoc->UpdateAllViews(NULL);
	//解除锁定
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());
}


void CMFCTest1View::OnTranV()
{
	// TODO: 在此添加命令处理程序代码
	// V型变换	
	CMFCTest1Doc* pDoc = GetDocument();// 获取文档	
	////////////////////////////////////////////////////////////////////////////////////////////////	
	long lSrcLineBytes;		//图象每行的字节数
	long	lSrcWidth;      //图象的宽度和高度
	long	lSrcHeight;
	int     lpSrcBitCount;       //图像的位深
	LPSTR	lpSrcDib;		//指向源图象的指针	
	LPSTR	lpSrcStartBits;	//指向源像素的指针
	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// 锁定DIB
	if (!lpSrcDib) return;
	if (pDoc->m_dib.GetColorNum(lpSrcDib) != 256)// 判断是否是8-bip位图
	{
		AfxMessageBox(L"对不起，不是256色位图！");// 警告				
		::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// 解除锁定		
		return;									//返回
	}
	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);			// 找到DIB图象像素起始位置	
	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);					// 获取图象的宽度		
	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);					// 获取图象的高度	
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);                    //获取图像位深
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount);		// 计算图象每行的字节数
	/////////////////////////////////////////////////////////////////////////////////////////////////
	DIg_Tran_V dlgPara;// 创建对话框	
	dlgPara.m_thresholdV = 127;
	if (dlgPara.DoModal() != IDOK)// 显示对话框，设定平移量
	{
		return;
	}

	int type, threshold;
	threshold = dlgPara.m_thresholdV;
	type = 2;
	Segmental2_Linear_Tran(lpSrcStartBits, lSrcWidth, lSrcHeight, type, threshold);

	//设置文档修改标志
	pDoc->SetModifiedFlag(true);
	//更新视图
	pDoc->UpdateAllViews(NULL);
	//解除锁定
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());

}


void CMFCTest1View::OnTranReverseL()
{
	// TODO: 在此添加命令处理程序代码
	// 倒L型变换	
	CMFCTest1Doc* pDoc = GetDocument();// 获取文档	
	////////////////////////////////////////////////////////////////////////////////////////////////	
	long lSrcLineBytes;		//图象每行的字节数
	long	lSrcWidth;      //图象的宽度和高度
	long	lSrcHeight;
	int     lpSrcBitCount;       //图像的位深
	LPSTR	lpSrcDib;		//指向源图象的指针	
	LPSTR	lpSrcStartBits;	//指向源像素的指针
	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// 锁定DIB
	if (!lpSrcDib) return;
	if (pDoc->m_dib.GetColorNum(lpSrcDib) != 256)// 判断是否是8-bpp位图
	{
		AfxMessageBox(L"对不起，不是256色位图！");// 警告				
		::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// 解除锁定		
		return;									//返回
	}
	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);			// 找到DIB图象像素起始位置	
	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);					// 获取图象的宽度		
	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);					// 获取图象的高度	
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);                    //获取图像位深
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount);		// 计算图象每行的字节数
	/////////////////////////////////////////////////////////////////////////////////////////////////
	DIg_Tran_Reverse_L dlgPara;// 创建对话框	
	dlgPara.m_thresholdRL = 127;
	if (dlgPara.DoModal() != IDOK)// 显示对话框，设定平移量
	{
		return;
	}
	
	int type, threshold;
	threshold = dlgPara.m_thresholdRL;
	type = 3;
	Segmental2_Linear_Tran(lpSrcStartBits, lSrcWidth, lSrcHeight, type, threshold);

	//设置文档修改标志
	pDoc->SetModifiedFlag(true);
	//更新视图
	pDoc->UpdateAllViews(NULL);
	//解除锁定
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());
}

// L型变换
void CMFCTest1View::OnTranL()
{
	// TODO: 在此添加命令处理程序代码
	// L型变换
	CMFCTest1Doc* pDoc = GetDocument();// 获取文档	
	////////////////////////////////////////////////////////////////////////////////////////////////	
	long lSrcLineBytes;		//图象每行的字节数
	long	lSrcWidth;      //图象的宽度和高度
	long	lSrcHeight;
	int     lpSrcBitCount;       //图像的位深
	LPSTR	lpSrcDib;		//指向源图象的指针	
	LPSTR	lpSrcStartBits;	//指向源像素的指针
	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// 锁定DIB
	if (!lpSrcDib) return;
	if (pDoc->m_dib.GetColorNum(lpSrcDib) != 256)// 判断是否是8-bip位图
	{
		AfxMessageBox(L"对不起，不是256色位图！");// 警告				
		::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// 解除锁定		
		return;									//返回
	}
	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);			// 找到DIB图象像素起始位置	
	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);					// 获取图象的宽度		
	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);					// 获取图象的高度	
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);                    //获取图像位深
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount);		// 计算图象每行的字节数
	/////////////////////////////////////////////////////////////////////////////////////////////////
	DIg_Tran_L dlgPara;// 创建对话框	
	dlgPara.m_thresholdL = 127;
	if (dlgPara.DoModal() != IDOK)// 显示对话框，设定平移量
	{
		return;
	}
	
	int type, threshold;
	threshold = dlgPara.m_thresholdL;
	type = 4;
	Segmental2_Linear_Tran(lpSrcStartBits, lSrcWidth, lSrcHeight, type, threshold);

	//设置文档修改标志
	pDoc->SetModifiedFlag(true);
	//更新视图
	pDoc->UpdateAllViews(NULL);
	//解除锁定
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());
}

//线性变换
void CMFCTest1View::OnLinerpara()
{
	CMFCTest1Doc* pDoc = GetDocument();// 获取文档	
	////////////////////////////////////////////////////////////////////////////////////////////////	
	long lSrcLineBytes;		//图象每行的字节数
	long	lSrcWidth;      //图象的宽度和高度
	long	lSrcHeight;
	int     lpSrcBitCount;       //图像的位深
	LPSTR	lpSrcDib;		//指向源图象的指针	
	LPSTR	lpSrcStartBits;	//指向源像素的指针
	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// 锁定DIB
	if (!lpSrcDib) return;
	if (pDoc->m_dib.GetColorNum(lpSrcDib) != 256)// 判断是否是8-bpp位图
	{
		AfxMessageBox(L"对不起，不是256色位图！");// 警告				
		::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// 解除锁定		
		return;									//返回
	}
	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);			// 找到DIB图象像素起始位置	
	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);					// 获取图象的宽度		
	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);					// 获取图象的高度	
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);                    //获取图像位深
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount);		// 计算图象每行的字节数
	/////////////////////////////////////////////////////////////////////////////////////////////////
	CDlgLinerPara dlgPara;// 创建对话框			
	if (dlgPara.DoModal() != IDOK)// 显示对话框，设定平移量
	{
		return;
	}
	FLOAT fA = dlgPara.m_fA;
	FLOAT fB = dlgPara.m_fB;  //(2f)
	LinerTrans(lpSrcStartBits, lSrcWidth, lSrcHeight, fA, fB);

	//设置文档修改标志
	pDoc->SetModifiedFlag(true);
	//更新视图
	pDoc->UpdateAllViews(NULL);
	//解除锁定
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());

}
// 灰度拉伸
void CMFCTest1View::OnPointStre()
{
	// 获取文档
	CMFCTest1Doc* pDoc = GetDocument();

	// 锁定DIB
	LPSTR lpDIB = (LPSTR)::GlobalLock((HGLOBAL)pDoc->GetHObject());
	if (!lpDIB) return;

	// 判断是否是8-bpp位图（这里为了方便，只处理8-bpp位图的灰度拉伸，其它的可以类推）
	if (pDoc->m_dib.GetColorNum(lpDIB) != 256)
	{
		// 提示用户
		AfxMessageBox(L"只支持8位灰度图像处理！");

		// 解除锁定
		::GlobalUnlock((HGLOBAL)pDoc->GetHObject());

		// 返回
		return;
	}

	// 找到DIB图像像素起始位置
	
	LPSTR lpDIBBits = pDoc->m_dib.GetBits(lpDIB);			// 找到DIB图象像素起始位置
	long lSrcWidth = pDoc->m_dib.GetWidth(lpDIB);					// 获取图象的宽度		
	long lSrcHeight = pDoc->m_dib.GetHeight(lpDIB);					// 获取图象的高度
	// 创建对话框
	DlgPointStre dlgPara;

	// 初始化变量值
	dlgPara.m_bX1 = 50;
	dlgPara.m_bY1 = 30;
	dlgPara.m_bX2 = 200;
	dlgPara.m_bY2 = 220;
	dlgPara.pDoc = pDoc;
	// 显示对话框，提示用户设定拉伸位置
	if (dlgPara.DoModal() != IDOK)
	{
		// 解除锁定
		//::GlobalUnlock((HGLOBAL)pDoc->GetHObject());

		// 返回
		return;
	}

	// 获取用户的设定
	BYTE bX1 = dlgPara.m_bX1;
	BYTE bY1 = dlgPara.m_bY1;
	BYTE bX2 = dlgPara.m_bX2;
	BYTE bY2 = dlgPara.m_bY2;

	// 删除对话框
	delete dlgPara;

	// 更改光标形状
	BeginWaitCursor();

	// 调用GrayStretch()函数进行灰度拉伸
	GrayStretch(lpDIBBits, lSrcWidth, lSrcHeight, bX1, bY1, bX2, bY2);

	// 设置文档修改标志
	pDoc->SetModifiedFlag(TRUE);

	// 更新视图
	pDoc->UpdateAllViews(NULL);

	// 解除锁定
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());

	// 恢复光标
	EndWaitCursor();
}


//位平面分解
void CMFCTest1View::OnBitplaneslicing()
{
	// TODO: 在此添加命令处理程序代码
	// 位平面分解

	CMFCTest1Doc* pDoc = GetDocument();// 获取文档	
	////////////////////////////////////////////////////////////////////////////////////////////////	
	long	lSrcLineBytes;		//图象每行的字节数
	long	lSrcWidth;      //图象的宽度和高度
	long	lSrcHeight;
	int     lpSrcBitCount;       //图像的位深
	LPSTR	lpSrcDib;		//指向源图象的指针	
	LPSTR	lpSrcStartBits;	//指向源像素的指针
	unsigned char* lpSrc;
	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// 锁定DIB
	if (!lpSrcDib) return;

	if (pDoc->m_dib.GetBitCount(lpSrcDib) != 8)// 判断是否是8-bpp位图
	{
		AfxMessageBox(L"对不起，不是8位图！");// 警告				
		::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// 解除锁定		
		return;									//返回
	}

	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);			// 找到DIB图象像素起始位置	
	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);					// 获取图象的宽度		
	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);					// 获取图象的高度	
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);                    //获取图像位深
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount);		// 计算图象每行的字节数

	DlgBitPlaneSlicing dlgPara;

	dlgPara.lSrcLineBytes = lSrcLineBytes;		//图象每行的字节数
	dlgPara.lSrcWidth = lSrcWidth;      //图象的宽度和高度
	dlgPara.lSrcHeight = lSrcHeight;
	dlgPara.lpSrcBitCount = lpSrcBitCount;       //图像的位深
	dlgPara.lpSrcDib = lpSrcDib;		//指向源图象的指针	
	dlgPara.lpSrcStartBits = lpSrcStartBits;	//指向源像素的指针


	//位平面分解
	if (dlgPara.DoModal() != IDOK) // 显示对话框 
	{
		return;
	}

	//////////////////////////
	delete dlgPara;
	EndWaitCursor();
	//设置文档修改标志
	//  pDoc->SetModifiedFlag(true);
	//更新视图
	pDoc->UpdateAllViews(NULL);
	// 解除锁定
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());
}

// 对数变换
void CMFCTest1View::OnLogtran()
{
	// TODO: 在此添加命令处理程序代码
	CMFCTest1Doc* pDoc = GetDocument();// 获取文档	
	////////////////////////////////////////////////////////////////////////////////////////////////	
	long	lSrcLineBytes;		//图象每行的字节数
	long	lSrcWidth;      //图象的宽度和高度
	long	lSrcHeight;
	int     lpSrcBitCount;       //图像的位深
	LPSTR	lpSrcDib;		//指向源图象的指针	
	LPSTR	lpSrcStartBits;	//指向源像素的指针
	unsigned char* lpSrc;
	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// 锁定DIB
	if (!lpSrcDib) return;

	if (pDoc->m_dib.GetBitCount(lpSrcDib) != 8)// 判断是否是8-bpp位图
	{
		AfxMessageBox(L"对不起，不是8位图！");// 警告				
		::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// 解除锁定		
		return;									//返回
	}

	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);			// 找到DIB图象像素起始位置	
	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);					// 获取图象的宽度		
	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);					// 获取图象的高度	
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);                    //获取图像位深
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount);		// 计算图象每行的字节数

	BitPlaneSlicing(lpSrcStartBits, lSrcWidth, lSrcLineBytes, lSrcHeight, 6);
	LogTranslation(lpSrcStartBits, lSrcWidth, lSrcHeight, lSrcLineBytes);


	EndWaitCursor();
	//设置文档修改标志
	pDoc->SetModifiedFlag(true);
	//更新视图
	pDoc->UpdateAllViews(NULL);
	// 解除锁定
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());
}


void CMFCTest1View::OnGammatran()
{
	// TODO: 在此添加命令处理程序代码
	// gamma 变换
	CMFCTest1Doc* pDoc = GetDocument();// 获取文档	
	////////////////////////////////////////////////////////////////////////////////////////////////	
	long	lSrcLineBytes;		//图象每行的字节数
	long	lSrcWidth;      //图象的宽度和高度
	long	lSrcHeight;
	int     lpSrcBitCount;       //图像的位深
	LPSTR	lpSrcDib;		//指向源图象的指针	
	LPSTR	lpSrcStartBits;	//指向源像素的指针
	unsigned char* lpSrc;
	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// 锁定DIB
	if (!lpSrcDib) return;

	if (pDoc->m_dib.GetBitCount(lpSrcDib) != 8)// 判断是否是8-bpp位图
	{
		AfxMessageBox(L"对不起，不是8位图！");// 警告				
		::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// 解除锁定		
		return;									//返回
	}

	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);			// 找到DIB图象像素起始位置	
	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);					// 获取图象的宽度		
	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);					// 获取图象的高度	
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);                    //获取图像位深
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount);		// 计算图象每行的字节数

	DlgGammaTran dlgPara;
	//位平面分解
	if (dlgPara.DoModal() != IDOK) // 显示对话框 
	{
		return;
	}
	float gamma = dlgPara.m_fValGamma;

	long i;                 //行循环变量
	long j;                 //列循环变量

	float val;
	for (i = 0; i < lSrcHeight; i++)// 行
	{
		for (j = 0; j < lSrcWidth; j++)// 列
		{
			lpSrc = (unsigned char*)lpSrcStartBits + lSrcLineBytes * (lSrcHeight - 1 - i) + j;// 指向DIB第i行，第j个像素的指针
			val = (*lpSrc);
			val = pow(val, gamma);
			val = 255 * val / pow(255, gamma);

			*lpSrc = (int)val;
		}
	}



	//////////////////////////
	delete dlgPara;
	EndWaitCursor();
	//设置文档修改标志
	//  pDoc->SetModifiedFlag(true);
	//更新视图
	pDoc->UpdateAllViews(NULL);
	// 解除锁定
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());
	
}

//平滑处理
void CMFCTest1View::OnEnhasmooth()
{
	// TODO: 在此添加命令处理程序代码

	// 获取文档
	CMFCTest1Doc* pDoc = GetDocument();

	// 指向DIB的指针
	LPSTR	lpDIB;

	// 指向DIB象素指针
	LPSTR   lpDIBBits;

	// 模板高度
	int		iTempH;

	// 模板宽度
	int		iTempW;

	// 模板系数
	FLOAT	fTempC;

	// 模板中心元素X坐标
	int		iTempMX;

	// 模板中心元素Y坐标
	int		iTempMY;

	// 模板元素数组
	double	aValue[25];

	// 锁定DIB
	lpDIB = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());

	// 找到DIB图像象素起始位置
	lpDIBBits = pDoc->m_dib.GetBits(lpDIB);
	long lpDIBWidth = pDoc->m_dib.GetWidth(lpDIB);					// 获取图象的宽度		
	long lpDIBHeight = pDoc->m_dib.GetHeight(lpDIB);					// 获取图象的高度

	// 判断是否是8-bip位图（这里为了方便，只处理8-bip位图的平滑，其它的可以类推）
	if (pDoc->m_dib.GetBitCount(lpDIB) != 8)
	{
		// 提示用户
		MessageBox(L"目前只支持256色位图的平滑！", L"系统提示", MB_ICONINFORMATION | MB_OK);

		// 解除锁定
		::GlobalUnlock((HGLOBAL)pDoc->GetHObject());

		// 返回
		return;
	}

	// 创建对话框
	CDlgSmooth dlgPara;

	// 给模板数组赋初值（为平均模板）
	aValue[0] = 1.0;
	aValue[1] = 1.0;
	aValue[2] = 1.0;
	aValue[3] = 0.0;
	aValue[4] = 0.0;
	aValue[5] = 1.0;
	aValue[6] = 1.0;
	aValue[7] = 1.0;
	aValue[8] = 0.0;
	aValue[9] = 0.0;
	aValue[10] = 1.0;
	aValue[11] = 1.0;
	aValue[12] = 1.0;
	aValue[13] = 0.0;
	aValue[14] = 0.0;
	aValue[15] = 0.0;
	aValue[16] = 0.0;
	aValue[17] = 0.0;
	aValue[18] = 0.0;
	aValue[19] = 0.0;
	aValue[20] = 0.0;
	aValue[21] = 0.0;
	aValue[22] = 0.0;
	aValue[23] = 0.0;
	aValue[24] = 0.0;

	// 初始化对话框变量值
	dlgPara.m_intType = 0;
	dlgPara.m_iTempH = 3;
	dlgPara.m_iTempW = 3;
	dlgPara.m_iTempMX = 1;
	dlgPara.m_iTempMY = 1;
	dlgPara.m_fTempC = (FLOAT)(1.0 / 9.0);
    dlgPara.m_fpArray = aValue;

	// 显示对话框，提示用户设定平移量
	if (dlgPara.DoModal() != IDOK)
	{
		// 返回
		return;
	}

	// 获取用户设定的平移量
	iTempH = dlgPara.m_iTempH;
	iTempW = dlgPara.m_iTempW;
	iTempMX = dlgPara.m_iTempMX;
	iTempMY = dlgPara.m_iTempMY;
	fTempC = dlgPara.m_fTempC;

	// 删除对话框
	delete dlgPara;

	// 更改光标形状
	BeginWaitCursor();

// 调用Template()函数平滑DIB
if (::Template(lpDIBBits, lpDIBWidth, lpDIBHeight,
	iTempH, iTempW, iTempMX, iTempMY, aValue, fTempC))
{

	// 设置脏标记
	pDoc->SetModifiedFlag(TRUE);

	// 更新视图
	pDoc->UpdateAllViews(NULL);
}
//else
//{
//	// 提示用户
//	MessageBox( L"分配内存失败！", L"系统提示", MB_ICONINFORMATION | MB_OK);
//}

// 解除锁定
::GlobalUnlock((HGLOBAL)pDoc->GetHObject());

// 恢复光标
EndWaitCursor();

}

//中值滤波
void CMFCTest1View::OnEnhaMidianf()
{
	// TODO: 在此添加命令处理程序代码
	// 获取文档	
	CMFCTest1Doc* pDoc = GetDocument();
	// 指向DIB的指针
	LPSTR	lpDIB;
	// 指向DIB象素指针
	LPSTR   lpDIBBits;
	// 滤波器的高度
	int iFilterH;

	// 滤波器的宽度
	int iFilterW;

	// 中心元素的X坐标
	int iFilterMX;

	// 中心元素的Y坐标
	int iFilterMY;

	// 锁定DIB
	lpDIB = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());

	// 找到DIB图像象素起始位置
	lpDIBBits = pDoc->m_dib.GetBits(lpDIB);
	long lpDIBWidth = pDoc->m_dib.GetWidth(lpDIB);					// 获取图象的宽度
	long lpDIBHeight = pDoc->m_dib.GetHeight(lpDIB);					// 获取图象的高度

	// 判断是否是8-bip位图（这里为了方便，只处理8-bip位图的中值滤波，其它的可以类推）
	if (pDoc->m_dib.GetBitCount(lpDIB) != 8)
	{
		// 提示用户
		MessageBox(L"目前只支持256色位图的中值滤波！", L"系统提示", MB_ICONINFORMATION | MB_OK);

		// 解除锁定
		::GlobalUnlock((HGLOBAL)pDoc->GetHObject());

		// 返回
		return;
	}

	// 创建对话框
	CDlgMidFilter dlgPara;
    
	// 初始化对话框变量值
	dlgPara.m_iFilterType = 0;
	dlgPara.m_iFilterH = 3;
	dlgPara.m_iFilterW = 1;
	dlgPara.m_iFilterMX = 0;
	dlgPara.m_iFilterMY = 1;

	// 显示对话框，提示用户设定平移量
	if (dlgPara.DoModal() != IDOK)
	{
		// 返回
		return;
	}

	// 获取用户的设定
	iFilterH = dlgPara.m_iFilterH;
	iFilterW = dlgPara.m_iFilterW;
	iFilterMX = dlgPara.m_iFilterMX;
	iFilterMY = dlgPara.m_iFilterMY;

	// 删除对话框
	delete dlgPara;

	// 更改光标形状
	BeginWaitCursor();

	// 调用MedianFilter()函数中值滤波
	if(::MedianFilter(lpDIBBits, lpDIBWidth, lpDIBHeight, 
		iFilterH, iFilterW, iFilterMX, iFilterMY))
	{
		// 设置文档修改标志
		pDoc->SetModifiedFlag(TRUE);

		// 更新视图
		pDoc->UpdateAllViews(NULL);
	}
	else
	{
		// 提示用户
		MessageBox(L"分配内存失败！", L"系统提示", MB_ICONINFORMATION | MB_OK);
	}

	// 解除锁定
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());

	// 恢复光标
	EndWaitCursor();

}

// 添加随机噪声
BOOL WINAPI AddNoise(LPSTR lpDIBBits, LONG lWidth, LONG lHeight)
{
	// 指向源图像的指针
	LPSTR	lpSrc;

	//循环变量
	long i;
	long j;

	// 图像每行的字节数
	LONG lLineBytes;

	//像素值
	unsigned char pixel;

	//噪声
	BYTE NoisePoint;

	// 计算图像每行的字节数
	lLineBytes = WIDTHBYTES(lWidth * 8);

	//生成伪随机种子
	srand((unsigned)time(NULL));

	//在图像中加噪
	for (j = 0; j < lHeight; j++)
	{
		for (i = 0; i < lLineBytes; i++)
		{
			NoisePoint = rand() / 1024;

			// 指向源图像倒数第j行，第i个象素的指针			
			lpSrc = (char*)lpDIBBits + lLineBytes * j + i;

			//取得像素值
			pixel = (unsigned char)*lpSrc;

			*lpSrc = (unsigned char)(pixel * 224 / 256 + NoisePoint);
		}
	}
	// 返回
	return true;
}

//添加噪声
void CMFCTest1View::OnNoise()
{
	// TODO: 在此添加命令处理程序代码
	// 获取文档
	CMFCTest1Doc* pDoc = GetDocument();

	// 指向DIB的指针
	LPSTR	lpDIB;

	// 指向DIB象素指针
	LPSTR   lpDIBBits;

	// 锁定DIB
	lpDIB = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());

	// 判断是否是8-bpp位图（这里为了方便，只处理8-bpp位图的模糊操作，其它的可以类推）
	if (pDoc->m_dib.GetBitCount(lpDIB) != 8)
	{
		// 提示用户
		MessageBox(L"目前只支持256色位图的运算！", L"系统提示", MB_ICONINFORMATION | MB_OK);

		// 解除锁定
		::GlobalUnlock((HGLOBAL)pDoc->GetHObject());

		// 返回
		return;
	}

	// 更改光标形状
	BeginWaitCursor();

	// 找到DIB图像象素起始位置
	lpDIBBits = pDoc->m_dib.GetBits(lpDIB);
	long lpDIBWidth = pDoc->m_dib.GetWidth(lpDIB);					// 获取图象的宽度
	long lpDIBHeight = pDoc->m_dib.GetHeight(lpDIB);					// 获取图象的高度

	// 调用NoiseBlurDIB()函数对DIB进行模糊加噪处理
	if (AddNoise(lpDIBBits, lpDIBWidth, lpDIBHeight))
	{

		// 设置脏标记
		pDoc->SetModifiedFlag(TRUE);

		// 更新视图
		pDoc->UpdateAllViews(NULL);
	}
	else
	{
		// 提示用户
		MessageBox(L"分配内存失败或图像尺寸不符合要求！", L"系统提示", MB_ICONINFORMATION | MB_OK);
	}

	// 解除锁定
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());

	// 恢复光标
	EndWaitCursor();

}

//拉普拉斯锐化
void CMFCTest1View::OnEnhaSharp()
{
	// TODO: 在此添加命令处理程序代码
	// 获取文档
	CMFCTest1Doc* pDoc = GetDocument();
	int neighborhoodType; // 4邻域
	// 指向DIB的指针
	LPSTR lpDIB;

	// 指向DIB象素指针
	LPSTR    lpDIBBits;

	// 模板高度
	int		iTempH;

	// 模板宽度
	int		iTempW;

	// 模板系数
	FLOAT	fTempC;

	// 模板中心元素X坐标
	int		iTempMX;

	// 模板中心元素Y坐标
	int		iTempMY;

	// 模板元素数组
	double	aValue[9];

	// 锁定DIB
	lpDIB = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());

	// 找到DIB图像象素起始位置
	lpDIBBits = pDoc->m_dib.GetBits(lpDIB);
	long lpDIBWidth = pDoc->m_dib.GetWidth(lpDIB);					// 获取图象的宽度
	long lpDIBHeight = pDoc->m_dib.GetHeight(lpDIB);					// 获取图象的高度

	// 判断是否是8-bpp位图（这里为了方便，只处理8-bpp位图的锐化，其它的可以类推）
	if (pDoc->m_dib.GetBitCount(lpDIB) != 8)
	{
		// 提示用户
		MessageBox(L"目前只支持256色位图的锐化！", L"系统提示",
			MB_ICONINFORMATION | MB_OK);

		// 解除锁定
		::GlobalUnlock((HGLOBAL)pDoc->GetHObject());

		// 返回
		return;
	}

	// 创建对话框
	Dlg_EnhaSharp dlgPara;

	// 初始化变量值
	dlgPara.m_neighborhoodType = 0;

	// 显示对话框，提示用户设定平移量
	if (dlgPara.DoModal() != IDOK)
	{
		// 返回
		return;
	}

	// 获取用户设定的平移量
	neighborhoodType = dlgPara.m_neighborhoodType;


	// 更改光标形状
	BeginWaitCursor();

	// 设置拉普拉斯模板参数
	iTempW = 3;
	iTempH = 3;
	fTempC = 1.0;
	iTempMX = 1;
	iTempMY = 1;
	// 根据邻域系统设置拉普拉斯模板参数
	if (neighborhoodType == 0) // 4邻域
	{
		aValue[0] = 0.0; aValue[1] = -1.0; aValue[2] = 0.0;
		aValue[3] = -1.0; aValue[4] = 5.0; aValue[5] = -1.0;
		aValue[6] = 0.0; aValue[7] = -1.0; aValue[8] = 0.0;
	}
	else if (neighborhoodType == 1) // 8邻域
	{
		aValue[0] = -1.0; aValue[1] = -1.0; aValue[2] = -1.0;
		aValue[3] = -1.0; aValue[4] = 9.0; aValue[5] = -1.0;
		aValue[6] = -1.0; aValue[7] = -1.0; aValue[8] = -1.0;
	}

	// 调用Template()函数用拉普拉斯模板锐化DIB
	if (::Template(lpDIBBits, lpDIBWidth, lpDIBHeight,
		iTempH, iTempW, iTempMX, iTempMY, aValue, fTempC))
	{

		// 设置脏标记
		pDoc->SetModifiedFlag(TRUE);

		// 更新视图
		pDoc->UpdateAllViews(NULL);
	}
	else
	{
		// 提示用户
		MessageBox(L"分配内存失败！",L"系统提示", MB_ICONINFORMATION | MB_OK);
	}

	// 解除锁定
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());

	// 恢复光标
	EndWaitCursor();
}

// 最大值滤波器函数
BOOL MaxFilter(LPSTR lpDIBBits, LONG lmageWidth, LONG lmageHeight, int mFilterH, int mFilterW, int mFilterMX, int mFilterMY)
{
	LPBYTE lpImage = (LPBYTE) new char[lmageWidth * lmageHeight];
	if (lpImage == NULL)
	{
		return FALSE;
	}
	memcpy(lpImage, lpDIBBits, lmageWidth * lmageHeight);

	for (int i = mFilterMY; i < lmageHeight - mFilterH + mFilterMY + 1; i++)
	{
		for (int j = mFilterMX; j < lmageWidth - mFilterW + mFilterMX + 1; j++)
		{
			unsigned char maxVal = 0; // 初始化最大值为最低可能值
			for (int k = 0; k < mFilterH; k++)
			{
				for (int l = 0; l < mFilterW; l++)
				{
					unsigned char* lpSrc = (unsigned char*)lpDIBBits + lmageWidth * (lmageHeight - 1 - i + mFilterMY - k) + j - mFilterMX + l;
					if (*lpSrc > maxVal) maxVal = *lpSrc; // 更新最大值
				}
			}
			unsigned char* lpDst = (unsigned char*)lpImage + lmageWidth * (lmageHeight - 1 - i) + j;
			*lpDst = maxVal; // 将最大值写入目标图像
		}
	}

	memcpy(lpDIBBits, lpImage, lmageWidth * lmageHeight);
	delete[] lpImage;
	return TRUE;
}


//最大值滤波
void CMFCTest1View::OnMaxfilter()
{
	// TODO: 在此添加命令处理程序代码
	// 获取文档
	CMFCTest1Doc* pDoc = GetDocument();
	// 锁定DIB
	LPSTR lpDIB = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());
	// 找到DIB图像象素起始位置
	LPSTR lpDIBBits = pDoc->m_dib.GetBits(lpDIB);
	long lpDIBWidth = pDoc->m_dib.GetWidth(lpDIB);
	long lpDIBHeight = pDoc->m_dib.GetHeight(lpDIB);

	// 判断是否是8-bip位图
	if (pDoc->m_dib.GetBitCount(lpDIB) != 8)
	{
		MessageBox(L"目前只支持256色位图的最大值滤波！", L"系统提示", MB_ICONINFORMATION | MB_OK);
		::GlobalUnlock((HGLOBAL)pDoc->GetHObject());
		return;
	}

	BeginWaitCursor();

	// 调用MaxFilter()函数进行最大值滤波，固定参数
	if (::MaxFilter(lpDIBBits, lpDIBWidth, lpDIBHeight, 3, 3, 1, 1))
	{
		pDoc->SetModifiedFlag(TRUE);
		pDoc->UpdateAllViews(NULL);
	}
	else
	{
		MessageBox(L"分配内存失败！", L"系统提示", MB_ICONINFORMATION | MB_OK);
	}

	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());
	EndWaitCursor();



}

// 最小值滤波器函数
BOOL MinFilter(LPSTR lpDIBBits, LONG lmageWidth, LONG lmageHeight, int mFilterH, int mFilterW, int mFilterMX, int mFilterMY)
{
	LPBYTE lpImage = (LPBYTE)new char[lmageWidth * lmageHeight];
	if (lpImage == NULL)
	{
		return FALSE;
	}
	memcpy(lpImage, lpDIBBits, lmageWidth * lmageHeight);

	for (int i = mFilterMY; i < lmageHeight - mFilterH + mFilterMY + 1; i++)
	{
		for (int j = mFilterMX; j < lmageWidth - mFilterW + mFilterMX + 1; j++)
		{
			unsigned char minVal = 255; // 初始化最小值为最高可能值
			for (int k = 0; k < mFilterH; k++)
			{
				for (int l = 0; l < mFilterW; l++)
				{
					unsigned char* lpSrc = (unsigned char*)lpDIBBits + lmageWidth * (lmageHeight - 1 - i + mFilterMY - k) + j - mFilterMX + l;
					if (*lpSrc < minVal) minVal = *lpSrc; // 更新最小值
				}
			}
			unsigned char* lpDst = (unsigned char*)lpImage + lmageWidth * (lmageHeight - 1 - i) + j;
			*lpDst = minVal; // 将最小值写入目标图像
		}
	}

	memcpy(lpDIBBits, lpImage, lmageWidth * lmageHeight);
	delete[] lpImage;
	return TRUE;
}

void CMFCTest1View::OnMinfilter()
{
	// TODO: 在此添加命令处理程序代码
	 // 获取文档
	CMFCTest1Doc* pDoc = GetDocument();
	// 锁定DIB
	LPSTR lpDIB = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());
	// 找到DIB图像象素起始位置
	LPSTR lpDIBBits = pDoc->m_dib.GetBits(lpDIB);
	long lpDIBWidth = pDoc->m_dib.GetWidth(lpDIB);
	long lpDIBHeight = pDoc->m_dib.GetHeight(lpDIB);

	// 判断是否是8-bip位图
	if (pDoc->m_dib.GetBitCount(lpDIB) != 8)
	{
		MessageBox(L"目前只支持256色位图的最小值滤波！", L"系统提示", MB_ICONINFORMATION | MB_OK);
		::GlobalUnlock((HGLOBAL)pDoc->GetHObject());
		return;
	}

	BeginWaitCursor();

	// 调用MinFilter()函数进行最小值滤波，固定参数
	if (::MinFilter(lpDIBBits, lpDIBWidth, lpDIBHeight, 3, 3, 1, 1))
	{
		pDoc->SetModifiedFlag(TRUE);
		pDoc->UpdateAllViews(NULL);
	}
	else
	{
		MessageBox(L"分配内存失败！", L"系统提示", MB_ICONINFORMATION | MB_OK);
	}

	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());
	EndWaitCursor();

}

// 中点滤波器函数
BOOL MidpointFilter(LPSTR lpDIBBits, LONG lmageWidth, LONG lmageHeight, int mFilterH, int mFilterW, int mFilterMX, int mFilterMY)
{
	LPBYTE lpImage = (LPBYTE) new char[lmageWidth * lmageHeight];
	if (lpImage == NULL)
	{
		return FALSE;
	}
	memcpy(lpImage, lpDIBBits, lmageWidth * lmageHeight);

	for (int i = mFilterMY; i < lmageHeight - mFilterH + mFilterMY + 1; i++)
	{
		for (int j = mFilterMX; j < lmageWidth - mFilterW + mFilterMX + 1; j++)
		{
			unsigned char maxVal = 0; // 初始化最大值为最低可能值
			unsigned char minVal = 255; // 初始化最小值为最高可能值
			for (int k = 0; k < mFilterH; k++)
			{
				for (int l = 0; l < mFilterW; l++)
				{
					unsigned char* lpSrc = (unsigned char*)lpDIBBits + lmageWidth * (lmageHeight - 1 - i + mFilterMY - k) + j - mFilterMX + l;
					if (*lpSrc > maxVal) maxVal = *lpSrc; // 更新最大值
					if (*lpSrc < minVal) minVal = *lpSrc; // 更新最小值
				}
			}
			unsigned char* lpDst = (unsigned char*)lpImage + lmageWidth * (lmageHeight - 1 - i) + j;
			*lpDst = (unsigned char)((maxVal + minVal) / 2); // 将最大值和最小值的平均值写入目标图像
		}
	}

	memcpy(lpDIBBits, lpImage, lmageWidth * lmageHeight);
	delete[] lpImage;
	return TRUE;
}

// 中点滤波
void CMFCTest1View::OnMidpointfilter()
{
	// TODO: 在此添加命令处理程序代码
	// 获取文档
	CMFCTest1Doc* pDoc = GetDocument();
	// 锁定DIB
	LPSTR lpDIB = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());
	// 找到DIB图像象素起始位置
	LPSTR lpDIBBits = pDoc->m_dib.GetBits(lpDIB);
	long lpDIBWidth = pDoc->m_dib.GetWidth(lpDIB);
	long lpDIBHeight = pDoc->m_dib.GetHeight(lpDIB);

	// 判断是否是8-bip位图
	if (pDoc->m_dib.GetBitCount(lpDIB) != 8)
	{
		MessageBox(L"目前只支持256色位图的中点滤波！", L"系统提示", MB_ICONINFORMATION | MB_OK);
		::GlobalUnlock((HGLOBAL)pDoc->GetHObject());
		return;
	}

	BeginWaitCursor();

	// 调用MidpointFilter()函数进行中点滤波，固定参数
	if (::MidpointFilter(lpDIBBits, lpDIBWidth, lpDIBHeight, 3, 3, 1, 1))
	{
		pDoc->SetModifiedFlag(TRUE);
		pDoc->UpdateAllViews(NULL);
	}
	else
	{
		MessageBox(L"分配内存失败！", L"系统提示", MB_ICONINFORMATION | MB_OK);
	}

	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());
	EndWaitCursor();
}

// 自适应中值滤波器函数
BOOL AdaptiveMedianFilter(LPSTR lpDIBBits, LONG lmageWidth, LONG lmageHeight, int minSize, int maxSize)
{
	LPBYTE lpImage = (LPBYTE) new char[lmageWidth * lmageHeight];
	if (lpImage == NULL)
	{
		return FALSE;
	}
	memcpy(lpImage, lpDIBBits, lmageWidth * lmageHeight);

	std::vector<unsigned char> window;

	for (int y = 0; y < lmageHeight; y++)
	{
		for (int x = 0; x < lmageWidth; x++)
		{
			int filterSize = minSize;
			bool filterDone = false;
			unsigned char pixel = 0;

			while (!filterDone && filterSize <= maxSize)
			{
				window.clear();
				int halfSize = filterSize / 2;

				for (int i = -halfSize; i <= halfSize; i++)
				{
					for (int j = -halfSize; j <= halfSize; j++)
					{
						int nx = x + j;
						int ny = y + i;

						if (nx >= 0 && nx < lmageWidth && ny >= 0 && ny < lmageHeight)
						{
							window.push_back(lpDIBBits[lmageWidth * ny + nx]);
						}
					}
				}

				std::sort(window.begin(), window.end());
				unsigned char med = window[window.size() / 2];
				unsigned char medMin = window.front();
				unsigned char medMax = window.back();

				if (medMin < med && med < medMax)
				{
					pixel = med;
					filterDone = true;
				}
				else
				{
					filterSize += 2; // 增加窗口尺寸
				}
			}

			if (!filterDone)
			{
				pixel = lpDIBBits[lmageWidth * y + x]; // 使用原像素值
			}

			lpImage[lmageWidth * y + x] = pixel;
		}
	}

	memcpy(lpDIBBits, lpImage, lmageWidth * lmageHeight);
	delete[] lpImage;
	return TRUE;
}

void CMFCTest1View::OnAdapmedfilter()
{
	// TODO: 在此添加命令处理程序代码
	// 获取文档
	CMFCTest1Doc* pDoc = GetDocument();
	// 锁定DIB
	LPSTR lpDIB = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());
	// 找到DIB图像象素起始位置
	LPSTR lpDIBBits = pDoc->m_dib.GetBits(lpDIB);
	long lpDIBWidth = pDoc->m_dib.GetWidth(lpDIB);
	long lpDIBHeight = pDoc->m_dib.GetHeight(lpDIB);

	// 判断是否是8-bip位图
	if (pDoc->m_dib.GetBitCount(lpDIB) != 8)
	{
		MessageBox(L"目前只支持256色位图的自适应中值滤波！", L"系统提示", MB_ICONINFORMATION | MB_OK);
		::GlobalUnlock((HGLOBAL)pDoc->GetHObject());
		return;
	}

	BeginWaitCursor();

	// 调用AdaptiveMedianFilter()函数进行自适应中值滤波，固定参数
	if (::AdaptiveMedianFilter(lpDIBBits, lpDIBWidth, lpDIBHeight, 3, 7))
	{
		pDoc->SetModifiedFlag(TRUE);
		pDoc->UpdateAllViews(NULL);
	}
	else
	{
		MessageBox(L"分配内存失败！", L"系统提示", MB_ICONINFORMATION | MB_OK);
	}

	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());
	EndWaitCursor();
}

/*************************************************************************
 *
 * 函数名称：
 *   RobertDIB()
 *
 * 参数:
 *   LPSTR lpDIBBits    - 指向源DIB图像指针
 *   LONG  lWidth       - 源图像宽度（象素数，必须是4的倍数）
 *   LONG  lHeight      - 源图像高度（象素数）
 * 返回值:
 *   BOOL               - 边缘检测成功返回TRUE，否则返回FALSE。
 *
 * 说明:
 * 该函数用Robert边缘检测算子对图像进行边缘检测运算。
 *
 * 要求目标图像为灰度图像。
 ************************************************************************/

BOOL WINAPI RobertDIB(LPSTR lpDIBBits, LONG lWidth, LONG lHeight)
{

	// 指向源图像的指针
	LPSTR	lpSrc;

	// 指向缓存图像的指针
	LPSTR	lpDst;

	// 指向缓存DIB图像的指针
	LPSTR	lpNewDIBBits;
	HLOCAL	hNewDIBBits;

	//循环变量
	long i;
	long j;

	//像素值
	double result;
	unsigned char pixel[4];

	// 暂时分配内存，以保存新图像
	hNewDIBBits = LocalAlloc(LHND, lWidth * lHeight);

	if (hNewDIBBits == NULL)
	{
		// 分配内存失败
		return FALSE;
	}

	// 锁定内存
	lpNewDIBBits = (char*)LocalLock(hNewDIBBits);

	// 初始化新分配的内存，设定初始值为255
	lpDst = (char*)lpNewDIBBits;
	memset(lpDst, (BYTE)255, static_cast<size_t>(lWidth) * lHeight);


	//使用水平方向的结构元素进行腐蚀
	for (j = lHeight - 1; j > 0; j--)
	{
		for (i = 0; i < lWidth - 1; i++)
		{
			//由于使用2×2的模板，为防止越界，所以不处理最下边和最右边的两列像素

			// 指向源图像第j行，第i个象素的指针			
			lpSrc = (char*)lpDIBBits + lWidth * j + i;

			// 指向目标图像第j行，第i个象素的指针			
			lpDst = (char*)lpNewDIBBits + lWidth * j + i;

			//取得当前指针处2*2区域的像素值，注意要转换为unsigned char型
			pixel[0] = (unsigned char)*lpSrc;
			pixel[1] = (unsigned char)*(lpSrc + 1);
			pixel[2] = (unsigned char)*(lpSrc - lWidth);
			pixel[3] = (unsigned char)*(lpSrc - lWidth + 1);

			//计算目标图像中的当前点
			result = sqrt((pixel[0] - pixel[3]) * (pixel[0] - pixel[3]) + \
				(pixel[1] - pixel[2]) * (pixel[1] - pixel[2]));
			*lpDst = (unsigned char)result;

		}
	}

	// 复制腐蚀后的图像
	memcpy(lpDIBBits, lpNewDIBBits, lWidth * lHeight);

	// 释放内存
	LocalUnlock(hNewDIBBits);
	LocalFree(hNewDIBBits);

	// 返回
	return TRUE;
}


void CMFCTest1View::OnEdgeRobert()
{
	// TODO: 在此添加命令处理程序代码

	//Robert边缘检测运算

	// 获取文档
	CMFCTest1Doc* pDoc = GetDocument();

	// 指向DIB的指针
	LPSTR	lpDIB;

	// 指向DIB象素指针
	LPSTR   lpDIBBits;

	// 锁定DIB
	lpDIB = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());

	// 判断是否是8-bpp位图（这里为了方便，只处理8-bpp位图的边缘检测，其它的可以类推）
	if (pDoc->m_dib.GetBitCount(lpDIB) != 8)
	{
		// 提示用户
		MessageBox(L"目前只支持256色位图的运算！", L"系统提示", MB_ICONINFORMATION | MB_OK);

		// 解除锁定
		::GlobalUnlock((HGLOBAL)pDoc->GetHObject());

		// 返回
		return;
	}

	// 更改光标形状
	BeginWaitCursor();

	// 找到DIB图像象素起始位置
	lpDIBBits = pDoc->m_dib.GetBits(lpDIB);
	long lpDIBWidth = pDoc->m_dib.GetWidth(lpDIB);
	long lpDIBHeight = pDoc->m_dib.GetHeight(lpDIB);

	// 调用RobertDIB()函数对DIB进行边缘检测
	if (RobertDIB(lpDIBBits, WIDTHBYTES(lpDIBWidth * 8), lpDIBHeight))
	{

		// 设置脏标记
		pDoc->SetModifiedFlag(TRUE);

		// 更新视图
		pDoc->UpdateAllViews(NULL);
	}
	else
	{
		// 提示用户
		MessageBox(L"分配内存失败！", L"系统提示", MB_ICONINFORMATION | MB_OK);
	}

	// 解除锁定
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());

	// 恢复光标
	EndWaitCursor();

}



/*************************************************************************
 *
 * 函数名称：
 *   SobelDIB()
 *
 * 参数:
 *   LPSTR lpDIBBits    - 指向源DIB图像指针
 *   LONG  lWidth       - 源图像宽度（象素数，必须是4的倍数）
 *   LONG  lHeight      - 源图像高度（象素数）
 * 返回值:
 *   BOOL               - 边缘检测成功返回TRUE，否则返回FALSE。
 *
 * 说明:
 * 该函数用Sobel边缘检测算子对图像进行边缘检测运算。
 *
 * 要求目标图像为灰度图像。
 ************************************************************************/

BOOL WINAPI SobelDIB(LPSTR lpDIBBits, LONG lWidth, LONG lHeight)
{

	// 指向缓存图像的指针
	LPSTR	lpDst1;
	LPSTR	lpDst2;

	// 指向缓存DIB图像的指针
	LPSTR	lpNewDIBBits1;
	HLOCAL	hNewDIBBits1;
	LPSTR	lpNewDIBBits2;
	HLOCAL	hNewDIBBits2;

	//循环变量
	long i;
	long j;

	// 模板高度
	int		iTempH;

	// 模板宽度
	int		iTempW;

	// 模板系数
	FLOAT	fTempC;

	// 模板中心元素X坐标
	int		iTempMX;

	// 模板中心元素Y坐标
	int		iTempMY;

	//模板数组
	double aTemplate[9];

	// 暂时分配内存，以保存新图像
	hNewDIBBits1 = LocalAlloc(LHND, lWidth * lHeight);

	if (hNewDIBBits1 == NULL)
	{
		// 分配内存失败
		return FALSE;
	}

	// 锁定内存
	lpNewDIBBits1 = (char*)LocalLock(hNewDIBBits1);

	// 暂时分配内存，以保存新图像
	hNewDIBBits2 = LocalAlloc(LHND, lWidth * lHeight);

	if (hNewDIBBits2 == NULL)
	{
		// 分配内存失败
		return FALSE;
	}

	// 锁定内存
	lpNewDIBBits2 = (char*)LocalLock(hNewDIBBits2);

	// 拷贝源图像到缓存图像中
	lpDst1 = (char*)lpNewDIBBits1;
	memcpy(lpNewDIBBits1, lpDIBBits, lWidth * lHeight);
	lpDst2 = (char*)lpNewDIBBits2;
	memcpy(lpNewDIBBits2, lpDIBBits, static_cast<size_t>(lWidth) * lHeight);

	// 设置Sobel模板参数
	iTempW = 3;
	iTempH = 3;
	fTempC = 1.0;
	iTempMX = 2;
	iTempMY = 2;
	aTemplate[0] = 1.0;
	aTemplate[1] = 2.0;
	aTemplate[2] = 1.0;
	aTemplate[3] = 0.0;
	aTemplate[4] = 0.0;
	aTemplate[5] = 0.0;
	aTemplate[6] = -1.0;
	aTemplate[7] = -2.0;
	aTemplate[8] = -1.0;

	// 调用Template()函数
	if (!Template(lpNewDIBBits1, lWidth, lHeight,
		iTempH, iTempW, iTempMX, iTempMY, aTemplate, fTempC))
	{
		return FALSE;
	}

	// 设置Sobel模板参数
	aTemplate[0] = -1.0;
	aTemplate[1] = 0.0;
	aTemplate[2] = 1.0;
	aTemplate[3] = -2.0;
	aTemplate[4] = 0.0;
	aTemplate[5] = 2.0;
	aTemplate[6] = -1.0;
	aTemplate[7] = 0.0;
	aTemplate[8] = 1.0;

	// 调用Template()函数
	if (!Template(lpNewDIBBits2, lWidth, lHeight,
		iTempH, iTempW, iTempMX, iTempMY, aTemplate, fTempC))
	{
		return FALSE;
	}

	//求两幅缓存图像的最大值
	for (j = 0; j < lHeight; j++)
	{
		for (i = 0; i < lWidth - 1; i++)
		{

			// 指向缓存图像1倒数第j行，第i个象素的指针			
			lpDst1 = (char*)lpNewDIBBits1 + lWidth * j + i;

			// 指向缓存图像2倒数第j行，第i个象素的指针			
			lpDst2 = (char*)lpNewDIBBits2 + lWidth * j + i;

			if (*lpDst2 > *lpDst1)
				*lpDst1 = *lpDst2;

		}
	}

	// 复制经过模板运算后的图像到源图像
	memcpy(lpDIBBits, lpNewDIBBits1, lWidth * lHeight);

	// 释放内存
	LocalUnlock(hNewDIBBits1);
	LocalFree(hNewDIBBits1);

	LocalUnlock(hNewDIBBits2);
	LocalFree(hNewDIBBits2);
	// 返回
	return TRUE;
}


//Sobel算子
void CMFCTest1View::OnEdgeSobel()
{
	// TODO: 在此添加命令处理程序代码

	//Sobel边缘检测运算

	// 获取文档
	CMFCTest1Doc* pDoc = GetDocument();

	// 指向DIB的指针
	LPSTR	lpDIB;

	// 指向DIB象素指针
	LPSTR   lpDIBBits;

	// 锁定DIB
	lpDIB = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());

	// 判断是否是8-bpp位图（这里为了方便，只处理8-bpp位图的边缘检测，其它的可以类推）
	if (pDoc->m_dib.GetBitCount(lpDIB) != 8)
	{
		// 提示用户
		MessageBox(L"目前只支持256色位图的运算！", L"系统提示", MB_ICONINFORMATION | MB_OK);

		// 解除锁定
		::GlobalUnlock((HGLOBAL)pDoc->GetHObject());

		// 返回
		return;
	}

	// 更改光标形状
	BeginWaitCursor();

	// 找到DIB图像象素起始位置
	lpDIBBits = pDoc->m_dib.GetBits(lpDIB);
	long lpDIBWidth = pDoc->m_dib.GetWidth(lpDIB);
	long lpDIBHeight = pDoc->m_dib.GetHeight(lpDIB);

	// 调用SobelDIB()函数对DIB进行边缘检测
	if (SobelDIB(lpDIBBits, WIDTHBYTES(lpDIBWidth * 8), lpDIBHeight))
	{

		// 设置脏标记
		pDoc->SetModifiedFlag(TRUE);

		// 更新视图
		pDoc->UpdateAllViews(NULL);
	}
	else
	{
		// 提示用户
		MessageBox(L"分配内存失败！", L"系统提示", MB_ICONINFORMATION | MB_OK);
	}

	// 解除锁定
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());

	// 恢复光标
	EndWaitCursor();

}

//添加椒盐噪声
BOOL WINAPI SaltNoiseDIB(LPSTR lpDIBBits, LONG lWidth, LONG lHeight)
{
	// 指向源图像的指针
	LPSTR lpSrc;

	// 循环变量
	long i;
	long j;

	// 图像每行的字节数
	LONG lLineBytes;

	// 计算图像每行的字节数
	lLineBytes = WIDTHBYTES(lWidth * 8);

	// 生成伪随机种子
	srand((unsigned)time(NULL));

	// 在图像中加噪
	for (j = 0; j < lHeight; j++)
	{
		for (i = 0; i < lLineBytes; i++)
		{
			// 产生随机数决定是否加噪以及加哪种噪声
			int randomValue = rand();
			if (randomValue > 31500)
			{
				// 指向源图像倒数第j行，第i个像素的指针
				lpSrc = (char*)lpDIBBits + lLineBytes * j + i;

				if (randomValue % 2 == 0) {
					// 图像中当前点置为黑色
					*lpSrc = 0;
				}
				else {
					// 图像中当前点置为白色
					*lpSrc = 255;
				}
			}
		}
	}
	// 返回
	return true;
}


//椒盐噪声
void CMFCTest1View::OnRestoreSaltnoise()
{
	// TODO: 在此添加命令处理程序代码
	// 获取文档
	CMFCTest1Doc* pDoc = GetDocument();

	// 指向DIB的指针
	LPSTR	lpDIB;

	// 指向DIB象素指针
	LPSTR   lpDIBBits;

	// 锁定DIB
	lpDIB = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());

	// 判断是否是8-bpp位图（这里为了方便，只处理8-bpp位图的模糊操作，其它的可以类推）
	if (pDoc->m_dib.GetBitCount(lpDIB) != 8)
	{
		// 提示用户
		MessageBox(L"目前只支持256色位图的运算！", L"系统提示", MB_ICONINFORMATION | MB_OK);

		// 解除锁定
		::GlobalUnlock((HGLOBAL)pDoc->GetHObject());

		// 返回
		return;
	}

	// 更改光标形状
	BeginWaitCursor();

	// 找到DIB图像象素起始位置
	lpDIBBits = pDoc->m_dib.GetBits(lpDIB);
	long lpDIBWidth = pDoc->m_dib.GetWidth(lpDIB);
	long lpDIBHeight = pDoc->m_dib.GetHeight(lpDIB);

	// 调用SaltNoiseDIB()函数对DIB进行加噪处理
	if (SaltNoiseDIB(lpDIBBits, lpDIBWidth, lpDIBHeight))
	{

		// 设置脏标记
		pDoc->SetModifiedFlag(TRUE);

		// 更新视图
		pDoc->UpdateAllViews(NULL);
	}
	else
	{
		// 提示用户
		MessageBox(L"分配内存失败！",L"系统提示", MB_ICONINFORMATION | MB_OK);
	}

	// 解除锁定
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());

	// 恢复光标
	EndWaitCursor();
}

BOOL WINAPI ErosionDIB(LPSTR lpDIBBits, LONG lWidth, LONG lHeight, int nMode, int ForeMode, int structure[3][3])
{
	// 根据 ForeMode 设置前景和背景色
	BYTE foreground = (ForeMode == 0) ? 255 : 0;  // 白色或黑色前景
	BYTE background = (ForeMode == 0) ? 0 : 255;  // 反色

	// 创建缓存图像
	std::vector<BYTE> buffer(lWidth * lHeight, background);
	LPSTR lpNewDIBBits = reinterpret_cast<LPSTR>(buffer.data());

	// 根据不同的 nMode 设置结构元素和进行腐蚀处理
	switch (nMode)
	{
	case 0:  // 水平方向
		for (LONG j = 0; j < lHeight; j++) {
			for (LONG i = 1; i < lWidth - 1; i++) {
				BYTE left = *(lpDIBBits + lWidth * j + i - 1);
				BYTE middle = *(lpDIBBits + lWidth * j + i);
				BYTE right = *(lpDIBBits + lWidth * j + i + 1);

				if (left == foreground && middle == foreground && right == foreground)
					*(lpNewDIBBits + lWidth * j + i) = foreground;
			}
		}
		break;

	case 1:  // 垂直方向
		for (LONG i = 0; i < lWidth; i++) {
			for (LONG j = 1; j < lHeight - 1; j++) {
				BYTE top = *(lpDIBBits + lWidth * (j - 1) + i);
				BYTE middle = *(lpDIBBits + lWidth * j + i);
				BYTE bottom = *(lpDIBBits + lWidth * (j + 1) + i);

				if (top == foreground && middle == foreground && bottom == foreground)
					*(lpNewDIBBits + lWidth * j + i) = foreground;
			}
		}
		break;

	case 2:  // 自定义结构元素
		for (LONG j = 1; j < lHeight - 1; j++) {
			for (LONG i = 1; i < lWidth - 1; i++) {
				BOOL allForeground = TRUE;
				for (int m = -1; m <= 1 && allForeground; m++) {
					for (int n = -1; n <= 1 && allForeground; n++) {
						if (structure[m + 1][n + 1] == 0) {
							BYTE pixel = *(lpDIBBits + lWidth * (j + m) + (i + n));
							if (pixel != foreground) {
								allForeground = FALSE;
							}
						}
					}
				}
				*(lpNewDIBBits + lWidth * j + i) = allForeground ? foreground : background;
			}
		}
		break;
	}

	// 复制腐蚀后的图像回原始图像指针
	memcpy(lpDIBBits, lpNewDIBBits, lWidth * lHeight);
	return TRUE;
}

//膨胀
BOOL WINAPI DilationDIB(LPSTR lpDIBBits, LONG lWidth, LONG lHeight, int nMode, int ForeMode, int structure[3][3])
{
	// 根据 ForeMode 设置前景和背景色
	BYTE foreground = (ForeMode == 0) ? 255 : 0;  // 白色或黑色前景
	BYTE background = (ForeMode == 0) ? 0 : 255;  // 反色

	// 创建缓存图像
	std::vector<BYTE> buffer(lWidth * lHeight, background);
	LPSTR lpNewDIBBits = reinterpret_cast<LPSTR>(buffer.data());

	// 根据不同的 nMode 设置结构元素和进行膨胀处理
	switch (nMode)
	{
	case 0:  // 水平方向
		for (LONG j = 0; j < lHeight; j++) {
			for (LONG i = 1; i < lWidth - 1; i++) {
				BYTE left = *(lpDIBBits + lWidth * j + i - 1);
				BYTE middle = *(lpDIBBits + lWidth * j + i);
				BYTE right = *(lpDIBBits + lWidth * j + i + 1);

				if (left == foreground || middle == foreground || right == foreground)
					*(lpNewDIBBits + lWidth * j + i) = foreground;
			}
		}
		break;

	case 1:  // 垂直方向
		for (LONG i = 0; i < lWidth; i++) {
			for (LONG j = 1; j < lHeight - 1; j++) {
				BYTE top = *(lpDIBBits + lWidth * (j - 1) + i);
				BYTE middle = *(lpDIBBits + lWidth * j + i);
				BYTE bottom = *(lpDIBBits + lWidth * (j + 1) + i);

				if (top == foreground || middle == foreground || bottom == foreground)
					*(lpNewDIBBits + lWidth * j + i) = foreground;
			}
		}
		break;

	case 2:  // 自定义结构元素
		for (LONG j = 1; j < lHeight - 1; j++) {
			for (LONG i = 1; i < lWidth - 1; i++) {
				BOOL anyForeground = FALSE;
				for (int m = -1; m <= 1 && !anyForeground; m++) {
					for (int n = -1; n <= 1 && !anyForeground; n++) {
						if (structure[m + 1][n + 1] == 0) {
							BYTE pixel = *(lpDIBBits + lWidth * (j + m) + (i + n));
							if (pixel == foreground) {
								anyForeground = TRUE;
							}
						}
					}
				}
				*(lpNewDIBBits + lWidth * j + i) = anyForeground ? foreground : background;
			}
		}
		break;
	}

	// 复制膨胀后的图像回原始图像指针
	memcpy(lpDIBBits, lpNewDIBBits, lWidth * lHeight);
	return TRUE;
}

//开启
BOOL WINAPI OpeningDIB(LPSTR lpDIBBits, LONG lWidth, LONG lHeight, int nMode, int ForeMode, int structure[3][3])
{
	// 首先进行腐蚀处理
	if (!ErosionDIB(lpDIBBits, lWidth, lHeight, nMode, ForeMode, structure)) {
		return FALSE;  // 如果腐蚀失败，则直接返回失败
	}

	// 接着进行膨胀处理
	if (!DilationDIB(lpDIBBits, lWidth, lHeight, nMode, ForeMode, structure)) {
		return FALSE;  // 如果膨胀失败，也返回失败
	}

	return TRUE;  // 两个操作都成功执行，则返回成功
}

//闭合
BOOL WINAPI ClosingDIB(LPSTR lpDIBBits, LONG lWidth, LONG lHeight, int nMode, int ForeMode, int structure[3][3])
{
	// 首先进行膨胀处理
	if (!DilationDIB(lpDIBBits, lWidth, lHeight, nMode, ForeMode, structure)) {
		return FALSE;  // 如果膨胀失败，则直接返回失败
	}

	// 接着进行腐蚀处理
	if (!ErosionDIB(lpDIBBits, lWidth, lHeight, nMode, ForeMode, structure)) {
		return FALSE;  // 如果腐蚀失败，也返回失败
	}

	return TRUE;  // 两个操作都成功执行，则返回成功
}

//内边界
BOOL WINAPI InnerBoundaryDIB(LPSTR lpDIBBits, LONG lWidth, LONG lHeight, int nMode, int ForeMode, int structure[3][3])
{
	// 创建一个临时缓存以保存腐蚀后的图像
	std::vector<BYTE> buffer(lWidth * lHeight);
	memcpy(buffer.data(), lpDIBBits, lWidth * lHeight);  // 复制原图像到缓存

	// 对临时图像执行腐蚀操作
	if (!ErosionDIB(reinterpret_cast<LPSTR>(buffer.data()), lWidth, lHeight, nMode, ForeMode, structure)) {
		return FALSE;  // 如果腐蚀失败，则直接返回失败
	}

	// 原图像与腐蚀后的图像相减，提取内边界
	for (LONG i = 0; i < lHeight * lWidth; i++) {
		BYTE originalPixel = static_cast<BYTE>(lpDIBBits[i]);
		BYTE erodedPixel = static_cast<BYTE>(buffer[i]);
		lpDIBBits[i] = (originalPixel != erodedPixel) ? 255 : 0;  // 假设边界为白色，非边界为黑色
	}

	return TRUE;
}


//外边界
BOOL WINAPI OuterBoundaryDIB(LPSTR lpDIBBits, LONG lWidth, LONG lHeight, int nMode, int ForeMode, int structure[3][3])
{
	// 创建一个临时缓存以保存膨胀后的图像
	std::vector<BYTE> buffer(lWidth * lHeight);
	memcpy(buffer.data(), lpDIBBits, lWidth * lHeight);  // 复制原图像到缓存

	// 对临时图像执行膨胀操作
	if (!DilationDIB(reinterpret_cast<LPSTR>(buffer.data()), lWidth, lHeight, nMode, ForeMode, structure)) {
		return FALSE;  // 如果膨胀失败，则直接返回失败
	}

	// 原图像与膨胀后的图像相减，提取外边界
	for (LONG i = 0; i < lHeight * lWidth; i++) {
		BYTE originalPixel = static_cast<BYTE>(lpDIBBits[i]);
		BYTE dilatedPixel = static_cast<BYTE>(buffer[i]);
		lpDIBBits[i] = (originalPixel != dilatedPixel) ? 255 : 0;  // 假设边界为白色，非边界为黑色
	}

	return TRUE;
}


//形态学处理总菜单
void CMFCTest1View::OnMorphologyMainmenu()
{
	// TODO: 在此添加命令处理程序代码
	//获取文档
	CMFCTest1Doc* pDoc = GetDocument();

	//获取DIB指针
	LPSTR lpDIB = (LPSTR)::GlobalLock((HGLOBAL)pDoc->GetHObject());

	//指向DIB图像象素的指针
	LPSTR lpDIBBits = pDoc->m_dib.GetBits(lpDIB);
	long lpDIBWidth = pDoc->m_dib.GetWidth(lpDIB);
	long lpDIBHeight = pDoc->m_dib.GetHeight(lpDIB);

	//判断是否是8-bip位图
	if (pDoc->m_dib.GetBitCount(lpDIB) != 8)
	{
		MessageBox(L"目前只支持256色位图的形态学处理！", L"系统提示", MB_ICONINFORMATION | MB_OK);
		::GlobalUnlock((HGLOBAL)pDoc->GetHObject());
		return;
	}

	int nMode=-1;
	int morphType=-1;
	int ForeMode= -1;
	int structure[3][3]{ };
	//显示形态学处理对话框
	DlgMorphMenu dlgPara;

	if (dlgPara.DoModal() != IDOK)
	{
		::GlobalUnlock((HGLOBAL)pDoc->GetHObject());
		return;
	}

	//获取对话框参数
	nMode = dlgPara.m_nMode;
	morphType = dlgPara.m_morphmenu;
	ForeMode = dlgPara.m_ForeMode;
	//debug显示nMode
	//CString str1;
	//str1.Format(L"%d", nMode);
	//MessageBox(str1);
	if (nMode == 2)
	{
		structure[0][0] = dlgPara.m_nStructure1;
		structure[0][1] = dlgPara.m_nStructure2;
		structure[0][2] = dlgPara.m_nStructure3;
		structure[1][0] = dlgPara.m_nStructure4;
		structure[1][1] = dlgPara.m_nStructure5;
		structure[1][2] = dlgPara.m_nStructure6;
		structure[2][0] = dlgPara.m_nStructure7;
		structure[2][1] = dlgPara.m_nStructure8;
		structure[2][2] = dlgPara.m_nStructure9;
		////debug提示框显示struct
		//CString str;
		//str.Format(L"%d %d %d\n%d %d %d\n%d %d %d", structure[0][0], structure[0][1], structure[0][2], structure[1][0], structure[1][1], structure[1][2], structure[2][0], structure[2][1], structure[2][2]);
		//MessageBox(str);
	}
	
	//根据用户选择的操作类型进行相应的操作
	// // 删除对话框
	delete dlgPara;
	// 更改光标形状
	BeginWaitCursor();
	//腐蚀
	if (morphType == 0) {
		
		//调用腐蚀函数
		if (ErosionDIB(lpDIBBits, lpDIBWidth, lpDIBHeight, nMode,ForeMode, structure))
		{
			pDoc->SetModifiedFlag(TRUE);
			pDoc->UpdateAllViews(NULL);
		}
		else
		{
			MessageBox(L"分配内存失败！", L"系统提示", MB_ICONINFORMATION | MB_OK);
		}

		
	}
	//膨胀
	else if (morphType == 1) {
		//调用膨胀函数
		if (DilationDIB(lpDIBBits, lpDIBWidth, lpDIBHeight, nMode, ForeMode, structure))
		{
			pDoc->SetModifiedFlag(TRUE);
			pDoc->UpdateAllViews(NULL);
		}
		else
		{
			MessageBox(L"分配内存失败！", L"系统提示", MB_ICONINFORMATION | MB_OK);
		}
	}
	//开启
	else if (morphType == 2) {
		//调用开启函数
		if (OpeningDIB(lpDIBBits, lpDIBWidth, lpDIBHeight, nMode, ForeMode, structure))
		{
			pDoc->SetModifiedFlag(TRUE);
			pDoc->UpdateAllViews(NULL);
		}
		else
		{
			MessageBox(L"分配内存失败！", L"系统提示", MB_ICONINFORMATION | MB_OK);
		}
	}
	//闭合
	else if (morphType == 3) {
		//调用闭合函数
		if (ClosingDIB(lpDIBBits, lpDIBWidth, lpDIBHeight, nMode, ForeMode, structure))
		{
			pDoc->SetModifiedFlag(TRUE);
			pDoc->UpdateAllViews(NULL);
		}
		else
		{
			MessageBox(L"分配内存失败！", L"系统提示", MB_ICONINFORMATION | MB_OK);
		}
	}
	//内边界
	else if (morphType == 4) {
		//调用内边界函数
		if (InnerBoundaryDIB(lpDIBBits, lpDIBWidth, lpDIBHeight, nMode, ForeMode, structure))
		{
			pDoc->SetModifiedFlag(TRUE);
			pDoc->UpdateAllViews(NULL);
		}
		else
		{
			MessageBox(L"分配内存失败！", L"系统提示", MB_ICONINFORMATION | MB_OK);
		}
	}
	//外边界
	else if (morphType == 5) {
		//调用外边界函数
		if (OuterBoundaryDIB(lpDIBBits, lpDIBWidth, lpDIBHeight, nMode, ForeMode, structure))
		{
			pDoc->SetModifiedFlag(TRUE);
			pDoc->UpdateAllViews(NULL);
		}
		else
		{
			MessageBox(L"分配内存失败！", L"系统提示", MB_ICONINFORMATION | MB_OK);
		}
	}


	//解除锁定
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());

	//恢复光标
	EndWaitCursor();
}


//阈值变换
void CMFCTest1View::OnPointThre()
{
	// TODO: 在此添加命令处理程序代码
	//获取文档
	CMFCTest1Doc* pDoc = GetDocument();

	LPSTR	lpSrcDib;		//指向源图象的指针	
	LPSTR	lpSrcStartBits;	//指向源像素的指针

	//参数对话框
	CDlgPointThre dlgPara;

	//阈值
	BYTE bThre;

	//算法模式
	int AMode;

	//锁定DIB
	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());

	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);			// 找到DIB图象像素起始位置	

	//指向DIB图像象素的指针
	
	long lpDIBWidth = pDoc->m_dib.GetWidth(lpSrcDib);
	long lpDIBHeight = pDoc->m_dib.GetHeight(lpSrcDib);

	//判断是否是8-bip位图
	if (pDoc->m_dib.GetBitCount(lpSrcDib) != 8)
	{
		MessageBox(L"目前只支持256色位图的形态学处理！", L"系统提示", MB_ICONINFORMATION | MB_OK);
		::GlobalUnlock((HGLOBAL)pDoc->GetHObject());
		return;
	}

	//初始化变量值
	dlgPara.m_bThre = 128;
	dlgPara.pDoc = pDoc;

	//显示对话框，提示用户设定阈值
	if (dlgPara.DoModal() != IDOK)
	{
		return;
	}
	//获取用户设定的算法模式
	AMode = dlgPara.m_AMode;

	//// Debug Output for AMode
	//CString strDebug;
	//strDebug.Format(L"AMode = %d", AMode);
	//AfxMessageBox(strDebug);

	//获取用户设定的阈值
	if (AMode != 3) {
		bThre = dlgPara.m_bThre;
		//调用ThresholdTrans()函数进行阈值变换
		::ThresholdTrans(lpSrcStartBits, lpDIBWidth, lpDIBHeight, bThre);
	}
		

	//删除对话框
	delete dlgPara;

	//更改光标形状
	BeginWaitCursor();

	

	//设置脏标记
	pDoc->SetModifiedFlag(TRUE);

	//更新视图
	pDoc->UpdateAllViews(NULL);

	//解除锁定
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());

	//恢复光标
	EndWaitCursor();
}

// 窗口变换
void CMFCTest1View::OnPointwind()
{
	// TODO: 在此添加命令处理程序代码
	// 获取文档
	CMFCTest1Doc* pDoc = GetDocument();

	// 指向DIB的指针
	LPSTR lpDIB;

	// 指向DIB象素指针
	LPSTR    lpDIBBits;

	// 创建对话框
	CDlgPointWin  dlgPara;

	// 窗口下限
	BYTE	bLow;

	// 窗口上限
	BYTE	bUp;

	// 锁定DIB
	lpDIB = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());

	// 找到DIB图像象素起始位置

	lpDIBBits = pDoc->m_dib.GetBits(lpDIB);			// 找到DIB图象像素起始位置	

	long lpDIBWidth = pDoc->m_dib.GetWidth(lpDIB);
	long lpDIBHeight = pDoc->m_dib.GetHeight(lpDIB);

	//判断是否是8-bip位图
	if (pDoc->m_dib.GetBitCount(lpDIB) != 8)
	{
		MessageBox(L"目前只支持256色位图的形态学处理！", L"系统提示", MB_ICONINFORMATION | MB_OK);
		::GlobalUnlock((HGLOBAL)pDoc->GetHObject());
		return;
	}
	// 初始化变量值
	dlgPara.m_bLow = 100;
	dlgPara.m_bUp = 200;
	dlgPara.pDoc = pDoc;

	// 显示对话框，提示用户设定窗口上下限
	if (dlgPara.DoModal() != IDOK)
	{
		// 返回
		return;
	}

	// 获取用户设定的窗口上下限
	bLow = dlgPara.m_bLow;
	bUp = dlgPara.m_bUp;

	// 删除对话框
	delete dlgPara;

	// 更改光标形状
	BeginWaitCursor();

	// 调用WindowTrans()函数进行窗口变换
	WindowTrans(lpDIBBits, lpDIBWidth, lpDIBHeight, bLow, bUp);

	// 设置脏标记
	pDoc->SetModifiedFlag(TRUE);

	// 更新视图
	pDoc->UpdateAllViews(NULL);

	// 解除锁定
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());

	// 恢复光标
	EndWaitCursor();
}

//直方图均衡化
void CMFCTest1View::OnPointequa()
{
	// TODO: 在此添加命令处理程序代码
	// 获取文档
	CMFCTest1Doc* pDoc = GetDocument();

	// 指向DIB的指针
	LPSTR	lpDIB;

	// 指向DIB象素指针
	LPSTR    lpDIBBits;

	// 锁定DIB
	lpDIB = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());

	lpDIBBits = pDoc->m_dib.GetBits(lpDIB);			// 找到DIB图象像素起始位置	

	long lpDIBWidth = pDoc->m_dib.GetWidth(lpDIB);
	long lpDIBHeight = pDoc->m_dib.GetHeight(lpDIB);

	//判断是否是8-bip位图
	if (pDoc->m_dib.GetBitCount(lpDIB) != 8)
	{
		MessageBox(L"目前只支持256色位图的形态学处理！", L"系统提示", MB_ICONINFORMATION | MB_OK);
		::GlobalUnlock((HGLOBAL)pDoc->GetHObject());
		return;
	}

	// 更改光标形状
	BeginWaitCursor();

	// 调用InteEqualize()函数进行直方图均衡
	InteEqualize(lpDIBBits, lpDIBWidth, lpDIBHeight);

	// 设置脏标记
	pDoc->SetModifiedFlag(TRUE);

	// 更新视图
	pDoc->UpdateAllViews(NULL);

	// 解除锁定
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());

	// 恢复光标
	EndWaitCursor();
}


//滤镜（模板操作）
BOOL WINAPI Template_Filter1(LPSTR lpDIBBits, LONG lWidth, LONG lHeight,
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

			fResult += threshold;

			//、、、、、、、、、、、、、、、

			//取绝对值
			fResult = (FLOAT)fabs(fResult);


			// 判断是否超过255
			if (fResult > 255)
			{
				// 直接赋g值为255
				*lpDst = 255;
			}
			else
			{
				// 赋值
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


//滤镜
void CMFCTest1View::OnFilter()
{
	// TODO: 在此添加命令处理程序代码
	//获取文档
	CMFCTest1Doc* pDoc = GetDocument();
	////////////////////////////////////////////////////////////////////////////////////////////////	
	long  lSrcLineBytes;		//图象每行的字节数
	long	  lSrcWidth;      //图象的宽度和高度
	long	  lSrcHeight;
	int    lpSrcBitCount;       //图像的位深
	LPSTR	lpSrcDib;		//指向源图象的指针	
	LPSTR	lpSrcStartBits;	//指向源像素的指针

	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());	//锁定DIB

	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);			// 找到DIB图象像素起始位置	

	/*if (pDoc->m_dib.GetColorNum(lpSrcDib) != 256)// 判断是否是8-bpp位图
	{
		MessageBox("对不起，不是256色位图！");// 警告
		::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// 解除锁定
		return;									//返回
	}										//判断是否是8-bpp位图,不是则返回*/

	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);			// 找到DIB图象像素起始位置	
	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);					// 获取图象的宽度		
	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);					// 获取图象的高度	
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);                    //获取图像位深
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount);		// 计算图象每行的字节数


	//模板元素数组
	FLOAT operator1;
	FLOAT operator2;
	FLOAT operator3;
	FLOAT operator4;
	FLOAT operator5;
	FLOAT operator6;
	FLOAT operator7;
	FLOAT operator8;
	FLOAT operator9;

	int edge_direction = 0;

	int constant;
	double coefficient;

	//创建对话框
	CDlgFilter dlgPara;
	dlgPara.pDoc = pDoc;
	////给CDlgFilter.cpp传值
	//dlgPara.pDoc = pDoc;
	//dlgPara.lpSrcBitCount = lpSrcBitCount;//////////////////////
	//dlgPara.lpSrcStartBits = lpSrcStartBits;/////////////////
	//dlgPara.lSrcHeight = lSrcHeight;///////////////////////////
	//dlgPara.lSrcWidth = lSrcWidth;///////////////////////////
	//dlgPara.lSrcLineBytes = lSrcLineBytes;///////////////////
	//dlgPara.beginBits = new unsigned char[lSrcHeight * lSrcWidth * sizeof(unsigned char)];
	//memcpy(dlgPara.beginBits, lpSrcStartBits, lSrcHeight * lSrcWidth * sizeof(unsigned char));

	//显示对话框
	if (dlgPara.DoModal() != IDOK)
	{
		//返回
		return;
	}
	if (dlgPara.m_bPreviewed)
	{
		return;
	}
	//获取用户设定
	operator1 = dlgPara.m_operator1;
	operator2 = dlgPara.m_operator2;
	operator3 = dlgPara.m_operator3;
	operator4 = dlgPara.m_operator4;
	operator5 = dlgPara.m_operator5;
	operator6 = dlgPara.m_operator6;
	operator7 = dlgPara.m_operator7;
	operator8 = dlgPara.m_operator8;
	operator9 = dlgPara.m_operator9;

	coefficient = dlgPara.m_coefficient;
	constant = dlgPara.m_constant;

	//模板高度
	int iTempH;
	//模板宽度
	int iTempW;
	//模板中心元素X坐标
	int iTempMX;
	//模板中心元素Y坐标
	int iTempMY;
	//模板元素数组
	FLOAT aValue[9];

	// 设定平移量（3*3）
	iTempH = 3;
	iTempW = 3;
	iTempMX = 1;
	iTempMY = 1;
	//fTempC  = coefficient;//系数  	

	aValue[0] = operator1;
	aValue[1] = operator2;
	aValue[2] = operator3;
	aValue[3] = operator4;
	aValue[4] = operator5;
	aValue[5] = operator6;
	aValue[6] = operator7;
	aValue[7] = operator8;
	aValue[8] = operator9;

	//删除对话框
	delete dlgPara;

	//更改光标形状
	BeginWaitCursor();

	if (Template_Filter1(lpSrcStartBits, lSrcWidth, lSrcHeight,
		iTempH, iTempW, iTempMX, iTempMY, aValue, coefficient, constant))
	{

		// 设置脏标记
		pDoc->SetModifiedFlag(TRUE);

		// 更新视图
		pDoc->UpdateAllViews(NULL);
	}
	else
	{
		// 提示用户
		//MessageBox("分配内存失败！", "系统提示" , MB_ICONINFORMATION | MB_OK);
		AfxMessageBox(L"分配内存失败！系统提示");// 警告
	}

	//解除锁定
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());

	//恢复光标
	EndWaitCursor();
}

int TranslationDIB1(char* lpSrcStartBits, long lSrcWidth, long lSrcHeight, long lXOffset, long lYOffset)
{
	// 创建一个新的图像缓冲区来存储平移后的图像
	char* lpDstBits = new char[lSrcWidth * lSrcHeight];

	if (!lpDstBits)
	{
		return 0; // 内存分配失败
	}

	// 将新图像缓冲区的初始值设为 255（表示白色）
	memset(lpDstBits, 255, lSrcWidth * lSrcHeight);

	for (long y = 0; y < lSrcHeight; ++y)
	{
		for (long x = 0; x < lSrcWidth; ++x)
		{
			// 计算新的坐标
			long newX = x + lXOffset;
			long newY = y - lYOffset;

			// 检查新的坐标是否在图像范围内
			if (newX >= 0 && newX < lSrcWidth && newY >= 0 && newY < lSrcHeight)
			{
				lpDstBits[newY * lSrcWidth + newX] = lpSrcStartBits[y * lSrcWidth + x];
			}
		}
	}

	// 将新图像缓冲区的数据复制回源图像缓冲区
	memcpy(lpSrcStartBits, lpDstBits, lSrcWidth * lSrcHeight);

	// 释放新图像缓冲区
	delete[] lpDstBits;

	return 1; // 平移成功
}



//图像平移
void CMFCTest1View::OnGeomTran()
{
	// TODO: 在此添加命令处理程序代码
	// 获取文档
	CMFCTest1Doc* pDoc = GetDocument();

	// 指向DIB的指针
	LPSTR lpDIB;

	// 指向DIB象素指针
	LPSTR lpDIBBits;

	// 锁定DIB
	lpDIB = (LPSTR)::GlobalLock((HGLOBAL)pDoc->GetHObject());

	// 获取图像的宽度和高度
	long lSrcWidth = pDoc->m_dib.GetWidth(lpDIB);
	long lSrcHeight = pDoc->m_dib.GetHeight(lpDIB);

	// 判断是否是8-bit位图
	if (pDoc->m_dib.GetBitCount(lpDIB) != 8)
	{
		MessageBox(L"目前只支持256色位图的平移！", L"系统提示", MB_ICONINFORMATION | MB_OK);
		::GlobalUnlock((HGLOBAL)pDoc->GetHObject());
		return;
	}

	LONG lXOffset;
	LONG lYOffset;

	// 创建对话框
	DlgGeoTran dlgPara;
	dlgPara.pDoc = pDoc;
	// 初始化变量值
	dlgPara.m_XOffset = 100;
	dlgPara.m_YOffset = 100;

	// 显示对话框，提示用户设定平移量
	if (dlgPara.DoModal() != IDOK)
	{
		// 返回
		::GlobalUnlock((HGLOBAL)pDoc->GetHObject());
		return;
	}
	if (dlgPara.m_bPreviewed)
	{
		return;
	}
	// 获取用户设定的平移量
	lXOffset = dlgPara.m_XOffset;
	lYOffset = dlgPara.m_YOffset;

	// 更改光标形状
	BeginWaitCursor();

	lpDIBBits = pDoc->m_dib.GetBits(lpDIB); // 找到DIB图象像素起始位置

	// 调用TranslationDIB1()函数平移DIB
	if (TranslationDIB1(lpDIBBits, lSrcWidth, lSrcHeight, lXOffset, lYOffset))
	{
		// 设置脏标记
		pDoc->SetModifiedFlag(TRUE);

		// 更新视图
		pDoc->UpdateAllViews(NULL);
	}
	else
	{
		// 提示用户
		MessageBox(L"分配内存失败！", L"系统提示", MB_ICONINFORMATION | MB_OK);
	}

	// 解除锁定
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());

	// 恢复光标
	EndWaitCursor();
}



// 图像旋转
void CMFCTest1View::OnGeomRota()
{
	// 获取文档
	CMFCTest1Doc* pDoc = GetDocument();
	// 指向DIB的指针
	LPSTR lpDIB;
	//锁定DIB
	lpDIB = (LPSTR)::GlobalLock((HGLOBAL)pDoc->GetHObject());
	//判断是否是8-bip位图
	if (pDoc->m_dib.GetBitCount(lpDIB) != 8)
	{
		MessageBox(L"目前只支持256色位图的旋转！", L"系统提示", MB_ICONINFORMATION | MB_OK);
		::GlobalUnlock((HGLOBAL)pDoc->GetHObject());
		return;
	}
	//旋转角度
	int iRotateAngle;	
	//创建对话框
	DlgGeoRota dlgPara;
	dlgPara.pDoc = pDoc;
	//初始化变量值
	dlgPara.m_iRotateAngle = 90;
	//显示对话框，提示用户设定旋转角度
	if (dlgPara.DoModal() != IDOK)
	{
		//返回
		::GlobalUnlock((HGLOBAL)pDoc->GetHObject());
		return;
	}
	//获取用户设置的角度
	iRotateAngle = dlgPara.m_iRotateAngle;
	//删除对话框
	delete dlgPara;

	//创建新DIB
	HDIB hNewDIB = NULL;

	//更改光标形状
	BeginWaitCursor();

	//调用RotateDIB()函数旋转DIB
	hNewDIB = (HDIB)RotateDIB(lpDIB, iRotateAngle);

	//判断是否旋转成功
	if (hNewDIB != NULL)
	{
		// 替换DIB，同时释放旧DIB对象
		pDoc->ReplaceHDIB(hNewDIB);

		// 更新DIB大小和调色板
		pDoc->InitDIBData();

		// 设置脏标记
		pDoc->SetModifiedFlag(TRUE);

		// 重新设置滚动视图大小
		SetScrollSizes(MM_TEXT, pDoc->GetDocSize());

		// 更新视图
		pDoc->UpdateAllViews(NULL);
	}
	else
	{
		//提示用户
		MessageBox(L"分配内存失败！", L"系统提示", MB_ICONINFORMATION | MB_OK);
	}

	//解除锁定
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());

	//恢复光标
	EndWaitCursor();
}


//缩放
HGLOBAL WINAPI ZoomDIB(LPSTR lpDIB, float fXZoomRatio, float fYZoomRatio)
{
	/*************************************************************************
	 * 说明:
	 *   该函数用来缩放DIB图像，返回新生成DIB的句柄。
	 ************************************************************************/
	 // 源图像的宽度和高度
	LONG	lWidth;
	LONG	lHeight;

	// 缩放后图像的宽度和高度
	LONG	lNewWidth;
	LONG	lNewHeight;

	// 缩放后图像的宽度（lNewWidth'，必须是4的倍数）
	LONG	lNewLineBytes;

	// 指向源图像的指针
	LPSTR	lpDIBBits;

	// 指向源象素的指针
	LPSTR	lpSrc;

	// 缩放后新DIB句柄
	HDIB	hDIB;

	// 指向缩放图像对应象素的指针
	LPSTR	lpDst;

	// 指向缩放图像的指针
	LPSTR	lpNewDIB;
	LPSTR	lpNewDIBBits;

	// 指向BITMAPINFO结构的指针（Win3.0）
	LPBITMAPINFOHEADER lpbmi;

	// 指向BITMAPCOREINFO结构的指针
	LPBITMAPCOREHEADER lpbmc;

	// 循环变量（象素在新DIB中的坐标）
	LONG	i;
	LONG	j;

	// 象素在源DIB中的坐标
	LONG	i0;
	LONG	j0;

	// 图像每行的字节数
	LONG lLineBytes;

	// 找到源DIB图像象素起始位置
	lpDIBBits = ::FindDIBBits(lpDIB);

	// 获取图像的宽度
	lWidth = ::DIBWidth(lpDIB);

	// 计算图像每行的字节数
	lLineBytes = WIDTHBYTES(lWidth * 8);

	// 获取图像的高度
	lHeight = ::DIBHeight(lpDIB);

	// 计算缩放后的图像实际宽度
	// 此处直接加0.5是由于强制类型转换时不四舍五入，而是直接截去小数部分
	lNewWidth = (LONG)(::DIBWidth(lpDIB) * fXZoomRatio + 0.5);

	// 计算新图像每行的字节数
	lNewLineBytes = WIDTHBYTES(lNewWidth * 8);

	// 计算缩放后的图像高度
	lNewHeight = (LONG)(lHeight * fYZoomRatio + 0.5);

	// 分配内存，以保存新DIB
	hDIB = (HDIB) ::GlobalAlloc(GHND, lNewLineBytes * lNewHeight + *(LPDWORD)lpDIB + ::PaletteSize(lpDIB));

	// 判断是否内存分配失败
	if (hDIB == NULL)
	{
		// 分配内存失败
		return NULL;
	}

	// 锁定内存
	lpNewDIB = (char*)::GlobalLock((HGLOBAL)hDIB);

	// 复制DIB信息头和调色板
	memcpy(lpNewDIB, lpDIB, *(LPDWORD)lpDIB + ::PaletteSize(lpDIB));

	// 找到新DIB象素起始位置
	lpNewDIBBits = ::FindDIBBits(lpNewDIB);

	// 获取指针
	lpbmi = (LPBITMAPINFOHEADER)lpNewDIB;
	lpbmc = (LPBITMAPCOREHEADER)lpNewDIB;

	// 更新DIB中图像的高度和宽度
	if (IS_WIN30_DIB(lpNewDIB))
	{
		// 对于Windows 3.0 DIB
		lpbmi->biWidth = lNewWidth;
		lpbmi->biHeight = lNewHeight;
	}
	else
	{
		// 对于其它格式的DIB
		lpbmc->bcWidth = (unsigned short)lNewWidth;
		lpbmc->bcHeight = (unsigned short)lNewHeight;
	}

	// 针对图像每行进行操作
	for (i = 0; i < lNewHeight; i++)
	{
		// 针对图像每列进行操作
		for (j = 0; j < lNewWidth; j++)
		{

			// 指向新DIB第i行，第j个象素的指针
			// 注意此处宽度和高度是新DIB的宽度和高度
			lpDst = (char*)lpNewDIBBits + lNewLineBytes * (lNewHeight - 1 - i) + j;

			// 计算该象素在源DIB中的坐标
			i0 = (LONG)(i / fYZoomRatio + 0.5);
			j0 = (LONG)(j / fXZoomRatio + 0.5);

			// 判断是否在源图范围内
			if ((j0 >= 0) && (j0 < lWidth) && (i0 >= 0) && (i0 < lHeight))
			{

				// 指向源DIB第i0行，第j0个象素的指针
				lpSrc = (char*)lpDIBBits + lLineBytes * (lHeight - 1 - i0) + j0;

				// 复制象素
				*lpDst = *lpSrc;
			}
			else
			{
				// 对于源图中没有的象素，直接赋值为255
				*((unsigned char*)lpDst) = 255;
			}

		}

	}

	// 返回
	return hDIB;
}

HGLOBAL __stdcall RotateDIB(LPSTR lpDIB, int iRotateAngle)
{
	// 源图像的宽度和高度
	LONG	lWidth;
	LONG	lHeight;

	// 旋转后图像的宽度和高度
	LONG	lNewWidth;
	LONG	lNewHeight;

	// 图像每行的字节数
	LONG	lLineBytes;

	// 旋转后图像的宽度（lNewWidth'，必须是4的倍数）
	LONG	lNewLineBytes;

	// 指向源图像的指针
	LPSTR	lpDIBBits;

	// 指向源象素的指针
	LPSTR	lpSrc;

	// 旋转后新DIB句柄
	HDIB	hDIB;

	// 指向旋转图像对应象素的指针
	LPSTR	lpDst;

	// 指向旋转图像的指针
	LPSTR	lpNewDIB;
	LPSTR	lpNewDIBBits;

	// 指向BITMAPINFO结构的指针（Win3.0）
	LPBITMAPINFOHEADER lpbmi;

	// 指向BITMAPCOREINFO结构的指针
	LPBITMAPCOREHEADER lpbmc;

	// 循环变量（象素在新DIB中的坐标）
	LONG	i;
	LONG	j;

	// 象素在源DIB中的坐标
	LONG	i0;
	LONG	j0;

	// 旋转角度（弧度）
	float	fRotateAngle;

	// 旋转角度的正弦和余弦
	float	fSina, fCosa;

	// 源图四个角的坐标（以图像中心为坐标系原点）
	float	fSrcX1, fSrcY1, fSrcX2, fSrcY2, fSrcX3, fSrcY3, fSrcX4, fSrcY4;

	// 旋转后四个角的坐标（以图像中心为坐标系原点）
	float	fDstX1, fDstY1, fDstX2, fDstY2, fDstX3, fDstY3, fDstX4, fDstY4;

	// 两个中间常量
	float	f1, f2;

	// 找到源DIB图像象素起始位置
	lpDIBBits = ::FindDIBBits(lpDIB);

	// 获取图像的"宽度"（4的倍数）
	lWidth = ::DIBWidth(lpDIB);

	// 计算图像每行的字节数
	lLineBytes = WIDTHBYTES(lWidth * 8);

	// 获取图像的高度
	lHeight = ::DIBHeight(lpDIB);

	// 将旋转角度从度转换到弧度
	fRotateAngle = (float)RADIAN(iRotateAngle);

	// 计算旋转角度的正弦
	fSina = (float)sin((double)fRotateAngle);

	// 计算旋转角度的余弦
	fCosa = (float)cos((double)fRotateAngle);

	// 计算原图的四个角的坐标（以图像中心为坐标系原点）
	fSrcX1 = (float)(-(lWidth - 1) / 2);
	fSrcY1 = (float)((lHeight - 1) / 2);
	fSrcX2 = (float)((lWidth - 1) / 2);
	fSrcY2 = (float)((lHeight - 1) / 2);
	fSrcX3 = (float)(-(lWidth - 1) / 2);
	fSrcY3 = (float)(-(lHeight - 1) / 2);
	fSrcX4 = (float)((lWidth - 1) / 2);
	fSrcY4 = (float)(-(lHeight - 1) / 2);

	// 计算新图四个角的坐标（以图像中心为坐标系原点）
	fDstX1 = fCosa * fSrcX1 + fSina * fSrcY1;
	fDstY1 = -fSina * fSrcX1 + fCosa * fSrcY1;
	fDstX2 = fCosa * fSrcX2 + fSina * fSrcY2;
	fDstY2 = -fSina * fSrcX2 + fCosa * fSrcY2;
	fDstX3 = fCosa * fSrcX3 + fSina * fSrcY3;
	fDstY3 = -fSina * fSrcX3 + fCosa * fSrcY3;
	fDstX4 = fCosa * fSrcX4 + fSina * fSrcY4;
	fDstY4 = -fSina * fSrcX4 + fCosa * fSrcY4;

	// 计算旋转后的图像实际宽度
	lNewWidth = (LONG)(max(fabs(fDstX4 - fDstX1), fabs(fDstX3 - fDstX2)) + 0.5);

	// 计算新图像每行的字节数
	lNewLineBytes = WIDTHBYTES(lNewWidth * 8);

	// 计算旋转后的图像高度
	lNewHeight = (LONG)(max(fabs(fDstY4 - fDstY1), fabs(fDstY3 - fDstY2)) + 0.5);

	// 两个常数，这样不用以后每次都计算了
	f1 = (float)(-0.5 * (lNewWidth - 1) * fCosa - 0.5 * (lNewHeight - 1) * fSina
		+ 0.5 * (lWidth - 1));
	f2 = (float)(0.5 * (lNewWidth - 1) * fSina - 0.5 * (lNewHeight - 1) * fCosa
		+ 0.5 * (lHeight - 1));

	// 分配内存，以保存新DIB
	hDIB = (HDIB) ::GlobalAlloc(GHND, lNewLineBytes * lNewHeight + *(LPDWORD)lpDIB + ::PaletteSize(lpDIB));

	// 判断是否内存分配失败
	if (hDIB == NULL)
	{
		// 分配内存失败
		return NULL;
	}

	// 锁定内存
	lpNewDIB = (char*)::GlobalLock((HGLOBAL)hDIB);

	// 复制DIB信息头和调色板
	memcpy(lpNewDIB, lpDIB, *(LPDWORD)lpDIB + ::PaletteSize(lpDIB));

	// 找到新DIB象素起始位置
	lpNewDIBBits = ::FindDIBBits(lpNewDIB);

	// 获取指针
	lpbmi = (LPBITMAPINFOHEADER)lpNewDIB;
	lpbmc = (LPBITMAPCOREHEADER)lpNewDIB;

	// 更新DIB中图像的高度和宽度
	if (IS_WIN30_DIB(lpNewDIB))
	{
		// 对于Windows 3.0 DIB
		lpbmi->biWidth = lNewWidth;
		lpbmi->biHeight = lNewHeight;
	}
	else
	{
		// 对于其它格式的DIB
		lpbmc->bcWidth = (unsigned short)lNewWidth;
		lpbmc->bcHeight = (unsigned short)lNewHeight;
	}

	// 针对图像每行进行操作
	for (i = 0; i < lNewHeight; i++)
	{
		// 针对图像每列进行操作
		for (j = 0; j < lNewWidth; j++)
		{
			// 指向新DIB第i行，第j个象素的指针
			// 注意此处宽度和高度是新DIB的宽度和高度
			lpDst = (char*)lpNewDIBBits + lNewLineBytes * (lNewHeight - 1 - i) + j;

			// 计算该象素在源DIB中的坐标
			i0 = (LONG)(-((float)j) * fSina + ((float)i) * fCosa + f2 + 0.5);
			j0 = (LONG)(((float)j) * fCosa + ((float)i) * fSina + f1 + 0.5);

			// 判断是否在源图范围内
			if ((j0 >= 0) && (j0 < lWidth) && (i0 >= 0) && (i0 < lHeight))
			{
				// 指向源DIB第i0行，第j0个象素的指针
				lpSrc = (char*)lpDIBBits + lLineBytes * (lHeight - 1 - i0) + j0;

				// 复制象素
				*lpDst = *lpSrc;
			}
			else
			{
				// 对于源图中没有的象素，直接赋值为255
				*((unsigned char*)lpDst) = 255;
			}

		}

	}

	// 返回
	return hDIB;
	
	
	return HGLOBAL();
}

// 图像缩放
void CMFCTest1View::OnGeomZoom()
{
	// TODO: 在此添加命令处理程序代码
	// 获取文档
	CMFCTest1Doc* pDoc = GetDocument();

	// 指向DIB的指针
	LPSTR lpDIB;

	// 锁定DIB
	lpDIB = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());

	// 判断是否是8-bpp位图（这里为了方便，只处理8-bpp位图的缩放，其它的可以类推）
	if (::DIBNumColors(lpDIB) != 256)
	{
		// 提示用户
		MessageBox(L"目前只支持256色位图的缩放！", L"系统提示", MB_ICONINFORMATION | MB_OK);

		// 解除锁定
		::GlobalUnlock((HGLOBAL)pDoc->GetHObject());

		// 返回
		return;
	}

	// 缩放比率
	float fXZoomRatio;
	float fYZoomRatio;

	// 创建对话框
	CDlgGeoZoom dlgPara;
	dlgPara.pDoc = pDoc;
	// 初始化变量值
	dlgPara.m_XZoom = 0.5;
	dlgPara.m_YZoom = 0.5;

	// 显示对话框，提示用户设定平移量
	if (dlgPara.DoModal() != IDOK)
	{
		// 返回
		return;
	}
	if (dlgPara.m_bPreviewed)
	{
		return;
	}
	// 获取用户设定的平移量
	fXZoomRatio = dlgPara.m_XZoom;
	fYZoomRatio = dlgPara.m_YZoom;

	// 删除对话框
	delete dlgPara;

	// 创建新DIB
	HDIB hNewDIB = NULL;

	// 更改光标形状
	BeginWaitCursor();

	// 调用ZoomDIB()函数转置DIB
	hNewDIB = (HDIB)ZoomDIB(lpDIB, fXZoomRatio, fYZoomRatio);

	// 判断缩放是否成功
	if (hNewDIB != NULL)
	{

		// 替换DIB，同时释放旧DIB对象
		pDoc->ReplaceHDIB(hNewDIB);

		// 更新DIB大小和调色板
		pDoc->InitDIBData();

		// 设置脏标记
		pDoc->SetModifiedFlag(TRUE);

		// 更新视图
		pDoc->UpdateAllViews(NULL);
	}
	else
	{
		// 提示用户
		MessageBox(L"分配内存失败！", L"系统提示", MB_ICONINFORMATION | MB_OK);
	}

	// 解除锁定
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());

	// 恢复光标
	EndWaitCursor();
}

//镜像
BOOL WINAPI MirrorDIB(LPSTR lpDIBBits, LONG lWidth, LONG lHeight, BOOL bDirection)
{
	/*************************************************************************
	 * 说明:
	 *   该函数用来镜像DIB图像。可以指定镜像的方式是水平还是垂直。
	 ************************************************************************/
	 // 指向源图像的指针
	LPSTR	lpSrc;

	// 指向要复制区域的指针
	LPSTR	lpDst;

	// 指向复制图像的指针
	LPSTR	lpBits;
	HLOCAL	hBits;

	// 循环变量
	LONG	i;
	LONG	j;

	// 图像每行的字节数
	LONG lLineBytes;

	// 计算图像每行的字节数
	lLineBytes = WIDTHBYTES(lWidth * 8);

	// 暂时分配内存，以保存一行图像
	hBits = LocalAlloc(LHND, lLineBytes);
	if (hBits == NULL)
	{
		// 分配内存失败
		return FALSE;
	}

	// 锁定内存
	lpBits = (char*)LocalLock(hBits);

	// 判断镜像方式
	if (bDirection)
	{
		// 水平镜像

		// 针对图像每行进行操作
		for (i = 0; i < lHeight; i++)
		{
			// 针对每行图像左半部分进行操作
			for (j = 0; j < lWidth / 2; j++)
			{

				// 指向倒数第i行，第j个象素的指针
				lpSrc = (char*)lpDIBBits + lLineBytes * i + j;

				// 指向倒数第i行，倒数第j个象素的指针
				lpDst = (char*)lpDIBBits + lLineBytes * (i + 1) - j;

				// 备份一个象素
				*lpBits = *lpDst;

				// 将倒数第i行，第j个象素复制到倒数第i行，倒数第j个象素
				*lpDst = *lpSrc;

				// 将倒数第i行，倒数第j个象素复制到倒数第i行，第j个象素
				*lpSrc = *lpBits;
			}

		}
	}
	else
	{
		// 垂直镜像

		// 针对上半图像进行操作
		for (i = 0; i < lHeight / 2; i++)
		{

			// 指向倒数第i行象素起点的指针
			lpSrc = (char*)lpDIBBits + lLineBytes * i;

			// 指向第i行象素起点的指针
			lpDst = (char*)lpDIBBits + lLineBytes * (lHeight - i - 1);

			// 备份一行，宽度为lWidth
			memcpy(lpBits, lpDst, lLineBytes);

			// 将倒数第i行象素复制到第i行
			memcpy(lpDst, lpSrc, lLineBytes);

			// 将第i行象素复制到倒数第i行
			memcpy(lpSrc, lpBits, lLineBytes);

		}
	}

	// 释放内存
	LocalUnlock(hBits);
	LocalFree(hBits);

	// 返回
	return TRUE;
}


//水平镜像
void CMFCTest1View::OnGeomMirh()
{
	// TODO: 在此添加命令处理程序代码
	// 获取文档
	CMFCTest1Doc* pDoc = GetDocument();

	// 指向DIB的指针
	LPSTR lpDIB;

	// 指向DIB象素指针
	LPSTR    lpDIBBits;

	// 锁定DIB
	lpDIB = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());

	// 判断是否是8-bpp位图（这里为了方便，只处理8-bpp位图的垂直镜像，其它的可以类推）
	if (::DIBNumColors(lpDIB) != 256)
	{
		// 提示用户
		MessageBox(L"目前只支持256色位图的垂直镜像！", L"系统提示", MB_ICONINFORMATION | MB_OK);

		// 解除锁定
		::GlobalUnlock((HGLOBAL)pDoc->GetHObject());

		// 返回
		return;
	}


	// 更改光标形状
	BeginWaitCursor();

	// 找到DIB图像象素起始位置
	lpDIBBits = ::FindDIBBits(lpDIB);

	// 调用MirrorDIB()函数垂直镜像DIB
	if (MirrorDIB(lpDIBBits, ::DIBWidth(lpDIB), ::DIBHeight(lpDIB), TRUE))
	{

		// 设置脏标记
		pDoc->SetModifiedFlag(TRUE);

		// 更新视图
		pDoc->UpdateAllViews(NULL);
	}
	else
	{
		// 提示用户
		MessageBox(L"分配内存失败！", L"系统提示", MB_ICONINFORMATION | MB_OK);
	}

	// 解除锁定
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());

	// 恢复光标
	EndWaitCursor();
}



// 垂直镜像
void CMFCTest1View::OnGeomMirv()
{
	// TODO: 在此添加命令处理程序代码
	// 获取文档
	CMFCTest1Doc* pDoc = GetDocument();

	// 指向DIB的指针
	LPSTR lpDIB;

	// 指向DIB象素指针
	LPSTR    lpDIBBits;

	// 锁定DIB
	lpDIB = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());

	// 判断是否是8-bpp位图（这里为了方便，只处理8-bpp位图的垂直镜像，其它的可以类推）
	if (::DIBNumColors(lpDIB) != 256)
	{
		// 提示用户
		MessageBox(L"目前只支持256色位图的垂直镜像！", L"系统提示", MB_ICONINFORMATION | MB_OK);

		// 解除锁定
		::GlobalUnlock((HGLOBAL)pDoc->GetHObject());

		// 返回
		return;
	}


	// 更改光标形状
	BeginWaitCursor();

	// 找到DIB图像象素起始位置
	lpDIBBits = ::FindDIBBits(lpDIB);

	// 调用MirrorDIB()函数垂直镜像DIB
	if (MirrorDIB(lpDIBBits, ::DIBWidth(lpDIB), ::DIBHeight(lpDIB), FALSE))
	{

		// 设置脏标记
		pDoc->SetModifiedFlag(TRUE);

		// 更新视图
		pDoc->UpdateAllViews(NULL);
	}
	else
	{
		// 提示用户
		MessageBox(L"分配内存失败！", L"系统提示", MB_ICONINFORMATION | MB_OK);
	}

	// 解除锁定
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());

	// 恢复光标
	EndWaitCursor();
}

/*************************************************************************
 *
 * 函数名称：
 *   TransposeDIB()
 *
 * 参数:
 *   LPSTR lpDIB        - 指向源DIB的指针
 *
 * 返回值:
 *   BOOL               - 转置成功返回TRUE，否则返回FALSE。
 *
 * 说明:
 *   该函数用来转置DIB图像，即图像x、y坐标互换。函数将不会改变图像的大小，
 * 但是图像的高宽将互换。
 *
 ************************************************************************/

BOOL WINAPI TransposeDIB(LPSTR lpDIB)
{
	// 图像的宽度和高度
	LONG lWidth;
	LONG lHeight;

	// 指向源图像的指针
	LPSTR lpDIBBits;

	// 指向源象素的指针
	LPSTR lpSrc;

	// 指向转置图像对应象素的指针
	LPSTR lpDst;

	// 指向转置图像的指针
	LPSTR lpNewDIBBits;
	HLOCAL hNewDIBBits;

	// 指向BITMAPINFO结构的指针（Win3.0）
	LPBITMAPINFOHEADER lpbmi;

	// 指向BITMAPCOREINFO结构的指针
	LPBITMAPCOREHEADER lpbmc;

	// 循环变量
	LONG i;
	LONG j;

	// 图像每行的字节数
	LONG lLineBytes;

	// 新图像每行的字节数
	LONG lNewLineBytes;

	// 获取指针
	lpbmi = (LPBITMAPINFOHEADER)lpDIB;
	lpbmc = (LPBITMAPCOREHEADER)lpDIB;

	// 找到源DIB图像象素起始位置
	lpDIBBits = ::FindDIBBits(lpDIB);

	// 获取图像的宽度（4的倍数）
	lWidth = ::DIBWidth(lpDIB);

	// 获取图像的高度
	lHeight = ::DIBHeight(lpDIB);

	// 计算图像每行的字节数
	lLineBytes = WIDTHBYTES(lWidth * 8);

	// 计算新图像每行的字节数
	lNewLineBytes = WIDTHBYTES(lHeight * 8);

	// 暂时分配内存，以保存新图像
	hNewDIBBits = LocalAlloc(LHND, lWidth * lNewLineBytes);

	// 判断是否内存分配失败
	if (hNewDIBBits == NULL)
	{
		// 分配内存失败
		return FALSE;
	}

	// 锁定内存
	lpNewDIBBits = (char*)LocalLock(hNewDIBBits);

	// 针对图像每行进行操作
	for (i = 0; i < lHeight; i++)
	{
		// 针对每行图像每列进行操作
		for (j = 0; j < lWidth; j++)
		{
			// 指向源DIB第i行，第j个象素的指针
			lpSrc = (char*)lpDIBBits + lLineBytes * (lHeight - 1 - i) + j;

			// 指向转置DIB第j行，第i个象素的指针
			// 注意此处lWidth和lHeight是源DIB的宽度和高度，应该互换
			lpDst = (char*)lpNewDIBBits + lNewLineBytes * (lWidth - 1 - j) + i;

			// 复制象素
			*lpDst = *lpSrc;
		}
	}

	// 复制转置后的图像
	memcpy(lpDIBBits, lpNewDIBBits, lWidth * lNewLineBytes);

	// 互换DIB中图像的高宽
	if (IS_WIN30_DIB(lpDIB))
	{
		// 对于Windows 3.0 DIB
		lpbmi->biWidth = lHeight;
		lpbmi->biHeight = lWidth;
	}
	else
	{
		// 对于其它格式的DIB
		lpbmc->bcWidth = (unsigned short)lHeight;
		lpbmc->bcHeight = (unsigned short)lWidth;
	}

	// 释放内存
	LocalUnlock(hNewDIBBits);
	LocalFree(hNewDIBBits);

	// 返回
	return TRUE;
}



//图像转置
void CMFCTest1View::OnGeomTrpos()
{
	// 获取文档
	CMFCTest1Doc* pDoc = GetDocument();

	// 指向DIB的指针
	LPSTR lpDIB;

	// 锁定DIB
	lpDIB = (LPSTR)::GlobalLock((HGLOBAL)pDoc->GetHObject());

	// 判断是否是8-bpp位图（这里只处理8-bpp位图的转置，其它的可以类推）
	if (::DIBNumColors(lpDIB) != 256)
	{
		// 提示用户
		MessageBox(L"目前只支持256色位图的转置！", L"系统提示", MB_ICONINFORMATION | MB_OK);

		// 解除锁定
		::GlobalUnlock((HGLOBAL)pDoc->GetHObject());

		// 返回
		return;
	}

	// 更改光标形状
	BeginWaitCursor();

	// 调用TransposeDIB()函数转置DIB
	if (TransposeDIB(lpDIB))
	{
		// 设置脏标记
		pDoc->SetModifiedFlag(TRUE);

		// 更新DIB大小和调色板
		pDoc->InitDIBData();

		// 重新设置滚动视图大小
		SetScrollSizes(MM_TEXT, pDoc->GetDocSize());

		// 更新视图
		pDoc->UpdateAllViews(NULL);
	}
	else
	{
		// 提示用户
		MessageBox(L"分配内存失败！", L"系统提示", MB_ICONINFORMATION | MB_OK);
	}

	// 解除锁定
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());

	// 恢复光标
	EndWaitCursor();
}


void ApplyMosaic(LPSTR lpSrcStartBits, int lSrcWidth, int lSrcHeight, int mosaicSize)
{
	// 遍历图像的每个马赛克单元
	for (int y = 0; y < lSrcHeight; y += mosaicSize)
	{
		for (int x = 0; x < lSrcWidth; x += mosaicSize)
		{
			int sum = 0;
			int count = 0;

			// 计算当前马赛克单元的灰度平均值
			for (int i = 0; i < mosaicSize; i++)
			{
				for (int j = 0; j < mosaicSize; j++)
				{
					int nx = x + j;
					int ny = y + i;

					// 确保像素坐标在图像范围内
					if (nx < lSrcWidth && ny < lSrcHeight)
					{
						sum += (unsigned char)lpSrcStartBits[ny * lSrcWidth + nx];
						count++;
					}
				}
			}

			int avgPixel = sum / count;

			// 混合当前马赛克单元的所有像素值与原始值
			for (int i = 0; i < mosaicSize; i++)
			{
				for (int j = 0; j < mosaicSize; j++)
				{
					int nx = x + j;
					int ny = y + i;

					if (nx < lSrcWidth && ny < lSrcHeight)
					{
						unsigned char originalPixel = (unsigned char)lpSrcStartBits[ny * lSrcWidth + nx];
						unsigned char newPixel = (unsigned char)(0.3 * originalPixel + 0.7 * avgPixel);
						lpSrcStartBits[ny * lSrcWidth + nx] = (CHAR)newPixel;
					}
				}
			}
		}
	}
}

//马赛克
void CMFCTest1View::OnMosaic()
{
	// TODO: 在此添加命令处理程序代码
	CMFCTest1Doc* pDoc = GetDocument();

	LPSTR lpSrcDib;         // 指向源图象的指针    
	LPSTR lpSrcStartBits;   // 指向源像素的指针

	long lSrcLineBytes;     // 图象每行的字节数
	long lSrcWidth;         // 图象的宽度和高度
	long lSrcHeight;
	int lpSrcBitCount;      // 图像的位深

	// 锁定DIB
	lpSrcDib = (LPSTR)::GlobalLock((HGLOBAL)pDoc->GetHObject());

	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);   // 找到DIB图象像素起始位置    

	if (pDoc->m_dib.GetColorNum(lpSrcDib) != 256) // 判断是否是8-bpp位图
	{
		MessageBox(L"对不起，不是256色位图！");  // 警告
		::GlobalUnlock((HGLOBAL)pDoc->GetHObject()); // 解除锁定
		return; // 返回
	} // 判断是否是8-bpp位图, 不是则返回

	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);      // 获取图象的宽度        
	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);    // 获取图象的高度    
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib); // 获取图像位深
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount); // 计算图象每行的字节数

	int mosaicSize = 10; // 设置马赛克单元的大小
	ApplyMosaic(lpSrcStartBits, lSrcWidth, lSrcHeight, mosaicSize);

	MessageBox(L"原图像已改变！");

	pDoc->SetModifiedFlag(true);
	pDoc->UpdateAllViews(NULL); // 是否保存更改后的图像
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject()); // 解除锁定

}
BOOL Oilpaint(LPSTR lpSrcStartBits, int lSrcWidth, int lSrcHeight, int brushSize, float transparency)
{
    // 创建目标图像数据缓冲区
    LPSTR lpDstBits = new CHAR[lSrcWidth * lSrcHeight];
    memset(lpDstBits, 0, lSrcWidth * lSrcHeight);

    // 遍历源图像的每个像素
    for (int y = 0; y < lSrcHeight; y++)
    {
        for (int x = 0; x < lSrcWidth; x++)
        {
            // 统计周围像素的灰度值
            int hist[256] = { 0 };
            for (int i = -brushSize; i <= brushSize; i++)
            {
                for (int j = -brushSize; j <= brushSize; j++)
                {
                    int nx = x + i;
                    int ny = y + j;
                    
                    // 处理边界条件
                    if (nx < 0) nx = 0;
                    if (nx >= lSrcWidth) nx = lSrcWidth - 1;
                    if (ny < 0) ny = 0;
                    if (ny >= lSrcHeight) ny = lSrcHeight - 1;

                    int pixelValue = (unsigned char)lpSrcStartBits[ny * lSrcWidth + nx];
                    hist[pixelValue]++;
                }
            }

            // 找到最常出现的像素值
            int maxFreq = 0;
            int maxPixel = 0;
            for (int k = 0; k < 256; k++)
            {
                if (hist[k] > maxFreq)
                {
                    maxFreq = hist[k];
                    maxPixel = k;
                }
            }

            // 判断像素灰度值是否为0，如果是，则将其替换为180
            if (maxPixel == 0)
            {
                maxPixel = 180;
            }

            // 在目标图像中设置像素值
            float srcPixelValue = (unsigned char)lpSrcStartBits[y * lSrcWidth + x];
            float newValue = transparency * maxPixel + (1 - transparency) * srcPixelValue;
            
            // 确保newValue在0到255之间
            if (newValue < 0) newValue = 0;
            if (newValue > 255) newValue = 255;

            lpDstBits[y * lSrcWidth + x] = (CHAR)newValue;
        }
    }

    // 将结果复制回源图像缓冲区
    memcpy(lpSrcStartBits, lpDstBits, lSrcWidth * lSrcHeight);

    // 释放内存
    delete[] lpDstBits;

    return TRUE;
}

void CMFCTest1View::OnOilpaint()
{
    CMFCTest1Doc* pDoc = GetDocument();

    LPSTR lpSrcDib;         // 指向源图象的指针    
    LPSTR lpSrcStartBits;   // 指向源像素的指针

    long lSrcLineBytes;     // 图象每行的字节数
    long lSrcWidth;         // 图象的宽度和高度
    long lSrcHeight;
    int lpSrcBitCount;      // 图像的位深

    // 锁定DIB
    lpSrcDib = (LPSTR)::GlobalLock((HGLOBAL)pDoc->GetHObject());

    lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);   // 找到DIB图象像素起始位置    

    if (pDoc->m_dib.GetColorNum(lpSrcDib) != 256) // 判断是否是8-bpp位图
    {
        MessageBox(L"对不起，不是256色位图！");  // 警告
        ::GlobalUnlock((HGLOBAL)pDoc->GetHObject()); // 解除锁定
        return; // 返回
    } // 判断是否是8-bpp位图, 不是则返回

    lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);      // 获取图象的宽度        
    lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);    // 获取图象的高度    
    lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib); // 获取图像位深
    lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount); // 计算图象每行的字节数

    int brushSize = 2;
    int transparency = 1;
    Oilpaint(lpSrcStartBits, lSrcWidth, lSrcHeight, brushSize, transparency);

    MessageBox(L"原图像已改变！");

    pDoc->SetModifiedFlag(true);
    pDoc->UpdateAllViews(NULL); // 是否保存更改后的图像
    ::GlobalUnlock((HGLOBAL)pDoc->GetHObject()); // 解除锁定
}



void ApplyRetroStyle(LPSTR lpSrcStartBits, int lSrcWidth, int lSrcHeight)
{
	// 增加对比度和亮度
	float contrast = 2.0f; // 更强的对比度因子
	int brightness = 30;   // 增加亮度偏移

	// 添加噪声
	float noiseAmount = 0.1f; // 增加噪声量
	srand((unsigned int)time(0)); // 随机数种子

	// 添加仿旧纸张纹理
	float textureAmount = 0.1f; // 纹理影响量
	for (int y = 0; y < lSrcHeight; y++)
	{
		for (int x = 0; x < lSrcWidth; x++)
		{
			int pixelValue = (unsigned char)lpSrcStartBits[y * lSrcWidth + x];

			// 增加对比度和亮度
			float newValue = pixelValue / 255.0f;
			newValue = (newValue - 0.5f) * contrast + 0.5f + brightness / 255.0f;
			newValue = newValue * 255.0f;

			// 添加噪声
			newValue += noiseAmount * 255.0f * ((rand() % 100 / 100.0f) - 0.5f);

			// 添加仿旧纸张纹理
			float texture = (sin(x / 5.0f) + cos(y / 5.0f)) * textureAmount * 255.0f;
			newValue += texture;

			// 确保值在0到255之间
			if (newValue < 0)
				newValue = 0;
			else if (newValue > 255)
				newValue = 255;

			// 应用新像素值
			lpSrcStartBits[y * lSrcWidth + x] = (CHAR)newValue;
		}
	}
}

void CMFCTest1View::OnRetrostyle()
{
	CMFCTest1Doc* pDoc = GetDocument();

	LPSTR lpSrcDib;         // 指向源图象的指针    
	LPSTR lpSrcStartBits;   // 指向源像素的指针

	long lSrcLineBytes;     // 图象每行的字节数
	long lSrcWidth;         // 图象的宽度和高度
	long lSrcHeight;
	int lpSrcBitCount;      // 图像的位深

	// 锁定DIB
	lpSrcDib = (LPSTR)::GlobalLock((HGLOBAL)pDoc->GetHObject());

	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);   // 找到DIB图象像素起始位置    

	if (pDoc->m_dib.GetColorNum(lpSrcDib) != 256) // 判断是否是8-bpp位图
	{
		MessageBox(L"对不起，不是256色位图！");  // 警告
		::GlobalUnlock((HGLOBAL)pDoc->GetHObject()); // 解除锁定
		return; // 返回
	} // 判断是否是8-bpp位图, 不是则返回

	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);      // 获取图象的宽度        
	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);    // 获取图象的高度    
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib); // 获取图像位深
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount); // 计算图象每行的字节数

	ApplyRetroStyle(lpSrcStartBits, lSrcWidth, lSrcHeight);

	MessageBox(L"原图像已改变！");

	pDoc->SetModifiedFlag(true);
	pDoc->UpdateAllViews(NULL); // 是否保存更改后的图像
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject()); // 解除锁定
}



// 使用Sobel算子进行边缘检测
void SobelEdgeDetection(LPSTR lpSrcStartBits, int lSrcWidth, int lSrcHeight, LPSTR lpDstBits)
{
	int Gx[3][3] = {
		{ -1, 0, 1 },
		{ -2, 0, 2 },
		{ -1, 0, 1 }
	};

	int Gy[3][3] = {
		{  1,  2,  1 },
		{  0,  0,  0 },
		{ -1, -2, -1 }
	};

	for (int y = 1; y < lSrcHeight - 1; y++)
	{
		for (int x = 1; x < lSrcWidth - 1; x++)
		{
			int sumX = 0;
			int sumY = 0;

			for (int i = -1; i <= 1; i++)
			{
				for (int j = -1; j <= 1; j++)
				{
					int pixelValue = (unsigned char)lpSrcStartBits[(y + i) * lSrcWidth + (x + j)];
					sumX += pixelValue * Gx[i + 1][j + 1];
					sumY += pixelValue * Gy[i + 1][j + 1];
				}
			}

			int edgeValue = std::sqrt((sumX * sumX) + (sumY * sumY));

			// 确保值在0到255之间
			if (edgeValue < 0)
				edgeValue = 0;
			else if (edgeValue > 255)
				edgeValue = 255;

			lpDstBits[y * lSrcWidth + x] = (CHAR)edgeValue;
		}
	}
}

void ApplyPencilDrawEffect(LPSTR lpSrcStartBits, int lSrcWidth, int lSrcHeight)
{
	LPSTR lpEdgeBits = new CHAR[lSrcWidth * lSrcHeight];
	memset(lpEdgeBits, 0, lSrcWidth * lSrcHeight);

	// 进行边缘检测
	SobelEdgeDetection(lpSrcStartBits, lSrcWidth, lSrcHeight, lpEdgeBits);

	// 反色处理
	for (int y = 0; y < lSrcHeight; y++)
	{
		for (int x = 0; x < lSrcWidth; x++)
		{
			int pixelValue = (unsigned char)lpEdgeBits[y * lSrcWidth + x];
			lpSrcStartBits[y * lSrcWidth + x] = 255 - pixelValue;
		}
	}

	delete[] lpEdgeBits;
}

void CMFCTest1View::OnPencildraw()
{
	CMFCTest1Doc* pDoc = GetDocument();

	LPSTR lpSrcDib;         // 指向源图象的指针    
	LPSTR lpSrcStartBits;   // 指向源像素的指针

	long lSrcLineBytes;     // 图象每行的字节数
	long lSrcWidth;         // 图象的宽度和高度
	long lSrcHeight;
	int lpSrcBitCount;      // 图像的位深

	// 锁定DIB
	lpSrcDib = (LPSTR)::GlobalLock((HGLOBAL)pDoc->GetHObject());

	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);   // 找到DIB图象像素起始位置    

	if (pDoc->m_dib.GetColorNum(lpSrcDib) != 256) // 判断是否是8-bpp位图
	{
		MessageBox(L"对不起，不是256色位图！");  // 警告
		::GlobalUnlock((HGLOBAL)pDoc->GetHObject()); // 解除锁定
		return; // 返回
	} // 判断是否是8-bpp位图, 不是则返回

	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);      // 获取图象的宽度        
	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);    // 获取图象的高度    
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib); // 获取图像位深
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount); // 计算图象每行的字节数

	ApplyPencilDrawEffect(lpSrcStartBits, lSrcWidth, lSrcHeight);

	MessageBox(L"原图像已改变！");

	pDoc->SetModifiedFlag(true);
	pDoc->UpdateAllViews(NULL); // 是否保存更改后的图像
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject()); // 解除锁定
}



#include <queue>
#include <vector>
#include <cstring>
#include <cmath>

#define MAX 10000

typedef struct point {
	int i;
	int j;
} point;

typedef struct Xiangsu {
	int xiangsu;
	int value;
} Xiangsu;

int dealer_four(LPSTR image, int width, int height, int Bg, int* labels)
{
	int** flag_max;
	flag_max = new int* [height];
	for (int i = 0; i < height; i++) {
		flag_max[i] = new int[width];
	}
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			flag_max[i][j] = 0;
		}
	}

	int count = 1; // 区域标记
	unsigned char* ptemp = (unsigned char*)image;

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if ((*(ptemp + i * width + j) == Bg) && (flag_max[i][j] == 0))
			{
				point temp;
				temp.i = i;
				temp.j = j;
				std::queue<point> buffer;
				buffer.push(temp);
				while (!buffer.empty())
				{
					temp = buffer.front();
					buffer.pop();
					if (temp.i >= 0 && temp.i < height && temp.j >= 0 && temp.j < width && *(ptemp + temp.i * width + temp.j) == Bg && flag_max[temp.i][temp.j] == 0)
					{
						flag_max[temp.i][temp.j] = count;
						labels[temp.i * width + temp.j] = count;
						if (temp.i - 1 >= 0 && *(ptemp + (temp.i - 1) * width + temp.j) == Bg && flag_max[temp.i - 1][temp.j] == 0) {
							buffer.push({ temp.i - 1, temp.j });
						}
						if (temp.j - 1 >= 0 && *(ptemp + temp.i * width + temp.j - 1) == Bg && flag_max[temp.i][temp.j - 1] == 0) {
							buffer.push({ temp.i, temp.j - 1 });
						}
						if (temp.j + 1 < width && *(ptemp + temp.i * width + temp.j + 1) == Bg && flag_max[temp.i][temp.j + 1] == 0) {
							buffer.push({ temp.i, temp.j + 1 });
						}
						if (temp.i + 1 < height && *(ptemp + (temp.i + 1) * width + temp.j) == Bg && flag_max[temp.i + 1][temp.j] == 0) {
							buffer.push({ temp.i + 1, temp.j });
						}
					}
				}
				count++;
			}
		}
	}

	for (int i = 0; i < height; i++) {
		delete[] flag_max[i];
	}
	delete[] flag_max;

	return count - 1;
}

int dealer_eight(LPSTR image, int width, int height, int Bg, int* labels)
{
	int** flag_max;
	flag_max = new int* [height];
	for (int i = 0; i < height; i++) {
		flag_max[i] = new int[width];
	}
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			flag_max[i][j] = 0;
		}
	}

	int count = 1; // 区域标记
	unsigned char* ptemp = (unsigned char*)image;

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if ((*(ptemp + i * width + j) == Bg) && (flag_max[i][j] == 0))
			{
				point temp;
				temp.i = i;
				temp.j = j;
				std::queue<point> buffer;
				buffer.push(temp);
				while (!buffer.empty())
				{
					temp = buffer.front();
					buffer.pop();
					if (temp.i >= 0 && temp.i < height && temp.j >= 0 && temp.j < width && *(ptemp + temp.i * width + temp.j) == Bg && flag_max[temp.i][temp.j] == 0)
					{
						flag_max[temp.i][temp.j] = count;
						labels[temp.i * width + temp.j] = count;
						if (temp.i - 1 >= 0 && temp.j - 1 >= 0 && *(ptemp + (temp.i - 1) * width + temp.j - 1) == Bg && flag_max[temp.i - 1][temp.j - 1] == 0) {
							buffer.push({ temp.i - 1, temp.j - 1 });
						}
						if (temp.i - 1 >= 0 && *(ptemp + (temp.i - 1) * width + temp.j) == Bg && flag_max[temp.i - 1][temp.j] == 0) {
							buffer.push({ temp.i - 1, temp.j });
						}
						if (temp.i - 1 >= 0 && temp.j + 1 < width && *(ptemp + (temp.i - 1) * width + temp.j + 1) == Bg && flag_max[temp.i - 1][temp.j + 1] == 0) {
							buffer.push({ temp.i - 1, temp.j + 1 });
						}
						if (temp.j - 1 >= 0 && *(ptemp + temp.i * width + temp.j - 1) == Bg && flag_max[temp.i][temp.j - 1] == 0) {
							buffer.push({ temp.i, temp.j - 1 });
						}
						if (temp.j + 1 < width && *(ptemp + temp.i * width + temp.j + 1) == Bg && flag_max[temp.i][temp.j + 1] == 0) {
							buffer.push({ temp.i, temp.j + 1 });
						}
						if (temp.i + 1 < height && temp.j - 1 >= 0 && *(ptemp + (temp.i + 1) * width + temp.j - 1) == Bg && flag_max[temp.i + 1][temp.j - 1] == 0) {
							buffer.push({ temp.i + 1, temp.j - 1 });
						}
						if (temp.i + 1 < height && *(ptemp + (temp.i + 1) * width + temp.j) == Bg && flag_max[temp.i + 1][temp.j] == 0) {
							buffer.push({ temp.i + 1, temp.j });
						}
						if (temp.i + 1 < height && temp.j + 1 < width && *(ptemp + (temp.i + 1) * width + temp.j + 1) == Bg && flag_max[temp.i + 1][temp.j + 1] == 0) {
							buffer.push({ temp.i + 1, temp.j + 1 });
						}
					}
				}
				count++;
			}
		}
	}

	for (int i = 0; i < height; i++) {
		delete[] flag_max[i];
	}
	delete[] flag_max;

	return count - 1;
}

LONG getArea(LPSTR image, int width, int height, int Bg, int connectivity, int* labels, int& maxLabel)
{
	int** flag_max;
	flag_max = new int* [height];
	for (int i = 0; i < height; i++) {
		flag_max[i] = new int[width];
	}
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			flag_max[i][j] = 0;
		}
	}

	int count = 1; // 区域标记
	unsigned char* ptemp = (unsigned char*)image;
	std::vector<int> areas;

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if ((*(ptemp + i * width + j) == Bg) && (flag_max[i][j] == 0))
			{
				point temp;
				temp.i = i;
				temp.j = j;
				std::queue<point> buffer;
				buffer.push(temp);
				int area = 0;
				while (!buffer.empty())
				{
					temp = buffer.front();
					buffer.pop();
					if (temp.i >= 0 && temp.i < height && temp.j >= 0 && temp.j < width && *(ptemp + temp.i * width + temp.j) == Bg && flag_max[temp.i][temp.j] == 0)
					{
						flag_max[temp.i][temp.j] = count;
						labels[temp.i * width + temp.j] = count;
						area++;
						if (temp.i - 1 >= 0 && *(ptemp + (temp.i - 1) * width + temp.j) == Bg && flag_max[temp.i - 1][temp.j] == 0) {
							buffer.push({ temp.i - 1, temp.j });
						}
						if (temp.j - 1 >= 0 && *(ptemp + temp.i * width + temp.j - 1) == Bg && flag_max[temp.i][temp.j - 1] == 0) {
							buffer.push({ temp.i, temp.j - 1 });
						}
						if (connectivity == 8)
						{
							if (temp.i - 1 >= 0 && temp.j - 1 >= 0 && *(ptemp + (temp.i - 1) * width + temp.j - 1) == Bg && flag_max[temp.i - 1][temp.j - 1] == 0) {
								buffer.push({ temp.i - 1, temp.j - 1 });
							}
							if (temp.i - 1 >= 0 && temp.j + 1 < width && *(ptemp + (temp.i - 1) * width + temp.j + 1) == Bg && flag_max[temp.i - 1][temp.j + 1] == 0) {
								buffer.push({ temp.i - 1, temp.j + 1 });
							}
							if (temp.i + 1 < height && temp.j - 1 >= 0 && *(ptemp + (temp.i + 1) * width + temp.j - 1) == Bg && flag_max[temp.i + 1][temp.j - 1] == 0) {
								buffer.push({ temp.i + 1, temp.j - 1 });
							}
							if (temp.i + 1 < height && temp.j + 1 < width && *(ptemp + (temp.i + 1) * width + temp.j + 1) == Bg && flag_max[temp.i + 1][temp.j + 1] == 0) {
								buffer.push({ temp.i + 1, temp.j + 1 });
							}
						}
						if (temp.j + 1 < width && *(ptemp + temp.i * width + temp.j + 1) == Bg && flag_max[temp.i][temp.j + 1] == 0) {
							buffer.push({ temp.i, temp.j + 1 });
						}
						if (temp.i + 1 < height && *(ptemp + (temp.i + 1) * width + temp.j) == Bg && flag_max[temp.i + 1][temp.j] == 0) {
							buffer.push({ temp.i + 1, temp.j });
						}
					}
				}
				areas.push_back(area);
				count++;
			}
		}
	}

	int maxArea = 0;
	for (int i = 0; i < areas.size(); i++) {
		if (areas[i] > maxArea) {
			maxArea = areas[i];
			maxLabel = i + 1; // 因为标记从1开始
		}
	}

	for (int i = 0; i < height; i++) {
		delete[] flag_max[i];
	}
	delete[] flag_max;

	return maxArea;
}

int calculatePerimeter(int* labels, int width, int height, int target_label)
{
	int perimeter = 0;
	for (int i = 1; i < height - 1; i++)
	{
		for (int j = 1; j < width - 1; j++)
		{
			if (labels[i * width + j] == target_label)
			{
				if (labels[(i - 1) * width + j] != target_label ||
					labels[(i + 1) * width + j] != target_label ||
					labels[i * width + (j - 1)] != target_label ||
					labels[i * width + (j + 1)] != target_label)
				{
					perimeter++;
				}
			}
		}
	}
	return perimeter;
}


int heartx(LONG lWidth, LONG lHeight, int* labels, int target_label)
{
	long long x_sum = 0;
	int count = 0;
	for (int i = 0; i < lHeight; i++)
	{
		for (int j = 0; j < lWidth; j++)
		{
			if (labels[i * lWidth + j] == target_label)
			{
				x_sum += j;  // 累加 x 坐标
				count++;
			}
		}
	}
	if (count == 0) return -1; // 避免除以零
	return static_cast<int>(x_sum / count);
}

int gethearty(LONG lWidth, LONG lHeight, int* labels, int target_label)
{
	long long y_sum = 0;
	int count = 0;
	for (int i = 0; i < lHeight; i++)
	{
		for (int j = 0; j < lWidth; j++)
		{
			if (labels[i * lWidth + j] == target_label)
			{
				y_sum += i;  // 累加 y 坐标
				count++;
			}
		}
	}
	if (count == 0) return -1; // 避免除以零
	return static_cast<int>(y_sum / count);
}


void CreatePaletteForImage(RGBQUAD* pPalette)
{
	srand((unsigned)time(NULL)); // 初始化随机数种子

	for (int i = 0; i < 256; i++)
	{
		pPalette[i].rgbBlue = i;
		pPalette[i].rgbGreen = i;
		pPalette[i].rgbRed = i;
		pPalette[i].rgbReserved = 0;
	}

	// 前景最大物体为蓝色
	pPalette[1].rgbBlue = 255; // 蓝色
	pPalette[1].rgbGreen = 0;
	pPalette[1].rgbRed = 0;
}

void SetRandomColor(RGBQUAD& color)
{
	do {
		color.rgbBlue = rand() % 256;
		color.rgbGreen = rand() % 256;
		color.rgbRed = rand() % 256;
	} while ((color.rgbBlue == 0 && color.rgbGreen == 0 && color.rgbRed == 0) || // 过滤黑色
		(color.rgbBlue == 255 && color.rgbGreen == 0 && color.rgbRed == 0)); // 过滤蓝色
}


void SetColorForObjects(LPSTR lpStartBits, int width, int height, int* labels, int maxLabel, RGBQUAD* pPalette)
{
	std::vector<RGBQUAD> colors(1); // 第一个元素保留为空，以便索引从1开始

	// 为每个非最大区域分配随机颜色
	for (int i = 0; i < width * height; i++)
	{
		int label = labels[i];
		if (label > 0 && label != maxLabel)
		{
			if (label >= colors.size())
			{
				colors.resize(label + 1);
				SetRandomColor(colors[label]);
			}
		}
	}

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			int index = i * width + j;
			int label = labels[index];
			if (label == maxLabel)
			{
				lpStartBits[index] = 1; // 蓝色
			}
			else if (label > 0)
			{
				lpStartBits[index] = label + 1; // 使用随机颜色
				pPalette[label + 1] = colors[label];
			}
		}
	}
}


void CMFCTest1View::OnApplication()
{
	// 获取文档
	CMFCTest1Doc* pDoc = GetDocument();

	LPSTR lpSrcDib;        // 指向源图象的指针    
	LPSTR lpSrcStartBits;  // 指向源像素的指针

	long lSrcLineBytes;    // 图象每行的字节数
	long lSrcWidth;        // 图象的宽度和高度
	long lSrcHeight;
	int lpSrcBitCount;     // 图像的位深

	// 锁定DIB
	lpSrcDib = (LPSTR)::GlobalLock((HGLOBAL)pDoc->GetHObject());

	if (lpSrcDib == nullptr)
	{
		MessageBox(L"无法锁定DIB对象！");
		return;
	}

	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib); // 找到DIB图象像素起始位置    

	if (pDoc->m_dib.GetColorNum(lpSrcDib) != 256) // 判断是否是8-bpp位图
	{
		MessageBox(L"对不起，不是256色位图！"); // 警告
		::GlobalUnlock((HGLOBAL)pDoc->GetHObject()); // 解除锁定
		return; //返回
	}

	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);  // 获取图象的宽度        
	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib); // 获取图象的高度    
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib); // 获取图像位深
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount); // 计算图象每行的字节数

	// 参数对话框
	CDlgApplication dlg;

	if (dlg.DoModal() != IDOK) // 显示对话框，设定平移量
	{
		::GlobalUnlock((HGLOBAL)pDoc->GetHObject()); // 解除锁定
		return;
	}

	int my_choice = dlg.m_foreground;
	int my_link = dlg.m_link;
	BOOL addColor = dlg.m_forecolor; // 获取是否需要加色

	int my_number = 0;
	double my_area = 0;
	double my_meter = 0;
	double my_circle = 0;
	double my_square = 0;

	int* labels = new int[lSrcWidth * lSrcHeight]; // 用于存储每个像素的标记
	memset(labels, 0, lSrcWidth * lSrcHeight * sizeof(int)); // 初始化标记数组

	int maxLabel = -1; // 最大物体的标记

	// 使用选择的前景色和连通数执行处理
	if (my_link == 0) // 4连通
	{
		if (my_choice == 0) // 黑
		{
			my_number = dealer_four(lpSrcStartBits, lSrcWidth, lSrcHeight, 0, labels);
			my_area = getArea(lpSrcStartBits, lSrcWidth, lSrcHeight, 0, 4, labels, maxLabel);
		}
		else if (my_choice == 1) // 白
		{
			my_number = dealer_four(lpSrcStartBits, lSrcWidth, lSrcHeight, 255, labels);
			my_area = getArea(lpSrcStartBits, lSrcWidth, lSrcHeight, 255, 4, labels, maxLabel);
		}
		else // 自动
		{
			int black = 0, white = 0;
			for (int i = 0; i < lSrcHeight; i++)
			{
				for (int j = 0; j < lSrcWidth; j++)
				{
					unsigned char* img = (unsigned char*)lpSrcStartBits + lSrcLineBytes * (lSrcHeight - 1 - i) + j;
					if (*img == 0)
						black++;
					else
						white++;
				}
			}

			if (black >= white) // 白
			{
				my_number = dealer_four(lpSrcStartBits, lSrcWidth, lSrcHeight, 255, labels);
				my_area = getArea(lpSrcStartBits, lSrcWidth, lSrcHeight, 255, 4, labels, maxLabel);
			}
			else // 黑
			{
				my_number = dealer_four(lpSrcStartBits, lSrcWidth, lSrcHeight, 0, labels);
				my_area = getArea(lpSrcStartBits, lSrcWidth, lSrcHeight, 0, 4, labels, maxLabel);
			}
		}

		my_meter = calculatePerimeter(labels, lSrcWidth, lSrcHeight, maxLabel);
		my_circle = 4 * 3.14 * my_area / (my_meter * my_meter); // 使用面积和周长计算圆形度
		my_circle = (my_circle < 1) ? my_circle : 1; // 将圆形度限制在0到1之间
		// 矩形度计算：物体面积 / 外接矩形面积
		int min_x = lSrcWidth, max_x = 0, min_y = lSrcHeight, max_y = 0;
		for (int i = 0; i < lSrcHeight; i++) {
			for (int j = 0; j < lSrcWidth; j++) {
				if (labels[i * lSrcWidth + j] == maxLabel) {
					if (i < min_y) min_y = i;
					if (i > max_y) max_y = i;
					if (j < min_x) min_x = j;
					if (j > max_x) max_x = j;
				}
			}
		}
		int bounding_width = max_x - min_x + 1;
		int bounding_height = max_y - min_y + 1;
		my_square = my_area / (double)(bounding_width * bounding_height);
	}

	if (my_link == 1) // 8连通
	{
		if (my_choice == 0) // 黑
		{
			my_number = dealer_eight(lpSrcStartBits, lSrcWidth, lSrcHeight, 0, labels);
			my_area = getArea(lpSrcStartBits, lSrcWidth, lSrcHeight, 0, 8, labels, maxLabel);
		}
		else if (my_choice == 1) // 白
		{
			my_number = dealer_eight(lpSrcStartBits, lSrcWidth, lSrcHeight, 255, labels);
			my_area = getArea(lpSrcStartBits, lSrcWidth, lSrcHeight, 255, 8, labels, maxLabel);
		}
		else // 自动
		{
			int black = 0, white = 0;
			for (int i = 0; i < lSrcHeight; i++)
			{
				for (int j = 0; j < lSrcWidth; j++)
				{
					unsigned char* img = (unsigned char*)lpSrcStartBits + lSrcLineBytes * (lSrcHeight - 1 - i) + j;
					if (*img == 0)
						black++;
					else
						white++;
				}
			}

			if (black >= white) // 白
			{
				my_number = dealer_eight(lpSrcStartBits, lSrcWidth, lSrcHeight, 255, labels);
				my_area = getArea(lpSrcStartBits, lSrcWidth, lSrcHeight, 255, 8, labels, maxLabel);
			}
			else // 黑
			{
				my_number = dealer_eight(lpSrcStartBits, lSrcWidth, lSrcHeight, 0, labels);
				my_area = getArea(lpSrcStartBits, lSrcWidth, lSrcHeight, 0, 8, labels, maxLabel);
			}
		}

		my_meter = calculatePerimeter(labels, lSrcWidth, lSrcHeight, maxLabel);
		my_circle = 4 * 3.14 * my_area / (my_meter * my_meter); // 使用面积和周长计算圆形度
		my_circle = (my_circle < 1) ? my_circle : 1; // 将圆形度限制在0到1之间
		// 矩形度计算：物体面积 / 外接矩形面积
		int min_x = lSrcWidth, max_x = 0, min_y = lSrcHeight, max_y = 0;
		for (int i = 0; i < lSrcHeight; i++) {
			for (int j = 0; j < lSrcWidth; j++) {
				if (labels[i * lSrcWidth + j] == maxLabel) {
					if (i < min_y) min_y = i;
					if (i > max_y) max_y = i;
					if (j < min_x) min_x = j;
					if (j > max_x) max_x = j;
				}
			}
		}
		int bounding_width = max_x - min_x + 1;
		int bounding_height = max_y - min_y + 1;
		my_square = my_area / (double)(bounding_width * bounding_height);
	}

	if (addColor)
	{
		RGBQUAD* pPalette = new RGBQUAD[256];
		CreatePaletteForImage(pPalette);

		SetColorForObjects(lpSrcStartBits, lSrcWidth, lSrcHeight, labels, maxLabel, pPalette);

		// 创建一个新的DIB，添加颜色表
		BITMAPINFOHEADER bmiHeader;
		memset(&bmiHeader, 0, sizeof(BITMAPINFOHEADER));
		bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
		bmiHeader.biWidth = lSrcWidth;
		bmiHeader.biHeight = lSrcHeight;
		bmiHeader.biPlanes = 1;
		bmiHeader.biBitCount = 8;
		bmiHeader.biCompression = BI_RGB;
		bmiHeader.biSizeImage = lSrcLineBytes * lSrcHeight;

		// 创建 DIB
		void* pBits = nullptr;
		HBITMAP hDib = CreateDIBSection(NULL, (BITMAPINFO*)&bmiHeader, DIB_RGB_COLORS, &pBits, NULL, 0);
		if (hDib && pBits)
		{
			memcpy(pBits, lpSrcStartBits, lSrcLineBytes * lSrcHeight);

			// 应用新的调色板
			unsigned char* newDIBBits = (unsigned char*)pBits;
			for (int i = 0; i < lSrcHeight; i++)
			{
				for (int j = 0; j < lSrcWidth; j++)
				{
					int index = i * lSrcWidth + j;
					newDIBBits[index] = lpSrcStartBits[index];
				}
			}

			// 将新的DIB设置到文档中
			pDoc->SetDIB(hDib, &bmiHeader, pPalette, pBits);

			// 设置脏标记
			pDoc->SetModifiedFlag(TRUE);

			// 更新视图
			pDoc->UpdateAllViews(NULL);
		}

		delete[] pPalette;
	}

	::GlobalUnlock((HGLOBAL)pDoc->GetHObject()); // 解除锁定

	CDlgApplication2 Dlg; // 创建结果显示对话框

	Dlg.m_Num = my_number;
	Dlg.m_mS = my_area;
	Dlg.m_mC = my_meter;
	Dlg.m_mRound = my_circle;
	Dlg.m_mRectangle = my_square;
	Dlg.m_x = heartx(lSrcWidth, lSrcHeight, labels, maxLabel);
	Dlg.m_y = lSrcHeight-gethearty(lSrcWidth, lSrcHeight, labels, maxLabel);//由从下往上改为从上往下

	if (Dlg.DoModal() != IDOK) // 显示对话框
	{
		return;
	}

	delete[] labels;
}




#include <vector>
#include <cmath>

// 改进后的高斯滤波核
const double gaussKernel[5][5] = {
	{1,  4,  6,  4, 1},
	{4, 16, 24, 16, 4},
	{6, 24, 36, 24, 6},
	{4, 16, 24, 16, 4},
	{1,  4,  6,  4, 1}
};

// Sobel算子
const int sobelX[3][3] = {
	{-1, 0, 1},
	{-2, 0, 2},
	{-1, 0, 1}
};

const int sobelY[3][3] = {
	{ 1,  2,  1},
	{ 0,  0,  0},
	{-1, -2, -1}
};

// 边界处理函数
inline int clamp(int x, int lower, int upper) {
	return x < lower ? lower : (x > upper ? upper : x);
}

// 高斯滤波
void gaussianBlur(const std::vector<std::vector<unsigned char>>& src, std::vector<std::vector<unsigned char>>& dst) {
	int width = src[0].size();
	int height = src.size();
	dst = std::vector<std::vector<unsigned char>>(height, std::vector<unsigned char>(width, 0));

	for (int i = 2; i < height - 2; i++) {
		for (int j = 2; j < width - 2; j++) {
			double sum = 0;
			double weightSum = 0;
			for (int u = -2; u <= 2; u++) {
				for (int v = -2; v <= 2; v++) {
					int x = clamp(j + v, 0, width - 1);
					int y = clamp(i + u, 0, height - 1);
					sum += src[y][x] * gaussKernel[u + 2][v + 2];
					weightSum += gaussKernel[u + 2][v + 2];
				}
			}
			dst[i][j] = static_cast<unsigned char>(sum / weightSum);
		}
	}
}

// 计算梯度幅值和方向
void computeGradient(const std::vector<std::vector<unsigned char>>& src, std::vector<std::vector<double>>& gradient, std::vector<std::vector<double>>& direction) {
	int width = src[0].size();
	int height = src.size();
	gradient = std::vector<std::vector<double>>(height, std::vector<double>(width, 0));
	direction = std::vector<std::vector<double>>(height, std::vector<double>(width, 0));

	for (int i = 1; i < height - 1; i++) {
		for (int j = 1; j < width - 1; j++) {
			double gx = 0, gy = 0;
			for (int u = -1; u <= 1; u++) {
				for (int v = -1; v <= 1; v++) {
					int x = clamp(j + v, 0, width - 1);
					int y = clamp(i + u, 0, height - 1);
					gx += src[y][x] * sobelX[u + 1][v + 1];
					gy += src[y][x] * sobelY[u + 1][v + 1];
				}
			}
			gradient[i][j] = std::sqrt(gx * gx + gy * gy);
			direction[i][j] = std::atan2(gy, gx);
		}
	}
}

// 非极大值抑制
void nonMaxSuppression(const std::vector<std::vector<double>>& gradient, const std::vector<std::vector<double>>& direction, std::vector<std::vector<double>>& suppressed) {
	int width = gradient[0].size();
	int height = gradient.size();
	suppressed = std::vector<std::vector<double>>(height, std::vector<double>(width, 0));

	for (int i = 1; i < height - 1; i++) {
		for (int j = 1; j < width - 1; j++) {
			double angle = direction[i][j] * 180.0 / 3.14;
			angle = angle < 0 ? angle + 180 : angle;

			double q = 255, r = 255;
			if ((0 <= angle && angle < 22.5) || (157.5 <= angle && angle <= 180)) {
				q = gradient[i][j + 1];
				r = gradient[i][j - 1];
			}
			else if (22.5 <= angle && angle < 67.5) {
				q = gradient[i + 1][j - 1];
				r = gradient[i - 1][j + 1];
			}
			else if (67.5 <= angle && angle < 112.5) {
				q = gradient[i + 1][j];
				r = gradient[i - 1][j];
			}
			else if (112.5 <= angle && angle < 157.5) {
				q = gradient[i - 1][j - 1];
				r = gradient[i + 1][j + 1];
			}

			if (gradient[i][j] >= q && gradient[i][j] >= r) {
				suppressed[i][j] = gradient[i][j];
			}
			else {
				suppressed[i][j] = 0;
			}
		}
	}
}

// 双阈值检测和边缘连接
void doubleThreshold(const std::vector<std::vector<double>>& suppressed, std::vector<std::vector<unsigned char>>& edges, double lowThreshold, double highThreshold) {
	int width = suppressed[0].size();
	int height = suppressed.size();
	edges = std::vector<std::vector<unsigned char>>(height, std::vector<unsigned char>(width, 0));

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (suppressed[i][j] >= highThreshold) {
				edges[i][j] = 255;
			}
			else if (suppressed[i][j] >= lowThreshold) {
				edges[i][j] = 128;
			}
		}
	}

	for (int i = 1; i < height - 1; i++) {
		for (int j = 1; j < width - 1; j++) {
			if (edges[i][j] == 128) {
				if ((edges[i + 1][j - 1] == 255) || (edges[i + 1][j] == 255) || (edges[i + 1][j + 1] == 255)
					|| (edges[i][j - 1] == 255) || (edges[i][j + 1] == 255)
					|| (edges[i - 1][j - 1] == 255) || (edges[i - 1][j] == 255) || (edges[i - 1][j + 1] == 255)) {
					edges[i][j] = 255;
				}
				else {
					edges[i][j] = 0;
				}
			}
		}
	}
}

void cannyEdgeDetection(const std::vector<std::vector<unsigned char>>& src, std::vector<std::vector<unsigned char>>& edges, double lowThreshold, double highThreshold) {
	std::vector<std::vector<unsigned char>> blurred;
	gaussianBlur(src, blurred);

	std::vector<std::vector<double>> gradient, direction;
	computeGradient(blurred, gradient, direction);

	std::vector<std::vector<double>> suppressed;
	nonMaxSuppression(gradient, direction, suppressed);

	doubleThreshold(suppressed, edges, lowThreshold, highThreshold);
}

void CMFCTest1View::OnCanny()
{
	// 获取文档
	CMFCTest1Doc* pDoc = GetDocument();

	LPSTR lpSrcDib;        // 指向源图象的指针    
	LPSTR lpSrcStartBits;  // 指向源像素的指针

	long lSrcLineBytes;    // 图象每行的字节数
	long lSrcWidth;        // 图象的宽度和高度
	long lSrcHeight;
	int lpSrcBitCount;     // 图像的位深

	// 锁定DIB
	lpSrcDib = (LPSTR)::GlobalLock((HGLOBAL)pDoc->GetHObject());

	if (lpSrcDib == nullptr)
	{
		MessageBox(L"无法锁定DIB对象！");
		return;
	}

	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib); // 找到DIB图象像素起始位置    

	if (pDoc->m_dib.GetColorNum(lpSrcDib) != 256) // 判断是否是8-bpp位图
	{
		MessageBox(L"对不起，不是256色位图！"); // 警告
		::GlobalUnlock((HGLOBAL)pDoc->GetHObject()); // 解除锁定
		return; //返回
	}

	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);  // 获取图象的宽度        
	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib); // 获取图象的高度    
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib); // 获取图像位深
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount); // 计算图象每行的字节数

	// 将 DIB 图像转换为二维数组格式
	std::vector<std::vector<unsigned char>> srcImg(lSrcHeight, std::vector<unsigned char>(lSrcWidth));
	for (int i = 0; i < lSrcHeight; i++) {
		for (int j = 0; j < lSrcWidth; j++) {
			srcImg[i][j] = lpSrcStartBits[i * lSrcLineBytes + j];
		}
	}

	// 执行 Canny 边缘检测
	std::vector<std::vector<unsigned char>> edges;
	double lowThreshold = 50;
	double highThreshold = 150;
	cannyEdgeDetection(srcImg, edges, lowThreshold, highThreshold);

	// 将检测结果保存回文档
	for (int i = 0; i < lSrcHeight; i++) {
		for (int j = 0; j < lSrcWidth; j++) {
			lpSrcStartBits[i * lSrcLineBytes + j] = edges[i][j];
		}
	}

	// 更新文档
	pDoc->SetModifiedFlag(TRUE);
	pDoc->UpdateAllViews(NULL);

	// 解除锁定
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());
}


//实现未遮蔽锐化
void unsharpMasking(const std::vector<std::vector<unsigned char>>& src, std::vector<std::vector<unsigned char>>& dst, double amount, double threshold) {
	int width = src[0].size();
	int height = src.size();
	dst = std::vector<std::vector<unsigned char>>(height, std::vector<unsigned char>(width, 0));

	std::vector<std::vector<unsigned char>> blurred;
	gaussianBlur(src, blurred);

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			int diff = src[i][j] - blurred[i][j];
			if (std::abs(diff) >= threshold) {
				int newValue = src[i][j] + static_cast<int>(amount * diff);
				dst[i][j] = clamp(newValue, 0, 255);
			}
			else {
				dst[i][j] = src[i][j];
			}
		}
	}
}

//实现USM锐化
void CMFCTest1View::OnUsm()
{
	// 获取文档
	CMFCTest1Doc* pDoc = GetDocument();

	LPSTR lpSrcDib;        // 指向源图象的指针    
	LPSTR lpSrcStartBits;  // 指向源像素的指针

	long lSrcLineBytes;    // 图象每行的字节数
	long lSrcWidth;        // 图象的宽度和高度
	long lSrcHeight;
	int lpSrcBitCount;     // 图像的位深

	// 锁定DIB
	lpSrcDib = (LPSTR)::GlobalLock((HGLOBAL)pDoc->GetHObject());

	if (lpSrcDib == nullptr)
	{
		MessageBox(L"无法锁定DIB对象！");
		return;
	}

	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib); // 找到DIB图象像素起始位置    

	if (pDoc->m_dib.GetColorNum(lpSrcDib) != 256) // 判断是否是8-bpp位图
	{
		MessageBox(L"对不起，不是256色位图！"); // 警告
		::GlobalUnlock((HGLOBAL)pDoc->GetHObject()); // 解除锁定
		return; //返回
	}

	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);  // 获取图象的宽度        
	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib); // 获取图象的高度    
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib); // 获取图像位深
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount); // 计算图象每行的字节数

	// 将 DIB 图像转换为二维数组格式
	std::vector<std::vector<unsigned char>> srcImg(lSrcHeight, std::vector<unsigned char>(lSrcWidth));
	for (int i = 0; i < lSrcHeight; i++) {
		for (int j = 0; j < lSrcWidth; j++) {
			srcImg[i][j] = lpSrcStartBits[i * lSrcWidth + j];
		}
	}

	// 执行 USM 锐化
	std::vector<std::vector<unsigned char>> dstImg;
	double amount = 1.5; // 锐化程度
	double threshold = 10; // 阈值
	unsharpMasking(srcImg, dstImg, amount, threshold);

	// 将锐化结果保存回文档
	for (int i = 0; i < lSrcHeight; i++) {
		for (int j = 0; j < lSrcWidth; j++) {
			lpSrcStartBits[i * lSrcWidth + j] = dstImg[i][j];
		}
	}

	// 更新文档
	pDoc->SetModifiedFlag(TRUE);
	pDoc->UpdateAllViews(NULL);

	// 解除锁定
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());
}
