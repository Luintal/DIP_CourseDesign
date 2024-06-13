

/**************************************************************************
 *  �ļ�����PointTrans.cpp
 *
 *  ͼ�������API�����⣺
 *
 *  LinerTrans()		- ͼ�����Ա任
 *	WindowTrans()		- ͼ�񴰿ڱ任
 *  GrayStretch()		- ͼ��Ҷ�����
 *  InteEqualize()		��ֱ��ͼ����
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
 * �������ƣ�
 *   LinerTrans()
 *
 * ����:
 *   LPSTR lpDIBBits    - ָ��ԴDIBͼ��ָ��
 *   LONG  lWidth       - Դͼ���ȣ���������
 *   LONG  lHeight      - Դͼ��߶ȣ���������
 *   FLOAT fA		    - ���Ա任��б��
 *   FLOAT fB           - ���Ա任�Ľؾ�
 *
 * ����ֵ:
 *   BOOL               - �ɹ�����TRUE�����򷵻�FALSE��
 *
 * ˵��:
 *   �ú���������ͼ����лҶȵ����Ա任������
 *
 ************************************************************************/

BOOL WINAPI LinerTrans(LPSTR lpDIBBits, LONG lWidth, LONG lHeight, FLOAT fA, FLOAT fB)
{
	
	// ָ��Դͼ���ָ��
	unsigned char*	lpSrc;
	
	// ѭ������
	LONG	i;
	LONG	j;
	
	// ͼ��ÿ�е��ֽ���
	LONG	lLineBytes;
	
	// �м����
	FLOAT	fTemp;
	
	// ����ͼ��ÿ�е��ֽ���
	lLineBytes = WIDTHBYTES(lWidth * 8);
	
	// ÿ��
	for(i = 0; i < lHeight; i++)
	{
		// ÿ��
		for(j = 0; j < lWidth; j++)
		{
			// ָ��DIB��i�У���j�����ص�ָ��
			lpSrc = (unsigned char*)lpDIBBits + lLineBytes * (lHeight - 1 - i) + j;
			
			// ���Ա任
			fTemp = fA * (*lpSrc) + fB;
			
			// �ж��Ƿ񳬳���Χ
			if (fTemp > 255)
			{
				// ֱ�Ӹ�ֵΪ255
				*lpSrc = 255;
			}
			else if (fTemp < 0)
			{
				// ֱ�Ӹ�ֵΪ0
				*lpSrc = 0;
			}
			else
			{
				// ��������
				*lpSrc = (unsigned char) (fTemp + 0.5);
			}
		}
	}
	
	// ����
	return TRUE;

}

/*************************************************************************
 *
 * �������ƣ�
 *   ThresholdTrans()
 *
 * ����:
 *   LPSTR lpDIBBits    - ָ��ԴDIBͼ��ָ��
 *   LONG  lWidth       - Դͼ���ȣ���������
 *   LONG  lHeight      - Դͼ��߶ȣ���������
 *   BYTE  bThre	    - ��ֵ
 *
 * ����ֵ:
 *   BOOL               - �ɹ�����TRUE�����򷵻�FALSE��
 *
 * ˵��:
 *   �ú���������ͼ�������ֵ�任�����ڻҶ�ֵС����ֵ������ֱ������
 * �Ҷ�ֵΪ0���Ҷ�ֵ������ֵ������ֱ������Ϊ255��
 *
 ************************************************************************/
BOOL WINAPI ThresholdTrans(LPSTR lpDIBBits, LONG lWidth, LONG lHeight, BYTE bThre)
{
	
	// ָ��Դͼ���ָ��
	unsigned char*	lpSrc;
	
	// ѭ������
	LONG	i;
	LONG	j;
	
	// ͼ��ÿ�е��ֽ���
	LONG	lLineBytes;
	
	// ����ͼ��ÿ�е��ֽ���
	lLineBytes = WIDTHBYTES(lWidth * 8);
	
	// ÿ��
	for(i = 0; i < lHeight; i++)
	{
		// ÿ��
		for(j = 0; j < lWidth; j++)
		{
			// ָ��DIB��i�У���j�����ص�ָ��
			lpSrc = (unsigned char*)lpDIBBits + lLineBytes * (lHeight - 1 - i) + j;
			
			// �ж��Ƿ�С����ֵ
			if ((*lpSrc) < bThre)
			{
				// ֱ�Ӹ�ֵΪ0
				*lpSrc = 0;
			}
			else
			{
				// ֱ�Ӹ�ֵΪ255
				*lpSrc = 255;
			}
		}
	}
	
	// ����
	return TRUE;
}

/*************************************************************************
 *
 * �������ƣ�
 *   WindowTrans()
 *
 * ����:
 *   LPSTR lpDIBBits    - ָ��ԴDIBͼ��ָ��
 *   LONG  lWidth       - Դͼ���ȣ���������
 *   LONG  lHeight      - Դͼ��߶ȣ���������
 *   BYTE  bLow		    - ��������
 *   BYTE  bUp          - ��������
 *
 * ����ֵ:
 *   BOOL               - �ɹ�����TRUE�����򷵻�FALSE��
 *
 * ˵��:
 *   �ú���������ͼ����д��ڱ任��ֻ���ڴ��ڷ�Χ�ڵĻҶȱ��ֲ��䣬
 * С�����޵�����ֱ�����ûҶ�ֵΪ0���������޵�����ֱ�����ûҶ�ֵΪ255��
 *
 ************************************************************************/
