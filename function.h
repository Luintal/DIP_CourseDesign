// function.h: interface for the function class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FUNCTION_H__6E194843_FEB3_491F_8062_765AA3465CBC__INCLUDED_)
#define AFX_FUNCTION_H__6E194843_FEB3_491F_8062_765AA3465CBC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "Dib.h"
#include <math.h>
// 常数π
#define pi 3.1415926535
#define WIDTHBYTES(bits)    (((bits) + 31) / 32 * 4)
#include <direct.h>
#include <complex>
using namespace std;
#define PI 3.14159265358979323846

//#endif // !defined(AFX_FUNCTION_H__6E194843_FEB3_491F_8062_765AA3465CBC__INCLUDED_)

typedef struct{
	int Value;
	int Dist;
	int AngleNumber;
}	MaxValue;


struct CplexNum
{
	double re;
	double im;
};

/////////////////////////////////////////////////////////
//用于复数运算
CplexNum Add(CplexNum c1,CplexNum c2)
{
	CplexNum c;
	c.re=c1.re+c2.re;
	c.im=c1.im+c2.im;
	return c;
}
CplexNum Sub(CplexNum c1,CplexNum c2)
{
	CplexNum c;
	c.re=c1.re-c2.re;
	c.im=c1.im-c2.im;
	return c;
}
CplexNum Mul(CplexNum c1,CplexNum c2)
{
	CplexNum c;
	c.re=c1.re*c2.re-c1.im*c2.im;
	c.im=c1.re*c2.im+c2.re*c1.im;
	return c;
}
////////////////////////////////////////////////////////
/*************************************************************************
 * 函数名称：AngleToRadian(int angle)
 * 函数参数:
 *   int angle
 * 函数类型:float      
 * 函数功能:用来角度到弧度的转换
 ************************************************************************/

double AngleToRadian(int angle)
{
	return ((angle)*pi/180.0);
}


/*************************************************************************
 * 函数名称：ThreeCrossMat(double *pMatrix, int rank, double *pQMatrix, 
					    double *pMainCross, double *pHypoCross)
 * 函数参数:
 *   double  *pMatrix ，指向矩阵的指针
 *   int     rank  ，矩阵阶数
 *   double	 *pQMatrix  ， householder变换后的的矩阵的指针
 *   double  *pMainCross ，对称三角阵中的主对角元素的指针
 *   double  *pHypoCross ， 对称三角阵中的次对角元素的指针
 * 函数类型:BOOL
 *函数功能:将n阶实对称矩阵化为对称三角阵
************************************************************************/

BOOL  ThreeCrossMat(double *pMatrix, int rank, double *pQMatrix, 
					    double *pMainCross, double *pHypoCross)
{	
	int i, j, k, u;//变量声明
    double h, f, g, h2;   
	
	for(i = 0; i <= rank-1; i++)// 将矩阵pQMatrix初始化
	{
		for(j = 0; j <= rank-1; j++)
		{
			u = i*rank + j; 
			pQMatrix[u] = pMatrix[u];
		}
	}
    for (i = rank-1; i >= 1; i--)
    {
		h = 0.0;
        if (i > 1)
          for (k = 0; k <= i-1; k++)
          {
			  u = i*rank + k; 
			  h = h + pQMatrix[u]*pQMatrix[u];
		  }      
		
		if (h + 1.0 == 1.0)// 如果一行全部为零
        {
			pHypoCross[i] = 0.0;
            if (i == 1) 
			{
				pHypoCross[i] = pQMatrix[i*rank+i-1];
			}
            pMainCross[i] = 0.0;
        }        		
		else
        {// 否则求正交矩阵的值
			
			pHypoCross[i] = sqrt(h);// 求次对角元素的值            			
			u = i*rank + i - 1;
            if (pQMatrix[u] > 0.0) // 判断i行i-1列元素是不是大于零
			{
				pHypoCross[i] = -pHypoCross[i];
			}            
			h = h - pQMatrix[u]*pHypoCross[i];
            pQMatrix[u] = pQMatrix[u] - pHypoCross[i];
            f = 0.0;            			
		    for (j = 0; j <= i-1; j++)// householder变换
            { 
				pQMatrix[j*rank+i] = pQMatrix[i*rank+j] / h;
                g = 0.0;
                
				for (k = 0; k <= j; k++)
				{
					g = g + pQMatrix[j*rank+k]*pQMatrix[i*rank+k];
				}                
				if (j+1 <= i-1)
                  for (k = j+1; k <= i-1; k++)
				  {
					  g = g + pQMatrix[k*rank+j]*pQMatrix[i*rank+k];
				  }                
				pHypoCross[j] = g / h;
                f = f + g*pQMatrix[j*rank+i];
            }
            
			h2 = f / (h + h);            			
			for (j = 0; j <= i-1; j++)// 求正交矩阵的值
            {
				f = pQMatrix[i*rank + j];
                g = pHypoCross[j] - h2*f;
                pHypoCross[j] = g;
                
				for (k = 0; k <= j; k++)
                {
					u = j*rank + k;
                    pQMatrix[u] = pQMatrix[u] - f*pHypoCross[k] - g*pQMatrix[i*rank + k];
                }
            }
            pMainCross[i] = h;
         }
    }
    
    for (i = 0; i <= rank-2; i++) // 赋零值
	{
		pHypoCross[i] = pHypoCross[i + 1];
	}
    pHypoCross[rank - 1] = 0.0;
    pMainCross[0]        = 0.0;    
	for (i = 0; i <= rank-1; i++)
    { // 主对角元素的计算		
		if ((pMainCross[i] != 0.0) && (i-1 >= 0))
			for (j = 0; j <= i-1; j++)
			{
				g = 0.0;
				for (k = 0; k <= i-1; k++)
				{g = g + pQMatrix[i*rank + k]*pQMatrix[k*rank + j];
				}
				for (k = 0; k <= i-1; k++)
				{ 
					u = k*rank + j;
					pQMatrix[u] = pQMatrix[u] - g*pQMatrix[k*rank + i];
				}
			}       
		u = i*rank + i;// 存储主对角线的元素
        pMainCross[i] = pQMatrix[u]; 
		pQMatrix[u]   = 1.0;       		
		if (i-1 >= 0)// 将三对角外所有的元素赋零值
          for (j = 0; j <= i-1; j++)
          { 
			  pQMatrix[i*rank + j] = 0.0; 
			  pQMatrix[j*rank+i]   = 0.0;
		  }
    }    
	return(TRUE);// 返回
}


/*************************************************************************
 *
 * 函数名称：EigenvalueVector(int rank, double *pMainCross, double *pHypoCross, 
				  double *pMatrix, double Precision, int MaxT)
 * 函数参数:
 *   int     rank ，矩阵A的阶数
 *   double	 *pMainCross  ，对称三角阵中的主对角元素的指针，返回时存放A的特征值
 *   double  *pHypoCross  ，对称三角阵中的次对角元素的指针
 *	 double  *pMatrix  ，对称矩阵A的特征向量的指针
 *   double Precision ，控制精度
 *   int MaxT  ， 最大迭代次数
 * 函数类型:BOOL 
 * 函数功能:用计算实对称三角矩阵的全部特征值以及相应的特征向量
 ************************************************************************/
BOOL EigenvalueVector(int rank, double *pMainCross, double *pHypoCross, 
				  double *pMatrix, double Precision, int MaxT)
{
	
	int i, j, k, m, it, u, v;// 变量声明
    double d, f, h, g, p, r, e, s;
	
    pHypoCross[rank - 1] = 0.0; // 初始化
	d = 0.0; 
	f = 0.0;
    
	for(j = 0; j <= rank-1; j++)
    {							//  迭代精度的控制		
		it = 0;
        h = Precision * (fabs(pMainCross[j]) + fabs(pHypoCross[j]));
        if(h > d) 
		{
			d = h;
		}
        m = j;
        
		while((m <= rank-1) && (fabs(pHypoCross[m]) > d)) 
		{
			m = m + 1;    
		}
		if(m != j)
        {
								// 迭代求矩阵A的特征值和特征向量
			do
            {
								// 超过迭代次数，迭代失败
				if(it == MaxT)
				{
					return(FALSE);
				}
                it = it + 1;
                g = pMainCross[j];
                p = (pMainCross[j + 1] - g) / (2.0 * pHypoCross[j]);
                r = sqrt(p*p + 1.0);                
								// 如果p大于0
				if (p >= 0.0)
				{
					pMainCross[j] = pHypoCross[j]/(p + r);
				}
                else
				{
					pMainCross[j] = pHypoCross[j]/(p - r); 
				}
				h = g - pMainCross[j];                
								//  计算主对角线的元素
				for (i = j + 1; i <= rank - 1; i++)
				{
					pMainCross[i] = pMainCross[i] - h;  
				}
								// 赋值
				f = f + h;
				p = pMainCross[m];
				e = 1.0; s = 0.0;
                
				for(i = m - 1; i >= j; i--)
                {
					g = e * pHypoCross[i];
					h = e * p;
                    
								//  主对角线元素的绝对值是否大于次对角线元素的
					if(fabs(p) >= fabs(pHypoCross[i]))
                    {
						e = pHypoCross[i] / p;
						r = sqrt(e*e + 1.0);
                        pHypoCross[i + 1] = s*p*r; 
						s = e / r;  e = 1.0 / r;
                     }
                    else
					{
						e = p / pHypoCross[i]; 
						r = sqrt(e*e + 1.0);
                        pHypoCross[i+1] = s * pHypoCross[i] * r;
                        s = 1.0 / r; e = e / r;
                      }                   
					p = e*pMainCross[i] - s*g;
                    pMainCross[i + 1] = h + s*(e*g + s*pMainCross[i]);
                    
								// 重新存储特征向量
					for(k = 0; k <= rank - 1; k++)
                    {
						u = k*rank + i + 1; v = u - 1;
                        h = pMatrix[u]; 
						pMatrix[u] = s*pMatrix[v] + e*h;
                        pMatrix[v] = e*pMatrix[v] - s*h;
                    }
                
				}               
								// 将主对角线和次对角线元素重新赋值
				pHypoCross[j] = s * p; 
				pMainCross[j] = e * p;
            
			}
            while (fabs(pHypoCross[j]) > d);
        }

        pMainCross[j] = pMainCross[j] + f;
    }   	
	for (i = 0; i <= rank-1; i++)
    {// 返回A的特征值
		k = i; p = pMainCross[i];        		
		if(i+1 <= rank-1)
        {// 将A特征值赋给p
			j = i + 1;
            while((j <= rank-1) && (pMainCross[j] <= p))
            { k = j; 
			  p = pMainCross[j]; 
			  j = j+1;
			}
        }        		
		if (k != i)
        {// 存储A的特征值和特征向量
			pMainCross[k] = pMainCross[i];
			pMainCross[i] = p;
            for(j = 0; j <= rank-1; j++)
            {
				u = j*rank + i; 
				v = j*rank + k;
                p = pMatrix[u]; 
				pMatrix[u] = pMatrix[v];
				pMatrix[v] = p;
            }
        }
    }  
  return(TRUE);// 返回
}


/*************************************************************************
 * 函数名称：
 *   Transpose(LPSTR lpSrcDib,LPSTR lpDibBits,long	lWidth,long	lHeight,
				   long lLineBytes,long lDstLineBytes)
 * 函数参数:
 *   LPSTR	lpSrcDib，指向源DIB的指针
     LPSTR	lpSrcStartBits,指向DIB起始像素的指针
	 long	lWidth，DIB图象的宽度
	 long	lHeight，DIB图象的高度
	 long	lLineBytes，DIB图象的行字节数，为4的倍数
	 long	lDstLineBytes，临时DIB图象的行字节数，为4的倍数
 * 函数类型:BOOL        
 * 函数功能:该函数用来转置DIB图象
 ************************************************************************/

BOOL  Transpose(LPSTR lpSrcDib,LPSTR lpSrcStartBits,long lWidth,long lHeight,
				   long lLineBytes,long lDstLineBytes)
{
	long i;                 //行循环变量
	long j;                 //列循环变量
	LPSTR	lpSrcDIBBits;	//指向源像素的指针
	LPSTR	lpDstDIBBits;	//指向临时图象对应像素的指针
	LPSTR	lpDstStartBits;	//指向临时图象对应像素的指针 		
	HLOCAL	hDstDIBBits;	//临时图象句柄
	LPBITMAPINFOHEADER lpbmi;							  // 指向BITMAPINFOHEADER结构的指针
	lpbmi = (LPBITMAPINFOHEADER)lpSrcDib;
	hDstDIBBits= LocalAlloc(LHND, lWidth * lDstLineBytes);// 分配临时内存
	if (hDstDIBBits== NULL)								 // 判断是否内存分配
	{		
		return FALSE;									// 分配内存失败
	}	
	lpDstStartBits= (char * )LocalLock(hDstDIBBits);	// 锁定内存		
	for(i = 0; i < lHeight; i++)						// 针对图象每行进行操作
	{		
		for(j = 0; j < lWidth; j++)						// 针对每行图象每列进行操作
		{						
			lpSrcDIBBits= (char *)lpSrcStartBits + lLineBytes * (lHeight - 1 - i) + j;// 指向源DIB第i行，第j个像素的指针
			lpDstDIBBits= (char *)lpDstStartBits + lDstLineBytes * (lWidth - 1 - j) + i;// 指向转置DIB第j行，第i个像素的指针			
			*(lpDstDIBBits)= *(lpSrcDIBBits);			// 复制像素			
		}		
	}	
	memcpy(lpSrcStartBits, lpDstStartBits, static_cast<size_t>(lWidth) * lDstLineBytes);// 复制转置后的图象
	lpbmi->biWidth = lHeight;		
	lpbmi->biHeight = lWidth;
	
	LocalUnlock(hDstDIBBits);							// 释放内存
	LocalFree(hDstDIBBits);								
	return TRUE;										// 返回
}

/*************************************************************************
 * 函数名称：Mirror(LPSTR lpSrcStartBits, long lWidth, long lHeight,long lLineBytes)
 * 函数参数:
     LPSTR	lpSrcStartBits,指向DIB起始像素的指针
	 long	lWidth，DIB图象的宽度
	 long	lHeight，DIB图象的高度
	 long	lLineBytes，DIB图象的行字节数，为4的倍数
 * 函数类型:BOOL        
 * 函数功能:该函数用来镜像DIB图象，本程序只实现了水平镜像，垂直镜像的原理书中也谈到。 很容易实现           
 ************************************************************************/

BOOL  Mirror(LPSTR lpSrcStartBits, long lWidth, long lHeight,long lLineBytes)
{	
	long i;                 //行循环变量
	long j;                 //列循环变量
	LPSTR	lpSrcDIBBits;	//指向源像素的指针
	LPSTR	lpDstDIBBits;	//指向临时图象对应像素的指针 		
	HLOCAL	hDstDIBBits;	//临时图象句柄
	LPSTR	lpBits;	// 指向中间像素的指针，当复制图象时，提供临时的像素内存空间
	hDstDIBBits= LocalAlloc(LHND, lLineBytes);// 分配临时内存保存行图象
	if (hDstDIBBits == NULL)		
	{		
		return FALSE;									// 分配内存失败
	}		
	lpDstDIBBits= (char * )LocalLock(hDstDIBBits);// 锁定				
	for(i = 0; i < lHeight; i++)// 水平镜像，针对图象每行进行操作
	{			
			for(j = 0; j < lWidth / 2; j++)// 针对每行图象左半部分进行操作
			{							
				lpSrcDIBBits= (char *)lpSrcStartBits + lLineBytes * i + j;// 指向倒数第i行，第j个像素的指针								
				lpBits= (char *)lpSrcStartBits + lLineBytes * (i + 1) - j;// 指向倒数第i+1行，倒数第j个像素的指针								
				*lpDstDIBBits=*lpBits;//保存中间像素								
				*lpBits = *lpSrcDIBBits;// 将倒数第i行，第j个像素复制到倒数第i行，倒数第j个像素								
				*lpSrcDIBBits=*lpDstDIBBits;// 将倒数第i行，倒数第j个像素复制到倒数第i行，第j个像素
			}			
	}		
	LocalUnlock(hDstDIBBits);// 释放内存
	LocalFree(hDstDIBBits);
	return TRUE;
}
/*************************************************************************
 * 函数名称：GrayEqualize(LPSTR lpSrcStartBits, long lWidth, long lHeight,long	lLineBytes)
 * 函数参数:
     LPSTR	lpSrcStartBits,指向DIB起始像素的指针
	 long	lWidth，DIB图象的宽度
	 long	lHeight，DIB图象的高度
	 long	lLineBytes，DIB图象的行字节数，为4的倍数
 * 函数类型:BOOL        
 * 函数功能:该函数用来进行直方图均衡
 ************************************************************************/

BOOL  GrayEqualize(LPSTR lpSrcStartBits, long lWidth, long lHeight,long	lLineBytes)
{			
	long i;                 //行循环变量
	long j;                 //列循环变量
	unsigned char*	lpSrcUnChr;	//指向像素的指针

	BYTE	bGrayMap[256];// 灰度映射		
	long	lGrayNum[256];// 灰度映射		
	for (i = 0; i < 256; i ++)// 置0
	{		
		lGrayNum[i] = 0;
	}		
	for (i = 0; i < lHeight; i ++)// 各灰度值计数
	{
		for (j = 0; j < lWidth; j ++)
		{
			lpSrcUnChr=(unsigned char*)lpSrcStartBits + lLineBytes * i + j;						
			lGrayNum[*(lpSrcUnChr)]++;// 加1
		}
	}		
	for (i = 0; i < 256; i++)// 计算灰度映射表
	{		
		long    varLong;		//临时变量
		varLong = 0;// 初始为0		
		for (j = 0; j <= i ; j++)
		{
			varLong += lGrayNum[j];
		}				
		bGrayMap[i] = (BYTE) (varLong * 255 / lHeight / lWidth);// 计算对应的新灰度值
	}		
	for(i = 0; i < lHeight; i++)// 行
	{		
		for(j = 0; j < lWidth; j++)// 列
		{
			// 指向DIB第i行，第j个像素的指针(unsigned char*)
			lpSrcUnChr= (unsigned char*)lpSrcStartBits + lLineBytes * (lHeight - 1 - i) + j;						
			*lpSrcUnChr= bGrayMap[*lpSrcUnChr];// 计算新的灰度值
		}
	}
	return TRUE;	
}
/*************************************************************************
 * 函数名称：LineTranslation(LPSTR lpSrcStartBits, long lWidth, long lHeight, float fSlope, float fIntercept,long lLineBytes)
 * 函数参数:
 *   LPSTR lpSrcStartBits，指向源DIB图象起始像素的指针
 *   long  lWidth，DIB图象宽度
 *   long  lHeight，DIB图象高度
 *   float fSlope，斜率
 *   float fIntercept，截距
 *   LONGlLineBytes，DIB图象的行字节数，为4的倍数
 * 函数类型:BOOL        
 * 函数功能:该函数用来对图象进行灰度的线性变换操作
 ************************************************************************/
BOOL  LineTranslation(LPSTR lpSrcStartBits, long lWidth, long lHeight, float fSlope, float fIntercept,long lLineBytes)
{		
	long i;                 //行循环变量
	long j;                 //列循环变量
	float varFloat;        //浮点参数变量
	unsigned char*	lpSrcUnChr;	//指向像素的指针	
	for(i=0;i<lHeight;i++)// 行
	{		
		for(j=0; j<lWidth; j++)// 列
		{			
			lpSrcUnChr=(unsigned char*)lpSrcStartBits+lLineBytes*(lHeight-1-i)+j;// 指向DIB第i行，第j个像素的指针						
			varFloat=fSlope*(*lpSrcUnChr)+fIntercept;// 线性变换						
			if (varFloat>255)// 超出范围直接赋值为255
			{				
				*lpSrcUnChr=255;
			}
			else if(varFloat<0)
			{				
				*lpSrcUnChr=0;// 直接赋值为0
			}
			else
			{				
				*lpSrcUnChr=(unsigned char)(varFloat+0.5);// 近似
			}
		}
	}
	return TRUE;
}
/*************************************************************************
 * 函数名称：ThresholdTranslation(LPSTR lpSrcStartBits, long lWidth, long lHeight, BYTE bThreshold,long lLineBytes)
 * 函数参数:
     LPSTR	lpSrcStartBits,指向DIB起始像素的指针
	 long	lWidth，DIB图象的宽度
	 long	lHeight，DIB图象的高度
	 long	lLineBytes，DIB图象的行字节数，为4的倍数
 * 函数类型:BOOL        
 * 函数功能:该函数用来对图象进行阈值变换 
 ************************************************************************/

BOOL  ThresholdTranslation(LPSTR lpSrcStartBits, long lWidth, long lHeight, 
						   BYTE bThreshold,long lLineBytes)
{			
	long i;                 //行循环变量
	long j;                 //列循环变量
	unsigned char*	lpSrcUnChr;	//指向像素的指针
	for(i = 0; i < lHeight; i++)// 行
	{		
		for(j = 0; j < lWidth; j++)// 列
		{			
			lpSrcUnChr= (unsigned char*)lpSrcStartBits + lLineBytes * (lHeight - 1 - i) + j;// 指向DIB第i行，第j个像素的指针			
			if ((*lpSrcUnChr) <bThreshold)// 小于阈值直接赋值为0
			{
				*lpSrcUnChr= 0;
			}
			else
			{				
				*lpSrcUnChr= 255;// 赋值为255
			}
		}
	}
	return TRUE;
}
/*************************************************************************
 * 函数名称：LogTranslation(LPSTR lpSrcStartBits, long lWidth, long lHeight, long lLineBytes)
 * 函数参数:
     LPSTR	lpSrcStartBits,指向DIB起始像素的指针
	 long	lWidth，DIB图象的宽度
	 long	lHeight，DIB图象的高度
	 long	lLineBytes，DIB图象的行字节数，为4的倍数
 * 函数类型:BOOL        
 * 函数功能:该函数用来对图象进行对数变换 
 ************************************************************************/

BOOL  LogTranslation(LPSTR lpSrcStartBits, long lWidth, long lHeight, long lLineBytes)
{			
	long i;                 //行循环变量
	long j;                 //列循环变量
	unsigned char*	lpSrcUnChr;	//指向像素的指针
	for(i = 0; i < lHeight; i++)// 行
	{		
		for(j = 0; j < lWidth; j++)// 列
		{	
			lpSrcUnChr= (unsigned char*)lpSrcStartBits + lLineBytes * (lHeight - 1 - i) + j;// 指向DIB第i行，第j个像素的指针
			//*lpSrcUnChr=50*(unsigned char)log((*lpSrcUnChr+1));
			*lpSrcUnChr = 255 * (unsigned char)log((*lpSrcUnChr + 1))/log(255);
		}
	}
	return TRUE;
}

/*************************************************************************
 * 函数名称：WindowTranslation(LPSTR lpSrcStartBits, long lWidth, long lHeight, BYTE bLower, BYTE bUpper,long	lLineBytes)
 * 函数参数:
 *   LPSTR lpSrcStartBits，指向源DIB图象起始像素的指针
 *   long  lWidth，DIB图象宽度
 *   long  lHeight，DIB图象高度
 *   BYTE	bLower，窗口变换下限
 *   BYTE	bUpper，窗口变换上限
 *   LONGl	LineBytes，DIB图象的行字节数，为4的倍数
 * 函数类型:BOOL        
 * 函数功能:该函数用来对图象进行窗口变换
 ************************************************************************/

BOOL  WindowTranslation(LPSTR lpSrcStartBits, long lWidth, long lHeight, BYTE bLower, BYTE bUpper,long	lLineBytes)
{			
	long i;                 //行循环变量
	long j;                 //列循环变量
	unsigned char*	lpSrcUnChr;	//指向像素的指针
	for(i = 0; i < lHeight; i++)// 行
	{		
		for(j = 0; j < lWidth; j++)// 列
		{			
			lpSrcUnChr= (unsigned char*)lpSrcStartBits + lLineBytes * (lHeight - 1 - i) + j;// 指向DIB第i行，第j个像素的指针						
			if ((*lpSrcUnChr) < bLower)// 超出范围直接赋值
			{				
				*lpSrcUnChr= 0;
			}
			else if ((*lpSrcUnChr) > bUpper)
			{				
				*lpSrcUnChr= 255;// 直接赋值为255
			}
		}
	}	
	return TRUE;
}

/*************************************************************************
 * 函数名称：GrayStretch(LPSTR lpSrcStartBits, long lWidth, long lHeight, BYTE bPointX1, BYTE bPointY1, BYTE bPointX2, BYTE bPointY2,long lLineBytes)
 * 函数参数:
 *   LPSTR lpSrcStartBits，指向源DIB图象起始像素的指针
 *   long  lWidth，DIB图象宽度
 *   long  lHeight，DIB图象高度
 *	 BYTE bPointX1,第一个点的X坐标
 *   BYTE bPointY1,第一个点的Y坐标
 *   BYTE bPointX2,第二个点的X坐标
 *   BYTE bPointY2,第二个点的Y坐标
 *   LONGl	LineBytes，DIB图象的行字节数，为4的倍数
 * 函数类型:BOOL        
 * 函数功能:该函数用来对图象进行灰度拉伸
 ************************************************************************/

BOOL  GrayStretch(LPSTR lpSrcStartBits, long lWidth, long lHeight, BYTE bPointX1, BYTE bPointY1, BYTE bPointX2, BYTE bPointY2,long lLineBytes)
{		
	long i;                 //行循环变量
	long j;                 //列循环变量
	unsigned char*	lpSrcUnChr;	//指向像素的指针
	BYTE	bMap[256];// 灰度映射			
	for (i = 0; i <= bPointX1; i++)// 计算灰度映射
	{		
		if (bPointX1 > 0)// 判断bPointX1是否大于0			
		{
			bMap[i] = (BYTE) bPointY1 * i / bPointX1;// 变换
		}
		else
		{			
			bMap[i] = 0;// 赋值为0
		}
	}
	for (; i <= bPointX2; i++)
	{		
		if (bPointX2 != bPointX1)// 判断bPointX1是否等于bPointX2			
		{
			bMap[i] = bPointY1 + (BYTE) ((bPointY2 - bPointY1) * (i - bPointX1) / (bPointX2 - bPointX1));// 变换
		}
		else
		{			
			bMap[i] = bPointY1;// 赋值为bPointY1
		}
	}
	for (; i < 256; i++)
	{		
		if (bPointX2 != 255)// 判断bPointX2是否等于255			
		{
			bMap[i] = bPointY2 + (BYTE) ((255 - bPointY2) * (i - bPointX2) / (255 - bPointX2));//变换
		}
		else
		{			
			bMap[i] = 255;// 赋值为255
		}
	}		
	for(i = 0; i < lHeight; i++)// 行
	{		
		for(j = 0; j < lWidth; j++)// 列
		{			
			lpSrcUnChr= (unsigned char*)lpSrcStartBits + lLineBytes * (lHeight - 1 - i) + j;// 指向DIB第i行，第j个像素的指针						
			*lpSrcUnChr= bMap[*lpSrcUnChr];// 新灰度值
		}
	}
	return TRUE;
}
/*************************************************************************
 * 函数名称：Translation(LPSTR lpSrcStartBits, long lWidth, long lHeight, long lXOffset, 
							long lYOffset,long lLineBytes,long lDstLineBytes)
 * 函数参数:
 *   LPSTR	lpSrcStartBits，指向源DIB起始像素的指针
 * 	 long	lWidth，DIB图象的宽度
 * 	 long	lHeight，DIB图象的高度
 * 	 long	lXOffset,X方向偏移量
 * 	 long	lYOffset,Y方向偏移量
 * 	 long	lLineBytes，DIB图象的行字节数，为4的倍数
 * 	 long	lDstLineBytes，临时DIB图象的行字节数，为4的倍数
 * 函数类型:BOOL        
 * 函数功能:该函数用来平移DIB图象
 ************************************************************************/
