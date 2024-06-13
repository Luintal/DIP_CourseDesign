// DlgGeoTran.cpp: 实现文件
//

#include "pch.h"
#include "MFCTest1.h"
#include "afxdialogex.h"
#include "DlgGeoTran.h"



// DlgGeoTran 对话框

IMPLEMENT_DYNAMIC(DlgGeoTran, CDialogEx)

DlgGeoTran::DlgGeoTran(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DLG_GEOTrans, pParent)
{
	m_XOffset = 0;
	m_YOffset = 0;
}

DlgGeoTran::~DlgGeoTran()
{
}

void DlgGeoTran::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_XOffset, m_XOffset);
	DDX_Text(pDX, IDC_EDIT_YOffset, m_YOffset);
}


BEGIN_MESSAGE_MAP(DlgGeoTran, CDialogEx)
	ON_BN_CLICKED(IDC_ImagePreview, &DlgGeoTran::OnBnClickedImagepreview)
	ON_BN_CLICKED(IDC_ImageRestore, &DlgGeoTran::OnBnClickedImagerestore)
END_MESSAGE_MAP()


// DlgGeoTran 消息处理程序
int TranslationDIB(char* lpSrcStartBits, long lSrcWidth, long lSrcHeight, long lXOffset, long lYOffset)
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

void DlgGeoTran::OnBnClickedImagepreview()
{
	// TODO: 在此添加控件通知处理程序代码
      // 获取用户设定的平移量
    UpdateData(TRUE);
    LONG lXOffset = m_XOffset;
    LONG lYOffset = m_YOffset;
    
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

    // 调用平移函数
    if (TranslationDIB(reinterpret_cast<char*>(lpSrcStartBits), lSrcWidth, lSrcHeight, lXOffset, lYOffset))
    {
		// 设置脏标记
		pDoc->SetModifiedFlag(FALSE);
		
		// 更新视图
        pDoc->UpdateAllViews(NULL);
		m_bPreviewed = TRUE;
    }
    else
    {
        MessageBox(L"分配内存失败！", L"系统提示", MB_ICONINFORMATION | MB_OK);
    }
}


void DlgGeoTran::OnBnClickedImagerestore()
{
	// TODO: 在此添加控件通知处理程序代码
    // 恢复原始图像数据
    pDoc->OnImgrestore();
    
    // 设置脏标记
    pDoc->SetModifiedFlag(FALSE);

    // 更新视图
    pDoc->UpdateAllViews(NULL);
}
