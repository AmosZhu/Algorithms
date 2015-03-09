#include "CDigest.hpp"
#include <stdio.h>
int main(int argc,char* argv[])
{
#if 0
    std::multiset<int> set1;
    set1.insert(2);
    set1.insert(2);
    set1.insert(3);
    set1.insert(3);
    set1.insert(4);
    set1.insert(5);
    set1.insert(6);
    set1.insert(7);
    set1.insert(8);
    set1.insert(10);
#endif /* Modify by Amos.zhu */

    if(argc!=2)
    {
        printf("Usage <func><Input file>\n");
        return 0;
    }

    CDigest partialDigets;
    partialDigets.InitPartialDigest(argv[1]);
    partialDigets.DoPartialDigest();
}