BOOL  Translation(LPSTR lpSrcStartBits, long lWidth, long lHeight, 
				  long lXOffset, long lYOffset,long lLineBytes,long lDstLineBytes)					 
{	
	long i;                 //行循环变量
	long j;                 //列循环变量
	LPSTR	lpSrcDIBBits;	//指向源像素的指针
	LPSTR	lpDstDIBBits;	//指向临时图象对应像素的指针
	LPSTR	lpDstStartBits;	//指向临时图象对应像素的指针 		
	HLOCAL	hDstDIBBits;	//临时图象句柄

	hDstDIBBits= LocalAlloc(LHND, lWidth * lDstLineBytes);// 分配临时内存
	lpDstStartBits= (char * )LocalLock(hDstDIBBits);// 锁定内存	
	if (hDstDIBBits== NULL)// 判断是否内存分配		
		return FALSE;// 分配内存失败				
	for(i = 0; i < lHeight; i++)// 行
	{
			for(j = 0; j < lWidth; j++)	// 列
		{
				lpDstDIBBits=(char*)lpDstStartBits+lLineBytes*(lHeight-1-i)
				+j;// 指向新DIB第i行，第j个像素的指针												
			if( (j-lYOffset>= 0) && (j-lYOffset< lWidth) && // 像素在源DIB中的坐标j-lXOffset
				(i-lXOffset>= 0) && (i-lXOffset < lHeight))// 判断是否在源图范围内
			{
				lpSrcDIBBits=(char *)lpSrcStartBits+lLineBytes*(lHeight-1-
					(i-lXOffset))+(j-lYOffset);// 指向源DIB第i0行，第j0个像素的指针								
				*lpDstDIBBits= *lpSrcDIBBits;// 复制像素
			}
			else
			{				
				* ((unsigned char*)lpDstDIBBits) = 255;// 源图中没有的像素，赋为255
			}			
		}
	}
	memcpy(lpSrcStartBits, lpDstStartBits, lLineBytes * lHeight);// 复制图象		
	LocalUnlock(hDstDIBBits);// 释放内存
	LocalFree(hDstDIBBits);		
	return TRUE;
}

/*************************************************************************
 * 函数名称：Rotate(LPSTR lpSrcDib, LPSTR lpSrcStartBits,long lWidth, long lHeight,
				   long lLineBytes,	WORD palSize, long lDstWidth, 
				   long lDstHeight,long lDstLineBytes,float	fSina, float fCosa)
 * 函数参数:
 *   LPSTR lpSrcDib,指向源DIB的指针
 *   LPSTR lpSrcStartBits,指向源DIB的起始像素的指针
 *   long lWidth,源DIB图象宽度
 *   long lHeight,源DIB图象高度
 *	 long lLineBytes,源DIB图象字节宽度（4的倍数）
 *	 WORD palSize,源DIB图象调色板大小
 *	 long lDstWidth,目标图象宽度
 *	 long lDstHeight,目标DIB图象高度
 *	 long lDstLineBytes,目标DIB图象行字节数（4的倍数）
 *	 float	fSina,旋转角的余弦，说明：为了避免两次求取正余弦，这里作为两个函数参数来用
 *	 float fCosa,旋转角的正弦
 * 函数类型:HGLOBAL
 * 函数功能:用来旋转DIB图象
 ************************************************************************/
HGLOBAL  Rotate(LPSTR lpSrcDib, LPSTR lpSrcStartBits,long lWidth, long lHeight,
				   long lLineBytes,	WORD palSize, long lDstWidth, 
				   long lDstHeight,long lDstLineBytes,float	fSina, float fCosa)
{	
	float varFloat1;        //浮点参数变量1
	float varFloat2;        //浮点参数变量2
	LPSTR	lpDstDib;		//指向临时图象的指针
	
	long i;                 //行循环变量
	long j;                 //列循环变量
	long i1;                 //行循环变量
	long j1;                 //列循环变量
	LPSTR	lpSrcDIBBits;	//指向源像素的指针
	LPSTR	lpDstDIBBits;	//指向临时图象对应像素的指针
	LPSTR	lpDstStartBits;	//指向临时图象对应像素的指针 			

	LPBITMAPINFOHEADER lpbmi;// 指向BITMAPINFOHEADER结构的指针		
	varFloat1= (float) (-0.5 * (lDstWidth - 1) * fCosa - 0.5 * (lDstHeight - 1) * fSina// 将经常用到的两个常数事先求出，以便作为常数使用
		+ 0.5 * (lDstWidth  - 1));
	varFloat2= (float) ( 0.5 * (lDstWidth - 1) * fSina - 0.5 * (lDstHeight - 1) * fCosa
		+ 0.5 * (lDstHeight - 1));		
	HGLOBAL hDIB = (HGLOBAL) ::GlobalAlloc(GHND, lDstLineBytes * lDstHeight + *(LPDWORD)lpSrcDib +palSize);// 分配内存，以保存新DIB		
	if (hDIB == NULL)// 判断是否是有效的DIB对象
	{		
		return FALSE;// 不是，则返回
	}	
	lpDstDib=  (char * )::GlobalLock((HGLOBAL) hDIB);// 锁定内存		
	memcpy(lpDstDib,lpSrcDib, *(LPDWORD)lpSrcDib +palSize);// 复制DIB信息头和调色板			
	
	lpbmi = (LPBITMAPINFOHEADER)lpDstDib;// 获取指针	
	lpbmi->biHeight=lDstHeight;// 更新DIB中图象的高度和宽度
	lpbmi->biWidth =lDstWidth;

	lpDstStartBits=lpDstDib+ *(LPDWORD)lpDstDib
		+palSize;// 求像素起始位置,作用如同::FindDIBBits(gCo.lpSrcDib)，这里尝试使用了这种方法，以避免对全局函数的调用
	
	for(i = 0; i < lDstHeight; i++)// 行操作
	{		
		for(j = 0; j < lDstWidth; j++)// 列操作
		{			
			lpDstDIBBits= (char *)lpDstStartBits+ lDstLineBytes * (lDstHeight - 1 - i) + j;// 指向新DIB第i行，第j个像素的指针			
			i1= (long) (-((float) j) * fSina + ((float) i) * fCosa + varFloat2 + 0.5);// 计算该像素在源DIB中的坐标
			j1= (long) ( ((float) j) * fCosa + ((float) i) * fSina + varFloat1 + 0.5);						
			if( (j1>= 0) && (j1< lWidth) && (i1>= 0) && (i1< lHeight))
			{// 判断是否在源图内				
				lpSrcDIBBits= (char *)lpSrcStartBits+ lLineBytes * (lHeight - 1 -i1) + j1;// 指向源DIB第i0行，第j0个像素的指针								
				*lpDstDIBBits= *lpSrcDIBBits;// 复制像素
			}
			else
			{
				* ((unsigned char*)lpDstDIBBits) = 255;// 源图中不存在的像素，赋为255
			}			
		}		
	}
	return hDIB;
}

/*************************************************************************
 * 函数名称：Zoom(LPSTR lpSrcDib, LPSTR lpSrcStartBits,long lWidth, long lHeight,
				   long lLineBytes,	WORD palSize, long lDstWidth, 
				   long lDstHeight,long lDstLineBytes,float	fXZoomRatio, float fYZoomRatio)
 * 函数参数:
 *   LPSTR lpSrcDib,指向源DIB的指针
 *   LPSTR lpSrcStartBits,指向源DIB的起始像素的指针
 *   long lWidth,源DIB图象宽度
 *   long lHeight,源DIB图象高度
 *	 long lLineBytes,源DIB图象字节宽度（4的倍数）
 *	 WORD palSize,源DIB图象调色板大小
 *	 long lDstWidth,目标图象宽度
 *	 long lDstHeight,目标DIB图象高度
 *	 long lDstLineBytes,目标DIB图象行字节数（4的倍数）
 *	 float	fhorRatio,水平缩放比率
 *	 float fverRatio,垂直缩放比率
 * 函数类型:HGLOBAL
 * 函数功能:用来缩放DIB图象
 ************************************************************************/

HGLOBAL  Zoom(LPSTR lpSrcDib, LPSTR lpSrcStartBits,long lWidth, long lHeight,
				   long lLineBytes,	WORD palSize,long lDstWidth,long lDstLineBytes,long lDstHeight,
				   float fhorRatio,float fverRatio)
{			
	LPSTR	lpDstDib;		//指向临时图象的指针	
	long i;                 //行循环变量
	long j;                 //列循环变量
	long i1;                 //行循环变量
	long j1;                 //列循环变量
	LPSTR	lpSrcDIBBits;	//指向源像素的指针
	LPSTR	lpDstDIBBits;	//指向临时图象对应像素的指针
	LPSTR	lpDstStartBits;	//指向临时图象对应像素的指针 		
			
	LPBITMAPINFOHEADER lpbmi;// 指向BITMAPINFO结构的指针
		
	// 分配内存，以保存缩放后的DIB
	HGLOBAL hDIB = (HGLOBAL) ::GlobalAlloc(GHND, lDstLineBytes* lDstHeight + *(LPDWORD)lpSrcDib +palSize);	
	if (hDIB == NULL)// 判断是否是有效的DIB对象
	{		
		return FALSE;// 不是，则返回
	}		
	lpDstDib=  (char * )::GlobalLock((HGLOBAL) hDIB);// 锁定内存		
	memcpy(lpDstDib, lpSrcDib, *(LPDWORD)lpSrcDib +palSize);// 复制DIB信息头和调色板		
	
	lpDstStartBits=lpDstDib+ *(LPDWORD)lpDstDib// 找到新DIB像素起始位置
		+palSize;// 求像素起始位置,作用如同::FindDIBBits(lpSrcDib)，这里尝试使用了这种方法，以避免对全局函数的调用		
	lpbmi = (LPBITMAPINFOHEADER)lpDstDib;// 获取指针
		
	lpbmi->biWidth = lDstWidth;// 更新DIB中图象的高度和宽度
	lpbmi->biHeight =lDstHeight;	
	
	for(i = 0; i < lDstHeight; i++)// 行操作
	{		
		for(j = 0; j < lDstWidth; j++)// 列操作
		{
			// 指向新DIB第i行，第j个像素的指针
			lpDstDIBBits= (char *)lpDstStartBits + lDstLineBytes * (lDstHeight-1-i)+j;						
			i1= (long) (i / fverRatio + 0.5);// 计算该像素在源DIB中的坐标
			j1= (long) (j / fhorRatio + 0.5);			
			
			if( (j1>= 0) && (j1< lWidth) && (i1>= 0) && (i1< lHeight))
			{// 判断是否在源图内				
				lpSrcDIBBits= (char *)lpSrcStartBits+ lLineBytes * (lHeight - 1 -i1) + j1;// 指向源DIB第i行，第j个像素的指针								
				*lpDstDIBBits= *lpSrcDIBBits;// 复制像素
			}
			else
			{
				* ((unsigned char*)lpDstDIBBits) = 255;// 源图中不存在的像素，赋为255
			}				
		}		
	}
	return hDIB;
}

/*************************************************************************
 * 函数名称：FastFourierTran(CplexNum * pTd, CplexNum* pFd, int power)
 * 函数参数:
 *   CplexNum * pTd,指向时域数组的指针
 *   CplexNum * pFd,指向频域数组的指针
 *   int             power,2的幂数，即迭代次数
 * 函数类型:void 
 函数功能:用来实现快速付立叶变换
************************************************************************/
void  FastFourierTran(CplexNum * pTd, CplexNum * pFd, int power)
{	
	long i;                 //行循环变量
	long j;                 //列循环变量
 			
	long	dotCount;// 付立叶变换点数		
	int		k;// 循环变量		
	int		bfsize,p;// 中间变量		
	double	angle;// 角度	
	CplexNum *pWn,*temReg1,*temReg2,*temReg;	
	
	dotCount= 1 <<power;// 计算付立叶变换点数		
	pWn= new CplexNum[sizeof(CplexNum)*dotCount/ 2];// 分配运算所需存储器
	temReg1 = new CplexNum[sizeof(CplexNum)*dotCount];
	temReg2 = new CplexNum[sizeof(CplexNum)*dotCount];		
	for(i = 0; i < dotCount/ 2; i++)// 计算加权系数
	{
		angle = -i * pi* 2 / dotCount;
		pWn[i].re = cos(angle);
		pWn[i].im=sin(angle);
	}	
	memcpy(temReg1, pTd, sizeof(CplexNum)*dotCount);// 将时域点写入temReg1		
	for(k = 0; k < power; k++)// 采用蝶形算法进行快速付立叶变换
	{
		for(j = 0; j < 1 << k; j++)
		{
			bfsize = 1 << (power-k);
			for(i = 0; i < bfsize / 2; i++)
			{
				p = j * bfsize;
				temReg2[i+p]=Add(temReg1[i+p],temReg1[i+p+bfsize/2]);
				temReg2[i+p+bfsize/2]=Mul(Sub(temReg1[i+p],temReg1[i+p+bfsize/2]),
				pWn[i*(1<<k)]);
			}
		}
		temReg  = temReg1;
		temReg1 = temReg2;
		temReg2 = temReg;
	}		
	for(j = 0; j <dotCount; j++)// 重新排序
	{
		p = 0;
		for(i = 0; i <power; i++)
		{
			if (j&(1<<i))
			{
				p+=1<<(power-i-1);
			}
		}
		pFd[j]=temReg1[p];
	}		
	delete pWn;// 释放内存
	delete temReg1;
	delete temReg2;
}

/*************************************************************************
 *
 * 函数名称：InverFastFourierTran(CplexNum * pFd, CplexNum * pTd, int power)
 * 函数参数:
 *   CplexNum  * pFd，指向频域值的指针
 *   CplexNum * pTd，指向时域值的指针
 *   int power	，2的幂数
 *函数类型:void
 *函数功能:用来实现快速付立叶反变换
 ************************************************************************/
void  InverFastFourierTran(CplexNum * pFd, CplexNum * pTd, int power)
{	
	LONG	dotCount;			// 付立叶变换点数	
	int		i;				// 循环变量
	CplexNum *pX;		
	dotCount= 1 << power;		// 计算付立叶变换点数		
	pX = new CplexNum[sizeof(CplexNum)*dotCount];// 分配运算所需存储器		
	memcpy(pX, pFd, sizeof(CplexNum)*dotCount);// 将频域点写入X		
	for(i = 0; i <dotCount; i++)// 求共轭
	{
		pX[i].re= pX[i].re;
		pX[i].im=-pX[i].im;
	}	
	FastFourierTran(pX, pTd, power);// 调用快速付立叶变换		
	for(i = 0; i <dotCount; i++)// 求时域点的共轭
	{
		pTd[i].re =pTd[i].re/dotCount;
		pTd[i].im=-pTd[i].im/dotCount;

	}		
	delete pX;				// 释放内存
}

/*************************************************************************
 * 函数名称：Fourier(CplexNum * pTd, int lWidth, int lHeight, CplexNum * pFd)
 * 函数参数:
 *   CplexNum * pTd，指向时域值的指针
 *   int    lWidth，图象宽度
 *   int    lHeight，图象高度
 *   CplexNum * pFd	，指向频域值的指针
 *
 * 函数类型:void
 * 函数功能:二维快速傅立叶变换
 *************************************************************************/
void  Fourier(CplexNum * pTd, int lWidth, int lHeight, CplexNum * pFd)
{
	
	// 循环控制变量
	int	j;
	int	i;
	// 进行傅立叶变换的宽度和高度，（2的整数次幂）
	// 图象的宽度和高度不一定为2的整数次幂
	int		wid=1;
	int 	hei=1;
	int		widpor=0,heiPor=0;//2的幂数

	while(wid * 2 <= lWidth)// 计算进行付立叶变换的宽度和高度（2的整数次方）
	{
		wid *= 2;
		widpor++;
	}	
	while(hei * 2 <= lHeight)
	{
		hei *= 2;
		heiPor++;
	}	
	
	for(i = 0; i < hei; i++)
	{
		// x方向进行快速傅立叶变换
		FastFourierTran(&pTd[wid * i], &pFd[wid * i], widpor);
	}
	
	// pFd中目前存储了pTd经过行变换的结果
	// 为了直接利用FastFourierTran，需要把pFd的二维数据转置，再一次利用FastFourierTran进行
	// 傅立叶行变换（实际上相当于对列进行傅立叶变换）
	for(i = 0; i < hei; i++)
	{
		for(j = 0; j < wid; j++)
		{
			pTd[hei * j + i] = pFd[wid * i + j];
		}
	}
	
	for(j = 0; j < wid; j++)
	{
		// 对x方向进行快速傅立叶变换，实际上相当于对原来的图象数据进行列方向的
		// 傅立叶变换
		FastFourierTran(&pTd[j * hei], &pFd[j * hei], heiPor);
	}

	// pFd中目前存储了pTd经过二维傅立叶变换的结果，但是为了方便列方向
	// 的傅立叶变换，对其进行了转置，现在把结果转置回来
	for(i = 0; i < hei; i++)
	{
		for(j = 0; j < wid; j++)
		{
			pTd[wid * i + j] = pFd[hei * j + i];
		}
	}

	memcpy(pTd, pFd, sizeof(CplexNum) * hei * wid );
}
/*************************************************************************
 * 函数名称：InverseFourier(CplexNum * pFd, CplexNum * pTd, int lWidth, int lHeight)
 * 函数参数:
 *   CplexNum * pTd，指向时域值的指针
 *   CplexNum * pFd	，指向频域值的指针
 *   int    lWidth，图象宽度
 *   int    lHeight，图象高度
 * 函数类型:void
 * 函数功能:二维快速傅立叶反变换
 *************************************************************************/
void  InverseFourier(CplexNum * pFd, CplexNum * pTd, int lWidth, int lHeight)
{
	// 循环控制变量
	int	j;
	int	i;
	// 进行傅立叶变换的宽度和高度，（2的整数次幂）
	// 图象的宽度和高度不一定为2的整数次幂
	int		wid=1;
	int 	hei=1;
	int		widpor=0,heiPor=0;//2的幂数

	while(wid * 2 <= lWidth)// 计算进行付立叶变换的宽度和高度（2的整数次方）
	{
		wid *= 2;
		widpor++;
	}	
	while(hei * 2 <= lHeight)
	{
		hei *= 2;
		heiPor++;
	}		
	// 分配工作需要的内存空间
	CplexNum *pCWork= new CplexNum[sizeof(CplexNum)*wid * hei];

	//临时变量
	CplexNum *pCTmp ;
	
	// 为了利用傅立叶正变换,可以把傅立叶频域的数据取共轭
	// 然后直接利用正变换，输出结果就是傅立叶反变换结果的共轭
	for(i = 0; i < hei; i++)
	{
		for(j = 0; j < wid; j++)
		{
			pCTmp = &pFd[wid * i + j] ;
			pCWork[wid * i + j].re=pCTmp->re;
			pCWork[wid * i + j].im=-pCTmp->im;
			//= complex<double>( pCTmp->real() , -pCTmp->imag() );
		}
	}

	// 调用傅立叶正变换
	Fourier(pCWork, lWidth, lHeight, pTd) ;
	
	// 求时域点的共轭，求得最终结果
	// 根据傅立叶变换原理，利用这样的方法求得的结果和实际的时域数据
	// 相差一个系数
	for(i = 0; i < hei; i++)
	{
		for(j = 0; j < wid; j++)
		{
			pCTmp = &pTd[wid * i + j];
			pTd[wid * i + j].re=pCTmp->re/(wid*hei);
			pTd[wid * i + j].im=-pCTmp->im/(wid*hei);			

		}
	}
	delete pCWork ;
}

/*************************************************************************
 * 函数名称：DisFCosTran(double *pTd, double *pFd, int power)
 * 函数参数:
 *   double * pTd,指向时域值的指针
 *   double * pFd,指向频域值的指针
 *   int    power,2的幂数
 *
 * 函数类型:void
 * 函数功能: 用来实现快速离散余弦变换
 ************************************************************************/
void  DisFCosTran(double *pTd, double *pFd, int power)
{	
	long i;                 //行循环变量				
	long	dotCount;// 离散余弦变换点数			
	double	dTemp;// 临时变量	
	CplexNum *temReg;		
	dotCount = 1<<power;// 计算离散余弦变换点数		
	temReg = new CplexNum[sizeof(CplexNum) *dotCount*2];// 分配内存		
	memset(temReg, 0, sizeof(CplexNum) * dotCount * 2);// 赋为0		
	for(i=0;i<dotCount;i++)// 将时域点写入数组temReg
	{
		temReg[i].re=pTd[i];
		temReg[i].im=0;
	}		
	FastFourierTran(temReg,temReg,power+1);// 调用快速付立叶变换		
	dTemp = 1/sqrt(dotCount);// 调整系数		
	pFd[0] = temReg[0].re*dTemp;// 求pFd[0]	
	dTemp *= sqrt(2);		
	for(i = 1; i < dotCount; i++)// 求pFd[u]	
	{
		pFd[i]=(temReg[i].re* cos(i*pi/(dotCount*2)) + temReg[i].im* sin(i*pi/(dotCount*2))) * dTemp;
	}		
	delete temReg;// 释放内存
}

/*************************************************************************
 * 函数名称：CosTran(LPSTR lpSrcStartBits, long lWidth, long lHeight,long lLineBytes)
 * 函数参数:
 *   LPSTR lpSrcStartBits,指向DIB起始像素的指针
 *   long lWidth,DIB的宽度
 *   long lHeight,DIB的高度
 *	 long lLineBytes,DIB的行字节数，为4的倍数
 * 函数类型:BOOL
 * 函数功能: 用来对图象进行离散余弦变换
************************************************************************/
BOOL  CosTran(LPSTR lpSrcStartBits, long lWidth, long lHeight,long lLineBytes)
{		
	unsigned char*	lpSrcUnChr;	//指向像素的指针
	long i;                 //行循环变量
	long j;                 //列循环变量 			
	long	wid=1,hei=1;// 进行付立叶变换的宽度和高度，初始化为1
	double	dTemp;// 中间变量	
	int		widpor=0,heiPor=0;//2的幂数

	while(wid * 2 <= lWidth)// 计算进行离散余弦变换的宽度和高度（2的整数次方）
	{
		wid *= 2;
		widpor++;
	}	
	while(hei * 2 <= lHeight)
	{
		hei *= 2;
		heiPor++;
	}		
	double *pTd= new double[wid * hei];// 分配内存
	double *pFd = new double[wid * hei];		
	for(i = 0; i < hei; i++)// 行
	{		
		for(j = 0; j < wid; j++)// 列
		{
			// 指向DIB第i行，第j个像素的指针
			lpSrcUnChr= (unsigned char*)lpSrcStartBits + lLineBytes * (lHeight- 1 - i) + j;						
			pTd[j + i * wid] = *(lpSrcUnChr);// 给时域赋值
		}
	}	
	for(i = 0; i < hei; i++)
	{		
		DisFCosTran(&pTd[wid * i], &pFd[wid * i], widpor);// 对y方向进行离散余弦变换
	}		
	for(i = 0; i < hei; i++)// 保存计算结果
	{
		for(j = 0; j < wid; j++)
		{
			pTd[j * hei + i] = pFd[j + wid * i];
		}
	}	
	for(j = 0; j < wid; j++)
	{		
		DisFCosTran(&pTd[j * hei], &pFd[j * hei], heiPor);// 对x方向进行离散余弦变换
	}		
	for(i = 0; i < hei; i++)// 行
	{		
		for(j = 0; j < wid; j++)// 列
		{			
			dTemp = fabs(pFd[j*hei+i]);// 计算频谱
			
			
			if (dTemp > 255)// 是否超过255,超过的，直接设置为255
			{
				dTemp = 255;
			}			
			// 指向DIB第y行，第x个像素的指针
			lpSrcUnChr= (unsigned char*)lpSrcStartBits + lLineBytes * (lHeight- 1 - i) + j;						
			* (lpSrcUnChr) = (BYTE)(dTemp);// 更新源图象
		}
	}		
	delete pTd;// 释放内存
	delete pFd;	
	return TRUE;
}

/*************************************************************************
 * 函数名称：Walshei_Har(double *pTd, double *pFd, int power)
 * 函数参数:
 *   double * pTd,指向时域值的指针
 *   double * pFd,指向频域值的指针
 *   int    power,2的幂数
 *
 * 函数类型:void
 * 函数功能: 用来实现快速沃尔什-哈达玛变换
************************************************************************/

void  Walshei_Har(double *pTd, double *pFd, int power)
{	
	long	dotCount;// 沃尔什-哈达玛变换点数		
	int		i,j,k;// 循环变量	
	int		bfsize,p;// 中间变量	
	double *temReg1,*temReg2,*temReg;		
	dotCount = 1 << power;// 计算快速沃尔什变换点数		
	temReg1 = new double[dotCount];// 分配运算所需的数组
	temReg2 = new double[dotCount];
	memcpy(temReg1, pTd, sizeof(double) * dotCount);// 将时域点写入数组temReg1		
	for(k = 0; k < power; k++)// 蝶形运算
	{
		for(j = 0; j < 1<<k; j++)
		{
			bfsize = 1 << (power-k);
			for(i = 0; i < bfsize / 2; i++)
			{
				p = j * bfsize;
				temReg2[i + p] = temReg1[i + p] + temReg1[i + p + bfsize / 2];
				temReg2[i + p + bfsize / 2] = temReg1[i + p] - temReg1[i + p + bfsize / 2];
			}
		}				
		temReg = temReg1;// 互换temReg1和temReg2  
		temReg1 = temReg2;
		temReg2 = temReg;
	}	
	for(j = 0; j < dotCount; j++)// 调整系数
	{
		p = 0;
		for(i = 0; i < power; i++)
		{
			if (j & (1<<i))
			{
				p += 1 << (power-i-1);
			}
		}
		pFd[j] = temReg1[p] / dotCount;
	}		
	delete temReg1;// 释放内存
	delete temReg2;
}

/*************************************************************************
 * 函数名称：Walsh_HarTran(LPSTR lpSrcStartBits, long lWidth, long lHeight,long lLineBytes)
 * 函数参数:
 *   LPSTR lpSrcStartBits,指向源DIB图象指针
 *   long  lWidth,源DIB图象宽度
 *   long  lHeight,源DIB图象高度
 *   long lLineBytes,源DIB图象的行字节数，为4的倍数
 * 函数类型:BOOL
 * 函数功能:用来对图象进行沃尔什-哈达玛变换
************************************************************************/

BOOL  Walsh_HarTran(LPSTR lpSrcStartBits, long lWidth, long lHeight,long lLineBytes)
{
	unsigned char*	lpSrcUnChr;	//指向像素的指针	
	long i;                 //行循环变量
	long j;                 //列循环变量		

	long	wid=1,hei=1;// 进行付立叶变换的宽度和高度，初始化为1
	double	dTemp;// 中间变量	
	int		widpor=0,heiPor=0;//2的幂数
	
	while(wid * 2 <= lWidth)// 计算进行离散余弦变换的宽度和高度（2的整数次方）
	{
		wid *= 2;
		widpor++;
	}	
	while(hei * 2 <= lHeight)
	{
		hei *= 2;
		heiPor++;
	}		
	double *pTd = new double[wid * hei];// 分配内存
	double *pFd = new double[wid * hei];		
	for(i = 0; i < hei; i++)// 行
	{
		
		for(j = 0; j < wid; j++)// 列
		{
			// 指向DIB第i行，第j个像素的指针
			lpSrcUnChr= (unsigned char*)lpSrcStartBits + lLineBytes * (lHeight- 1 - i) + j;						
			pTd[j + i * wid] = *(lpSrcUnChr);// 给时域赋值
		}
	}	
	for(i = 0; i < hei; i++)
	{		
		Walshei_Har(pTd + wid * i, pFd + wid * i, widpor);// 对y方向进行沃尔什-哈达玛变换
	}		
	for(i = 0; i < hei; i++)// 保存计算结果
	{
		for(j = 0; j < wid; j++)
		{
			pTd[j * hei + i] = pFd[j + wid * i];
		}
	}	
	for(j = 0; j < wid; j++)
	{		
		Walshei_Har(pTd + j * hei, pFd+ j * hei, heiPor);// 对x方向进行沃尔什-哈达玛变换
	}		
	for(i = 0; i < hei; i++)// 行
	{		
		for(j = 0; j < wid; j++)// 列
		{			
			dTemp = fabs(pFd[j * hei + i] * 1000);// 计算频谱						
			if (dTemp > 255)// 对于超过255的，直接设置为255
			{
				dTemp = 255;
			}			
			// 指向DIB第i行，第j个像素的指针
			lpSrcUnChr= (unsigned char*)lpSrcStartBits + lLineBytes * (lHeight- 1 - i) + j;						
			* (lpSrcUnChr) = (BYTE)(dTemp);// 更新源图象
		}
	}		
	delete pTd;//释放内存
	delete pFd;
	return TRUE;
}

