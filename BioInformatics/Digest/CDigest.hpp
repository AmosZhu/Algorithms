#ifndef _CDIGEST_HPP_
#define _CDIGEST_HPP_

#include <set>
#include <string>

class CDigest
{
public:
    CDigest();
    ~CDigest();

    void InitPartialDigest(std::multiset<int> srcSet);
    void InitPartialDigest(const char* fileName);
    void DoPartialDigest(void);

private:
    std::multiset<int> delta(std::multiset<int>* srcSet,int y);
    void place(std::multiset<int>* L,std::multiset<int>* X,int maxNum,std::string gap="");

private:
    std::multiset<int> m_setL;

};


#endif
