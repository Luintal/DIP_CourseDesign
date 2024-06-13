// PointTrans.h
#define PI 3.14159265
#define MIN(x,y) ((x)<(y)?(x):(y))
#define MAX(x,y) ((x)>(y)?(x):(y))

#ifndef _INC_PointTransAPI
#define _INC_PointTransAPI

// º¯ÊýÔ­ÐÍ
BOOL WINAPI LinerTrans(LPSTR lpDIBBits, LONG lWidth, LONG lHeight, FLOAT fA, FLOAT fB);
BOOL WINAPI ThresholdTrans(LPSTR lpDIBBits, LONG lWidth, LONG lHeight, BYTE bThre);
BOOL WINAPI WindowTrans(LPSTR lpDIBBits, LONG lWidth, LONG lHeight, BYTE bLow, BYTE bUp);
BOOL WINAPI GrayStretch(LPSTR lpDIBBits, LONG lWidth, LONG lHeight, BYTE bX1, BYTE bY1, BYTE bX2, BYTE bY2);
BOOL WINAPI InteEqualize(LPSTR lpDIBBits, LONG lWidth, LONG lHeight);

BOOL WINAPI Segmental2_Linear_Tran(LPSTR lpDIBBits, LONG lWidth, LONG lHeight,  int type,int threshold=128);
BOOL WINAPI LinerTrans24(LPSTR lpDIBBits, LONG lWidth, LONG lHeight, FLOAT fA, FLOAT fB);

BOOL WINAPI Tran24ColTo24Gray(LPSTR lpDIBBits, LONG lWidth, LONG lHeight);
BOOL WINAPI Tran8ColTo8Gray(LPSTR lpDIB,LPSTR lpDIBBits, LONG lWidth, LONG lHeight);
BOOL WINAPI Tran24ColTo8Gray(LPSTR lpDIB,LPSTR lpDIBBits, LONG lWidth, LONG lHeight);
BOOL WINAPI Tran24ColTo8Col(LPSTR lpDIB,LPSTR lpDIBBits, LONG lWidth, LONG lHeight);

BOOL WINAPI RGB2HSI(LPSTR lpDIBBits, LONG lWidth, LONG lHeight,unsigned char* lH_data,unsigned char* lS_data,unsigned char* lI_data);
BOOL WINAPI HSI2RGB(double H,double S,double I,double &R,double &G,double &B);


BOOL WINAPI ChangeGray(LPSTR lpDIBBits, int BitCount,LONG lWidth, LONG lHeight,int offset);
BOOL WINAPI Color8Add(LPSTR lpDib, LPSTR lpDIBBits, int BitCount, LONG lWidth, LONG lHeight, int offset);
BOOL WINAPI Color8Add_HSI(LPSTR lpDib, LPSTR lpDIBBits, int BitCount, LONG lWidth, LONG lHeight, int offset);
BOOL WINAPI If8Gray(LPSTR lpDib, int BitCount);

#endif //!_INC_PointTransAPI