BOOL WINAPI WindowTrans(LPSTR lpDIBBits, LONG lWidth, LONG lHeight, BYTE bLow, BYTE bUp)
{
	
	// ָ��Դͼ���ָ��
	unsigned char*	lpSrc;
	
	// ѭ������
	LONG	i;
	LONG	j;
	
	// ͼ��ÿ�е��ֽ���
	LONG	lLineBytes;
	
	// ����ͼ��ÿ�е��ֽ���
	lLineBytes = WIDTHBYTES(lWidth * 8);
	
	// ÿ��
	for(i = 0; i < lHeight; i++)
	{
		// ÿ��
		for(j = 0; j < lWidth; j++)
		{
			// ָ��DIB��i�У���j�����ص�ָ��
			lpSrc = (unsigned char*)lpDIBBits + lLineBytes * (lHeight - 1 - i) + j;
			
			// �ж��Ƿ񳬳���Χ
			if ((*lpSrc) < bLow)
			{
				// ֱ�Ӹ�ֵΪ0
				*lpSrc = 0;
			}
			else if ((*lpSrc) > bUp)
			{
				// ֱ�Ӹ�ֵΪ255
				*lpSrc = 255;
			}
		}
	}
	
	// ����
	return TRUE;
}

/*************************************************************************
 *
 * �������ƣ�
 *   GrayStretch()
 *
 * ����:
 *   LPSTR lpDIBBits    - ָ��ԴDIBͼ��ָ��
 *   LONG  lWidth       - Դͼ���ȣ���������
 *   LONG  lHeight      - Դͼ��߶ȣ���������
 *   BYTE bX1			- �Ҷ������һ�����X����
 *   BYTE bY1			- �Ҷ������һ�����Y����
 *   BYTE bX2			- �Ҷ�����ڶ������X����
 *   BYTE bY2			- �Ҷ�����ڶ������Y����
 *
 * ����ֵ:
 *   BOOL               - �ɹ�����TRUE�����򷵻�FALSE��
 *
 * ˵��:
 *   �ú���������ͼ����лҶ����졣
 *
 ************************************************************************/
BOOL WINAPI GrayStretch(LPSTR lpDIBBits, LONG lWidth, LONG lHeight, BYTE bX1, BYTE bY1, BYTE bX2, BYTE bY2)
{
	
	// ָ��Դͼ���ָ��
	unsigned char*	lpSrc;
	
	// ѭ������
	LONG	i;
	LONG	j;
	
	// �Ҷ�ӳ���
	BYTE	bMap[256];
	
	// ͼ��ÿ�е��ֽ���
	LONG	lLineBytes;
	
	// ����ͼ��ÿ�е��ֽ���
	lLineBytes = WIDTHBYTES(lWidth * 8);
	
	// ����Ҷ�ӳ���
	for (i = 0; i <= bX1; i++)
	{
		// �ж�bX1�Ƿ����0����ֹ��ĸΪ0��
		if (bX1 > 0)
		{
			// ���Ա任
			bMap[i] = (BYTE) bY1 * i / bX1;
		}
		else
		{
			// ֱ�Ӹ�ֵΪ0
			bMap[i] = 0;
		}
	}
	for (; i <= bX2; i++)
	{
		// �ж�bX1�Ƿ����bX2����ֹ��ĸΪ0��
		if (bX2 != bX1)
		{
			// ���Ա任
			bMap[i] = bY1 + (BYTE) ((bY2 - bY1) * (i - bX1) / (bX2 - bX1));
		}
		else
		{
			// ֱ�Ӹ�ֵΪbY1
			bMap[i] = bY1;
		}
	}
	for (; i < 256; i++)
	{
		// �ж�bX2�Ƿ����255����ֹ��ĸΪ0��
		if (bX2 != 255)
		{
			// ���Ա任
			bMap[i] = bY2 + (BYTE) ((255 - bY2) * (i - bX2) / (255 - bX2));
		}
		else
		{
			// ֱ�Ӹ�ֵΪ255
			bMap[i] = 255;
		}
	}
	
	// ÿ��
	for(i = 0; i < lHeight; i++)
	{
		// ÿ��
		for(j = 0; j < lWidth; j++)
		{
			// ָ��DIB��i�У���j�����ص�ָ��
			lpSrc = (unsigned char*)lpDIBBits + lLineBytes * (lHeight - 1 - i) + j;
			
			// �����µĻҶ�ֵ
			*lpSrc = bMap[*lpSrc];
		}
	}
	
	// ����
	return TRUE;
}

/*************************************************************************
 *
 * �������ƣ�
 *   InteEqualize()
 *
 * ����:
 *   LPSTR lpDIBBits    - ָ��ԴDIBͼ��ָ��
 *   LONG  lWidth       - Դͼ���ȣ���������
 *   LONG  lHeight      - Դͼ��߶ȣ���������
 *
 * ����ֵ:
 *   BOOL               - �ɹ�����TRUE�����򷵻�FALSE��
 *
 * ˵��:
 *   �ú���������ͼ�����ֱ��ͼ���⡣
 *
 ************************************************************************/