/*************************************************************************
 *
 * 函数名称：
 *   DisK_L(LPSTR lpSrcStartBits, long lWidth, long lHeight,long lLineBytes)
 *函数参数:
 *   LPSTR lpSrcStartBits,指向源DIB图象指针
 *   long  lWidth,源DIB图象宽度
 *   long  lHeight,源DIB图象高度
 *   long lLineBytes,源DIB图象的行字节数，为4的倍数
 * 函数类型:BOOL
 * 函数功能:用来对图象进行旋转
 ************************************************************************/

BOOL DisK_L(LPSTR lpSrcStartBits, long lWidth, long lHeight,long lLineBytes)
{
	unsigned char*	lpSrcUnChr;	//指向像素的指针	
	LONG	i,j,// 循环变量
		    lMaxRange,// 经过变换后图象最大可能范围		
		    AverEx,AverEy,//  目标坐标均值		
		    ToaCount;//  目标总的像素数	
	double  Matr4C[2][2],// 坐标值的协方差矩阵
			QMatrix[2][2],// 存放协方差矩阵的特征向量		
			MainCross[2],HypoCross[2],//  三对角阵的主对角和次对角线元素		
			dTemp;// 临时变量
	LONG    lTempI,lTempJ;
				
	if(lWidth>lHeight)// 估计图象经过旋转后可能最大的宽度和高度
	{
		lMaxRange = lWidth;
	}
	else
	{
		lMaxRange =lHeight;
	}
		
	AverEx=0.0;// 初始化
	AverEy=0.0;
	ToaCount = 0;
	Matr4C[0][0] = Matr4C[0][1] = Matr4C[1][0] = Matr4C[1][1] = 0.0;
		
	double *F = new double[lWidth*lHeight];// 分配内存		
	for(i = 0; i < lHeight; i++)// 行
	{		
		for(j = 0; j < lWidth; j++)// 列
		{			
			F[i*lWidth + j] = 255;// 给旋转后坐标轴的每个点赋零值
			// 指向位图i行j列像素的指针
			lpSrcUnChr= (unsigned char*)lpSrcStartBits + lLineBytes*i + j;
						
			// 值小于255（非背景色白色）的像素认为目标的一部分
			// 并将其坐标值x和y看作二维随机矢量
			if((*lpSrcUnChr) < 255)
			{				
				
				AverEx=AverEx+i;// 属于目标像素的Y坐标和X坐标累计值
				AverEy=AverEy+j;				
				ToaCount++;// 目标总的像素数加一
                   
                // 随机矢量协方差矩阵的累计值
				Matr4C[0][0] = Matr4C[0][0] + i*i;
                Matr4C[0][1] = Matr4C[0][1] + i*j;
				Matr4C[1][0] = Matr4C[1][0] + j*i;
				Matr4C[1][1] = Matr4C[1][1] + j*j;
			}
		}
	}
			
	AverEx = AverEx/ToaCount;// 计算随机矢量的均值
	AverEy = AverEy/ToaCount;
	
    Matr4C[0][0] = Matr4C[0][0]/ToaCount - AverEx*AverEx;//  计算随机矢量的协方差矩阵
	Matr4C[0][1] = Matr4C[0][1]/ToaCount - AverEx*AverEy;
	Matr4C[1][0] = Matr4C[1][0]/ToaCount - AverEx*AverEy;
	Matr4C[1][1] = Matr4C[1][1]/ToaCount - AverEy*AverEy;
    
	double Precision = 0.000001;// 规定迭代的计算精度
		
    ThreeCrossMat(*Matr4C, 2, *QMatrix, MainCross, HypoCross);// 将协方差矩阵化作三对角对称阵		
	EigenvalueVector(2, MainCross,HypoCross, *Matr4C, Precision, 50);// 求协方差矩阵的特征值和特征矢向量
   	
    dTemp = Matr4C[0][1];// 将特征列向量转化称特征列向量
	Matr4C[0][1] = Matr4C[1][0];
	Matr4C[1][0] = dTemp;
	
	for(i=0;i<=1;i++)
	{// 对特征列向量进行归一化
		dTemp = pow(Matr4C[i][0],2) + pow(Matr4C[i][1],2);
		dTemp = sqrt(dTemp);
		Matr4C[i][0] = Matr4C[i][0]/dTemp;
		Matr4C[i][1] = Matr4C[i][1]/dTemp;
	}	
	// 查找经离散K-L变换后的坐标点在原坐标系中的坐标    
    for(i = -lMaxRange+1; i < lMaxRange; i++)
	{
		for(j = -lMaxRange+1; j < lMaxRange; j++)
		{
			//  将新坐标值映射到旧的坐标系
			int Cx = (int)(i*Matr4C[0][0]-j*Matr4C[0][1])+AverEx;
			int Cy = (int)(-i*Matr4C[1][0]+j*Matr4C[1][1])+AverEy;
			
			//  映射值是否属于源图象
			if( Cx>=0 && Cx<lHeight && Cy>=0 && Cy<lWidth )
			{
				lpSrcUnChr= (unsigned char*)lpSrcStartBits + lLineBytes*Cx + Cy;

				// 映射值是否属于原来的目标
				if(*(lpSrcUnChr)<255)
				{
					//  将新坐标系原点平移到中心，以便显示
					lTempI=(LONG)(lHeight/2)+j;
					lTempJ=(LONG)(lWidth/2)+i;

					// 看如果能够进行显示，赋值给数组，进行存储
					if( lTempI>=0 && lTempI<lHeight && lTempJ>=0 && lTempJ<lWidth )
						F[lTempJ+ (lTempI) * lWidth]=*(lpSrcUnChr);
				}

			}		
		}
	}
		
	for(i = 0; i < lMaxRange; i++)// 行
	{		
		for(j = 0; j < lMaxRange; j++)// 列
		{			
		    dTemp = F[i * lMaxRange + j] ;// 离散K-L变换后的像素值			
			// 指向位图i行j列像素的指针
			lpSrcUnChr= (unsigned char*)lpSrcStartBits + lLineBytes * (lHeight - 1 - i) + j;						
			* (lpSrcUnChr) = (BYTE)(dTemp);// 更新源图象
		}
	}		
	delete F;// 释放内存	
	return TRUE;// 返回
}

 /*************************************************************************
 * 函数名称：InverseFilter (LPSTR lpSrcStartBits, long lWidth, long lHeight, long lLineBytes)
 * 函数参数:
 *   LPSTR lpSrcStartBits,指向DIB起始像素的指针
 *   long lWidth,DIB的宽度
 *   long lHeight,DIB的高度
 *	 long lLineBytes,DIB的行字节数，为4的倍数
 * 函数类型:BOOL
 * 函数功能: 用来对图象进行逆滤波复原
************************************************************************/
BOOL  InverseFilter (LPSTR lpSrcStartBits, long lWidth, long lHeight, long lLineBytes)
{	
    unsigned char*	lpSrcUnChr;	//指向像素的指针			
	long i;//循环变量
	long j;	
	double tempre, tempim, a, b, c, d;//临时变量	
	LONG	wid = 1;// 实际进行付立叶变换的宽度和高度
	LONG	hei = 1;	
	int		widpor = 0;
	int		heiPor = 0;	
	while(wid * 2 <= lLineBytes)// 保证离散傅立叶变换的宽度和高度为2的整数次方
	{
		wid = wid * 2;
		widpor++;
	}
	
	while(hei * 2 <= lHeight)
	{
		hei = hei * 2;
		heiPor++;
	}	
	CplexNum  *pTdSrc,*pTh;//用来存储源图象和变换核的时域数据	
	CplexNum  *pFdSrc,*pFh;//用来存储源图象和变换核的频域数据		
	double MaxNum;//图象归一化因子		
	if(wid != (int) lLineBytes)//输入退化图象的长和宽必须为2的整数倍
	{
		return FALSE;
	}

	if(hei != (int) lHeight)
	{
		return FALSE;
	}	
	pTdSrc = new CplexNum [sizeof(CplexNum)*lHeight*lLineBytes];// 为时域和频域的数组分配空间
	pTh   = new CplexNum [sizeof(CplexNum)*lHeight*lLineBytes];	
	pFdSrc = new CplexNum [sizeof(CplexNum)*lHeight*lLineBytes];
	pFh   = new CplexNum [sizeof(CplexNum)*lHeight*lLineBytes];
	
	for (j = 0; j < lHeight; j++)// 将退化图象数据存入时域数组
	{
		for(i = 0; i < lLineBytes; i++)
		{						
			lpSrcUnChr= (unsigned char *)lpSrcStartBits + lLineBytes * j + i;// 指向退化图象倒数第j行，第i个像素的指针	
			pTdSrc[ lLineBytes*j + i ].re =(double)*lpSrcUnChr;
			pTdSrc[ lLineBytes*j + i ].im=0.0;
			pFdSrc[ lLineBytes*j + i ].re =0.0;
			pFdSrc[ lLineBytes*j + i ].im =0.0;
	
			if(i < 5 && j < 5)
			{
				pTh[ lLineBytes*j + i ].re =0.04;// complex<double>(0.04 , 0.0);
				pTh[ lLineBytes*j + i ].im =0.0;
			}
			else
			{
				pTh[ lLineBytes*j + i ].re =0.0;
				pTh[ lLineBytes*j + i ].im =0.0;
			}
			pFh[ lLineBytes*j + i ].re =0.0;
			pFh[ lLineBytes*j + i ].im =0.0;
		}
	}	
	Fourier(pTdSrc, lLineBytes, lHeight, pFdSrc);//对退化图象进行FFT		
	Fourier(pTh, lLineBytes, lHeight, pFh);//对变换核图象进行FFT		
	for (i = 0;i <lHeight*lLineBytes;i++)//频域相除
	{
		a = pFdSrc[i].re;
		b = pFdSrc[i].im;
		c = pFh[i].re;
		d = pFh[i].im;				
		if (c*c + d*d > 1e-3)//如果频域值太小，不予考虑
		{
			tempre = ( a*c + b*d ) / ( c*c + d*d );
			tempim = ( b*c - a*d ) / ( c*c + d*d );
		}
		pFdSrc[i].re=tempre;
		pFdSrc[i].im=tempim;

	}	
	InverseFourier(pFdSrc, pTdSrc, lLineBytes, lHeight);//对复原图象进行反FFT	
	MaxNum=300;//确定归一化因子	
	for (j = 0;j < lHeight ;j++)//转换为复原图象
	{
		for(i = 0;i < lLineBytes ;i++)
		{
						
 			lpSrcUnChr = (unsigned char *)lpSrcStartBits + lLineBytes * j + i;// 指向复原图象倒数第j行，第i个像素的指针	
			*lpSrcUnChr= (unsigned char) (pTdSrc[(lLineBytes)*j + i].re*255.0/MaxNum);
		}
	}		
	delete pTdSrc;//释放存储空间
	delete pTh;
	delete pFdSrc;
	delete pFh;	
	return TRUE;// 返回
}
/*************************************************************************
 * 函数名称：WinnerFilter(LPSTR lpSrcStartBits, long lWidth, long lHeight, long lLineBytes)
 * 函数参数:
 *   LPSTR lpSrcStartBits,指向DIB起始像素的指针
 *   long lWidth,DIB的宽度
 *   long lHeight,DIB的高度
 *	 long lLineBytes,DIB的行字节数，为4的倍数
 * 函数类型:BOOL
 * 函数功能: 用来对图象进行维纳滤波复原
************************************************************************/
BOOL  WinnerFilter (LPSTR lpSrcStartBits, long lWidth, long lHeight, long lLineBytes)
{
	unsigned char*	lpSrcUnChr;	//指向像素的指针	
	long i;//循环变量
	long j;	
	double temp, tempre, tempim, //临时变量
			a, b, c, d, tempnorm;		
	LONG	wid = 1;// 实际进行付立叶变换的宽度和高度
	LONG	hei = 1;
	
	int		widpor = 0;
	int		heiPor = 0;
	
	while(wid * 2 <= lLineBytes)// 保证离散傅立叶变换的宽度和高度为2的整数次方
	{
		wid = wid * 2;
		widpor++;
	}	
	while(hei * 2 <= lHeight)
	{
		hei = hei * 2;
		heiPor++;
	}
	CplexNum *pTdSrc,*pTh;	//用来存储源图象和变换核的时域数据	
	CplexNum  *pFdSrc,*pFh;//用来存储源图象和变换核的频域数据	
	
	if(wid != (int) lLineBytes)//输入退化图象的长和宽必须为2的整数倍
	{
		return FALSE;
	}
	if(hei != (int) lHeight)
	{
		return FALSE;
	}	
	pTdSrc		= new CplexNum [sizeof(CplexNum)*lHeight*lLineBytes];// 为时域和频域的数组分配空间
	pTh		= new CplexNum [sizeof(CplexNum)*lHeight*lLineBytes];
	
	pFdSrc		= new CplexNum [sizeof(CplexNum)*lHeight*lLineBytes];
	pFh		= new CplexNum [sizeof(CplexNum)*lHeight*lLineBytes];
	
	double *pCFFilter   = new double [lHeight*lLineBytes];// 滤波器加权系数

	for (j = 0;j < lHeight ;j++)
	{
		for(i = 0;i < lLineBytes ;i++)
		{
			lpSrcUnChr= (unsigned char *)lpSrcStartBits + lLineBytes * j + i;// 指向退化图象倒数第j行，第i个像素的指针
			pTdSrc[ lLineBytes*j + i ].re =(double)*lpSrcUnChr;// 将像素值存储到时域数组中
			pTdSrc[ lLineBytes*j + i ].im=0.0;
			
			pFdSrc[ lLineBytes*j + i ].re=0.0;//// 频域赋零值
			pFdSrc[ lLineBytes*j + i ].im=0.0;//				
			if(i < 5 && j <5)// 退化系统时域及维纳滤波加权系数赋值
			{
				pTh[ lLineBytes*j + i ].re =0.04;
				pTh[ lLineBytes*j + i ].im =0.0;
				pCFFilter[ lLineBytes*j + i ]= 0.5;
			}
			else
			{
				pTh[ lLineBytes*j + i ].re =0.0;
				pTh[ lLineBytes*j + i ].im =0.0;
				pCFFilter[ lLineBytes*j + i ] = 0.05;
			}			
			pFh[ lLineBytes*j + i ].re =0.0;// 频域赋零值
			pFh[ lLineBytes*j + i ].im =0.0;
		}
	}		
	Fourier(pTdSrc, lLineBytes, lHeight, pFdSrc);//对退化图象进行FFT		
	Fourier(pTh, lLineBytes, lHeight, pFh);//对变换核图象进行FFT		
	for (i = 0; i < lHeight * lLineBytes; i++)// 计算M
	{			
			a = pFdSrc[i].re;// 赋值
			b = pFdSrc[i].im;
			c = pFh[i].re;
			d = pFh[i].im;			
			tempnorm = c * c + d * d;// 求模		
			temp  = (tempnorm ) / (tempnorm + pCFFilter[i]);// |H(u,v)|*|H(u,v)|/(|H(u,v)|*|H(u,v)|+a)
			{				
				tempre = ( a*c + b*d ) / ( c*c + d*d );
				tempim = ( b*c - a*d ) / ( c*c + d*d );				
				pFdSrc[i].re=temp*tempre;// 求得f(u,v)
				pFdSrc[i].im=temp*tempim;
			}						
	}	
	InverseFourier(pFdSrc, pTdSrc, lLineBytes, lHeight);//对复原图象进行反FFT	
	for (j = 0;j < lHeight ;j++)//转换为复原图象
	{
		for(i = 0;i < lLineBytes ;i++)
		{
						
 			lpSrcUnChr= (unsigned char *)lpSrcStartBits + lLineBytes * j + i;// 指向复原图象倒数第j行，第i个像素的指针
			a = pTdSrc[(lLineBytes)*j + i].re;
			b = pTdSrc[(lLineBytes)*j + i].im;
			tempnorm  = a*a + b*b;
			tempnorm  = sqrt(tempnorm) + 40;
	
			if(tempnorm > 255)
			{
				tempnorm = 255.0;
			}
			if(tempnorm < 0)
			{
				tempnorm = 0;
			}

			*lpSrcUnChr= (unsigned char) (tempnorm);			
		}
	}	
	delete pTdSrc;//释放存储空间
	delete pTh;
	delete pFdSrc;
	delete pFh;
	delete pCFFilter;	
	return TRUE;// 返回
}
// function.h: interface for the function class.
//
//////////////////////////////////////////////////////////////////////




/*************************************************************************
 * \函数名称：
 *   GrayLinTrans()
 * \输入参数:
 *	 LPSTR lpDIBBits		//指向源图像的像素指针
 *	 LONG lmageWidth		//源图像的宽度
 *	 LONG lmageHeight		// 源图像的高度
 *   int   oralow			// 原始图像的灰度值集中区域－低值
 *   int   orahig			// 原始图像的灰度值集中区域－高值
 *   int   newlow			// 变换后图像灰度的动态范围－低值
 *   int   newhig			// 变换后图像灰度的动态范围－高值
 * \返回值:
 *   BOOL               // 成功返回TRUE，否则返回FALSE。
 * \说明:
 *   该函数用来对图像指定的灰度分布进行灰度变换主要用来实现灰度分布的扩展
*************************************************************************/
BOOL GrayLinTrans(LPSTR lpDIBBits, LONG lmageWidth, LONG lmageHeight,int oralow, int orahig, int newlow, int newhig)
{
	unsigned char*	lpSrc;								// 指向源图像的指针
	int i;												// 循环变量
	int j;												// 循环变量
	BYTE	byMap[256];								// 定义灰度映射表
	for (i = 0; i <= oralow; i++)								//当灰度级小于要增强的灰度级时
	{
		if (newlow > 0)									//判断新灰度级是否大于0
		{
			byMap[i] = newlow;							//赋予新值
		}
		else
		{
			byMap[i] = 0;								//直接赋值为0
		}
	}
	for (; i <= orahig; i++)
	{
		if (orahig != oralow)								// 判断orahig是否等于oralow(防止
											 //分母为0)
		{
			//线性变换
			byMap[i] = newlow + (BYTE) ((newhig - newlow) * (i - oralow) / (orahig - oralow));
		}
		else
		{
			byMap[i] = newlow;							//直接赋值为newlow
		}
	}
	for (; i < newhig; i++)
	{
		if (newhig <= 255)								//判断d是否大于255
		{
			byMap[i] = newhig;							//直接赋值为newhig
		}
		else
		{
			byMap[i] = 255;								//直接赋值为255
		}
	}
	for(i = 0; i < lmageHeight; i++)							//对图像的每个像素值进行变换
	{
		for(j = 0; j < lmageWidth; j++)						//每列
		{
			// 指向DIB第i行，第j个象素的指针
			lpSrc = (unsigned char*)lpDIBBits + lmageWidth * (lmageHeight - 1 - i) + j;
			*lpSrc = byMap[*lpSrc];						//用新的灰度替代原有的灰度
		}
	}
	return TRUE;										//返回
}



/*************************************************************************
* \函数名称：
 *   GrayHistEnhance()
* \输入参数:
 *	 LPSTR lpDIBBits		//指向源图像的像素指针
 *	 LONG lmageWidth		//源图像的宽度
 *	 LONG lmageHeight		//源图像的高度
 * \返回值:
 *   BOOL		       	//成功则返回TRUE，否则返回FALSE
 * \说明:
 *   该函数对指定的图像进行直方图均衡化处理
*************************************************************************/
 BOOL GrayHistEnhance(LPSTR lpDIBBits, LONG lmageWidth, LONG lmageHeight)
 {
	unsigned char*	lpSrc;									//指向源图像的指针
	int	nTemp;											//临时变量
	int j;													//循环变量
	int i;													//循环变量
	BYTE	byMap[256];									//累积直方图，即灰度映射表
	int	nCount[256];										//直方图
	for (i = 0; i < 256; i ++)									//重置计数为0
	{
		nCount[i] = 0;										//清零
	}
	for(i = 0; i < lmageHeight; i++)								//每行
	{
		for(j = 0; j < lmageWidth; j++)							//每列
		{
			// 指向DIB第i行，第j个象素的指针
			lpSrc = (unsigned char*)lpDIBBits + lmageWidth * (lmageHeight - 1 - i) + j;
			nCount[*(lpSrc)]++;								//计数加1
		}
	}
	for (i = 0; i < 256; i++)										//计算累积直方图
	{
		nTemp = 0;										//初始为0
		for (j = 0; j <= i ; j++)
		{
			nTemp += nCount[j];
		}
		byMap[i] = (BYTE) (nTemp * 255 / lmageHeight / lmageWidth); 	//计算对应的新灰度值
//说明：* 255实际上就是将新的灰度值也转换为0～255的范围。
	}
	for(i = 0; i < lmageHeight; i++)
	{
		for(j = 0; j < lmageWidth; j++)							//每列
		{
			//指向DIB第i行，第j个象素的指针
			lpSrc = (unsigned char*)lpDIBBits + lmageWidth * (lmageHeight - 1 - i) + j;
			*lpSrc = byMap[*lpSrc];							//计算新的灰度值
		}
	}
	return TRUE;											//返回
 }	


 /*************************************************************************
 * \函数名称：
 *  Template()
 * \输入参数:
 *	 LPSTR lpDIBBits		- 指向源图像的像素指针
 *	 LONG lmageWidth		- 源图像的宽度
 *	 LONG lmageHeight		- 源图像的高度
 *   int nTempWidth		- 模板的宽度
 *   int nTempHeight		- 模板的高度
 *   int nTempCenX		- 模板中心的X坐标（相对于模板）
 *   int nTempCenY		- 模板中心的Y坐标（相对于模板）
 *   double* Tempdata		- 模板数组的指针
 *   double* TempCoef		- 模板的系数
 * \返回值:
 *   BOOL			- 成功则返回TRUE，否则返回FALSE
 * \说明:
 *   该函数用指定的模板对lpDIBBits指向的图象进行模板操作。模板的定义了宽度，高度，中心坐标
*和系数，模板的数据存放在Tempdata中。对图象进行模板操作后，仍然存放在lpDIBBits指向的对象
*中。需要注意的是，该函数只能处理8位的图象，否则，指向的数据将出错。
 **************************************************************************/
BOOL  Template(LPSTR lpDIBBits, LONG lmageWidth, LONG lmageHeight,
					 int nTempWidth, int nTempHeight, 
					 int nTempCenX, int nTempCenY,
					 double* Tempdata, double TempCoef)
{
	LPBYTE			lpImage;								// 临时存放图像数据的指针
	int 		i;											// 循环变量
	int		j;											// 循环变量
	int 		k;											// 循环变量
	int 		l;											// 循环变量
	unsigned char*	lpSrc;									// 指向源图像的指针
	unsigned char*	lpDst;									// 指向要复制区域的指针
	double	dbResult;										// 计算结果
	lpImage = (LPBYTE) new  char[lmageWidth*lmageHeight];			// 分配内存
	if (lpImage == NULL)										// 判断是否内存分配失败
	{
		return FALSE;										// 分配内存失败
	}
	
	// 将原始图像的数据拷贝到临时存放内存中
	memcpy(lpImage, lpDIBBits, lmageWidth*lmageHeight);
	// 进行模板计算，行(除去边缘几行)
	for(i = nTempCenY ; i <lmageHeight - nTempHeight + nTempCenY + 1; i++)
	{
		// 列(除去边缘几列)
		for(j = nTempCenX; j < lmageWidth - nTempWidth + nTempCenX + 1; j++)
		{
			// 指向新DIB第i行，第j个象素的指针
			lpDst = (unsigned char*)lpImage + lmageWidth * (lmageHeight - 1 - i) + j;
			dbResult = 0;										// 置0
			for (k = 0; k < nTempHeight; k++)
			{
				for (l = 0; l < nTempWidth; l++)
				{
					// 指向DIB第i - iFilterMY + k行，第j - iFilterMX + l个象素的指针
					lpSrc = (unsigned char*)lpDIBBits + lmageWidth * (lmageHeight - 1 - i + nTempCenY - k) + j - nTempCenX + l;
					dbResult += (* lpSrc) * Tempdata[k * nTempWidth + l];	// 保存象素值
				}
			}
			dbResult *= TempCoef;								// 乘上系数
			dbResult = (double ) fabs(dbResult);						// 取绝对值
			if(dbResult > 255)									// 判断是否超过255
			{
				* lpDst = 255;									// 直接赋值为255
			}
			else
			{
				* lpDst = (unsigned char) (dbResult + 0.5);				// 赋值
			}
		}
	}
	memcpy(lpDIBBits, lpImage, lmageWidth*lmageHeight);				//复制变换后的图像
	delete[] lpImage;												// 释放内存
	return TRUE;												// 返回
}

/*************************************************************************
* 函数名称：
 *   MedianValue()
* 参数:
 *   unsigned char * FiltValue	- 指向要获取中值的数组指针
 *   int   iFilterLen				- 数组长度
* 返回值:
 *   unsigned char				- 返回指定数组的中值。
* 说明:
 *   该函数用冒泡法对一维数组进行排序，并返回数组元素的中值。
************************************************************************/

unsigned char  MedianValue(unsigned char * FiltValue, int mFilterLen)
{
	int		i;										// 循环变量
	int		j;										// 循环变量
	unsigned char Temp;									// 中间变量
	// 用冒泡法对数组进行排序
	for (j = 0; j < mFilterLen - 1; j ++)
	{
		for (i = 0; i < mFilterLen - j - 1; i ++)
		{
			if (FiltValue[i] > FiltValue[i + 1])					// 前面的值大于后面的
			{
				Temp = FiltValue[i];
				FiltValue[i] = FiltValue[i + 1];				// 二者的值互换
				FiltValue[i + 1] = Temp;
			}
		}
	}
	if ((mFilterLen & 1) > 0)								// 计算中值
	{
		//数组有奇数个元素，返回中间一个元素
		Temp = FiltValue[(mFilterLen + 1) / 2];
	}
	else
	{
		//数组有偶数个元素，返回中间两个元素平均值
		Temp = (FiltValue[mFilterLen / 2] + FiltValue[mFilterLen / 2 + 1]) / 2;
	}
	return Temp;										// 返回中值
}




/*************************************************************************
* 函数名称：
 *   MedianFilter()
* 参数:
 *   LPSTR lpDIBBits			- 指向源DIB图像指针
 *   LONG  lmageWidth		- 源图像宽度（象素数）
 *   LONG  lmageHeight		- 源图像高度（象素数）
 *   int   mFilterH				- 滤波器的高度
 *   int   mFilterW			- 滤波器的宽度
 *   int   mFilterMX			- 滤波器的中心元素X坐标
 *   int   mFilterMY			- 滤波器的中心元素Y坐标
* 返回值:
 *   BOOL					- 成功返回TRUE，否则返回FALSE。
 * 说明:
 *   该函数对DIB图像进行中值滤波。
************************************************************************/

BOOL  MedianFilter(LPSTR lpDIBBits, LONG lmageWidth, LONG lmageHeight, 
						 int mFilterH, int mFilterW, int mFilterMX, int mFilterMY)
{
	unsigned char*	lpSrc;								// 指向源图像的指针
	unsigned char*	lpDst;								// 指向要复制区域的指针
	LPBYTE lpImage;									// 指向复制图像的指针
	unsigned char* FiltValue;								// 指向滤波器数组的指针
	int			i;									// 循环变量
	int			j;									// 循环变量
	int			k;									// 循环变量
	int			l;									// 循环变量
	lpImage = (LPBYTE) new char[lmageWidth *lmageHeight];		// 暂时分配内存，以保存新图像
	if (lpImage == NULL)									// 判断是否内存分配失败
	{
		return FALSE;									// 分配内存失败
	}	
	memcpy(lpImage, lpDIBBits, lmageWidth *lmageHeight);		// 初始化图像为原始图像
	FiltValue = new unsigned char[mFilterH *mFilterW];			// 暂时分配内存，以保存滤波器数组
	if (FiltValue == NULL)								// 判断是否内存分配失败
	{
		delete[]lpImage;									// 释放已分配内存
		return FALSE;									// 分配内存失败
	}
	// 开始中值滤波
	for(i = mFilterMY; i < lmageHeight - mFilterH + mFilterMY + 1; i++)
	{
		for(j = mFilterMX; j < lmageWidth - mFilterW + mFilterMX + 1; j++)
		{
			// 指向新DIB第i行，第j个象素的指针
			lpDst = (unsigned char*)lpImage + lmageWidth * (lmageHeight - 1 - i) + j;
			for (k = 0; k < mFilterH; k++)					// 读取滤波器数组
			{
				for (l = 0; l < mFilterW; l++)
				{
					// 指向DIB第i - iFilterMY + k行，第j - iFilterMX + l个象素的指针
					lpSrc = (unsigned char*)lpDIBBits + lmageWidth  * (lmageHeight - 1 - i + mFilterMY 
						  - k) + j - mFilterMX + l;
					FiltValue[k * mFilterW + l] = *lpSrc;		// 保存象素值
				}
			}
			*lpDst= MedianValue(FiltValue, (mFilterH * mFilterW)); // 获取中值
		}
	}
	memcpy(lpDIBBits, lpImage, lmageWidth*lmageHeight);			// 复制变换后的图像
	delete[]lpImage;										// 释放内存
	delete[]FiltValue;
	return TRUE;										// 返回
}



