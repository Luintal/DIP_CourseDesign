

/**************************************************************************
 *  文件名：PointTrans.cpp
 *
 *  图像点运算API函数库：
 *
 *  LinerTrans()		- 图像线性变换
 *	WindowTrans()		- 图像窗口变换
 *  GrayStretch()		- 图像灰度拉伸
 *  InteEqualize()		－直方图均衡
 *
 *************************************************************************/

#include "stdafx.h"
#include "PointTrans.h"
#include "DIBAPI.h"
#include "24Transf8.cpp"

#include <math.h>
#include <direct.h>

/*************************************************************************
 *
 * 函数名称：
 *   LinerTrans()
 *
 * 参数:
 *   LPSTR lpDIBBits    - 指向源DIB图像指针
 *   LONG  lWidth       - 源图像宽度（象素数）
 *   LONG  lHeight      - 源图像高度（象素数）
 *   FLOAT fA		    - 线性变换的斜率
 *   FLOAT fB           - 线性变换的截距
 *
 * 返回值:
 *   BOOL               - 成功返回TRUE，否则返回FALSE。
 *
 * 说明:
 *   该函数用来对图像进行灰度的线性变换操作。
 *
 ************************************************************************/

BOOL WINAPI LinerTrans(LPSTR lpDIBBits, LONG lWidth, LONG lHeight, FLOAT fA, FLOAT fB)
{
	
	// 指向源图像的指针
	unsigned char*	lpSrc;
	
	// 循环变量
	LONG	i;
	LONG	j;
	
	// 图像每行的字节数
	LONG	lLineBytes;
	
	// 中间变量
	FLOAT	fTemp;
	
	// 计算图像每行的字节数
	lLineBytes = WIDTHBYTES(lWidth * 8);
	
	// 每行
	for(i = 0; i < lHeight; i++)
	{
		// 每列
		for(j = 0; j < lWidth; j++)
		{
			// 指向DIB第i行，第j个象素的指针
			lpSrc = (unsigned char*)lpDIBBits + lLineBytes * (lHeight - 1 - i) + j;
			
			// 线性变换
			fTemp = fA * (*lpSrc) + fB;
			
			// 判断是否超出范围
			if (fTemp > 255)
			{
				// 直接赋值为255
				*lpSrc = 255;
			}
			else if (fTemp < 0)
			{
				// 直接赋值为0
				*lpSrc = 0;
			}
			else
			{
				// 四舍五入
				*lpSrc = (unsigned char) (fTemp + 0.5);
			}
		}
	}
	
	// 返回
	return TRUE;

}

/*************************************************************************
 *
 * 函数名称：
 *   ThresholdTrans()
 *
 * 参数:
 *   LPSTR lpDIBBits    - 指向源DIB图像指针
 *   LONG  lWidth       - 源图像宽度（象素数）
 *   LONG  lHeight      - 源图像高度（象素数）
 *   BYTE  bThre	    - 阈值
 *
 * 返回值:
 *   BOOL               - 成功返回TRUE，否则返回FALSE。
 *
 * 说明:
 *   该函数用来对图像进行阈值变换。对于灰度值小于阈值的象素直接设置
 * 灰度值为0；灰度值大于阈值的象素直接设置为255。
 *
 ************************************************************************/
