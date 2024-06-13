#include <assert.h>
#include <iostream>
#include <wtypes.h>

using namespace std;

//����ƽ����ĺ���  
int PFC(int color1, int color2)
{
    int x, y, z;
    x = (color1 & 0xf) - (color2 & 0xf);
    y = ((color1 >> 4) & 0xf) - ((color2 >> 4) & 0xf);
    z = ((color1 >> 8) & 0xf) - ((color2 >> 8) & 0xf);
    return (x * x + y * y + z * z);
};


//ֱ�Ӳ�������  
int Sort1(int* src, int* attach, int n)
{
    int cur, cur1;
    int i, j, k = 0;
    for (i = 1; i < n; i++)
    {
        cur = src[i];
        cur1 = attach[i];
        for (j = i - 1; j >= 0; j--)
        {
            if (cur > src[j])
            {
                src[j + 1] = src[j];
                attach[j + 1] = attach[j];
            }
            else
                break;
        }
        src[j + 1] = cur;
        attach[j + 1] = cur1;
    }
    return 0;
}


//��������  
int Sort2(int* src, int* attach, int n)
{
    if (n <= 12)
        return Sort1(src, attach, n);
    int low = 1, high = n - 1;
    int tmp;
    while (low <= high)
    {
        while (src[low] >= src[0])
        {
            if (++low > n - 1)
                break;
        }
        while (src[high] < src[0])
        {
            if (--high < 1)
                break;
        }
        if (low > high)
            break;
        {
            tmp = src[low];
            src[low] = src[high];
            src[high] = tmp;
            tmp = attach[low];
            attach[low] = attach[high];
            attach[high] = tmp;
        }
        low++;
        high--;
    }


    {
        tmp = src[low - 1];
        src[low - 1] = src[0];
        src[0] = tmp;
        tmp = attach[low - 1];
        attach[low - 1] = attach[0];
        attach[0] = tmp;
    }
    if (low > 1)
        Sort2(src, attach, low - 1);
    if (low < n)
        Sort2(&src[low], &attach[low], n - low);
    return 0;
}

//ð������  ???
int Sort3(int* src, int* attach, int n)
{
    int i, j;
    int temp;
    for (i = 0; i < n - 1; i++)
        for (j = i + 1; j < n; j++)
        {
            if (src[i] < src[j])
            {
                temp = src[j];
                src[j] = src[i];
                src[i] = temp;

                temp = attach[j];
                attach[j] = attach[i];
                attach[i] = temp;

            }
        }


    return 0;
}


/******************************************************/
//��24bit��������ɫ����ת��Ϊ256ɫͼ��ͼ������(������ֵ)  
/*WORD *color24bit,24λ��ɫ��ȡ��4λ�����ɫ��        */
/* int len   ,8λ��ͼ���С                           */
/*BYTE *Index,����ֵ                                  */
/*RGBMixPlate *mainColor,��ɫ��                       */
/*****************************************************/
static int Transfer(WORD* color24bit, LONG len, BYTE* Index, RGBQUAD* mainColor)
{
    int usedTimes[4096] = { 0 };
    int miniColor[4096];
    LONG i;
    for (i = 0; i < 4096; i++)
        miniColor[i] = i;
    i = 0;
    for (i = 0; i < len; i++)
    {
        assert(color24bit[i] < 4096);  //ͼ����п�ҪΪ4�ı���������
        usedTimes[color24bit[i]]++;
    }
    LONG numberOfColors = 0;
    for (i = 0; i < 4096; i++)
    {
        if (usedTimes[i] > 0)
            numberOfColors++;
    }
    //��usedTimes�����������������minColor����(��������ɫֵ)Ҳ����useTimes  
    //�������ƵĽ���  
    //Sort2(usedTimes, miniColor, 4096);   //ok 
    Sort3(usedTimes, miniColor, 4096);    //ok
    //usedTimes�������Ǹ���ɫʹ��Ƶ�ʣ��Ӹߵ������У���Ȼ��numberOfColor��֮��Ķ�Ϊ0  
    //miniColor����������Ӧ����ɫ����  
    //��ǰ256����ɫ���ݱ��浽256ɫλͼ�ĵ�ɫ����  
    for (i = 0; i < 256; i++)
    {
        mainColor[i].rgbBlue = (BYTE)((miniColor[i] >> 8) << 4);
        mainColor[i].rgbGreen = (BYTE)(((miniColor[i] >> 4) & 0xf) << 4);
        mainColor[i].rgbRed = (BYTE)((miniColor[i] & 0xf) << 4);
        mainColor[i].rgbReserved = 0;
    }

    int* colorIndex = usedTimes;//��ԭ����useTimes��������������ֵ  
    memset(colorIndex, 0, sizeof(int) * 4096);

    if (numberOfColors <= 256)
    {
        for (i = 0; i < numberOfColors; i++)
            colorIndex[miniColor[i]] = i;
    }
    else//Ϊ��256֮�����ɫ��ǰ256����ɫ����һ����ӽ���  
    {
        for (i = 0; i < 256; i++)
            colorIndex[miniColor[i]] = i;

        int index, tmp, tmp1;
        for (i = 256; i < numberOfColors; i++)
        {
            tmp = PFC(miniColor[0], miniColor[i]);
            index = 0;
            for (int j = 1; j < 256; j++)
            {
                tmp1 = PFC(miniColor[j], miniColor[i]);
                if (tmp > tmp1)
                {
                    tmp = tmp1;
                    index = j;
                }
            }
            colorIndex[miniColor[i]] = index;
        }
    }
    //��¼������ɫ���ݵ�����ֵ����256ɫλͼ����ɫ����  
    for (i = 0; i < len; i++)
    {
        assert(colorIndex[color24bit[i]] < 256);
        Index[i] = colorIndex[color24bit[i]];
    }

    return 1;
}
