#include "NeedlemanWunsch.hpp"
#include <string.h>
#include <iostream>
#include <iomanip>

CNeedlemanWunsch::CNeedlemanWunsch(char* seq1,char* seq2)
{
    int i,j;
    int lenX,lenY;
    m_sequenceX=seq1;
    m_sequenceY=seq2;

    lenX=m_sequenceX.length();
    lenY=m_sequenceY.length();
    m_scoreMatrix=new matrixNode_t*[lenX+1];
    for(i=0; i<=lenX; i++)
    {
        m_scoreMatrix[i]=new matrixNode_t[lenY+1];
        memset(m_scoreMatrix[i],0,sizeof(int)*(lenY+1));
    }

    for(i=0; i<lenX; i++)
    {
        m_chMapX.insert(std::pair<int,char>(i,m_sequenceX.at(i)));
    }

    for(j=0; j<lenY; j++)
    {
        m_chMapY.insert(std::pair<int,char>(j,m_sequenceY.at(j)));
    }

    sqlite3_open("BLOSUM50.db",&m_database);


}

CNeedlemanWunsch::CNeedlemanWunsch(std::string seq1,std::string seq2)
{
    int i,j;
    int lenX,lenY;
    m_sequenceX=seq1;
    m_sequenceY=seq2;

    lenX=m_sequenceX.length();
    lenY=m_sequenceY.length();
    m_scoreMatrix=new matrixNode_t*[lenX+1];
    for(i=0; i<=lenX; i++)
    {
        m_scoreMatrix[i]=new matrixNode_t[lenY+1];
        memset(m_scoreMatrix[i],0,sizeof(matrixNode_t)*(lenY+1));
    }

    for(i=0; i<lenX; i++)
    {
        m_chMapX.insert(std::pair<int,char>(i,m_sequenceX.at(i)));
    }

    for(j=0; j<lenY; j++)
    {
        m_chMapY.insert(std::pair<int,char>(j,m_sequenceY.at(j)));
    }

    sqlite3_open("BLOSUM50.db",&m_database);

}

CNeedlemanWunsch::~CNeedlemanWunsch(void)
{
    int i;
    for(i=0; i<=m_sequenceX.length(); i++)
    {
        delete[] m_scoreMatrix[i];
    }
    delete m_scoreMatrix;

    sqlite3_close(m_database);
}

void CNeedlemanWunsch::SetPenalty(int penalty)
{
    m_penalty=penalty;
}

void CNeedlemanWunsch::BestScore()
{
    int i,j;
    int lenX,lenY;
    lenX=m_sequenceX.length();
    lenY=m_sequenceY.length();
    int maxScore;
    int direction;


    for(i=0; i<=lenX; i++)
    {
        for(j=0; j<=lenY; j++)
        {
            if(i==0&&j==0)
            {
                m_scoreMatrix[0][0].value=0;
                m_scoreMatrix[0][j].direction=-1;
            }
            else if(i==0&&j!=0)
            {
                m_scoreMatrix[0][j].value=j*m_penalty;
                m_scoreMatrix[0][j].direction=LEFT;
            }
            else if(i!=0&&j==0)
            {
                m_scoreMatrix[i][0].value=i*m_penalty;
                m_scoreMatrix[i][0].direction=TOP;
            }
            else
            {
                maxScore=m_scoreMatrix[i-1][j-1].value+scoreBLOSUM50(i,j);
                direction=DIAGONAL;

                if(maxScore<(m_scoreMatrix[i-1][j].value+m_penalty))
                {
                    maxScore=m_scoreMatrix[i-1][j].value+m_penalty;
                    direction=TOP;
                }
                else if(maxScore==(m_scoreMatrix[i-1][j].value+m_penalty))
                {
                    direction|=TOP;
                }

                if(maxScore<(m_scoreMatrix[i][j-1].value+m_penalty))
                {
                    maxScore=m_scoreMatrix[i][j-1].value+m_penalty;
                    direction=LEFT;
                }
                else if(maxScore==(m_scoreMatrix[i][j-1].value+m_penalty))
                {
                    direction|=LEFT;
                }

                m_scoreMatrix[i][j].value=maxScore;
                m_scoreMatrix[i][j].direction=direction;
            }

        }
    }
}

