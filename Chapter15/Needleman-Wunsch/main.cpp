#include "NeedlemanWunsch.hpp"

int main(int argc,char* argv[])
{
    if(argc!=3)
    {
        printf("Usage: <func><sequence1><sequence2>\n");
        return -1;
    }

    CNeedlemanWunsch needleman(argv[1],argv[2]);
    needleman.SetPenalty(-8);
    needleman.BestScore();
    needleman.PrintOut();
}
