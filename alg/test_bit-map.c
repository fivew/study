# include <stdio.h>
# include <stdlib.h>


//********************************************/
// 学习使用bit-map
//
//
//*******************************************/

//******************************************/
// 1. 最基础， 一个字节8位，表示8个数字0~7
// 2. 保存N个数，需要N/8个字节,比起传统的N*4，大大节约空间
//*******************************************/

int main()
{   
    int iMax=134;
    int iArray[] = {7,6,4,2,3,1,0,56,87,43,90,67,23,13,9,100,134};
    int iSize = (iMax+7)/8;
    // 1. 定义需要的空间大小
    char* pBitMap = malloc(iSize);
    if (NULL == pBitMap)
    {
    return 1;
    }
    memset(pBitMap, 0, iSize);

    // 2. 将数据存存入bitMap数组中
    int iLenofArr = sizeof(iArray)/sizeof(iArray[0]);
    int i = 0;
    int j = 0;
    for(i = 0; i < iLenofArr; i++)
    {
        // 1. 找到N属于第几个字节 N/8
        // 2. 找打N属于第几位 N%8
        // 3. 将第N位设置为1
        int iBytes = iArray[i]/8;
        int iBit = iArray[i]%8;
        *(pBitMap + iBytes) |= (1<<iBit);
        //printf("%x\n", *pBitMap);
    }

   // 3. 输出存放的记录
   for(i = 0; i<iSize; i++)
   {
      //printf("%X\n", *(pBitMap+i));
      for(j = 0; j<8; j++)
      {
         // printf("%X %X \n", 1<<j, *(pBitMap + i)&(1<<j));
     if(0 != (*(pBitMap + i)&(1<<j)))
         {
            printf("%d ", i*8+j);
         }
      }
   }
   printf("\n");
   free(pBitMap);
   pBitMap = NULL;
   
   return 0;
}
