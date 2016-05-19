#include <iostream>
#include <map>
#include <vector>

using namespace std;


int main()
{

    map<int, int> intMap;
    // 测试[]

    iterator<int, int> *it = NULL;
    if(intMap.find(1) != intMap.end())
    {
        cout<<"1: find!"<<endl;
    }

    intMap[1];

    if(intMap.find(1) != intMap.end())
    {
        cout<<"2: find!"<<endl;
    }

 
    // 测试 value 为std

    map<int, vector<int> > int_vec_map;   

	return 0;
}