/*************************************************************************
 *
 * \函数名称：
 *   FFT_1D()
 *
 * \输入参数:
 *   complex<double> * pCTData	- 指向时域数据的指针，输入的需要变换的数据
 *   complex<double> * pCFData	- 指向频域数据的指针，输出的经过变换的数据
 *   nLevel						－傅立叶变换蝶形算法的级数，2的幂数，
 *
 * \返回值:
 *   无
 *
 * \说明:
 *   一维快速傅立叶变换。
 *
 *************************************************************************
 */
void FFT_1D(complex<double> * pCTData, complex<double> * pCFData, int nLevel)
{
		// 循环控制变量
	int		i;
	int     j;
	int     k;

	// 傅立叶变换点数
	int	nCount =0 ;

	// 计算傅立叶变换点数
	nCount =(int)pow(2,nLevel) ;
	
	// 某一级的长度
	int		nBtFlyLen;
	nBtFlyLen = 0 ;
	
	// 变换系数的角度 ＝2 * PI * i / nCount
	double	dAngle;
	
	complex<double> *pCW ;
	
	// 分配内存，存储傅立叶变化需要的系数表
	pCW  = new complex<double>[nCount / 2];

    // 计算傅立叶变换的系数
	for(i = 0; i < nCount / 2; i++)
	{
		dAngle = -2 * PI * i / nCount;
		pCW[i] = complex<double> ( cos(dAngle), sin(dAngle) );
	}

	// 变换需要的工作空间
	complex<double> *pCWork1,*pCWork2; 
	
	// 分配工作空间
	pCWork1 = new complex<double>[nCount];

	pCWork2 = new complex<double>[nCount];

	
	// 临时变量
	complex<double> *pCTmp;
	
	// 初始化，写入数据
	memcpy(pCWork1, pCTData, sizeof(complex<double>) * nCount);

	// 临时变量
	int nInter; 
	nInter = 0;

	// 蝶形算法进行快速傅立叶变换
	for(k = 0; k < nLevel; k++)
	{
		for(j = 0; j < (int)pow(2,k); j++)
		{
			//计算长度
			nBtFlyLen = (int)pow( 2,(nLevel-k) );
			
			//倒序重排，加权计算
			for(i = 0; i < nBtFlyLen/2; i++)
			{
				nInter = j * nBtFlyLen;
				pCWork2[i + nInter] = 
					pCWork1[i + nInter] + pCWork1[i + nInter + nBtFlyLen / 2];
				pCWork2[i + nInter + nBtFlyLen / 2] =
					(pCWork1[i + nInter] - pCWork1[i + nInter + nBtFlyLen / 2]) 
					* pCW[(int)(i * pow(2,k))];
			}
		}

		// 交换 pCWork1和pCWork2的数据
		pCTmp   = pCWork1	;
		pCWork1 = pCWork2	;
		pCWork2 = pCTmp		;
	}
	
	// 重新排序
	for(j = 0; j < nCount; j++)
	{
		nInter = 0;
		for(i = 0; i < nLevel; i++)
		{
			if ( j&(1<<i) )
			{
				nInter += 1<<(nLevel-i-1);
			}
		}
		pCFData[j]=pCWork1[nInter];
	}
	
	// 释放内存空间
	delete pCW;
	delete pCWork1;
	delete pCWork2;
	pCW		=	NULL	;
	pCWork1 =	NULL	;
	pCWork2 =	NULL	;

}
/*************************************************************************
 *
 * \函数名称：
 *    IFFT_1D()
 *
 * \输入参数:
 *   complex<double> * pCTData	- 指向时域数据的指针，输入的需要反变换的数据
 *   complex<double> * pCFData	- 指向频域数据的指针，输出的经过反变换的数据
 *   nLevel						－傅立叶变换蝶形算法的级数，2的幂数，
 *
 * \返回值:
 *   无
 *
 * \说明:
 *   一维快速傅立叶反变换。
 *
 ************************************************************************
 */
void IFFT_1D(complex<double> * pCFData, complex<double> * pCTData, int nLevel)
{
	
	// 循环控制变量
	int		i;

	// 傅立叶反变换点数
	int nCount;

	// 计算傅立叶变换点数
	nCount = (int)pow(2,nLevel) ;
	
	// 变换需要的工作空间
	complex<double> *pCWork;	
	
	// 分配工作空间
	pCWork = new complex<double>[nCount];
	
	// 将需要反变换的数据写入工作空间pCWork
	memcpy(pCWork, pCFData, sizeof(complex<double>) * nCount);
	
	// 为了利用傅立叶正变换,可以把傅立叶频域的数据取共轭
	// 然后直接利用正变换，输出结果就是傅立叶反变换结果的共轭
	for(i = 0; i < nCount; i++)
	{
		pCWork[i] = complex<double> (pCWork[i].real(), -pCWork[i].imag());
	}
	
	// 调用快速傅立叶变换实现反变换，结果存储在pCTData中
	FFT_1D(pCWork, pCTData, nLevel);
	
	// 求时域点的共轭，求得最终结果
	// 根据傅立叶变换原理，利用这样的方法求得的结果和实际的时域数据
	// 相差一个系数nCount
	for(i = 0; i < nCount; i++)
	{
		pCTData[i] = 
			complex<double> (pCTData[i].real() / nCount, -pCTData[i].imag() / nCount);
	}
	
	// 释放内存
	delete pCWork;
	pCWork = NULL;
}

/*************************************************************************
 *
 * \函数名称：
 *   FFT_2D()
 *
 * \输入参数:
 *   complex<double> * pCTData	- 图像数据
 *   int    nWidth				- 数据宽度
 *   int    nHeight				- 数据高度
 *   complex<double> * pCFData	- 傅立叶变换后的结果
 *
 * \返回值:
 *   无
 *
 * \说明:
 *   二维傅立叶变换。
 *
 ************************************************************************
 */
void FFT_2D(complex<double> * pCTData, int nWidth, int nHeight, complex<double> * pCFData)
{
	
	// 循环控制变量
	int	x;
	int	y;
	
	// 临时变量
	double	dTmpOne;
	double  dTmpTwo;
	
	// 进行傅立叶变换的宽度和高度，（2的整数次幂）
	// 图像的宽度和高度不一定为2的整数次幂
	int		nTransWidth;
	int 	nTransHeight;

	// 计算进行傅立叶变换的宽度	（2的整数次幂）
	dTmpOne = log(nWidth)/log(2);
	dTmpTwo = ceil(dTmpOne)		   ;
	dTmpTwo = pow(2,dTmpTwo)	   ;
	nTransWidth = (int) dTmpTwo	   ;
	
	// 计算进行傅立叶变换的高度 （2的整数次幂）
	dTmpOne = log(nHeight)/log(2);
	dTmpTwo = ceil(dTmpOne)		   ;
	dTmpTwo = pow(2,dTmpTwo)	   ;
	nTransHeight = (int) dTmpTwo	   ;	
	
	// x，y（行列）方向上的迭代次数
	int		nXLev;
	int		nYLev;

	// 计算x，y（行列）方向上的迭代次数
	nXLev = (int) ( log(nTransWidth)/log(2) +  0.5 );
	nYLev = (int) ( log(nTransHeight)/log(2) + 0.5 );
	
	for(y = 0; y < nTransHeight; y++)
	{
		// x方向进行快速傅立叶变换
		FFT_1D(&pCTData[nTransWidth * y], &pCFData[nTransWidth * y], nXLev);
	}
	
	// pCFData中目前存储了pCTData经过行变换的结果
	// 为了直接利用FFT_1D，需要把pCFData的二维数据转置，再一次利用FFT_1D进行
	// 傅立叶行变换（实际上相当于对列进行傅立叶变换）
	for(y = 0; y < nTransHeight; y++)
	{
		for(x = 0; x < nTransWidth; x++)
		{
			pCTData[nTransHeight * x + y] = pCFData[nTransWidth * y + x];
		}
	}
	
	for(x = 0; x < nTransWidth; x++)
	{
		// 对x方向进行快速傅立叶变换，实际上相当于对原来的图象数据进行列方向的
		// 傅立叶变换
		FFT_1D(&pCTData[x * nTransHeight], &pCFData[x * nTransHeight], nYLev);
	}

	// pCFData中目前存储了pCTData经过二维傅立叶变换的结果，但是为了方便列方向
	// 的傅立叶变换，对其进行了转置，现在把结果转置回来
	for(y = 0; y < nTransHeight; y++)
	{
		for(x = 0; x < nTransWidth; x++)
		{
			pCTData[nTransWidth * y + x] = pCFData[nTransHeight * x + y];
		}
	}

	memcpy(pCTData, pCFData, sizeof(complex<double>) * nTransHeight * nTransWidth );
}

/*************************************************************************
 *
 * \函数名称：
 *   IFFT_2D()
 *
 * \输入参数:
 *   complex<double> * pCFData	- 频域数据
 *   complex<double> * pCTData	- 时域数据
 *   int    nWidth				- 图像数据宽度
 *   int    nHeight				- 图像数据高度
 *
 * \返回值:
 *   无
 *
 * \说明:
 *   二维傅立叶反变换。
 *
 ************************************************************************
 */
void IFFT_2D(complex<double> * pCFData, complex<double> * pCTData, int nWidth, int nHeight)
{
	// 循环控制变量
	int	x;
	int	y;
	
	// 临时变量
	double	dTmpOne;
	double  dTmpTwo;
	
	// 进行傅立叶变换的宽度和高度，（2的整数次幂）
	// 图像的宽度和高度不一定为2的整数次幂
	int		nTransWidth;
	int 	nTransHeight;

	// 计算进行傅立叶变换的宽度	（2的整数次幂）
	dTmpOne = log(nWidth)/log(2);
	dTmpTwo = ceil(dTmpOne)		   ;
	dTmpTwo = pow(2,dTmpTwo)	   ;
	nTransWidth = (int) dTmpTwo	   ;
	
	// 计算进行傅立叶变换的高度 （2的整数次幂）
	dTmpOne = log(nHeight)/log(2);
	dTmpTwo = ceil(dTmpOne)		   ;
	dTmpTwo = pow(2,dTmpTwo)	   ;
	nTransHeight = (int) dTmpTwo	   ;
	
	// 分配工作需要的内存空间
	complex<double> *pCWork= new complex<double>[nTransWidth * nTransHeight];

	//临时变量
	complex<double> *pCTmp ;
	
	// 为了利用傅立叶正变换,可以把傅立叶频域的数据取共轭
	// 然后直接利用正变换，输出结果就是傅立叶反变换结果的共轭
	for(y = 0; y < nTransHeight; y++)
	{
		for(x = 0; x < nTransWidth; x++)
		{
			pCTmp = &pCFData[nTransWidth * y + x] ;
			pCWork[nTransWidth * y + x] = complex<double>( pCTmp->real() , -pCTmp->imag() );
		}
	}

	// 调用傅立叶正变换
	FFT_2D(pCWork, nWidth, nHeight, pCTData) ;
	
	// 求时域点的共轭，求得最终结果
	// 根据傅立叶变换原理，利用这样的方法求得的结果和实际的时域数据
	// 相差一个系数
	for(y = 0; y < nTransHeight; y++)
	{
		for(x = 0; x < nTransWidth; x++)
		{
			pCTmp = &pCTData[nTransWidth * y + x] ;
			pCTData[nTransWidth * y + x] = 
				complex<double>( pCTmp->real()/(nTransWidth*nTransHeight),
								 -pCTmp->imag()/(nTransWidth*nTransHeight) );
		}
	}
	delete pCWork ;
	pCWork = NULL ;
}





/*************************************************************************
* \函数名称：
 *   LowPassFilter()
* \输入参数:
 *   LPSTR lpDIBBits					- 指向需要滤波的图像像素指针
 *   int nWidth						- 数据宽度
 *   int nHeight						- 数据高度
 *   int nRadius1						- 理想低通滤波的横向滤波半径
 *	 int nRadius2						- 理想低通滤波的纵向滤波半径
 * \返回值:
 *    BOOL								// 成功返回TRUE，否则返回FALSE。
 * \说明:
 *  lpDIBBits 是指向需要滤波的图像像素指针。
 *  经过低通滤波的数据仍然存储在lpDIBBits 当中。
**************************************************************************/
BOOL LowPassFilter(LPSTR lpDIBBits, LONG nWidth, LONG nHeight,int nRadius1,int nRadius2)
{ 
	unsigned char*	lpSrc;							// 指向源图像的指针
	int y ;										// 循环控制变量
	int x ;										// 循环控制变量
	double dTmpOne ;								//存放临时变量
	double dTmpTwo ;								//存放临时变量
	int nTransWidth ;								// 傅立叶变换的宽度（2的整数次幂）
	int nTransHeight;								// 傅立叶变换的高度（2的整数次幂）
	double unchValue;								// 存贮图像各像素灰度的临时变量
	complex<double> * pCTData ;						// 指向时域数据的指针
	complex<double> * pCFData ;						// 指向频域数据的指针
	// 计算进行傅立叶变换的点数－横向	（2的整数次幂）
	dTmpOne = log(nWidth)/log(2);
	dTmpTwo = ceil(dTmpOne)	;
	dTmpTwo = pow(2,dTmpTwo);
	nTransWidth = (int) dTmpTwo;	
	// 计算进行傅立叶变换的点数－纵向 （2的整数次幂）
	dTmpOne = log(nHeight)/log(2);
	dTmpTwo = ceil(dTmpOne)	;
	dTmpTwo = pow(2,dTmpTwo);
	nTransHeight = (int) dTmpTwo;
	double dReal;									// 傅立叶变换的实部
	double dImag;									// 傅立叶变换的虚部
	// 低通滤波的半径不能超过频域的最大半径
	if(nRadius1>nTransWidth || nRadius2>nTransHeight)
	{
		return (false);								// 返回FALSE
	}	
	pCTData=new complex<double>[nTransWidth * nTransHeight];	// 分配内存
	pCFData=new complex<double>[nTransWidth * nTransHeight];	// 分配内存
	// 图像数据的宽和高不一定是2的整数次幂，所以pCTData有一部分数据需要补0
	for(y=0; y<nTransHeight; y++)
	{
		for(x=0; x<nTransWidth; x++)
		{
			pCTData[y*nTransWidth + x]=complex<double>(0,0);		// 补零
		}
	}
	//把图像数据传给pCTData
	for(y=0; y<nHeight; y++)
	{
		for(x=0; x<nWidth; x++)
		{
			// 指向DIB第y行，第x个象素的指针
			lpSrc = (unsigned char*)lpDIBBits + nWidth * (nHeight - 1 - y) + x;
			unchValue = *lpSrc;
			pCTData[y*nTransWidth + x]=complex<double>(unchValue,0);
		}
	}
	FFT_2D(pCTData, nWidth, nHeight, pCFData) ;					// 傅立叶正变换
	for(x=0;x<nTransWidth;x++)								//开始实施理想的低通滤波
	{
		for(y=nRadius2;y<nTransHeight-nRadius2;y++)
		{
			// 把纵向所有大于nRadius2的高频分量设置为0
			pCFData[x*nTransHeight + y]=complex<double>(0,0);
		}
	}
	for(x=nRadius1;x<nTransWidth-nRadius1;x++)
	{
		for(y=0;y<nTransHeight;y++)
		{
			// 把横向所有大于nRadius1的高频分量设置为0
			pCFData[x*nTransHeight + y]=complex<double>(0,0);
		}
	}
	IFFT_2D(pCFData, pCTData,nHeight, nWidth); 				// 经过低通滤波的图象进行反变换
	for(y=0; y<nHeight; y++)								// 反变换的数据传给lpDIBBits
	{
		for(x=0; x<nWidth; x++)
		{
			//需要考虑信号的正负问题以及实际所用的图象数据是灰度值还是原始数据
			dReal = pCTData[y*nTransWidth + x].real() ;			// 实部
			dImag = pCTData[y*nTransWidth + x].imag() ;		// 虚部
			unchValue =dReal;
			// 指向DIB第y行，第x个象素的指针
			lpSrc = (unsigned char*)lpDIBBits + nWidth * (nHeight - 1 - y) + x;
			*lpSrc =unchValue ;
		}
	}	
	delete pCTData;										// 释放内存
	delete pCFData;										// 释放内存
	pCTData = NULL;
	pCFData = NULL;	
	return (true);										//返回结果
}


/*************************************************************************
* \函数名称：
 *   ButterWorthLowPass()
* \输入参数:
 *	 LPSTR lpDIBBits					- 指向需要滤波的图像像素指针
 *   int nWidth						- 数据宽度
 *   int nHeight						- 数据高度
 *   int nRadius						- ButterWorth低通滤波的"半功率"点
* \返回值:
 *    BOOL								// 成功返回TRUE，否则返回FALSE。
* \说明:
 *  pDIBBits 是指向需要滤波的图像像素指针。
 *  经过ButterWorth低通滤波的数据仍然存储在lpDIBBits 当中。
 **************************************************************************/
BOOL ButterWorthLowPass(LPSTR lpDIBBits, LONG nWidth, LONG nHeight, int nRadius)
{
	unsigned char*	lpSrc;							// 指向源图像的指针
	int y ;										// 循环控制变量
	int x ;										// 循环控制变量
	double dTmpOne ;								//存放临时变量
	double dTmpTwo ;								//存放临时变量
	double H ;										// ButterWorth 滤波系数
	int nTransWidth ;								// 傅立叶变换的宽度（2的整数次幂）
	int nTransHeight;								// 傅立叶变换的高度（2的整数次幂）
	double dReal ;									// 傅立叶变换的实部
	double dImag;									// 傅立叶变换的虚部
	double unchValue;								// 存贮图像各像素灰度的临时变量
	complex<double> * pCTData ;						// 指向时域数据的指针
	complex<double> * pCFData ;						// 指向频域数据的指针
	// 计算进行傅立叶变换的点数－横向	（2的整数次幂）
	dTmpOne = log(nWidth)/log(2);
	dTmpTwo = ceil(dTmpOne)	;
	dTmpTwo = pow(2,dTmpTwo);
	nTransWidth = (int) dTmpTwo;	
	// 计算进行傅立叶变换的点数－纵向 （2的整数次幂）
	dTmpOne = log(nHeight)/log(2);
	dTmpTwo = ceil(dTmpOne)	;
	dTmpTwo = pow(2,dTmpTwo);
	nTransHeight = (int) dTmpTwo;	
	pCTData=new complex<double>[nTransWidth * nTransHeight]; // 分配内存
	pCFData=new complex<double>[nTransWidth * nTransHeight]; // 分配内存
	// 图像数据的宽和高不一定是2的整数次幂，所以pCTData有一部分数据需要补0
	for(y=0; y<nTransHeight; y++)
	{
		for(x=0; x<nTransWidth; x++)
		{
			pCTData[y*nTransWidth + x]=complex<double>(0,0);	// 补零
		}
	}
	for(y=0; y<nHeight; y++)							// 把图像数据传给pCTData
	{
		for(x=0; x<nWidth; x++)
		{
			// 指向DIB第y行，第x个象素的指针
			lpSrc = (unsigned char*)lpDIBBits + nWidth * (nHeight - 1 - y) + x;
			unchValue = *lpSrc;
			pCTData[y*nTransWidth + x]=complex<double>(unchValue,0);
		}
	}	
	FFT_2D(pCTData, nWidth, nHeight, pCFData) ;			// 傅立叶正变换
	for(y=0; y<nTransHeight; y++)						// 开始实施ButterWorth低通滤波
	{
		for(x=0; x<nTransWidth; x++)
		{
			H = (double)(y*y+x*x) ; 
			H = H / (nRadius * nRadius); 
			H = 1/(1+H)  ;							// 求H值
			pCFData[y*nTransWidth + x]=complex<double>(pCFData[y*nTransWidth + x].real()*H, 
			pCFData[y*nTransWidth + x].imag()*H);
		}
	}
	// 经过ButterWorth低通滤波的图象进行反变换
	IFFT_2D(pCFData, pCTData, nWidth, nHeight);
	for(y=0; y<nHeight; y++)							// 反变换的数据传给lpDIBBits
	{
		for(x=0; x<nWidth; x++)
		{
			dReal = pCTData[y*nTransWidth + x].real() ;
			dImag = pCTData[y*nTransWidth + x].imag() ;
			unchValue = max(0,min(255,sqrt(dReal*dReal+dImag*dImag) ));
			// 指向DIB第y行，第x个象素的指针
			lpSrc = (unsigned char*)lpDIBBits + nWidth * (nHeight - 1 - y) + x;
			*lpSrc =unchValue ;
		}
	}
	delete pCTData;									// 释放内存
	delete pCFData;									// 释放内存
	pCTData = NULL;
	pCFData = NULL;
	return (true);									//返回结果	
}

/*************************************************************************
* \函数名称：
 *   HighPassFilter()
* \输入参数:
 *   LPSTR lpDIBBits					- 指向需要滤波的图像像素指针
 *   int nWidth						- 数据宽度
 *   int nHeight						- 数据高度
 *   int nRadius1						- 理想高通滤波的横向滤波半径
 *	 int nRadius2						- 理想高通滤波的纵向滤波半径
 * \返回值:
 *    BOOL								// 成功返回TRUE，否则返回FALSE。
 * \说明:
 *  lpDIBBits 是指向需要滤波的图像像素指针。
 *  经过高通滤波的数据仍然存储在lpDIBBits 当中。
**************************************************************************/
BOOL HighPassFilter(LPSTR lpDIBBits, LONG nWidth, LONG nHeight,int nRadius1,int nRadius2)
{
	unsigned char*	lpSrc;							// 指向源图像的指针
	int y ;										// 循环控制变量
	int x ;										// 循环控制变量
	double dTmpOne ;								//存放临时变量
	double dTmpTwo ;								//存放临时变量
	int nTransWidth ;								// 傅立叶变换的宽度（2的整数次幂）
	int nTransHeight;								// 傅立叶变换的高度（2的整数次幂）
	double unchValue;								// 存贮图像各像素灰度的临时变量
	complex<double> * pCTData ;						// 指向时域数据的指针
	complex<double> * pCFData ;						// 指向频域数据的指针
	// 计算进行傅立叶变换的点数－横向	（2的整数次幂）
	dTmpOne = log(nWidth)/log(2);
	dTmpTwo = ceil(dTmpOne)	;
	dTmpTwo = pow(2,dTmpTwo);
	nTransWidth = (int) dTmpTwo;	
	// 计算进行傅立叶变换的点数－纵向 （2的整数次幂）
	dTmpOne = log(nHeight)/log(2);
	dTmpTwo = ceil(dTmpOne)	;
	dTmpTwo = pow(2,dTmpTwo);
	nTransHeight = (int) dTmpTwo;
	double dReal;									// 傅立叶变换的实部
	double dImag;									// 傅立叶变换的虚部
	// 滤波的半径不能超过频域的最大半径
	if(nRadius1>nTransWidth-1 || nRadius2>nTransHeight-1)
	{
		return (false);								// 返回false
	}
	pCTData=new complex<double>[nTransWidth * nTransHeight];	// 分配内存
	pCFData=new complex<double>[nTransWidth * nTransHeight];	// 分配内存
	// 图像数据的宽和高不一定是2的整数次幂，所以pCTData有一部分数据需要补0
	for(y=0; y<nTransHeight; y++)
	{
		for(x=0; x<nTransWidth; x++)
		{
			pCTData[y*nTransWidth + x]=complex<double>(0,0);	// 补零
		}
	}
	for(y=0; y<nHeight; y++)								// 把图像数据传给pCTData
	{
		for(x=0; x<nWidth; x++)
		{
			// 指向DIB第y行，第x个象素的指针
			lpSrc = (unsigned char*)lpDIBBits + nWidth * (nHeight - 1 - y) + x;
			unchValue = *lpSrc;
			pCTData[y*nTransWidth + x]=complex<double>(unchValue,0);
		}
	}	
	FFT_2D(pCTData, nWidth, nHeight, pCFData) ;				// 傅立叶正变换
	for(x=0;x<nTransWidth;x++)							// 开始实施理想的高通滤波
	{
			for(y=0;y<nRadius2;y++)
			{
				//把纵向所有小于nRadius2的低频分量设置为0
				pCFData[x*nTransHeight + y]=complex<double>(0,0);
			}
			for(y=nTransHeight-1-nRadius2;y<nTransHeight;y++)
			{
				pCFData[x*nTransHeight + y]=complex<double>(0,0);
			}
	}
		for(x=0;x<nRadius1;x++)
		{
			//把横向所有小于nRadius1的低频分量设置为0
			for(y=0;y<nTransHeight;y++)
				pCFData[x*nTransHeight + y]=complex<double>(0,0);
		}
		for(x=nTransWidth-nRadius1;x<nTransWidth;x++)
		{
			for(y=0;y<nTransHeight;y++)
				pCFData[x*nTransHeight + y]=complex<double>(0,0);
		} 
	IFFT_2D(pCFData, pCTData,nHeight, nWidth);			// 经过高通滤波的图象进行反变换
	for(y=0; y<nHeight; y++)							// 反变换的数据传给lpDIBBits
	{
		for(x=0; x<nWidth; x++)
		{
			//需要考虑信号的正负问题以及实际所用的图象数据是灰度值还是原始数据
			dReal = pCTData[y*nTransWidth + x].real() ;
			dImag = pCTData[y*nTransWidth + x].imag() ;
			unchValue =dReal;
			// 指向DIB第y行，第x个象素的指针
			lpSrc = (unsigned char*)lpDIBBits + nWidth * (nHeight - 1 - y) + x;
			*lpSrc =unchValue ;
		}
	}
	delete pCTData;										// 释放内存
	delete pCFData;										// 释放内存
	pCTData = NULL;
	pCFData = NULL;	
	return (true);										// 返回结果
}

/*************************************************************************
 * \函数名称：
 *   ButterWorthHighPass()
 * \输入参数:
 *	 LPSTR lpDIBBits					- 指向需要滤波的图像像素指针
 *   int nWidth							- 数据宽度
 *   int nHeight						- 数据高度
 *   int nRadius            - ButterWorth高通滤波的"半功率"点
* \返回值:
 *    BOOL								// 成功返回TRUE，否则返回FALSE。
* \说明:
 *  pDIBBits 是指向需要滤波的图像像素指针。
 *  经过ButterWorth低通滤波的数据仍然存储在lpDIBBits 当中。
 **************************************************************************/
