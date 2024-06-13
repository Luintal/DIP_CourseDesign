
// MFCTest1Doc.h: CMFCTest1Doc 类的接口
//


#pragma once
#include "Dib.h"
//extern CDib m_dib;

class CMFCTest1Doc : public CDocument
{
protected: // 仅从序列化创建
	CMFCTest1Doc() noexcept;
	DECLARE_DYNCREATE(CMFCTest1Doc)

// 特性
public:
	CDib m_dib;
// 操作
public:
	HGLOBAL GetHObject() const	//获取Dib对象的句柄
	{
		return m_hDIB;
	}
	CPalette* GetDocPal() const	//获取调色板指针
	{
		return m_palDIB;
	}
	CSize GetDocDimension() const//获取调色板大小
	{
		return m_sizeDoc;
	}
	void UpdateObject(HGLOBAL hDIB);//更新dib对象
	void UpdateColorImage(BYTE* pColorData, int width, int height);
	void SetDIB(HBITMAP hDib, BITMAPINFOHEADER* pBmiHeader, RGBQUAD* pColors, void* pBits);

	void InitDIBData();

	void ReplaceHDIB(HGLOBAL hNewDIB);

	CSize GetDocSize() const;
	
// 重写
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 实现
public:
	void SetDib();				//初始化dib对象
	virtual ~CMFCTest1Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
private:
	CBitmap m_ColorBitmap;  // 用于存储彩色位图的成员变量

protected:
	HGLOBAL m_hDIB;
	CPalette* m_palDIB;
	CSize m_sizeDoc;
// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 用于为搜索处理程序设置搜索内容的 Helper 函数
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	afx_msg void OnImgrestore();



};


