#ifndef _NEEDLEMANWUNSCH_HPP_
#define _NEEDLEMANWUNSCH_HPP_

#include <string>
#include <map>
#include <sqlite3.h>

#define LEFT 0x00000001
#define TOP 0x00000002
#define DIAGONAL 0x00000004
#define STOP 0x10000000

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
    void GlobalAlignment(void);
    void GlobalAlignmentPrintOut(void);
    void RepeatAlignment(int threshold);
    void RepeatAlignmentPrintOut(void);
    void OverlapAlignment(void);
    void OverlapAlignmentPrintOut(void);

private:
    int scoreBLOSUM50(int i,int j);
    void bestSubSequence(int i,int j,std::string xSuffix,std::string ySuffix);
        void overlapSubSequence(int i,int j,std::string xSuffix,std::string ySuffix);

private:
    sqlite3* m_database;
    matrixNode_t** m_scoreMatrix=nullptr;
    std::map<int,char> m_chMapX;
    std::map<int,char> m_chMapY;
    std::string m_sequenceX;
    std::string m_sequenceY;
    int m_penalty;
    int m_rpScore=0;
    int m_threshold=0;
};

#endif
