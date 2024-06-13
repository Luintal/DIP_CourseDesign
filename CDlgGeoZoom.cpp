// CDlgGeoZoom.cpp: 实现文件
//

#include "pch.h"
#include "MFCTest1.h"
#include "afxdialogex.h"
#include "CDlgGeoZoom.h"
#include "DIBAPI.H"
#include "GeoTrans.h"

// CDlgGeoZoom 对话框

IMPLEMENT_DYNAMIC(CDlgGeoZoom, CDialogEx)

CDlgGeoZoom::CDlgGeoZoom(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DlgGeoZoom, pParent)
{
	m_XZoom = 0.0f;
	m_YZoom = 0.0f;
}

CDlgGeoZoom::~CDlgGeoZoom()
{
}

void CDlgGeoZoom::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_XZoom, m_XZoom);
	DDV_MinMaxFloat(pDX, m_XZoom, 0.25f, 4.f);
	DDX_Text(pDX, IDC_EDIT_YZoom, m_YZoom);
	DDV_MinMaxFloat(pDX, m_YZoom, 0.25f, 4.f);
}


BEGIN_MESSAGE_MAP(CDlgGeoZoom, CDialogEx)
	ON_BN_CLICKED(IDC_PriImg, &CDlgGeoZoom::OnBnClickedPriimg)
	ON_BN_CLICKED(IDC_ResImg, &CDlgGeoZoom::OnBnClickedResimg)
END_MESSAGE_MAP()


// CDlgGeoZoom 消息处理程序



void CDlgGeoZoom::OnBnClickedPriimg()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	// 缩放比率
	float fXZoomRatio= m_XZoom;
	float fYZoomRatio= m_YZoom;
	// 锁定DIB
	LPSTR lpDIB = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());
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
		m_bPreviewed = TRUE;
	}
	else
	{
		// 提示用户
		MessageBox(L"分配内存失败！", L"系统提示", MB_ICONINFORMATION | MB_OK);
	}

}


void CDlgGeoZoom::OnBnClickedResimg()
{
	// TODO: 在此添加控件通知处理程序代码
	pDoc->OnImgrestore();

	// 设置脏标记
	pDoc->SetModifiedFlag(FALSE);

	// 更新视图
	pDoc->UpdateAllViews(NULL);
}
