
// MFCTest1Doc.cpp: CMFCTest1Doc 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "MFCTest1.h"
#endif

#include "MFCTest1Doc.h"

#include <propkey.h>
#include"DIBAPI.H"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMFCTest1Doc

IMPLEMENT_DYNCREATE(CMFCTest1Doc, CDocument)

BEGIN_MESSAGE_MAP(CMFCTest1Doc, CDocument)
	ON_COMMAND(ID_ImgRestore, &CMFCTest1Doc::OnImgrestore)
END_MESSAGE_MAP()


// CMFCTest1Doc 构造/析构

CMFCTest1Doc::CMFCTest1Doc() noexcept
{
	// TODO: 在此添加一次性构造代码
	m_hDIB = NULL;// 初始化变量
	m_palDIB = NULL;
	m_sizeDoc = CSize(1, 1);
}

CMFCTest1Doc::~CMFCTest1Doc()
{
	if (m_hDIB != NULL)// 判断是否有DIB对象
	{
		::GlobalFree((HGLOBAL)m_hDIB);
	}


	if (m_palDIB != NULL)// 判断调色板是否存在
	{
		delete m_palDIB;
	}
}

BOOL CMFCTest1Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}




// CMFCTest1Doc 序列化

void CMFCTest1Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 在此添加存储代码
	}
	else
	{
		// TODO: 在此添加加载代码
	}
}

#ifdef SHARED_HANDLERS

// 缩略图的支持
void CMFCTest1Doc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 修改此代码以绘制文档数据
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 搜索处理程序的支持
void CMFCTest1Doc::InitializeSearchContent()
{
	CString strSearchContent;
	// 从文档数据设置搜索内容。
	// 内容部分应由“;”分隔

	// 例如:     strSearchContent = _T("point;rectangle;circle;ole object;")；
	SetSearchContent(strSearchContent);
}

void CMFCTest1Doc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CMFCTest1Doc 诊断

#ifdef _DEBUG
void CMFCTest1Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMFCTest1Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CMFCTest1Doc 命令


BOOL CMFCTest1Doc::OnOpenDocument(LPCTSTR lpszPathName)
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;

	// TODO:  在此添加您专用的创建代码
	CFile file;
	if (!file.Open(lpszPathName, CFile::modeRead |
		CFile::shareDenyWrite))// 打开文件
	{
		return FALSE;// 返回FALSE
	}
	DeleteContents();
	m_hDIB = m_dib.LoadFile(file);
	if (m_hDIB == NULL)// 调用LoadFile()读取图象
	{
		return FALSE;
	}
	SetDib();// 初始化DIB
	if (m_hDIB == NULL)	// 判断读取文件是否成功
	{
		AfxMessageBox(L"读取图像时出错");// 提示出错				
		return FALSE;// 返回FALSE
	}
	SetPathName(lpszPathName);// 设置文件名称		
	SetModifiedFlag(FALSE);// 初始化修改标记为FALSE		
	return TRUE;// 返回TRUE
}


BOOL CMFCTest1Doc::OnSaveDocument(LPCTSTR lpszPathName)
{
	// TODO: 在此添加专用代码和/或调用基类
	// TODO: 在此添加专用代码和/或调用基类
	CFile file;
	if (!file.Open(lpszPathName, CFile::modeCreate |// 打开文件
		CFile::modeReadWrite | CFile::shareExclusive))
	{
		return FALSE;// 返回FALSE
	}
	BOOL bSuccess = FALSE;
	bSuccess = m_dib.SaveFile(m_hDIB, file);	// 保存图象	
	file.Close();// 关闭文件	
	SetModifiedFlag(FALSE);// 重置脏标记为FALSE
	if (!bSuccess)
	{
		AfxMessageBox(L"保存BMP图象时出错");// 提示出错
	}
	return bSuccess;
	//return CDocument::OnSaveDocument(lpszPathName);
	return CDocument::OnSaveDocument(lpszPathName);
}

