#include <stdio.h>
#include <stdlib.h>

typedef struct _result
{
    int d;
    int x;
    int y;
} LINEAR_RES;

int EUCLID(int a,int b);
LINEAR_RES EXTENDED_EUCLID(int a,int b);
static void Print_EUCLID(LINEAR_RES res)
{
    printf("d=%d,x=%d,y=%d\n",res.d,res.x,res.y);
}

int main(void)
{
#if 0
    int d;
    d=EUCLID(100,60);
    printf("gcd = %d\n",d);
#endif /* Modify by mac.zhu */

    LINEAR_RES res;
    res=EXTENDED_EUCLID(99,78);
    Print_EUCLID(res);
    return 1;
}

int EUCLID(int a,int b)
{
    int d; //gcd
    if(b==0)
        return a;

    d=EUCLID(b,a%b);
    return d;
}

LINEAR_RES EXTENDED_EUCLID(int a, int b)
{
    LINEAR_RES res,res1;
    if(b==0)
    {
        res.d=a;
        res.x=1;
        res.y=0;
        return res;
    }

    res1=EXTENDED_EUCLID(b,a%b);
    //Print_EUCLID(res1);
    res.d=res1.d;
    res.x=res1.y;
    res.y=(res1.x-(a/b)*res1.y);
    return res;
}