BOOL WINAPI InteEqualize(LPSTR lpDIBBits, LONG lWidth, LONG lHeight)
{
	
	// ָ��Դͼ���ָ��
	unsigned char*	lpSrc;
	
	// ��ʱ����
	LONG	lTemp;
	
	// ѭ������
	LONG	i;
	LONG	j;
	
	// �Ҷ�ӳ���
	BYTE	bMap[256];
	
	// �Ҷ�ӳ���
	LONG	lCount[256];
	
	// ͼ��ÿ�е��ֽ���
	LONG	lLineBytes;
	
	// ����ͼ��ÿ�е��ֽ���
	lLineBytes = WIDTHBYTES(lWidth * 8);
	
	// ���ü���Ϊ0
	for (i = 0; i < 256; i ++)
	{
		// ����
		lCount[i] = 0;
	}
	
	// ��������Ҷ�ֵ�ļ���
	for (i = 0; i < lHeight; i ++)
	{
		for (j = 0; j < lWidth; j ++)
		{
			lpSrc = (unsigned char *)lpDIBBits + lLineBytes * i + j;
			
			// ������1
			lCount[*(lpSrc)]++;
		}
	}
	
	// ����Ҷ�ӳ���
	for (i = 0; i < 256; i++)
	{
		// ��ʼΪ0
		lTemp = 0;
		
		for (j = 0; j <= i ; j++)
		{
			lTemp += lCount[j];
		}
		
		// �����Ӧ���»Ҷ�ֵ
		bMap[i] = (BYTE) (lTemp * 255 / lHeight / lWidth);
	}
	
	// ÿ��
	for(i = 0; i < lHeight; i++)
	{
		// ÿ��
		for(j = 0; j < lWidth; j++)
		{
			// ָ��DIB��i�У���j�����ص�ָ��
			lpSrc = (unsigned char*)lpDIBBits + lLineBytes * (lHeight - 1 - i) + j;
			
			// �����µĻҶ�ֵ
			*lpSrc = bMap[*lpSrc];
		}
	}
	
	// ����
	return TRUE;
}
/*************************************************************************
 *
 * �������ƣ�
 *   Segmental2_Linear_Tran()
 *  �ֶ����Ա任
 * ����:
 *   LPSTR lpDIBBits    - ָ��ԴDIBͼ��ָ��
 *   LONG  lWidth       - Դͼ���ȣ���������
 *   LONG  lHeight      - Դͼ��߶ȣ���������
 *   int type - �任���ͣ�1����V���ͣ�2��V���ͣ�3����L�ͣ�4-L�ͣ�
 *   int threshold      -��ֵ
 * ����ֵ:
 *   BOOL               - �ɹ�����TRUE�����򷵻�FALSE��
 *
 * ˵��:
 *   �ú���������ͼ����зֶ����Ա任��
 *
 ************************************************************************/
BOOL WINAPI Segmental2_Linear_Tran(LPSTR lpDIBBits, LONG lWidth, LONG lHeight,  int type,int threshold)
{
	// ָ��Դͼ���ָ��
	unsigned char*	lpSrc;
	
	// ѭ������
	LONG	i;
	LONG	j;
	
	// ͼ��ÿ�е��ֽ���
	LONG	lLineBytes;
	
	// �м����
	FLOAT	fTemp=127.0,fA1=1,fB1=0,fA2=1,fB2=0;
	//�м�Ҷ�
	int seg_gray= threshold;

	// ����ͼ��ÿ�е��ֽ���
	lLineBytes = WIDTHBYTES(lWidth * 8);
	//�������Ա任�Ĳ���
	if (type == 1) // ��V����
	{
		fA1 = (float)(255.0 / (float)threshold); // Ӧ��Ϊ2.0����� threshold == 127
		fB1 = 0.0;  // (2f)

		fA2 = -(float)(255.0 / (255.0 - (float)threshold)); // Ӧ��Ϊ-2.0����� threshold == 127
		fB2 = (float)(255.0 + (-255.0 * (float)threshold) / (255.0 - (float)threshold)); // (-2f + 255) ����� threshold == 127

		// ������Ϣ������ע�͵�
		/*
		CString string1, string2;
		string1.Format(L"%d,%f,%f", threshold, fA1, fB1); // ��������װ���ַ�����
		MessageBox(NULL, string1, L"��ֵ��б��1���ؾ�1", MB_OK);

		string2.Format(L"%d,%f,%f", threshold, fA2, fB2); // ��������װ���ַ�����
		MessageBox(NULL, string2, L"��ֵ��б��2���ؾ�2", MB_OK);
		*/
	}

	if(type==2)//V����
	{
		fA1 = -255.0f / threshold;
		fB1 = 255.0f;
		fA2 = 255.0f / (255 - threshold);
		fB2 = -fA2 * threshold;
	}
	if(type==3)//��L����
	{
		fA1 = 255.0f / threshold;
		fB1 = 0.0f;
		fA2 = 0.0f;
		fB2 = 255.0f;
	}
	if(type==4)//L����   ���ע�⣬��ֵ���������⣡����//2024.4.8�Ѹ���
	{
		fA1 = -255.0f / threshold;
		fB1 = 255.0f;
		fA2 = 0.0f;
		fB2 = 0.0f;
	}
	// ÿ��
	for(i = 0; i < lHeight; i++)
	{
		// ÿ��
		for(j = 0; j < lWidth; j++)
		{
			// ָ��DIB��i�У���j�����ص�ָ��
			lpSrc = (unsigned char*)lpDIBBits + lLineBytes * (lHeight - 1 - i) + j;
			
			// ���Ա任,�ֶ�
			if(*lpSrc>=0 && *lpSrc<=seg_gray)
				fTemp = fA1 * (float)(*lpSrc) + fB1;
			if(*lpSrc>=seg_gray+1 &&(float) (*lpSrc)<=255)
				fTemp = fA2 * (float)(*lpSrc) + fB2;
			
			// �ж��Ƿ񳬳���Χ
			if (fTemp > 255)
			{
				// ֱ�Ӹ�ֵΪ255
				*lpSrc = 255;
			}
			else if (fTemp < 0)
			{
				// ֱ�Ӹ�ֵΪ0
				*lpSrc = 0;
			}
			else
			{
				// ��������
				*lpSrc = (unsigned char) (fTemp + 0.5);
			}
		}
	}
	
	// ����
	return TRUE;


}

 /*************************************************************************
 *
 * �������ƣ�
 *   LinerTrans24()
 *
 * ����:
 *   LPSTR lpDIBBits    - ָ��ԴDIBͼ��ָ��
 *   LONG  lWidth       - Դͼ���ȣ���������
 *   LONG  lHeight      - Դͼ��߶ȣ���������
 *   FLOAT fA		    - ���Ա任��б��
 *   FLOAT fB           - ���Ա任�Ľؾ�
 *
 * ����ֵ:
 *   BOOL               - �ɹ�����TRUE�����򷵻�FALSE��
 *
 * ˵��:
 *   �ú���������ͼ����лҶȵ����Ա任������24λ
 *
 ************************************************************************/