BOOL ButterWorthHighPass(LPSTR lpDIBBits, LONG nWidth, LONG nHeight, int nRadius)
{
	unsigned char*	lpSrc;							// 指向源图像的指针
	int y ;										// 循环控制变量
	int x ;										// 循环控制变量
	double dTmpOne ;								//存放临时变量
	double dTmpTwo ;								//存放临时变量
	double H ;										// ButterWorth 滤波系数
	int nTransWidth ;								// 傅立叶变换的宽度（2的整数次幂）
	int nTransHeight;								// 傅立叶变换的高度（2的整数次幂）
	double dReal ;									// 傅立叶变换的实部
	double dImag;									// 傅立叶变换的虚部
	double unchValue;								// 存贮图像各像素灰度的临时变量
	complex<double> * pCTData ;						// 指向时域数据的指针
	complex<double> * pCFData ;						// 指向频域数据的指针
	// 计算进行傅立叶变换的点数－横向（2的整数次幂）
	dTmpOne = log(nWidth)/log(2);
	dTmpTwo = ceil(dTmpOne);
	dTmpTwo = pow(2,dTmpTwo);
	nTransWidth = (int) dTmpTwo;	
	// 计算进行傅立叶变换的点数－纵向 （2的整数次幂）
	dTmpOne = log(nHeight)/log(2);
	dTmpTwo = ceil(dTmpOne)	;
	dTmpTwo = pow(2,dTmpTwo);
	nTransHeight = (int) dTmpTwo;	
	pCTData=new complex<double>[nTransWidth * nTransHeight];	// 分配内存
	pCFData=new complex<double>[nTransWidth * nTransHeight];	// 分配内存
	// 图像数据的宽和高不一定是2的整数次幂，所以pCTData有一部分数据需要补0
	for(y=0; y<nTransHeight; y++)
	{
		for(x=0; x<nTransWidth; x++)
		{
			pCTData[y*nTransWidth + x]=complex<double>(0,0);	// 补零
		}
	}
	for(y=0; y<nHeight; y++)						// 把图像数据传给pCTData
	{
		for(x=0; x<nWidth; x++)
		{
		// 指向DIB第y行，第x个象素的指针
			lpSrc = (unsigned char*)lpDIBBits + nWidth * (nHeight - 1 - y) + x;
			unchValue = *lpSrc;
			pCTData[y*nTransWidth + x]=complex<double>(unchValue,0);
		}
	}
	FFT_2D(pCTData, nWidth, nHeight, pCFData) ;		// 傅立叶正变换
	for(y=0; y<nTransHeight; y++)					// 下面开始实施ButterWorth高通滤波
	{
		for(x=0; x<nTransWidth; x++)
		{
			H = (double)(y*y+x*x) ; 
			H = (nRadius * nRadius) / H ; 
			H = 1/(1+H);						// 求H值
			pCFData[y*nTransWidth + x]=complex<double>(H*(pCFData[y*nTransWidth + x].real()),
					 H*(pCFData[y*nTransWidth + x].imag())  );
		}
	}
	// 经过ButterWorth高通滤波的图象进行反变换
	IFFT_2D(pCFData, pCTData, nWidth, nHeight);
	for(y=0; y<nHeight; y++)						// 反变换的数据传给lpDIBBits
	{
		for(x=0; x<nWidth; x++)
		{
			dReal = pCTData[y*nTransWidth + x].real() ;
			dImag = pCTData[y*nTransWidth + x].imag() ;
			unchValue = max(0,min(255,sqrt(dReal*dReal+dImag*dImag)+100 ));
			// 指向DIB第y行，第x个象素的指针
			lpSrc = (unsigned char*)lpDIBBits + nWidth * (nHeight - 1 - y) + x;
			*lpSrc =unchValue ;
		}
	}	
	delete pCTData;									// 释放内存
	delete pCFData;									// 释放内存
	pCTData = NULL;
	pCFData = NULL;
	return (true);									// 返回结果
}


/*************************************************************************
 *
 * 函数名称：
 *   Erosion()
 *
 * 参数:
 *   LPSTR lpDIBBits    - 指向源DIB图像指针
 *   LONG  lmageWidth   - 源图像宽度（象素数，必须是4的倍数）
 *   LONG  lmageHeight  - 源图像高度（象素数）
 *   int   type			- 腐蚀方式，0表示水平方向，1表示垂直方向。
 *	 int   num			- 结构元素的个数（水平方向和垂直方向）。
 *
 * 返回值:
 *   BOOL               - 腐蚀成功返回TRUE，否则返回FALSE。
 *
 * 说明:
 * 该函数用于对图像进行腐蚀运算。结构元素为水平方向或垂直方向，个数由用户选择
 * 为3，5或7，结构原点位于其中心。
 * 要求目标图像为只有0和255两个灰度值的灰度图像，如果不满足，则强行转换。
 ************************************************************************/

BOOL  Erosion(LPSTR lpDIBBits, LONG lmageWidth, LONG lmageHeight, int type , int num)
{
	// 指向源图像的指针
	unsigned char*	lpSrc;	
	// 指向要复制区域的指针
	unsigned char*	lpDst;
	// 指向复制图像的指针
	LPBYTE lpImage;
	// 循环变量
	int			i;
	int			j;
	int			k;		
	// 暂时分配内存，以保存新图像
	lpImage = (LPBYTE) new char[lmageWidth*lmageHeight];	
	// 判断是否内存分配失败
	if (lpImage == NULL)
	{
		// 分配内存失败
		return FALSE;
	}
	//像素值
	unsigned char pixeltemp;
	lpDst = (unsigned char *)lpImage;
	memset(lpDst, (BYTE)255, lmageWidth * lmageHeight);

	//如果图像不是二值图像，转化为二值图像
	for(j = 0; j <lmageHeight; j++)
	{
		for(i = 0;i <lmageWidth; i++)
		{

			// 指向源图像倒数第j行，第i个象素的指针			
			lpSrc = (unsigned char *)lpDIBBits + lmageWidth * j + i;

			//取得当前指针处的像素值，注意要转换为unsigned char型
			pixeltemp = (unsigned char)*lpSrc;

			//目标图像中灰度值大于120的设置为255，否则设置为0
			if(pixeltemp >= 120)
			{
				*lpSrc=(unsigned char)255;
			}
			else
			{
				*lpSrc=(unsigned char)0;
			}
		}
	}


	if(type == 0)
	{
		//使用水平方向的结构元素进行腐蚀
		for(j = 0; j <lmageHeight; j++)
		{
			for(i = (num-1)/2;i <lmageWidth-(num-1)/2; i++)
			{
				//由于使用1×num的结构元素，为防止越界，所以不处理最左边和最右边的(num-1)/2列像素

				// 指向源图像倒数第j行，第i个象素的指针			
				lpSrc = (unsigned char *)lpDIBBits + lmageWidth * j + i;

				// 指向目标图像倒数第j行，第i个象素的指针			
				lpDst = (unsigned char *)lpImage + lmageWidth * j + i;

				//取得当前指针处的像素值，注意要转换为unsigned char型
				pixeltemp = (unsigned char)*lpSrc;
				
				//目标图像中的当前点先赋成黑色
				*lpDst = (unsigned char)0;

				//如果源图像中当前点自身或者左右有(num-1)/2个点不是黑色，
				//则将目标图像中的当前点赋成白色
				for (k = 0;k < num;k++ )
				{
					//读取像素灰度值
					pixeltemp = *(lpSrc+k-(num-1)/2);
					//发现一个白点
					if (pixeltemp == 255 )
					{
						//该点设置为白点
						*lpDst = (unsigned char)255;
						break;
					}
				}
				
			}
		}

	}
	else if(type == 1)
	{
		//使用垂直方向的结构元素进行腐蚀
		for(j = (num-1)/2; j <lmageHeight-(num-1)/2; j++)
		{
			for(i = 0;i <lmageWidth; i++)
			{
				//由于使用1×num的结构元素，为防止越界，所以不处理最上边和最下边的(num-1)/2列像素

				// 指向源图像倒数第j行，第i个象素的指针			
				lpSrc = (unsigned char *)lpDIBBits + lmageWidth * j + i;

				// 指向目标图像倒数第j行，第i个象素的指针			
				lpDst = (unsigned char *)lpImage + lmageWidth * j + i;

				//取得当前指针处的像素值，注意要转换为unsigned char型
				pixeltemp = (unsigned char)*lpSrc;

				//目标图像中的当前点先赋成黑色
				*lpDst = (unsigned char)0;

				//如果源图像中当前点自身或者上下有(num-1)/2个点不是黑色，，
				//则将目标图像中的当前点赋成白色
				for (k = 0;k < num;k++ )
				{	
					//读取像素灰度值
					pixeltemp = *(lpSrc+(k-(num-1)/2)*lmageWidth);
					//发现一个白点
					if (pixeltemp == 255 )
					{
						//该点设置为白点
						*lpDst = (unsigned char)255;
						break;
					}
				}
				
			}
		}

	}
	// 复制腐蚀后的图像
	memcpy(lpDIBBits, lpImage, lmageWidth * lmageHeight);

	// 释放内存
	delete[] lpImage;

	// 返回
	return TRUE;
}



/*************************************************************************
 *
 * 函数名称：
 *   Dilation()
 *
 * 参数:
 *   LPSTR lpDIBBits    - 指向源DIB图像指针
 *   LONG  lmageWidth   - 源图像宽度（象素数，必须是4的倍数）
 *   LONG  lmageHeight  - 源图像高度（象素数）
 *   int   type			- 膨胀方式，0表示水平方向，1表示垂直方向。
 *	 int   num			- 结构元素的个数（水平方向和垂直方向）。
 *
 * 返回值:
 *   BOOL               - 膨胀成功返回TRUE，否则返回FALSE。
 *
 * 说明:
 * 该函数用于对图像进行膨胀运算。结构元素为水平方向或垂直方向，个数由用户选择
 * 为3，5或7，结构原点位于其中心。
 * 要求目标图像为只有0和255两个灰度值的灰度图像，如果不满足，则强行转换。
 ************************************************************************/

BOOL  Dilation(LPSTR lpDIBBits, LONG lmageWidth, LONG lmageHeight, int type , int num)
{
	// 指向源图像的指针
	unsigned char*	lpSrc;	
	// 指向要复制区域的指针
	unsigned char*	lpDst;
	// 指向复制图像的指针
	LPBYTE lpImage;
	// 循环变量
	int			i;
	int			j;
	int			k;		
	// 暂时分配内存，以保存新图像
	lpImage = (LPBYTE) new char[lmageWidth*lmageHeight];	
	// 判断是否内存分配失败
	if (lpImage == NULL)
	{
		// 分配内存失败
		return FALSE;
	}
	//像素值
	unsigned char pixeltemp;
	lpDst = (unsigned char *)lpImage;
	memset(lpDst, (BYTE)255, lmageWidth * lmageHeight);

	//如果图像不是二值图像，转化为二值图像
	for(j = 0; j <lmageHeight; j++)
	{
		for(i = 0;i <lmageWidth; i++)
		{

			// 指向源图像倒数第j行，第i个象素的指针			
			lpSrc = (unsigned char *)lpDIBBits + lmageWidth * j + i;

			//取得当前指针处的像素值，注意要转换为unsigned char型
			pixeltemp = (unsigned char)*lpSrc;

			//目标图像中灰度值大于120的设置为255，否则设置为0
			if(pixeltemp >= 120)
			{
				*lpSrc=(unsigned char)255;
			}
			else
			{
				*lpSrc=(unsigned char)0;
			}
		}
	}


	if(type == 0)
	{
		//使用水平方向的结构元素进行膨胀
		for(j = 0; j <lmageHeight; j++)
		{
			for(i = (num-1)/2;i <lmageWidth-(num-1)/2; i++)
			{
				//由于使用1×num的结构元素，为防止越界，所以不处理最左边和最右边的(num-1)/2列像素

				// 指向源图像倒数第j行，第i个象素的指针			
				lpSrc = (unsigned char *)lpDIBBits + lmageWidth * j + i;

				// 指向目标图像倒数第j行，第i个象素的指针			
				lpDst = (unsigned char *)lpImage + lmageWidth * j + i;

				//取得当前指针处的像素值，注意要转换为unsigned char型
				pixeltemp = (unsigned char)*lpSrc;
				
				//目标图像中的当前点先赋成白色
				*lpDst = (unsigned char)255;

				//如果源图像中当前点自身或者左右各(num-1)/2只要有个点是黑色，
				//则将目标图像中的当前点赋成黑色
				for (k = 0;k < num;k++ )
				{
					//读取像素灰度值
					pixeltemp = *(lpSrc+k-(num-1)/2);
					//发现一个黑点
					if (pixeltemp == 0 )
					{
						//该点设置为黑点
						*lpDst = (unsigned char)0;
						break;
					}
				}
				
			}
		}

	}
	else if(type == 1)
	{
		//使用垂直方向的结构元素进行膨胀
		for(j = (num-1)/2; j <lmageHeight-(num-1)/2; j++)
		{
			for(i = 0;i <lmageWidth; i++)
			{
				//由于使用1×num的结构元素，为防止越界，所以不处理最上边和最下边的(num-1)/2列像素

				// 指向源图像倒数第j行，第i个象素的指针			
				lpSrc = (unsigned char *)lpDIBBits + lmageWidth * j + i;

				// 指向目标图像倒数第j行，第i个象素的指针			
				lpDst = (unsigned char *)lpImage + lmageWidth * j + i;

				//取得当前指针处的像素值，注意要转换为unsigned char型
				pixeltemp = (unsigned char)*lpSrc;

				//目标图像中的当前点先赋成白色
				*lpDst = (unsigned char)255;

				//如果源图像中当前点自身或者上下各(num-1)/2只要有个点是黑色，
				//则将目标图像中的当前点赋成白色
				for (k = 0;k < num;k++ )
				{	
					//读取像素灰度值
					pixeltemp = *(lpSrc+(k-(num-1)/2)*lmageWidth);
					//发现一个白点
					if (pixeltemp == 0 )
					{
						//该点设置为白点
						*lpDst = (unsigned char)0;
						break;
					}
				}
				
			}
		}

	}
	// 复制膨胀后的图像
	memcpy(lpDIBBits, lpImage, lmageWidth * lmageHeight);

	// 释放内存
	delete[] lpImage;

	// 返回
	return TRUE;
}



/*************************************************************************
 *
 * 函数名称：
 *   Thining()
 *
 * 参数:
 *   LPSTR lpDIBBits    - 指向源DIB图像指针
 *   LONG  lmageWidth   - 源图像宽度（象素数，必须是4的倍数）
 *   LONG  lmageHeight  - 源图像高度（象素数）
 *
 * 返回值:
 *   BOOL               - 膨胀成功返回TRUE，否则返回FALSE。
 *
 * 说明:
 * 采用8临域细化的方法，分别进行水平方向和垂直方向的细化
 ************************************************************************/

BOOL Thining(LPSTR lpDIBBits, LONG lmageWidth, LONG lmageHeight)
{
	//创建八临域销点表
	static int erasetable[256]={
                          0,0,1,1,0,0,1,1, 1,1,0,1,1,1,0,1, 1,1,0,0,1,1,1,1, 0,0,0,0,0,0,0,1,
						  0,0,1,1,0,0,1,1, 1,1,0,1,1,1,0,1, 1,1,0,0,1,1,1,1, 0,0,0,0,0,0,0,1,
                          1,1,0,0,1,1,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
						  1,1,0,0,1,1,0,0, 1,1,0,1,1,1,0,1, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
						  0,0,1,1,0,0,1,1, 1,1,0,1,1,1,0,1, 1,1,0,0,1,1,1,1, 0,0,0,0,0,0,0,1,
                          0,0,1,1,0,0,1,1, 1,1,0,1,1,1,0,1, 1,1,0,0,1,1,1,1, 0,0,0,0,0,0,0,0,
						  1,1,0,0,1,1,0,0, 0,0,0,0,0,0,0,0, 1,1,0,0,1,1,1,1, 0,0,0,0,0,0,0,0,
                          1,1,0,0,1,1,0,0, 1,1,0,1,1,1,0,0, 1,1,0,0,1,1,1,0, 1,1,0,0,1,0,0,0
						};

	// 指向源图像的指针
	unsigned char*	lpSrc;	
	// 指向要复制区域的指针
	unsigned char*	lpDst;
	// 指向复制图像的指针
	LPBYTE lpImage;
	// 循环变量
	int			i;
	int			j;
    int         num;

	//临时变量
	int        nw,n,ne,w,e,sw,s,se;
	// 暂时分配内存，以保存新图像
	lpImage = (LPBYTE) new char[lmageWidth*lmageHeight];	
	// 判断是否内存分配失败
	if (lpImage == NULL)
	{
		// 分配内存失败
		return FALSE;
	}
	//像素值
	unsigned char pixeltemp;
	lpDst = (unsigned char *)lpImage;
	//将目标图像赋值（全白）
	//memset(lpDst, (BYTE)255, lmageWidth * lmageHeight);

	//如果图像不是二值图像，转化为二值图像
	for(j = 0; j <lmageHeight; j++)
	{
		for(i = 0;i <lmageWidth; i++)
		{

			// 指向源图像倒数第j行，第i个象素的指针			
			lpSrc = (unsigned char *)lpDIBBits + lmageWidth * j + i;

			//取得当前指针处的像素值，注意要转换为unsigned char型
			pixeltemp = (unsigned char)*lpSrc;

			//目标图像中灰度值大于120的设置为255，否则设置为0
			if(pixeltemp >= 120)
			{
				*lpSrc=(unsigned char)255;
			}
			else
			{
				*lpSrc=(unsigned char)0;
			}
		}
	}

		// 初始化图像为原始图像
	memcpy(lpImage, lpDIBBits, lmageWidth*lmageHeight);	

	//先进行水平方向的细化
	for(j = 1; j <lmageHeight-1; j++)
	{
		for(i = 1;i <lmageWidth-1; i++)
		{
			//为防止越界，宽度，高度上下左右各留出一行

			// 指向源图像倒数第j行，第i个象素的指针			
			lpSrc = (unsigned char *)lpDIBBits + lmageWidth * j + i;

			// 指向目标图像倒数第j行，第i个象素的指针			
			lpDst = (unsigned char *)lpImage + lmageWidth * j + i;
			//是黑点才做处理	
			if(*(lpSrc)==0)
			{
				w=(unsigned char)*(lpSrc-1);  //左邻点
                e=(unsigned char)*(lpSrc+1);  //右邻点
				//如果左右两个邻居中至少有一个是白点才处理
				if( (w==255)|| (e==255))
				{
					nw=(unsigned char)*(lpSrc+lmageWidth-1); //左上邻点
                    n=(unsigned char)*(lpSrc+lmageWidth); //上邻点
                    ne=(unsigned char)*(lpSrc+lmageWidth+1); //右上邻点
                    sw=(unsigned char)*(lpSrc-lmageWidth-1); //左下邻点
                    s=(unsigned char)*(lpSrc-lmageWidth); //下邻点
                    se=(unsigned char)*(lpSrc-lmageWidth+1); //右下邻点
					//计算索引
                    num=nw/255+n/255*2+ne/255*4+w/255*8+e/255*16+sw/255*32+s/255*64+se/255*128;
					if(erasetable[num]==1)
					{ //经查表，可以删除
					//在原图缓冲区中将该黑点删除
					 *(lpSrc)=(unsigned char)255; 					 
					//结果图中该黑点也删除
                    *(lpDst)=(unsigned char)255; 
					}					 
				}
			}		
		}
	}
	//再进行垂直方向的细化
	
	for(i = 1;i <lmageWidth-1; i++)
	{
		for(j = 1; j <lmageHeight-1; j++)
		{
			// 指向源图像倒数第j行，第i个象素的指针			
			lpSrc = (unsigned char *)lpDIBBits + lmageWidth * j + i;
			// 指向目标图像倒数第j行，第i个象素的指针			
			lpDst = (unsigned char *)lpImage + lmageWidth * j + i;
			//是黑点才做处理	
			if(*(lpSrc)==0)
			{
				n=(unsigned char)*(lpSrc+lmageWidth);
                s=(unsigned char)*(lpSrc-lmageWidth);
				//如果上下两个邻居中至少有一个是白点才处理
                if( (n==255)|| (s==255))
				{
					 nw=(unsigned char)*(lpSrc+lmageWidth-1);
                     ne=(unsigned char)*(lpSrc+lmageWidth+1);
                     w=(unsigned char)*(lpSrc-1);
                     e=(unsigned char)*(lpSrc+1);
                     sw=(unsigned char)*(lpSrc-lmageWidth-1);
                     se=(unsigned char)*(lpSrc-lmageWidth+1);
                      //计算索引
					num=nw/255+n/255*2+ne/255*4+w/255*8+e/255*16+sw/255*32+s/255*64+se/255*128;

                     if(erasetable[num]==1)
					 { 
						 //经查表，可以删除
						 //在原图缓冲区中将该黑点删除
						*(lpSrc)=(unsigned char)255; 					 
						//结果图中该黑点也删除
						*(lpDst)=(unsigned char)255; 
					 }
				}
			}
		}
	}
	// 复制细化后的图像
	memcpy(lpDIBBits, lpImage, lmageWidth * lmageHeight);
	// 释放内存
	delete[] lpImage;
	// 返回
	return TRUE;
}


/*************************************************************************
 * 函数名称：
 *   EdgeDetection()
 * 参数:
 *   LPSTR lpDIBBits    - 指向源DIB图像指针
 *   LONG  lWidth       - 源图像宽度（象素数，必须是4的倍数）
 *   LONG  lHeight      - 源图像高度（象素数）
 *	 int mode			- 算子类型
 * 返回值:
 *   BOOL               - 边缘检测成功返回TRUE，否则返回FALSE。
 *
 * 说明:
 * 该函数用Sobel、Isotropic Sobel、LOG边缘检测算子对图像进行边缘检测运算。
 * 要求目标图像为灰度图像。
 ************************************************************************/

BOOL EdgeDetection(LPSTR lpDIBBits, LONG lmageWidth, LONG lmageHeight,int mode)
{

	int nTempWidth;		//模板的宽度
    int nTempHeight;	 // 模板的高度
    int nTempCenX;		//模板中心的X坐标（相对于模板）
    int nTempCenY;		//模板中心的Y坐标（相对于模板）
    double* Tempdata;	//模板数组的指针	
	double TempCoef;	//模板系数
	//循环变量
	int i;
	int j;
	if(mode==0)		//Sobel算子
	{
		// 指向缓存图像的指针
		 unsigned char*	lpDst1;	
		 unsigned char*	lpDst2;
		// 指向存贮图像的指针
		LPBYTE lpImage1;
		LPBYTE lpImage2;	
	
		// 暂时分配内存，以保存新图像
		lpImage1 = (LPBYTE) new  char[lmageWidth*lmageHeight];
		lpImage2 = (LPBYTE) new  char[lmageWidth*lmageHeight];
		// 判断是否内存分配失败
		if (lpImage1 == NULL)
		{
			// 分配内存失败
			return FALSE;
		}	
			// 判断是否内存分配失败
		if (lpImage2 == NULL)
		{
			// 分配内存失败
			return FALSE;
		}
		// 初始化图像为原始图像
		memcpy(lpImage1, lpDIBBits, lmageWidth*lmageHeight);
		memcpy(lpImage2, lpDIBBits, lmageWidth*lmageHeight);
		lpDst1 = (unsigned char*)lpImage1;
		lpDst2 = (unsigned char*)lpImage2;
		//Sobel算子水平检测模板参数
		nTempWidth=3;
		nTempHeight=3;
		nTempCenX=1;
		nTempCenY=1;
		TempCoef=1;
		Tempdata=new double[9];//Sobel算子模板为3X3
		//水平向模板参数
		Tempdata[0]=-1;
		Tempdata[1]=-2;
		Tempdata[2]=-1;
		Tempdata[3]=0;
		Tempdata[4]=0;
		Tempdata[5]=0;
		Tempdata[6]=1;
		Tempdata[7]=2;
		Tempdata[8]=1;
		if (!Template((LPSTR)lpImage1, lmageWidth, lmageHeight,nTempWidth, nTempHeight, 
				nTempCenX, nTempCenY,Tempdata, TempCoef))
		{
			return FALSE;
		}
		//垂直方向模板参数
		Tempdata[0]=-1;
		Tempdata[1]=0;
		Tempdata[2]=1;
		Tempdata[3]=-2;
		Tempdata[4]=0;
		Tempdata[5]=2;
		Tempdata[6]=-1;
		Tempdata[7]=0;
		Tempdata[8]=1;
		if (!Template((LPSTR)lpImage2, lmageWidth, lmageHeight,nTempWidth, nTempHeight, 
				nTempCenX, nTempCenY,Tempdata, TempCoef))
		{
			return FALSE;
		}
		delete[] Tempdata;
		//求两幅缓存图像的最大值
		for(j = 0; j <lmageHeight; j++)
		{
			for(i = 0;i <lmageWidth; i++)
			{

				// 指向缓存图像1倒数第j行，第i个象素的指针			
				lpDst1 = (unsigned char*)lpImage1 + lmageWidth * j + i;

				// 指向缓存图像2倒数第j行，第i个象素的指针			
				lpDst2 = (unsigned char*)lpImage2 + lmageWidth * j + i;
			
				if(*lpDst2 > *lpDst1)
				{
					*lpDst1 = *lpDst2;
				}
		
			}
		}
		//复制经过模板运算后的图像到源图像
		memcpy(lpDIBBits, lpImage1,lmageWidth*lmageHeight);
		return TRUE;
	}
	if(mode==1)		//Isotropic Sobel算子
	{

		// 指向缓存图像的指针
		 unsigned char*	lpDst1;	
		 unsigned char*	lpDst2;
		// 指向存贮图像的指针
		LPBYTE lpImage1;
		LPBYTE lpImage2;	
	
		// 暂时分配内存，以保存新图像
		lpImage1 = (LPBYTE) new  char[lmageWidth*lmageHeight];
		lpImage2 = (LPBYTE) new  char[lmageWidth*lmageHeight];
		// 判断是否内存分配失败
		if (lpImage1 == NULL)
		{
			// 分配内存失败
			return FALSE;
		}	
			// 判断是否内存分配失败
		if (lpImage2 == NULL)
		{
			// 分配内存失败
			return FALSE;
		}
		// 初始化图像为原始图像
		memcpy(lpImage1, lpDIBBits, lmageWidth*lmageHeight);
		memcpy(lpImage2, lpDIBBits, lmageWidth*lmageHeight);
		lpDst1 = (unsigned char*)lpImage1;
		lpDst2 = (unsigned char*)lpImage2;
		//Sobel算子水平检测模板参数
		nTempWidth=3;
		nTempHeight=3;
		nTempCenX=1;
		nTempCenY=1;
		TempCoef=1;
		Tempdata=new double[9];//Sobel算子模板为3X3
		//水平向模板参数
		Tempdata[0]=-1;
		Tempdata[1]=-sqrt(2);
		Tempdata[2]=-1;
		Tempdata[3]=0;
		Tempdata[4]=0;
		Tempdata[5]=0;
		Tempdata[6]=1;
		Tempdata[7]=sqrt(2);
		Tempdata[8]=1;
		if (!Template((LPSTR)lpImage1, lmageWidth, lmageHeight,nTempWidth, nTempHeight, 
				nTempCenX, nTempCenY,Tempdata, TempCoef))
		{
			return FALSE;
		}
		//垂直方向模板参数
		Tempdata[0]=-1;
		Tempdata[1]=0;
		Tempdata[2]=1;
		Tempdata[3]=-sqrt(2);
		Tempdata[4]=0;
		Tempdata[5]=sqrt(2);
		Tempdata[6]=-1;
		Tempdata[7]=0;
		Tempdata[8]=1;
		if (!Template((LPSTR)lpImage2, lmageWidth, lmageHeight,nTempWidth, nTempHeight, 
				nTempCenX, nTempCenY,Tempdata, TempCoef))
		{
			return FALSE;
		}
		delete[] Tempdata;
		//求两幅缓存图像的最大值
		for(j = 0; j <lmageHeight; j++)
		{
			for(i = 0;i <lmageWidth; i++)
			{

				// 指向缓存图像1倒数第j行，第i个象素的指针			
				lpDst1 = (unsigned char*)lpImage1 + lmageWidth * j + i;

				// 指向缓存图像2倒数第j行，第i个象素的指针			
				lpDst2 = (unsigned char*)lpImage2 + lmageWidth * j + i;
			
				if(*lpDst2 > *lpDst1)
				{
					*lpDst1 = *lpDst2;
				}
		
			}
		}
		//复制经过模板运算后的图像到源图像
		memcpy(lpDIBBits, lpImage1,lmageWidth*lmageHeight);
		return TRUE;
	}

	if(mode==2)		//LOG算子
	{
		nTempWidth=5;
		nTempHeight=5;
		nTempCenX=2;
		nTempCenY=2;
		TempCoef=1;
		Tempdata=new double[25];
		Tempdata[0]=-2;
		Tempdata[1]=-4;
		Tempdata[2]=-4;
		Tempdata[3]=-4;
		Tempdata[4]=-2;
		Tempdata[5]=-4;
		Tempdata[6]=0;
		Tempdata[7]=8;
		Tempdata[8]=0;
		Tempdata[9]=-4;
		Tempdata[10]=-4;
		Tempdata[11]=8;
		Tempdata[12]=24;
		Tempdata[13]=8;
		Tempdata[14]=-4;
		Tempdata[15]=-4;
		Tempdata[16]=0;
		Tempdata[17]=8;
		Tempdata[18]=0;
		Tempdata[19]=-4;
		Tempdata[20]=-2;
		Tempdata[21]=-4;
		Tempdata[22]=-4;
		Tempdata[23]=-4;
		Tempdata[24]=-2;
		if (!Template(lpDIBBits, lmageWidth, lmageHeight,nTempWidth, nTempHeight, 
				nTempCenX, nTempCenY,Tempdata, TempCoef))
		{
			return FALSE;
		}
		delete[] Tempdata;
		return TRUE;
	}
		return TRUE;
}



