
// MFCTest1View.h: CMFCTest1View 类的接口
//

#pragma once


class CMFCTest1View : public CScrollView
{
protected: // 仅从序列化创建
	CMFCTest1View() noexcept;
	DECLARE_DYNCREATE(CMFCTest1View)

// 特性
public:
	CMFCTest1Doc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CMFCTest1View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDispimginfo();
	afx_msg void OnChangeimglight();
	afx_msg void OnViewHistyogram();
	afx_msg void On24colto8col();
	afx_msg void On24colto8gray();
	afx_msg void OnCvtgray();
	afx_msg void OnCvthalftone();
	afx_msg void OnCvtbinary();
	afx_msg void OnPointinvert();
	afx_msg void OnTranReverseV();
	afx_msg void OnTranV();
	afx_msg void OnTranReverseL();
	afx_msg void OnTranL();
	afx_msg void OnLinerpara();
	afx_msg void OnPointStre();
	afx_msg void OnBitplaneslicing();
	afx_msg void OnLogtran();
	afx_msg void OnGammatran();
	afx_msg void OnEnhasmooth();
	afx_msg void OnEnhaMidianf();
	afx_msg void OnNoise();
	afx_msg void OnEnhaSharp();
	afx_msg void OnMaxfilter();
	afx_msg void OnMinfilter();
	afx_msg void OnMidpointfilter();
	afx_msg void OnAdapmedfilter();
	afx_msg void OnEdgeRobert();
	afx_msg void OnEdgeSobel();
	afx_msg void OnRestoreSaltnoise();
	afx_msg void OnMorphologyMainmenu();
	afx_msg void OnPointThre();
	afx_msg void OnPointwind();
	afx_msg void OnPointequa();
	afx_msg void OnFilter();
	afx_msg void OnGeomTran();
	afx_msg
		

	void OnGeomRota();
	afx_msg void OnGeomZoom();
	afx_msg void OnGeomMirh();
	afx_msg void OnGeomMirv();
	afx_msg void OnGeomTrpos();
	afx_msg void OnMosaic();
	afx_msg void OnOilpaint();
	afx_msg void OnRetrostyle();
	afx_msg void OnPencildraw();
	afx_msg void OnApplication();
	afx_msg void OnCanny();
	afx_msg void OnUsm();
};

#ifndef _DEBUG  // MFCTest1View.cpp 中的调试版本
inline CMFCTest1Doc* CMFCTest1View::GetDocument() const
   { return reinterpret_cast<CMFCTest1Doc*>(m_pDocument); }
#endif

