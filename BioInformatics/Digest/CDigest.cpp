#include "CDigest.hpp"
#include <iterator>
#include <algorithm>
#include <iostream>
#include <math.h>

#define DEBUG 1


typedef std::multiset<int, std::less<int>,std::allocator<int> > set_type;

inline std::ostream& operator<< (std::ostream& out,
                                 const set_type& s)
{
    typedef std::ostream_iterator<set_type::value_type, char,std::char_traits<char> > os_iter;

    std::copy (s.begin (), s.end (), os_iter (std::cout, " "));

    return out;
}
CDigest::CDigest()
{}

CDigest::~CDigest()
{}

void CDigest::InitPartialDigest(std::multiset<int> srcSet)
{
    m_setL=srcSet;
}

void CDigest::InitPartialDigest(const char* fileName)
{
    FILE* fp;
    int val;
    if((fp=fopen(fileName,"rb"))==NULL)
    {
        std::cout<<"file name not exist!"<<std::endl;
        return;
    }


    while(fscanf(fp,"%d",&val)&&val!=-1)
    {
        m_setL.insert(val);
    }

    fclose(fp);
}

void CDigest::DoPartialDigest(void)
{
    std::multiset<int> X;
    if(m_setL.empty())
    {
        std::cout<<"The initial set L is empty!"<<std::endl;
        return;
    }

    //std::cout<<m_setL<<std::endl;

    auto it=m_setL.end();
    it--;
    int maxNum=*it;

    X.insert(0);
    X.insert(maxNum);
    m_setL.erase(maxNum);

    place(&m_setL,&X,maxNum);

}

void CDigest::place(std::multiset <int> *L, std::multiset <int> *X, int maxNum,std::string str)
{
#if DEBUG
    std::cout<<str<<"L="<<*L<<std::endl;
    std::cout<<str<<"X="<<*X<<std::endl;
#endif /* Modify by Amos.zhu */
    int y,ys; //y smaller
    std::multiset<int>::iterator it;
    std::multiset<int> deltaRes;
    std::multiset<int> tempSet;
    if(L->empty())
    {
        std::cout<<"Result: \n"<<*X<<std::endl;
        printf("===================================!!!!\n");
        return;
    }

    it=L->end();
    y=*(--it);

    ys=maxNum-y;

    /*
    *   Calculate from the smaller number
    */
    deltaRes=delta(X,ys);
    tempSet.clear();
    std::set_intersection(L->begin (), L->end (),deltaRes.begin (), deltaRes.end (),std::inserter(tempSet, tempSet.begin()));
#if DEBUG
    std::cout<<str<<"ys="<<ys<<std::endl;
    std::cout<<str<<"Delta(X,ys)= "<<deltaRes<<std::endl;
    std::cout<<str<<"tempSet= "<<tempSet<<std::endl;
#endif /* Modify by Amos.zhu */
    if(deltaRes==tempSet)
    {
        X->insert(ys);
        for(it=deltaRes.begin(); it!=deltaRes.end(); it++)
        {
            L->erase(L->find(*it));
        }
        place(L,X,maxNum,str+"  ");
        X->erase(X->find(ys));
        /*
        *   Bug in union, use for loop
        */
        for(it=deltaRes.begin(); it!=deltaRes.end(); it++)
        {
            L->insert(*it);
        }
    }

    /*
    *   Calculate from the original number
    */
#if DEBUG
    std::cout<<str<<"L="<<*L<<std::endl;
    std::cout<<str<<"X="<<*X<<std::endl;
#endif /* Modify by Amos.zhu */
    deltaRes=delta(X,y);
    tempSet.clear();
    std::set_intersection(L->begin (), L->end (),deltaRes.begin (), deltaRes.end (),std::inserter(tempSet, tempSet.begin()));
#if DEBUG
    std::cout<<str<<"y="<<y<<std::endl;
    std::cout<<str<<"Delta(X,y)= "<<deltaRes<<std::endl;
    std::cout<<str<<"tempSet= "<<tempSet<<std::endl;
#endif /* Modify by Amos.zhu */

    if(deltaRes==tempSet)
    {
        X->insert(y);
        for(it=deltaRes.begin(); it!=deltaRes.end(); it++)
        {
            L->erase(L->find(*it));
        }
        place(L,X,maxNum,str+"  ");
        X->erase(X->find(y));
        /*
        *   Bug in union, use for loop
        */
        for(it=deltaRes.begin(); it!=deltaRes.end(); it++)
        {
            L->insert(*it);
        }
    }

    return;

}

std::multiset<int> CDigest::delta(std::multiset <int> *srcSet, int y)
{
    std::multiset<int> res;
    std::multiset<int>::iterator it=srcSet->begin();

    for(; it!=srcSet->end(); it++)
    {
        res.insert(std::abs(*it-y));
    }

    return res;

}