BOOL WINAPI ThresholdTrans(LPSTR lpDIBBits, LONG lWidth, LONG lHeight, BYTE bThre)
{
	
	// 指向源图像的指针
	unsigned char*	lpSrc;
	
	// 循环变量
	LONG	i;
	LONG	j;
	
	// 图像每行的字节数
	LONG	lLineBytes;
	
	// 计算图像每行的字节数
	lLineBytes = WIDTHBYTES(lWidth * 8);
	
	// 每行
	for(i = 0; i < lHeight; i++)
	{
		// 每列
		for(j = 0; j < lWidth; j++)
		{
			// 指向DIB第i行，第j个象素的指针
			lpSrc = (unsigned char*)lpDIBBits + lLineBytes * (lHeight - 1 - i) + j;
			
			// 判断是否小于阈值
			if ((*lpSrc) < bThre)
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
	
	// 返回
	return TRUE;
}

/*************************************************************************
 *
 * 函数名称：
 *   WindowTrans()
 *
 * 参数:
 *   LPSTR lpDIBBits    - 指向源DIB图像指针
 *   LONG  lWidth       - 源图像宽度（象素数）
 *   LONG  lHeight      - 源图像高度（象素数）
 *   BYTE  bLow		    - 窗口下限
 *   BYTE  bUp          - 窗口上限
 *
 * 返回值:
 *   BOOL               - 成功返回TRUE，否则返回FALSE。
 *
 * 说明:
 *   该函数用来对图像进行窗口变换。只有在窗口范围内的灰度保持不变，
 * 小于下限的象素直接设置灰度值为0；大于上限的象素直接设置灰度值为255。
 *
 ************************************************************************/
BOOL WINAPI WindowTrans(LPSTR lpDIBBits, LONG lWidth, LONG lHeight, BYTE bLow, BYTE bUp)
{
	
	// 指向源图像的指针
	unsigned char*	lpSrc;
	
	// 循环变量
	LONG	i;
	LONG	j;
	
	// 图像每行的字节数
	LONG	lLineBytes;
	
	// 计算图像每行的字节数
	lLineBytes = WIDTHBYTES(lWidth * 8);
	
	// 每行
	for(i = 0; i < lHeight; i++)
	{
		// 每列
		for(j = 0; j < lWidth; j++)
		{
			// 指向DIB第i行，第j个象素的指针
			lpSrc = (unsigned char*)lpDIBBits + lLineBytes * (lHeight - 1 - i) + j;
			
			// 判断是否超出范围
			if ((*lpSrc) < bLow)
			{
				// 直接赋值为0
				*lpSrc = 0;
			}
			else if ((*lpSrc) > bUp)
			{
				// 直接赋值为255
				*lpSrc = 255;
			}
		}
	}
	
	// 返回
	return TRUE;
}

/*************************************************************************
 *
 * 函数名称：
 *   GrayStretch()
 *
 * 参数:
 *   LPSTR lpDIBBits    - 指向源DIB图像指针
 *   LONG  lWidth       - 源图像宽度（象素数）
 *   LONG  lHeight      - 源图像高度（象素数）
 *   BYTE bX1			- 灰度拉伸第一个点的X坐标
 *   BYTE bY1			- 灰度拉伸第一个点的Y坐标
 *   BYTE bX2			- 灰度拉伸第二个点的X坐标
 *   BYTE bY2			- 灰度拉伸第二个点的Y坐标
 *
 * 返回值:
 *   BOOL               - 成功返回TRUE，否则返回FALSE。
 *
 * 说明:
 *   该函数用来对图像进行灰度拉伸。
 *
 ************************************************************************/
BOOL WINAPI GrayStretch(LPSTR lpDIBBits, LONG lWidth, LONG lHeight, BYTE bX1, BYTE bY1, BYTE bX2, BYTE bY2)
{
	
	// 指向源图像的指针
	unsigned char*	lpSrc;
	
	// 循环变量
	LONG	i;
	LONG	j;
	
	// 灰度映射表
	BYTE	bMap[256];
	
	// 图像每行的字节数
	LONG	lLineBytes;
	
	// 计算图像每行的字节数
	lLineBytes = WIDTHBYTES(lWidth * 8);
	
	// 计算灰度映射表
	for (i = 0; i <= bX1; i++)
	{
		// 判断bX1是否大于0（防止分母为0）
		if (bX1 > 0)
		{
			// 线性变换
			bMap[i] = (BYTE) bY1 * i / bX1;
		}
		else
		{
			// 直接赋值为0
			bMap[i] = 0;
		}
	}
	for (; i <= bX2; i++)
	{
		// 判断bX1是否等于bX2（防止分母为0）
		if (bX2 != bX1)
		{
			// 线性变换
			bMap[i] = bY1 + (BYTE) ((bY2 - bY1) * (i - bX1) / (bX2 - bX1));
		}
		else
		{
			// 直接赋值为bY1
			bMap[i] = bY1;
		}
	}
	for (; i < 256; i++)
	{
		// 判断bX2是否等于255（防止分母为0）
		if (bX2 != 255)
		{
			// 线性变换
			bMap[i] = bY2 + (BYTE) ((255 - bY2) * (i - bX2) / (255 - bX2));
		}
		else
		{
			// 直接赋值为255
			bMap[i] = 255;
		}
	}
	
	// 每行
	for(i = 0; i < lHeight; i++)
	{
		// 每列
		for(j = 0; j < lWidth; j++)
		{
			// 指向DIB第i行，第j个象素的指针
			lpSrc = (unsigned char*)lpDIBBits + lLineBytes * (lHeight - 1 - i) + j;
			
			// 计算新的灰度值
			*lpSrc = bMap[*lpSrc];
		}
	}
	
	// 返回
	return TRUE;
}

/*************************************************************************
 *
 * 函数名称：
 *   InteEqualize()
 *
 * 参数:
 *   LPSTR lpDIBBits    - 指向源DIB图像指针
 *   LONG  lWidth       - 源图像宽度（象素数）
 *   LONG  lHeight      - 源图像高度（象素数）
 *
 * 返回值:
 *   BOOL               - 成功返回TRUE，否则返回FALSE。
 *
 * 说明:
 *   该函数用来对图像进行直方图均衡。
 *
 ************************************************************************/
BOOL WINAPI InteEqualize(LPSTR lpDIBBits, LONG lWidth, LONG lHeight)
{
	
	// 指向源图像的指针
	unsigned char*	lpSrc;
	
	// 临时变量
	LONG	lTemp;
	
	// 循环变量
	LONG	i;
	LONG	j;
	
	// 灰度映射表
	BYTE	bMap[256];
	
	// 灰度映射表
	LONG	lCount[256];
	
	// 图像每行的字节数
	LONG	lLineBytes;
	
	// 计算图像每行的字节数
	lLineBytes = WIDTHBYTES(lWidth * 8);
	
	// 重置计数为0
	for (i = 0; i < 256; i ++)
	{
		// 清零
		lCount[i] = 0;
	}
	
	// 计算各个灰度值的计数
	for (i = 0; i < lHeight; i ++)
	{
		for (j = 0; j < lWidth; j ++)
		{
			lpSrc = (unsigned char *)lpDIBBits + lLineBytes * i + j;
			
			// 计数加1
			lCount[*(lpSrc)]++;
		}
	}
	
	// 计算灰度映射表
	for (i = 0; i < 256; i++)
	{
		// 初始为0
		lTemp = 0;
		
		for (j = 0; j <= i ; j++)
		{
			lTemp += lCount[j];
		}
		
		// 计算对应的新灰度值
		bMap[i] = (BYTE) (lTemp * 255 / lHeight / lWidth);
	}
	
	// 每行
	for(i = 0; i < lHeight; i++)
	{
		// 每列
		for(j = 0; j < lWidth; j++)
		{
			// 指向DIB第i行，第j个象素的指针
			lpSrc = (unsigned char*)lpDIBBits + lLineBytes * (lHeight - 1 - i) + j;
			
			// 计算新的灰度值
			*lpSrc = bMap[*lpSrc];
		}
	}
	
	// 返回
	return TRUE;
}
/*************************************************************************
 *
 * 函数名称：
 *   Segmental2_Linear_Tran()
 *  分段线性变换
 * 参数:
 *   LPSTR lpDIBBits    - 指向源DIB图像指针
 *   LONG  lWidth       - 源图像宽度（象素数）
 *   LONG  lHeight      - 源图像高度（象素数）
 *   int type - 变换类型（1：倒V字型；2：V字型，3：倒L型，4-L型）
 *   int threshold      -阈值
 * 返回值:
 *   BOOL               - 成功返回TRUE，否则返回FALSE。
 *
 * 说明:
 *   该函数用来对图像进行分段线性变换。
 *
 ************************************************************************/
BOOL WINAPI Segmental2_Linear_Tran(LPSTR lpDIBBits, LONG lWidth, LONG lHeight,  int type,int threshold)
{
	// 指向源图像的指针
	unsigned char*	lpSrc;
	
	// 循环变量
	LONG	i;
	LONG	j;
	
	// 图像每行的字节数
	LONG	lLineBytes;
	
	// 中间变量
	FLOAT	fTemp=127.0,fA1=1,fB1=0,fA2=1,fB2=0;
	//中间灰度
	int seg_gray= threshold;

	// 计算图像每行的字节数
	lLineBytes = WIDTHBYTES(lWidth * 8);
	//计算线性变换的参数
	if (type == 1) // 倒V字型
	{
		fA1 = (float)(255.0 / (float)threshold); // 应该为2.0，如果 threshold == 127
		fB1 = 0.0;  // (2f)

		fA2 = -(float)(255.0 / (255.0 - (float)threshold)); // 应该为-2.0，如果 threshold == 127
		fB2 = (float)(255.0 + (-255.0 * (float)threshold) / (255.0 - (float)threshold)); // (-2f + 255) ，如果 threshold == 127

		// 调试信息，可以注释掉
		/*
		CString string1, string2;
		string1.Format(L"%d,%f,%f", threshold, fA1, fB1); // 将变量组装到字符串中
		MessageBox(NULL, string1, L"阈值，斜率1，截距1", MB_OK);

		string2.Format(L"%d,%f,%f", threshold, fA2, fB2); // 将变量组装到字符串中
		MessageBox(NULL, string2, L"阈值，斜率2，截距2", MB_OK);
		*/
	}

	if(type==2)//V字型
	{
		fA1 = -255.0f / threshold;
		fB1 = 255.0f;
		fA2 = 255.0f / (255 - threshold);
		fB2 = -fA2 * threshold;
	}
	if(type==3)//倒L字型
	{
		fA1 = 255.0f / threshold;
		fB1 = 0.0f;
		fA2 = 0.0f;
		fB2 = 255.0f;
	}
	if(type==4)//L字型   大家注意，赋值好像有问题！！！//2024.4.8已改正
	{
		fA1 = -255.0f / threshold;
		fB1 = 255.0f;
		fA2 = 0.0f;
		fB2 = 0.0f;
	}
	// 每行
	for(i = 0; i < lHeight; i++)
	{
		// 每列
		for(j = 0; j < lWidth; j++)
		{
			// 指向DIB第i行，第j个象素的指针
			lpSrc = (unsigned char*)lpDIBBits + lLineBytes * (lHeight - 1 - i) + j;
			
			// 线性变换,分段
			if(*lpSrc>=0 && *lpSrc<=seg_gray)
				fTemp = fA1 * (float)(*lpSrc) + fB1;
			if(*lpSrc>=seg_gray+1 &&(float) (*lpSrc)<=255)
				fTemp = fA2 * (float)(*lpSrc) + fB2;
			
			// 判断是否超出范围
			if (fTemp > 255)
			{
				// 直接赋值为255
				*lpSrc = 255;
			}
			else if (fTemp < 0)
			{
				// 直接赋值为0
				*lpSrc = 0;
			}
			else
			{
				// 四舍五入
				*lpSrc = (unsigned char) (fTemp + 0.5);
			}
		}
	}
	
	// 返回
	return TRUE;


}

 /*************************************************************************
 *
 * 函数名称：
 *   LinerTrans24()
 *
 * 参数:
 *   LPSTR lpDIBBits    - 指向源DIB图像指针
 *   LONG  lWidth       - 源图像宽度（象素数）
 *   LONG  lHeight      - 源图像高度（象素数）
 *   FLOAT fA		    - 线性变换的斜率
 *   FLOAT fB           - 线性变换的截距
 *
 * 返回值:
 *   BOOL               - 成功返回TRUE，否则返回FALSE。
 *
 * 说明:
 *   该函数用来对图像进行灰度的线性变换操作。24位
 *
 ************************************************************************/

BOOL WINAPI LinerTrans24(LPSTR lpDIBBits, LONG lWidth, LONG lHeight, FLOAT fA, FLOAT fB)
{
	
	// 指向源图像的指针
	unsigned char*	lpSrc;	
	// 循环变量
	LONG	i;
	LONG	j;	
	// 图像每行的字节数
	LONG	lLineBytes;	
	// 中间变量
	FLOAT	fTemp;	
	// 计算图像每行的字节数
	lLineBytes = WIDTHBYTES(lWidth * 24);	
	// 每行
	for(i = 0; i < lHeight; i++)
	{
		// 每列
		for(j = 0; j < lWidth; j++)
		{
			// 指向DIB第i行，第j个象素的指针
			//lpSrc = (unsigned char*)lpDIBBits + lLineBytes * (lHeight - 1 - i) + j*3;			
			lpSrc = (unsigned char*)lpDIBBits + lLineBytes * i + j*3;			
			// 线性变换
			fTemp =float( fA * (*lpSrc) + fB);			
			// 判断是否超出范围
			if (fTemp > 255)
			{
				// 直接赋值为255
				*lpSrc = 255;
			}
			else if (fTemp < 0)
			{
				// 直接赋值为0
				*lpSrc = 0;
			}
			else
			{
				// 四舍五入
				*lpSrc = (unsigned char) (fTemp + 0.5);
			}
			
			// 指向DIB第i行，第j个象素的指针
			lpSrc = (unsigned char*)lpDIBBits + lLineBytes * i + j*3+1;			
			// 线性变换
			fTemp = float( fA * (*lpSrc) + fB);			
			// 判断是否超出范围
			if (fTemp > 255)
			{
				// 直接赋值为255
				*lpSrc = 255;
			}
			else if (fTemp < 0)
			{
				// 直接赋值为0
				*lpSrc = 0;
			}
			else
			{
				// 四舍五入
				*lpSrc = (unsigned char) (fTemp + 0.5);
			}

			// 指向DIB第i行，第j个象素的指针
			lpSrc = (unsigned char*)lpDIBBits + lLineBytes * i + j*3+2;			
			// 线性变换
			fTemp =float(  fA * (*lpSrc) + fB);			
			// 判断是否超出范围
			if (fTemp > 255)
			{
				// 直接赋值为255
				*lpSrc = 255;
			}
			else if (fTemp < 0)
			{
				// 直接赋值为0
				*lpSrc = 0;
			}
			else
			{
				// 四舍五入
				*lpSrc = (unsigned char) (fTemp + 0.5);
			}
			
		}
	}
	
	// 返回
	return TRUE;

}
/*************************************************************************
*
* 函数名称：
*   If8Color()
*
* 参数:
*   LPSTR lpDib        -指向源DIB指针
*   LPSTR lpDIBBits    - 指向源DIB图像指针
*   LONG  lWidth       - 源图像宽度（象素数）
*   LONG  lHeight      - 源图像高度（象素数）
*   
*   int BitCount       -图像位数
*
* 返回值:
*   BOOL               - 成功返回TRUE，否则返回FALSE。
*
* 说明:
*   该函数用来对8位彩色改变亮度,改变调色板的办法
*
************************************************************************/
BOOL WINAPI If8Gray(LPSTR lpDib, int BitCount)
{
	// 指向源图像的指针
	unsigned char* lpSrc;
	// 循环变量
	LONG	i;
	LONG	j;
	int r, g, b;
	int grayflag = 1;//是否灰度
	// 图像每行的字节数
	LONG	lLineBytes;

	// 计算图像每行的字节数
	//lLineBytes = WIDTHBYTES(lWidth * 8);

	RGBQUAD* pTable, * pTable1;//颜色表指针
	if (BitCount != 8) return false;
	pTable = (RGBQUAD*)(lpDib + sizeof(BITMAPINFOHEADER));
	pTable1 = pTable;
	for (i = 0; i < 256; i++)//遍历调色板 
	{
		r = pTable->rgbRed;
		g = pTable->rgbGreen;
		b = pTable->rgbBlue;
		if (r != g || r != b || g != b)
		{
			grayflag = 0; //彩色
			break;
		}
		pTable++;
	}
	if (grayflag == 0)
	{
		return false;

	}
	return true;
}

/*************************************************************************
*
* 函数名称：
*   8ColorAdd()
*
* 参数:
*   LPSTR lpDib        -指向源DIB指针
*   LPSTR lpDIBBits    - 指向源DIB图像指针
*   LONG  lWidth       - 源图像宽度（象素数）
*   LONG  lHeight      - 源图像高度（象素数）
*   int offset         - 变化值
*   int BitCount       -图像位数
*
* 返回值:
*   BOOL               - 成功返回TRUE，否则返回FALSE。
*
* 说明:
*   该函数用来对8位彩色改变亮度,改变调色板的办法
*
************************************************************************/
BOOL WINAPI Color8Add(LPSTR lpDib,LPSTR lpDIBBits, int BitCount, LONG lWidth, LONG lHeight, int offset)
{
	// 指向源图像的指针
	unsigned char* lpSrc;
	// 循环变量
	LONG	i;
	LONG	j;
	int r, g, b;
	//int grayflag = 1;//是否灰度
	// 图像每行的字节数
	//LONG	lLineBytes;

	// 计算图像每行的字节数
	//lLineBytes = WIDTHBYTES(lWidth * 8);

	RGBQUAD* pTable, * pTable1;//颜色表指针

	pTable = (RGBQUAD*)(lpDib + sizeof(BITMAPINFOHEADER));
	pTable1 = pTable;
	if (BitCount != 8) return false;
	if (!If8Gray(lpDib, BitCount))
	{
		pTable = pTable1;
		for (i = 0; i < 256; i++)//遍历调色板 
		{
			r = pTable->rgbRed + offset;
			g = pTable->rgbGreen + offset;
			b = pTable->rgbBlue + offset;
			if (r >255)
			{
				r = 255;
			}
			if (r < 0)
			{
				r = 0;
			}
			if (g > 255)
			{
				g = 255;
			}
			if (g < 0)
			{
				g = 0;
			}
			if (b > 255)
			{
				b = 255;
			}
			if (b < 0)
			{
				b = 0;
			}
			pTable->rgbRed = r;
			pTable->rgbGreen = g;
			pTable->rgbBlue = b;

			pTable++;
		}
	
	}
	
	return true;
}

/*************************************************************************
*
* 函数名称：
*   8ColorAdd_HSI()
*
* 参数:
*   LPSTR lpDib        -指向源DIB指针
*   LPSTR lpDIBBits    - 指向源DIB图像指针
*   LONG  lWidth       - 源图像宽度（象素数）
*   LONG  lHeight      - 源图像高度（象素数）
*   int offset         - 变化值
*   int BitCount       -图像位数
*
* 返回值:
*   BOOL               - 成功返回TRUE，否则返回FALSE。
*
* 说明:
*   该函数用来对8位彩色改变亮度,改变调色板的办法,中间使用HSI颜色模型
*
************************************************************************/
BOOL WINAPI Color8Add_HSI(LPSTR lpDib, LPSTR lpDIBBits, int BitCount, LONG lWidth, LONG lHeight, int offset)
{
	// 指向源图像的指针
	unsigned char* lpSrc;
	// 循环变量
	LONG	i;
	LONG	j;
	int r,r_old, g, g_old,b,b_old;
	double H, S, I,theta;//色调，饱和度，亮度,角度(弧度)
	BOOL white=false, black=false;//白色，黑色
	int degree;//角度
	//int grayflag = 1;//是否灰度
	// 图像每行的字节数
	//LONG	lLineBytes;

	// 计算图像每行的字节数
	//lLineBytes = WIDTHBYTES(lWidth * 8);

	RGBQUAD* pTable, * pTable1;//颜色表指针

	pTable = (RGBQUAD*)(lpDib + sizeof(BITMAPINFOHEADER));
	pTable1 = pTable;
	if (BitCount != 8) return false;

	if (!If8Gray(lpDib, BitCount))
	{
		pTable = pTable1;
		for (i = 0; i < 256; i++)//遍历调色板 
		{
			r = pTable->rgbRed;
			g = pTable->rgbGreen;
			b = pTable->rgbBlue;
			r_old = pTable->rgbRed;
			g_old = pTable->rgbGreen;
			b_old = pTable->rgbBlue;
			//RGB 转换为HSI
			I = ((double)r + (double)g + (double)b) / 3.0 ;
			H = 1234.0;//初值
			S = 1234.0;//初值
			if (r == 255 && g == 255 && b == 255)
			{
				H = 0; S = 0; white = true; black=false;
				
			}
			if (r == 0 && g == 0 && b == 0)
			{
				H = 0; S = 0; black = true; white = false;
			}
			if (I > 0 && I < 255)S = 1.0 - 3.0 * min(r, min(g, b)) / ((double)r + (double)g + (double)b);//饱和度
			if (I > 0 && I < 255)
			{
				theta = acos(0.5 * (((double)r - (double)g) + ((double)r - (double)b)) / sqrt(((double)r - (double)g) * ((double)r - (double)g) + ((double)r - (double)b) * ((double)g - (double)b)));
				if (b <= g) H = theta;
				else H = 2 * PI - theta;
			}

			degree = (int)(180.0 / PI * H);
			I = ((double)r + (double)g + (double)b) / 3.0 + (double)offset;//亮度改变
			if (I < 0) I = 0;
			if (I > 255) I = 255;
			//HSI 转换为RGB
			if (degree == 0 && !white   && !black  )
			{
				r = (int)(I + (2 * I * S));
				g = (int)(I - (I * S));
				b = (int)(I - (I * S));
			}
			if (degree > 0 && degree < 120 && !white   && !black  )
			{
				b = (int)(I * (1.0 - S));
				r = (int)(I * (1.0 + S * cos(H) / cos(60.0 * PI / 180.0 - H)));
				g = (int)(3.0 * I - ((double)r + (double)b));
			}
			if (degree == 120 && !white   && !black  )
			{
				r = (int)(I + ( I * S));
				g = (int)(I - (2*I * S));
				b = (int)(I - (I * S));
			}
			if (degree > 120 && degree < 240 && !white   && !black  )
			{
				H = H - 120.0 * PI / 180.0;
				r = (int)(I * (1.0 - S));
				g = (int)(I * (1.0 + S * cos(H) / cos(60.0 * PI / 180.0 - H)));
				b = (int)(3.0 * I - ((double)r + (double)g));
			}
			if (degree == 240 && !white   && !black  )
			{
				r = (int)(I + (I * S));
				g = (int)(I - ( I * S));
				b = (int)(I - (2*I * S));
			}
			if (degree > 240 && degree < 360 && !white   && !black  )
			{
				H = H - 240.0 * PI / 180.0;
				g = (int)(I * (1.0 - S));
				b = (int)(I * (1.0 + S * cos(H) / cos(60.0 * PI / 180.0 - H)));
				r = (int)(3.0 * I - ((double)g + (double)b));
			}
			
			if (white  || black  )
			{
				r = r_old+offset;
				g = g_old + offset;
				b = b_old + offset;
				if (r < 0)r = 0;
				if (r > 255)r = 255;
				if (g < 0)g = 0;
				if (g > 255)g = 255;
				if (b < 0)b = 0;
				if (b > 255)b = 255;
			}
			
			//重新写回调色板
			pTable->rgbRed = (BYTE)r;
			pTable->rgbGreen = (BYTE)g;
			pTable->rgbBlue = (BYTE)b;

			pTable++;
		}
	}
		return true;
	}

	


 /*************************************************************************
 *
 * 函数名称：
 *   ChangeGray()
 *
 * 参数:
 *   LPSTR lpDIBBits    - 指向源DIB图像指针
 *   LONG  lWidth       - 源图像宽度（象素数）
 *   LONG  lHeight      - 源图像高度（象素数）
 *   int offset         - 变化值
 *   int BitCount       -图像位数
 *
 * 返回值:
 *   BOOL               - 成功返回TRUE，否则返回FALSE。
 *
 * 说明:
 *   该函数用来对图像的亮度进行改变
 *
 ************************************************************************/
 BOOL WINAPI ChangeGray(LPSTR lpDIBBits, int BitCount,LONG lWidth, LONG lHeight,int offset)
 {
	  // 指向源图像的指针
	unsigned char*	lpSrc;	
	// 循环变量
	LONG	i;
	LONG	j;	
	// 图像每行的字节数
	LONG	lLineBytes;	
	int temp,k;
	// 计算图像每行的字节数
	lLineBytes = WIDTHBYTES(lWidth * BitCount);
	int page = 1;
	if(BitCount==24) page=3;
	if(BitCount==8) page=1;
	
	 //逐行扫描
	for(i = 0; i < lHeight; i++)
	{
	//逐列扫描
		for(j = 0; j < lWidth; j++)
		{
		// 指向DIB第i行，第j个象素的指针
			for (k=0;k<page;k++)
			{
				lpSrc = (unsigned char*)lpDIBBits + lLineBytes * (lHeight - 1 - i) + j*page+k;
				// 变换
				temp=*lpSrc + offset;
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
					*lpSrc = (unsigned char) (temp + 0.5);
				}
			
			}
		}
	}
	return true;
 }
 
 /*************************************************************************
 *
 * 函数名称：
 *   Tran24ColTo24Gray()
 *
 * 参数:
 *   LPSTR lpDIBBits    - 指向源DIB图像指针
 *   LONG  lWidth       - 源图像宽度（象素数）
 *   LONG  lHeight      - 源图像高度（象素数）
 *   
 *   
 *
 * 返回值:
 *   BOOL               - 成功返回TRUE，否则返回FALSE。
 *
 * 说明:
 *   该函数用来对图像进行变换。24位彩色TO24位灰度
 *
 ************************************************************************/
 BOOL WINAPI Tran24ColTo24Gray(LPSTR lpDIBBits, LONG lWidth, LONG lHeight)
 {
	 // 指向源图像的指针
	unsigned char*	lpSrc;	
	// 循环变量
	LONG	i;
	LONG	j;	
	// 图像每行的字节数
	LONG	lLineBytes;	
	
	// 计算图像每行的字节数
	lLineBytes = WIDTHBYTES(lWidth * 24);	
	
	int R,G,B,Gray;
	for(i=0;i<lHeight;i++)
	{
		for(j=0;j<lWidth;j++)
		{
			lpSrc=(unsigned char*)lpDIBBits+i*lLineBytes+j*3;
			B=*lpSrc;
			lpSrc=(unsigned char*)lpDIBBits+i*lLineBytes+j*3+1;
			G=*lpSrc;
			lpSrc=(unsigned char*)lpDIBBits+i*lLineBytes+j*3+2;
			R=*lpSrc;
			Gray=((R+G+B)/3.0+0.5);

			lpSrc=(unsigned char*)lpDIBBits+i*lLineBytes+j*3;
			*lpSrc=Gray;
			lpSrc=(unsigned char*)lpDIBBits+i*lLineBytes+j*3+1;
			*lpSrc=Gray;
			lpSrc=(unsigned char*)lpDIBBits+i*lLineBytes+j*3+2;
			*lpSrc=Gray;

		}
	}
	return true;
 }

  /*************************************************************************
 *
 * 函数名称：
 *   Tran8ColTo8Gray()
 *
 * 参数:
 *   LPSTR lpDIB        - 指向源DIB图像指针
 *   LPSTR lpDIBBits    - 指向源DIB图像数据指针
 *   LONG  lWidth       - 源图像宽度（象素数）
 *   LONG  lHeight      - 源图像高度（象素数）
 *   
 *   
 *
 * 返回值:
 *   BOOL               - 成功返回TRUE，否则返回FALSE。
 *
 * 说明:
 *   该函数用来对图像进行变换。8位彩色TO8位灰度
 *
 ************************************************************************/
 BOOL WINAPI Tran8ColTo8Gray(LPSTR lpDIB,LPSTR lpDIBBits, LONG lWidth, LONG lHeight)
 {
	  // 指向源图像的指针
	unsigned char*	lpSrc;	
	// 循环变量
	LONG	i;
	LONG	j;	
	// 图像每行的字节数
	LONG	lLineBytes;	
	
	// 计算图像每行的字节数
	lLineBytes = WIDTHBYTES(lWidth * 8);	
	
	// 灰度映射表
	BYTE bMap[256];				
	RGBQUAD *pTable,*pTable1;//颜色表指针

	pTable=(RGBQUAD*)(lpDIB+sizeof(BITMAPINFOHEADER));
	for (i=0;i<256;i++)//生成新的调色板,并转换灰度
	{
	// 计算该颜色对应的灰度值g=0.299*r+0.587*g+0.114*b	
		bMap[i] = (BYTE)(0.299 * pTable->rgbRed + 0.587 * pTable->rgbGreen + 0.114 * pTable->rgbBlue + 0.5);		
		pTable->rgbRed=(BYTE)i;
		pTable->rgbGreen=(BYTE)i;
		pTable->rgbBlue=(BYTE)i;
		pTable->rgbReserved=(BYTE)0;	
		pTable++;
	}	
	// 更换每个象素的颜色索引（即按照灰度映射表换成灰度值）
	//逐行扫描
	for(i = 0; i < lHeight; i++)
	{
	//逐列扫描
		for(j = 0; j < lWidth; j++)
		{
		// 指向DIB第i行，第j个象素的指针
			lpSrc = (unsigned char*)lpDIBBits + lLineBytes * (lHeight - 1 - i) + j;
			// 变换
			*lpSrc =bMap[*lpSrc];
		}
	}

	return true;
 }
 /*************************************************************************
 *
 * 函数名称：
 *   Tran24ColTo8Gray()
 *
 * 参数:
 *	 LPSTR lpDIB        - 指向源DIB图像指针
 *   LPSTR lpDIBBits    - 指向源DIB图像数据指针
 *   LONG  lWidth       - 源图像宽度（象素数）
 *   LONG  lHeight      - 源图像高度（象素数）
 *   
 *   
 *
 * 返回值:
 *   BOOL               - 成功返回TRUE，否则返回FALSE。
 *
 * 说明:
 *   该函数用来对图像进行变换。24位彩色TO8位灰度
 *
 ************************************************************************/
 BOOL WINAPI Tran24ColTo8Gray(LPSTR lpDIB,LPSTR lpDIBBits, LONG lWidth, LONG lHeight)
 {
	 // 指向源图像的指针
	unsigned char*	lpSrc;	
	// 循环变量
	LONG	i;
	LONG	j;	
	// 图像每行的字节数
	LONG	lLineBytes;		
	// 计算图像每行的字节数
	lLineBytes = WIDTHBYTES(lWidth * 24);	
	BITMAPINFOHEADER *pHead;
	RGBQUAD* pColorTable;
	int lineByteNew;
	int biBitCount=8;
	lineByteNew=(lWidth * biBitCount/8+3)/4*4; 
	//申请位图数据所需要的空间，读位图数据进内存
	unsigned char *pBmpBufNew;
	pBmpBufNew=new unsigned char[lineByteNew * lHeight + sizeof(BITMAPINFOHEADER) + 256*4];//申请新图像的空间
	memcpy(pBmpBufNew,(unsigned char *)lpDIB,sizeof(BITMAPINFOHEADER));//信息头拷贝
	pHead=(BITMAPINFOHEADER *)pBmpBufNew;
	pHead->biBitCount=8;//改变位数,
	pHead->biHeight=lHeight;
	pHead->biWidth=lWidth;
	pHead->biClrUsed=256;
	pHead->biClrImportant=0;
	pHead->biCompression=0;
	pHead->biPlanes=1;
	pHead->biSize=40;
	pHead->biSizeImage=lineByteNew*lHeight;
	pHead->biXPelsPerMeter=0;
	pHead->biYPelsPerMeter=0;
	pColorTable=(RGBQUAD*)(pBmpBufNew +sizeof(BITMAPINFOHEADER));
	//灰度图像有颜色表，且颜色表表项为
	if(biBitCount==8){
	//申请颜色表所需要的空间，给颜色表赋值
		for(int i=0;i<256;i++)
		{			
			pColorTable[i].rgbBlue=i;
			pColorTable[i].rgbGreen=i;
			pColorTable[i].rgbRed=i;
			pColorTable[i].rgbReserved=0;
		}
	} 	 
				
	int Red,Green,Blue,Gray,offset;
	offset=sizeof(BITMAPINFOHEADER)+256*4;
	//逐行扫描
	for(i = 0; i < lHeight; i++)
	{
	//逐列扫描
		for(j = 0; j < lWidth; j++)
		{
		// 指向DIB第i行，第j个象素的指针
			lpSrc = (unsigned char*)lpDIBBits + lLineBytes * (lHeight - 1 - i) + j*3;
			Blue = *lpSrc;
			Green=*(++lpSrc);
			Red=*(++lpSrc);
			Gray= (BYTE)(0.299 * Red + 0.587 * Green + 0.114 * Blue + 0.5);
			// 变换
			lpSrc= (unsigned char*)(pBmpBufNew+offset) + lineByteNew * (lHeight - 1 - i) + j;
			*lpSrc =Gray;					
		}
	}
			//拷贝
	memcpy(lpDIB,pBmpBufNew,lineByteNew * lHeight+ sizeof(BITMAPINFOHEADER) + 256*4);

	delete []pBmpBufNew;

	return true;
 }
 /*************************************************************************
 *
 * 函数名称：
 *   Tran24ColTo8Col()
 *
 * 参数:
 *	 LPSTR lpDIB        - 指向源DIB图像指针
 *   LPSTR lpDIBBits    - 指向源DIB图像数据指针
 *   LONG  lWidth       - 源图像宽度（象素数）
 *   LONG  lHeight      - 源图像高度（象素数）
 *   
 *   
 *
 * 返回值:
 *   BOOL               - 成功返回TRUE，否则返回FALSE。
 *
 * 说明:
 *   该函数用来对图像进行变换。24位彩色TO8位彩色
 *
 ************************************************************************/
 BOOL WINAPI  Tran24ColTo8Col(LPSTR lpDIB,LPSTR lpDIBBits, LONG lWidth, LONG lHeight)
 {
	 // 指向源图像的指针
	unsigned char*	lpSrc;	
	// 循环变量
	LONG	i;
	LONG	j;	
	// 图像每行的字节数
	LONG	lLineBytes;		
	// 计算图像每行的字节数
	lLineBytes = WIDTHBYTES(lWidth * 24);	
	BITMAPINFOHEADER *pHead;
	RGBQUAD* pColorTable=NULL;
	int lineByteNew;
	int biBitCount=8;
	lineByteNew=(lWidth * biBitCount/8+3)/4*4; 
	//灰度图像有颜色表，且颜色表表项为
	if(biBitCount==8){
		//申请颜色表所需要的空间，给颜色表赋值
		pColorTable=new RGBQUAD[256];
 		memset(pColorTable, 0, sizeof(RGBQUAD)*256);  
	} 	  
	BYTE* Index = new BYTE[lineByteNew*lHeight]; //图像数据区的数据(保存在Index中)
	WORD* shortColor = new WORD[lineByteNew*lHeight]; //颜色的高4位
	memset(shortColor, 0, sizeof(WORD)*lineByteNew*lHeight); //清零

	int iRed, iGreen, iBlue;  
	for (int i = 0; i < lHeight; i++)  
	{//取RGB颜色的高4位  
		for(int j=0;j<lWidth;j++)
		{
			lpSrc = (unsigned char*)lpDIBBits + lLineBytes * (lHeight - 1 - i) + j*3;
			iBlue = (*lpSrc)>>4;
			iGreen=(*(++lpSrc))>>4;
			iRed=(*(++lpSrc))>>4;						
			shortColor[lineByteNew * (lHeight - 1 - i) + j] =(iBlue<<8) + (iGreen<<4) + iRed ;  					
		}
	} 
	//调用转换函数  24color To->8color
    Transfer(shortColor, lineByteNew*lHeight, Index, pColorTable);  

	//申请位图数据所需要的空间，读位图数据进内存
	unsigned char *pBmpBufNew;
	pBmpBufNew=new unsigned char[sizeof(BITMAPINFOHEADER) + 256*4];//申请新图像的空间
	memcpy(pBmpBufNew,(unsigned char *)lpDIB,sizeof(BITMAPINFOHEADER));//信息头拷贝
	pHead=(BITMAPINFOHEADER *)pBmpBufNew;
	pHead->biBitCount=8;//改变位数,
	pHead->biHeight=lHeight;
	pHead->biWidth=lWidth;
	pHead->biClrUsed=256;
	pHead->biClrImportant=0;
	pHead->biCompression=0;
	pHead->biPlanes=1;
	pHead->biSize=40;
	pHead->biSizeImage=lineByteNew*lHeight;
	pHead->biXPelsPerMeter=0;
	pHead->biYPelsPerMeter=0;

	//拷贝
	memcpy(lpDIB,pBmpBufNew, sizeof(BITMAPINFOHEADER));
	memcpy(lpDIB+sizeof(BITMAPINFOHEADER),pColorTable, sizeof(RGBQUAD)*256);
	memcpy(lpDIB+sizeof(BITMAPINFOHEADER)+sizeof(RGBQUAD)*256,Index,lineByteNew*lHeight);

	delete []Index;
	delete []shortColor;

	return true;
 }
 /*************************************************************************
 *
 * 函数名称：
 *   RGB2HSI()
 *
 * 参数:
 *	 LPSTR lH_data        - 指向目标指针等
 *   LPSTR lpDIBBits    - 指向源DIB图像数据指针
 *   LONG  lWidth       - 源图像宽度（象素数）
 *   LONG  lHeight      - 源图像高度（象素数）
 *   
 *   
 *
 * 返回值:
 *   BOOL               - 成功返回TRUE，否则返回FALSE。
 *
 * 说明:
 *   该函数用来对图像进行变换。RGB TOHSI
 *
 ************************************************************************/
 BOOL WINAPI RGB2HSI(LPSTR lpDIBBits, LONG lWidth, LONG lHeight,unsigned char* lH_data,unsigned char* lS_data,unsigned char* lI_data)
 {
	 // 指向源图像的指针
	unsigned char*	lpSrc,*lpH1,*lpS1,*lpI1;	
	// 循环变量
	LONG	i;
	LONG	j;	
	// 图像每行的字节数
	LONG	lLineBytes,lineByteNew;		
	// 计算图像每行的字节数
	lLineBytes = WIDTHBYTES(lWidth * 24);	
	lineByteNew=WIDTHBYTES(lWidth * 8);
	double R,G,B,H,S,I,th,min,max;
	for(i=0;i<lHeight;i++)
	{
		for(j=0;j<lWidth;j++)
		{
			lpSrc = (unsigned char*)lpDIBBits + lLineBytes * (lHeight - 1 - i) + j*3;
			B=*lpSrc;
			lpSrc = (unsigned char*)lpDIBBits + lLineBytes * (lHeight - 1 - i) + j*3+1;
			G=*lpSrc;
			lpSrc = (unsigned char*)lpDIBBits + lLineBytes * (lHeight - 1 - i) + j*3+2;
			R=*lpSrc;
			R=R/255;
			G=G/255;
			B=B/255;
			if(R>G && R>B)
			{
				max=R;
				min=MIN(G,B);
			}
			else
			{
				if(G>B)
				{
					max=G;
					min=MIN(R,B);
				}
				else
				{
					max=B;
					min=MIN(R,G);
				}
			}
			I=(R+G+B)/3.0;
			if(I==0||max==min)
			{
				//this is a black image or grayscale image point
				S=0;H=0;
			}
			else
			{
				S=1-min/I;
				th=(R-G)*(R-G)+(R-B)*(G-B);
				th=sqrt(th);
				th=acos((R-G+R-B)*0.5/th);
				if(G>=B)
					H=th;
				else
					H=2*PI-th;
			}
			lpSrc = (unsigned char*)lH_data + lineByteNew * (lHeight - 1 - i) + j;
			*lpSrc=255*H/(2*PI)+0.5;
			lpSrc = (unsigned char*)lS_data + lineByteNew * (lHeight - 1 - i) + j;
			*lpSrc=255*S +0.5;
			lpSrc = (unsigned char*)lI_data + lineByteNew * (lHeight - 1 - i) + j;
			*lpSrc=255*I +0.5;
		}
	}


	return true;
 }
 /*************************************************************************
 *
 * 函数名称：
 *   HSI2RGB()
 *
 * 参数:
 *	 LPSTR lH_data        - 指向目标指针等
 *   LPSTR lpDIBBits    - 指向源DIB图像数据指针
 *   LONG  lWidth       - 源图像宽度（象素数）
 *   LONG  lHeight      - 源图像高度（象素数）
 *   
 *   
 *
 * 返回值:
 *   BOOL               - 成功返回TRUE，否则返回FALSE。
 *
 * 说明:
 *   该函数用来对图像进行变换。RGB TOHSI
 *
 ************************************************************************/
 BOOL WINAPI HSI2RGB(double H,double S,double I,double &R,double &G,double &B)
 {
	if(H<0||H>1||S<0||S>1||I<0||I>255)
		return 0;
	if(I==0)//black
		R=G=B=0;
	else
	{
		if(S==0.0)//grayscal image
			R=G=B=I;
	}
	double temp1,temp2,temp3;
	temp1=(1-S)/3;
	temp2=S*cos(H);
	if(H>=0 && H<(PI*2/3))
	{
		B=temp1;
		temp3=cos(PI/3-H);
		R=(1+temp2/temp3)/3;
		G=1-R-B;
		R=3*I*R;
		G=3*G*I;
		B=3*I*B;
	}
	else if(H>=(PI*2/3) && H<(PI*4/3))
	{
		R=temp1;
		temp3=cos(PI-H);
		G=(1+temp2/temp3)/3;
		B=1-R-B;
		R=3*I*R;
		G=3*G*I;
	}
	else if(H>=(PI*4/3) && H<(PI*2))
	{
		G=temp1;
		temp3=cos(PI*5/3-H);
		B=(1+temp2/temp3)/3;
		R=1-R-B;
		R=3*I*R;
		G=3*G*I;
		B=3*I*B;
	}
	R=(int)R*255;
	G=(int)G*255;
	B=(int)B*255;

	 return true;
 }