void CMFCTest1Doc::SetDib() //这个函数需要手动添加
{
	LPSTR lpdib = (LPSTR) ::GlobalLock((HGLOBAL)m_hDIB);

	if (m_dib.GetWidth(lpdib) > INT_MAX || m_dib.GetHeight(lpdib) > INT_MAX)// 判断图象是否过大
	{
		::GlobalUnlock((HGLOBAL)m_hDIB);
		::GlobalFree((HGLOBAL)m_hDIB);	// 释放DIB对象			
		m_hDIB = NULL;// 设置DIB为空		
		AfxMessageBox(L"初始化失败");
		return;
	}
	m_sizeDoc = CSize((int)m_dib.GetWidth(lpdib), (int)m_dib.GetHeight(lpdib));// 设置文档大小	
	::GlobalUnlock((HGLOBAL)m_hDIB);
	m_palDIB = new CPalette;// 创建新调色板		
	if (m_palDIB == NULL)// 判断是否创建成功
	{
		::GlobalFree((HGLOBAL)m_hDIB);	// 失败		
		m_hDIB = NULL;// 设置DIB对象为空
		return;
	}
	// 调用CreateDIBPalette来创建调色板
	if (m_dib.ConstructPalette(m_hDIB, m_palDIB) == NULL)
	{
		delete m_palDIB;// 删除				
		m_palDIB = NULL;// 设置为空	
		return;// 返回空
	}
}
void CMFCTest1Doc::UpdateObject(HGLOBAL hDIB)   //这个函数需要手动添加
{
	if (m_hDIB != NULL)               // 判断DIB是否为空
	{
		::GlobalFree((HGLOBAL)m_hDIB);// 非空，则清除
	}
	m_hDIB = hDIB;                     // 替换成新的DIB对象	
}

void CMFCTest1Doc::OnImgrestore()
{
	// TODO: 在此添加命令处理程序代码
	if (IsModified())
	{
		// 提示用户该操作将丢失所有当前的修改
		if (MessageBox(NULL, L"重新加载图像将丢失所有的改动！是否继续？", __T("系统提示"), MB_ICONQUESTION | MB_YESNO) == IDNO)
		{
			// 用户取消操作，直接返回
			return;
		}
	}

	CFile file;
	CFileException fe;

	CString strPathName;

	// 获取当前文件路径
	strPathName = GetPathName();
	// TODO:  在此添加您专用的创建代码

	if (!file.Open(strPathName, CFile::modeRead |
		CFile::shareDenyWrite))// 打开文件
	{
		return;// 返回FALSE
	}
	DeleteContents();
	m_hDIB = m_dib.LoadFile(file);
	if (m_hDIB == NULL)// 调用LoadFile()读取图象
	{
		return;
	}
	SetDib();// 初始化DIB
	if (m_hDIB == NULL)	// 判断读取文件是否成功
	{
		AfxMessageBox(L"读取图像时出错");// 提示出错				
		return;// 返回FALSE
	}
	SetPathName(strPathName);// 设置文件名称		
	SetModifiedFlag(FALSE);// 初始化修改标记为FALSE		
	UpdateAllViews(NULL);
	return;// 返回TRUE
}

void CMFCTest1Doc::UpdateColorImage(BYTE* pColorData, int width, int height)
{
	if (m_ColorBitmap.GetSafeHandle())
		m_ColorBitmap.DeleteObject();  // 如果位图已经存在，先删除

	// 创建位图信息头和调色板
	BITMAPINFO bmi;
	ZeroMemory(&bmi, sizeof(bmi));
	bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmi.bmiHeader.biWidth = width;
	bmi.bmiHeader.biHeight = -height; // 顶向下的位图
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biBitCount = 8;  // 8位彩色图（使用调色板）
	bmi.bmiHeader.biCompression = BI_RGB;

	// 定义调色板
	RGBQUAD* palette = bmi.bmiColors;
	for (int i = 0; i < 256; i++) {
		palette[i].rgbRed = palette[i].rgbGreen = palette[i].rgbBlue = i;
		palette[i].rgbReserved = 0;
	}

	CDC* pDC = AfxGetMainWnd()->GetDC();
	if (m_ColorBitmap.CreateCompatibleBitmap(pDC, width, height)) {
		if (!SetDIBits(pDC->m_hDC, m_ColorBitmap, 0, height, pColorData, &bmi, DIB_RGB_COLORS)) {
			// 处理SetDIBits失败的情况
			AfxMessageBox(L"Failed to set DIB bits.");
		}
	}
	else {
		// 处理位图创建失败的情况
		AfxMessageBox(L"Failed to create compatible bitmap.");
	}
	AfxGetMainWnd()->ReleaseDC(pDC);

	SetModifiedFlag(TRUE);  // 设置文档为已修改状态
	UpdateAllViews(NULL);   // 更新所有视图
}