/*************************************************************************
 * 函数名称：
 *   HoughTrans()
 * 参数:
 *   LPSTR lpDIBBits       - 指向源DIB图像指针
 *   LONG  lmageWidth       - 源图像宽度（象素数，必须是4的倍数）
 *   LONG  lmageHeight      - 源图像高度（象素数）
 * 返回值:
 *   BOOL               - 运算成功返回TRUE，否则返回FALSE。
 * 说明:
 * 该函数用于对检测图像中的两条最长的直线。
 * 要求目标图像为只有0和255两个灰度值的灰度图像。
 ************************************************************************/

BOOL  HoughTrans(LPSTR lpDIBBits, LONG lmageWidth, LONG lmageHeight)
{
	// 指向源图像的指针
	unsigned char*	lpSrc;		
	// 指向要复制区域的指针
	unsigned char*	lpDst;
	// 指向变换域的指针
	unsigned char*  lpTrans;
	// 指向复制图像的指针
	LPBYTE lpImage;
	//指向变换域的指针
	LPBYTE lptransImage;
	//变换域的尺寸
	int mMaxDist;//长度
	int mMaxAngleNumber;//角度
	//变换域的坐标
	int mDist;
	int mAngleNumber;
	//循环变量
	int i;
	int j;
	//像素值
	unsigned char pixel;
	//临时像素变量
	unsigned char pixeltemp;

	//存储变换域中的最大值
	MaxValue MaxValue1;
	MaxValue MaxValue2;

	lpImage = (LPBYTE) new  char[lmageWidth*lmageHeight];	
	// 判断是否内存分配失败
	if (lpImage == NULL)
	{
		// 分配内存失败
		return FALSE;
	}
	
	// 初始化新分配的内存，设定初始值为255
	lpDst = (unsigned char *)lpImage;
	memset(lpDst, (BYTE)255, lmageWidth*lmageHeight);
	//计算变换域的尺寸
	//最大距离
	mMaxDist = (int) sqrt(lmageWidth*lmageWidth + lmageHeight*lmageHeight);
	//角度从0－180，每格2度
	mMaxAngleNumber = 90;
	//为变换域分配内存
	lptransImage = (LPBYTE) new  int[lmageWidth*lmageHeight];
	if (lptransImage == NULL)
	{
		// 分配内存失败
		return FALSE;
	}
	// 初始化新分配的内存，设定初始值为255
	lpTrans = (unsigned char *)lptransImage;
	memset(lpTrans, 0, lmageWidth*lmageHeight);

	//如果图像不是二值图像，转化为二值图像
	for(j = 0; j <lmageHeight; j++)
	{
		for(i = 0;i <lmageWidth; i++)
		{

			// 指向源图像倒数第j行，第i个象素的指针			
			lpSrc = (unsigned char *)lpDIBBits + lmageWidth * j + i;

			//取得当前指针处的像素值，注意要转换为unsigned char型
			pixeltemp = (unsigned char)*lpSrc;

			//目标图像中灰度值大于120的设置为255，否则设置为0
			if(pixeltemp >= 120)
			{
				*lpSrc=(unsigned char)255;
			}
			else
			{
				*lpSrc=(unsigned char)0;
			}

			pixel = (unsigned char)*lpSrc;
				//如果是黑点，则在变换域的对应各点上加1
			if(pixel == 0)
			{
				//注意步长是2度
				for(mAngleNumber=0; mAngleNumber<mMaxAngleNumber; mAngleNumber++)
				{
					mDist = (int) fabs(i*cos(mAngleNumber*2*PI/180.0) + j*sin(mAngleNumber*2*PI/180.0));
				
					//变换域的对应点上加1
					*(lptransImage+mDist*mMaxAngleNumber+mAngleNumber) = *(lptransImage+mDist*mMaxAngleNumber+mAngleNumber) +1;
				}
			}

		}
	}
	//找到变换域中的最大值点
	MaxValue1.Value=0;
	MaxValue2.Value=0;

	//找到第一个最大值点
	for (mDist=0; mDist<mMaxDist;mDist++)
	{
		for(mAngleNumber=0; mAngleNumber<mMaxAngleNumber; mAngleNumber++)
		{
			if((int)*(lptransImage+mDist*mMaxAngleNumber+mAngleNumber)>=MaxValue1.Value)
			{
				MaxValue1.Value = (int)*(lptransImage+mDist*mMaxAngleNumber+mAngleNumber);
				MaxValue1.Dist = mDist;
				MaxValue1.AngleNumber = mAngleNumber;
			}

		}
	}

	//将第一个最大值点附近清零
	for (mDist = -9;mDist < 10;mDist++)
	{
		for(mAngleNumber=-1; mAngleNumber<2; mAngleNumber++)
		{
			if(mDist+MaxValue1.Dist>=0 && mDist+MaxValue1.Dist<mMaxDist \
				&& mAngleNumber+MaxValue1.AngleNumber>=0 && mAngleNumber+MaxValue1.AngleNumber<=mMaxAngleNumber)
			{
				*(lptransImage+(mDist+MaxValue1.Dist)*mMaxAngleNumber+\
					(mAngleNumber+MaxValue1.AngleNumber))=0;
			}
		}
	}

	//找到第二个最大值点
	for (mDist=0; mDist<mMaxDist;mDist++)
	{
		for(mAngleNumber=0; mAngleNumber<mMaxAngleNumber; mAngleNumber++)
		{
			if((int)*(lptransImage+mDist*mMaxAngleNumber+mAngleNumber)>=MaxValue2.Value)
			{
				MaxValue2.Value = (int)*(lptransImage+mDist*mMaxAngleNumber+mAngleNumber);
				MaxValue2.Dist = mDist;
				MaxValue2.AngleNumber = mAngleNumber;
			}

		}
	}

	for(j = 0; j <lmageHeight; j++)
	{
		for(i = 0;i <lmageWidth; i++)
		{	
			lpSrc=(unsigned char *)lpDIBBits + lmageWidth * j + i;
			// 指向缓存图像倒数第j行，第i个象素的指针			
			lpDst = (unsigned char *)lpImage + lmageWidth * j + i;	
			//如果该点在某一条直线上，则在缓存图像上将该点赋为黑		
			//在第一条直线上
			mDist = (int) fabs(i*cos(MaxValue1.AngleNumber*2*PI/180.0) + j*sin(MaxValue1.AngleNumber*2*PI/180.0));
			if ((mDist == MaxValue1.Dist)&&(*lpSrc==(unsigned char)0))
			{
				*lpDst = (unsigned char)0;
			}

			//在第二条直线上
			mDist = (int) fabs(i*cos(MaxValue2.AngleNumber*2*PI/180.0) + j*sin(MaxValue2.AngleNumber*2*PI/180.0));
			if ((mDist == MaxValue2.Dist)&&(*lpSrc==(unsigned char)0))
			{
			*lpDst = (unsigned char)0;
			}
		}
	}
	// 复制霍夫变换后的图像
	memcpy(lpDIBBits, lpImage, lmageWidth * lmageHeight);
	delete[] lpImage;
	delete[] lptransImage;
	// 返回
	return TRUE;

}


/*************************************************************************
 * 函数名称：
 *   Outline()
 * 参数:
 *   LPSTR lpDIBBits    - 指向源DIB图像指针
 *   LONG  lmageWidth       - 源图像宽度（象素数，必须是4的倍数）
 *   LONG  lmageHeight      - 源图像高度（象素数）
 * 返回值:
 *   BOOL               - 运算成功返回TRUE，否则返回FALSE。
 *
 * 说明:
 * 该函数用于对图像进行轮廓提取运算。
 * 要求目标图像为只有0和255两个灰度值的灰度图像。
 ************************************************************************/

BOOL Outline(LPSTR lpDIBBits, LONG lmageWidth, LONG lmageHeight)
{
	// 指向源图像的指针
	unsigned char*	lpSrc;	
	// 指向要复制区域的指针
	unsigned char*	lpDst;
	// 指向复制图像的指针
	LPBYTE lpImage;
	// 循环变量
	int			i;
	int			j;
	//存放处理像素八邻域的像素灰度
	unsigned char n,e,s,w,ne,se,nw,sw;
	// 暂时分配内存，以保存新图像
	lpImage = (LPBYTE) new char[lmageWidth*lmageHeight];	
	// 判断是否内存分配失败
	if (lpImage == NULL)
	{
		// 分配内存失败
		return FALSE;
	}
	//像素值
	unsigned char pixeltemp;
	// 初始化新分配的内存，设定初始值为255
	lpDst = (unsigned char *)lpImage;
	memset(lpDst, (BYTE)255, lmageWidth * lmageHeight);

	//如果图像不是二值图像，转化为二值图像
	for(j = 0; j <lmageHeight; j++)
	{
		for(i = 0;i <lmageWidth; i++)
		{

			// 指向源图像倒数第j行，第i个象素的指针			
			lpSrc = (unsigned char *)lpDIBBits + lmageWidth * j + i;

			//取得当前指针处的像素值，注意要转换为unsigned char型
			pixeltemp = (unsigned char)*lpSrc;

			//目标图像中灰度值大于120的设置为255，否则设置为0
			if(pixeltemp >= 120)
			{
				*lpSrc=(unsigned char)255;
			}
			else
			{
				*lpSrc=(unsigned char)0;
			}
		}
	}

	for(j = 1; j <lmageHeight-1; j++)
	{
		for(i = 1;i <lmageWidth-1; i++)
		{
			//为防止越界，宽度，高度上下左右各留出一行
			// 指向源图像倒数第j行，第i个象素的指针			
			lpSrc = (unsigned char *)lpDIBBits + lmageWidth * j + i;

			// 指向目标图像倒数第j行，第i个象素的指针			
			lpDst = (unsigned char *)lpImage + lmageWidth * j + i;
			//是黑点才做处理	
			if(*(lpSrc)==0)
			{
				//目标图像相应的像素也相应的为黑点
				*(lpDst)=0;
				w=(unsigned char)*(lpSrc-1);  //左邻点
                e=(unsigned char)*(lpSrc+1);  //右邻点
				nw=(unsigned char)*(lpSrc+lmageWidth-1); //左上邻点
                n=(unsigned char)*(lpSrc+lmageWidth); //上邻点
                ne=(unsigned char)*(lpSrc+lmageWidth+1); //右上邻点
                sw=(unsigned char)*(lpSrc-lmageWidth-1); //左下邻点
                s=(unsigned char)*(lpSrc-lmageWidth); //下邻点
                se=(unsigned char)*(lpSrc-lmageWidth+1); //右下邻点
				//如果相邻的八个点都是黑点
				if(nw+n+ne+w+e+sw+s+se==0)
				{
					//结果图中该黑点删除
					*(lpDst) = (unsigned char)255;
				}		 					 
			}		
		}
	}
	// 复制轮廓提取后的图像
	memcpy(lpDIBBits, lpImage, lmageWidth * lmageHeight);
	// 释放内存
	delete[] lpImage;
	// 返回
	return TRUE;
}


/*************************************************************************
 * 函数名称：
 *   ContourTrace()
 * 参数:
 *   LPSTR lpDIBBits    - 指向源DIB图像指针
 *   LONG  lWidth       - 源图像宽度（象素数，必须是4的倍数）
 *   LONG  lHeight      - 源图像高度（象素数）
 * 返回值:
 *   BOOL               - 运算成功返回TRUE，否则返回FALSE。
 * 说明:
 * 该函数用于对图像进行轮廓跟踪运算。
 * 要求目标图像为只有0和255两个灰度值的灰度图像，否则自动转化。
 ************************************************************************/

BOOL ContourTrace(LPSTR lpDIBBits, LONG lmageWidth, LONG lmageHeight)
{

	// 指向源图像的指针
	unsigned char*	lpSrc;	
	// 指向要复制区域的指针
	unsigned char*	lpDst;
	// 指向复制图像的指针
	LPBYTE lpImage;
	// 循环变量
	int			i;
	int			j;
	//像素值
	unsigned char pixeltemp;
	//是否找到起始点及回到起始点
	bool IsStartPoint;
	//是否扫描到一个边界点
	bool Pointfind;
	//起始边界点与当前边界点
	CPoint StartPoint;
	CPoint CurrentPoint;
	//八个方向和起始扫描方向
	int Direction[8][2]={{-1,1},{0,1},{1,1},{1,0},{1,-1},{0,-1},{-1,-1},{-1,0}};
	int BeginDirect;

	// 暂时分配内存，以保存新图像
	lpImage = (LPBYTE) new char[lmageWidth*lmageHeight];	
	// 判断是否内存分配失败
	if (lpImage == NULL)
	{
		// 分配内存失败
		return FALSE;
	}
	
	// 初始化新分配的内存，设定初始值为255
	lpDst = (unsigned char *)lpImage;
	memset(lpDst, (BYTE)255, lmageWidth * lmageHeight);

		//如果图像不是二值图像，转化为二值图像
	for(j = 0; j <lmageHeight; j++)
	{
		for(i = 0;i <lmageWidth; i++)
		{

			// 指向源图像倒数第j行，第i个象素的指针			
			lpSrc = (unsigned char *)lpDIBBits + lmageWidth * j + i;

			//取得当前指针处的像素值，注意要转换为unsigned char型
			pixeltemp = (unsigned char)*lpSrc;

			//目标图像中灰度值大于120的设置为255，否则设置为0
			if(pixeltemp >= 120)
			{
				*lpSrc=(unsigned char)255;
			}
			else
			{
				*lpSrc=(unsigned char)0;
			}
		}
	}

	//先找到图像最左下方的边界点，注意是左下方
	IsStartPoint = false;
	for (j = 1;j < lmageHeight && !IsStartPoint;j++)
	{
		for(i = 1;i < lmageWidth && !IsStartPoint;i++)
		{
			// 指向源图像倒数第j行，第i个象素的指针			
			lpSrc = (unsigned char *)lpDIBBits + lmageWidth * j + i;
			
			//取得当前指针处的像素值
			pixeltemp = (unsigned char)*lpSrc;
			//如果为黑点，则为起始点		
			if(pixeltemp == 0)
			{
				IsStartPoint = true;
				StartPoint.y = j;		//起始点的垂直位置
				StartPoint.x = i;		//起始点的水平位置

				// 指向目标图像倒数第j行，第i个象素的指针			
				lpDst = (unsigned char *)lpImage + lmageWidth * j + i;	
				*lpDst = (unsigned char)0;		//目标点设置为黑点
			}		
		}
	}

	//由于起始点是在左下方，故起始扫描沿左上方向
	BeginDirect = 0;
	//跟踪边界
	IsStartPoint = false;
	//从初始点开始扫描
	CurrentPoint.y = StartPoint.y;
	CurrentPoint.x = StartPoint.x;
	while(!IsStartPoint)
	{
		Pointfind = false;
		while(!Pointfind)
		{
			//沿扫描方向查看下一个像素
			lpSrc = (unsigned char *)lpDIBBits + lmageWidth * ( CurrentPoint.y + Direction[BeginDirect][1])
				+ (CurrentPoint.x + Direction[BeginDirect][0]);
			//存贮该点的像素值
			pixeltemp = (unsigned char)*lpSrc;
			//如果该点为黑点
			if(pixeltemp == 0)
			{
				//找到了点，设置为真
				Pointfind = true;
				//记录当前点的位置
				CurrentPoint.y = CurrentPoint.y + Direction[BeginDirect][1];
				CurrentPoint.x = CurrentPoint.x + Direction[BeginDirect][0];
				//如果当前点就是起始点
				if(CurrentPoint.y == StartPoint.y && CurrentPoint.x == StartPoint.x)
				{
					//起始点变量设置为真，退出循环
					IsStartPoint = true;
				}
				//记录当前点，设置为黑点
				lpDst = (unsigned char *)lpImage + lmageWidth * CurrentPoint.y + CurrentPoint.x;
				*lpDst = (unsigned char)0;
				//扫描的方向逆时针旋转两格
				BeginDirect--; //选择一格
				if(BeginDirect == -1)  //如果方向为－1表明是方向7
				{
					BeginDirect = 7;
				}
				BeginDirect--;
				if(BeginDirect == -1)	//如果方向为－1表明是方向7
				{
					BeginDirect = 7;
				}
			}
			//扫描方向的下一个点为白点，那么我们需要改变扫描方向，继续寻找
			else
			{
				//扫描方向顺时针旋转一格
				BeginDirect++;
				if(BeginDirect == 8)
				{
					BeginDirect = 0;	//如果方向为8表明是方向0
				}

			}

		}
	}

	// 复制轮廓跟踪后的图像
	memcpy(lpDIBBits, lpImage, lmageWidth * lmageHeight);
	// 释放内存
	delete[] lpImage;
	// 返回
	return TRUE;
}
//强调一点，本程序只是轮廓跟踪的简单演示，首先搜索图像的左下方，找到的第一个黑点
//就设置为起始点，以此点为基础进行边界扫描，因此只能跟踪一个物体轮廓，当有多个物体
//轮廓需要跟踪时，需要将已经跟踪过的物体去除，继续上述过程。

/*************************************************************************
 * 函数名称：
 *   RegionDivideThreshold()
 * 参数:
 *   LPSTR lpDIBBits    - 指向源DIB图像指针
 *   LONG  lWidth       - 源图像宽度（象素数，必须是4的倍数）
 *   LONG  lHeight      - 源图像高度（象素数）
 *   int threshold		- 分割门限
 * 返回值:
 *   BOOL               - 运算成功返回TRUE，否则返回FALSE。
 * 说明:
 * 该函数用于对图像进行固定阈值分割。
 ************************************************************************/
BOOL RegionDivideThreshold(LPSTR lpDIBBits, LONG lmageWidth, LONG lmageHeight, int threshold)
{
	int i;  //循环变量
	int j;	//循环变量
	// 指向源图像的指针
	unsigned char*	lpSrc;	
	//像素值
	unsigned char pixeltemp;
	for(j = 0; j <lmageHeight; j++)
	{
		for(i = 0;i <lmageWidth; i++)
		{

			// 指向源图像倒数第j行，第i个象素的指针			
			lpSrc = (unsigned char *)lpDIBBits + lmageWidth * j + i;
			//取得当前指针处的像素值
			pixeltemp = (unsigned char)*lpSrc;
			//目标图像中灰度值小于门限则设置为黑点
			if(pixeltemp <= threshold)
			{
				*lpSrc=(unsigned char)0;
			}
			else	//否则设置为白点
			{
				*lpSrc=(unsigned char)255;
			}		
		}
	}
	return true;
}

/*************************************************************************
 * \函数名称：
 *   RegionDivideAdaptive()
 * 参数:
 *   LPSTR lpDIBBits    - 指向源DIB图像指针
 *   LONG  lmageWidth       - 源图像宽度（象素数，必须是4的倍数）
 *   LONG  lmageHeight      - 源图像高度（象素数）
 * 返回值:
 *   BOOL               - 运算成功返回TRUE，否则返回FALSE。
 * 说明:
 * 该函数用于对图像进行自适应阈值分割。把图像分成四个子图象，然后计算每个子图象的均值，
 *  根据均值设置阈值，阈值只是应用在对应的子图像
 *************************************************************************
 */
BOOL RegionDivideAdaptive(LPSTR lpDIBBits, LONG lmageWidth, LONG lmageHeight)
{
	int i;  //循环变量
	int j;	//循环变量
	// 指向源图像的指针
	unsigned char*	lpSrc;	
	//像素值
	unsigned char pixeltemp;	
	// 子图像灰度的平均值
	int nAvg ;
	nAvg = 0 ; //初始化为0
	// 对左下图像逐点扫描：
	for(j = 0; j <lmageHeight/2; j++)
	{
		for(i = 0;i <lmageWidth/2; i++)
		{
			// 指向源图像倒数第j行，第i个象素的指针			
			lpSrc = (unsigned char *)lpDIBBits + lmageWidth * j + i;
			//取得当前指针处的像素值
			pixeltemp = (unsigned char)*lpSrc;
			//灰度的累计
			nAvg = (int)pixeltemp+nAvg;
		}
	}
	// 计算均值
	nAvg = nAvg /((lmageHeight/2) * (lmageWidth/2)) ;
	// 对左下图像逐点扫描：
	for(j = 0; j <lmageHeight/2; j++)
	{
		for(i = 0;i <lmageWidth/2; i++)
		{
			// 指向源图像倒数第j行，第i个象素的指针			
			lpSrc = (unsigned char *)lpDIBBits + lmageWidth * j + i;
			//取得当前指针处的像素值
			pixeltemp = (unsigned char)*lpSrc;
			//目标图像中灰度值小于门限则设置为黑点
			if(pixeltemp <= nAvg)
			{
				*lpSrc=(unsigned char)0;
			}
			else	//否则设置为白点
			{
				*lpSrc=(unsigned char)255;
			}		
		}
	}

	nAvg =0;   //初始化为0

	// 对左上图像逐点扫描：
	for(j = lmageHeight/2; j <lmageHeight; j++)
	{
		for(i = 0;i <lmageWidth/2; i++)
		{
			// 指向源图像倒数第j行，第i个象素的指针			
			lpSrc = (unsigned char *)lpDIBBits + lmageWidth * j + i;
			//取得当前指针处的像素值
			pixeltemp = (unsigned char)*lpSrc;
			//灰度的累计
			nAvg = (int)pixeltemp+nAvg;
		}
	}
	// 计算均值
	nAvg = nAvg /((lmageHeight/2) * (lmageWidth/2)) ;
	// 对左上图像逐点扫描：
	for(j = lmageHeight/2; j <lmageHeight; j++)
	{
		for(i = 0;i <lmageWidth/2; i++)
		{
			// 指向源图像倒数第j行，第i个象素的指针			
			lpSrc = (unsigned char *)lpDIBBits + lmageWidth * j + i;
			//取得当前指针处的像素值
			pixeltemp = (unsigned char)*lpSrc;
			//目标图像中灰度值小于门限则设置为黑点
			if(pixeltemp <= nAvg)
			{
				*lpSrc=(unsigned char)0;
			}
			else	//否则设置为白点
			{
				*lpSrc=(unsigned char)255;
			}		
		}
	}

	nAvg =0;   //初始化为0

	// 对右上图像逐点扫描：
	for(j = lmageHeight/2; j <lmageHeight; j++)
	{
		for(i = lmageWidth/2;i <lmageWidth; i++)
		{
			// 指向源图像倒数第j行，第i个象素的指针			
			lpSrc = (unsigned char *)lpDIBBits + lmageWidth * j + i;
			//取得当前指针处的像素值
			pixeltemp = (unsigned char)*lpSrc;
			//灰度的累计
			nAvg = (int)pixeltemp+nAvg;
		}
	}
	// 计算均值
	nAvg = nAvg /((lmageHeight/2) * (lmageWidth/2)) ;
	// 对右上图像逐点扫描：
	for(j = lmageHeight/2; j <lmageHeight; j++)
	{
		for(i = lmageWidth/2;i <lmageWidth; i++)
		{
			// 指向源图像倒数第j行，第i个象素的指针			
			lpSrc = (unsigned char *)lpDIBBits + lmageWidth * j + i;
			//取得当前指针处的像素值
			pixeltemp = (unsigned char)*lpSrc;
			//目标图像中灰度值小于门限则设置为黑点
			if(pixeltemp <= nAvg)
			{
				*lpSrc=(unsigned char)0;
			}
			else	//否则设置为白点
			{
				*lpSrc=(unsigned char)255;
			}		
		}
	}

		nAvg =0;   //初始化为0

	// 对右下图像逐点扫描：
	for(j = 0; j <lmageHeight/2; j++)
	{
		for(i = lmageWidth/2;i <lmageWidth; i++)
		{
			// 指向源图像倒数第j行，第i个象素的指针			
			lpSrc = (unsigned char *)lpDIBBits + lmageWidth * j + i;
			//取得当前指针处的像素值
			pixeltemp = (unsigned char)*lpSrc;
			//灰度的累计
			nAvg = (int)pixeltemp+nAvg;
		}
	}
	// 计算均值
	nAvg = nAvg /((lmageHeight/2) * (lmageWidth/2)) ;
	// 对右下图像逐点扫描：
	for(j = 0; j <lmageHeight/2; j++)
	{
		for(i = lmageWidth/2;i <lmageWidth; i++)
		{
			// 指向源图像倒数第j行，第i个象素的指针			
			lpSrc = (unsigned char *)lpDIBBits + lmageWidth * j + i;
			//取得当前指针处的像素值
			pixeltemp = (unsigned char)*lpSrc;
			//目标图像中灰度值小于门限则设置为黑点
			if(pixeltemp <= nAvg)
			{
				*lpSrc=(unsigned char)0;
			}
			else	//否则设置为白点
			{
				*lpSrc=(unsigned char)255;
			}		
		}
	}
	return true;
}


/*************************************************************************
 * \函数名称：
 *   RegionGrow()
 * 参数:
 *   LPSTR lpDIBBits    - 指向源DIB图像指针
 *   LONG  lmageWidth       - 源图像宽度（象素数，必须是4的倍数）
 *   LONG  lmageHeight      - 源图像高度（象素数）
 *	 int nThreshold			- 区域生长门限
 *	 int seedx				- 区域生长种子的横坐标
 *	 int seedy				- 区域生长种子的纵坐标
  *	 int mode				- 区域生长种子的选取类型
 * 返回值:
 *   BOOL               - 运算成功返回TRUE，否则返回FALSE。
 * \说明:
 *   本函数的处理结果是将生长后的区域表示为黑色像素，未生长区域表示为白色像素。
 *   区域生长一般包含三个比较重要的问题：
 *		1. 种子点的选取
 *		2. 生长准则
 *		3. 终止条件
 *	 可以认为，这三个问题需要具体分析，而且每个问题解决的好坏直接关系到
 *	 区域生长的结果。
 *************************************************************************/
BOOL RegionGrow(LPSTR lpDIBBits, LONG lmageWidth, LONG lmageHeight, int nThreshold,int seedx,int seedy,int mode)
{	
	//设置用于处理四临域的数组
	static int Dx[]={-1,0,1,0};	//X向
	static int Dy[]={0,1,0,-1};	//y向
	// 临时存放图像数据的指针
	LPBYTE			lpImage;	
	// 指向源图像的指针
	unsigned char*	lpSrc;
	unsigned char*	lpSrc1;
	// 指向要复制区域的指针
	unsigned char*	lpDst;
	// 分配内存
	lpImage = (LPBYTE) new  char[lmageWidth*lmageHeight];	
	// 判断是否内存分配失败
	if (lpImage == NULL)
	{
		// 分配内存失败
		return FALSE;
	}
	// 将目标图像所有像素初始化为白点
	lpDst = (unsigned char *)lpImage;
	memset(lpDst, (BYTE)255, lmageWidth * lmageHeight);
	// 种子点
	CPoint seed;
	if(mode==0) // 如果选择种子点为图像的中心
	{
		// 设置种子点为图像的中心
		seed.x=lmageWidth/2;
		seed.y=lmageHeight/2;
	}
	else //自己设置种子点
	{
		// 设置种子点为输入点
		seed.x=seedx;
		seed.y=seedy;
	}

	// 定义堆栈，分别存贮X Y坐标
	int * GrowX ;
	int * GrowY ;
	
	// 分配空间，最大为图像的像素数目
	GrowX = new int [ lmageWidth * lmageHeight];
	GrowY = new int [ lmageWidth * lmageHeight];

	
	// 定义堆栈的起点和终点
	// 当Start=End, 表示堆栈中只有一个点
	int Start ;
	int End   ;
	//初始化
	Start = 0 ;
	End   = 0 ;
	// 把种子点的坐标压入栈
	GrowX[End] = seed.x;
	GrowY[End] = seed.y;
	// 当前正在处理的象素
	CPoint Current;
	// 循环控制变量
	int k ;
	// 图象的横纵坐标,用来对当前象素的4邻域进行遍历
	int xx;
	int yy;
	while (Start<=End)
	{
		// 当前种子点的坐标
		Current.x = GrowX[Start];
		Current.y = GrowY[Start];
		// 对当前点的4邻域进行遍历
		for (k=0; k<4; k++)	
		{	
			// 4邻域象素的坐标
			xx = Current.x+Dx[k];
			yy = Current.y+Dy[k];
			
			// 判断象素(xx，yy) 是否在图像内部
			// 判断象素(xx，yy) 是否已经处理过
			// *lpDst==255 表示还没有处理
			// 指向源图像(xx，yy)象素的指针			
			lpSrc = (unsigned char *)lpDIBBits + lmageWidth * (lmageHeight-yy) + xx;
			lpSrc1 = (unsigned char *)lpDIBBits + lmageWidth * (lmageHeight-Current.y) + Current.x;
			// 指向目标图像第j行，第i个象素的指针			
			lpDst = (unsigned char *)lpImage + lmageWidth * (lmageHeight-yy) + xx;
			// 生长条件：判断象素(xx，yy)和当前象素(nCurrX,nCurrY) 象素值差的绝对值
			if ((xx < lmageWidth) && (xx>=0) && (yy<lmageHeight) && (yy>=0) && (*lpDst==255) 
					&& abs(*lpSrc-*lpSrc1)<nThreshold )
			{
				// 堆栈的尾部指针后移一位
				End++;
				// 象素(xx，yy) 压入栈
				GrowX[End] = xx;
				GrowY[End] = yy;
				// 目标图像为黑点，同时也表明该象素处理过
				*lpDst=0 ;
			}
		}
		Start++;
	}
	// 复制区域生长后的图像
	memcpy(lpDIBBits, lpImage, lmageWidth * lmageHeight);
	// 释放内存
	delete[] lpImage;
	delete[] GrowX;
	delete[] GrowY;
	// 返回
	return TRUE;
}

