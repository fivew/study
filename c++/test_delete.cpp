#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;

namespace hyf{


#define DELETE_A(p)  \
   {				\
        if(NULL != p)		\
 		{			\
			delete [] p;\
            p = NULL;\
 		}			\
    }				\

#define NEW(p, clasename) \
	{						\
		p = new clasename;	\
	}						\

}

int main()
{
    
    char* pTmp = NULL;
    NEW(pTmp, char[12])
    
    memset(pTmp, 0, sizeof(12));
    // 测试重复释放指针问题
    DELETE_A(pTmp)
    DELETE_A(pTmp)

    
    

    return 0;
}