void CMFCTest1Doc::SetDIB(HBITMAP hDib, BITMAPINFOHEADER* pBmiHeader, RGBQUAD* pColors, void* pBits)
{
	// 清理现有 DIB 对象
	if (m_hDIB)
	{
		::GlobalUnlock(m_hDIB);
		::GlobalFree(m_hDIB);
		m_hDIB = NULL;
	}

	// 设置新的 DIB 对象
	m_hDIB = ::GlobalAlloc(GHND, sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD) * 256 + pBmiHeader->biSizeImage);
	if (m_hDIB)
	{
		LPBYTE lpDib = (LPBYTE)::GlobalLock(m_hDIB);
		if (lpDib)
		{
			// 拷贝 BITMAPINFOHEADER
			memcpy(lpDib, pBmiHeader, sizeof(BITMAPINFOHEADER));
			lpDib += sizeof(BITMAPINFOHEADER);

			// 拷贝颜色表
			memcpy(lpDib, pColors, sizeof(RGBQUAD) * 256);
			lpDib += sizeof(RGBQUAD) * 256;

			// 拷贝图像数据
			memcpy(lpDib, pBits, pBmiHeader->biSizeImage);

			::GlobalUnlock(m_hDIB);
		}
	}
}

void CMFCTest1Doc::InitDIBData()
{
	// 初始化DIB对象

	// 判断调色板是否为空
	if (m_palDIB != NULL)
	{
		// 删除调色板对象
		delete m_palDIB;

		// 重置调色板为空
		m_palDIB = NULL;
	}

	// 如果DIB对象为空，直接返回
	if (m_hDIB == NULL)
	{
		// 返回
		return;
	}

	LPSTR lpDIB = (LPSTR) ::GlobalLock((HGLOBAL)m_hDIB);

	// 判断图像是否过大
	if (::DIBWidth(lpDIB) > INT_MAX || ::DIBHeight(lpDIB) > INT_MAX)
	{
		::GlobalUnlock((HGLOBAL)m_hDIB);

		// 释放DIB对象
		::GlobalFree((HGLOBAL)m_hDIB);

		// 设置DIB为空
		m_hDIB = NULL;

		CString strMsg;
		strMsg = "BMP图像太大！";

		// 提示用户
		MessageBox(NULL, strMsg, L"系统提示", MB_ICONINFORMATION | MB_OK);

		// 返回
		return;
	}

	// 设置文档大小
	m_sizeDoc = CSize((int) ::DIBWidth(lpDIB), (int) ::DIBHeight(lpDIB));

	::GlobalUnlock((HGLOBAL)m_hDIB);

	// 创建新调色板
	m_palDIB = new CPalette;

	// 判断是否创建成功
	if (m_palDIB == NULL)
	{
		// 失败，可能是内存不足
		::GlobalFree((HGLOBAL)m_hDIB);

		// 设置DIB对象为空
		m_hDIB = NULL;

		// 返回
		return;
	}

	// 调用CreateDIBPalette来创建调色板
	if (::CreateDIBPalette((HDIB)m_hDIB, m_palDIB) == NULL)
	{
		// 返回空，可能该DIB对象没有调色板

		// 删除
		delete m_palDIB;

		// 设置为空
		m_palDIB = NULL;

		// 返回
		return;
	}
}

void CMFCTest1Doc::ReplaceHDIB(HGLOBAL hDIB)
{
	// 替换DIB，在功能粘贴中用到该函数

	// 判断DIB是否为空
	if (m_hDIB != NULL)
	{
		// 非空，则清除
		::GlobalFree((HGLOBAL)m_hDIB);
	}

	// 替换成新的DIB对象
	m_hDIB = hDIB;

}

CSize CMFCTest1Doc::GetDocSize() const
{
	if (m_hDIB == NULL)
		return CSize(0, 0);

	LPSTR lpDIB = (LPSTR)::GlobalLock(m_hDIB);
	if (lpDIB == NULL)
		return CSize(0, 0);

	BITMAPINFOHEADER* pBIH = (BITMAPINFOHEADER*)(lpDIB + sizeof(BITMAPFILEHEADER));
	CSize size(pBIH->biWidth, pBIH->biHeight);

	::GlobalUnlock(m_hDIB);
	return size;
}