BOOL WINAPI LinerTrans24(LPSTR lpDIBBits, LONG lWidth, LONG lHeight, FLOAT fA, FLOAT fB)
{
	
	// ָ��Դͼ���ָ��
	unsigned char*	lpSrc;	
	// ѭ������
	LONG	i;
	LONG	j;	
	// ͼ��ÿ�е��ֽ���
	LONG	lLineBytes;	
	// �м����
	FLOAT	fTemp;	
	// ����ͼ��ÿ�е��ֽ���
	lLineBytes = WIDTHBYTES(lWidth * 24);	
	// ÿ��
	for(i = 0; i < lHeight; i++)
	{
		// ÿ��
		for(j = 0; j < lWidth; j++)
		{
			// ָ��DIB��i�У���j�����ص�ָ��
			//lpSrc = (unsigned char*)lpDIBBits + lLineBytes * (lHeight - 1 - i) + j*3;			
			lpSrc = (unsigned char*)lpDIBBits + lLineBytes * i + j*3;			
			// ���Ա任
			fTemp =float( fA * (*lpSrc) + fB);			
			// �ж��Ƿ񳬳���Χ
			if (fTemp > 255)
			{
				// ֱ�Ӹ�ֵΪ255
				*lpSrc = 255;
			}
			else if (fTemp < 0)
			{
				// ֱ�Ӹ�ֵΪ0
				*lpSrc = 0;
			}
			else
			{
				// ��������
				*lpSrc = (unsigned char) (fTemp + 0.5);
			}
			
			// ָ��DIB��i�У���j�����ص�ָ��
			lpSrc = (unsigned char*)lpDIBBits + lLineBytes * i + j*3+1;			
			// ���Ա任
			fTemp = float( fA * (*lpSrc) + fB);			
			// �ж��Ƿ񳬳���Χ
			if (fTemp > 255)
			{
				// ֱ�Ӹ�ֵΪ255
				*lpSrc = 255;
			}
			else if (fTemp < 0)
			{
				// ֱ�Ӹ�ֵΪ0
				*lpSrc = 0;
			}
			else
			{
				// ��������
				*lpSrc = (unsigned char) (fTemp + 0.5);
			}

			// ָ��DIB��i�У���j�����ص�ָ��
			lpSrc = (unsigned char*)lpDIBBits + lLineBytes * i + j*3+2;			
			// ���Ա任
			fTemp =float(  fA * (*lpSrc) + fB);			
			// �ж��Ƿ񳬳���Χ
			if (fTemp > 255)
			{
				// ֱ�Ӹ�ֵΪ255
				*lpSrc = 255;
			}
			else if (fTemp < 0)
			{
				// ֱ�Ӹ�ֵΪ0
				*lpSrc = 0;
			}
			else
			{
				// ��������
				*lpSrc = (unsigned char) (fTemp + 0.5);
			}
			
		}
	}
	
	// ����
	return TRUE;

}
/*************************************************************************
*
* �������ƣ�
*   If8Color()
*
* ����:
*   LPSTR lpDib        -ָ��ԴDIBָ��
*   LPSTR lpDIBBits    - ָ��ԴDIBͼ��ָ��
*   LONG  lWidth       - Դͼ���ȣ���������
*   LONG  lHeight      - Դͼ��߶ȣ���������
*   
*   int BitCount       -ͼ��λ��
*
* ����ֵ:
*   BOOL               - �ɹ�����TRUE�����򷵻�FALSE��
*
* ˵��:
*   �ú���������8λ��ɫ�ı�����,�ı��ɫ��İ취
*
************************************************************************/
BOOL WINAPI If8Gray(LPSTR lpDib, int BitCount)
{
	// ָ��Դͼ���ָ��
	unsigned char* lpSrc;
	// ѭ������
	LONG	i;
	LONG	j;
	int r, g, b;
	int grayflag = 1;//�Ƿ�Ҷ�
	// ͼ��ÿ�е��ֽ���
	LONG	lLineBytes;

	// ����ͼ��ÿ�е��ֽ���
	//lLineBytes = WIDTHBYTES(lWidth * 8);

	RGBQUAD* pTable, * pTable1;//��ɫ��ָ��
	if (BitCount != 8) return false;
	pTable = (RGBQUAD*)(lpDib + sizeof(BITMAPINFOHEADER));
	pTable1 = pTable;
	for (i = 0; i < 256; i++)//������ɫ�� 
	{
		r = pTable->rgbRed;
		g = pTable->rgbGreen;
		b = pTable->rgbBlue;
		if (r != g || r != b || g != b)
		{
			grayflag = 0; //��ɫ
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
* �������ƣ�
*   8ColorAdd()
*
* ����:
*   LPSTR lpDib        -ָ��ԴDIBָ��
*   LPSTR lpDIBBits    - ָ��ԴDIBͼ��ָ��
*   LONG  lWidth       - Դͼ���ȣ���������
*   LONG  lHeight      - Դͼ��߶ȣ���������
*   int offset         - �仯ֵ
*   int BitCount       -ͼ��λ��
*
* ����ֵ:
*   BOOL               - �ɹ�����TRUE�����򷵻�FALSE��
*
* ˵��:
*   �ú���������8λ��ɫ�ı�����,�ı��ɫ��İ취
*
************************************************************************/
BOOL WINAPI Color8Add(LPSTR lpDib,LPSTR lpDIBBits, int BitCount, LONG lWidth, LONG lHeight, int offset)
{
	// ָ��Դͼ���ָ��
	unsigned char* lpSrc;
	// ѭ������
	LONG	i;
	LONG	j;
	int r, g, b;
	//int grayflag = 1;//�Ƿ�Ҷ�
	// ͼ��ÿ�е��ֽ���
	//LONG	lLineBytes;

	// ����ͼ��ÿ�е��ֽ���
	//lLineBytes = WIDTHBYTES(lWidth * 8);

	RGBQUAD* pTable, * pTable1;//��ɫ��ָ��

	pTable = (RGBQUAD*)(lpDib + sizeof(BITMAPINFOHEADER));
	pTable1 = pTable;
	if (BitCount != 8) return false;
	if (!If8Gray(lpDib, BitCount))
	{
		pTable = pTable1;
		for (i = 0; i < 256; i++)//������ɫ�� 
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
* �������ƣ�
*   8ColorAdd_HSI()
*
* ����:
*   LPSTR lpDib        -ָ��ԴDIBָ��
*   LPSTR lpDIBBits    - ָ��ԴDIBͼ��ָ��
*   LONG  lWidth       - Դͼ���ȣ���������
*   LONG  lHeight      - Դͼ��߶ȣ���������
*   int offset         - �仯ֵ
*   int BitCount       -ͼ��λ��
*
* ����ֵ:
*   BOOL               - �ɹ�����TRUE�����򷵻�FALSE��
*
* ˵��:
*   �ú���������8λ��ɫ�ı�����,�ı��ɫ��İ취,�м�ʹ��HSI��ɫģ��
*
************************************************************************/
BOOL WINAPI Color8Add_HSI(LPSTR lpDib, LPSTR lpDIBBits, int BitCount, LONG lWidth, LONG lHeight, int offset)
{
	// ָ��Դͼ���ָ��
	unsigned char* lpSrc;
	// ѭ������
	LONG	i;
	LONG	j;
	int r,r_old, g, g_old,b,b_old;
	double H, S, I,theta;//ɫ�������Ͷȣ�����,�Ƕ�(����)
	BOOL white=false, black=false;//��ɫ����ɫ
	int degree;//�Ƕ�
	//int grayflag = 1;//�Ƿ�Ҷ�
	// ͼ��ÿ�е��ֽ���
	//LONG	lLineBytes;

	// ����ͼ��ÿ�е��ֽ���
	//lLineBytes = WIDTHBYTES(lWidth * 8);

	RGBQUAD* pTable, * pTable1;//��ɫ��ָ��

	pTable = (RGBQUAD*)(lpDib + sizeof(BITMAPINFOHEADER));
	pTable1 = pTable;
	if (BitCount != 8) return false;

	if (!If8Gray(lpDib, BitCount))
	{
		pTable = pTable1;
		for (i = 0; i < 256; i++)//������ɫ�� 
		{
			r = pTable->rgbRed;
			g = pTable->rgbGreen;
			b = pTable->rgbBlue;
			r_old = pTable->rgbRed;
			g_old = pTable->rgbGreen;
			b_old = pTable->rgbBlue;
			//RGB ת��ΪHSI
			I = ((double)r + (double)g + (double)b) / 3.0 ;
			H = 1234.0;//��ֵ
			S = 1234.0;//��ֵ
			if (r == 255 && g == 255 && b == 255)
			{
				H = 0; S = 0; white = true; black=false;
				
			}
			if (r == 0 && g == 0 && b == 0)
			{
				H = 0; S = 0; black = true; white = false;
			}
			if (I > 0 && I < 255)S = 1.0 - 3.0 * min(r, min(g, b)) / ((double)r + (double)g + (double)b);//���Ͷ�
			if (I > 0 && I < 255)
			{
				theta = acos(0.5 * (((double)r - (double)g) + ((double)r - (double)b)) / sqrt(((double)r - (double)g) * ((double)r - (double)g) + ((double)r - (double)b) * ((double)g - (double)b)));
				if (b <= g) H = theta;
				else H = 2 * PI - theta;
			}

			degree = (int)(180.0 / PI * H);
			I = ((double)r + (double)g + (double)b) / 3.0 + (double)offset;//���ȸı�
			if (I < 0) I = 0;
			if (I > 255) I = 255;
			//HSI ת��ΪRGB
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
			
			//����д�ص�ɫ��
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
 * �������ƣ�
 *   ChangeGray()
 *
 * ����:
 *   LPSTR lpDIBBits    - ָ��ԴDIBͼ��ָ��
 *   LONG  lWidth       - Դͼ���ȣ���������
 *   LONG  lHeight      - Դͼ��߶ȣ���������
 *   int offset         - �仯ֵ
 *   int BitCount       -ͼ��λ��
 *
 * ����ֵ:
 *   BOOL               - �ɹ�����TRUE�����򷵻�FALSE��
 *
 * ˵��:
 *   �ú���������ͼ������Ƚ��иı�
 *
 ************************************************************************/
 BOOL WINAPI ChangeGray(LPSTR lpDIBBits, int BitCount,LONG lWidth, LONG lHeight,int offset)
 {
	  // ָ��Դͼ���ָ��
	unsigned char*	lpSrc;	
	// ѭ������
	LONG	i;
	LONG	j;	
	// ͼ��ÿ�е��ֽ���
	LONG	lLineBytes;	
	int temp,k;
	// ����ͼ��ÿ�е��ֽ���
	lLineBytes = WIDTHBYTES(lWidth * BitCount);
	int page = 1;
	if(BitCount==24) page=3;
	if(BitCount==8) page=1;
	
	 //����ɨ��
	for(i = 0; i < lHeight; i++)
	{
	//����ɨ��
		for(j = 0; j < lWidth; j++)
		{
		// ָ��DIB��i�У���j�����ص�ָ��
			for (k=0;k<page;k++)
			{
				lpSrc = (unsigned char*)lpDIBBits + lLineBytes * (lHeight - 1 - i) + j*page+k;
				// �任
				temp=*lpSrc + offset;
				if (temp > 255)
				{
					// ֱ�Ӹ�ֵΪ255
					*lpSrc = 255;
				}
				else if (temp < 0)
				{
					// ֱ�Ӹ�ֵΪ0
					*lpSrc = 0;
				}
				else
				{
					// ��������
					*lpSrc = (unsigned char) (temp + 0.5);
				}
			
			}
		}
	}
	return true;
 }
 
 /*************************************************************************
 *
 * �������ƣ�
 *   Tran24ColTo24Gray()
 *
 * ����:
 *   LPSTR lpDIBBits    - ָ��ԴDIBͼ��ָ��
 *   LONG  lWidth       - Դͼ���ȣ���������
 *   LONG  lHeight      - Դͼ��߶ȣ���������
 *   
 *   
 *
 * ����ֵ:
 *   BOOL               - �ɹ�����TRUE�����򷵻�FALSE��
 *
 * ˵��:
 *   �ú���������ͼ����б任��24λ��ɫTO24λ�Ҷ�
 *
 ************************************************************************/
 BOOL WINAPI Tran24ColTo24Gray(LPSTR lpDIBBits, LONG lWidth, LONG lHeight)
 {
	 // ָ��Դͼ���ָ��
	unsigned char*	lpSrc;	
	// ѭ������
	LONG	i;
	LONG	j;	
	// ͼ��ÿ�е��ֽ���
	LONG	lLineBytes;	
	
	// ����ͼ��ÿ�е��ֽ���
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
 * �������ƣ�
 *   Tran8ColTo8Gray()
 *
 * ����:
 *   LPSTR lpDIB        - ָ��ԴDIBͼ��ָ��
 *   LPSTR lpDIBBits    - ָ��ԴDIBͼ������ָ��
 *   LONG  lWidth       - Դͼ���ȣ���������
 *   LONG  lHeight      - Դͼ��߶ȣ���������
 *   
 *   
 *
 * ����ֵ:
 *   BOOL               - �ɹ�����TRUE�����򷵻�FALSE��
 *
 * ˵��:
 *   �ú���������ͼ����б任��8λ��ɫTO8λ�Ҷ�
 *
 ************************************************************************/
 BOOL WINAPI Tran8ColTo8Gray(LPSTR lpDIB,LPSTR lpDIBBits, LONG lWidth, LONG lHeight)
 {
	  // ָ��Դͼ���ָ��
	unsigned char*	lpSrc;	
	// ѭ������
	LONG	i;
	LONG	j;	
	// ͼ��ÿ�е��ֽ���
	LONG	lLineBytes;	
	
	// ����ͼ��ÿ�е��ֽ���
	lLineBytes = WIDTHBYTES(lWidth * 8);	
	
	// �Ҷ�ӳ���
	BYTE bMap[256];				
	RGBQUAD *pTable,*pTable1;//��ɫ��ָ��

	pTable=(RGBQUAD*)(lpDIB+sizeof(BITMAPINFOHEADER));
	for (i=0;i<256;i++)//�����µĵ�ɫ��,��ת���Ҷ�
	{
	// �������ɫ��Ӧ�ĻҶ�ֵg=0.299*r+0.587*g+0.114*b	
		bMap[i] = (BYTE)(0.299 * pTable->rgbRed + 0.587 * pTable->rgbGreen + 0.114 * pTable->rgbBlue + 0.5);		
		pTable->rgbRed=(BYTE)i;
		pTable->rgbGreen=(BYTE)i;
		pTable->rgbBlue=(BYTE)i;
		pTable->rgbReserved=(BYTE)0;	
		pTable++;
	}	
	// ����ÿ�����ص���ɫ�����������ջҶ�ӳ����ɻҶ�ֵ��
	//����ɨ��
	for(i = 0; i < lHeight; i++)
	{
	//����ɨ��
		for(j = 0; j < lWidth; j++)
		{
		// ָ��DIB��i�У���j�����ص�ָ��
			lpSrc = (unsigned char*)lpDIBBits + lLineBytes * (lHeight - 1 - i) + j;
			// �任
			*lpSrc =bMap[*lpSrc];
		}
	}

	return true;
 }
 /*************************************************************************
 *
 * �������ƣ�
 *   Tran24ColTo8Gray()
 *
 * ����:
 *	 LPSTR lpDIB        - ָ��ԴDIBͼ��ָ��
 *   LPSTR lpDIBBits    - ָ��ԴDIBͼ������ָ��
 *   LONG  lWidth       - Դͼ���ȣ���������
 *   LONG  lHeight      - Դͼ��߶ȣ���������
 *   
 *   
 *
 * ����ֵ:
 *   BOOL               - �ɹ�����TRUE�����򷵻�FALSE��
 *
 * ˵��:
 *   �ú���������ͼ����б任��24λ��ɫTO8λ�Ҷ�
 *
 ************************************************************************/
 BOOL WINAPI Tran24ColTo8Gray(LPSTR lpDIB,LPSTR lpDIBBits, LONG lWidth, LONG lHeight)
 {
	 // ָ��Դͼ���ָ��
	unsigned char*	lpSrc;	
	// ѭ������
	LONG	i;
	LONG	j;	
	// ͼ��ÿ�е��ֽ���
	LONG	lLineBytes;		
	// ����ͼ��ÿ�е��ֽ���
	lLineBytes = WIDTHBYTES(lWidth * 24);	
	BITMAPINFOHEADER *pHead;
	RGBQUAD* pColorTable;
	int lineByteNew;
	int biBitCount=8;
	lineByteNew=(lWidth * biBitCount/8+3)/4*4; 
	//����λͼ��������Ҫ�Ŀռ䣬��λͼ���ݽ��ڴ�
	unsigned char *pBmpBufNew;
	pBmpBufNew=new unsigned char[lineByteNew * lHeight + sizeof(BITMAPINFOHEADER) + 256*4];//������ͼ��Ŀռ�
	memcpy(pBmpBufNew,(unsigned char *)lpDIB,sizeof(BITMAPINFOHEADER));//��Ϣͷ����
	pHead=(BITMAPINFOHEADER *)pBmpBufNew;
	pHead->biBitCount=8;//�ı�λ��,
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
	//�Ҷ�ͼ������ɫ������ɫ�����Ϊ
	if(biBitCount==8){
	//������ɫ������Ҫ�Ŀռ䣬����ɫ��ֵ
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
	//����ɨ��
	for(i = 0; i < lHeight; i++)
	{
	//����ɨ��
		for(j = 0; j < lWidth; j++)
		{
		// ָ��DIB��i�У���j�����ص�ָ��
			lpSrc = (unsigned char*)lpDIBBits + lLineBytes * (lHeight - 1 - i) + j*3;
			Blue = *lpSrc;
			Green=*(++lpSrc);
			Red=*(++lpSrc);
			Gray= (BYTE)(0.299 * Red + 0.587 * Green + 0.114 * Blue + 0.5);
			// �任
			lpSrc= (unsigned char*)(pBmpBufNew+offset) + lineByteNew * (lHeight - 1 - i) + j;
			*lpSrc =Gray;					
		}
	}
			//����
	memcpy(lpDIB,pBmpBufNew,lineByteNew * lHeight+ sizeof(BITMAPINFOHEADER) + 256*4);

	delete []pBmpBufNew;

	return true;
 }
 /*************************************************************************
 *
 * �������ƣ�
 *   Tran24ColTo8Col()
 *
 * ����:
 *	 LPSTR lpDIB        - ָ��ԴDIBͼ��ָ��
 *   LPSTR lpDIBBits    - ָ��ԴDIBͼ������ָ��
 *   LONG  lWidth       - Դͼ���ȣ���������
 *   LONG  lHeight      - Դͼ��߶ȣ���������
 *   
 *   
 *
 * ����ֵ:
 *   BOOL               - �ɹ�����TRUE�����򷵻�FALSE��
 *
 * ˵��:
 *   �ú���������ͼ����б任��24λ��ɫTO8λ��ɫ
 *
 ************************************************************************/
 BOOL WINAPI  Tran24ColTo8Col(LPSTR lpDIB,LPSTR lpDIBBits, LONG lWidth, LONG lHeight)
 {
	 // ָ��Դͼ���ָ��
	unsigned char*	lpSrc;	
	// ѭ������
	LONG	i;
	LONG	j;	
	// ͼ��ÿ�е��ֽ���
	LONG	lLineBytes;		
	// ����ͼ��ÿ�е��ֽ���
	lLineBytes = WIDTHBYTES(lWidth * 24);	
	BITMAPINFOHEADER *pHead;
	RGBQUAD* pColorTable=NULL;
	int lineByteNew;
	int biBitCount=8;
	lineByteNew=(lWidth * biBitCount/8+3)/4*4; 
	//�Ҷ�ͼ������ɫ������ɫ�����Ϊ
	if(biBitCount==8){
		//������ɫ������Ҫ�Ŀռ䣬����ɫ��ֵ
		pColorTable=new RGBQUAD[256];
 		memset(pColorTable, 0, sizeof(RGBQUAD)*256);  
	} 	  
	BYTE* Index = new BYTE[lineByteNew*lHeight]; //ͼ��������������(������Index��)
	WORD* shortColor = new WORD[lineByteNew*lHeight]; //��ɫ�ĸ�4λ
	memset(shortColor, 0, sizeof(WORD)*lineByteNew*lHeight); //����

	int iRed, iGreen, iBlue;  
	for (int i = 0; i < lHeight; i++)  
	{//ȡRGB��ɫ�ĸ�4λ  
		for(int j=0;j<lWidth;j++)
		{
			lpSrc = (unsigned char*)lpDIBBits + lLineBytes * (lHeight - 1 - i) + j*3;
			iBlue = (*lpSrc)>>4;
			iGreen=(*(++lpSrc))>>4;
			iRed=(*(++lpSrc))>>4;						
			shortColor[lineByteNew * (lHeight - 1 - i) + j] =(iBlue<<8) + (iGreen<<4) + iRed ;  					
		}
	} 
	//����ת������  24color To->8color
    Transfer(shortColor, lineByteNew*lHeight, Index, pColorTable);  

	//����λͼ��������Ҫ�Ŀռ䣬��λͼ���ݽ��ڴ�
	unsigned char *pBmpBufNew;
	pBmpBufNew=new unsigned char[sizeof(BITMAPINFOHEADER) + 256*4];//������ͼ��Ŀռ�
	memcpy(pBmpBufNew,(unsigned char *)lpDIB,sizeof(BITMAPINFOHEADER));//��Ϣͷ����
	pHead=(BITMAPINFOHEADER *)pBmpBufNew;
	pHead->biBitCount=8;//�ı�λ��,
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

	//����
	memcpy(lpDIB,pBmpBufNew, sizeof(BITMAPINFOHEADER));
	memcpy(lpDIB+sizeof(BITMAPINFOHEADER),pColorTable, sizeof(RGBQUAD)*256);
	memcpy(lpDIB+sizeof(BITMAPINFOHEADER)+sizeof(RGBQUAD)*256,Index,lineByteNew*lHeight);

	delete []Index;
	delete []shortColor;

	return true;
 }
 /*************************************************************************
 *
 * �������ƣ�
 *   RGB2HSI()
 *
 * ����:
 *	 LPSTR lH_data        - ָ��Ŀ��ָ���
 *   LPSTR lpDIBBits    - ָ��ԴDIBͼ������ָ��
 *   LONG  lWidth       - Դͼ���ȣ���������
 *   LONG  lHeight      - Դͼ��߶ȣ���������
 *   
 *   
 *
 * ����ֵ:
 *   BOOL               - �ɹ�����TRUE�����򷵻�FALSE��
 *
 * ˵��:
 *   �ú���������ͼ����б任��RGB TOHSI
 *
 ************************************************************************/
 BOOL WINAPI RGB2HSI(LPSTR lpDIBBits, LONG lWidth, LONG lHeight,unsigned char* lH_data,unsigned char* lS_data,unsigned char* lI_data)
 {
	 // ָ��Դͼ���ָ��
	unsigned char*	lpSrc,*lpH1,*lpS1,*lpI1;	
	// ѭ������
	LONG	i;
	LONG	j;	
	// ͼ��ÿ�е��ֽ���
	LONG	lLineBytes,lineByteNew;		
	// ����ͼ��ÿ�е��ֽ���
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
 * �������ƣ�
 *   HSI2RGB()
 *
 * ����:
 *	 LPSTR lH_data        - ָ��Ŀ��ָ���
 *   LPSTR lpDIBBits    - ָ��ԴDIBͼ������ָ��
 *   LONG  lWidth       - Դͼ���ȣ���������
 *   LONG  lHeight      - Դͼ��߶ȣ���������
 *   
 *   
 *
 * ����ֵ:
 *   BOOL               - �ɹ�����TRUE�����򷵻�FALSE��
 *
 * ˵��:
 *   �ú���������ͼ����б任��RGB TOHSI
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