void CNeedlemanWunsch::PrintOut(void)
{
    int i,j;
    int lenX,lenY;
    std::string xPrime;
    std::string yPrime;
    lenX=m_sequenceX.length();
    lenY=m_sequenceY.length();
    for(i=0; i<=lenX; i++)
    {
        for(j=0; j<=lenY; j++)
        {
            std::cout<<"|"<<std::setw(5)<<m_scoreMatrix[i][j].value;
        }
        std::cout<<"|"<<std::endl;
    }

    i=lenX;
    j=lenY;
    bestSubSequence(i,j,"","");
#if 0
    while(i+j>0)
    {
        if(m_scoreMatrix[i][j].direction==DIAGONAL)
        {
            xPrime=m_sequenceX.at(i-1)+xPrime;
            yPrime=m_sequenceY.at(j-1)+yPrime;
            i--;
            j--;
        }
        else if(m_scoreMatrix[i][j].direction==TOP)
        {
            xPrime=m_sequenceX.at(i-1)+xPrime;
            yPrime="-"+yPrime;
            i--;
        }
        else if(m_scoreMatrix[i][j].direction==LEFT)
        {
            xPrime="-"+xPrime;
            yPrime=m_sequenceY.at(j-1)+yPrime;
            j--;
        }
    }
    std::cout<<"Best alignment: "<<std::endl;
    std::cout<<"X: "<<xPrime<<std::endl;
    std::cout<<"Y: "<<yPrime<<std::endl;
#endif /* Modify by Amos.zhu */

}

void CNeedlemanWunsch::bestSubSequence(int i,int j,std::string xSuffix,std::string ySuffix)
{
    std::string xPrime=xSuffix;
    std::string yPrime=ySuffix;

    int count=0;
    int direction;
    int x,y;

    while(i+j>0)
    {
        count=0;
        direction=m_scoreMatrix[i][j].direction;
        x=i;
        y=j;
        xSuffix=xPrime;
        ySuffix=yPrime;
        if(direction&DIAGONAL)
        {
            count++;
            xPrime=m_sequenceX.at(i-1)+xSuffix;
            yPrime=m_sequenceY.at(j-1)+ySuffix;
            i--;
            j--;
        }

        if(direction&TOP)
        {
            count++;
            if(count>=2)
            {
                bestSubSequence(x-1,y,m_sequenceX.at(x-1)+xSuffix,"-"+ySuffix);
            }
            else
            {
                xPrime=m_sequenceX.at(i-1)+xSuffix;
                yPrime="-"+ySuffix;
                i--;
            }

        }

        if(direction&LEFT)
        {
            count++;
            if(count>=2)
            {
                bestSubSequence(x,y-1,"-"+xSuffix,m_sequenceY.at(y-1)+ySuffix);
            }
            else
            {
                xPrime="-"+xSuffix;
                yPrime=m_sequenceY.at(j-1)+ySuffix;
                j--;
            }
        }
    }

    std::cout<<"Best alignment: "<<std::endl;
    std::cout<<"X: "<<xPrime<<std::endl;
    std::cout<<"Y: "<<yPrime<<std::endl;

}

int CNeedlemanWunsch::scoreBLOSUM50(int i,int j)
{
    sqlite3_stmt* res;
    int rc;
    char* errMsg;
    char sqlStatement[128];
    char X,Y;
    X=m_chMapX[i-1];
    Y=m_chMapY[j-1];
    int score;

    snprintf(sqlStatement,128,"select %c from BLOSUM50 where protein= '%c'",Y,X);

    rc=sqlite3_prepare_v2(m_database,sqlStatement,strlen(sqlStatement),&res,NULL);
    if(rc)
    {
        fprintf(stderr, "Can't open statement: %s\n", sqlite3_errmsg(m_database));
        return -0XFFFFF;
    }

    int nColumn;
    nColumn = sqlite3_column_count(res);
    //printf("column=%d\n",nColumn);
    while(sqlite3_step(res)==SQLITE_ROW)
    {
        score=sqlite3_column_int(res,0);
        //printf("%s score is %d\n",sqlStatement,score);
    }

    return score;
}
