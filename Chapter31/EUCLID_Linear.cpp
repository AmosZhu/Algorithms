#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <iterator>

typedef struct _result
{
    int d;
    int x;
    int y;
} LINEAR_RES;

int EUCLID(int a,int b);
LINEAR_RES EXTENDED_EUCLID(int a,int b);
std::vector<int> Modular_Linear_Equation_Solver(int a,int b,int n);
static void Print_result(std::vector<int> res)
{
    printf("result\n");
    for(std::vector<int>::iterator iter=res.begin(); iter!=res.end(); iter++)
    {
        printf("x=%d, ",*iter);
    }

    printf("\n");
}

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
    LINEAR_RES res;
    res=EXTENDED_EUCLID(99,78);
    Print_EUCLID(res);
#endif /* Modify by Amos.zhu */

    std::vector<int> res;
    res=Modular_Linear_Equation_Solver(4,8,12);
    Print_result(res);
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

std::vector<int> Modular_Linear_Equation_Solver(int a,int b,int n)
{
    std::vector<int> res;
    LINEAR_RES Linear_res;
    int i;
    int x0,xi;
    Linear_res=EXTENDED_EUCLID(a,n);
    Print_EUCLID(Linear_res);
    if(b%Linear_res.d==0)
    {
        x0=Linear_res.x*(b/Linear_res.d)%n; //x0=x'*(b/d) mod n
        res.push_back(x0);
        for(i=1; i<Linear_res.d; i++)
        {
            xi=x0+i*(n/Linear_res.d);       //xi=x0+i(n/d)  i from 1 to d-1
            res.push_back(xi);
        }
    }

    return res;
}

