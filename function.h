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
// ������
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
//���ڸ�������
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
 * �������ƣ�AngleToRadian(int angle)
 * ��������:
 *   int angle
 * ��������:float      
 * ��������:�����Ƕȵ����ȵ�ת��
 ************************************************************************/

double AngleToRadian(int angle)
{
	return ((angle)*pi/180.0);
}


/*************************************************************************
 * �������ƣ�ThreeCrossMat(double *pMatrix, int rank, double *pQMatrix, 
					    double *pMainCross, double *pHypoCross)
 * ��������:
 *   double  *pMatrix ��ָ������ָ��
 *   int     rank  ���������
 *   double	 *pQMatrix  �� householder�任��ĵľ����ָ��
 *   double  *pMainCross ���Գ��������е����Խ�Ԫ�ص�ָ��
 *   double  *pHypoCross �� �Գ��������еĴζԽ�Ԫ�ص�ָ��
 * ��������:BOOL
 *��������:��n��ʵ�Գƾ���Ϊ�Գ�������
************************************************************************/

BOOL  ThreeCrossMat(double *pMatrix, int rank, double *pQMatrix, 
					    double *pMainCross, double *pHypoCross)
{	
	int i, j, k, u;//��������
    double h, f, g, h2;   
	
	for(i = 0; i <= rank-1; i++)// ������pQMatrix��ʼ��
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
		
		if (h + 1.0 == 1.0)// ���һ��ȫ��Ϊ��
        {
			pHypoCross[i] = 0.0;
            if (i == 1) 
			{
				pHypoCross[i] = pQMatrix[i*rank+i-1];
			}
            pMainCross[i] = 0.0;
        }        		
		else
        {// ���������������ֵ
			
			pHypoCross[i] = sqrt(h);// ��ζԽ�Ԫ�ص�ֵ            			
			u = i*rank + i - 1;
            if (pQMatrix[u] > 0.0) // �ж�i��i-1��Ԫ���ǲ��Ǵ�����
			{
				pHypoCross[i] = -pHypoCross[i];
			}            
			h = h - pQMatrix[u]*pHypoCross[i];
            pQMatrix[u] = pQMatrix[u] - pHypoCross[i];
            f = 0.0;            			
		    for (j = 0; j <= i-1; j++)// householder�任
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
			for (j = 0; j <= i-1; j++)// �����������ֵ
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
    
    for (i = 0; i <= rank-2; i++) // ����ֵ
	{
		pHypoCross[i] = pHypoCross[i + 1];
	}
    pHypoCross[rank - 1] = 0.0;
    pMainCross[0]        = 0.0;    
	for (i = 0; i <= rank-1; i++)
    { // ���Խ�Ԫ�صļ���		
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
		u = i*rank + i;// �洢���Խ��ߵ�Ԫ��
        pMainCross[i] = pQMatrix[u]; 
		pQMatrix[u]   = 1.0;       		
		if (i-1 >= 0)// �����Խ������е�Ԫ�ظ���ֵ
          for (j = 0; j <= i-1; j++)
          { 
			  pQMatrix[i*rank + j] = 0.0; 
			  pQMatrix[j*rank+i]   = 0.0;
		  }
    }    
	return(TRUE);// ����
}


/*************************************************************************
 *
 * �������ƣ�EigenvalueVector(int rank, double *pMainCross, double *pHypoCross, 
				  double *pMatrix, double Precision, int MaxT)
 * ��������:
 *   int     rank ������A�Ľ���
 *   double	 *pMainCross  ���Գ��������е����Խ�Ԫ�ص�ָ�룬����ʱ���A������ֵ
 *   double  *pHypoCross  ���Գ��������еĴζԽ�Ԫ�ص�ָ��
 *	 double  *pMatrix  ���Գƾ���A������������ָ��
 *   double Precision �����ƾ���
 *   int MaxT  �� ����������
 * ��������:BOOL 
 * ��������:�ü���ʵ�Գ����Ǿ����ȫ������ֵ�Լ���Ӧ����������
 ************************************************************************/
BOOL EigenvalueVector(int rank, double *pMainCross, double *pHypoCross, 
				  double *pMatrix, double Precision, int MaxT)
{
	
	int i, j, k, m, it, u, v;// ��������
    double d, f, h, g, p, r, e, s;
	
    pHypoCross[rank - 1] = 0.0; // ��ʼ��
	d = 0.0; 
	f = 0.0;
    
	for(j = 0; j <= rank-1; j++)
    {							//  �������ȵĿ���		
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
								// ���������A������ֵ����������
			do
            {
								// ������������������ʧ��
				if(it == MaxT)
				{
					return(FALSE);
				}
                it = it + 1;
                g = pMainCross[j];
                p = (pMainCross[j + 1] - g) / (2.0 * pHypoCross[j]);
                r = sqrt(p*p + 1.0);                
								// ���p����0
				if (p >= 0.0)
				{
					pMainCross[j] = pHypoCross[j]/(p + r);
				}
                else
				{
					pMainCross[j] = pHypoCross[j]/(p - r); 
				}
				h = g - pMainCross[j];                
								//  �������Խ��ߵ�Ԫ��
				for (i = j + 1; i <= rank - 1; i++)
				{
					pMainCross[i] = pMainCross[i] - h;  
				}
								// ��ֵ
				f = f + h;
				p = pMainCross[m];
				e = 1.0; s = 0.0;
                
				for(i = m - 1; i >= j; i--)
                {
					g = e * pHypoCross[i];
					h = e * p;
                    
								//  ���Խ���Ԫ�صľ���ֵ�Ƿ���ڴζԽ���Ԫ�ص�
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
                    
								// ���´洢��������
					for(k = 0; k <= rank - 1; k++)
                    {
						u = k*rank + i + 1; v = u - 1;
                        h = pMatrix[u]; 
						pMatrix[u] = s*pMatrix[v] + e*h;
                        pMatrix[v] = e*pMatrix[v] - s*h;
                    }
                
				}               
								// �����Խ��ߺʹζԽ���Ԫ�����¸�ֵ
				pHypoCross[j] = s * p; 
				pMainCross[j] = e * p;
            
			}
            while (fabs(pHypoCross[j]) > d);
        }

        pMainCross[j] = pMainCross[j] + f;
    }   	
	for (i = 0; i <= rank-1; i++)
    {// ����A������ֵ
		k = i; p = pMainCross[i];        		
		if(i+1 <= rank-1)
        {// ��A����ֵ����p
			j = i + 1;
            while((j <= rank-1) && (pMainCross[j] <= p))
            { k = j; 
			  p = pMainCross[j]; 
			  j = j+1;
			}
        }        		
		if (k != i)
        {// �洢A������ֵ����������
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
  return(TRUE);// ����
}


/*************************************************************************
 * �������ƣ�
 *   Transpose(LPSTR lpSrcDib,LPSTR lpDibBits,long	lWidth,long	lHeight,
				   long lLineBytes,long lDstLineBytes)
 * ��������:
 *   LPSTR	lpSrcDib��ָ��ԴDIB��ָ��
     LPSTR	lpSrcStartBits,ָ��DIB��ʼ���ص�ָ��
	 long	lWidth��DIBͼ��Ŀ��
	 long	lHeight��DIBͼ��ĸ߶�
	 long	lLineBytes��DIBͼ������ֽ�����Ϊ4�ı���
	 long	lDstLineBytes����ʱDIBͼ������ֽ�����Ϊ4�ı���
 * ��������:BOOL        
 * ��������:�ú�������ת��DIBͼ��
 ************************************************************************/

BOOL  Transpose(LPSTR lpSrcDib,LPSTR lpSrcStartBits,long lWidth,long lHeight,
				   long lLineBytes,long lDstLineBytes)
{
	long i;                 //��ѭ������
	long j;                 //��ѭ������
	LPSTR	lpSrcDIBBits;	//ָ��Դ���ص�ָ��
	LPSTR	lpDstDIBBits;	//ָ����ʱͼ���Ӧ���ص�ָ��
	LPSTR	lpDstStartBits;	//ָ����ʱͼ���Ӧ���ص�ָ�� 		
	HLOCAL	hDstDIBBits;	//��ʱͼ����
	LPBITMAPINFOHEADER lpbmi;							  // ָ��BITMAPINFOHEADER�ṹ��ָ��
	lpbmi = (LPBITMAPINFOHEADER)lpSrcDib;
	hDstDIBBits= LocalAlloc(LHND, lWidth * lDstLineBytes);// ������ʱ�ڴ�
	if (hDstDIBBits== NULL)								 // �ж��Ƿ��ڴ����
	{		
		return FALSE;									// �����ڴ�ʧ��
	}	
	lpDstStartBits= (char * )LocalLock(hDstDIBBits);	// �����ڴ�		
	for(i = 0; i < lHeight; i++)						// ���ͼ��ÿ�н��в���
	{		
		for(j = 0; j < lWidth; j++)						// ���ÿ��ͼ��ÿ�н��в���
		{						
			lpSrcDIBBits= (char *)lpSrcStartBits + lLineBytes * (lHeight - 1 - i) + j;// ָ��ԴDIB��i�У���j�����ص�ָ��
			lpDstDIBBits= (char *)lpDstStartBits + lDstLineBytes * (lWidth - 1 - j) + i;// ָ��ת��DIB��j�У���i�����ص�ָ��			
			*(lpDstDIBBits)= *(lpSrcDIBBits);			// ��������			
		}		
	}	
	memcpy(lpSrcStartBits, lpDstStartBits, static_cast<size_t>(lWidth) * lDstLineBytes);// ����ת�ú��ͼ��
	lpbmi->biWidth = lHeight;		
	lpbmi->biHeight = lWidth;
	
	LocalUnlock(hDstDIBBits);							// �ͷ��ڴ�
	LocalFree(hDstDIBBits);								
	return TRUE;										// ����
}

/*************************************************************************
 * �������ƣ�Mirror(LPSTR lpSrcStartBits, long lWidth, long lHeight,long lLineBytes)
 * ��������:
     LPSTR	lpSrcStartBits,ָ��DIB��ʼ���ص�ָ��
	 long	lWidth��DIBͼ��Ŀ��
	 long	lHeight��DIBͼ��ĸ߶�
	 long	lLineBytes��DIBͼ������ֽ�����Ϊ4�ı���
 * ��������:BOOL        
 * ��������:�ú�����������DIBͼ�󣬱�����ֻʵ����ˮƽ���񣬴�ֱ�����ԭ������Ҳ̸���� ������ʵ��           
 ************************************************************************/

BOOL  Mirror(LPSTR lpSrcStartBits, long lWidth, long lHeight,long lLineBytes)
{	
	long i;                 //��ѭ������
	long j;                 //��ѭ������
	LPSTR	lpSrcDIBBits;	//ָ��Դ���ص�ָ��
	LPSTR	lpDstDIBBits;	//ָ����ʱͼ���Ӧ���ص�ָ�� 		
	HLOCAL	hDstDIBBits;	//��ʱͼ����
	LPSTR	lpBits;	// ָ���м����ص�ָ�룬������ͼ��ʱ���ṩ��ʱ�������ڴ�ռ�
	hDstDIBBits= LocalAlloc(LHND, lLineBytes);// ������ʱ�ڴ汣����ͼ��
	if (hDstDIBBits == NULL)		
	{		
		return FALSE;									// �����ڴ�ʧ��
	}		
	lpDstDIBBits= (char * )LocalLock(hDstDIBBits);// ����				
	for(i = 0; i < lHeight; i++)// ˮƽ�������ͼ��ÿ�н��в���
	{			
			for(j = 0; j < lWidth / 2; j++)// ���ÿ��ͼ����벿�ֽ��в���
			{							
				lpSrcDIBBits= (char *)lpSrcStartBits + lLineBytes * i + j;// ָ������i�У���j�����ص�ָ��								
				lpBits= (char *)lpSrcStartBits + lLineBytes * (i + 1) - j;// ָ������i+1�У�������j�����ص�ָ��								
				*lpDstDIBBits=*lpBits;//�����м�����								
				*lpBits = *lpSrcDIBBits;// ��������i�У���j�����ظ��Ƶ�������i�У�������j������								
				*lpSrcDIBBits=*lpDstDIBBits;// ��������i�У�������j�����ظ��Ƶ�������i�У���j������
			}			
	}		
	LocalUnlock(hDstDIBBits);// �ͷ��ڴ�
	LocalFree(hDstDIBBits);
	return TRUE;
}
/*************************************************************************
 * �������ƣ�GrayEqualize(LPSTR lpSrcStartBits, long lWidth, long lHeight,long	lLineBytes)
 * ��������:
     LPSTR	lpSrcStartBits,ָ��DIB��ʼ���ص�ָ��
	 long	lWidth��DIBͼ��Ŀ��
	 long	lHeight��DIBͼ��ĸ߶�
	 long	lLineBytes��DIBͼ������ֽ�����Ϊ4�ı���
 * ��������:BOOL        
 * ��������:�ú�����������ֱ��ͼ����
 ************************************************************************/

BOOL  GrayEqualize(LPSTR lpSrcStartBits, long lWidth, long lHeight,long	lLineBytes)
{			
	long i;                 //��ѭ������
	long j;                 //��ѭ������
	unsigned char*	lpSrcUnChr;	//ָ�����ص�ָ��

	BYTE	bGrayMap[256];// �Ҷ�ӳ��		
	long	lGrayNum[256];// �Ҷ�ӳ��		
	for (i = 0; i < 256; i ++)// ��0
	{		
		lGrayNum[i] = 0;
	}		
	for (i = 0; i < lHeight; i ++)// ���Ҷ�ֵ����
	{
		for (j = 0; j < lWidth; j ++)
		{
			lpSrcUnChr=(unsigned char*)lpSrcStartBits + lLineBytes * i + j;						
			lGrayNum[*(lpSrcUnChr)]++;// ��1
		}
	}		
	for (i = 0; i < 256; i++)// ����Ҷ�ӳ���
	{		
		long    varLong;		//��ʱ����
		varLong = 0;// ��ʼΪ0		
		for (j = 0; j <= i ; j++)
		{
			varLong += lGrayNum[j];
		}				
		bGrayMap[i] = (BYTE) (varLong * 255 / lHeight / lWidth);// �����Ӧ���»Ҷ�ֵ
	}		
	for(i = 0; i < lHeight; i++)// ��
	{		
		for(j = 0; j < lWidth; j++)// ��
		{
			// ָ��DIB��i�У���j�����ص�ָ��(unsigned char*)
			lpSrcUnChr= (unsigned char*)lpSrcStartBits + lLineBytes * (lHeight - 1 - i) + j;						
			*lpSrcUnChr= bGrayMap[*lpSrcUnChr];// �����µĻҶ�ֵ
		}
	}
	return TRUE;	
}
/*************************************************************************
 * �������ƣ�LineTranslation(LPSTR lpSrcStartBits, long lWidth, long lHeight, float fSlope, float fIntercept,long lLineBytes)
 * ��������:
 *   LPSTR lpSrcStartBits��ָ��ԴDIBͼ����ʼ���ص�ָ��
 *   long  lWidth��DIBͼ����
 *   long  lHeight��DIBͼ��߶�
 *   float fSlope��б��
 *   float fIntercept���ؾ�
 *   LONGlLineBytes��DIBͼ������ֽ�����Ϊ4�ı���
 * ��������:BOOL        
 * ��������:�ú���������ͼ����лҶȵ����Ա任����
 ************************************************************************/
BOOL  LineTranslation(LPSTR lpSrcStartBits, long lWidth, long lHeight, float fSlope, float fIntercept,long lLineBytes)
{		
	long i;                 //��ѭ������
	long j;                 //��ѭ������
	float varFloat;        //�����������
	unsigned char*	lpSrcUnChr;	//ָ�����ص�ָ��	
	for(i=0;i<lHeight;i++)// ��
	{		
		for(j=0; j<lWidth; j++)// ��
		{			
			lpSrcUnChr=(unsigned char*)lpSrcStartBits+lLineBytes*(lHeight-1-i)+j;// ָ��DIB��i�У���j�����ص�ָ��						
			varFloat=fSlope*(*lpSrcUnChr)+fIntercept;// ���Ա任						
			if (varFloat>255)// ������Χֱ�Ӹ�ֵΪ255
			{				
				*lpSrcUnChr=255;
			}
			else if(varFloat<0)
			{				
				*lpSrcUnChr=0;// ֱ�Ӹ�ֵΪ0
			}
			else
			{				
				*lpSrcUnChr=(unsigned char)(varFloat+0.5);// ����
			}
		}
	}
	return TRUE;
}
/*************************************************************************
 * �������ƣ�ThresholdTranslation(LPSTR lpSrcStartBits, long lWidth, long lHeight, BYTE bThreshold,long lLineBytes)
 * ��������:
     LPSTR	lpSrcStartBits,ָ��DIB��ʼ���ص�ָ��
	 long	lWidth��DIBͼ��Ŀ��
	 long	lHeight��DIBͼ��ĸ߶�
	 long	lLineBytes��DIBͼ������ֽ�����Ϊ4�ı���
 * ��������:BOOL        
 * ��������:�ú���������ͼ�������ֵ�任 
 ************************************************************************/

BOOL  ThresholdTranslation(LPSTR lpSrcStartBits, long lWidth, long lHeight, 
						   BYTE bThreshold,long lLineBytes)
{			
	long i;                 //��ѭ������
	long j;                 //��ѭ������
	unsigned char*	lpSrcUnChr;	//ָ�����ص�ָ��
	for(i = 0; i < lHeight; i++)// ��
	{		
		for(j = 0; j < lWidth; j++)// ��
		{			
			lpSrcUnChr= (unsigned char*)lpSrcStartBits + lLineBytes * (lHeight - 1 - i) + j;// ָ��DIB��i�У���j�����ص�ָ��			
			if ((*lpSrcUnChr) <bThreshold)// С����ֱֵ�Ӹ�ֵΪ0
			{
				*lpSrcUnChr= 0;
			}
			else
			{				
				*lpSrcUnChr= 255;// ��ֵΪ255
			}
		}
	}
	return TRUE;
}
/*************************************************************************
 * �������ƣ�LogTranslation(LPSTR lpSrcStartBits, long lWidth, long lHeight, long lLineBytes)
 * ��������:
     LPSTR	lpSrcStartBits,ָ��DIB��ʼ���ص�ָ��
	 long	lWidth��DIBͼ��Ŀ��
	 long	lHeight��DIBͼ��ĸ߶�
	 long	lLineBytes��DIBͼ������ֽ�����Ϊ4�ı���
 * ��������:BOOL        
 * ��������:�ú���������ͼ����ж����任 
 ************************************************************************/

BOOL  LogTranslation(LPSTR lpSrcStartBits, long lWidth, long lHeight, long lLineBytes)
{			
	long i;                 //��ѭ������
	long j;                 //��ѭ������
	unsigned char*	lpSrcUnChr;	//ָ�����ص�ָ��
	for(i = 0; i < lHeight; i++)// ��
	{		
		for(j = 0; j < lWidth; j++)// ��
		{	
			lpSrcUnChr= (unsigned char*)lpSrcStartBits + lLineBytes * (lHeight - 1 - i) + j;// ָ��DIB��i�У���j�����ص�ָ��
			//*lpSrcUnChr=50*(unsigned char)log((*lpSrcUnChr+1));
			*lpSrcUnChr = 255 * (unsigned char)log((*lpSrcUnChr + 1))/log(255);
		}
	}
	return TRUE;
}

/*************************************************************************
 * �������ƣ�WindowTranslation(LPSTR lpSrcStartBits, long lWidth, long lHeight, BYTE bLower, BYTE bUpper,long	lLineBytes)
 * ��������:
 *   LPSTR lpSrcStartBits��ָ��ԴDIBͼ����ʼ���ص�ָ��
 *   long  lWidth��DIBͼ����
 *   long  lHeight��DIBͼ��߶�
 *   BYTE	bLower�����ڱ任����
 *   BYTE	bUpper�����ڱ任����
 *   LONGl	LineBytes��DIBͼ������ֽ�����Ϊ4�ı���
 * ��������:BOOL        
 * ��������:�ú���������ͼ����д��ڱ任
 ************************************************************************/

BOOL  WindowTranslation(LPSTR lpSrcStartBits, long lWidth, long lHeight, BYTE bLower, BYTE bUpper,long	lLineBytes)
{			
	long i;                 //��ѭ������
	long j;                 //��ѭ������
	unsigned char*	lpSrcUnChr;	//ָ�����ص�ָ��
	for(i = 0; i < lHeight; i++)// ��
	{		
		for(j = 0; j < lWidth; j++)// ��
		{			
			lpSrcUnChr= (unsigned char*)lpSrcStartBits + lLineBytes * (lHeight - 1 - i) + j;// ָ��DIB��i�У���j�����ص�ָ��						
			if ((*lpSrcUnChr) < bLower)// ������Χֱ�Ӹ�ֵ
			{				
				*lpSrcUnChr= 0;
			}
			else if ((*lpSrcUnChr) > bUpper)
			{				
				*lpSrcUnChr= 255;// ֱ�Ӹ�ֵΪ255
			}
		}
	}	
	return TRUE;
}

/*************************************************************************
 * �������ƣ�GrayStretch(LPSTR lpSrcStartBits, long lWidth, long lHeight, BYTE bPointX1, BYTE bPointY1, BYTE bPointX2, BYTE bPointY2,long lLineBytes)
 * ��������:
 *   LPSTR lpSrcStartBits��ָ��ԴDIBͼ����ʼ���ص�ָ��
 *   long  lWidth��DIBͼ����
 *   long  lHeight��DIBͼ��߶�
 *	 BYTE bPointX1,��һ�����X����
 *   BYTE bPointY1,��һ�����Y����
 *   BYTE bPointX2,�ڶ������X����
 *   BYTE bPointY2,�ڶ������Y����
 *   LONGl	LineBytes��DIBͼ������ֽ�����Ϊ4�ı���
 * ��������:BOOL        
 * ��������:�ú���������ͼ����лҶ�����
 ************************************************************************/

BOOL  GrayStretch(LPSTR lpSrcStartBits, long lWidth, long lHeight, BYTE bPointX1, BYTE bPointY1, BYTE bPointX2, BYTE bPointY2,long lLineBytes)
{		
	long i;                 //��ѭ������
	long j;                 //��ѭ������
	unsigned char*	lpSrcUnChr;	//ָ�����ص�ָ��
	BYTE	bMap[256];// �Ҷ�ӳ��			
	for (i = 0; i <= bPointX1; i++)// ����Ҷ�ӳ��
	{		
		if (bPointX1 > 0)// �ж�bPointX1�Ƿ����0			
		{
			bMap[i] = (BYTE) bPointY1 * i / bPointX1;// �任
		}
		else
		{			
			bMap[i] = 0;// ��ֵΪ0
		}
	}
	for (; i <= bPointX2; i++)
	{		
		if (bPointX2 != bPointX1)// �ж�bPointX1�Ƿ����bPointX2			
		{
			bMap[i] = bPointY1 + (BYTE) ((bPointY2 - bPointY1) * (i - bPointX1) / (bPointX2 - bPointX1));// �任
		}
		else
		{			
			bMap[i] = bPointY1;// ��ֵΪbPointY1
		}
	}
	for (; i < 256; i++)
	{		
		if (bPointX2 != 255)// �ж�bPointX2�Ƿ����255			
		{
			bMap[i] = bPointY2 + (BYTE) ((255 - bPointY2) * (i - bPointX2) / (255 - bPointX2));//�任
		}
		else
		{			
			bMap[i] = 255;// ��ֵΪ255
		}
	}		
	for(i = 0; i < lHeight; i++)// ��
	{		
		for(j = 0; j < lWidth; j++)// ��
		{			
			lpSrcUnChr= (unsigned char*)lpSrcStartBits + lLineBytes * (lHeight - 1 - i) + j;// ָ��DIB��i�У���j�����ص�ָ��						
			*lpSrcUnChr= bMap[*lpSrcUnChr];// �»Ҷ�ֵ
		}
	}
	return TRUE;
}
/*************************************************************************
 * �������ƣ�Translation(LPSTR lpSrcStartBits, long lWidth, long lHeight, long lXOffset, 
							long lYOffset,long lLineBytes,long lDstLineBytes)
 * ��������:
 *   LPSTR	lpSrcStartBits��ָ��ԴDIB��ʼ���ص�ָ��
 * 	 long	lWidth��DIBͼ��Ŀ��
 * 	 long	lHeight��DIBͼ��ĸ߶�
 * 	 long	lXOffset,X����ƫ����
 * 	 long	lYOffset,Y����ƫ����
 * 	 long	lLineBytes��DIBͼ������ֽ�����Ϊ4�ı���
 * 	 long	lDstLineBytes����ʱDIBͼ������ֽ�����Ϊ4�ı���
 * ��������:BOOL        
 * ��������:�ú�������ƽ��DIBͼ��
 ************************************************************************/
BOOL  Translation(LPSTR lpSrcStartBits, long lWidth, long lHeight, 
				  long lXOffset, long lYOffset,long lLineBytes,long lDstLineBytes)					 
{	
	long i;                 //��ѭ������
	long j;                 //��ѭ������
	LPSTR	lpSrcDIBBits;	//ָ��Դ���ص�ָ��
	LPSTR	lpDstDIBBits;	//ָ����ʱͼ���Ӧ���ص�ָ��
	LPSTR	lpDstStartBits;	//ָ����ʱͼ���Ӧ���ص�ָ�� 		
	HLOCAL	hDstDIBBits;	//��ʱͼ����

	hDstDIBBits= LocalAlloc(LHND, lWidth * lDstLineBytes);// ������ʱ�ڴ�
	lpDstStartBits= (char * )LocalLock(hDstDIBBits);// �����ڴ�	
	if (hDstDIBBits== NULL)// �ж��Ƿ��ڴ����		
		return FALSE;// �����ڴ�ʧ��				
	for(i = 0; i < lHeight; i++)// ��
	{
			for(j = 0; j < lWidth; j++)	// ��
		{
				lpDstDIBBits=(char*)lpDstStartBits+lLineBytes*(lHeight-1-i)
				+j;// ָ����DIB��i�У���j�����ص�ָ��												
			if( (j-lYOffset>= 0) && (j-lYOffset< lWidth) && // ������ԴDIB�е�����j-lXOffset
				(i-lXOffset>= 0) && (i-lXOffset < lHeight))// �ж��Ƿ���Դͼ��Χ��
			{
				lpSrcDIBBits=(char *)lpSrcStartBits+lLineBytes*(lHeight-1-
					(i-lXOffset))+(j-lYOffset);// ָ��ԴDIB��i0�У���j0�����ص�ָ��								
				*lpDstDIBBits= *lpSrcDIBBits;// ��������
			}
			else
			{				
				* ((unsigned char*)lpDstDIBBits) = 255;// Դͼ��û�е����أ���Ϊ255
			}			
		}
	}
	memcpy(lpSrcStartBits, lpDstStartBits, lLineBytes * lHeight);// ����ͼ��		
	LocalUnlock(hDstDIBBits);// �ͷ��ڴ�
	LocalFree(hDstDIBBits);		
	return TRUE;
}

/*************************************************************************
 * �������ƣ�Rotate(LPSTR lpSrcDib, LPSTR lpSrcStartBits,long lWidth, long lHeight,
				   long lLineBytes,	WORD palSize, long lDstWidth, 
				   long lDstHeight,long lDstLineBytes,float	fSina, float fCosa)
 * ��������:
 *   LPSTR lpSrcDib,ָ��ԴDIB��ָ��
 *   LPSTR lpSrcStartBits,ָ��ԴDIB����ʼ���ص�ָ��
 *   long lWidth,ԴDIBͼ����
 *   long lHeight,ԴDIBͼ��߶�
 *	 long lLineBytes,ԴDIBͼ���ֽڿ�ȣ�4�ı�����
 *	 WORD palSize,ԴDIBͼ���ɫ���С
 *	 long lDstWidth,Ŀ��ͼ����
 *	 long lDstHeight,Ŀ��DIBͼ��߶�
 *	 long lDstLineBytes,Ŀ��DIBͼ�����ֽ�����4�ı�����
 *	 float	fSina,��ת�ǵ����ң�˵����Ϊ�˱���������ȡ�����ң�������Ϊ����������������
 *	 float fCosa,��ת�ǵ�����
 * ��������:HGLOBAL
 * ��������:������תDIBͼ��
 ************************************************************************/
HGLOBAL  Rotate(LPSTR lpSrcDib, LPSTR lpSrcStartBits,long lWidth, long lHeight,
				   long lLineBytes,	WORD palSize, long lDstWidth, 
				   long lDstHeight,long lDstLineBytes,float	fSina, float fCosa)
{	
	float varFloat1;        //�����������1
	float varFloat2;        //�����������2
	LPSTR	lpDstDib;		//ָ����ʱͼ���ָ��
	
	long i;                 //��ѭ������
	long j;                 //��ѭ������
	long i1;                 //��ѭ������
	long j1;                 //��ѭ������
	LPSTR	lpSrcDIBBits;	//ָ��Դ���ص�ָ��
	LPSTR	lpDstDIBBits;	//ָ����ʱͼ���Ӧ���ص�ָ��
	LPSTR	lpDstStartBits;	//ָ����ʱͼ���Ӧ���ص�ָ�� 			

	LPBITMAPINFOHEADER lpbmi;// ָ��BITMAPINFOHEADER�ṹ��ָ��		
	varFloat1= (float) (-0.5 * (lDstWidth - 1) * fCosa - 0.5 * (lDstHeight - 1) * fSina// �������õ���������������������Ա���Ϊ����ʹ��
		+ 0.5 * (lDstWidth  - 1));
	varFloat2= (float) ( 0.5 * (lDstWidth - 1) * fSina - 0.5 * (lDstHeight - 1) * fCosa
		+ 0.5 * (lDstHeight - 1));		
	HGLOBAL hDIB = (HGLOBAL) ::GlobalAlloc(GHND, lDstLineBytes * lDstHeight + *(LPDWORD)lpSrcDib +palSize);// �����ڴ棬�Ա�����DIB		
	if (hDIB == NULL)// �ж��Ƿ�����Ч��DIB����
	{		
		return FALSE;// ���ǣ��򷵻�
	}	
	lpDstDib=  (char * )::GlobalLock((HGLOBAL) hDIB);// �����ڴ�		
	memcpy(lpDstDib,lpSrcDib, *(LPDWORD)lpSrcDib +palSize);// ����DIB��Ϣͷ�͵�ɫ��			
	
	lpbmi = (LPBITMAPINFOHEADER)lpDstDib;// ��ȡָ��	
	lpbmi->biHeight=lDstHeight;// ����DIB��ͼ��ĸ߶ȺͿ��
	lpbmi->biWidth =lDstWidth;

	lpDstStartBits=lpDstDib+ *(LPDWORD)lpDstDib
		+palSize;// ��������ʼλ��,������ͬ::FindDIBBits(gCo.lpSrcDib)�����ﳢ��ʹ�������ַ������Ա����ȫ�ֺ����ĵ���
	
	for(i = 0; i < lDstHeight; i++)// �в���
	{		
		for(j = 0; j < lDstWidth; j++)// �в���
		{			
			lpDstDIBBits= (char *)lpDstStartBits+ lDstLineBytes * (lDstHeight - 1 - i) + j;// ָ����DIB��i�У���j�����ص�ָ��			
			i1= (long) (-((float) j) * fSina + ((float) i) * fCosa + varFloat2 + 0.5);// �����������ԴDIB�е�����
			j1= (long) ( ((float) j) * fCosa + ((float) i) * fSina + varFloat1 + 0.5);						
			if( (j1>= 0) && (j1< lWidth) && (i1>= 0) && (i1< lHeight))
			{// �ж��Ƿ���Դͼ��				
				lpSrcDIBBits= (char *)lpSrcStartBits+ lLineBytes * (lHeight - 1 -i1) + j1;// ָ��ԴDIB��i0�У���j0�����ص�ָ��								
				*lpDstDIBBits= *lpSrcDIBBits;// ��������
			}
			else
			{
				* ((unsigned char*)lpDstDIBBits) = 255;// Դͼ�в����ڵ����أ���Ϊ255
			}			
		}		
	}
	return hDIB;
}

/*************************************************************************
 * �������ƣ�Zoom(LPSTR lpSrcDib, LPSTR lpSrcStartBits,long lWidth, long lHeight,
				   long lLineBytes,	WORD palSize, long lDstWidth, 
				   long lDstHeight,long lDstLineBytes,float	fXZoomRatio, float fYZoomRatio)
 * ��������:
 *   LPSTR lpSrcDib,ָ��ԴDIB��ָ��
 *   LPSTR lpSrcStartBits,ָ��ԴDIB����ʼ���ص�ָ��
 *   long lWidth,ԴDIBͼ����
 *   long lHeight,ԴDIBͼ��߶�
 *	 long lLineBytes,ԴDIBͼ���ֽڿ�ȣ�4�ı�����
 *	 WORD palSize,ԴDIBͼ���ɫ���С
 *	 long lDstWidth,Ŀ��ͼ����
 *	 long lDstHeight,Ŀ��DIBͼ��߶�
 *	 long lDstLineBytes,Ŀ��DIBͼ�����ֽ�����4�ı�����
 *	 float	fhorRatio,ˮƽ���ű���
 *	 float fverRatio,��ֱ���ű���
 * ��������:HGLOBAL
 * ��������:��������DIBͼ��
 ************************************************************************/

HGLOBAL  Zoom(LPSTR lpSrcDib, LPSTR lpSrcStartBits,long lWidth, long lHeight,
				   long lLineBytes,	WORD palSize,long lDstWidth,long lDstLineBytes,long lDstHeight,
				   float fhorRatio,float fverRatio)
{			
	LPSTR	lpDstDib;		//ָ����ʱͼ���ָ��	
	long i;                 //��ѭ������
	long j;                 //��ѭ������
	long i1;                 //��ѭ������
	long j1;                 //��ѭ������
	LPSTR	lpSrcDIBBits;	//ָ��Դ���ص�ָ��
	LPSTR	lpDstDIBBits;	//ָ����ʱͼ���Ӧ���ص�ָ��
	LPSTR	lpDstStartBits;	//ָ����ʱͼ���Ӧ���ص�ָ�� 		
			
	LPBITMAPINFOHEADER lpbmi;// ָ��BITMAPINFO�ṹ��ָ��
		
	// �����ڴ棬�Ա������ź��DIB
	HGLOBAL hDIB = (HGLOBAL) ::GlobalAlloc(GHND, lDstLineBytes* lDstHeight + *(LPDWORD)lpSrcDib +palSize);	
	if (hDIB == NULL)// �ж��Ƿ�����Ч��DIB����
	{		
		return FALSE;// ���ǣ��򷵻�
	}		
	lpDstDib=  (char * )::GlobalLock((HGLOBAL) hDIB);// �����ڴ�		
	memcpy(lpDstDib, lpSrcDib, *(LPDWORD)lpSrcDib +palSize);// ����DIB��Ϣͷ�͵�ɫ��		
	
	lpDstStartBits=lpDstDib+ *(LPDWORD)lpDstDib// �ҵ���DIB������ʼλ��
		+palSize;// ��������ʼλ��,������ͬ::FindDIBBits(lpSrcDib)�����ﳢ��ʹ�������ַ������Ա����ȫ�ֺ����ĵ���		
	lpbmi = (LPBITMAPINFOHEADER)lpDstDib;// ��ȡָ��
		
	lpbmi->biWidth = lDstWidth;// ����DIB��ͼ��ĸ߶ȺͿ��
	lpbmi->biHeight =lDstHeight;	
	
	for(i = 0; i < lDstHeight; i++)// �в���
	{		
		for(j = 0; j < lDstWidth; j++)// �в���
		{
			// ָ����DIB��i�У���j�����ص�ָ��
			lpDstDIBBits= (char *)lpDstStartBits + lDstLineBytes * (lDstHeight-1-i)+j;						
			i1= (long) (i / fverRatio + 0.5);// �����������ԴDIB�е�����
			j1= (long) (j / fhorRatio + 0.5);			
			
			if( (j1>= 0) && (j1< lWidth) && (i1>= 0) && (i1< lHeight))
			{// �ж��Ƿ���Դͼ��				
				lpSrcDIBBits= (char *)lpSrcStartBits+ lLineBytes * (lHeight - 1 -i1) + j1;// ָ��ԴDIB��i�У���j�����ص�ָ��								
				*lpDstDIBBits= *lpSrcDIBBits;// ��������
			}
			else
			{
				* ((unsigned char*)lpDstDIBBits) = 255;// Դͼ�в����ڵ����أ���Ϊ255
			}				
		}		
	}
	return hDIB;
}

/*************************************************************************
 * �������ƣ�FastFourierTran(CplexNum * pTd, CplexNum* pFd, int power)
 * ��������:
 *   CplexNum * pTd,ָ��ʱ�������ָ��
 *   CplexNum * pFd,ָ��Ƶ�������ָ��
 *   int             power,2������������������
 * ��������:void 
 ��������:����ʵ�ֿ��ٸ���Ҷ�任
************************************************************************/
void  FastFourierTran(CplexNum * pTd, CplexNum * pFd, int power)
{	
	long i;                 //��ѭ������
	long j;                 //��ѭ������
 			
	long	dotCount;// ����Ҷ�任����		
	int		k;// ѭ������		
	int		bfsize,p;// �м����		
	double	angle;// �Ƕ�	
	CplexNum *pWn,*temReg1,*temReg2,*temReg;	
	
	dotCount= 1 <<power;// ���㸶��Ҷ�任����		
	pWn= new CplexNum[sizeof(CplexNum)*dotCount/ 2];// ������������洢��
	temReg1 = new CplexNum[sizeof(CplexNum)*dotCount];
	temReg2 = new CplexNum[sizeof(CplexNum)*dotCount];		
	for(i = 0; i < dotCount/ 2; i++)// �����Ȩϵ��
	{
		angle = -i * pi* 2 / dotCount;
		pWn[i].re = cos(angle);
		pWn[i].im=sin(angle);
	}	
	memcpy(temReg1, pTd, sizeof(CplexNum)*dotCount);// ��ʱ���д��temReg1		
	for(k = 0; k < power; k++)// ���õ����㷨���п��ٸ���Ҷ�任
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
	for(j = 0; j <dotCount; j++)// ��������
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
	delete pWn;// �ͷ��ڴ�
	delete temReg1;
	delete temReg2;
}

/*************************************************************************
 *
 * �������ƣ�InverFastFourierTran(CplexNum * pFd, CplexNum * pTd, int power)
 * ��������:
 *   CplexNum  * pFd��ָ��Ƶ��ֵ��ָ��
 *   CplexNum * pTd��ָ��ʱ��ֵ��ָ��
 *   int power	��2������
 *��������:void
 *��������:����ʵ�ֿ��ٸ���Ҷ���任
 ************************************************************************/
void  InverFastFourierTran(CplexNum * pFd, CplexNum * pTd, int power)
{	
	LONG	dotCount;			// ����Ҷ�任����	
	int		i;				// ѭ������
	CplexNum *pX;		
	dotCount= 1 << power;		// ���㸶��Ҷ�任����		
	pX = new CplexNum[sizeof(CplexNum)*dotCount];// ������������洢��		
	memcpy(pX, pFd, sizeof(CplexNum)*dotCount);// ��Ƶ���д��X		
	for(i = 0; i <dotCount; i++)// ����
	{
		pX[i].re= pX[i].re;
		pX[i].im=-pX[i].im;
	}	
	FastFourierTran(pX, pTd, power);// ���ÿ��ٸ���Ҷ�任		
	for(i = 0; i <dotCount; i++)// ��ʱ���Ĺ���
	{
		pTd[i].re =pTd[i].re/dotCount;
		pTd[i].im=-pTd[i].im/dotCount;

	}		
	delete pX;				// �ͷ��ڴ�
}

/*************************************************************************
 * �������ƣ�Fourier(CplexNum * pTd, int lWidth, int lHeight, CplexNum * pFd)
 * ��������:
 *   CplexNum * pTd��ָ��ʱ��ֵ��ָ��
 *   int    lWidth��ͼ����
 *   int    lHeight��ͼ��߶�
 *   CplexNum * pFd	��ָ��Ƶ��ֵ��ָ��
 *
 * ��������:void
 * ��������:��ά���ٸ���Ҷ�任
 *************************************************************************/
void  Fourier(CplexNum * pTd, int lWidth, int lHeight, CplexNum * pFd)
{
	
	// ѭ�����Ʊ���
	int	j;
	int	i;
	// ���и���Ҷ�任�Ŀ�Ⱥ͸߶ȣ���2���������ݣ�
	// ͼ��Ŀ�Ⱥ͸߶Ȳ�һ��Ϊ2����������
	int		wid=1;
	int 	hei=1;
	int		widpor=0,heiPor=0;//2������

	while(wid * 2 <= lWidth)// ������и���Ҷ�任�Ŀ�Ⱥ͸߶ȣ�2�������η���
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
		// x������п��ٸ���Ҷ�任
		FastFourierTran(&pTd[wid * i], &pFd[wid * i], widpor);
	}
	
	// pFd��Ŀǰ�洢��pTd�����б任�Ľ��
	// Ϊ��ֱ������FastFourierTran����Ҫ��pFd�Ķ�ά����ת�ã���һ������FastFourierTran����
	// ����Ҷ�б任��ʵ�����൱�ڶ��н��и���Ҷ�任��
	for(i = 0; i < hei; i++)
	{
		for(j = 0; j < wid; j++)
		{
			pTd[hei * j + i] = pFd[wid * i + j];
		}
	}
	
	for(j = 0; j < wid; j++)
	{
		// ��x������п��ٸ���Ҷ�任��ʵ�����൱�ڶ�ԭ����ͼ�����ݽ����з����
		// ����Ҷ�任
		FastFourierTran(&pTd[j * hei], &pFd[j * hei], heiPor);
	}

	// pFd��Ŀǰ�洢��pTd������ά����Ҷ�任�Ľ��������Ϊ�˷����з���
	// �ĸ���Ҷ�任�����������ת�ã����ڰѽ��ת�û���
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
 * �������ƣ�InverseFourier(CplexNum * pFd, CplexNum * pTd, int lWidth, int lHeight)
 * ��������:
 *   CplexNum * pTd��ָ��ʱ��ֵ��ָ��
 *   CplexNum * pFd	��ָ��Ƶ��ֵ��ָ��
 *   int    lWidth��ͼ����
 *   int    lHeight��ͼ��߶�
 * ��������:void
 * ��������:��ά���ٸ���Ҷ���任
 *************************************************************************/
void  InverseFourier(CplexNum * pFd, CplexNum * pTd, int lWidth, int lHeight)
{
	// ѭ�����Ʊ���
	int	j;
	int	i;
	// ���и���Ҷ�任�Ŀ�Ⱥ͸߶ȣ���2���������ݣ�
	// ͼ��Ŀ�Ⱥ͸߶Ȳ�һ��Ϊ2����������
	int		wid=1;
	int 	hei=1;
	int		widpor=0,heiPor=0;//2������

	while(wid * 2 <= lWidth)// ������и���Ҷ�任�Ŀ�Ⱥ͸߶ȣ�2�������η���
	{
		wid *= 2;
		widpor++;
	}	
	while(hei * 2 <= lHeight)
	{
		hei *= 2;
		heiPor++;
	}		
	// ���乤����Ҫ���ڴ�ռ�
	CplexNum *pCWork= new CplexNum[sizeof(CplexNum)*wid * hei];

	//��ʱ����
	CplexNum *pCTmp ;
	
	// Ϊ�����ø���Ҷ���任,���԰Ѹ���ҶƵ�������ȡ����
	// Ȼ��ֱ���������任�����������Ǹ���Ҷ���任����Ĺ���
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

	// ���ø���Ҷ���任
	Fourier(pCWork, lWidth, lHeight, pTd) ;
	
	// ��ʱ���Ĺ��������ս��
	// ���ݸ���Ҷ�任ԭ�����������ķ�����õĽ����ʵ�ʵ�ʱ������
	// ���һ��ϵ��
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
 * �������ƣ�DisFCosTran(double *pTd, double *pFd, int power)
 * ��������:
 *   double * pTd,ָ��ʱ��ֵ��ָ��
 *   double * pFd,ָ��Ƶ��ֵ��ָ��
 *   int    power,2������
 *
 * ��������:void
 * ��������: ����ʵ�ֿ�����ɢ���ұ任
 ************************************************************************/
void  DisFCosTran(double *pTd, double *pFd, int power)
{	
	long i;                 //��ѭ������				
	long	dotCount;// ��ɢ���ұ任����			
	double	dTemp;// ��ʱ����	
	CplexNum *temReg;		
	dotCount = 1<<power;// ������ɢ���ұ任����		
	temReg = new CplexNum[sizeof(CplexNum) *dotCount*2];// �����ڴ�		
	memset(temReg, 0, sizeof(CplexNum) * dotCount * 2);// ��Ϊ0		
	for(i=0;i<dotCount;i++)// ��ʱ���д������temReg
	{
		temReg[i].re=pTd[i];
		temReg[i].im=0;
	}		
	FastFourierTran(temReg,temReg,power+1);// ���ÿ��ٸ���Ҷ�任		
	dTemp = 1/sqrt(dotCount);// ����ϵ��		
	pFd[0] = temReg[0].re*dTemp;// ��pFd[0]	
	dTemp *= sqrt(2);		
	for(i = 1; i < dotCount; i++)// ��pFd[u]	
	{
		pFd[i]=(temReg[i].re* cos(i*pi/(dotCount*2)) + temReg[i].im* sin(i*pi/(dotCount*2))) * dTemp;
	}		
	delete temReg;// �ͷ��ڴ�
}

/*************************************************************************
 * �������ƣ�CosTran(LPSTR lpSrcStartBits, long lWidth, long lHeight,long lLineBytes)
 * ��������:
 *   LPSTR lpSrcStartBits,ָ��DIB��ʼ���ص�ָ��
 *   long lWidth,DIB�Ŀ��
 *   long lHeight,DIB�ĸ߶�
 *	 long lLineBytes,DIB�����ֽ�����Ϊ4�ı���
 * ��������:BOOL
 * ��������: ������ͼ�������ɢ���ұ任
************************************************************************/
BOOL  CosTran(LPSTR lpSrcStartBits, long lWidth, long lHeight,long lLineBytes)
{		
	unsigned char*	lpSrcUnChr;	//ָ�����ص�ָ��
	long i;                 //��ѭ������
	long j;                 //��ѭ������ 			
	long	wid=1,hei=1;// ���и���Ҷ�任�Ŀ�Ⱥ͸߶ȣ���ʼ��Ϊ1
	double	dTemp;// �м����	
	int		widpor=0,heiPor=0;//2������

	while(wid * 2 <= lWidth)// ���������ɢ���ұ任�Ŀ�Ⱥ͸߶ȣ�2�������η���
	{
		wid *= 2;
		widpor++;
	}	
	while(hei * 2 <= lHeight)
	{
		hei *= 2;
		heiPor++;
	}		
	double *pTd= new double[wid * hei];// �����ڴ�
	double *pFd = new double[wid * hei];		
	for(i = 0; i < hei; i++)// ��
	{		
		for(j = 0; j < wid; j++)// ��
		{
			// ָ��DIB��i�У���j�����ص�ָ��
			lpSrcUnChr= (unsigned char*)lpSrcStartBits + lLineBytes * (lHeight- 1 - i) + j;						
			pTd[j + i * wid] = *(lpSrcUnChr);// ��ʱ��ֵ
		}
	}	
	for(i = 0; i < hei; i++)
	{		
		DisFCosTran(&pTd[wid * i], &pFd[wid * i], widpor);// ��y���������ɢ���ұ任
	}		
	for(i = 0; i < hei; i++)// ���������
	{
		for(j = 0; j < wid; j++)
		{
			pTd[j * hei + i] = pFd[j + wid * i];
		}
	}	
	for(j = 0; j < wid; j++)
	{		
		DisFCosTran(&pTd[j * hei], &pFd[j * hei], heiPor);// ��x���������ɢ���ұ任
	}		
	for(i = 0; i < hei; i++)// ��
	{		
		for(j = 0; j < wid; j++)// ��
		{			
			dTemp = fabs(pFd[j*hei+i]);// ����Ƶ��
			
			
			if (dTemp > 255)// �Ƿ񳬹�255,�����ģ�ֱ������Ϊ255
			{
				dTemp = 255;
			}			
			// ָ��DIB��y�У���x�����ص�ָ��
			lpSrcUnChr= (unsigned char*)lpSrcStartBits + lLineBytes * (lHeight- 1 - i) + j;						
			* (lpSrcUnChr) = (BYTE)(dTemp);// ����Դͼ��
		}
	}		
	delete pTd;// �ͷ��ڴ�
	delete pFd;	
	return TRUE;
}

/*************************************************************************
 * �������ƣ�Walshei_Har(double *pTd, double *pFd, int power)
 * ��������:
 *   double * pTd,ָ��ʱ��ֵ��ָ��
 *   double * pFd,ָ��Ƶ��ֵ��ָ��
 *   int    power,2������
 *
 * ��������:void
 * ��������: ����ʵ�ֿ����ֶ�ʲ-������任
************************************************************************/

void  Walshei_Har(double *pTd, double *pFd, int power)
{	
	long	dotCount;// �ֶ�ʲ-������任����		
	int		i,j,k;// ѭ������	
	int		bfsize,p;// �м����	
	double *temReg1,*temReg2,*temReg;		
	dotCount = 1 << power;// ��������ֶ�ʲ�任����		
	temReg1 = new double[dotCount];// �����������������
	temReg2 = new double[dotCount];
	memcpy(temReg1, pTd, sizeof(double) * dotCount);// ��ʱ���д������temReg1		
	for(k = 0; k < power; k++)// ��������
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
		temReg = temReg1;// ����temReg1��temReg2  
		temReg1 = temReg2;
		temReg2 = temReg;
	}	
	for(j = 0; j < dotCount; j++)// ����ϵ��
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
	delete temReg1;// �ͷ��ڴ�
	delete temReg2;
}

/*************************************************************************
 * �������ƣ�Walsh_HarTran(LPSTR lpSrcStartBits, long lWidth, long lHeight,long lLineBytes)
 * ��������:
 *   LPSTR lpSrcStartBits,ָ��ԴDIBͼ��ָ��
 *   long  lWidth,ԴDIBͼ����
 *   long  lHeight,ԴDIBͼ��߶�
 *   long lLineBytes,ԴDIBͼ������ֽ�����Ϊ4�ı���
 * ��������:BOOL
 * ��������:������ͼ������ֶ�ʲ-������任
************************************************************************/

BOOL  Walsh_HarTran(LPSTR lpSrcStartBits, long lWidth, long lHeight,long lLineBytes)
{
	unsigned char*	lpSrcUnChr;	//ָ�����ص�ָ��	
	long i;                 //��ѭ������
	long j;                 //��ѭ������		

	long	wid=1,hei=1;// ���и���Ҷ�任�Ŀ�Ⱥ͸߶ȣ���ʼ��Ϊ1
	double	dTemp;// �м����	
	int		widpor=0,heiPor=0;//2������
	
	while(wid * 2 <= lWidth)// ���������ɢ���ұ任�Ŀ�Ⱥ͸߶ȣ�2�������η���
	{
		wid *= 2;
		widpor++;
	}	
	while(hei * 2 <= lHeight)
	{
		hei *= 2;
		heiPor++;
	}		
	double *pTd = new double[wid * hei];// �����ڴ�
	double *pFd = new double[wid * hei];		
	for(i = 0; i < hei; i++)// ��
	{
		
		for(j = 0; j < wid; j++)// ��
		{
			// ָ��DIB��i�У���j�����ص�ָ��
			lpSrcUnChr= (unsigned char*)lpSrcStartBits + lLineBytes * (lHeight- 1 - i) + j;						
			pTd[j + i * wid] = *(lpSrcUnChr);// ��ʱ��ֵ
		}
	}	
	for(i = 0; i < hei; i++)
	{		
		Walshei_Har(pTd + wid * i, pFd + wid * i, widpor);// ��y��������ֶ�ʲ-������任
	}		
	for(i = 0; i < hei; i++)// ���������
	{
		for(j = 0; j < wid; j++)
		{
			pTd[j * hei + i] = pFd[j + wid * i];
		}
	}	
	for(j = 0; j < wid; j++)
	{		
		Walshei_Har(pTd + j * hei, pFd+ j * hei, heiPor);// ��x��������ֶ�ʲ-������任
	}		
	for(i = 0; i < hei; i++)// ��
	{		
		for(j = 0; j < wid; j++)// ��
		{			
			dTemp = fabs(pFd[j * hei + i] * 1000);// ����Ƶ��						
			if (dTemp > 255)// ���ڳ���255�ģ�ֱ������Ϊ255
			{
				dTemp = 255;
			}			
			// ָ��DIB��i�У���j�����ص�ָ��
			lpSrcUnChr= (unsigned char*)lpSrcStartBits + lLineBytes * (lHeight- 1 - i) + j;						
			* (lpSrcUnChr) = (BYTE)(dTemp);// ����Դͼ��
		}
	}		
	delete pTd;//�ͷ��ڴ�
	delete pFd;
	return TRUE;
}

/*************************************************************************
 *
 * �������ƣ�
 *   DisK_L(LPSTR lpSrcStartBits, long lWidth, long lHeight,long lLineBytes)
 *��������:
 *   LPSTR lpSrcStartBits,ָ��ԴDIBͼ��ָ��
 *   long  lWidth,ԴDIBͼ����
 *   long  lHeight,ԴDIBͼ��߶�
 *   long lLineBytes,ԴDIBͼ������ֽ�����Ϊ4�ı���
 * ��������:BOOL
 * ��������:������ͼ�������ת
 ************************************************************************/

BOOL DisK_L(LPSTR lpSrcStartBits, long lWidth, long lHeight,long lLineBytes)
{
	unsigned char*	lpSrcUnChr;	//ָ�����ص�ָ��	
	LONG	i,j,// ѭ������
		    lMaxRange,// �����任��ͼ�������ܷ�Χ		
		    AverEx,AverEy,//  Ŀ�������ֵ		
		    ToaCount;//  Ŀ���ܵ�������	
	double  Matr4C[2][2],// ����ֵ��Э�������
			QMatrix[2][2],// ���Э����������������		
			MainCross[2],HypoCross[2],//  ���Խ�������ԽǺʹζԽ���Ԫ��		
			dTemp;// ��ʱ����
	LONG    lTempI,lTempJ;
				
	if(lWidth>lHeight)// ����ͼ�󾭹���ת��������Ŀ�Ⱥ͸߶�
	{
		lMaxRange = lWidth;
	}
	else
	{
		lMaxRange =lHeight;
	}
		
	AverEx=0.0;// ��ʼ��
	AverEy=0.0;
	ToaCount = 0;
	Matr4C[0][0] = Matr4C[0][1] = Matr4C[1][0] = Matr4C[1][1] = 0.0;
		
	double *F = new double[lWidth*lHeight];// �����ڴ�		
	for(i = 0; i < lHeight; i++)// ��
	{		
		for(j = 0; j < lWidth; j++)// ��
		{			
			F[i*lWidth + j] = 255;// ����ת���������ÿ���㸳��ֵ
			// ָ��λͼi��j�����ص�ָ��
			lpSrcUnChr= (unsigned char*)lpSrcStartBits + lLineBytes*i + j;
						
			// ֵС��255���Ǳ���ɫ��ɫ����������ΪĿ���һ����
			// ����������ֵx��y������ά���ʸ��
			if((*lpSrcUnChr) < 255)
			{				
				
				AverEx=AverEx+i;// ����Ŀ�����ص�Y�����X�����ۼ�ֵ
				AverEy=AverEy+j;				
				ToaCount++;// Ŀ���ܵ���������һ
                   
                // ���ʸ��Э���������ۼ�ֵ
				Matr4C[0][0] = Matr4C[0][0] + i*i;
                Matr4C[0][1] = Matr4C[0][1] + i*j;
				Matr4C[1][0] = Matr4C[1][0] + j*i;
				Matr4C[1][1] = Matr4C[1][1] + j*j;
			}
		}
	}
			
	AverEx = AverEx/ToaCount;// �������ʸ���ľ�ֵ
	AverEy = AverEy/ToaCount;
	
    Matr4C[0][0] = Matr4C[0][0]/ToaCount - AverEx*AverEx;//  �������ʸ����Э�������
	Matr4C[0][1] = Matr4C[0][1]/ToaCount - AverEx*AverEy;
	Matr4C[1][0] = Matr4C[1][0]/ToaCount - AverEx*AverEy;
	Matr4C[1][1] = Matr4C[1][1]/ToaCount - AverEy*AverEy;
    
	double Precision = 0.000001;// �涨�����ļ��㾫��
		
    ThreeCrossMat(*Matr4C, 2, *QMatrix, MainCross, HypoCross);// ��Э������������ԽǶԳ���		
	EigenvalueVector(2, MainCross,HypoCross, *Matr4C, Precision, 50);// ��Э������������ֵ������ʸ����
   	
    dTemp = Matr4C[0][1];// ������������ת��������������
	Matr4C[0][1] = Matr4C[1][0];
	Matr4C[1][0] = dTemp;
	
	for(i=0;i<=1;i++)
	{// ���������������й�һ��
		dTemp = pow(Matr4C[i][0],2) + pow(Matr4C[i][1],2);
		dTemp = sqrt(dTemp);
		Matr4C[i][0] = Matr4C[i][0]/dTemp;
		Matr4C[i][1] = Matr4C[i][1]/dTemp;
	}	
	// ���Ҿ���ɢK-L�任����������ԭ����ϵ�е�����    
    for(i = -lMaxRange+1; i < lMaxRange; i++)
	{
		for(j = -lMaxRange+1; j < lMaxRange; j++)
		{
			//  ��������ֵӳ�䵽�ɵ�����ϵ
			int Cx = (int)(i*Matr4C[0][0]-j*Matr4C[0][1])+AverEx;
			int Cy = (int)(-i*Matr4C[1][0]+j*Matr4C[1][1])+AverEy;
			
			//  ӳ��ֵ�Ƿ�����Դͼ��
			if( Cx>=0 && Cx<lHeight && Cy>=0 && Cy<lWidth )
			{
				lpSrcUnChr= (unsigned char*)lpSrcStartBits + lLineBytes*Cx + Cy;

				// ӳ��ֵ�Ƿ�����ԭ����Ŀ��
				if(*(lpSrcUnChr)<255)
				{
					//  ��������ϵԭ��ƽ�Ƶ����ģ��Ա���ʾ
					lTempI=(LONG)(lHeight/2)+j;
					lTempJ=(LONG)(lWidth/2)+i;

					// ������ܹ�������ʾ����ֵ�����飬���д洢
					if( lTempI>=0 && lTempI<lHeight && lTempJ>=0 && lTempJ<lWidth )
						F[lTempJ+ (lTempI) * lWidth]=*(lpSrcUnChr);
				}

			}		
		}
	}
		
	for(i = 0; i < lMaxRange; i++)// ��
	{		
		for(j = 0; j < lMaxRange; j++)// ��
		{			
		    dTemp = F[i * lMaxRange + j] ;// ��ɢK-L�任�������ֵ			
			// ָ��λͼi��j�����ص�ָ��
			lpSrcUnChr= (unsigned char*)lpSrcStartBits + lLineBytes * (lHeight - 1 - i) + j;						
			* (lpSrcUnChr) = (BYTE)(dTemp);// ����Դͼ��
		}
	}		
	delete F;// �ͷ��ڴ�	
	return TRUE;// ����
}

 /*************************************************************************
 * �������ƣ�InverseFilter (LPSTR lpSrcStartBits, long lWidth, long lHeight, long lLineBytes)
 * ��������:
 *   LPSTR lpSrcStartBits,ָ��DIB��ʼ���ص�ָ��
 *   long lWidth,DIB�Ŀ��
 *   long lHeight,DIB�ĸ߶�
 *	 long lLineBytes,DIB�����ֽ�����Ϊ4�ı���
 * ��������:BOOL
 * ��������: ������ͼ��������˲���ԭ
************************************************************************/
BOOL  InverseFilter (LPSTR lpSrcStartBits, long lWidth, long lHeight, long lLineBytes)
{	
    unsigned char*	lpSrcUnChr;	//ָ�����ص�ָ��			
	long i;//ѭ������
	long j;	
	double tempre, tempim, a, b, c, d;//��ʱ����	
	LONG	wid = 1;// ʵ�ʽ��и���Ҷ�任�Ŀ�Ⱥ͸߶�
	LONG	hei = 1;	
	int		widpor = 0;
	int		heiPor = 0;	
	while(wid * 2 <= lLineBytes)// ��֤��ɢ����Ҷ�任�Ŀ�Ⱥ͸߶�Ϊ2�������η�
	{
		wid = wid * 2;
		widpor++;
	}
	
	while(hei * 2 <= lHeight)
	{
		hei = hei * 2;
		heiPor++;
	}	
	CplexNum  *pTdSrc,*pTh;//�����洢Դͼ��ͱ任�˵�ʱ������	
	CplexNum  *pFdSrc,*pFh;//�����洢Դͼ��ͱ任�˵�Ƶ������		
	double MaxNum;//ͼ���һ������		
	if(wid != (int) lLineBytes)//�����˻�ͼ��ĳ��Ϳ����Ϊ2��������
	{
		return FALSE;
	}

	if(hei != (int) lHeight)
	{
		return FALSE;
	}	
	pTdSrc = new CplexNum [sizeof(CplexNum)*lHeight*lLineBytes];// Ϊʱ���Ƶ����������ռ�
	pTh   = new CplexNum [sizeof(CplexNum)*lHeight*lLineBytes];	
	pFdSrc = new CplexNum [sizeof(CplexNum)*lHeight*lLineBytes];
	pFh   = new CplexNum [sizeof(CplexNum)*lHeight*lLineBytes];
	
	for (j = 0; j < lHeight; j++)// ���˻�ͼ�����ݴ���ʱ������
	{
		for(i = 0; i < lLineBytes; i++)
		{						
			lpSrcUnChr= (unsigned char *)lpSrcStartBits + lLineBytes * j + i;// ָ���˻�ͼ������j�У���i�����ص�ָ��	
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
	Fourier(pTdSrc, lLineBytes, lHeight, pFdSrc);//���˻�ͼ�����FFT		
	Fourier(pTh, lLineBytes, lHeight, pFh);//�Ա任��ͼ�����FFT		
	for (i = 0;i <lHeight*lLineBytes;i++)//Ƶ�����
	{
		a = pFdSrc[i].re;
		b = pFdSrc[i].im;
		c = pFh[i].re;
		d = pFh[i].im;				
		if (c*c + d*d > 1e-3)//���Ƶ��ֵ̫С�����迼��
		{
			tempre = ( a*c + b*d ) / ( c*c + d*d );
			tempim = ( b*c - a*d ) / ( c*c + d*d );
		}
		pFdSrc[i].re=tempre;
		pFdSrc[i].im=tempim;

	}	
	InverseFourier(pFdSrc, pTdSrc, lLineBytes, lHeight);//�Ը�ԭͼ����з�FFT	
	MaxNum=300;//ȷ����һ������	
	for (j = 0;j < lHeight ;j++)//ת��Ϊ��ԭͼ��
	{
		for(i = 0;i < lLineBytes ;i++)
		{
						
 			lpSrcUnChr = (unsigned char *)lpSrcStartBits + lLineBytes * j + i;// ָ��ԭͼ������j�У���i�����ص�ָ��	
			*lpSrcUnChr= (unsigned char) (pTdSrc[(lLineBytes)*j + i].re*255.0/MaxNum);
		}
	}		
	delete pTdSrc;//�ͷŴ洢�ռ�
	delete pTh;
	delete pFdSrc;
	delete pFh;	
	return TRUE;// ����
}
/*************************************************************************
 * �������ƣ�WinnerFilter(LPSTR lpSrcStartBits, long lWidth, long lHeight, long lLineBytes)
 * ��������:
 *   LPSTR lpSrcStartBits,ָ��DIB��ʼ���ص�ָ��
 *   long lWidth,DIB�Ŀ��
 *   long lHeight,DIB�ĸ߶�
 *	 long lLineBytes,DIB�����ֽ�����Ϊ4�ı���
 * ��������:BOOL
 * ��������: ������ͼ�����ά���˲���ԭ
************************************************************************/
BOOL  WinnerFilter (LPSTR lpSrcStartBits, long lWidth, long lHeight, long lLineBytes)
{
	unsigned char*	lpSrcUnChr;	//ָ�����ص�ָ��	
	long i;//ѭ������
	long j;	
	double temp, tempre, tempim, //��ʱ����
			a, b, c, d, tempnorm;		
	LONG	wid = 1;// ʵ�ʽ��и���Ҷ�任�Ŀ�Ⱥ͸߶�
	LONG	hei = 1;
	
	int		widpor = 0;
	int		heiPor = 0;
	
	while(wid * 2 <= lLineBytes)// ��֤��ɢ����Ҷ�任�Ŀ�Ⱥ͸߶�Ϊ2�������η�
	{
		wid = wid * 2;
		widpor++;
	}	
	while(hei * 2 <= lHeight)
	{
		hei = hei * 2;
		heiPor++;
	}
	CplexNum *pTdSrc,*pTh;	//�����洢Դͼ��ͱ任�˵�ʱ������	
	CplexNum  *pFdSrc,*pFh;//�����洢Դͼ��ͱ任�˵�Ƶ������	
	
	if(wid != (int) lLineBytes)//�����˻�ͼ��ĳ��Ϳ����Ϊ2��������
	{
		return FALSE;
	}
	if(hei != (int) lHeight)
	{
		return FALSE;
	}	
	pTdSrc		= new CplexNum [sizeof(CplexNum)*lHeight*lLineBytes];// Ϊʱ���Ƶ����������ռ�
	pTh		= new CplexNum [sizeof(CplexNum)*lHeight*lLineBytes];
	
	pFdSrc		= new CplexNum [sizeof(CplexNum)*lHeight*lLineBytes];
	pFh		= new CplexNum [sizeof(CplexNum)*lHeight*lLineBytes];
	
	double *pCFFilter   = new double [lHeight*lLineBytes];// �˲�����Ȩϵ��

	for (j = 0;j < lHeight ;j++)
	{
		for(i = 0;i < lLineBytes ;i++)
		{
			lpSrcUnChr= (unsigned char *)lpSrcStartBits + lLineBytes * j + i;// ָ���˻�ͼ������j�У���i�����ص�ָ��
			pTdSrc[ lLineBytes*j + i ].re =(double)*lpSrcUnChr;// ������ֵ�洢��ʱ��������
			pTdSrc[ lLineBytes*j + i ].im=0.0;
			
			pFdSrc[ lLineBytes*j + i ].re=0.0;//// Ƶ����ֵ
			pFdSrc[ lLineBytes*j + i ].im=0.0;//				
			if(i < 5 && j <5)// �˻�ϵͳʱ��ά���˲���Ȩϵ����ֵ
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
			pFh[ lLineBytes*j + i ].re =0.0;// Ƶ����ֵ
			pFh[ lLineBytes*j + i ].im =0.0;
		}
	}		
	Fourier(pTdSrc, lLineBytes, lHeight, pFdSrc);//���˻�ͼ�����FFT		
	Fourier(pTh, lLineBytes, lHeight, pFh);//�Ա任��ͼ�����FFT		
	for (i = 0; i < lHeight * lLineBytes; i++)// ����M
	{			
			a = pFdSrc[i].re;// ��ֵ
			b = pFdSrc[i].im;
			c = pFh[i].re;
			d = pFh[i].im;			
			tempnorm = c * c + d * d;// ��ģ		
			temp  = (tempnorm ) / (tempnorm + pCFFilter[i]);// |H(u,v)|*|H(u,v)|/(|H(u,v)|*|H(u,v)|+a)
			{				
				tempre = ( a*c + b*d ) / ( c*c + d*d );
				tempim = ( b*c - a*d ) / ( c*c + d*d );				
				pFdSrc[i].re=temp*tempre;// ���f(u,v)
				pFdSrc[i].im=temp*tempim;
			}						
	}	
	InverseFourier(pFdSrc, pTdSrc, lLineBytes, lHeight);//�Ը�ԭͼ����з�FFT	
	for (j = 0;j < lHeight ;j++)//ת��Ϊ��ԭͼ��
	{
		for(i = 0;i < lLineBytes ;i++)
		{
						
 			lpSrcUnChr= (unsigned char *)lpSrcStartBits + lLineBytes * j + i;// ָ��ԭͼ������j�У���i�����ص�ָ��
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
	delete pTdSrc;//�ͷŴ洢�ռ�
	delete pTh;
	delete pFdSrc;
	delete pFh;
	delete pCFFilter;	
	return TRUE;// ����
}
// function.h: interface for the function class.
//
//////////////////////////////////////////////////////////////////////




/*************************************************************************
 * \�������ƣ�
 *   GrayLinTrans()
 * \�������:
 *	 LPSTR lpDIBBits		//ָ��Դͼ�������ָ��
 *	 LONG lmageWidth		//Դͼ��Ŀ��
 *	 LONG lmageHeight		// Դͼ��ĸ߶�
 *   int   oralow			// ԭʼͼ��ĻҶ�ֵ�������򣭵�ֵ
 *   int   orahig			// ԭʼͼ��ĻҶ�ֵ�������򣭸�ֵ
 *   int   newlow			// �任��ͼ��ҶȵĶ�̬��Χ����ֵ
 *   int   newhig			// �任��ͼ��ҶȵĶ�̬��Χ����ֵ
 * \����ֵ:
 *   BOOL               // �ɹ�����TRUE�����򷵻�FALSE��
 * \˵��:
 *   �ú���������ͼ��ָ���ĻҶȷֲ����лҶȱ任��Ҫ����ʵ�ֻҶȷֲ�����չ
*************************************************************************/
BOOL GrayLinTrans(LPSTR lpDIBBits, LONG lmageWidth, LONG lmageHeight,int oralow, int orahig, int newlow, int newhig)
{
	unsigned char*	lpSrc;								// ָ��Դͼ���ָ��
	int i;												// ѭ������
	int j;												// ѭ������
	BYTE	byMap[256];								// ����Ҷ�ӳ���
	for (i = 0; i <= oralow; i++)								//���Ҷȼ�С��Ҫ��ǿ�ĻҶȼ�ʱ
	{
		if (newlow > 0)									//�ж��»Ҷȼ��Ƿ����0
		{
			byMap[i] = newlow;							//������ֵ
		}
		else
		{
			byMap[i] = 0;								//ֱ�Ӹ�ֵΪ0
		}
	}
	for (; i <= orahig; i++)
	{
		if (orahig != oralow)								// �ж�orahig�Ƿ����oralow(��ֹ
											 //��ĸΪ0)
		{
			//���Ա任
			byMap[i] = newlow + (BYTE) ((newhig - newlow) * (i - oralow) / (orahig - oralow));
		}
		else
		{
			byMap[i] = newlow;							//ֱ�Ӹ�ֵΪnewlow
		}
	}
	for (; i < newhig; i++)
	{
		if (newhig <= 255)								//�ж�d�Ƿ����255
		{
			byMap[i] = newhig;							//ֱ�Ӹ�ֵΪnewhig
		}
		else
		{
			byMap[i] = 255;								//ֱ�Ӹ�ֵΪ255
		}
	}
	for(i = 0; i < lmageHeight; i++)							//��ͼ���ÿ������ֵ���б任
	{
		for(j = 0; j < lmageWidth; j++)						//ÿ��
		{
			// ָ��DIB��i�У���j�����ص�ָ��
			lpSrc = (unsigned char*)lpDIBBits + lmageWidth * (lmageHeight - 1 - i) + j;
			*lpSrc = byMap[*lpSrc];						//���µĻҶ����ԭ�еĻҶ�
		}
	}
	return TRUE;										//����
}



/*************************************************************************
* \�������ƣ�
 *   GrayHistEnhance()
* \�������:
 *	 LPSTR lpDIBBits		//ָ��Դͼ�������ָ��
 *	 LONG lmageWidth		//Դͼ��Ŀ��
 *	 LONG lmageHeight		//Դͼ��ĸ߶�
 * \����ֵ:
 *   BOOL		       	//�ɹ��򷵻�TRUE�����򷵻�FALSE
 * \˵��:
 *   �ú�����ָ����ͼ�����ֱ��ͼ���⻯����
*************************************************************************/
 BOOL GrayHistEnhance(LPSTR lpDIBBits, LONG lmageWidth, LONG lmageHeight)
 {
	unsigned char*	lpSrc;									//ָ��Դͼ���ָ��
	int	nTemp;											//��ʱ����
	int j;													//ѭ������
	int i;													//ѭ������
	BYTE	byMap[256];									//�ۻ�ֱ��ͼ�����Ҷ�ӳ���
	int	nCount[256];										//ֱ��ͼ
	for (i = 0; i < 256; i ++)									//���ü���Ϊ0
	{
		nCount[i] = 0;										//����
	}
	for(i = 0; i < lmageHeight; i++)								//ÿ��
	{
		for(j = 0; j < lmageWidth; j++)							//ÿ��
		{
			// ָ��DIB��i�У���j�����ص�ָ��
			lpSrc = (unsigned char*)lpDIBBits + lmageWidth * (lmageHeight - 1 - i) + j;
			nCount[*(lpSrc)]++;								//������1
		}
	}
	for (i = 0; i < 256; i++)										//�����ۻ�ֱ��ͼ
	{
		nTemp = 0;										//��ʼΪ0
		for (j = 0; j <= i ; j++)
		{
			nTemp += nCount[j];
		}
		byMap[i] = (BYTE) (nTemp * 255 / lmageHeight / lmageWidth); 	//�����Ӧ���»Ҷ�ֵ
//˵����* 255ʵ���Ͼ��ǽ��µĻҶ�ֵҲת��Ϊ0��255�ķ�Χ��
	}
	for(i = 0; i < lmageHeight; i++)
	{
		for(j = 0; j < lmageWidth; j++)							//ÿ��
		{
			//ָ��DIB��i�У���j�����ص�ָ��
			lpSrc = (unsigned char*)lpDIBBits + lmageWidth * (lmageHeight - 1 - i) + j;
			*lpSrc = byMap[*lpSrc];							//�����µĻҶ�ֵ
		}
	}
	return TRUE;											//����
 }	


 /*************************************************************************
 * \�������ƣ�
 *  Template()
 * \�������:
 *	 LPSTR lpDIBBits		- ָ��Դͼ�������ָ��
 *	 LONG lmageWidth		- Դͼ��Ŀ��
 *	 LONG lmageHeight		- Դͼ��ĸ߶�
 *   int nTempWidth		- ģ��Ŀ��
 *   int nTempHeight		- ģ��ĸ߶�
 *   int nTempCenX		- ģ�����ĵ�X���꣨�����ģ�壩
 *   int nTempCenY		- ģ�����ĵ�Y���꣨�����ģ�壩
 *   double* Tempdata		- ģ�������ָ��
 *   double* TempCoef		- ģ���ϵ��
 * \����ֵ:
 *   BOOL			- �ɹ��򷵻�TRUE�����򷵻�FALSE
 * \˵��:
 *   �ú�����ָ����ģ���lpDIBBitsָ���ͼ�����ģ�������ģ��Ķ����˿�ȣ��߶ȣ���������
*��ϵ����ģ������ݴ����Tempdata�С���ͼ�����ģ���������Ȼ�����lpDIBBitsָ��Ķ���
*�С���Ҫע����ǣ��ú���ֻ�ܴ���8λ��ͼ�󣬷���ָ������ݽ�����
 **************************************************************************/
BOOL  Template(LPSTR lpDIBBits, LONG lmageWidth, LONG lmageHeight,
					 int nTempWidth, int nTempHeight, 
					 int nTempCenX, int nTempCenY,
					 double* Tempdata, double TempCoef)
{
	LPBYTE			lpImage;								// ��ʱ���ͼ�����ݵ�ָ��
	int 		i;											// ѭ������
	int		j;											// ѭ������
	int 		k;											// ѭ������
	int 		l;											// ѭ������
	unsigned char*	lpSrc;									// ָ��Դͼ���ָ��
	unsigned char*	lpDst;									// ָ��Ҫ���������ָ��
	double	dbResult;										// ������
	lpImage = (LPBYTE) new  char[lmageWidth*lmageHeight];			// �����ڴ�
	if (lpImage == NULL)										// �ж��Ƿ��ڴ����ʧ��
	{
		return FALSE;										// �����ڴ�ʧ��
	}
	
	// ��ԭʼͼ������ݿ�������ʱ����ڴ���
	memcpy(lpImage, lpDIBBits, lmageWidth*lmageHeight);
	// ����ģ����㣬��(��ȥ��Ե����)
	for(i = nTempCenY ; i <lmageHeight - nTempHeight + nTempCenY + 1; i++)
	{
		// ��(��ȥ��Ե����)
		for(j = nTempCenX; j < lmageWidth - nTempWidth + nTempCenX + 1; j++)
		{
			// ָ����DIB��i�У���j�����ص�ָ��
			lpDst = (unsigned char*)lpImage + lmageWidth * (lmageHeight - 1 - i) + j;
			dbResult = 0;										// ��0
			for (k = 0; k < nTempHeight; k++)
			{
				for (l = 0; l < nTempWidth; l++)
				{
					// ָ��DIB��i - iFilterMY + k�У���j - iFilterMX + l�����ص�ָ��
					lpSrc = (unsigned char*)lpDIBBits + lmageWidth * (lmageHeight - 1 - i + nTempCenY - k) + j - nTempCenX + l;
					dbResult += (* lpSrc) * Tempdata[k * nTempWidth + l];	// ��������ֵ
				}
			}
			dbResult *= TempCoef;								// ����ϵ��
			dbResult = (double ) fabs(dbResult);						// ȡ����ֵ
			if(dbResult > 255)									// �ж��Ƿ񳬹�255
			{
				* lpDst = 255;									// ֱ�Ӹ�ֵΪ255
			}
			else
			{
				* lpDst = (unsigned char) (dbResult + 0.5);				// ��ֵ
			}
		}
	}
	memcpy(lpDIBBits, lpImage, lmageWidth*lmageHeight);				//���Ʊ任���ͼ��
	delete[] lpImage;												// �ͷ��ڴ�
	return TRUE;												// ����
}

/*************************************************************************
* �������ƣ�
 *   MedianValue()
* ����:
 *   unsigned char * FiltValue	- ָ��Ҫ��ȡ��ֵ������ָ��
 *   int   iFilterLen				- ���鳤��
* ����ֵ:
 *   unsigned char				- ����ָ���������ֵ��
* ˵��:
 *   �ú�����ð�ݷ���һά����������򣬲���������Ԫ�ص���ֵ��
************************************************************************/

unsigned char  MedianValue(unsigned char * FiltValue, int mFilterLen)
{
	int		i;										// ѭ������
	int		j;										// ѭ������
	unsigned char Temp;									// �м����
	// ��ð�ݷ��������������
	for (j = 0; j < mFilterLen - 1; j ++)
	{
		for (i = 0; i < mFilterLen - j - 1; i ++)
		{
			if (FiltValue[i] > FiltValue[i + 1])					// ǰ���ֵ���ں����
			{
				Temp = FiltValue[i];
				FiltValue[i] = FiltValue[i + 1];				// ���ߵ�ֵ����
				FiltValue[i + 1] = Temp;
			}
		}
	}
	if ((mFilterLen & 1) > 0)								// ������ֵ
	{
		//������������Ԫ�أ������м�һ��Ԫ��
		Temp = FiltValue[(mFilterLen + 1) / 2];
	}
	else
	{
		//������ż����Ԫ�أ������м�����Ԫ��ƽ��ֵ
		Temp = (FiltValue[mFilterLen / 2] + FiltValue[mFilterLen / 2 + 1]) / 2;
	}
	return Temp;										// ������ֵ
}




/*************************************************************************
* �������ƣ�
 *   MedianFilter()
* ����:
 *   LPSTR lpDIBBits			- ָ��ԴDIBͼ��ָ��
 *   LONG  lmageWidth		- Դͼ���ȣ���������
 *   LONG  lmageHeight		- Դͼ��߶ȣ���������
 *   int   mFilterH				- �˲����ĸ߶�
 *   int   mFilterW			- �˲����Ŀ��
 *   int   mFilterMX			- �˲���������Ԫ��X����
 *   int   mFilterMY			- �˲���������Ԫ��Y����
* ����ֵ:
 *   BOOL					- �ɹ�����TRUE�����򷵻�FALSE��
 * ˵��:
 *   �ú�����DIBͼ�������ֵ�˲���
************************************************************************/

BOOL  MedianFilter(LPSTR lpDIBBits, LONG lmageWidth, LONG lmageHeight, 
						 int mFilterH, int mFilterW, int mFilterMX, int mFilterMY)
{
	unsigned char*	lpSrc;								// ָ��Դͼ���ָ��
	unsigned char*	lpDst;								// ָ��Ҫ���������ָ��
	LPBYTE lpImage;									// ָ����ͼ���ָ��
	unsigned char* FiltValue;								// ָ���˲��������ָ��
	int			i;									// ѭ������
	int			j;									// ѭ������
	int			k;									// ѭ������
	int			l;									// ѭ������
	lpImage = (LPBYTE) new char[lmageWidth *lmageHeight];		// ��ʱ�����ڴ棬�Ա�����ͼ��
	if (lpImage == NULL)									// �ж��Ƿ��ڴ����ʧ��
	{
		return FALSE;									// �����ڴ�ʧ��
	}	
	memcpy(lpImage, lpDIBBits, lmageWidth *lmageHeight);		// ��ʼ��ͼ��Ϊԭʼͼ��
	FiltValue = new unsigned char[mFilterH *mFilterW];			// ��ʱ�����ڴ棬�Ա����˲�������
	if (FiltValue == NULL)								// �ж��Ƿ��ڴ����ʧ��
	{
		delete[]lpImage;									// �ͷ��ѷ����ڴ�
		return FALSE;									// �����ڴ�ʧ��
	}
	// ��ʼ��ֵ�˲�
	for(i = mFilterMY; i < lmageHeight - mFilterH + mFilterMY + 1; i++)
	{
		for(j = mFilterMX; j < lmageWidth - mFilterW + mFilterMX + 1; j++)
		{
			// ָ����DIB��i�У���j�����ص�ָ��
			lpDst = (unsigned char*)lpImage + lmageWidth * (lmageHeight - 1 - i) + j;
			for (k = 0; k < mFilterH; k++)					// ��ȡ�˲�������
			{
				for (l = 0; l < mFilterW; l++)
				{
					// ָ��DIB��i - iFilterMY + k�У���j - iFilterMX + l�����ص�ָ��
					lpSrc = (unsigned char*)lpDIBBits + lmageWidth  * (lmageHeight - 1 - i + mFilterMY 
						  - k) + j - mFilterMX + l;
					FiltValue[k * mFilterW + l] = *lpSrc;		// ��������ֵ
				}
			}
			*lpDst= MedianValue(FiltValue, (mFilterH * mFilterW)); // ��ȡ��ֵ
		}
	}
	memcpy(lpDIBBits, lpImage, lmageWidth*lmageHeight);			// ���Ʊ任���ͼ��
	delete[]lpImage;										// �ͷ��ڴ�
	delete[]FiltValue;
	return TRUE;										// ����
}



/*************************************************************************
 *
 * \�������ƣ�
 *   FFT_1D()
 *
 * \�������:
 *   complex<double> * pCTData	- ָ��ʱ�����ݵ�ָ�룬�������Ҫ�任������
 *   complex<double> * pCFData	- ָ��Ƶ�����ݵ�ָ�룬����ľ����任������
 *   nLevel						������Ҷ�任�����㷨�ļ�����2��������
 *
 * \����ֵ:
 *   ��
 *
 * \˵��:
 *   һά���ٸ���Ҷ�任��
 *
 *************************************************************************
 */
void FFT_1D(complex<double> * pCTData, complex<double> * pCFData, int nLevel)
{
		// ѭ�����Ʊ���
	int		i;
	int     j;
	int     k;

	// ����Ҷ�任����
	int	nCount =0 ;

	// ���㸵��Ҷ�任����
	nCount =(int)pow(2,nLevel) ;
	
	// ĳһ���ĳ���
	int		nBtFlyLen;
	nBtFlyLen = 0 ;
	
	// �任ϵ���ĽǶ� ��2 * PI * i / nCount
	double	dAngle;
	
	complex<double> *pCW ;
	
	// �����ڴ棬�洢����Ҷ�仯��Ҫ��ϵ����
	pCW  = new complex<double>[nCount / 2];

    // ���㸵��Ҷ�任��ϵ��
	for(i = 0; i < nCount / 2; i++)
	{
		dAngle = -2 * PI * i / nCount;
		pCW[i] = complex<double> ( cos(dAngle), sin(dAngle) );
	}

	// �任��Ҫ�Ĺ����ռ�
	complex<double> *pCWork1,*pCWork2; 
	
	// ���乤���ռ�
	pCWork1 = new complex<double>[nCount];

	pCWork2 = new complex<double>[nCount];

	
	// ��ʱ����
	complex<double> *pCTmp;
	
	// ��ʼ����д������
	memcpy(pCWork1, pCTData, sizeof(complex<double>) * nCount);

	// ��ʱ����
	int nInter; 
	nInter = 0;

	// �����㷨���п��ٸ���Ҷ�任
	for(k = 0; k < nLevel; k++)
	{
		for(j = 0; j < (int)pow(2,k); j++)
		{
			//���㳤��
			nBtFlyLen = (int)pow( 2,(nLevel-k) );
			
			//�������ţ���Ȩ����
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

		// ���� pCWork1��pCWork2������
		pCTmp   = pCWork1	;
		pCWork1 = pCWork2	;
		pCWork2 = pCTmp		;
	}
	
	// ��������
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
	
	// �ͷ��ڴ�ռ�
	delete pCW;
	delete pCWork1;
	delete pCWork2;
	pCW		=	NULL	;
	pCWork1 =	NULL	;
	pCWork2 =	NULL	;

}
/*************************************************************************
 *
 * \�������ƣ�
 *    IFFT_1D()
 *
 * \�������:
 *   complex<double> * pCTData	- ָ��ʱ�����ݵ�ָ�룬�������Ҫ���任������
 *   complex<double> * pCFData	- ָ��Ƶ�����ݵ�ָ�룬����ľ������任������
 *   nLevel						������Ҷ�任�����㷨�ļ�����2��������
 *
 * \����ֵ:
 *   ��
 *
 * \˵��:
 *   һά���ٸ���Ҷ���任��
 *
 ************************************************************************
 */
void IFFT_1D(complex<double> * pCFData, complex<double> * pCTData, int nLevel)
{
	
	// ѭ�����Ʊ���
	int		i;

	// ����Ҷ���任����
	int nCount;

	// ���㸵��Ҷ�任����
	nCount = (int)pow(2,nLevel) ;
	
	// �任��Ҫ�Ĺ����ռ�
	complex<double> *pCWork;	
	
	// ���乤���ռ�
	pCWork = new complex<double>[nCount];
	
	// ����Ҫ���任������д�빤���ռ�pCWork
	memcpy(pCWork, pCFData, sizeof(complex<double>) * nCount);
	
	// Ϊ�����ø���Ҷ���任,���԰Ѹ���ҶƵ�������ȡ����
	// Ȼ��ֱ���������任�����������Ǹ���Ҷ���任����Ĺ���
	for(i = 0; i < nCount; i++)
	{
		pCWork[i] = complex<double> (pCWork[i].real(), -pCWork[i].imag());
	}
	
	// ���ÿ��ٸ���Ҷ�任ʵ�ַ��任������洢��pCTData��
	FFT_1D(pCWork, pCTData, nLevel);
	
	// ��ʱ���Ĺ��������ս��
	// ���ݸ���Ҷ�任ԭ�����������ķ�����õĽ����ʵ�ʵ�ʱ������
	// ���һ��ϵ��nCount
	for(i = 0; i < nCount; i++)
	{
		pCTData[i] = 
			complex<double> (pCTData[i].real() / nCount, -pCTData[i].imag() / nCount);
	}
	
	// �ͷ��ڴ�
	delete pCWork;
	pCWork = NULL;
}

/*************************************************************************
 *
 * \�������ƣ�
 *   FFT_2D()
 *
 * \�������:
 *   complex<double> * pCTData	- ͼ������
 *   int    nWidth				- ���ݿ��
 *   int    nHeight				- ���ݸ߶�
 *   complex<double> * pCFData	- ����Ҷ�任��Ľ��
 *
 * \����ֵ:
 *   ��
 *
 * \˵��:
 *   ��ά����Ҷ�任��
 *
 ************************************************************************
 */
void FFT_2D(complex<double> * pCTData, int nWidth, int nHeight, complex<double> * pCFData)
{
	
	// ѭ�����Ʊ���
	int	x;
	int	y;
	
	// ��ʱ����
	double	dTmpOne;
	double  dTmpTwo;
	
	// ���и���Ҷ�任�Ŀ�Ⱥ͸߶ȣ���2���������ݣ�
	// ͼ��Ŀ�Ⱥ͸߶Ȳ�һ��Ϊ2����������
	int		nTransWidth;
	int 	nTransHeight;

	// ������и���Ҷ�任�Ŀ��	��2���������ݣ�
	dTmpOne = log(nWidth)/log(2);
	dTmpTwo = ceil(dTmpOne)		   ;
	dTmpTwo = pow(2,dTmpTwo)	   ;
	nTransWidth = (int) dTmpTwo	   ;
	
	// ������и���Ҷ�任�ĸ߶� ��2���������ݣ�
	dTmpOne = log(nHeight)/log(2);
	dTmpTwo = ceil(dTmpOne)		   ;
	dTmpTwo = pow(2,dTmpTwo)	   ;
	nTransHeight = (int) dTmpTwo	   ;	
	
	// x��y�����У������ϵĵ�������
	int		nXLev;
	int		nYLev;

	// ����x��y�����У������ϵĵ�������
	nXLev = (int) ( log(nTransWidth)/log(2) +  0.5 );
	nYLev = (int) ( log(nTransHeight)/log(2) + 0.5 );
	
	for(y = 0; y < nTransHeight; y++)
	{
		// x������п��ٸ���Ҷ�任
		FFT_1D(&pCTData[nTransWidth * y], &pCFData[nTransWidth * y], nXLev);
	}
	
	// pCFData��Ŀǰ�洢��pCTData�����б任�Ľ��
	// Ϊ��ֱ������FFT_1D����Ҫ��pCFData�Ķ�ά����ת�ã���һ������FFT_1D����
	// ����Ҷ�б任��ʵ�����൱�ڶ��н��и���Ҷ�任��
	for(y = 0; y < nTransHeight; y++)
	{
		for(x = 0; x < nTransWidth; x++)
		{
			pCTData[nTransHeight * x + y] = pCFData[nTransWidth * y + x];
		}
	}
	
	for(x = 0; x < nTransWidth; x++)
	{
		// ��x������п��ٸ���Ҷ�任��ʵ�����൱�ڶ�ԭ����ͼ�����ݽ����з����
		// ����Ҷ�任
		FFT_1D(&pCTData[x * nTransHeight], &pCFData[x * nTransHeight], nYLev);
	}

	// pCFData��Ŀǰ�洢��pCTData������ά����Ҷ�任�Ľ��������Ϊ�˷����з���
	// �ĸ���Ҷ�任�����������ת�ã����ڰѽ��ת�û���
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
 * \�������ƣ�
 *   IFFT_2D()
 *
 * \�������:
 *   complex<double> * pCFData	- Ƶ������
 *   complex<double> * pCTData	- ʱ������
 *   int    nWidth				- ͼ�����ݿ��
 *   int    nHeight				- ͼ�����ݸ߶�
 *
 * \����ֵ:
 *   ��
 *
 * \˵��:
 *   ��ά����Ҷ���任��
 *
 ************************************************************************
 */
void IFFT_2D(complex<double> * pCFData, complex<double> * pCTData, int nWidth, int nHeight)
{
	// ѭ�����Ʊ���
	int	x;
	int	y;
	
	// ��ʱ����
	double	dTmpOne;
	double  dTmpTwo;
	
	// ���и���Ҷ�任�Ŀ�Ⱥ͸߶ȣ���2���������ݣ�
	// ͼ��Ŀ�Ⱥ͸߶Ȳ�һ��Ϊ2����������
	int		nTransWidth;
	int 	nTransHeight;

	// ������и���Ҷ�任�Ŀ��	��2���������ݣ�
	dTmpOne = log(nWidth)/log(2);
	dTmpTwo = ceil(dTmpOne)		   ;
	dTmpTwo = pow(2,dTmpTwo)	   ;
	nTransWidth = (int) dTmpTwo	   ;
	
	// ������и���Ҷ�任�ĸ߶� ��2���������ݣ�
	dTmpOne = log(nHeight)/log(2);
	dTmpTwo = ceil(dTmpOne)		   ;
	dTmpTwo = pow(2,dTmpTwo)	   ;
	nTransHeight = (int) dTmpTwo	   ;
	
	// ���乤����Ҫ���ڴ�ռ�
	complex<double> *pCWork= new complex<double>[nTransWidth * nTransHeight];

	//��ʱ����
	complex<double> *pCTmp ;
	
	// Ϊ�����ø���Ҷ���任,���԰Ѹ���ҶƵ�������ȡ����
	// Ȼ��ֱ���������任�����������Ǹ���Ҷ���任����Ĺ���
	for(y = 0; y < nTransHeight; y++)
	{
		for(x = 0; x < nTransWidth; x++)
		{
			pCTmp = &pCFData[nTransWidth * y + x] ;
			pCWork[nTransWidth * y + x] = complex<double>( pCTmp->real() , -pCTmp->imag() );
		}
	}

	// ���ø���Ҷ���任
	FFT_2D(pCWork, nWidth, nHeight, pCTData) ;
	
	// ��ʱ���Ĺ��������ս��
	// ���ݸ���Ҷ�任ԭ�����������ķ�����õĽ����ʵ�ʵ�ʱ������
	// ���һ��ϵ��
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
* \�������ƣ�
 *   LowPassFilter()
* \�������:
 *   LPSTR lpDIBBits					- ָ����Ҫ�˲���ͼ������ָ��
 *   int nWidth						- ���ݿ��
 *   int nHeight						- ���ݸ߶�
 *   int nRadius1						- �����ͨ�˲��ĺ����˲��뾶
 *	 int nRadius2						- �����ͨ�˲��������˲��뾶
 * \����ֵ:
 *    BOOL								// �ɹ�����TRUE�����򷵻�FALSE��
 * \˵��:
 *  lpDIBBits ��ָ����Ҫ�˲���ͼ������ָ�롣
 *  ������ͨ�˲���������Ȼ�洢��lpDIBBits ���С�
**************************************************************************/
BOOL LowPassFilter(LPSTR lpDIBBits, LONG nWidth, LONG nHeight,int nRadius1,int nRadius2)
{ 
	unsigned char*	lpSrc;							// ָ��Դͼ���ָ��
	int y ;										// ѭ�����Ʊ���
	int x ;										// ѭ�����Ʊ���
	double dTmpOne ;								//�����ʱ����
	double dTmpTwo ;								//�����ʱ����
	int nTransWidth ;								// ����Ҷ�任�Ŀ�ȣ�2���������ݣ�
	int nTransHeight;								// ����Ҷ�任�ĸ߶ȣ�2���������ݣ�
	double unchValue;								// ����ͼ������ػҶȵ���ʱ����
	complex<double> * pCTData ;						// ָ��ʱ�����ݵ�ָ��
	complex<double> * pCFData ;						// ָ��Ƶ�����ݵ�ָ��
	// ������и���Ҷ�任�ĵ���������	��2���������ݣ�
	dTmpOne = log(nWidth)/log(2);
	dTmpTwo = ceil(dTmpOne)	;
	dTmpTwo = pow(2,dTmpTwo);
	nTransWidth = (int) dTmpTwo;	
	// ������и���Ҷ�任�ĵ��������� ��2���������ݣ�
	dTmpOne = log(nHeight)/log(2);
	dTmpTwo = ceil(dTmpOne)	;
	dTmpTwo = pow(2,dTmpTwo);
	nTransHeight = (int) dTmpTwo;
	double dReal;									// ����Ҷ�任��ʵ��
	double dImag;									// ����Ҷ�任���鲿
	// ��ͨ�˲��İ뾶���ܳ���Ƶ������뾶
	if(nRadius1>nTransWidth || nRadius2>nTransHeight)
	{
		return (false);								// ����FALSE
	}	
	pCTData=new complex<double>[nTransWidth * nTransHeight];	// �����ڴ�
	pCFData=new complex<double>[nTransWidth * nTransHeight];	// �����ڴ�
	// ͼ�����ݵĿ�͸߲�һ����2���������ݣ�����pCTData��һ����������Ҫ��0
	for(y=0; y<nTransHeight; y++)
	{
		for(x=0; x<nTransWidth; x++)
		{
			pCTData[y*nTransWidth + x]=complex<double>(0,0);		// ����
		}
	}
	//��ͼ�����ݴ���pCTData
	for(y=0; y<nHeight; y++)
	{
		for(x=0; x<nWidth; x++)
		{
			// ָ��DIB��y�У���x�����ص�ָ��
			lpSrc = (unsigned char*)lpDIBBits + nWidth * (nHeight - 1 - y) + x;
			unchValue = *lpSrc;
			pCTData[y*nTransWidth + x]=complex<double>(unchValue,0);
		}
	}
	FFT_2D(pCTData, nWidth, nHeight, pCFData) ;					// ����Ҷ���任
	for(x=0;x<nTransWidth;x++)								//��ʼʵʩ����ĵ�ͨ�˲�
	{
		for(y=nRadius2;y<nTransHeight-nRadius2;y++)
		{
			// ���������д���nRadius2�ĸ�Ƶ��������Ϊ0
			pCFData[x*nTransHeight + y]=complex<double>(0,0);
		}
	}
	for(x=nRadius1;x<nTransWidth-nRadius1;x++)
	{
		for(y=0;y<nTransHeight;y++)
		{
			// �Ѻ������д���nRadius1�ĸ�Ƶ��������Ϊ0
			pCFData[x*nTransHeight + y]=complex<double>(0,0);
		}
	}
	IFFT_2D(pCFData, pCTData,nHeight, nWidth); 				// ������ͨ�˲���ͼ����з��任
	for(y=0; y<nHeight; y++)								// ���任�����ݴ���lpDIBBits
	{
		for(x=0; x<nWidth; x++)
		{
			//��Ҫ�����źŵ����������Լ�ʵ�����õ�ͼ�������ǻҶ�ֵ����ԭʼ����
			dReal = pCTData[y*nTransWidth + x].real() ;			// ʵ��
			dImag = pCTData[y*nTransWidth + x].imag() ;		// �鲿
			unchValue =dReal;
			// ָ��DIB��y�У���x�����ص�ָ��
			lpSrc = (unsigned char*)lpDIBBits + nWidth * (nHeight - 1 - y) + x;
			*lpSrc =unchValue ;
		}
	}	
	delete pCTData;										// �ͷ��ڴ�
	delete pCFData;										// �ͷ��ڴ�
	pCTData = NULL;
	pCFData = NULL;	
	return (true);										//���ؽ��
}


/*************************************************************************
* \�������ƣ�
 *   ButterWorthLowPass()
* \�������:
 *	 LPSTR lpDIBBits					- ָ����Ҫ�˲���ͼ������ָ��
 *   int nWidth						- ���ݿ��
 *   int nHeight						- ���ݸ߶�
 *   int nRadius						- ButterWorth��ͨ�˲���"�빦��"��
* \����ֵ:
 *    BOOL								// �ɹ�����TRUE�����򷵻�FALSE��
* \˵��:
 *  pDIBBits ��ָ����Ҫ�˲���ͼ������ָ�롣
 *  ����ButterWorth��ͨ�˲���������Ȼ�洢��lpDIBBits ���С�
 **************************************************************************/
BOOL ButterWorthLowPass(LPSTR lpDIBBits, LONG nWidth, LONG nHeight, int nRadius)
{
	unsigned char*	lpSrc;							// ָ��Դͼ���ָ��
	int y ;										// ѭ�����Ʊ���
	int x ;										// ѭ�����Ʊ���
	double dTmpOne ;								//�����ʱ����
	double dTmpTwo ;								//�����ʱ����
	double H ;										// ButterWorth �˲�ϵ��
	int nTransWidth ;								// ����Ҷ�任�Ŀ�ȣ�2���������ݣ�
	int nTransHeight;								// ����Ҷ�任�ĸ߶ȣ�2���������ݣ�
	double dReal ;									// ����Ҷ�任��ʵ��
	double dImag;									// ����Ҷ�任���鲿
	double unchValue;								// ����ͼ������ػҶȵ���ʱ����
	complex<double> * pCTData ;						// ָ��ʱ�����ݵ�ָ��
	complex<double> * pCFData ;						// ָ��Ƶ�����ݵ�ָ��
	// ������и���Ҷ�任�ĵ���������	��2���������ݣ�
	dTmpOne = log(nWidth)/log(2);
	dTmpTwo = ceil(dTmpOne)	;
	dTmpTwo = pow(2,dTmpTwo);
	nTransWidth = (int) dTmpTwo;	
	// ������и���Ҷ�任�ĵ��������� ��2���������ݣ�
	dTmpOne = log(nHeight)/log(2);
	dTmpTwo = ceil(dTmpOne)	;
	dTmpTwo = pow(2,dTmpTwo);
	nTransHeight = (int) dTmpTwo;	
	pCTData=new complex<double>[nTransWidth * nTransHeight]; // �����ڴ�
	pCFData=new complex<double>[nTransWidth * nTransHeight]; // �����ڴ�
	// ͼ�����ݵĿ�͸߲�һ����2���������ݣ�����pCTData��һ����������Ҫ��0
	for(y=0; y<nTransHeight; y++)
	{
		for(x=0; x<nTransWidth; x++)
		{
			pCTData[y*nTransWidth + x]=complex<double>(0,0);	// ����
		}
	}
	for(y=0; y<nHeight; y++)							// ��ͼ�����ݴ���pCTData
	{
		for(x=0; x<nWidth; x++)
		{
			// ָ��DIB��y�У���x�����ص�ָ��
			lpSrc = (unsigned char*)lpDIBBits + nWidth * (nHeight - 1 - y) + x;
			unchValue = *lpSrc;
			pCTData[y*nTransWidth + x]=complex<double>(unchValue,0);
		}
	}	
	FFT_2D(pCTData, nWidth, nHeight, pCFData) ;			// ����Ҷ���任
	for(y=0; y<nTransHeight; y++)						// ��ʼʵʩButterWorth��ͨ�˲�
	{
		for(x=0; x<nTransWidth; x++)
		{
			H = (double)(y*y+x*x) ; 
			H = H / (nRadius * nRadius); 
			H = 1/(1+H)  ;							// ��Hֵ
			pCFData[y*nTransWidth + x]=complex<double>(pCFData[y*nTransWidth + x].real()*H, 
			pCFData[y*nTransWidth + x].imag()*H);
		}
	}
	// ����ButterWorth��ͨ�˲���ͼ����з��任
	IFFT_2D(pCFData, pCTData, nWidth, nHeight);
	for(y=0; y<nHeight; y++)							// ���任�����ݴ���lpDIBBits
	{
		for(x=0; x<nWidth; x++)
		{
			dReal = pCTData[y*nTransWidth + x].real() ;
			dImag = pCTData[y*nTransWidth + x].imag() ;
			unchValue = max(0,min(255,sqrt(dReal*dReal+dImag*dImag) ));
			// ָ��DIB��y�У���x�����ص�ָ��
			lpSrc = (unsigned char*)lpDIBBits + nWidth * (nHeight - 1 - y) + x;
			*lpSrc =unchValue ;
		}
	}
	delete pCTData;									// �ͷ��ڴ�
	delete pCFData;									// �ͷ��ڴ�
	pCTData = NULL;
	pCFData = NULL;
	return (true);									//���ؽ��	
}

/*************************************************************************
* \�������ƣ�
 *   HighPassFilter()
* \�������:
 *   LPSTR lpDIBBits					- ָ����Ҫ�˲���ͼ������ָ��
 *   int nWidth						- ���ݿ��
 *   int nHeight						- ���ݸ߶�
 *   int nRadius1						- �����ͨ�˲��ĺ����˲��뾶
 *	 int nRadius2						- �����ͨ�˲��������˲��뾶
 * \����ֵ:
 *    BOOL								// �ɹ�����TRUE�����򷵻�FALSE��
 * \˵��:
 *  lpDIBBits ��ָ����Ҫ�˲���ͼ������ָ�롣
 *  ������ͨ�˲���������Ȼ�洢��lpDIBBits ���С�
**************************************************************************/
BOOL HighPassFilter(LPSTR lpDIBBits, LONG nWidth, LONG nHeight,int nRadius1,int nRadius2)
{
	unsigned char*	lpSrc;							// ָ��Դͼ���ָ��
	int y ;										// ѭ�����Ʊ���
	int x ;										// ѭ�����Ʊ���
	double dTmpOne ;								//�����ʱ����
	double dTmpTwo ;								//�����ʱ����
	int nTransWidth ;								// ����Ҷ�任�Ŀ�ȣ�2���������ݣ�
	int nTransHeight;								// ����Ҷ�任�ĸ߶ȣ�2���������ݣ�
	double unchValue;								// ����ͼ������ػҶȵ���ʱ����
	complex<double> * pCTData ;						// ָ��ʱ�����ݵ�ָ��
	complex<double> * pCFData ;						// ָ��Ƶ�����ݵ�ָ��
	// ������и���Ҷ�任�ĵ���������	��2���������ݣ�
	dTmpOne = log(nWidth)/log(2);
	dTmpTwo = ceil(dTmpOne)	;
	dTmpTwo = pow(2,dTmpTwo);
	nTransWidth = (int) dTmpTwo;	
	// ������и���Ҷ�任�ĵ��������� ��2���������ݣ�
	dTmpOne = log(nHeight)/log(2);
	dTmpTwo = ceil(dTmpOne)	;
	dTmpTwo = pow(2,dTmpTwo);
	nTransHeight = (int) dTmpTwo;
	double dReal;									// ����Ҷ�任��ʵ��
	double dImag;									// ����Ҷ�任���鲿
	// �˲��İ뾶���ܳ���Ƶ������뾶
	if(nRadius1>nTransWidth-1 || nRadius2>nTransHeight-1)
	{
		return (false);								// ����false
	}
	pCTData=new complex<double>[nTransWidth * nTransHeight];	// �����ڴ�
	pCFData=new complex<double>[nTransWidth * nTransHeight];	// �����ڴ�
	// ͼ�����ݵĿ�͸߲�һ����2���������ݣ�����pCTData��һ����������Ҫ��0
	for(y=0; y<nTransHeight; y++)
	{
		for(x=0; x<nTransWidth; x++)
		{
			pCTData[y*nTransWidth + x]=complex<double>(0,0);	// ����
		}
	}
	for(y=0; y<nHeight; y++)								// ��ͼ�����ݴ���pCTData
	{
		for(x=0; x<nWidth; x++)
		{
			// ָ��DIB��y�У���x�����ص�ָ��
			lpSrc = (unsigned char*)lpDIBBits + nWidth * (nHeight - 1 - y) + x;
			unchValue = *lpSrc;
			pCTData[y*nTransWidth + x]=complex<double>(unchValue,0);
		}
	}	
	FFT_2D(pCTData, nWidth, nHeight, pCFData) ;				// ����Ҷ���任
	for(x=0;x<nTransWidth;x++)							// ��ʼʵʩ����ĸ�ͨ�˲�
	{
			for(y=0;y<nRadius2;y++)
			{
				//����������С��nRadius2�ĵ�Ƶ��������Ϊ0
				pCFData[x*nTransHeight + y]=complex<double>(0,0);
			}
			for(y=nTransHeight-1-nRadius2;y<nTransHeight;y++)
			{
				pCFData[x*nTransHeight + y]=complex<double>(0,0);
			}
	}
		for(x=0;x<nRadius1;x++)
		{
			//�Ѻ�������С��nRadius1�ĵ�Ƶ��������Ϊ0
			for(y=0;y<nTransHeight;y++)
				pCFData[x*nTransHeight + y]=complex<double>(0,0);
		}
		for(x=nTransWidth-nRadius1;x<nTransWidth;x++)
		{
			for(y=0;y<nTransHeight;y++)
				pCFData[x*nTransHeight + y]=complex<double>(0,0);
		} 
	IFFT_2D(pCFData, pCTData,nHeight, nWidth);			// ������ͨ�˲���ͼ����з��任
	for(y=0; y<nHeight; y++)							// ���任�����ݴ���lpDIBBits
	{
		for(x=0; x<nWidth; x++)
		{
			//��Ҫ�����źŵ����������Լ�ʵ�����õ�ͼ�������ǻҶ�ֵ����ԭʼ����
			dReal = pCTData[y*nTransWidth + x].real() ;
			dImag = pCTData[y*nTransWidth + x].imag() ;
			unchValue =dReal;
			// ָ��DIB��y�У���x�����ص�ָ��
			lpSrc = (unsigned char*)lpDIBBits + nWidth * (nHeight - 1 - y) + x;
			*lpSrc =unchValue ;
		}
	}
	delete pCTData;										// �ͷ��ڴ�
	delete pCFData;										// �ͷ��ڴ�
	pCTData = NULL;
	pCFData = NULL;	
	return (true);										// ���ؽ��
}

/*************************************************************************
 * \�������ƣ�
 *   ButterWorthHighPass()
 * \�������:
 *	 LPSTR lpDIBBits					- ָ����Ҫ�˲���ͼ������ָ��
 *   int nWidth							- ���ݿ��
 *   int nHeight						- ���ݸ߶�
 *   int nRadius            - ButterWorth��ͨ�˲���"�빦��"��
* \����ֵ:
 *    BOOL								// �ɹ�����TRUE�����򷵻�FALSE��
* \˵��:
 *  pDIBBits ��ָ����Ҫ�˲���ͼ������ָ�롣
 *  ����ButterWorth��ͨ�˲���������Ȼ�洢��lpDIBBits ���С�
 **************************************************************************/
BOOL ButterWorthHighPass(LPSTR lpDIBBits, LONG nWidth, LONG nHeight, int nRadius)
{
	unsigned char*	lpSrc;							// ָ��Դͼ���ָ��
	int y ;										// ѭ�����Ʊ���
	int x ;										// ѭ�����Ʊ���
	double dTmpOne ;								//�����ʱ����
	double dTmpTwo ;								//�����ʱ����
	double H ;										// ButterWorth �˲�ϵ��
	int nTransWidth ;								// ����Ҷ�任�Ŀ�ȣ�2���������ݣ�
	int nTransHeight;								// ����Ҷ�任�ĸ߶ȣ�2���������ݣ�
	double dReal ;									// ����Ҷ�任��ʵ��
	double dImag;									// ����Ҷ�任���鲿
	double unchValue;								// ����ͼ������ػҶȵ���ʱ����
	complex<double> * pCTData ;						// ָ��ʱ�����ݵ�ָ��
	complex<double> * pCFData ;						// ָ��Ƶ�����ݵ�ָ��
	// ������и���Ҷ�任�ĵ���������2���������ݣ�
	dTmpOne = log(nWidth)/log(2);
	dTmpTwo = ceil(dTmpOne);
	dTmpTwo = pow(2,dTmpTwo);
	nTransWidth = (int) dTmpTwo;	
	// ������и���Ҷ�任�ĵ��������� ��2���������ݣ�
	dTmpOne = log(nHeight)/log(2);
	dTmpTwo = ceil(dTmpOne)	;
	dTmpTwo = pow(2,dTmpTwo);
	nTransHeight = (int) dTmpTwo;	
	pCTData=new complex<double>[nTransWidth * nTransHeight];	// �����ڴ�
	pCFData=new complex<double>[nTransWidth * nTransHeight];	// �����ڴ�
	// ͼ�����ݵĿ�͸߲�һ����2���������ݣ�����pCTData��һ����������Ҫ��0
	for(y=0; y<nTransHeight; y++)
	{
		for(x=0; x<nTransWidth; x++)
		{
			pCTData[y*nTransWidth + x]=complex<double>(0,0);	// ����
		}
	}
	for(y=0; y<nHeight; y++)						// ��ͼ�����ݴ���pCTData
	{
		for(x=0; x<nWidth; x++)
		{
		// ָ��DIB��y�У���x�����ص�ָ��
			lpSrc = (unsigned char*)lpDIBBits + nWidth * (nHeight - 1 - y) + x;
			unchValue = *lpSrc;
			pCTData[y*nTransWidth + x]=complex<double>(unchValue,0);
		}
	}
	FFT_2D(pCTData, nWidth, nHeight, pCFData) ;		// ����Ҷ���任
	for(y=0; y<nTransHeight; y++)					// ���濪ʼʵʩButterWorth��ͨ�˲�
	{
		for(x=0; x<nTransWidth; x++)
		{
			H = (double)(y*y+x*x) ; 
			H = (nRadius * nRadius) / H ; 
			H = 1/(1+H);						// ��Hֵ
			pCFData[y*nTransWidth + x]=complex<double>(H*(pCFData[y*nTransWidth + x].real()),
					 H*(pCFData[y*nTransWidth + x].imag())  );
		}
	}
	// ����ButterWorth��ͨ�˲���ͼ����з��任
	IFFT_2D(pCFData, pCTData, nWidth, nHeight);
	for(y=0; y<nHeight; y++)						// ���任�����ݴ���lpDIBBits
	{
		for(x=0; x<nWidth; x++)
		{
			dReal = pCTData[y*nTransWidth + x].real() ;
			dImag = pCTData[y*nTransWidth + x].imag() ;
			unchValue = max(0,min(255,sqrt(dReal*dReal+dImag*dImag)+100 ));
			// ָ��DIB��y�У���x�����ص�ָ��
			lpSrc = (unsigned char*)lpDIBBits + nWidth * (nHeight - 1 - y) + x;
			*lpSrc =unchValue ;
		}
	}	
	delete pCTData;									// �ͷ��ڴ�
	delete pCFData;									// �ͷ��ڴ�
	pCTData = NULL;
	pCFData = NULL;
	return (true);									// ���ؽ��
}


/*************************************************************************
 *
 * �������ƣ�
 *   Erosion()
 *
 * ����:
 *   LPSTR lpDIBBits    - ָ��ԴDIBͼ��ָ��
 *   LONG  lmageWidth   - Դͼ���ȣ���������������4�ı�����
 *   LONG  lmageHeight  - Դͼ��߶ȣ���������
 *   int   type			- ��ʴ��ʽ��0��ʾˮƽ����1��ʾ��ֱ����
 *	 int   num			- �ṹԪ�صĸ�����ˮƽ����ʹ�ֱ���򣩡�
 *
 * ����ֵ:
 *   BOOL               - ��ʴ�ɹ�����TRUE�����򷵻�FALSE��
 *
 * ˵��:
 * �ú������ڶ�ͼ����и�ʴ���㡣�ṹԪ��Ϊˮƽ�����ֱ���򣬸������û�ѡ��
 * Ϊ3��5��7���ṹԭ��λ�������ġ�
 * Ҫ��Ŀ��ͼ��Ϊֻ��0��255�����Ҷ�ֵ�ĻҶ�ͼ����������㣬��ǿ��ת����
 ************************************************************************/

BOOL  Erosion(LPSTR lpDIBBits, LONG lmageWidth, LONG lmageHeight, int type , int num)
{
	// ָ��Դͼ���ָ��
	unsigned char*	lpSrc;	
	// ָ��Ҫ���������ָ��
	unsigned char*	lpDst;
	// ָ����ͼ���ָ��
	LPBYTE lpImage;
	// ѭ������
	int			i;
	int			j;
	int			k;		
	// ��ʱ�����ڴ棬�Ա�����ͼ��
	lpImage = (LPBYTE) new char[lmageWidth*lmageHeight];	
	// �ж��Ƿ��ڴ����ʧ��
	if (lpImage == NULL)
	{
		// �����ڴ�ʧ��
		return FALSE;
	}
	//����ֵ
	unsigned char pixeltemp;
	lpDst = (unsigned char *)lpImage;
	memset(lpDst, (BYTE)255, lmageWidth * lmageHeight);

	//���ͼ���Ƕ�ֵͼ��ת��Ϊ��ֵͼ��
	for(j = 0; j <lmageHeight; j++)
	{
		for(i = 0;i <lmageWidth; i++)
		{

			// ָ��Դͼ������j�У���i�����ص�ָ��			
			lpSrc = (unsigned char *)lpDIBBits + lmageWidth * j + i;

			//ȡ�õ�ǰָ�봦������ֵ��ע��Ҫת��Ϊunsigned char��
			pixeltemp = (unsigned char)*lpSrc;

			//Ŀ��ͼ���лҶ�ֵ����120������Ϊ255����������Ϊ0
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
		//ʹ��ˮƽ����ĽṹԪ�ؽ��и�ʴ
		for(j = 0; j <lmageHeight; j++)
		{
			for(i = (num-1)/2;i <lmageWidth-(num-1)/2; i++)
			{
				//����ʹ��1��num�ĽṹԪ�أ�Ϊ��ֹԽ�磬���Բ���������ߺ����ұߵ�(num-1)/2������

				// ָ��Դͼ������j�У���i�����ص�ָ��			
				lpSrc = (unsigned char *)lpDIBBits + lmageWidth * j + i;

				// ָ��Ŀ��ͼ������j�У���i�����ص�ָ��			
				lpDst = (unsigned char *)lpImage + lmageWidth * j + i;

				//ȡ�õ�ǰָ�봦������ֵ��ע��Ҫת��Ϊunsigned char��
				pixeltemp = (unsigned char)*lpSrc;
				
				//Ŀ��ͼ���еĵ�ǰ���ȸ��ɺ�ɫ
				*lpDst = (unsigned char)0;

				//���Դͼ���е�ǰ���������������(num-1)/2���㲻�Ǻ�ɫ��
				//��Ŀ��ͼ���еĵ�ǰ�㸳�ɰ�ɫ
				for (k = 0;k < num;k++ )
				{
					//��ȡ���ػҶ�ֵ
					pixeltemp = *(lpSrc+k-(num-1)/2);
					//����һ���׵�
					if (pixeltemp == 255 )
					{
						//�õ�����Ϊ�׵�
						*lpDst = (unsigned char)255;
						break;
					}
				}
				
			}
		}

	}
	else if(type == 1)
	{
		//ʹ�ô�ֱ����ĽṹԪ�ؽ��и�ʴ
		for(j = (num-1)/2; j <lmageHeight-(num-1)/2; j++)
		{
			for(i = 0;i <lmageWidth; i++)
			{
				//����ʹ��1��num�ĽṹԪ�أ�Ϊ��ֹԽ�磬���Բ��������ϱߺ����±ߵ�(num-1)/2������

				// ָ��Դͼ������j�У���i�����ص�ָ��			
				lpSrc = (unsigned char *)lpDIBBits + lmageWidth * j + i;

				// ָ��Ŀ��ͼ������j�У���i�����ص�ָ��			
				lpDst = (unsigned char *)lpImage + lmageWidth * j + i;

				//ȡ�õ�ǰָ�봦������ֵ��ע��Ҫת��Ϊunsigned char��
				pixeltemp = (unsigned char)*lpSrc;

				//Ŀ��ͼ���еĵ�ǰ���ȸ��ɺ�ɫ
				*lpDst = (unsigned char)0;

				//���Դͼ���е�ǰ���������������(num-1)/2���㲻�Ǻ�ɫ����
				//��Ŀ��ͼ���еĵ�ǰ�㸳�ɰ�ɫ
				for (k = 0;k < num;k++ )
				{	
					//��ȡ���ػҶ�ֵ
					pixeltemp = *(lpSrc+(k-(num-1)/2)*lmageWidth);
					//����һ���׵�
					if (pixeltemp == 255 )
					{
						//�õ�����Ϊ�׵�
						*lpDst = (unsigned char)255;
						break;
					}
				}
				
			}
		}

	}
	// ���Ƹ�ʴ���ͼ��
	memcpy(lpDIBBits, lpImage, lmageWidth * lmageHeight);

	// �ͷ��ڴ�
	delete[] lpImage;

	// ����
	return TRUE;
}



/*************************************************************************
 *
 * �������ƣ�
 *   Dilation()
 *
 * ����:
 *   LPSTR lpDIBBits    - ָ��ԴDIBͼ��ָ��
 *   LONG  lmageWidth   - Դͼ���ȣ���������������4�ı�����
 *   LONG  lmageHeight  - Դͼ��߶ȣ���������
 *   int   type			- ���ͷ�ʽ��0��ʾˮƽ����1��ʾ��ֱ����
 *	 int   num			- �ṹԪ�صĸ�����ˮƽ����ʹ�ֱ���򣩡�
 *
 * ����ֵ:
 *   BOOL               - ���ͳɹ�����TRUE�����򷵻�FALSE��
 *
 * ˵��:
 * �ú������ڶ�ͼ������������㡣�ṹԪ��Ϊˮƽ�����ֱ���򣬸������û�ѡ��
 * Ϊ3��5��7���ṹԭ��λ�������ġ�
 * Ҫ��Ŀ��ͼ��Ϊֻ��0��255�����Ҷ�ֵ�ĻҶ�ͼ����������㣬��ǿ��ת����
 ************************************************************************/

BOOL  Dilation(LPSTR lpDIBBits, LONG lmageWidth, LONG lmageHeight, int type , int num)
{
	// ָ��Դͼ���ָ��
	unsigned char*	lpSrc;	
	// ָ��Ҫ���������ָ��
	unsigned char*	lpDst;
	// ָ����ͼ���ָ��
	LPBYTE lpImage;
	// ѭ������
	int			i;
	int			j;
	int			k;		
	// ��ʱ�����ڴ棬�Ա�����ͼ��
	lpImage = (LPBYTE) new char[lmageWidth*lmageHeight];	
	// �ж��Ƿ��ڴ����ʧ��
	if (lpImage == NULL)
	{
		// �����ڴ�ʧ��
		return FALSE;
	}
	//����ֵ
	unsigned char pixeltemp;
	lpDst = (unsigned char *)lpImage;
	memset(lpDst, (BYTE)255, lmageWidth * lmageHeight);

	//���ͼ���Ƕ�ֵͼ��ת��Ϊ��ֵͼ��
	for(j = 0; j <lmageHeight; j++)
	{
		for(i = 0;i <lmageWidth; i++)
		{

			// ָ��Դͼ������j�У���i�����ص�ָ��			
			lpSrc = (unsigned char *)lpDIBBits + lmageWidth * j + i;

			//ȡ�õ�ǰָ�봦������ֵ��ע��Ҫת��Ϊunsigned char��
			pixeltemp = (unsigned char)*lpSrc;

			//Ŀ��ͼ���лҶ�ֵ����120������Ϊ255����������Ϊ0
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
		//ʹ��ˮƽ����ĽṹԪ�ؽ�������
		for(j = 0; j <lmageHeight; j++)
		{
			for(i = (num-1)/2;i <lmageWidth-(num-1)/2; i++)
			{
				//����ʹ��1��num�ĽṹԪ�أ�Ϊ��ֹԽ�磬���Բ���������ߺ����ұߵ�(num-1)/2������

				// ָ��Դͼ������j�У���i�����ص�ָ��			
				lpSrc = (unsigned char *)lpDIBBits + lmageWidth * j + i;

				// ָ��Ŀ��ͼ������j�У���i�����ص�ָ��			
				lpDst = (unsigned char *)lpImage + lmageWidth * j + i;

				//ȡ�õ�ǰָ�봦������ֵ��ע��Ҫת��Ϊunsigned char��
				pixeltemp = (unsigned char)*lpSrc;
				
				//Ŀ��ͼ���еĵ�ǰ���ȸ��ɰ�ɫ
				*lpDst = (unsigned char)255;

				//���Դͼ���е�ǰ������������Ҹ�(num-1)/2ֻҪ�и����Ǻ�ɫ��
				//��Ŀ��ͼ���еĵ�ǰ�㸳�ɺ�ɫ
				for (k = 0;k < num;k++ )
				{
					//��ȡ���ػҶ�ֵ
					pixeltemp = *(lpSrc+k-(num-1)/2);
					//����һ���ڵ�
					if (pixeltemp == 0 )
					{
						//�õ�����Ϊ�ڵ�
						*lpDst = (unsigned char)0;
						break;
					}
				}
				
			}
		}

	}
	else if(type == 1)
	{
		//ʹ�ô�ֱ����ĽṹԪ�ؽ�������
		for(j = (num-1)/2; j <lmageHeight-(num-1)/2; j++)
		{
			for(i = 0;i <lmageWidth; i++)
			{
				//����ʹ��1��num�ĽṹԪ�أ�Ϊ��ֹԽ�磬���Բ��������ϱߺ����±ߵ�(num-1)/2������

				// ָ��Դͼ������j�У���i�����ص�ָ��			
				lpSrc = (unsigned char *)lpDIBBits + lmageWidth * j + i;

				// ָ��Ŀ��ͼ������j�У���i�����ص�ָ��			
				lpDst = (unsigned char *)lpImage + lmageWidth * j + i;

				//ȡ�õ�ǰָ�봦������ֵ��ע��Ҫת��Ϊunsigned char��
				pixeltemp = (unsigned char)*lpSrc;

				//Ŀ��ͼ���еĵ�ǰ���ȸ��ɰ�ɫ
				*lpDst = (unsigned char)255;

				//���Դͼ���е�ǰ������������¸�(num-1)/2ֻҪ�и����Ǻ�ɫ��
				//��Ŀ��ͼ���еĵ�ǰ�㸳�ɰ�ɫ
				for (k = 0;k < num;k++ )
				{	
					//��ȡ���ػҶ�ֵ
					pixeltemp = *(lpSrc+(k-(num-1)/2)*lmageWidth);
					//����һ���׵�
					if (pixeltemp == 0 )
					{
						//�õ�����Ϊ�׵�
						*lpDst = (unsigned char)0;
						break;
					}
				}
				
			}
		}

	}
	// �������ͺ��ͼ��
	memcpy(lpDIBBits, lpImage, lmageWidth * lmageHeight);

	// �ͷ��ڴ�
	delete[] lpImage;

	// ����
	return TRUE;
}



/*************************************************************************
 *
 * �������ƣ�
 *   Thining()
 *
 * ����:
 *   LPSTR lpDIBBits    - ָ��ԴDIBͼ��ָ��
 *   LONG  lmageWidth   - Դͼ���ȣ���������������4�ı�����
 *   LONG  lmageHeight  - Դͼ��߶ȣ���������
 *
 * ����ֵ:
 *   BOOL               - ���ͳɹ�����TRUE�����򷵻�FALSE��
 *
 * ˵��:
 * ����8����ϸ���ķ������ֱ����ˮƽ����ʹ�ֱ�����ϸ��
 ************************************************************************/

BOOL Thining(LPSTR lpDIBBits, LONG lmageWidth, LONG lmageHeight)
{
	//���������������
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

	// ָ��Դͼ���ָ��
	unsigned char*	lpSrc;	
	// ָ��Ҫ���������ָ��
	unsigned char*	lpDst;
	// ָ����ͼ���ָ��
	LPBYTE lpImage;
	// ѭ������
	int			i;
	int			j;
    int         num;

	//��ʱ����
	int        nw,n,ne,w,e,sw,s,se;
	// ��ʱ�����ڴ棬�Ա�����ͼ��
	lpImage = (LPBYTE) new char[lmageWidth*lmageHeight];	
	// �ж��Ƿ��ڴ����ʧ��
	if (lpImage == NULL)
	{
		// �����ڴ�ʧ��
		return FALSE;
	}
	//����ֵ
	unsigned char pixeltemp;
	lpDst = (unsigned char *)lpImage;
	//��Ŀ��ͼ��ֵ��ȫ�ף�
	//memset(lpDst, (BYTE)255, lmageWidth * lmageHeight);

	//���ͼ���Ƕ�ֵͼ��ת��Ϊ��ֵͼ��
	for(j = 0; j <lmageHeight; j++)
	{
		for(i = 0;i <lmageWidth; i++)
		{

			// ָ��Դͼ������j�У���i�����ص�ָ��			
			lpSrc = (unsigned char *)lpDIBBits + lmageWidth * j + i;

			//ȡ�õ�ǰָ�봦������ֵ��ע��Ҫת��Ϊunsigned char��
			pixeltemp = (unsigned char)*lpSrc;

			//Ŀ��ͼ���лҶ�ֵ����120������Ϊ255����������Ϊ0
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

		// ��ʼ��ͼ��Ϊԭʼͼ��
	memcpy(lpImage, lpDIBBits, lmageWidth*lmageHeight);	

	//�Ƚ���ˮƽ�����ϸ��
	for(j = 1; j <lmageHeight-1; j++)
	{
		for(i = 1;i <lmageWidth-1; i++)
		{
			//Ϊ��ֹԽ�磬��ȣ��߶��������Ҹ�����һ��

			// ָ��Դͼ������j�У���i�����ص�ָ��			
			lpSrc = (unsigned char *)lpDIBBits + lmageWidth * j + i;

			// ָ��Ŀ��ͼ������j�У���i�����ص�ָ��			
			lpDst = (unsigned char *)lpImage + lmageWidth * j + i;
			//�Ǻڵ��������	
			if(*(lpSrc)==0)
			{
				w=(unsigned char)*(lpSrc-1);  //���ڵ�
                e=(unsigned char)*(lpSrc+1);  //���ڵ�
				//������������ھ���������һ���ǰ׵�Ŵ���
				if( (w==255)|| (e==255))
				{
					nw=(unsigned char)*(lpSrc+lmageWidth-1); //�����ڵ�
                    n=(unsigned char)*(lpSrc+lmageWidth); //���ڵ�
                    ne=(unsigned char)*(lpSrc+lmageWidth+1); //�����ڵ�
                    sw=(unsigned char)*(lpSrc-lmageWidth-1); //�����ڵ�
                    s=(unsigned char)*(lpSrc-lmageWidth); //���ڵ�
                    se=(unsigned char)*(lpSrc-lmageWidth+1); //�����ڵ�
					//��������
                    num=nw/255+n/255*2+ne/255*4+w/255*8+e/255*16+sw/255*32+s/255*64+se/255*128;
					if(erasetable[num]==1)
					{ //���������ɾ��
					//��ԭͼ�������н��úڵ�ɾ��
					 *(lpSrc)=(unsigned char)255; 					 
					//���ͼ�иúڵ�Ҳɾ��
                    *(lpDst)=(unsigned char)255; 
					}					 
				}
			}		
		}
	}
	//�ٽ��д�ֱ�����ϸ��
	
	for(i = 1;i <lmageWidth-1; i++)
	{
		for(j = 1; j <lmageHeight-1; j++)
		{
			// ָ��Դͼ������j�У���i�����ص�ָ��			
			lpSrc = (unsigned char *)lpDIBBits + lmageWidth * j + i;
			// ָ��Ŀ��ͼ������j�У���i�����ص�ָ��			
			lpDst = (unsigned char *)lpImage + lmageWidth * j + i;
			//�Ǻڵ��������	
			if(*(lpSrc)==0)
			{
				n=(unsigned char)*(lpSrc+lmageWidth);
                s=(unsigned char)*(lpSrc-lmageWidth);
				//������������ھ���������һ���ǰ׵�Ŵ���
                if( (n==255)|| (s==255))
				{
					 nw=(unsigned char)*(lpSrc+lmageWidth-1);
                     ne=(unsigned char)*(lpSrc+lmageWidth+1);
                     w=(unsigned char)*(lpSrc-1);
                     e=(unsigned char)*(lpSrc+1);
                     sw=(unsigned char)*(lpSrc-lmageWidth-1);
                     se=(unsigned char)*(lpSrc-lmageWidth+1);
                      //��������
					num=nw/255+n/255*2+ne/255*4+w/255*8+e/255*16+sw/255*32+s/255*64+se/255*128;

                     if(erasetable[num]==1)
					 { 
						 //���������ɾ��
						 //��ԭͼ�������н��úڵ�ɾ��
						*(lpSrc)=(unsigned char)255; 					 
						//���ͼ�иúڵ�Ҳɾ��
						*(lpDst)=(unsigned char)255; 
					 }
				}
			}
		}
	}
	// ����ϸ�����ͼ��
	memcpy(lpDIBBits, lpImage, lmageWidth * lmageHeight);
	// �ͷ��ڴ�
	delete[] lpImage;
	// ����
	return TRUE;
}


/*************************************************************************
 * �������ƣ�
 *   EdgeDetection()
 * ����:
 *   LPSTR lpDIBBits    - ָ��ԴDIBͼ��ָ��
 *   LONG  lWidth       - Դͼ���ȣ���������������4�ı�����
 *   LONG  lHeight      - Դͼ��߶ȣ���������
 *	 int mode			- ��������
 * ����ֵ:
 *   BOOL               - ��Ե���ɹ�����TRUE�����򷵻�FALSE��
 *
 * ˵��:
 * �ú�����Sobel��Isotropic Sobel��LOG��Ե������Ӷ�ͼ����б�Ե������㡣
 * Ҫ��Ŀ��ͼ��Ϊ�Ҷ�ͼ��
 ************************************************************************/

BOOL EdgeDetection(LPSTR lpDIBBits, LONG lmageWidth, LONG lmageHeight,int mode)
{

	int nTempWidth;		//ģ��Ŀ��
    int nTempHeight;	 // ģ��ĸ߶�
    int nTempCenX;		//ģ�����ĵ�X���꣨�����ģ�壩
    int nTempCenY;		//ģ�����ĵ�Y���꣨�����ģ�壩
    double* Tempdata;	//ģ�������ָ��	
	double TempCoef;	//ģ��ϵ��
	//ѭ������
	int i;
	int j;
	if(mode==0)		//Sobel����
	{
		// ָ�򻺴�ͼ���ָ��
		 unsigned char*	lpDst1;	
		 unsigned char*	lpDst2;
		// ָ�����ͼ���ָ��
		LPBYTE lpImage1;
		LPBYTE lpImage2;	
	
		// ��ʱ�����ڴ棬�Ա�����ͼ��
		lpImage1 = (LPBYTE) new  char[lmageWidth*lmageHeight];
		lpImage2 = (LPBYTE) new  char[lmageWidth*lmageHeight];
		// �ж��Ƿ��ڴ����ʧ��
		if (lpImage1 == NULL)
		{
			// �����ڴ�ʧ��
			return FALSE;
		}	
			// �ж��Ƿ��ڴ����ʧ��
		if (lpImage2 == NULL)
		{
			// �����ڴ�ʧ��
			return FALSE;
		}
		// ��ʼ��ͼ��Ϊԭʼͼ��
		memcpy(lpImage1, lpDIBBits, lmageWidth*lmageHeight);
		memcpy(lpImage2, lpDIBBits, lmageWidth*lmageHeight);
		lpDst1 = (unsigned char*)lpImage1;
		lpDst2 = (unsigned char*)lpImage2;
		//Sobel����ˮƽ���ģ�����
		nTempWidth=3;
		nTempHeight=3;
		nTempCenX=1;
		nTempCenY=1;
		TempCoef=1;
		Tempdata=new double[9];//Sobel����ģ��Ϊ3X3
		//ˮƽ��ģ�����
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
		//��ֱ����ģ�����
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
		//����������ͼ������ֵ
		for(j = 0; j <lmageHeight; j++)
		{
			for(i = 0;i <lmageWidth; i++)
			{

				// ָ�򻺴�ͼ��1������j�У���i�����ص�ָ��			
				lpDst1 = (unsigned char*)lpImage1 + lmageWidth * j + i;

				// ָ�򻺴�ͼ��2������j�У���i�����ص�ָ��			
				lpDst2 = (unsigned char*)lpImage2 + lmageWidth * j + i;
			
				if(*lpDst2 > *lpDst1)
				{
					*lpDst1 = *lpDst2;
				}
		
			}
		}
		//���ƾ���ģ��������ͼ��Դͼ��
		memcpy(lpDIBBits, lpImage1,lmageWidth*lmageHeight);
		return TRUE;
	}
	if(mode==1)		//Isotropic Sobel����
	{

		// ָ�򻺴�ͼ���ָ��
		 unsigned char*	lpDst1;	
		 unsigned char*	lpDst2;
		// ָ�����ͼ���ָ��
		LPBYTE lpImage1;
		LPBYTE lpImage2;	
	
		// ��ʱ�����ڴ棬�Ա�����ͼ��
		lpImage1 = (LPBYTE) new  char[lmageWidth*lmageHeight];
		lpImage2 = (LPBYTE) new  char[lmageWidth*lmageHeight];
		// �ж��Ƿ��ڴ����ʧ��
		if (lpImage1 == NULL)
		{
			// �����ڴ�ʧ��
			return FALSE;
		}	
			// �ж��Ƿ��ڴ����ʧ��
		if (lpImage2 == NULL)
		{
			// �����ڴ�ʧ��
			return FALSE;
		}
		// ��ʼ��ͼ��Ϊԭʼͼ��
		memcpy(lpImage1, lpDIBBits, lmageWidth*lmageHeight);
		memcpy(lpImage2, lpDIBBits, lmageWidth*lmageHeight);
		lpDst1 = (unsigned char*)lpImage1;
		lpDst2 = (unsigned char*)lpImage2;
		//Sobel����ˮƽ���ģ�����
		nTempWidth=3;
		nTempHeight=3;
		nTempCenX=1;
		nTempCenY=1;
		TempCoef=1;
		Tempdata=new double[9];//Sobel����ģ��Ϊ3X3
		//ˮƽ��ģ�����
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
		//��ֱ����ģ�����
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
		//����������ͼ������ֵ
		for(j = 0; j <lmageHeight; j++)
		{
			for(i = 0;i <lmageWidth; i++)
			{

				// ָ�򻺴�ͼ��1������j�У���i�����ص�ָ��			
				lpDst1 = (unsigned char*)lpImage1 + lmageWidth * j + i;

				// ָ�򻺴�ͼ��2������j�У���i�����ص�ָ��			
				lpDst2 = (unsigned char*)lpImage2 + lmageWidth * j + i;
			
				if(*lpDst2 > *lpDst1)
				{
					*lpDst1 = *lpDst2;
				}
		
			}
		}
		//���ƾ���ģ��������ͼ��Դͼ��
		memcpy(lpDIBBits, lpImage1,lmageWidth*lmageHeight);
		return TRUE;
	}

	if(mode==2)		//LOG����
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
 * �������ƣ�
 *   HoughTrans()
 * ����:
 *   LPSTR lpDIBBits       - ָ��ԴDIBͼ��ָ��
 *   LONG  lmageWidth       - Դͼ���ȣ���������������4�ı�����
 *   LONG  lmageHeight      - Դͼ��߶ȣ���������
 * ����ֵ:
 *   BOOL               - ����ɹ�����TRUE�����򷵻�FALSE��
 * ˵��:
 * �ú������ڶԼ��ͼ���е��������ֱ�ߡ�
 * Ҫ��Ŀ��ͼ��Ϊֻ��0��255�����Ҷ�ֵ�ĻҶ�ͼ��
 ************************************************************************/

BOOL  HoughTrans(LPSTR lpDIBBits, LONG lmageWidth, LONG lmageHeight)
{
	// ָ��Դͼ���ָ��
	unsigned char*	lpSrc;		
	// ָ��Ҫ���������ָ��
	unsigned char*	lpDst;
	// ָ��任���ָ��
	unsigned char*  lpTrans;
	// ָ����ͼ���ָ��
	LPBYTE lpImage;
	//ָ��任���ָ��
	LPBYTE lptransImage;
	//�任��ĳߴ�
	int mMaxDist;//����
	int mMaxAngleNumber;//�Ƕ�
	//�任�������
	int mDist;
	int mAngleNumber;
	//ѭ������
	int i;
	int j;
	//����ֵ
	unsigned char pixel;
	//��ʱ���ر���
	unsigned char pixeltemp;

	//�洢�任���е����ֵ
	MaxValue MaxValue1;
	MaxValue MaxValue2;

	lpImage = (LPBYTE) new  char[lmageWidth*lmageHeight];	
	// �ж��Ƿ��ڴ����ʧ��
	if (lpImage == NULL)
	{
		// �����ڴ�ʧ��
		return FALSE;
	}
	
	// ��ʼ���·�����ڴ棬�趨��ʼֵΪ255
	lpDst = (unsigned char *)lpImage;
	memset(lpDst, (BYTE)255, lmageWidth*lmageHeight);
	//����任��ĳߴ�
	//������
	mMaxDist = (int) sqrt(lmageWidth*lmageWidth + lmageHeight*lmageHeight);
	//�Ƕȴ�0��180��ÿ��2��
	mMaxAngleNumber = 90;
	//Ϊ�任������ڴ�
	lptransImage = (LPBYTE) new  int[lmageWidth*lmageHeight];
	if (lptransImage == NULL)
	{
		// �����ڴ�ʧ��
		return FALSE;
	}
	// ��ʼ���·�����ڴ棬�趨��ʼֵΪ255
	lpTrans = (unsigned char *)lptransImage;
	memset(lpTrans, 0, lmageWidth*lmageHeight);

	//���ͼ���Ƕ�ֵͼ��ת��Ϊ��ֵͼ��
	for(j = 0; j <lmageHeight; j++)
	{
		for(i = 0;i <lmageWidth; i++)
		{

			// ָ��Դͼ������j�У���i�����ص�ָ��			
			lpSrc = (unsigned char *)lpDIBBits + lmageWidth * j + i;

			//ȡ�õ�ǰָ�봦������ֵ��ע��Ҫת��Ϊunsigned char��
			pixeltemp = (unsigned char)*lpSrc;

			//Ŀ��ͼ���лҶ�ֵ����120������Ϊ255����������Ϊ0
			if(pixeltemp >= 120)
			{
				*lpSrc=(unsigned char)255;
			}
			else
			{
				*lpSrc=(unsigned char)0;
			}

			pixel = (unsigned char)*lpSrc;
				//����Ǻڵ㣬���ڱ任��Ķ�Ӧ�����ϼ�1
			if(pixel == 0)
			{
				//ע�ⲽ����2��
				for(mAngleNumber=0; mAngleNumber<mMaxAngleNumber; mAngleNumber++)
				{
					mDist = (int) fabs(i*cos(mAngleNumber*2*PI/180.0) + j*sin(mAngleNumber*2*PI/180.0));
				
					//�任��Ķ�Ӧ���ϼ�1
					*(lptransImage+mDist*mMaxAngleNumber+mAngleNumber) = *(lptransImage+mDist*mMaxAngleNumber+mAngleNumber) +1;
				}
			}

		}
	}
	//�ҵ��任���е����ֵ��
	MaxValue1.Value=0;
	MaxValue2.Value=0;

	//�ҵ���һ�����ֵ��
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

	//����һ�����ֵ�㸽������
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

	//�ҵ��ڶ������ֵ��
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
			// ָ�򻺴�ͼ������j�У���i�����ص�ָ��			
			lpDst = (unsigned char *)lpImage + lmageWidth * j + i;	
			//����õ���ĳһ��ֱ���ϣ����ڻ���ͼ���Ͻ��õ㸳Ϊ��		
			//�ڵ�һ��ֱ����
			mDist = (int) fabs(i*cos(MaxValue1.AngleNumber*2*PI/180.0) + j*sin(MaxValue1.AngleNumber*2*PI/180.0));
			if ((mDist == MaxValue1.Dist)&&(*lpSrc==(unsigned char)0))
			{
				*lpDst = (unsigned char)0;
			}

			//�ڵڶ���ֱ����
			mDist = (int) fabs(i*cos(MaxValue2.AngleNumber*2*PI/180.0) + j*sin(MaxValue2.AngleNumber*2*PI/180.0));
			if ((mDist == MaxValue2.Dist)&&(*lpSrc==(unsigned char)0))
			{
			*lpDst = (unsigned char)0;
			}
		}
	}
	// ���ƻ���任���ͼ��
	memcpy(lpDIBBits, lpImage, lmageWidth * lmageHeight);
	delete[] lpImage;
	delete[] lptransImage;
	// ����
	return TRUE;

}


/*************************************************************************
 * �������ƣ�
 *   Outline()
 * ����:
 *   LPSTR lpDIBBits    - ָ��ԴDIBͼ��ָ��
 *   LONG  lmageWidth       - Դͼ���ȣ���������������4�ı�����
 *   LONG  lmageHeight      - Դͼ��߶ȣ���������
 * ����ֵ:
 *   BOOL               - ����ɹ�����TRUE�����򷵻�FALSE��
 *
 * ˵��:
 * �ú������ڶ�ͼ�����������ȡ���㡣
 * Ҫ��Ŀ��ͼ��Ϊֻ��0��255�����Ҷ�ֵ�ĻҶ�ͼ��
 ************************************************************************/

BOOL Outline(LPSTR lpDIBBits, LONG lmageWidth, LONG lmageHeight)
{
	// ָ��Դͼ���ָ��
	unsigned char*	lpSrc;	
	// ָ��Ҫ���������ָ��
	unsigned char*	lpDst;
	// ָ����ͼ���ָ��
	LPBYTE lpImage;
	// ѭ������
	int			i;
	int			j;
	//��Ŵ������ذ���������ػҶ�
	unsigned char n,e,s,w,ne,se,nw,sw;
	// ��ʱ�����ڴ棬�Ա�����ͼ��
	lpImage = (LPBYTE) new char[lmageWidth*lmageHeight];	
	// �ж��Ƿ��ڴ����ʧ��
	if (lpImage == NULL)
	{
		// �����ڴ�ʧ��
		return FALSE;
	}
	//����ֵ
	unsigned char pixeltemp;
	// ��ʼ���·�����ڴ棬�趨��ʼֵΪ255
	lpDst = (unsigned char *)lpImage;
	memset(lpDst, (BYTE)255, lmageWidth * lmageHeight);

	//���ͼ���Ƕ�ֵͼ��ת��Ϊ��ֵͼ��
	for(j = 0; j <lmageHeight; j++)
	{
		for(i = 0;i <lmageWidth; i++)
		{

			// ָ��Դͼ������j�У���i�����ص�ָ��			
			lpSrc = (unsigned char *)lpDIBBits + lmageWidth * j + i;

			//ȡ�õ�ǰָ�봦������ֵ��ע��Ҫת��Ϊunsigned char��
			pixeltemp = (unsigned char)*lpSrc;

			//Ŀ��ͼ���лҶ�ֵ����120������Ϊ255����������Ϊ0
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
			//Ϊ��ֹԽ�磬��ȣ��߶��������Ҹ�����һ��
			// ָ��Դͼ������j�У���i�����ص�ָ��			
			lpSrc = (unsigned char *)lpDIBBits + lmageWidth * j + i;

			// ָ��Ŀ��ͼ������j�У���i�����ص�ָ��			
			lpDst = (unsigned char *)lpImage + lmageWidth * j + i;
			//�Ǻڵ��������	
			if(*(lpSrc)==0)
			{
				//Ŀ��ͼ����Ӧ������Ҳ��Ӧ��Ϊ�ڵ�
				*(lpDst)=0;
				w=(unsigned char)*(lpSrc-1);  //���ڵ�
                e=(unsigned char)*(lpSrc+1);  //���ڵ�
				nw=(unsigned char)*(lpSrc+lmageWidth-1); //�����ڵ�
                n=(unsigned char)*(lpSrc+lmageWidth); //���ڵ�
                ne=(unsigned char)*(lpSrc+lmageWidth+1); //�����ڵ�
                sw=(unsigned char)*(lpSrc-lmageWidth-1); //�����ڵ�
                s=(unsigned char)*(lpSrc-lmageWidth); //���ڵ�
                se=(unsigned char)*(lpSrc-lmageWidth+1); //�����ڵ�
				//������ڵİ˸��㶼�Ǻڵ�
				if(nw+n+ne+w+e+sw+s+se==0)
				{
					//���ͼ�иúڵ�ɾ��
					*(lpDst) = (unsigned char)255;
				}		 					 
			}		
		}
	}
	// ����������ȡ���ͼ��
	memcpy(lpDIBBits, lpImage, lmageWidth * lmageHeight);
	// �ͷ��ڴ�
	delete[] lpImage;
	// ����
	return TRUE;
}


/*************************************************************************
 * �������ƣ�
 *   ContourTrace()
 * ����:
 *   LPSTR lpDIBBits    - ָ��ԴDIBͼ��ָ��
 *   LONG  lWidth       - Դͼ���ȣ���������������4�ı�����
 *   LONG  lHeight      - Դͼ��߶ȣ���������
 * ����ֵ:
 *   BOOL               - ����ɹ�����TRUE�����򷵻�FALSE��
 * ˵��:
 * �ú������ڶ�ͼ����������������㡣
 * Ҫ��Ŀ��ͼ��Ϊֻ��0��255�����Ҷ�ֵ�ĻҶ�ͼ�񣬷����Զ�ת����
 ************************************************************************/

BOOL ContourTrace(LPSTR lpDIBBits, LONG lmageWidth, LONG lmageHeight)
{

	// ָ��Դͼ���ָ��
	unsigned char*	lpSrc;	
	// ָ��Ҫ���������ָ��
	unsigned char*	lpDst;
	// ָ����ͼ���ָ��
	LPBYTE lpImage;
	// ѭ������
	int			i;
	int			j;
	//����ֵ
	unsigned char pixeltemp;
	//�Ƿ��ҵ���ʼ�㼰�ص���ʼ��
	bool IsStartPoint;
	//�Ƿ�ɨ�赽һ���߽��
	bool Pointfind;
	//��ʼ�߽���뵱ǰ�߽��
	CPoint StartPoint;
	CPoint CurrentPoint;
	//�˸��������ʼɨ�跽��
	int Direction[8][2]={{-1,1},{0,1},{1,1},{1,0},{1,-1},{0,-1},{-1,-1},{-1,0}};
	int BeginDirect;

	// ��ʱ�����ڴ棬�Ա�����ͼ��
	lpImage = (LPBYTE) new char[lmageWidth*lmageHeight];	
	// �ж��Ƿ��ڴ����ʧ��
	if (lpImage == NULL)
	{
		// �����ڴ�ʧ��
		return FALSE;
	}
	
	// ��ʼ���·�����ڴ棬�趨��ʼֵΪ255
	lpDst = (unsigned char *)lpImage;
	memset(lpDst, (BYTE)255, lmageWidth * lmageHeight);

		//���ͼ���Ƕ�ֵͼ��ת��Ϊ��ֵͼ��
	for(j = 0; j <lmageHeight; j++)
	{
		for(i = 0;i <lmageWidth; i++)
		{

			// ָ��Դͼ������j�У���i�����ص�ָ��			
			lpSrc = (unsigned char *)lpDIBBits + lmageWidth * j + i;

			//ȡ�õ�ǰָ�봦������ֵ��ע��Ҫת��Ϊunsigned char��
			pixeltemp = (unsigned char)*lpSrc;

			//Ŀ��ͼ���лҶ�ֵ����120������Ϊ255����������Ϊ0
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

	//���ҵ�ͼ�������·��ı߽�㣬ע�������·�
	IsStartPoint = false;
	for (j = 1;j < lmageHeight && !IsStartPoint;j++)
	{
		for(i = 1;i < lmageWidth && !IsStartPoint;i++)
		{
			// ָ��Դͼ������j�У���i�����ص�ָ��			
			lpSrc = (unsigned char *)lpDIBBits + lmageWidth * j + i;
			
			//ȡ�õ�ǰָ�봦������ֵ
			pixeltemp = (unsigned char)*lpSrc;
			//���Ϊ�ڵ㣬��Ϊ��ʼ��		
			if(pixeltemp == 0)
			{
				IsStartPoint = true;
				StartPoint.y = j;		//��ʼ��Ĵ�ֱλ��
				StartPoint.x = i;		//��ʼ���ˮƽλ��

				// ָ��Ŀ��ͼ������j�У���i�����ص�ָ��			
				lpDst = (unsigned char *)lpImage + lmageWidth * j + i;	
				*lpDst = (unsigned char)0;		//Ŀ�������Ϊ�ڵ�
			}		
		}
	}

	//������ʼ���������·�������ʼɨ�������Ϸ���
	BeginDirect = 0;
	//���ٱ߽�
	IsStartPoint = false;
	//�ӳ�ʼ�㿪ʼɨ��
	CurrentPoint.y = StartPoint.y;
	CurrentPoint.x = StartPoint.x;
	while(!IsStartPoint)
	{
		Pointfind = false;
		while(!Pointfind)
		{
			//��ɨ�跽��鿴��һ������
			lpSrc = (unsigned char *)lpDIBBits + lmageWidth * ( CurrentPoint.y + Direction[BeginDirect][1])
				+ (CurrentPoint.x + Direction[BeginDirect][0]);
			//�����õ������ֵ
			pixeltemp = (unsigned char)*lpSrc;
			//����õ�Ϊ�ڵ�
			if(pixeltemp == 0)
			{
				//�ҵ��˵㣬����Ϊ��
				Pointfind = true;
				//��¼��ǰ���λ��
				CurrentPoint.y = CurrentPoint.y + Direction[BeginDirect][1];
				CurrentPoint.x = CurrentPoint.x + Direction[BeginDirect][0];
				//�����ǰ�������ʼ��
				if(CurrentPoint.y == StartPoint.y && CurrentPoint.x == StartPoint.x)
				{
					//��ʼ���������Ϊ�棬�˳�ѭ��
					IsStartPoint = true;
				}
				//��¼��ǰ�㣬����Ϊ�ڵ�
				lpDst = (unsigned char *)lpImage + lmageWidth * CurrentPoint.y + CurrentPoint.x;
				*lpDst = (unsigned char)0;
				//ɨ��ķ�����ʱ����ת����
				BeginDirect--; //ѡ��һ��
				if(BeginDirect == -1)  //�������Ϊ��1�����Ƿ���7
				{
					BeginDirect = 7;
				}
				BeginDirect--;
				if(BeginDirect == -1)	//�������Ϊ��1�����Ƿ���7
				{
					BeginDirect = 7;
				}
			}
			//ɨ�跽�����һ����Ϊ�׵㣬��ô������Ҫ�ı�ɨ�跽�򣬼���Ѱ��
			else
			{
				//ɨ�跽��˳ʱ����תһ��
				BeginDirect++;
				if(BeginDirect == 8)
				{
					BeginDirect = 0;	//�������Ϊ8�����Ƿ���0
				}

			}

		}
	}

	// �����������ٺ��ͼ��
	memcpy(lpDIBBits, lpImage, lmageWidth * lmageHeight);
	// �ͷ��ڴ�
	delete[] lpImage;
	// ����
	return TRUE;
}
//ǿ��һ�㣬������ֻ���������ٵļ���ʾ����������ͼ������·����ҵ��ĵ�һ���ڵ�
//������Ϊ��ʼ�㣬�Դ˵�Ϊ�������б߽�ɨ�裬���ֻ�ܸ���һ���������������ж������
//������Ҫ����ʱ����Ҫ���Ѿ����ٹ�������ȥ���������������̡�

/*************************************************************************
 * �������ƣ�
 *   RegionDivideThreshold()
 * ����:
 *   LPSTR lpDIBBits    - ָ��ԴDIBͼ��ָ��
 *   LONG  lWidth       - Դͼ���ȣ���������������4�ı�����
 *   LONG  lHeight      - Դͼ��߶ȣ���������
 *   int threshold		- �ָ�����
 * ����ֵ:
 *   BOOL               - ����ɹ�����TRUE�����򷵻�FALSE��
 * ˵��:
 * �ú������ڶ�ͼ����й̶���ֵ�ָ
 ************************************************************************/
BOOL RegionDivideThreshold(LPSTR lpDIBBits, LONG lmageWidth, LONG lmageHeight, int threshold)
{
	int i;  //ѭ������
	int j;	//ѭ������
	// ָ��Դͼ���ָ��
	unsigned char*	lpSrc;	
	//����ֵ
	unsigned char pixeltemp;
	for(j = 0; j <lmageHeight; j++)
	{
		for(i = 0;i <lmageWidth; i++)
		{

			// ָ��Դͼ������j�У���i�����ص�ָ��			
			lpSrc = (unsigned char *)lpDIBBits + lmageWidth * j + i;
			//ȡ�õ�ǰָ�봦������ֵ
			pixeltemp = (unsigned char)*lpSrc;
			//Ŀ��ͼ���лҶ�ֵС������������Ϊ�ڵ�
			if(pixeltemp <= threshold)
			{
				*lpSrc=(unsigned char)0;
			}
			else	//��������Ϊ�׵�
			{
				*lpSrc=(unsigned char)255;
			}		
		}
	}
	return true;
}

/*************************************************************************
 * \�������ƣ�
 *   RegionDivideAdaptive()
 * ����:
 *   LPSTR lpDIBBits    - ָ��ԴDIBͼ��ָ��
 *   LONG  lmageWidth       - Դͼ���ȣ���������������4�ı�����
 *   LONG  lmageHeight      - Դͼ��߶ȣ���������
 * ����ֵ:
 *   BOOL               - ����ɹ�����TRUE�����򷵻�FALSE��
 * ˵��:
 * �ú������ڶ�ͼ���������Ӧ��ֵ�ָ��ͼ��ֳ��ĸ���ͼ��Ȼ�����ÿ����ͼ��ľ�ֵ��
 *  ���ݾ�ֵ������ֵ����ֵֻ��Ӧ���ڶ�Ӧ����ͼ��
 *************************************************************************
 */
BOOL RegionDivideAdaptive(LPSTR lpDIBBits, LONG lmageWidth, LONG lmageHeight)
{
	int i;  //ѭ������
	int j;	//ѭ������
	// ָ��Դͼ���ָ��
	unsigned char*	lpSrc;	
	//����ֵ
	unsigned char pixeltemp;	
	// ��ͼ��Ҷȵ�ƽ��ֵ
	int nAvg ;
	nAvg = 0 ; //��ʼ��Ϊ0
	// ������ͼ�����ɨ�裺
	for(j = 0; j <lmageHeight/2; j++)
	{
		for(i = 0;i <lmageWidth/2; i++)
		{
			// ָ��Դͼ������j�У���i�����ص�ָ��			
			lpSrc = (unsigned char *)lpDIBBits + lmageWidth * j + i;
			//ȡ�õ�ǰָ�봦������ֵ
			pixeltemp = (unsigned char)*lpSrc;
			//�Ҷȵ��ۼ�
			nAvg = (int)pixeltemp+nAvg;
		}
	}
	// �����ֵ
	nAvg = nAvg /((lmageHeight/2) * (lmageWidth/2)) ;
	// ������ͼ�����ɨ�裺
	for(j = 0; j <lmageHeight/2; j++)
	{
		for(i = 0;i <lmageWidth/2; i++)
		{
			// ָ��Դͼ������j�У���i�����ص�ָ��			
			lpSrc = (unsigned char *)lpDIBBits + lmageWidth * j + i;
			//ȡ�õ�ǰָ�봦������ֵ
			pixeltemp = (unsigned char)*lpSrc;
			//Ŀ��ͼ���лҶ�ֵС������������Ϊ�ڵ�
			if(pixeltemp <= nAvg)
			{
				*lpSrc=(unsigned char)0;
			}
			else	//��������Ϊ�׵�
			{
				*lpSrc=(unsigned char)255;
			}		
		}
	}

	nAvg =0;   //��ʼ��Ϊ0

	// ������ͼ�����ɨ�裺
	for(j = lmageHeight/2; j <lmageHeight; j++)
	{
		for(i = 0;i <lmageWidth/2; i++)
		{
			// ָ��Դͼ������j�У���i�����ص�ָ��			
			lpSrc = (unsigned char *)lpDIBBits + lmageWidth * j + i;
			//ȡ�õ�ǰָ�봦������ֵ
			pixeltemp = (unsigned char)*lpSrc;
			//�Ҷȵ��ۼ�
			nAvg = (int)pixeltemp+nAvg;
		}
	}
	// �����ֵ
	nAvg = nAvg /((lmageHeight/2) * (lmageWidth/2)) ;
	// ������ͼ�����ɨ�裺
	for(j = lmageHeight/2; j <lmageHeight; j++)
	{
		for(i = 0;i <lmageWidth/2; i++)
		{
			// ָ��Դͼ������j�У���i�����ص�ָ��			
			lpSrc = (unsigned char *)lpDIBBits + lmageWidth * j + i;
			//ȡ�õ�ǰָ�봦������ֵ
			pixeltemp = (unsigned char)*lpSrc;
			//Ŀ��ͼ���лҶ�ֵС������������Ϊ�ڵ�
			if(pixeltemp <= nAvg)
			{
				*lpSrc=(unsigned char)0;
			}
			else	//��������Ϊ�׵�
			{
				*lpSrc=(unsigned char)255;
			}		
		}
	}

	nAvg =0;   //��ʼ��Ϊ0

	// ������ͼ�����ɨ�裺
	for(j = lmageHeight/2; j <lmageHeight; j++)
	{
		for(i = lmageWidth/2;i <lmageWidth; i++)
		{
			// ָ��Դͼ������j�У���i�����ص�ָ��			
			lpSrc = (unsigned char *)lpDIBBits + lmageWidth * j + i;
			//ȡ�õ�ǰָ�봦������ֵ
			pixeltemp = (unsigned char)*lpSrc;
			//�Ҷȵ��ۼ�
			nAvg = (int)pixeltemp+nAvg;
		}
	}
	// �����ֵ
	nAvg = nAvg /((lmageHeight/2) * (lmageWidth/2)) ;
	// ������ͼ�����ɨ�裺
	for(j = lmageHeight/2; j <lmageHeight; j++)
	{
		for(i = lmageWidth/2;i <lmageWidth; i++)
		{
			// ָ��Դͼ������j�У���i�����ص�ָ��			
			lpSrc = (unsigned char *)lpDIBBits + lmageWidth * j + i;
			//ȡ�õ�ǰָ�봦������ֵ
			pixeltemp = (unsigned char)*lpSrc;
			//Ŀ��ͼ���лҶ�ֵС������������Ϊ�ڵ�
			if(pixeltemp <= nAvg)
			{
				*lpSrc=(unsigned char)0;
			}
			else	//��������Ϊ�׵�
			{
				*lpSrc=(unsigned char)255;
			}		
		}
	}

		nAvg =0;   //��ʼ��Ϊ0

	// ������ͼ�����ɨ�裺
	for(j = 0; j <lmageHeight/2; j++)
	{
		for(i = lmageWidth/2;i <lmageWidth; i++)
		{
			// ָ��Դͼ������j�У���i�����ص�ָ��			
			lpSrc = (unsigned char *)lpDIBBits + lmageWidth * j + i;
			//ȡ�õ�ǰָ�봦������ֵ
			pixeltemp = (unsigned char)*lpSrc;
			//�Ҷȵ��ۼ�
			nAvg = (int)pixeltemp+nAvg;
		}
	}
	// �����ֵ
	nAvg = nAvg /((lmageHeight/2) * (lmageWidth/2)) ;
	// ������ͼ�����ɨ�裺
	for(j = 0; j <lmageHeight/2; j++)
	{
		for(i = lmageWidth/2;i <lmageWidth; i++)
		{
			// ָ��Դͼ������j�У���i�����ص�ָ��			
			lpSrc = (unsigned char *)lpDIBBits + lmageWidth * j + i;
			//ȡ�õ�ǰָ�봦������ֵ
			pixeltemp = (unsigned char)*lpSrc;
			//Ŀ��ͼ���лҶ�ֵС������������Ϊ�ڵ�
			if(pixeltemp <= nAvg)
			{
				*lpSrc=(unsigned char)0;
			}
			else	//��������Ϊ�׵�
			{
				*lpSrc=(unsigned char)255;
			}		
		}
	}
	return true;
}


/*************************************************************************
 * \�������ƣ�
 *   RegionGrow()
 * ����:
 *   LPSTR lpDIBBits    - ָ��ԴDIBͼ��ָ��
 *   LONG  lmageWidth       - Դͼ���ȣ���������������4�ı�����
 *   LONG  lmageHeight      - Դͼ��߶ȣ���������
 *	 int nThreshold			- ������������
 *	 int seedx				- �����������ӵĺ�����
 *	 int seedy				- �����������ӵ�������
  *	 int mode				- �����������ӵ�ѡȡ����
 * ����ֵ:
 *   BOOL               - ����ɹ�����TRUE�����򷵻�FALSE��
 * \˵��:
 *   �������Ĵ������ǽ�������������ʾΪ��ɫ���أ�δ���������ʾΪ��ɫ���ء�
 *   ��������һ����������Ƚ���Ҫ�����⣺
 *		1. ���ӵ��ѡȡ
 *		2. ����׼��
 *		3. ��ֹ����
 *	 ������Ϊ��������������Ҫ�������������ÿ���������ĺû�ֱ�ӹ�ϵ��
 *	 ���������Ľ����
 *************************************************************************/
BOOL RegionGrow(LPSTR lpDIBBits, LONG lmageWidth, LONG lmageHeight, int nThreshold,int seedx,int seedy,int mode)
{	
	//�������ڴ��������������
	static int Dx[]={-1,0,1,0};	//X��
	static int Dy[]={0,1,0,-1};	//y��
	// ��ʱ���ͼ�����ݵ�ָ��
	LPBYTE			lpImage;	
	// ָ��Դͼ���ָ��
	unsigned char*	lpSrc;
	unsigned char*	lpSrc1;
	// ָ��Ҫ���������ָ��
	unsigned char*	lpDst;
	// �����ڴ�
	lpImage = (LPBYTE) new  char[lmageWidth*lmageHeight];	
	// �ж��Ƿ��ڴ����ʧ��
	if (lpImage == NULL)
	{
		// �����ڴ�ʧ��
		return FALSE;
	}
	// ��Ŀ��ͼ���������س�ʼ��Ϊ�׵�
	lpDst = (unsigned char *)lpImage;
	memset(lpDst, (BYTE)255, lmageWidth * lmageHeight);
	// ���ӵ�
	CPoint seed;
	if(mode==0) // ���ѡ�����ӵ�Ϊͼ�������
	{
		// �������ӵ�Ϊͼ�������
		seed.x=lmageWidth/2;
		seed.y=lmageHeight/2;
	}
	else //�Լ��������ӵ�
	{
		// �������ӵ�Ϊ�����
		seed.x=seedx;
		seed.y=seedy;
	}

	// �����ջ���ֱ����X Y����
	int * GrowX ;
	int * GrowY ;
	
	// ����ռ䣬���Ϊͼ���������Ŀ
	GrowX = new int [ lmageWidth * lmageHeight];
	GrowY = new int [ lmageWidth * lmageHeight];

	
	// �����ջ�������յ�
	// ��Start=End, ��ʾ��ջ��ֻ��һ����
	int Start ;
	int End   ;
	//��ʼ��
	Start = 0 ;
	End   = 0 ;
	// �����ӵ������ѹ��ջ
	GrowX[End] = seed.x;
	GrowY[End] = seed.y;
	// ��ǰ���ڴ��������
	CPoint Current;
	// ѭ�����Ʊ���
	int k ;
	// ͼ��ĺ�������,�����Ե�ǰ���ص�4������б���
	int xx;
	int yy;
	while (Start<=End)
	{
		// ��ǰ���ӵ������
		Current.x = GrowX[Start];
		Current.y = GrowY[Start];
		// �Ե�ǰ���4������б���
		for (k=0; k<4; k++)	
		{	
			// 4�������ص�����
			xx = Current.x+Dx[k];
			yy = Current.y+Dy[k];
			
			// �ж�����(xx��yy) �Ƿ���ͼ���ڲ�
			// �ж�����(xx��yy) �Ƿ��Ѿ������
			// *lpDst==255 ��ʾ��û�д���
			// ָ��Դͼ��(xx��yy)���ص�ָ��			
			lpSrc = (unsigned char *)lpDIBBits + lmageWidth * (lmageHeight-yy) + xx;
			lpSrc1 = (unsigned char *)lpDIBBits + lmageWidth * (lmageHeight-Current.y) + Current.x;
			// ָ��Ŀ��ͼ���j�У���i�����ص�ָ��			
			lpDst = (unsigned char *)lpImage + lmageWidth * (lmageHeight-yy) + xx;
			// �����������ж�����(xx��yy)�͵�ǰ����(nCurrX,nCurrY) ����ֵ��ľ���ֵ
			if ((xx < lmageWidth) && (xx>=0) && (yy<lmageHeight) && (yy>=0) && (*lpDst==255) 
					&& abs(*lpSrc-*lpSrc1)<nThreshold )
			{
				// ��ջ��β��ָ�����һλ
				End++;
				// ����(xx��yy) ѹ��ջ
				GrowX[End] = xx;
				GrowY[End] = yy;
				// Ŀ��ͼ��Ϊ�ڵ㣬ͬʱҲ���������ش����
				*lpDst=0 ;
			}
		}
		Start++;
	}
	// ���������������ͼ��
	memcpy(lpDIBBits, lpImage, lmageWidth * lmageHeight);
	// �ͷ��ڴ�
	delete[] lpImage;
	delete[] GrowX;
	delete[] GrowY;
	// ����
	return TRUE;
}

/*************************************************************************
 *
 * �������ƣ�
 *   Project()
 *
 * ����:
 *   LPSTR lpDIBBits		- ָ��ԴDIBͼ��ָ��
 *   LONG  lmageWidth       - Դͼ���ȣ���������������4�ı�����
 *   LONG  lmageHeight      - Դͼ��߶ȣ���������
 *	 int   direction		- ͶӰ����
 * ����ֵ:
 *   BOOL               - ����ɹ�����TRUE�����򷵻�FALSE��
 * ˵��:
 * �ú������ڶ�����ͼ�����ˮƽ����ֱͶӰ���㡣 
 * Ҫ��Ŀ��ͼ��Ϊֻ��0��255�����Ҷ�ֵ�ĻҶ�ͼ�񣬷���ǿ��ת����
 ************************************************************************/

BOOL  Project(LPSTR lpDIBBits, LONG lmageWidth, LONG lmageHeight, int direction)
{
	// ��ʱ���ͼ�����ݵ�ָ��
	LPBYTE			lpImage;	
	// ָ��Դͼ���ָ��
	unsigned char*	lpSrc;
	// ָ��Ҫ���������ָ��
	unsigned char*	lpDst;
	// �����ڴ�
	lpImage = (LPBYTE) new  char[lmageWidth*lmageHeight];	
	// �ж��Ƿ��ڴ����ʧ��
	if (lpImage == NULL)
	{
		// �����ڴ�ʧ��
		return FALSE;
	}
	// ��Ŀ��ͼ���������س�ʼ��Ϊ�׵�
	lpDst = (unsigned char *)lpImage;
	memset(lpDst, (BYTE)255, lmageWidth * lmageHeight);

	//ѭ������
	int i;
	int j;
	int k;
	//ͼ����ÿ���ڵĺڵ����
	int BlackNumber;
	//����ֵ
	unsigned char pixeltemp;	
	//���ͼ���Ƕ�ֵͼ��ת��Ϊ��ֵͼ��
	for(j = 0; j <lmageHeight; j++)
	{
		for(i = 0;i <lmageWidth; i++)
		{
			// ָ��Դͼ������j�У���i�����ص�ָ��			
			lpSrc = (unsigned char *)lpDIBBits + lmageWidth * j + i;
			//ȡ�õ�ǰָ�봦������ֵ��ע��Ҫת��Ϊunsigned char��
			pixeltemp = (unsigned char)*lpSrc;
			//Ŀ��ͼ���лҶ�ֵ����120������Ϊ255����������Ϊ0
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

	if(direction==0)  //ˮƽ����ͶӰ
	{
		for(j = 0; j <lmageHeight; j++)
		{
			BlackNumber = 0;	//�ڵ���Ŀ��0
			for(i = 0;i <lmageWidth; i++)
			{
				// ָ��Դͼ������j�У���i�����ص�ָ��			
				lpSrc = (unsigned char *)lpDIBBits + lmageWidth * j + i;
				//ȡ�õ�ǰָ�봦������ֵ��ע��Ҫת��Ϊunsigned char��
				pixeltemp = (unsigned char)*lpSrc;
				if(pixeltemp == 0)//������ֺڵ�
				{
					BlackNumber++; //�ڵ���Ŀ��1
				}
			}
			for(k = 0;k < BlackNumber ;k++)
			{	
				// ָ��Ŀ��ͼ������j�У���i�����ص�ָ��			
				lpDst = (unsigned char *)lpImage + lmageWidth * j + k;
				*lpDst = (unsigned char)0; //��Ϊ�ڵ�
			}	
		}
	}
	else if(direction==1)  //��ֱ����ͶӰ
	{
		for(i = 0;i <lmageWidth; i++)
		{
			BlackNumber = 0;	//�ڵ���Ŀ��0
			for(j = 0; j <lmageHeight; j++)
			{
				// ָ��Դͼ������j�У���i�����ص�ָ��			
				lpSrc = (unsigned char *)lpDIBBits + lmageWidth * j + i;
				//ȡ�õ�ǰָ�봦������ֵ��ע��Ҫת��Ϊunsigned char��
				pixeltemp = (unsigned char)*lpSrc;
				if(pixeltemp == 0)//������ֺڵ�
				{
					BlackNumber++; //�ڵ���Ŀ��1
				}
			}
			for(k = 0;k < BlackNumber ;k++)
			{	
				// ָ��Ŀ��ͼ������j�У���i�����ص�ָ��			
				lpDst = (unsigned char *)lpImage + lmageWidth * k + i;
				*lpDst = (unsigned char)0; //��Ϊ�ڵ�
			}	
		}
	}
	// ���������������ͼ��
	memcpy(lpDIBBits, lpImage, lmageWidth * lmageHeight);
	// �ͷ��ڴ�
	delete[] lpImage;
	// ����
	return TRUE;
}

/*************************************************************************
 * �������ƣ�
 *   Subtract()
 * ����:
 *   LPSTR lpDIBBits1   - ָ��ԴDIBͼ��ָ��
 *   LPSTR lpDIBBits2   - ָ�򱳾�DIBͼ��ָ��
 *   LONG  lmageWidth       - Դͼ���ȣ���������������4�ı�����
 *   LONG  lmageHeight      - Դͼ��߶ȣ���������
 *
 * ����ֵ:
 *   BOOL               - ����ɹ�����TRUE�����򷵻�FALSE��
 * ˵��:
 * �ú������ڶ�����ͼ����в�Ӱ���㡣
 * Ҫ��Ŀ��ͼ��Ϊ255���Ҷ�ֵ�ĻҶ�ͼ��
 ************************************************************************/

BOOL Subtract(LPSTR lpDIBBits1, LPSTR lpDIBBits2, LONG lmageWidth, LONG lmageHeight)
{
	// ��ʱ���ͼ�����ݵ�ָ��
	LPBYTE			lpImage;	
	// ָ��Դͼ���ָ��
	unsigned char*	lpSrc1;
	// ָ�򱳾�ͼ���ָ��
	unsigned char*	lpSrc2;
	// ָ��Ҫ���������ָ��
	unsigned char*	lpDst;
	//����ֵ
	unsigned char pixeltemp1;
	unsigned char pixeltemp2;
	// �����ڴ�
	lpImage = (LPBYTE) new  char[lmageWidth*lmageHeight];	
	// �ж��Ƿ��ڴ����ʧ��
	if (lpImage == NULL)
	{
		// �����ڴ�ʧ��
		return FALSE;
	}
	// ��Ŀ��ͼ���������س�ʼ��Ϊ�׵�
	lpDst = (unsigned char *)lpImage;
	memset(lpDst, (BYTE)255, lmageWidth * lmageHeight);

	//ѭ������
	int i;
	int j;
	for(j = 0; j <lmageHeight; j++)
	{
		for(i = 0;i <lmageWidth; i++)
		{
			// ָ��Դͼ������j�У���i�����ص�ָ��			
			lpSrc1 = (unsigned char *)lpDIBBits1 + lmageWidth * j + i;
			// ָ�򱳾�ͼ������j�У���i�����ص�ָ��			
			lpSrc2 = (unsigned char *)lpDIBBits2 + lmageWidth * j + i;
			// ָ�򻺳�ͼ������j�У���i�����ص�ָ��			
			lpDst = (unsigned char *)lpImage + lmageWidth * j + i;
			//ȡ��Դͼ��ǰָ�봦������ֵ��ע��Ҫת��Ϊunsigned char��
			pixeltemp1 = (unsigned char)*lpSrc1;
			//ȡ�ñ���ͼ��ǰָ�봦������ֵ��ע��Ҫת��Ϊunsigned char��
			pixeltemp2 = (unsigned char)*lpSrc2;
			//���в�Ӱ����
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

	// ���������������ͼ��
	memcpy(lpDIBBits1, lpImage, lmageWidth * lmageHeight);
	// �ͷ��ڴ�
	delete[] lpImage;
	// ����
	return TRUE;
}


/*************************************************************************
 * �������ƣ�
 *   TemplateMatch()
 * ����:
 *   LPSTR lpDIBBits1    - ָ��ԴDIBͼ��ָ��
 *   LPSTR lpDIBBits2    - ָ��ģ��DIBͼ��ָ��
 *   LONG  lmageWidth    - Դͼ���ȣ���������������4�ı�����
 *   LONG  lmageHeight   - Դͼ��߶ȣ���������
 *   LONG  TemplateWidth       - ģ��ͼ���ȣ���������������4�ı�����
 *   LONG  TemplateHeight      - ģ��ͼ��߶ȣ���������
 * ����ֵ:
 *   BOOL               - ����ɹ�����TRUE�����򷵻�FALSE��
 * ˵��:
 * �ú������ڶ�ͼ�����ģ��ƥ�����㡣
 * Ҫ��Ŀ��ͼ��Ϊ255���Ҷ�ֵ�ĻҶ�ͼ��
 ************************************************************************/

BOOL TemplateMatch(LPSTR lpDIBBits1, LPSTR lpDIBBits2,  LONG lmageWidth, LONG lmageHeight,
							  LONG TemplateWidth,LONG TemplateHeight)
{	
	// ��ʱ���ͼ�����ݵ�ָ��
	LPBYTE			lpImage;	
	// ָ��Դͼ���ָ��
	unsigned char*	lpSrc1;
	// ָ��ģ��ͼ���ָ��
	unsigned char*	lpSrc2;
	// ָ��Ҫ���������ָ��
	unsigned char*	lpDst;
	//����ֵ
	unsigned char pixeltemp1;//Դͼ������
	unsigned char pixeltemp2;//ģ��ͼ������
	// �����ڴ�
	lpImage = (LPBYTE) new  char[lmageWidth*lmageHeight];	
	// �ж��Ƿ��ڴ����ʧ��
	if (lpImage == NULL)
	{
		// �����ڴ�ʧ��
		return FALSE;
	}
	// ��Ŀ��ͼ���������س�ʼ��Ϊ�Ұ׵�
	lpDst = (unsigned char *)lpImage;
	memset(lpDst, (BYTE)205, lmageWidth * lmageHeight);
	//ѭ������
	int i;
	int j;
	int m;
	int n;
	int cofT;//ģ�����������ֵ
	int cofS;//Դ���������ֵ
	int cofTS;//ģ�塢Դͼ�����ػҶȻ����ֵ
	double R;//���R
	double Rmax;//�����
	CPoint matchpoint;//ƥ���
	//����cofT
	cofT = 0;
	for(j = 0; j <TemplateHeight; j++)
	{
		for(i = 0;i <TemplateWidth; i++)
		{
			// ָ��ģ��ͼ������j�У���i�����ص�ָ��			
			lpSrc2 = (unsigned char *)lpDIBBits2 + lmageWidth * j + i;
			//ȡ��ģ��ͼ��ǰָ�봦������ֵ��ע��Ҫת��Ϊunsigned char��
			pixeltemp2 = (unsigned char) *lpSrc2;
			//�������������
			cofT=cofT+pixeltemp2*pixeltemp2;
		}
	}

	//�ҵ�ͼ������������Եĳ���λ��
	Rmax = 0.0;
	for (j = 0;j < lmageHeight - TemplateHeight +1 ;j++)
	{
		for(i = 0;i < lmageWidth - TemplateWidth + 1;i++)
		{
			cofS = 0; //��ʼ��Ϊ0
			cofTS = 0;//��ʼ��Ϊ0

			for (n = 0;n < TemplateHeight ;n++)
			{
				for(m = 0;m < TemplateWidth ;m++)
				{
					// ָ��Դͼ������j+n�У���i+m�����ص�ָ��			
					lpSrc1 = (unsigned char *)lpDIBBits1+ lmageWidth * (j+n) + (i+m);
					// ָ��ģ��ͼ������n�У���m�����ص�ָ��			
					lpSrc2 = (unsigned char *)lpDIBBits2 + TemplateWidth * n + m;
					//��ȡ
					pixeltemp1 = (unsigned char)*lpSrc1;
					pixeltemp2 = (unsigned char)*lpSrc2;

					cofS = cofS+(double)pixeltemp1*pixeltemp1;
					cofTS = cofTS+(double)pixeltemp1*pixeltemp2;
				}
			}
			//����������
			R = cofTS / ( sqrt(cofS)*sqrt(cofT));
			//����������ԱȽ�
			if (R > Rmax)
			{
				Rmax = R;
				matchpoint.x = i;
				matchpoint.y = j;
			}
		}
	}
	

	//��Դͼ������ģ��ͼ��ƥ������������Ƶ�Ŀ��ͼ��
	for (n = 0;n < TemplateHeight ;n++)
	{
		for(m = 0;m < TemplateWidth ;m++)
		{
			lpSrc1 = (unsigned char *)lpDIBBits1 + lmageWidth  * (n+matchpoint.y) + (m+matchpoint.x);
			lpDst = (unsigned char *)lpImage + lmageWidth  * (n+matchpoint.y) + (m+matchpoint.x);
			*lpDst = *lpSrc1;
		}
	}	
	// ����ͼ��
	memcpy(lpDIBBits1, lpImage, lmageWidth * lmageHeight);
	// �ͷ��ڴ�
	delete[] lpImage;
	// ����
	return TRUE;
}


/*************************************************************************
 * �������ƣ�
 *	 PCXCoding()
 * ����:
 *   LPSTR   lpDIBBits  - ָ��DIB�������ص�ָ��
 *   LONG  ImageWidth   - Դͼ���ȣ���������������4�ı�����
 *   LONG  ImageHeight  - Դͼ��߶ȣ���������
 *   CFile& file        - Ҫ������ļ�
 * ����ֵ:
 *   BOOL               - �ɹ�����True�����򷵻�False��
 * ˵��:
 *   �ú�����ָ����256ɫDIB���󱣴�Ϊ256ɫPCX�ļ���
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

	// ѭ������
	int	i;
	int	j;
	// �м����
	BYTE	bChar1;
	BYTE	bChar2;
	
	// ָ��Դͼ�����ص�ָ��
	BYTE *	lpSrc;	
	// ָ������ͼ�����ݵ�ָ��
	BYTE *	lpDst;	
	// �ظ����ؼ���
	int		iCount;	
	// ��������ʹ�õ��ֽ���
	DWORD	dwBuffUsed;
	// PCX�ļ�ͷ
	PCXHEAD pcxHeadr;	
	// PCX��ʶ��
	pcxHeadr.manufacturer = 0x0A;	
	// PCX�汾��
	pcxHeadr.version = 5;
	// PCX���뷽ʽ��1��ʾRLE���룩
	pcxHeadr.encoding = 1;
	// ����λ����256ɫΪ8λ��
	pcxHeadr.bits_per_pixel = 8;
	// ͼ���������Ļ�����Ͻ�X���꣨������Ϊ��λ��
	pcxHeadr.xmin = 0;
	// ͼ���������Ļ�����Ͻ�Y���꣨������Ϊ��λ��
	pcxHeadr.ymin = 0;
	// ͼ���������Ļ�����½�X���꣨������Ϊ��λ��
	pcxHeadr.xmax = ImageWidth - 1;
	// ͼ���������Ļ�����½�Y���꣨������Ϊ��λ��
	pcxHeadr.ymax = ImageHeight - 1;
	// ͼ���ˮƽ�ֱ���
	pcxHeadr.hres = ImageWidth;
	// ͼ��Ĵ�ֱ�ֱ���
	pcxHeadr.vres = ImageHeight;
	// ��ɫ�����ݣ�����256ɫPCX�����壬ֱ�Ӹ�ֵΪ0��
	for (i = 0; i < 48; i ++)
	{
		pcxHeadr.palette[i] = 0;
	}	
	// �������趨Ϊ0��
	pcxHeadr.reserved = 0;	
	// ͼ��ɫ��ƽ����Ŀ������256ɫPCX�趨Ϊ1����
	pcxHeadr.colour_planes = 1;	
	// ͼ��Ŀ�ȣ��ֽ�Ϊ��λ��������Ϊż����
	pcxHeadr.bytes_per_line = ImageWidth;
	// ͼ���ɫ������ͣ�1��ʾ��ɫ���ߵ�ɫͼ��2��ʾͼ���ǻҶ�ͼ��
	pcxHeadr.palette_type = 1;
	// ������ͼ�����Ļ��ȣ�����Ϊ��λ��
//	pcxHeadr.wSrcWidth = 0;
	// ������ͼ�����Ļ�߶ȣ�����Ϊ��λ��
//	pcxHeadr.wSrcDepth = 0;
	// ������ȡֵ�趨Ϊ0��
	for (i = 0; i < 54; i ++)
	{
		pcxHeadr.filler[i] = 0;
	}	
	// д���ļ�ͷ
	file.Write((LPSTR)&pcxHeadr, sizeof(PCXHEAD));
	// ��ʼ����
	
	// ����һƬ������(2��ԭʼͼ���С)�Ա��������
	lpDst = new BYTE[ImageHeight * ImageWidth * 2];
	// ָ����ǰ�Ѿ����˶��ٻ��������ֽ�����
	dwBuffUsed = 0;	
	// ÿ��
	for (i = 0; i < ImageHeight; i++)
	{
		// ָ��DIB��i�У���0�����ص�ָ��
		lpSrc = (BYTE *)lpDIBBits + ImageWidth * (ImageHeight - 1 - i);	
		// ��bChar1��ֵ
		bChar1 = *lpSrc;	
		// ����iCountΪ1
		iCount = 1;
		// ʣ����
		for (j = 1; j < ImageWidth; j ++)
		{
			// ָ��DIB��i�У���j�����ص�ָ��
			lpSrc++;
			// ��ȡ��һ������
			bChar2 = *lpSrc;
			// �ж��Ƿ��bChar1��ͬ����iCount < 63
			if ((bChar1 == bChar2) && (iCount < 63))
			{
				// ��ͬ��������1
				iCount ++;	
				// ��������һ��
			}
			else
			{
				// ��ͬ������iCount = 63	
				// д�뻺����
				if ((iCount > 1) || (bChar1 >= 0xC0))
				{
					// �����볤��Ϣ
					lpDst[dwBuffUsed] = iCount | 0xC0;
					// ����bChar1
					lpDst[dwBuffUsed + 1] = bChar1;
					// ����dwBuffUsed
					dwBuffUsed += 2;
				}
				else
				{
					// ֱ�ӱ����ֵ
					lpDst[dwBuffUsed] = bChar1;
					// ����dwBuffUsed
					dwBuffUsed ++;
				}	
				// ���¸�bChar1��ֵ
				bChar1 = bChar2;
				// ����iCountΪ1
				iCount = 1;
			}
		}
		
		// ����ÿ�����һ���ֱ���
		if ((iCount > 1) || (bChar1 >= 0xC0))
		{
			// �����볤��Ϣ
			lpDst[dwBuffUsed] = iCount | 0xC0;	
			// ����bChar1
			lpDst[dwBuffUsed + 1] = bChar1;
			// ����dwBuffUsed
			dwBuffUsed += 2;
		}
		else
		{
			// ֱ�ӱ����ֵ
			lpDst[dwBuffUsed] = bChar1;	
			// ����dwBuffUsed
			dwBuffUsed ++;
		}
	}
	// д�������
	file.Write((LPSTR)lpDst, dwBuffUsed);
	// �ͷ��ڴ�
	delete[] lpDst;	
	// ����һƬ�������Ա����ɫ��
	lpDst = new BYTE[769];
	// ��ɫ����ʼ�ֽ�
	* lpDst = 0x0C;
	for (i = 0; i < 256; i ++)
	{	
		// ��ȡDIB��ɫ���ɫ����
		lpDst[i * 3 + 1] = i;	
		// ��ȡDIB��ɫ����ɫ����
		lpDst[i * 3 + 2] = i;	
		// ��ȡDIB��ɫ����ɫ����
		lpDst[i * 3 + 3] = i;
	}
	// д���ɫ����Ϣ
	file.Write((LPSTR)lpDst, 769);
	// ����
	return TRUE;
}



typedef struct gifc_var// GIF�������
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
// ������
#define DWORD_WBYTES(x)         ( (((x) + 31UL) >> 5) << 2 )
#define WORD_WBYTES(x)          ( (((x) + 15UL) >> 4) << 1 )
#define BYTE_WBYTES(x)          (  ((x) +  7UL) >> 3       )
/*************************************************************************
* �������ƣ�
 *  WriteCode()
* ����:
 *   CFile& file			- Ҫ������ļ�
 *	 WORD wCode			- Ҫ��ӵı���
 *   LPSTR lpSubBlock		- �ӿ�
 *	 LPBYTE lpbyCurrentBits	- ��ǰλ��
 *	 LPGIFC_VAR lpGIFCVar	- ָ��GIFC_VAR�ṹ��ָ��
* ����ֵ:
 *   ��
* ˵��:
 *   �ú����������һ�����롣
*************************************************************************/
void WriteCode(CFile& file, WORD wCode, LPSTR lpSubBlock,LPBYTE 
lpbyCurrentBits,LPGIFC_VAR lpGIFCVar)
{	
// ����ñ���
	lpGIFCVar->dwTempCode |= ((DWORD)wCode << lpGIFCVar->byLeftBits);
	lpGIFCVar->byLeftBits += (*lpbyCurrentBits);
	while(lpGIFCVar->byLeftBits >= 0x08)
	{
		lpSubBlock[lpGIFCVar->wBlockNdx++] = (BYTE)lpGIFCVar->dwTempCode;
		// �ж��Ƿ񳬳�MAX_SUBBLOCK_SIZE��255
		if (lpGIFCVar->wBlockNdx > 255)
		{
			// �ж�wByteCnt + 256�Ƿ񳬹�MAX_BUFF_SIZE-32768
			if ((lpGIFCVar->wByteCnt + 256) >= 32768)
			{
				// ���
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
	return;												// ����
}

/*************************************************************************
* �������ƣ�
 *   CodingGIFLZW()
* ����:
 *   LPSTR lpDIBBits		- ָ��ԴDIBͼ��ָ��
 *   CFile& file			- Ҫ������ļ�
 *   LPGIFC_VAR lpGIFCVar	- ָ��GIFC_VAR�ṹ��ָ��
 *	 WORD wWidthBytes		- ÿ��ͼ���ֽ���
 *	 BOOL bInterlace		- �Ƿ��ս���ʽ����
* ����ֵ:
 *   ��
* ˵��:
 *   �ú�����ָ��ͼ�����GIF_LZW���롣
*************************************************************************/

void  CodingGIFLZW(LPSTR lpDIBBits, CFile& file, LPGIFC_VAR lpGIFCVar,WORD wWidthBytes, 
				  BOOL bInterlace)
{
	HANDLE hTableNdx;									// �ڴ������
	HANDLE hPrefix;									// �ڴ������
	HANDLE hSuffix;									// �ڴ������
	LPWORD lpwTableNdx;								// ָ���ִ���ָ��
	LPWORD lpwPrefix;									// �����ִ�������������
	LPBYTE lpbySuffix;									// �����ִ�������������
	LPSTR  lpImage;									// ָ��ǰ�������ص�ָ��
	DWORD  dwDataNdx;								// ���㵱ǰ����ͼ���ƫ����
	WORD   wLZW_CLEAR;								// LZW_CLEAR
	WORD   wLZW_EOI;								// LZW_EOI
	BYTE   byLZW_MinCodeLen;							// LZW_MinCodeLen
	WORD   wPreTableNdx;								// �ִ�������
	WORD   wNowTableNdx;								// �ִ�������
	WORD   wTopTableNdx;								// �ִ�������
	WORD   wHashNdx;									// ��ϣ������
	WORD   wHashGap;									// ��ϣ������
	WORD   wPrefix;								
	WORD   wRowNum;								// ��ǰͼ�������
	WORD   wWidthCnt;								// ��ǰͼ�������
	WORD   wi;										// ѭ������
	WORD   wj;									// ѭ������
	WORD   wIncTable[5]  = { 8,8,4,2,0 }; 				// ����ʽ�洢ʱÿ�����ӵ����� 
	WORD   wBgnTable[5]  = { 0,4,2,1,0 }; 				// ����ʽ�洢ʱ��ʼ����
	BOOL   bStart;									// ��ʼ��־
	BYTE   bySuffix;
	BYTE   bySubBlock[256];
	BYTE   byCurrentBits;
	BYTE   byPass;
	BYTE   byTemp;								// ��ʱ�ֽڱ���
	hTableNdx = GlobalAlloc(GHND,(DWORD)(5051<<1));		// ���ִ�������ڴ�
	hPrefix = GlobalAlloc(GHND,(DWORD)(5051<<1));		// ���ִ�������ڴ�
	hSuffix = GlobalAlloc(GHND,(DWORD)5051);			// ���ִ�������ڴ�
	lpwTableNdx = (LPWORD)GlobalLock(hTableNdx);		// �����ڴ�
	lpwPrefix  = (LPWORD)GlobalLock(hPrefix);			// �����ڴ�
	lpbySuffix  = (LPBYTE)GlobalLock(hSuffix);			// �����ڴ�
	// ����LZW_MinCodeLen
	byLZW_MinCodeLen = (BYTE)((lpGIFCVar->wBits>1) ? lpGIFCVar->wBits : 0x02);
	file.Write((LPSTR)&byLZW_MinCodeLen,1);			// дGIF LZW��С�����С
	wRowNum  = 0;								// ��ʼ��
	bStart  = TRUE;								// ��ʼ��
	byPass = 0x00;									// ��ʼ��
	wLZW_CLEAR = 1 << byLZW_MinCodeLen;			// ����LZW_CLEAR
	wLZW_EOI = wLZW_CLEAR + 1;					// ����LZW_EOI
	byCurrentBits = byLZW_MinCodeLen + (BYTE)0x01;		// ��ʼ���ִ���
	wNowTableNdx = wLZW_CLEAR + 2;					// ��ʼ���ִ���
	wTopTableNdx  = 1 << byCurrentBits;					// ��ʼ���ִ���
	for(wi=0; wi<5051; wi++)
	{
		*(lpwTableNdx+wi) = 0xFFFF;					// ��ʼ��Ϊ0xFFFF
	}	
	// ���LZW_CLEAR
	WriteCode(file, wLZW_CLEAR, (LPSTR)bySubBlock,&byCurrentBits, lpGIFCVar);	
	for(wi=0; wi<lpGIFCVar->wDepth; wi++)				// ���б���
	{
		// ���㵱ǰƫ����
		dwDataNdx  = (DWORD)(lpGIFCVar->wDepth - 1 - wRowNum) * (DWORD)wWidthBytes;
		// ָ��ǰ��ͼ���ָ��
		lpImage = (LPSTR) (((BYTE*)lpDIBBits) + dwDataNdx);	
		wWidthCnt = 0;
		if (bStart)
		{
			byTemp = *lpImage++;					// 256ɫͼ��ֱ�Ӹ�ֵ����
			wPrefix    = (WORD)byTemp;
			bStart     = FALSE;
			wWidthCnt ++;
		}
		while(wWidthCnt < lpGIFCVar->wWidth)				// ÿ�б���
		{
			byTemp = *lpImage++;						// 256ɫ��ֱ�Ӹ�ֵ����
			bySuffix   = byTemp;
			wWidthCnt ++;
			// ���ҵ�ǰ�ַ����Ƿ�������ִ�����
			wHashNdx = wPrefix ^ ((WORD)bySuffix << 4);
			wHashGap = (wHashNdx ? (5051 - wHashNdx) : 1);
			while(TRUE)								// �жϵ�ǰ�ַ����Ƿ����ִ�����
			{
				if (*(lpwTableNdx + wHashNdx) == 0xFFFF)		// ��ǰ�ַ��������ִ�����
				{
				   break;								// ���ַ������˳�ѭ��
				}
				// �ж��Ƿ��ҵ����ַ���
				if ((*(lpwPrefix+wHashNdx)  == wPrefix) &&(*(lpbySuffix+wHashNdx) == bySuffix))
				{
					break;							// �ҵ����˳�ѭ��
				}
				if (wHashNdx < wHashGap)					// �ڶ���ϣ��
				{
					wHashNdx += 5051;
				}
				wHashNdx -= wHashGap;
			}
			if (*(lpwTableNdx+wHashNdx) != 0xFFFF)			// �ж��Ƿ������ַ���
			{
				wPrefix = *(lpwTableNdx + wHashNdx);		// �������ַ���
			 }
			 else
			 {
				// ���ַ���������ñ���
				WriteCode(file,wPrefix,(LPSTR)bySubBlock,&byCurrentBits,lpGIFCVar);
				wPreTableNdx = wNowTableNdx;			// �������ַ�����ӵ��ִ�����
				if (wNowTableNdx < 4096)					// �ж��Ƿ�ﵽ����ִ����С
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
					else								// �ִ�������󳤶�
					{
						// ���LZW_CLEAR
						WriteCode(file, wLZW_CLEAR, (LPSTR)bySubBlock,
										 &byCurrentBits,lpGIFCVar);
						// ���³�ʼ���ִ���
						byCurrentBits = byLZW_MinCodeLen + (BYTE)0x01;
						wLZW_CLEAR = 1 << byLZW_MinCodeLen;
						wLZW_EOI = wLZW_CLEAR + 1;
						wNowTableNdx = wLZW_CLEAR + 2;
						wTopTableNdx = 1 << byCurrentBits;
						for(wj=0;wj<5051;wj++)
						{
							*(lpwTableNdx+wj) = 0xFFFF;		// ��ʼ��Ϊ0xFFFF
						}
					}
				}
				wPrefix = (WORD)bySuffix;
			}
		}
		if (bInterlace)										// �ж��Ƿ��ǽ���ʽ
		{
			wRowNum += wIncTable[byPass];					// ����ʽ��������һ��λ��
			if (wRowNum>=lpGIFCVar->wDepth)
			{
				byPass ++;
				wRowNum = wBgnTable[byPass];
			}
		}
		else
		{
			wRowNum ++;									// �ǽ���ʽ��ֱ��������һ	
		}
	}
	// �����ǰ����
	WriteCode(file, wPrefix, (LPSTR)bySubBlock,&byCurrentBits,lpGIFCVar);
	// ���LZW_EOI
	WriteCode(file,wLZW_EOI,(LPSTR)bySubBlock,&byCurrentBits,lpGIFCVar);
	if (lpGIFCVar->byLeftBits)
	{
		// ������ַ�
		bySubBlock[lpGIFCVar->wBlockNdx++] = (BYTE)lpGIFCVar->dwTempCode;
		// �ж��Ƿ񳬳�MAX_SUBBLOCK_SIZE
		if (lpGIFCVar->wBlockNdx > 255)
		{
			// �ж�wByteCnt + 256�Ƿ񳬹�MAX_BUFF_SIZE
			if ((lpGIFCVar->wByteCnt + 256) >= 32768)
			{
				// ���
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
		// �ж�wByteCnt + 256�Ƿ񳬹�MAX_BUFF_SIZE
		if ((lpGIFCVar->wByteCnt + 256) >= 32768)
		{
			// ���
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
	GlobalUnlock(hTableNdx);								// �������
	GlobalUnlock(hPrefix);								// �������
	GlobalUnlock(hSuffix);								// �������
	GlobalFree(hTableNdx);								// �ͷ��ڴ�
	GlobalFree(hPrefix);									// �ͷ��ڴ�
	GlobalFree(hSuffix);									// �ͷ��ڴ�
	return;											// �˳�
}

/*************************************************************************
* �������ƣ�
 *   GIFLZW()
* ����:
 *   LPSTR 	lpDIBBits     		- ָ��DIB�������ݵ�ָ��
 *	 WORD  wWidth		   	- ָ��DIB����ͼ����
 *	 WORD 	wHeight			- ָ��DIB����ͼ��߶�
 *   CFile& file        			- Ҫ������ļ�
 *   BOOL	bInterlace			- �Ƿ��ս���ʽ����
* ����ֵ:
 *   BOOL               - �ɹ�����True�����򷵻�False��
* ˵��:
 *   �ú�����ָ����DIB����256ɫ������ΪGIF�ļ���
*************************************************************************/
BOOL  GIFLZW(LPSTR lpDIBBits,WORD wWidth,WORD wHeight, CFile& file, BOOL bInterlace)
{
	int	i;											// ѭ������
	int	j;											// ѭ������
	typedef struct gifheader								// GIF�ļ�ͷ
   	{
      BYTE bySignature[3];								//GIF����
      BYTE byVersion[3];									//�汾��
   	}  GIFHEADER;
	typedef struct gifscrdesc								// GIF�߼���Ļ������
  	{
      WORD wWidth;									//�߼���Ļ���
      WORD wDepth;									//�߼���Ļ�߶�
      struct globalflag
         {
            BYTE PalBits   : 3;							//ȫ����ɫ�б��С
            BYTE SortFlag  : 1;							//�����־
            BYTE ColorRes  : 3;							//��ɫ���
            BYTE GlobalPal : 1;							//ȫ����ɫ�б��־
         }  GlobalFlag;
      BYTE byBackground;								//����ɫ
      BYTE byAspect;									//���ؿ�߱�
   	}  GIFSCRDESC;
	typedef struct gifimage									// GIFͼ���ʶ��
   	{
      WORD wLeft;										//X����ƫ����
      WORD wTop;										//Y����ƫ����
      WORD wWidth;									//ͼ����
      WORD wDepth;									//ͼ��߶�
      struct localflag
         {
            BYTE PalBits   : 3;							//�ֲ���ɫ�б��С
            BYTE Reserved  : 2;							//�����������ʼ��Ϊ0
            BYTE SortFlag  : 1;							//�����־
            BYTE Interlace : 1;								//��֯��־
            BYTE LocalPal  : 1;							//�ֲ���ɫ�б��־
         }  LocalFlag;
   	}  GIFIMAGE;
	GIFHEADER          GIFH;							// GIF�ļ�ͷ
	GIFSCRDESC         GIFS;							// GIF�߼���Ļ������
	GIFIMAGE           GIFI;							// GIFͼ��������
	GIFC_VAR           GIFCVar;						// GIF�������
	WORD               wColors;						// ��ɫ��Ŀ
	BYTE               byGIF_Pal[768];					// ��ɫ��
	BYTE               byChar;							// �ֽڱ���
	GIFCVar.wWidth     = wWidth;						// ��GIFCVar�ṹ��ֵ
	GIFCVar.wDepth     = wHeight;						// ��GIFCVar�ṹ��ֵ
	GIFCVar.wBits      = 8;								// ��GIFCVar�ṹ��ֵ
	GIFCVar.wLineBytes = (WORD)BYTE_WBYTES((DWORD)GIFCVar.wWidth *(DWORD)GIFCVar.wBits);
	WORD	wWidthBytes;								// ÿ���ֽ���
	wWidthBytes = (WORD)DWORD_WBYTES(wWidth * (DWORD)GIFCVar.wBits);
	wColors     = 256;									//��ɫ��Ŀ
	j = 0;
	for (i = 0; i < wColors; i++)
	{
		byGIF_Pal[j++] = i;								// ���ú�ɫ����
		byGIF_Pal[j++] = i;								// ������ɫ����
		byGIF_Pal[j++] = i;								// ������ɫ����
	}
	
	// ��ʼдGIF�ļ�
	GIFH.bySignature[0] = 'G';								// ����GIF�ļ�ͷ
	GIFH.bySignature[1] = 'I';								// ����GIF�ļ�ͷ
	GIFH.bySignature[2] = 'F';								// ����GIF�ļ�ͷ
	GIFH.byVersion[0]='8';								// ����GIF�ļ�ͷ
	GIFH.byVersion[1]='9';								// ����GIF�ļ�ͷ
	GIFH.byVersion[2]='a';								// ����GIF�ļ�ͷ
	file.Write((LPSTR)&GIFH, 6);							// дGIF�ļ�ͷ
	GIFS.wWidth = GIFCVar.wWidth;						// ����GIF�߼���Ļ���������
	GIFS.wDepth = GIFCVar.wDepth;						// ����GIF�߼���Ļ���������
	GIFS.GlobalFlag.PalBits   = (BYTE)(GIFCVar.wBits - 1);		// ����GIF�߼���Ļ���������
	GIFS.GlobalFlag.SortFlag  = 0x00;						// ����GIF�߼���Ļ���������
	GIFS.GlobalFlag.ColorRes  = (BYTE)(GIFCVar.wBits - 1);		// ����GIF�߼���Ļ���������
	GIFS.GlobalFlag.GlobalPal = 0x01;						// ����GIF�߼���Ļ���������
	GIFS.byBackground = 0x00;								// ����GIF�߼���Ļ���������
	GIFS.byAspect = 0x00;								// ����GIF�߼���Ļ���������
	file.Write((LPSTR)&GIFS, 7);							// дGIF�߼���Ļ������
	file.Write((LPSTR)byGIF_Pal,(wColors*3));					// дGIFȫ�ֵ�ɫ��
	byChar      = 0x2C;
	file.Write((LPSTR)&byChar,1);							// дGIFͼ�����������
	GIFI.wLeft = 0;										// ����GIFͼ�����������
	GIFI.wTop = 0;										// ����GIFͼ�����������
	GIFI.wWidth = GIFCVar.wWidth;						// ����GIFͼ�����������
	GIFI.wDepth = GIFCVar.wDepth;							// ����GIFͼ�����������
	GIFI.LocalFlag.PalBits = 0x00;							// ����GIFͼ�����������
	GIFI.LocalFlag.Reserved = 0x00;							// ����GIFͼ�����������
	GIFI.LocalFlag.SortFlag = 0x00;							// ����GIFͼ�����������
	GIFI.LocalFlag.Interlace = (BYTE)(bInterlace ? 0x01 : 0x00);		// ����GIFͼ�����������
	GIFI.LocalFlag.LocalPal  = 0x00;						// ����GIFͼ�����������
	file.Write((LPSTR)&GIFI, 9);							// дGIFͼ��������
	// дGIFͼ��ѹ������
	HANDLE hSrcBuff = GlobalAlloc(GHND,(DWORD)32768);		// �����ڴ�
	GIFCVar.lpDataBuff = (LPSTR)GlobalLock(hSrcBuff);
	GIFCVar.lpEndBuff  = GIFCVar.lpDataBuff;
	GIFCVar.dwTempCode = 0UL;							// ����GIFͼ��ѹ�����ݲ���
	GIFCVar.wByteCnt   = 0;								// ����GIFͼ��ѹ�����ݲ���
	GIFCVar.wBlockNdx  = 1;								// ����GIFͼ��ѹ�����ݲ���
	GIFCVar.byLeftBits = 0x00;								// ����GIFͼ��ѹ�����ݲ���
	CodingGIFLZW(lpDIBBits, file, &GIFCVar,wWidthBytes, bInterlace); // ����GIF_LZW����
	if (GIFCVar.wByteCnt)								// �ж��Ƿ����ɹ�
	{
		file.Write(GIFCVar.lpDataBuff, GIFCVar.wByteCnt);	// д���ļ�
	}
	GlobalUnlock(hSrcBuff);							// �������
	GlobalFree(hSrcBuff);								// �ͷ��ڴ�
	byChar   = 0x00;
	file.Write((LPSTR)&byChar,1);						// дGIF Block Terminator
	byChar   = 0x3B;
	file.Write((LPSTR)&byChar,1);						// дGIF�ļ���β��
	return TRUE;									// ����
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
 * \�������ƣ�
 *   DWTStep_1D()
 *
 * \�������:
 *   double * pDbSrc		- ָ��Դ���ݵ�ָ��
 *   int nCurLevel		- ��ǰ�ֽ�Ĳ���
 *   int nInv			- �Ƿ�ΪDWT��1��ʾΪIDWT��0��ʾDWT
 *   int nStep			- ��ǰ�ļ������
 *   int nSupp			- С�����Ľ�֧���ĳ���
 *
 * \����ֵ:
 *   BOOL			- �ɹ��򷵻�TRUE�����򷵻�FALSE
 *
 * \˵��:
 *   �ú����öԴ����pDBSrc�е����ݽ���һ���һάDWT����IDWT�����У�nInvΪ��ʾ����
 *   DWT����IDWT�ı�־��nCurLevelΪ��ǰ��Ҫ���зֽ�Ĳ�����nStepΪ�Ѿ��ֽ�Ĳ���
 *   ����������Դ����pDbSrc��
 *
 *************************************************************************
 */
BOOL DWTStep_1D(double* pDbSrc, int nCurLevel,
			int nInv, int nStep,int nSupp)
{
	double s = sqrt(2);
	// ���С������ָ��
	double* h = (double*)hCoef[nSupp-1];
	// ȷ�ϵ�ǰ������Ч
	ASSERT(nCurLevel>=0);

	// ���㵱ǰ�����ĳ���
	int CurN = 1<<nCurLevel;
	if (nInv) CurN <<= 1;

	// ȷ����ѡ���С�����͵�ǰ�����ĳ�����Ч
	if (nSupp<1 || nSupp>10 || CurN<2*nSupp) 
		return FALSE;

	// ������ʱ�ڴ����ڴ�Ž��
	double *ptemp = new double[CurN];
	if (!ptemp) return FALSE;

	double	s1, s2;
	int	Index1, Index2;

	// �ж��ǽ���DWT����IDWT
	if (!nInv)
	{	// DWT
		Index1=0;
		Index2=2*nSupp-1;
		
		// ���о��������s1Ϊ��Ƶ���֣�s2Ϊ��Ƶ���ֵĽ��
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

			// ������������ʱ�ڴ���
			ptemp[i] = s1/s;
			ptemp[i+CurN/2] = s2/s;

			Index1 -= 2*nSupp;
			Index2 += 2*nSupp;
			Index1 += 2;
			Index2 += 2;
		}
	}

	// �������IDWT
	else
	{	// IDWT
		Index1 = CurN/2;
		Index2 = CurN/2-nSupp+1;
		
		// ���о������������s1Ϊ��Ƶ���֣�s2Ϊ��Ƶ���ֵĽ��
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

			// �����������ʱ�ڴ�
			ptemp[2*i] = s1*s;
			ptemp[2*i+1] = s2*s;

			Index1 += nSupp;
			Index2 -= nSupp;
			Index1++;
			Index2++;
		}
	}
	
	// ���������Դͼ����
	for (int i=0; i<CurN; i++)
		pDbSrc[i*nStep] = ptemp[i];

	// �ͷ���ʱ�ڴ棬������
	delete[] ptemp;
	return TRUE;
}

/*************************************************************************
 *
 * \�������ƣ�
 *   DWTStep_2D()
 *
 * \�������:
 *   double * pDbSrc		- ָ��Դ���ݵ�ָ��
 *   int nCurWLevel		- X�����ϵ�ǰ�ֽ�Ĳ���
 *   int nCurHLevel		- Y�����ϵ�ǰ�ֽ�Ĳ���
 *   int nMaxWLevel		- X���������ɷֽ�Ĳ���
 *   int nMaxHLevel		- Y���������ɷֽ�Ĳ���
 *   int nInv			- �Ƿ�ΪDWT��1��ʾΪIDWT��0��ʾDWT
 *   int nStep			- ��ǰ�ļ������
 *   int nSupp			- С�����Ľ�֧���ĳ���
 *
 * \����ֵ:
 *   BOOL			- �ɹ��򷵻�TRUE�����򷵻�FALSE
 *
 * \˵��:
 *   �ú����öԴ����pDBSrc�е����ݽ���һ��Ķ�άDWT����IDWT��
 *   ����������Դ����pDbSrc��
 *
 *************************************************************************
 */
BOOL DWTStep_2D(double* pDbSrc, int nCurWLevel, int nCurHLevel,
		int nMaxWLevel, int nMaxHLevel, int nInv, int nStep, int nSupp)
{
	// ����ͼ��ĳ��ȺͿ�ȣ�2���ݶ��룩
	int W = 1<<nMaxWLevel, H = 1<<nMaxHLevel;

	// ���㵱ǰ�ֽ��ͼ��ĳ��ȺͿ��
	int CurW = 1<<nCurWLevel, CurH = 1<<nCurHLevel;

	// �ж��ǽ���DWT����IDWT
	if (!nInv)
	{	// ���н���һάDWT
		for (int i=0; i<CurH; i++)
			if (!DWTStep_1D(pDbSrc+(int)i*W*nStep, nCurWLevel, nInv, nStep, nSupp)) return FALSE;
		// ���н���һάDWT
		for (int i=0; i<CurW; i++)
			if (!DWTStep_1D(pDbSrc+i*nStep, nCurHLevel, nInv, W*nStep, nSupp)) return FALSE;
	}

	// �������IDWT
	else
	{
		// ���㵱ǰ�任��ͼ��ĳ��ȺͿ��
		CurW <<= 1;
		CurH <<= 1;

		// ���н���IDWT
		for (int i=0; i<CurW; i++)
			if (!DWTStep_1D(pDbSrc+i*nStep, nCurHLevel, nInv, W*nStep, nSupp)) return FALSE;
		// ���н���IDWT
		for (int i=0; i<CurH; i++)
			if (!DWTStep_1D(pDbSrc+(int)i*W*nStep, nCurWLevel, nInv, nStep, nSupp)) return FALSE;
	}

	// ����
	return TRUE;
}


/*************************************************************************
 *
 * \�������ƣ�
 *   FloatToByte()
 *
 * \�������:
 *   double  f			- ����˫���ȱ���
 *
 * \����ֵ:
 *   BYTE			- ���ر����ͱ���
 *
 * \˵��:
 *   �ú����������˫���ȱ���ת��ΪBYTE�͵ı���
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
 * \�������ƣ�
 *   FloatToChar()
 *
 * \�������:
 *   double  f			- ����˫���ȱ���
 *
 * \����ֵ:
 *   Char			- �����ַ�����
 *
 * \˵��:
 *   �ú����������˫���ȱ���ת��ΪChar�͵ı���
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
 * \�������ƣ�
 *   Log2()
 *
 * \�������:
 *   int  n			- �������ͱ���
 *
 * \����ֵ:
 *   int			- ������������Ķ���
 *
 * \˵��:
 *   �ú�����ȡ�����������2Ϊ�׵Ķ�������ת��Ϊ���������
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
	// ѭ������
	int i, j;

	// ��ȡ�任��������
	int nMaxWLevel = Log2(nWidth);
	int nMaxHLevel = Log2(nHeight);
	int nMaxLevel;
	if (nWidth == 1<<nMaxWLevel && nHeight == 1<<nMaxHLevel)
		nMaxLevel = min(nMaxWLevel, nMaxHLevel);

	// ��ʱ����
	double	*pDbTemp;
	BYTE	*pBits;

	// ���С���任�Ĵ洢�ڴ滹û�з��䣬�������ڴ�
	if(!m_pDbImage){			
		m_pDbImage = new double[nWidth*nHeight];
		if (!m_pDbImage)	return FALSE;

		// ��ͼ�����ݷ���m_pDbImage�� 
		for (j=0; j<nHeight; j++)
		{
			pDbTemp = m_pDbImage + j*nWidth;
			pBits = (unsigned char *)lpDIBBits + (nHeight-1-j)*nWidth;		
			for (i=0; i<nWidth; i++)
				pDbTemp[i] = pBits[i];
		}
	}
	
	// ����С���任���򷴱任��
	if (!DWTStep_2D(m_pDbImage, nMaxWLevel-m_nDWTCurDepth, nMaxHLevel-m_nDWTCurDepth,
						nMaxWLevel, nMaxHLevel, nInv, 1, m_nSupp))
		return FALSE;

	// ����Ƿ��任����ǰ������1
	if (nInv)
		m_nDWTCurDepth --;
	// �����1
	else
		m_nDWTCurDepth ++;

	// Ȼ�󣬽����ݿ�����ԭCDib�У���������Ӧ������ת��
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

	// ����
	return TRUE;
}


/////////////////////////////////////////
//------------------λƽ���зֺ���
/*************************************************************************
* �������ƣ�
*   BitPlaneSlicing()
* ����:
*   LPSTR lpDIBBits    - ָ��ԴDIBͼ��ָ��
*   LONG  lWidth       - Դͼ���ȣ���������������4�ı�����
*   LONG  lHeight      - Դͼ��߶ȣ���������
*   LONG  lLineBytes   -ÿ���ֽ���
*   int   Bit    		- �ָ� λ ��0---7��
* ����ֵ:
*   BOOL               - ����ɹ�����TRUE�����򷵻�FALSE��
* ˵��:
* �ú������ڶ�ͼ�����λƽ��ָ8λ
************************************************************************/
BOOL BitPlaneSlicing(LPSTR lpDIBBits, LONG lmageWidth, LONG  lLineBytes, LONG lmageHeight, int Bit)
{
	int i;  //ѭ������
	int j;	//ѭ������
			// ָ��Դͼ���ָ��
	unsigned char*	lpSrc;
	//����ֵ
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

			// ָ��Դͼ������j�У���i�����ص�ָ��			
			//lpSrc = (unsigned char *)lpDIBBits + lmageWidth * j + i;
			lpSrc = (unsigned char *)lpDIBBits + lLineBytes * j + i;
			//ȡ�õ�ǰָ�봦������ֵ
			pixeltemp = (unsigned char)*lpSrc;
			//Ŀ��ͼ���лҶ�ֵС������������Ϊ�ڵ�
			if (pixeltemp >= threshold1 &&pixeltemp < threshold2)
			{
				//*lpSrc = (unsigned char)255;
			}
			else	//��������Ϊ�׵�
			{
				*lpSrc = (unsigned char)0;
			}
		}
	}
	return true;
}






#endif // !defined(AFX_FUNCTION_H__6E194843_FEB3_491F_8062_765AA3465CBC__INCLUDED_)
