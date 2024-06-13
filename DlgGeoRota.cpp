// DlgGeoRota.cpp: 实现文件
//

#include "pch.h"
#include "MFCTest1.h"
#include "afxdialogex.h"
#include "DlgGeoRota.h"
#include "afxwin.h"

// DlgGeoRota 对话框

IMPLEMENT_DYNAMIC(DlgGeoRota, CDialogEx)

DlgGeoRota::DlgGeoRota(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DLG_GEORota, pParent)
{
	m_iRotateAngle = 0;
}

DlgGeoRota::~DlgGeoRota()
{
}

void DlgGeoRota::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_Rotate, m_iRotateAngle);
	DDV_MinMaxInt(pDX, m_iRotateAngle, 0, 360);
}


BEGIN_MESSAGE_MAP(DlgGeoRota, CDialogEx)
	ON_BN_CLICKED(IDC_ImagePre, &DlgGeoRota::OnBnClickedImagepre)
	ON_BN_CLICKED(IDC_ImageRes, &DlgGeoRota::OnBnClickedImageres)
END_MESSAGE_MAP()


// DlgGeoRota 消息处理程序


void DlgGeoRota::OnBnClickedImagepre()
{
	// TODO: 在此添加控件通知处理程序代码
	// 获取旋转角度	
	UpdateData(TRUE);
	
	// 指向DIB的指针
	LPSTR lpDIB;
	//锁定DIB
	lpDIB = (LPSTR)::GlobalLock((HGLOBAL)pDoc->GetHObject());
	
	//旋转角度
	int iRotateAngle=m_iRotateAngle;

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
		//SetScrollSizes(MM_TEXT, pDoc->GetDocSize());

		// 更新视图
		pDoc->UpdateAllViews(NULL);
		m_bPreviewed = TRUE;
	}
	else
	{
		//提示用户
		MessageBox(L"分配内存失败！", L"系统提示", MB_ICONINFORMATION | MB_OK);
	}
}


void DlgGeoRota::OnBnClickedImageres()
{
	// TODO: 在此添加控件通知处理程序代码
	// 恢复原始图像数据
	pDoc->OnImgrestore();

	// 设置脏标记
	pDoc->SetModifiedFlag(FALSE);

	// 更新视图
	pDoc->UpdateAllViews(NULL);
}