/*************************************************************************
 *
 * 函数名称：
 *   Project()
 *
 * 参数:
 *   LPSTR lpDIBBits		- 指向源DIB图像指针
 *   LONG  lmageWidth       - 源图像宽度（象素数，必须是4的倍数）
 *   LONG  lmageHeight      - 源图像高度（象素数）
 *	 int   direction		- 投影方向
 * 返回值:
 *   BOOL               - 运算成功返回TRUE，否则返回FALSE。
 * 说明:
 * 该函数用于对两幅图像进行水平、垂直投影运算。 
 * 要求目标图像为只有0和255两个灰度值的灰度图像，否则强行转换。
 ************************************************************************/

BOOL  Project(LPSTR lpDIBBits, LONG lmageWidth, LONG lmageHeight, int direction)
{
	// 临时存放图像数据的指针
	LPBYTE			lpImage;	
	// 指向源图像的指针
	unsigned char*	lpSrc;
	// 指向要复制区域的指针
	unsigned char*	lpDst;
	// 分配内存
	lpImage = (LPBYTE) new  char[lmageWidth*lmageHeight];	
	// 判断是否内存分配失败
	if (lpImage == NULL)
	{
		// 分配内存失败
		return FALSE;
	}
	// 将目标图像所有像素初始化为白点
	lpDst = (unsigned char *)lpImage;
	memset(lpDst, (BYTE)255, lmageWidth * lmageHeight);

	//循环变量
	int i;
	int j;
	int k;
	//图像中每行内的黑点个数
	int BlackNumber;
	//像素值
	unsigned char pixeltemp;	
	//如果图像不是二值图像，转化为二值图像
	for(j = 0; j <lmageHeight; j++)
	{
		for(i = 0;i <lmageWidth; i++)
		{
			// 指向源图像倒数第j行，第i个象素的指针			
			lpSrc = (unsigned char *)lpDIBBits + lmageWidth * j + i;
			//取得当前指针处的像素值，注意要转换为unsigned char型
			pixeltemp = (unsigned char)*lpSrc;
			//目标图像中灰度值大于120的设置为255，否则设置为0
			if(pixeltemp >= 120)
			{
				*lpSrc=(unsigned char)255;
			}
			else
			{
				*lpSrc=(unsigned char)0;
			}
		}
	}

	if(direction==0)  //水平方向投影
	{
		for(j = 0; j <lmageHeight; j++)
		{
			BlackNumber = 0;	//黑点数目置0
			for(i = 0;i <lmageWidth; i++)
			{
				// 指向源图像倒数第j行，第i个象素的指针			
				lpSrc = (unsigned char *)lpDIBBits + lmageWidth * j + i;
				//取得当前指针处的像素值，注意要转换为unsigned char型
				pixeltemp = (unsigned char)*lpSrc;
				if(pixeltemp == 0)//如果发现黑点
				{
					BlackNumber++; //黑点数目加1
				}
			}
			for(k = 0;k < BlackNumber ;k++)
			{	
				// 指向目标图像倒数第j行，第i个象素的指针			
				lpDst = (unsigned char *)lpImage + lmageWidth * j + k;
				*lpDst = (unsigned char)0; //置为黑点
			}	
		}
	}
	else if(direction==1)  //垂直方向投影
	{
		for(i = 0;i <lmageWidth; i++)
		{
			BlackNumber = 0;	//黑点数目置0
			for(j = 0; j <lmageHeight; j++)
			{
				// 指向源图像倒数第j行，第i个象素的指针			
				lpSrc = (unsigned char *)lpDIBBits + lmageWidth * j + i;
				//取得当前指针处的像素值，注意要转换为unsigned char型
				pixeltemp = (unsigned char)*lpSrc;
				if(pixeltemp == 0)//如果发现黑点
				{
					BlackNumber++; //黑点数目加1
				}
			}
			for(k = 0;k < BlackNumber ;k++)
			{	
				// 指向目标图像倒数第j行，第i个象素的指针			
				lpDst = (unsigned char *)lpImage + lmageWidth * k + i;
				*lpDst = (unsigned char)0; //置为黑点
			}	
		}
	}
	// 复制区域生长后的图像
	memcpy(lpDIBBits, lpImage, lmageWidth * lmageHeight);
	// 释放内存
	delete[] lpImage;
	// 返回
	return TRUE;
}

/*************************************************************************
 * 函数名称：
 *   Subtract()
 * 参数:
 *   LPSTR lpDIBBits1   - 指向源DIB图像指针
 *   LPSTR lpDIBBits2   - 指向背景DIB图像指针
 *   LONG  lmageWidth       - 源图像宽度（象素数，必须是4的倍数）
 *   LONG  lmageHeight      - 源图像高度（象素数）
 *
 * 返回值:
 *   BOOL               - 运算成功返回TRUE，否则返回FALSE。
 * 说明:
 * 该函数用于对两幅图像进行差影运算。
 * 要求目标图像为255个灰度值的灰度图像。
 ************************************************************************/

BOOL Subtract(LPSTR lpDIBBits1, LPSTR lpDIBBits2, LONG lmageWidth, LONG lmageHeight)
{
	// 临时存放图像数据的指针
	LPBYTE			lpImage;	
	// 指向源图像的指针
	unsigned char*	lpSrc1;
	// 指向背景图像的指针
	unsigned char*	lpSrc2;
	// 指向要复制区域的指针
	unsigned char*	lpDst;
	//像素值
	unsigned char pixeltemp1;
	unsigned char pixeltemp2;
	// 分配内存
	lpImage = (LPBYTE) new  char[lmageWidth*lmageHeight];	
	// 判断是否内存分配失败
	if (lpImage == NULL)
	{
		// 分配内存失败
		return FALSE;
	}
	// 将目标图像所有像素初始化为白点
	lpDst = (unsigned char *)lpImage;
	memset(lpDst, (BYTE)255, lmageWidth * lmageHeight);

	//循环变量
	int i;
	int j;
	for(j = 0; j <lmageHeight; j++)
	{
		for(i = 0;i <lmageWidth; i++)
		{
			// 指向源图像倒数第j行，第i个象素的指针			
			lpSrc1 = (unsigned char *)lpDIBBits1 + lmageWidth * j + i;
			// 指向背景图像倒数第j行，第i个象素的指针			
			lpSrc2 = (unsigned char *)lpDIBBits2 + lmageWidth * j + i;
			// 指向缓冲图像倒数第j行，第i个象素的指针			
			lpDst = (unsigned char *)lpImage + lmageWidth * j + i;
			//取得源图像当前指针处的像素值，注意要转换为unsigned char型
			pixeltemp1 = (unsigned char)*lpSrc1;
			//取得背景图像当前指针处的像素值，注意要转换为unsigned char型
			pixeltemp2 = (unsigned char)*lpSrc2;
			//进行差影运算
			if(pixeltemp1-pixeltemp2<0)
			{
				*lpDst =0;
			}
			else
			{
				*lpDst =pixeltemp1 - pixeltemp2;
			}		
		}
	}

	// 复制区域生长后的图像
	memcpy(lpDIBBits1, lpImage, lmageWidth * lmageHeight);
	// 释放内存
	delete[] lpImage;
	// 返回
	return TRUE;
}


/*************************************************************************
 * 函数名称：
 *   TemplateMatch()
 * 参数:
 *   LPSTR lpDIBBits1    - 指向源DIB图像指针
 *   LPSTR lpDIBBits2    - 指向模板DIB图像指针
 *   LONG  lmageWidth    - 源图像宽度（象素数，必须是4的倍数）
 *   LONG  lmageHeight   - 源图像高度（象素数）
 *   LONG  TemplateWidth       - 模板图像宽度（象素数，必须是4的倍数）
 *   LONG  TemplateHeight      - 模板图像高度（象素数）
 * 返回值:
 *   BOOL               - 运算成功返回TRUE，否则返回FALSE。
 * 说明:
 * 该函数用于对图像进行模板匹配运算。
 * 要求目标图像为255个灰度值的灰度图像。
 ************************************************************************/

BOOL TemplateMatch(LPSTR lpDIBBits1, LPSTR lpDIBBits2,  LONG lmageWidth, LONG lmageHeight,
							  LONG TemplateWidth,LONG TemplateHeight)
{	
	// 临时存放图像数据的指针
	LPBYTE			lpImage;	
	// 指向源图像的指针
	unsigned char*	lpSrc1;
	// 指向模板图像的指针
	unsigned char*	lpSrc2;
	// 指向要复制区域的指针
	unsigned char*	lpDst;
	//像素值
	unsigned char pixeltemp1;//源图像像素
	unsigned char pixeltemp2;//模板图像像素
	// 分配内存
	lpImage = (LPBYTE) new  char[lmageWidth*lmageHeight];	
	// 判断是否内存分配失败
	if (lpImage == NULL)
	{
		// 分配内存失败
		return FALSE;
	}
	// 将目标图像所有像素初始化为灰白点
	lpDst = (unsigned char *)lpImage;
	memset(lpDst, (BYTE)205, lmageWidth * lmageHeight);
	//循环变量
	int i;
	int j;
	int m;
	int n;
	int cofT;//模板像素自相关值
	int cofS;//源像素自相关值
	int cofTS;//模板、源图像像素灰度互相关值
	double R;//测度R
	double Rmax;//最大测度
	CPoint matchpoint;//匹配点
	//计算cofT
	cofT = 0;
	for(j = 0; j <TemplateHeight; j++)
	{
		for(i = 0;i <TemplateWidth; i++)
		{
			// 指向模板图像倒数第j行，第i个象素的指针			
			lpSrc2 = (unsigned char *)lpDIBBits2 + lmageWidth * j + i;
			//取得模板图像当前指针处的像素值，注意要转换为unsigned char型
			pixeltemp2 = (unsigned char) *lpSrc2;
			//进行自相关运算
			cofT=cofT+pixeltemp2*pixeltemp2;
		}
	}

	//找到图像中最大相似性的出现位置
	Rmax = 0.0;
	for (j = 0;j < lmageHeight - TemplateHeight +1 ;j++)
	{
		for(i = 0;i < lmageWidth - TemplateWidth + 1;i++)
		{
			cofS = 0; //初始化为0
			cofTS = 0;//初始化为0

			for (n = 0;n < TemplateHeight ;n++)
			{
				for(m = 0;m < TemplateWidth ;m++)
				{
					// 指向源图像倒数第j+n行，第i+m个象素的指针			
					lpSrc1 = (unsigned char *)lpDIBBits1+ lmageWidth * (j+n) + (i+m);
					// 指向模板图像倒数第n行，第m个象素的指针			
					lpSrc2 = (unsigned char *)lpDIBBits2 + TemplateWidth * n + m;
					//获取
					pixeltemp1 = (unsigned char)*lpSrc1;
					pixeltemp2 = (unsigned char)*lpSrc2;

					cofS = cofS+(double)pixeltemp1*pixeltemp1;
					cofTS = cofTS+(double)pixeltemp1*pixeltemp2;
				}
			}
			//计算相似性
			R = cofTS / ( sqrt(cofS)*sqrt(cofT));
			//与最大相似性比较
			if (R > Rmax)
			{
				Rmax = R;
				matchpoint.x = i;
				matchpoint.y = j;
			}
		}
	}
	

	//将源图像中与模板图像匹配的像素区域复制到目标图像
	for (n = 0;n < TemplateHeight ;n++)
	{
		for(m = 0;m < TemplateWidth ;m++)
		{
			lpSrc1 = (unsigned char *)lpDIBBits1 + lmageWidth  * (n+matchpoint.y) + (m+matchpoint.x);
			lpDst = (unsigned char *)lpImage + lmageWidth  * (n+matchpoint.y) + (m+matchpoint.x);
			*lpDst = *lpSrc1;
		}
	}	
	// 复制图像
	memcpy(lpDIBBits1, lpImage, lmageWidth * lmageHeight);
	// 释放内存
	delete[] lpImage;
	// 返回
	return TRUE;
}


/*************************************************************************
 * 函数名称：
 *	 PCXCoding()
 * 参数:
 *   LPSTR   lpDIBBits  - 指向DIB对象像素的指针
 *   LONG  ImageWidth   - 源图像宽度（象素数，必须是4的倍数）
 *   LONG  ImageHeight  - 源图像高度（象素数）
 *   CFile& file        - 要保存的文件
 * 返回值:
 *   BOOL               - 成功返回True，否则返回False。
 * 说明:
 *   该函数将指定的256色DIB对象保存为256色PCX文件。
 *************************************************************************/
BOOL PCXCoding(LPSTR  lpDIBBits, LONG  ImageWidth, LONG  ImageHeight, CFile& file)
{
	typedef struct{
              		char manufacturer;
             		char version;
              		char encoding;
              		char bits_per_pixel;
              		WORD xmin,ymin;
               		WORD xmax,ymax;
               		WORD hres;
               		WORD vres;
               		char palette[48];
               		char reserved;
               		char colour_planes;
              		WORD bytes_per_line;
               		WORD palette_type;
               		char filler[58];
      				} PCXHEAD;

	// 循环变量
	int	i;
	int	j;
	// 中间变量
	BYTE	bChar1;
	BYTE	bChar2;
	
	// 指向源图像象素的指针
	BYTE *	lpSrc;	
	// 指向编码后图像数据的指针
	BYTE *	lpDst;	
	// 重复像素计数
	int		iCount;	
	// 缓冲区已使用的字节数
	DWORD	dwBuffUsed;
	// PCX文件头
	PCXHEAD pcxHeadr;	
	// PCX标识码
	pcxHeadr.manufacturer = 0x0A;	
	// PCX版本号
	pcxHeadr.version = 5;
	// PCX编码方式（1表示RLE编码）
	pcxHeadr.encoding = 1;
	// 像素位数（256色为8位）
	pcxHeadr.bits_per_pixel = 8;
	// 图像相对于屏幕的左上角X坐标（以像素为单位）
	pcxHeadr.xmin = 0;
	// 图像相对于屏幕的左上角Y坐标（以像素为单位）
	pcxHeadr.ymin = 0;
	// 图像相对于屏幕的右下角X坐标（以像素为单位）
	pcxHeadr.xmax = ImageWidth - 1;
	// 图像相对于屏幕的右下角Y坐标（以像素为单位）
	pcxHeadr.ymax = ImageHeight - 1;
	// 图像的水平分辨率
	pcxHeadr.hres = ImageWidth;
	// 图像的垂直分辨率
	pcxHeadr.vres = ImageHeight;
	// 调色板数据（对于256色PCX无意义，直接赋值为0）
	for (i = 0; i < 48; i ++)
	{
		pcxHeadr.palette[i] = 0;
	}	
	// 保留域，设定为0。
	pcxHeadr.reserved = 0;	
	// 图像色彩平面数目（对于256色PCX设定为1）。
	pcxHeadr.colour_planes = 1;	
	// 图像的宽度（字节为单位），必须为偶数。
	pcxHeadr.bytes_per_line = ImageWidth;
	// 图像调色板的类型，1表示彩色或者单色图像，2表示图像是灰度图。
	pcxHeadr.palette_type = 1;
	// 制作该图像的屏幕宽度（像素为单位）
//	pcxHeadr.wSrcWidth = 0;
	// 制作该图像的屏幕高度（像素为单位）
//	pcxHeadr.wSrcDepth = 0;
	// 保留域，取值设定为0。
	for (i = 0; i < 54; i ++)
	{
		pcxHeadr.filler[i] = 0;
	}	
	// 写入文件头
	file.Write((LPSTR)&pcxHeadr, sizeof(PCXHEAD));
	// 开始编码
	
	// 开辟一片缓冲区(2被原始图像大小)以保存编码结果
	lpDst = new BYTE[ImageHeight * ImageWidth * 2];
	// 指明当前已经用了多少缓冲区（字节数）
	dwBuffUsed = 0;	
	// 每行
	for (i = 0; i < ImageHeight; i++)
	{
		// 指向DIB第i行，第0个象素的指针
		lpSrc = (BYTE *)lpDIBBits + ImageWidth * (ImageHeight - 1 - i);	
		// 给bChar1赋值
		bChar1 = *lpSrc;	
		// 设置iCount为1
		iCount = 1;
		// 剩余列
		for (j = 1; j < ImageWidth; j ++)
		{
			// 指向DIB第i行，第j个象素的指针
			lpSrc++;
			// 读取下一个像素
			bChar2 = *lpSrc;
			// 判断是否和bChar1相同并且iCount < 63
			if ((bChar1 == bChar2) && (iCount < 63))
			{
				// 相同，计数加1
				iCount ++;	
				// 继续读下一个
			}
			else
			{
				// 不同，或者iCount = 63	
				// 写入缓冲区
				if ((iCount > 1) || (bChar1 >= 0xC0))
				{
					// 保存码长信息
					lpDst[dwBuffUsed] = iCount | 0xC0;
					// 保存bChar1
					lpDst[dwBuffUsed + 1] = bChar1;
					// 更新dwBuffUsed
					dwBuffUsed += 2;
				}
				else
				{
					// 直接保存该值
					lpDst[dwBuffUsed] = bChar1;
					// 更新dwBuffUsed
					dwBuffUsed ++;
				}	
				// 重新给bChar1赋值
				bChar1 = bChar2;
				// 设置iCount为1
				iCount = 1;
			}
		}
		
		// 保存每行最后一部分编码
		if ((iCount > 1) || (bChar1 >= 0xC0))
		{
			// 保存码长信息
			lpDst[dwBuffUsed] = iCount | 0xC0;	
			// 保存bChar1
			lpDst[dwBuffUsed + 1] = bChar1;
			// 更新dwBuffUsed
			dwBuffUsed += 2;
		}
		else
		{
			// 直接保存该值
			lpDst[dwBuffUsed] = bChar1;	
			// 更新dwBuffUsed
			dwBuffUsed ++;
		}
	}
	// 写入编码结果
	file.Write((LPSTR)lpDst, dwBuffUsed);
	// 释放内存
	delete[] lpDst;	
	// 开辟一片缓冲区以保存调色板
	lpDst = new BYTE[769];
	// 调色板起始字节
	* lpDst = 0x0C;
	for (i = 0; i < 256; i ++)
	{	
		// 读取DIB调色板红色分量
		lpDst[i * 3 + 1] = i;	
		// 读取DIB调色板绿色分量
		lpDst[i * 3 + 2] = i;	
		// 读取DIB调色板蓝色分量
		lpDst[i * 3 + 3] = i;
	}
	// 写入调色板信息
	file.Write((LPSTR)lpDst, 769);
	// 返回
	return TRUE;
}



typedef struct gifc_var// GIF编码参数
   {
      LPSTR lpDataBuff;
      LPSTR lpEndBuff;
      DWORD dwTempCode;
      WORD  wWidth;
      WORD  wDepth;
      WORD  wLineBytes;
      WORD  wBits;
      WORD  wByteCnt;
      WORD  wBlockNdx;
      BYTE  byLeftBits;
   }  GIFC_VAR;
typedef GIFC_VAR FAR *LPGIFC_VAR;
// 宏运算
#define DWORD_WBYTES(x)         ( (((x) + 31UL) >> 5) << 2 )
#define WORD_WBYTES(x)          ( (((x) + 15UL) >> 4) << 1 )
#define BYTE_WBYTES(x)          (  ((x) +  7UL) >> 3       )
/*************************************************************************
* 函数名称：
 *  WriteCode()
* 参数:
 *   CFile& file			- 要保存的文件
 *	 WORD wCode			- 要添加的编码
 *   LPSTR lpSubBlock		- 子块
 *	 LPBYTE lpbyCurrentBits	- 当前位数
 *	 LPGIFC_VAR lpGIFCVar	- 指向GIFC_VAR结构的指针
* 返回值:
 *   无
* 说明:
 *   该函数用来输出一个编码。
*************************************************************************/
void WriteCode(CFile& file, WORD wCode, LPSTR lpSubBlock,LPBYTE 
lpbyCurrentBits,LPGIFC_VAR lpGIFCVar)
{	
// 输出该编码
	lpGIFCVar->dwTempCode |= ((DWORD)wCode << lpGIFCVar->byLeftBits);
	lpGIFCVar->byLeftBits += (*lpbyCurrentBits);
	while(lpGIFCVar->byLeftBits >= 0x08)
	{
		lpSubBlock[lpGIFCVar->wBlockNdx++] = (BYTE)lpGIFCVar->dwTempCode;
		// 判断是否超出MAX_SUBBLOCK_SIZE即255
		if (lpGIFCVar->wBlockNdx > 255)
		{
			// 判断wByteCnt + 256是否超过MAX_BUFF_SIZE-32768
			if ((lpGIFCVar->wByteCnt + 256) >= 32768)
			{
				// 输出
				file.Write(lpGIFCVar->lpDataBuff,lpGIFCVar->wByteCnt);
	              lpGIFCVar->lpEndBuff = lpGIFCVar->lpDataBuff;
		        	lpGIFCVar->wByteCnt  = 0;
			}
			lpSubBlock[0] = (BYTE)(lpGIFCVar->wBlockNdx - 1);
			memcpy(lpGIFCVar->lpEndBuff,lpSubBlock,lpGIFCVar->wBlockNdx);
			lpGIFCVar->lpEndBuff += lpGIFCVar->wBlockNdx;
			lpGIFCVar->wByteCnt += lpGIFCVar->wBlockNdx;
			lpGIFCVar->wBlockNdx  = 1;
		}
		lpGIFCVar->dwTempCode >>= 8;
		lpGIFCVar->byLeftBits  -= 0x08;
	}
	return;												// 返回
}

/*************************************************************************
* 函数名称：
 *   CodingGIFLZW()
* 参数:
 *   LPSTR lpDIBBits		- 指向源DIB图像指针
 *   CFile& file			- 要保存的文件
 *   LPGIFC_VAR lpGIFCVar	- 指向GIFC_VAR结构的指针
 *	 WORD wWidthBytes		- 每行图像字节数
 *	 BOOL bInterlace		- 是否按照交错方式保存
* 返回值:
 *   无
* 说明:
 *   该函数对指定图像进行GIF_LZW编码。
*************************************************************************/

