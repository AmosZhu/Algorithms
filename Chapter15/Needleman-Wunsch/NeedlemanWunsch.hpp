#ifndef _NEEDLEMANWUNSCH_HPP_
#define _NEEDLEMANWUNSCH_HPP_

#include <string>
#include <map>
#include <sqlite3.h>

#define LEFT 0
#define TOP 1
#define DIAGONAL 2

struct matrixNode_t
{
    int value;
    int direction;
};

class CNeedlemanWunsch
{
public:
    CNeedlemanWunsch(void)=delete;
    CNeedlemanWunsch(std::string seq1,std::string seq2);
    CNeedlemanWunsch(char* seq1,char* seq2);
    ~CNeedlemanWunsch(void);
    void SetPenalty(int penalty);
    void BestScore(void);

    void PrintOut(void);

private:
    int scoreBLOSUM50(int i,int j);

private:
        sqlite3* m_database;
    matrixNode_t** m_scoreMatrix=nullptr;
    std::map<int,char> m_chMapX;
    std::map<int,char> m_chMapY;
    std::string m_sequenceX;
    std::string m_sequenceY;
    int m_penalty;
};

#endif
