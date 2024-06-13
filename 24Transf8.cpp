#include <assert.h>
#include <iostream>
#include <wtypes.h>

using namespace std;

//计算平方差的函数  
int PFC(int color1, int color2)
{
    int x, y, z;
    x = (color1 & 0xf) - (color2 & 0xf);
    y = ((color1 >> 4) & 0xf) - ((color2 >> 4) & 0xf);
    z = ((color1 >> 8) & 0xf) - ((color2 >> 8) & 0xf);
    return (x * x + y * y + z * z);
};


//直接插入排序  
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


//快速排序  
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

//冒泡排序  ???
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
//将24bit的象素颜色数据转换为256色图的图像数据(即索引值)  
/*WORD *color24bit,24位颜色（取高4位后的颜色）        */
/* int len   ,8位的图像大小                           */
/*BYTE *Index,索引值                                  */
/*RGBMixPlate *mainColor,调色板                       */
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
        assert(color24bit[i] < 4096);  //图像的列宽要为4的倍数！！！
        usedTimes[color24bit[i]]++;
    }
    LONG numberOfColors = 0;
    for (i = 0; i < 4096; i++)
    {
        if (usedTimes[i] > 0)
            numberOfColors++;
    }
    //对usedTimes进行排序，排序过程中minColor数组(保存了颜色值)也作与useTimes  
    //数组相似的交换  
    //Sort2(usedTimes, miniColor, 4096);   //ok 
    Sort3(usedTimes, miniColor, 4096);    //ok
    //usedTimes数组中是各颜色使用频率，从高到低排列，显然第numberOfColor个之后的都为0  
    //miniColor数组中是相应的颜色数据  
    //将前256个颜色数据保存到256色位图的调色盘中  
    for (i = 0; i < 256; i++)
    {
        mainColor[i].rgbBlue = (BYTE)((miniColor[i] >> 8) << 4);
        mainColor[i].rgbGreen = (BYTE)(((miniColor[i] >> 4) & 0xf) << 4);
        mainColor[i].rgbRed = (BYTE)((miniColor[i] & 0xf) << 4);
        mainColor[i].rgbReserved = 0;
    }

    int* colorIndex = usedTimes;//用原来的useTimes数组来保存索引值  
    memset(colorIndex, 0, sizeof(int) * 4096);

    if (numberOfColors <= 256)
    {
        for (i = 0; i < numberOfColors; i++)
            colorIndex[miniColor[i]] = i;
    }
    else//为第256之后的颜色在前256种颜色中找一个最接近的  
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
    //记录各点颜色数据的索引值，即256色位图的颜色数据  
    for (i = 0; i < len; i++)
    {
        assert(colorIndex[color24bit[i]] < 256);
        Index[i] = colorIndex[color24bit[i]];
    }

    return 1;
}