void  CodingGIFLZW(LPSTR lpDIBBits, CFile& file, LPGIFC_VAR lpGIFCVar,WORD wWidthBytes, 
				  BOOL bInterlace)
{
	HANDLE hTableNdx;									// 内存分配句柄
	HANDLE hPrefix;									// 内存分配句柄
	HANDLE hSuffix;									// 内存分配句柄
	LPWORD lpwTableNdx;								// 指向字串表指针
	LPWORD lpwPrefix;									// 用于字串表搜索的索引
	LPBYTE lpbySuffix;									// 用于字串表搜索的索引
	LPSTR  lpImage;									// 指向当前编码像素的指针
	DWORD  dwDataNdx;								// 计算当前数据图像的偏移量
	WORD   wLZW_CLEAR;								// LZW_CLEAR
	WORD   wLZW_EOI;								// LZW_EOI
	BYTE   byLZW_MinCodeLen;							// LZW_MinCodeLen
	WORD   wPreTableNdx;								// 字串表索引
	WORD   wNowTableNdx;								// 字串表索引
	WORD   wTopTableNdx;								// 字串表索引
	WORD   wHashNdx;									// 哈希表索引
	WORD   wHashGap;									// 哈希表索引
	WORD   wPrefix;								
	WORD   wRowNum;								// 当前图像的行数
	WORD   wWidthCnt;								// 当前图像的列数
	WORD   wi;										// 循环变量
	WORD   wj;									// 循环变量
	WORD   wIncTable[5]  = { 8,8,4,2,0 }; 				// 交错方式存储时每次增加的行数 
	WORD   wBgnTable[5]  = { 0,4,2,1,0 }; 				// 交错方式存储时起始行数
	BOOL   bStart;									// 开始标志
	BYTE   bySuffix;
	BYTE   bySubBlock[256];
	BYTE   byCurrentBits;
	BYTE   byPass;
	BYTE   byTemp;								// 临时字节变量
	hTableNdx = GlobalAlloc(GHND,(DWORD)(5051<<1));		// 给字串表分配内存
	hPrefix = GlobalAlloc(GHND,(DWORD)(5051<<1));		// 给字串表分配内存
	hSuffix = GlobalAlloc(GHND,(DWORD)5051);			// 给字串表分配内存
	lpwTableNdx = (LPWORD)GlobalLock(hTableNdx);		// 锁定内存
	lpwPrefix  = (LPWORD)GlobalLock(hPrefix);			// 锁定内存
	lpbySuffix  = (LPBYTE)GlobalLock(hSuffix);			// 锁定内存
	// 计算LZW_MinCodeLen
	byLZW_MinCodeLen = (BYTE)((lpGIFCVar->wBits>1) ? lpGIFCVar->wBits : 0x02);
	file.Write((LPSTR)&byLZW_MinCodeLen,1);			// 写GIF LZW最小代码大小
	wRowNum  = 0;								// 初始化
	bStart  = TRUE;								// 初始化
	byPass = 0x00;									// 初始化
	wLZW_CLEAR = 1 << byLZW_MinCodeLen;			// 计算LZW_CLEAR
	wLZW_EOI = wLZW_CLEAR + 1;					// 计算LZW_EOI
	byCurrentBits = byLZW_MinCodeLen + (BYTE)0x01;		// 初始化字串表
	wNowTableNdx = wLZW_CLEAR + 2;					// 初始化字串表
	wTopTableNdx  = 1 << byCurrentBits;					// 初始化字串表
	for(wi=0; wi<5051; wi++)
	{
		*(lpwTableNdx+wi) = 0xFFFF;					// 初始化为0xFFFF
	}	
	// 输出LZW_CLEAR
	WriteCode(file, wLZW_CLEAR, (LPSTR)bySubBlock,&byCurrentBits, lpGIFCVar);	
	for(wi=0; wi<lpGIFCVar->wDepth; wi++)				// 逐行编码
	{
		// 计算当前偏移量
		dwDataNdx  = (DWORD)(lpGIFCVar->wDepth - 1 - wRowNum) * (DWORD)wWidthBytes;
		// 指向当前行图像的指针
		lpImage = (LPSTR) (((BYTE*)lpDIBBits) + dwDataNdx);	
		wWidthCnt = 0;
		if (bStart)
		{
			byTemp = *lpImage++;					// 256色图像，直接赋值即可
			wPrefix    = (WORD)byTemp;
			bStart     = FALSE;
			wWidthCnt ++;
		}
		while(wWidthCnt < lpGIFCVar->wWidth)				// 每行编码
		{
			byTemp = *lpImage++;						// 256色，直接赋值即可
			bySuffix   = byTemp;
			wWidthCnt ++;
			// 查找当前字符串是否存在于字串表中
			wHashNdx = wPrefix ^ ((WORD)bySuffix << 4);
			wHashGap = (wHashNdx ? (5051 - wHashNdx) : 1);
			while(TRUE)								// 判断当前字符串是否在字串表中
			{
				if (*(lpwTableNdx + wHashNdx) == 0xFFFF)		// 当前字符串不在字串表中
				{
				   break;								// 新字符串，退出循环
				}
				// 判断是否找到该字符串
				if ((*(lpwPrefix+wHashNdx)  == wPrefix) &&(*(lpbySuffix+wHashNdx) == bySuffix))
				{
					break;							// 找到，退出循环
				}
				if (wHashNdx < wHashGap)					// 第二哈希表
				{
					wHashNdx += 5051;
				}
				wHashNdx -= wHashGap;
			}
			if (*(lpwTableNdx+wHashNdx) != 0xFFFF)			// 判断是否是新字符串
			{
				wPrefix = *(lpwTableNdx + wHashNdx);		// 不是新字符串
			 }
			 else
			 {
				// 新字符串，输出该编码
				WriteCode(file,wPrefix,(LPSTR)bySubBlock,&byCurrentBits,lpGIFCVar);
				wPreTableNdx = wNowTableNdx;			// 将该新字符串添加到字串表中
				if (wNowTableNdx < 4096)					// 判断是否达到最大字串表大小
				{
					*(lpwTableNdx+wHashNdx) = wNowTableNdx++;
					*(lpwPrefix+wHashNdx)   = wPrefix;
					*(lpbySuffix+wHashNdx)  = bySuffix;
				}
				if (wPreTableNdx == wTopTableNdx)
				{
					if (byCurrentBits<12)
					{
						byCurrentBits ++;
						wTopTableNdx <<= 1;
					}
					else								// 字串表到达最大长度
					{
						// 输出LZW_CLEAR
						WriteCode(file, wLZW_CLEAR, (LPSTR)bySubBlock,
										 &byCurrentBits,lpGIFCVar);
						// 重新初始化字串表
						byCurrentBits = byLZW_MinCodeLen + (BYTE)0x01;
						wLZW_CLEAR = 1 << byLZW_MinCodeLen;
						wLZW_EOI = wLZW_CLEAR + 1;
						wNowTableNdx = wLZW_CLEAR + 2;
						wTopTableNdx = 1 << byCurrentBits;
						for(wj=0;wj<5051;wj++)
						{
							*(lpwTableNdx+wj) = 0xFFFF;		// 初始化为0xFFFF
						}
					}
				}
				wPrefix = (WORD)bySuffix;
			}
		}
		if (bInterlace)										// 判断是否是交错方式
		{
			wRowNum += wIncTable[byPass];					// 交错方式，计算下一行位置
			if (wRowNum>=lpGIFCVar->wDepth)
			{
				byPass ++;
				wRowNum = wBgnTable[byPass];
			}
		}
		else
		{
			wRowNum ++;									// 非交错方式，直接行数加一	
		}
	}
	// 输出当前编码
	WriteCode(file, wPrefix, (LPSTR)bySubBlock,&byCurrentBits,lpGIFCVar);
	// 输出LZW_EOI
	WriteCode(file,wLZW_EOI,(LPSTR)bySubBlock,&byCurrentBits,lpGIFCVar);
	if (lpGIFCVar->byLeftBits)
	{
		// 加入该字符
		bySubBlock[lpGIFCVar->wBlockNdx++] = (BYTE)lpGIFCVar->dwTempCode;
		// 判断是否超出MAX_SUBBLOCK_SIZE
		if (lpGIFCVar->wBlockNdx > 255)
		{
			// 判断wByteCnt + 256是否超过MAX_BUFF_SIZE
			if ((lpGIFCVar->wByteCnt + 256) >= 32768)
			{
				// 输出
				file.Write(lpGIFCVar->lpDataBuff,lpGIFCVar->wByteCnt);
				lpGIFCVar->lpEndBuff = lpGIFCVar->lpDataBuff;
				lpGIFCVar->wByteCnt  = 0;
			}
			bySubBlock[0] = (BYTE)(lpGIFCVar->wBlockNdx - 1);
			memcpy(lpGIFCVar->lpEndBuff,(LPSTR)bySubBlock,lpGIFCVar->wBlockNdx);
			lpGIFCVar->lpEndBuff+= lpGIFCVar->wBlockNdx;
			lpGIFCVar->wByteCnt += lpGIFCVar->wBlockNdx;
			lpGIFCVar->wBlockNdx = 1;
		}
		lpGIFCVar->dwTempCode = 0UL;
		lpGIFCVar->byLeftBits = 0x00;
	}
	if (lpGIFCVar->wBlockNdx > 1)
	{
		// 判断wByteCnt + 256是否超过MAX_BUFF_SIZE
		if ((lpGIFCVar->wByteCnt + 256) >= 32768)
		{
			// 输出
			file.Write(lpGIFCVar->lpDataBuff,lpGIFCVar->wByteCnt);
			lpGIFCVar->lpEndBuff = lpGIFCVar->lpDataBuff;
			lpGIFCVar->wByteCnt  = 0;
		}
		bySubBlock[0] = (BYTE)(lpGIFCVar->wBlockNdx - 1);
		memcpy(lpGIFCVar->lpEndBuff,(LPSTR)bySubBlock,lpGIFCVar->wBlockNdx);
		lpGIFCVar->lpEndBuff += lpGIFCVar->wBlockNdx;
		lpGIFCVar->wByteCnt += lpGIFCVar->wBlockNdx;
		lpGIFCVar->wBlockNdx = 1;
	}
	GlobalUnlock(hTableNdx);								// 解除锁定
	GlobalUnlock(hPrefix);								// 解除锁定
	GlobalUnlock(hSuffix);								// 解除锁定
	GlobalFree(hTableNdx);								// 释放内存
	GlobalFree(hPrefix);									// 释放内存
	GlobalFree(hSuffix);									// 释放内存
	return;											// 退出
}

/*************************************************************************
* 函数名称：
 *   GIFLZW()
* 参数:
 *   LPSTR 	lpDIBBits     		- 指向DIB对象数据的指针
 *	 WORD  wWidth		   	- 指向DIB对象图像宽度
 *	 WORD 	wHeight			- 指向DIB对象图像高度
 *   CFile& file        			- 要保存的文件
 *   BOOL	bInterlace			- 是否按照交错方式保存
* 返回值:
 *   BOOL               - 成功返回True，否则返回False。
* 说明:
 *   该函数将指定的DIB对象（256色）保存为GIF文件。
*************************************************************************/
BOOL  GIFLZW(LPSTR lpDIBBits,WORD wWidth,WORD wHeight, CFile& file, BOOL bInterlace)
{
	int	i;											// 循环变量
	int	j;											// 循环变量
	typedef struct gifheader								// GIF文件头
   	{
      BYTE bySignature[3];								//GIF署名
      BYTE byVersion[3];									//版本号
   	}  GIFHEADER;
	typedef struct gifscrdesc								// GIF逻辑屏幕描述块
  	{
      WORD wWidth;									//逻辑屏幕宽度
      WORD wDepth;									//逻辑屏幕高度
      struct globalflag
         {
            BYTE PalBits   : 3;							//全局颜色列表大小
            BYTE SortFlag  : 1;							//分类标志
            BYTE ColorRes  : 3;							//颜色深度
            BYTE GlobalPal : 1;							//全局颜色列表标志
         }  GlobalFlag;
      BYTE byBackground;								//背景色
      BYTE byAspect;									//像素宽高比
   	}  GIFSCRDESC;
	typedef struct gifimage									// GIF图像标识符
   	{
      WORD wLeft;										//X方向偏移量
      WORD wTop;										//Y方向偏移量
      WORD wWidth;									//图象宽度
      WORD wDepth;									//图象高度
      struct localflag
         {
            BYTE PalBits   : 3;							//局部颜色列表大小
            BYTE Reserved  : 2;							//保留，必须初始化为0
            BYTE SortFlag  : 1;							//分类标志
            BYTE Interlace : 1;								//交织标志
            BYTE LocalPal  : 1;							//局部颜色列表标志
         }  LocalFlag;
   	}  GIFIMAGE;
	GIFHEADER          GIFH;							// GIF文件头
	GIFSCRDESC         GIFS;							// GIF逻辑屏幕描述块
	GIFIMAGE           GIFI;							// GIF图像描述块
	GIFC_VAR           GIFCVar;						// GIF编码参数
	WORD               wColors;						// 颜色数目
	BYTE               byGIF_Pal[768];					// 调色板
	BYTE               byChar;							// 字节变量
	GIFCVar.wWidth     = wWidth;						// 给GIFCVar结构赋值
	GIFCVar.wDepth     = wHeight;						// 给GIFCVar结构赋值
	GIFCVar.wBits      = 8;								// 给GIFCVar结构赋值
	GIFCVar.wLineBytes = (WORD)BYTE_WBYTES((DWORD)GIFCVar.wWidth *(DWORD)GIFCVar.wBits);
	WORD	wWidthBytes;								// 每行字节数
	wWidthBytes = (WORD)DWORD_WBYTES(wWidth * (DWORD)GIFCVar.wBits);
	wColors     = 256;									//颜色数目
	j = 0;
	for (i = 0; i < wColors; i++)
	{
		byGIF_Pal[j++] = i;								// 设置红色分量
		byGIF_Pal[j++] = i;								// 设置绿色分量
		byGIF_Pal[j++] = i;								// 设置蓝色分量
	}
	
	// 开始写GIF文件
	GIFH.bySignature[0] = 'G';								// 设置GIF文件头
	GIFH.bySignature[1] = 'I';								// 设置GIF文件头
	GIFH.bySignature[2] = 'F';								// 设置GIF文件头
	GIFH.byVersion[0]='8';								// 设置GIF文件头
	GIFH.byVersion[1]='9';								// 设置GIF文件头
	GIFH.byVersion[2]='a';								// 设置GIF文件头
	file.Write((LPSTR)&GIFH, 6);							// 写GIF文件头
	GIFS.wWidth = GIFCVar.wWidth;						// 设置GIF逻辑屏幕描述块参数
	GIFS.wDepth = GIFCVar.wDepth;						// 设置GIF逻辑屏幕描述块参数
	GIFS.GlobalFlag.PalBits   = (BYTE)(GIFCVar.wBits - 1);		// 设置GIF逻辑屏幕描述块参数
	GIFS.GlobalFlag.SortFlag  = 0x00;						// 设置GIF逻辑屏幕描述块参数
	GIFS.GlobalFlag.ColorRes  = (BYTE)(GIFCVar.wBits - 1);		// 设置GIF逻辑屏幕描述块参数
	GIFS.GlobalFlag.GlobalPal = 0x01;						// 设置GIF逻辑屏幕描述块参数
	GIFS.byBackground = 0x00;								// 设置GIF逻辑屏幕描述块参数
	GIFS.byAspect = 0x00;								// 设置GIF逻辑屏幕描述块参数
	file.Write((LPSTR)&GIFS, 7);							// 写GIF逻辑屏幕描述块
	file.Write((LPSTR)byGIF_Pal,(wColors*3));					// 写GIF全局调色板
	byChar      = 0x2C;
	file.Write((LPSTR)&byChar,1);							// 写GIF图像描述间隔符
	GIFI.wLeft = 0;										// 设置GIF图像描述块参数
	GIFI.wTop = 0;										// 设置GIF图像描述块参数
	GIFI.wWidth = GIFCVar.wWidth;						// 设置GIF图像描述块参数
	GIFI.wDepth = GIFCVar.wDepth;							// 设置GIF图像描述块参数
	GIFI.LocalFlag.PalBits = 0x00;							// 设置GIF图像描述块参数
	GIFI.LocalFlag.Reserved = 0x00;							// 设置GIF图像描述块参数
	GIFI.LocalFlag.SortFlag = 0x00;							// 设置GIF图像描述块参数
	GIFI.LocalFlag.Interlace = (BYTE)(bInterlace ? 0x01 : 0x00);		// 设置GIF图像描述块参数
	GIFI.LocalFlag.LocalPal  = 0x00;						// 设置GIF图像描述块参数
	file.Write((LPSTR)&GIFI, 9);							// 写GIF图像描述块
	// 写GIF图像压缩数据
	HANDLE hSrcBuff = GlobalAlloc(GHND,(DWORD)32768);		// 分配内存
	GIFCVar.lpDataBuff = (LPSTR)GlobalLock(hSrcBuff);
	GIFCVar.lpEndBuff  = GIFCVar.lpDataBuff;
	GIFCVar.dwTempCode = 0UL;							// 设置GIF图像压缩数据参数
	GIFCVar.wByteCnt   = 0;								// 设置GIF图像压缩数据参数
	GIFCVar.wBlockNdx  = 1;								// 设置GIF图像压缩数据参数
	GIFCVar.byLeftBits = 0x00;								// 设置GIF图像压缩数据参数
	CodingGIFLZW(lpDIBBits, file, &GIFCVar,wWidthBytes, bInterlace); // 进行GIF_LZW编码
	if (GIFCVar.wByteCnt)								// 判断是否编码成功
	{
		file.Write(GIFCVar.lpDataBuff, GIFCVar.wByteCnt);	// 写入文件
	}
	GlobalUnlock(hSrcBuff);							// 解除锁定
	GlobalFree(hSrcBuff);								// 释放内存
	byChar   = 0x00;
	file.Write((LPSTR)&byChar,1);						// 写GIF Block Terminator
	byChar   = 0x3B;
	file.Write((LPSTR)&byChar,1);						// 写GIF文件结尾块
	return TRUE;									// 返回
}



/////////////////////////////////////////////////
const double hCoef[10][20] =
{
	{ .707106781187,  .707106781187},

	{ .482962913145,  .836516303738,  .224143868042, -.129409522551 },

	{ .332670552950,  .806891509311,  .459877502118, -.135011020010, -.085441273882,  .035226291882 },

	{ .230377813309,  .714846570553,  .630880767930, -.027983769417,
	 -.187034811719,  .030841381836,  .032883011667, -.010597401785 },

	{ .160102397974,  .603829269797,  .724308528438,  .138428145901, -.242294887066,
	 -.032244869585,  .077571493840, -.006241490213, -.012580751999,  .003335725285 },

	{ .111540743350,  .494623890398,  .751133908021,  .315250351709, -.226264693965,
	 -.129766867567,  .097501605587,  .027522865530, -.031582039318,  .000553842201,
	  .004777257511, -.001077301085 },

	{ .077852054085,  .396539319482,  .729132090846,  .469782287405, -.143906003929,
	 -.224036184994,  .071309219267,  .080612609151, -.038029936935, -.016574541631,
	  .012550998556,  .000429577973, -.001801640704,  .000353713800 },

	{ .054415842243,  .312871590914,  .675630736297,  .585354683654, -.015829105256,
	 -.284015542962,  .000472484574,  .128747426620, -.017369301002, -.044088253931,
	  .013981027917,  .008746094047, -.004870352993, -.000391740373,  .000675449406,
	 -.000117476784 },

	{ .038077947364,  .243834674613,  .604823123690,  .657288078051,  .133197385825,
	 -.293273783279, -.096840783223,  .148540749338,  .030725681479, -.067632829061,
	  .000250947115,  .022361662124, -.004723204758, -.004281503682,  .001847646883,
	  .000230385764, -.000251963189,  .000039347320 },

	{ .026670057901,  .188176800078,  .527201188932,  .688459039454,  .281172343661,
	 -.249846424327, -.195946274377,  .127369340336,  .093057364604, -.071394147166,
	 -.029457536822,  .033212674059,  .003606553567, -.010733175483,  .001395351747,
	  .001992405295, -.000685856695, -.000116466855,  .000093588670, -.000013264203 }
};
/*************************************************************************
 *
 * \函数名称：
 *   DWTStep_1D()
 *
 * \输入参数:
 *   double * pDbSrc		- 指向源数据的指针
 *   int nCurLevel		- 当前分界的层数
 *   int nInv			- 是否为DWT，1表示为IDWT，0表示DWT
 *   int nStep			- 当前的计算层数
 *   int nSupp			- 小波基的紧支集的长度
 *
 * \返回值:
 *   BOOL			- 成功则返回TRUE，否则返回FALSE
 *
 * \说明:
 *   该函数用对存放在pDBSrc中的数据进行一层的一维DWT或者IDWT。其中，nInv为表示进行
 *   DWT或者IDWT的标志。nCurLevel为当前需要进行分界的层数。nStep为已经分界的层数
 *   计算后数据仍存放在pDbSrc中
 *
 *************************************************************************
 */
BOOL DWTStep_1D(double* pDbSrc, int nCurLevel,
			int nInv, int nStep,int nSupp)
{
	double s = sqrt(2);
	// 获得小波基的指针
	double* h = (double*)hCoef[nSupp-1];
	// 确认当前层数有效
	ASSERT(nCurLevel>=0);

	// 计算当前层数的长度
	int CurN = 1<<nCurLevel;
	if (nInv) CurN <<= 1;

	// 确认所选择的小波基和当前层数的长度有效
	if (nSupp<1 || nSupp>10 || CurN<2*nSupp) 
		return FALSE;

	// 分配临时内存用于存放结果
	double *ptemp = new double[CurN];
	if (!ptemp) return FALSE;

	double	s1, s2;
	int	Index1, Index2;

	// 判断是进行DWT还是IDWT
	if (!nInv)
	{	// DWT
		Index1=0;
		Index2=2*nSupp-1;
		
		// 进行卷积，其中s1为低频部分，s2为高频部分的结果
		for (int i=0; i<CurN/2; i++)
		{	
			s1 = s2 = 0;
			double t = -1;
			for (int j=0; j<2*nSupp; j++, t=-t)
			{
				s1 += h[j]*pDbSrc[(Index1 & CurN-1) * nStep];
				s2 += t*h[j]*pDbSrc[(Index2 & CurN-1) * nStep];

				Index1++;
				Index2--;
			}

			// 将结果存放在临时内存中
			ptemp[i] = s1/s;
			ptemp[i+CurN/2] = s2/s;

			Index1 -= 2*nSupp;
			Index2 += 2*nSupp;
			Index1 += 2;
			Index2 += 2;
		}
	}

	// 否则进行IDWT
	else
	{	// IDWT
		Index1 = CurN/2;
		Index2 = CurN/2-nSupp+1;
		
		// 进行卷积，其中其中s1为低频部分，s2为高频部分的结果
		for (int i=0; i<CurN/2; i++)
		{
			s1 = s2 = 0;
			int Index3 = 0;
			for (int j=0; j<nSupp; j++)
			{
					s1 += h[Index3]*pDbSrc[(Index1 & CurN/2-1) * nStep]
						 +h[Index3+1]*pDbSrc[((Index2 & CurN/2-1) + CurN/2) * nStep];
					s2 += h[Index3+1]*pDbSrc[(Index1 & CurN/2-1) * nStep]
						 -h[Index3]*pDbSrc[((Index2 & CurN/2-1) + CurN/2) * nStep];
					
					Index3+=2;
					Index1--,		Index2++;
			}

			// 将结果存入临时内存
			ptemp[2*i] = s1*s;
			ptemp[2*i+1] = s2*s;

			Index1 += nSupp;
			Index2 -= nSupp;
			Index1++;
			Index2++;
		}
	}
	
	// 将结果存入源图象中
	for (int i=0; i<CurN; i++)
		pDbSrc[i*nStep] = ptemp[i];

	// 释放临时内存，并返回
	delete[] ptemp;
	return TRUE;
}

/*************************************************************************
 *
 * \函数名称：
 *   DWTStep_2D()
 *
 * \输入参数:
 *   double * pDbSrc		- 指向源数据的指针
 *   int nCurWLevel		- X方向上当前分解的层数
 *   int nCurHLevel		- Y方向上当前分解的层数
 *   int nMaxWLevel		- X方向上最大可分解的层数
 *   int nMaxHLevel		- Y方向上最大可分解的层数
 *   int nInv			- 是否为DWT，1表示为IDWT，0表示DWT
 *   int nStep			- 当前的计算层数
 *   int nSupp			- 小波基的紧支集的长度
 *
 * \返回值:
 *   BOOL			- 成功则返回TRUE，否则返回FALSE
 *
 * \说明:
 *   该函数用对存放在pDBSrc中的数据进行一层的二维DWT或者IDWT。
 *   计算后数据仍存放在pDbSrc中
 *
 *************************************************************************
 */
BOOL DWTStep_2D(double* pDbSrc, int nCurWLevel, int nCurHLevel,
		int nMaxWLevel, int nMaxHLevel, int nInv, int nStep, int nSupp)
{
	// 计算图象的长度和宽度（2次幂对齐）
	int W = 1<<nMaxWLevel, H = 1<<nMaxHLevel;

	// 计算当前分解的图象的长度和宽度
	int CurW = 1<<nCurWLevel, CurH = 1<<nCurHLevel;

	// 判断是进行DWT还是IDWT
	if (!nInv)
	{	// 对行进行一维DWT
		for (int i=0; i<CurH; i++)
			if (!DWTStep_1D(pDbSrc+(int)i*W*nStep, nCurWLevel, nInv, nStep, nSupp)) return FALSE;
		// 对列进行一维DWT
		for (int i=0; i<CurW; i++)
			if (!DWTStep_1D(pDbSrc+i*nStep, nCurHLevel, nInv, W*nStep, nSupp)) return FALSE;
	}

	// 否则进行IDWT
	else
	{
		// 计算当前变换的图象的长度和宽度
		CurW <<= 1;
		CurH <<= 1;

		// 对列进行IDWT
		for (int i=0; i<CurW; i++)
			if (!DWTStep_1D(pDbSrc+i*nStep, nCurHLevel, nInv, W*nStep, nSupp)) return FALSE;
		// 对行进行IDWT
		for (int i=0; i<CurH; i++)
			if (!DWTStep_1D(pDbSrc+(int)i*W*nStep, nCurWLevel, nInv, nStep, nSupp)) return FALSE;
	}

	// 返回
	return TRUE;
}


/*************************************************************************
 *
 * \函数名称：
 *   FloatToByte()
 *
 * \输入参数:
 *   double  f			- 输入双精度变量
 *
 * \返回值:
 *   BYTE			- 返回比特型变量
 *
 * \说明:
 *   该函数将输入的双精度变量转换为BYTE型的变量
 *
 *************************************************************************
 */
BYTE FloatToByte(double f)
{
	if (f<=0) return (BYTE)0;
	else if (f>=255) return (BYTE)255;
	else return (BYTE)(f+0.5);
}

/*************************************************************************
 *
 * \函数名称：
 *   FloatToChar()
 *
 * \输入参数:
 *   double  f			- 输入双精度变量
 *
 * \返回值:
 *   Char			- 返回字符变量
 *
 * \说明:
 *   该函数将输入的双精度变量转换为Char型的变量
 *
 *************************************************************************
 */
char FloatToChar(double f)
{
	if (f>=0)
		if (f>=127.0)
			return (char)127;
		else return (char)(f+0.5);
	else
		if (f<=-128)
			return (char)-128;
		else return -(char)(-f+0.5);
}

/*************************************************************************
 *
 * \函数名称：
 *   Log2()
 *
 * \输入参数:
 *   int  n			- 输入整型变量
 *
 * \返回值:
 *   int			- 返回输入参数的对数
 *
 * \说明:
 *   该函数求取输入参数的以2为底的对数，并转换为整型输出。
 *
 *************************************************************************
 */
int Log2(int n)
{
	int rsl = 0;
	while (n >>= 1) rsl++;
	return rsl;
}




BOOL DIBDWTStep(LPSTR lpDIBBits,double*m_pDbImage, int nWidth,int nHeight, int nInv,int m_nDWTCurDepth,int m_nSupp)
{
	// 循环变量
	int i, j;

	// 获取变换的最大层数
	int nMaxWLevel = Log2(nWidth);
	int nMaxHLevel = Log2(nHeight);
	int nMaxLevel;
	if (nWidth == 1<<nMaxWLevel && nHeight == 1<<nMaxHLevel)
		nMaxLevel = min(nMaxWLevel, nMaxHLevel);

	// 临时变量
	double	*pDbTemp;
	BYTE	*pBits;

	// 如果小波变换的存储内存还没有分配，则分配此内存
	if(!m_pDbImage){			
		m_pDbImage = new double[nWidth*nHeight];
		if (!m_pDbImage)	return FALSE;

		// 将图象数据放入m_pDbImage中 
		for (j=0; j<nHeight; j++)
		{
			pDbTemp = m_pDbImage + j*nWidth;
			pBits = (unsigned char *)lpDIBBits + (nHeight-1-j)*nWidth;		
			for (i=0; i<nWidth; i++)
				pDbTemp[i] = pBits[i];
		}
	}
	
	// 进行小波变换（或反变换）
	if (!DWTStep_2D(m_pDbImage, nMaxWLevel-m_nDWTCurDepth, nMaxHLevel-m_nDWTCurDepth,
						nMaxWLevel, nMaxHLevel, nInv, 1, m_nSupp))
		return FALSE;

	// 如果是反变换，则当前层数减1
	if (nInv)
		m_nDWTCurDepth --;
	// 否则加1
	else
		m_nDWTCurDepth ++;

	// 然后，将数据拷贝回原CDib中，并进行相应的数据转换
	int lfw = nWidth>>m_nDWTCurDepth, lfh = nHeight>>m_nDWTCurDepth;
	for (j=0; j<nHeight; j++)
	{
		pDbTemp = m_pDbImage + j*nWidth;
		pBits = (unsigned char *)lpDIBBits + (nHeight-1-j)*nWidth;
		for (i=0; i<nWidth; i++)
		{
			if (j<lfh && i<lfw)
				pBits[i] = FloatToByte(pDbTemp[i]);
			else
				pBits[i] = BYTE(FloatToChar(pDbTemp[i]) ^ 0x80);			
		}
	}

	// 返回
	return TRUE;
}


/////////////////////////////////////////
//------------------位平面切分函数
/*************************************************************************
* 函数名称：
*   BitPlaneSlicing()
* 参数:
*   LPSTR lpDIBBits    - 指向源DIB图像指针
*   LONG  lWidth       - 源图像宽度（象素数，必须是4的倍数）
*   LONG  lHeight      - 源图像高度（象素数）
*   LONG  lLineBytes   -每行字节数
*   int   Bit    		- 分割 位 （0---7）
* 返回值:
*   BOOL               - 运算成功返回TRUE，否则返回FALSE。
* 说明:
* 该函数用于对图像进行位平面分割。8位
************************************************************************/
BOOL BitPlaneSlicing(LPSTR lpDIBBits, LONG lmageWidth, LONG  lLineBytes, LONG lmageHeight, int Bit)
{
	int i;  //循环变量
	int j;	//循环变量
			// 指向源图像的指针
	unsigned char*	lpSrc;
	//像素值
	unsigned char pixeltemp;
	int threshold1, threshold2;
	switch (Bit)
	{
		case 7:
			threshold1 = 128;
			threshold2 = 256;
			break;
		case 6:
			threshold1 = 64;
			threshold2 = 128;
			break;
		case 5:
			threshold1 = 32;
			threshold2 = 64;
			break;
		case 4:
			threshold1 = 16;
			threshold2 = 32;
			break;
		case 3:
			threshold1 = 8;
			threshold2 = 16;
			break;
		case 2:
			threshold1 = 4;
			threshold2 = 8;
			break;
		case 1:
			threshold1 = 2;
			threshold2 = 4;
			break;
		case 0:
			threshold1 = 0;
			threshold2 = 2;
			break;
		default:
			return false;

	}
	for (j = 0; j <lmageHeight; j++)
	{
		for (i = 0;i <lmageWidth; i++)
		{

			// 指向源图像倒数第j行，第i个象素的指针			
			//lpSrc = (unsigned char *)lpDIBBits + lmageWidth * j + i;
			lpSrc = (unsigned char *)lpDIBBits + lLineBytes * j + i;
			//取得当前指针处的像素值
			pixeltemp = (unsigned char)*lpSrc;
			//目标图像中灰度值小于门限则设置为黑点
			if (pixeltemp >= threshold1 &&pixeltemp < threshold2)
			{
				//*lpSrc = (unsigned char)255;
			}
			else	//否则设置为白点
			{
				*lpSrc = (unsigned char)0;
			}
		}
	}
	return true;
}






#endif // !defined(AFX_FUNCTION_H__6E194843_FEB3_491F_8062_765AA3465CBC__INCLUDED_)
