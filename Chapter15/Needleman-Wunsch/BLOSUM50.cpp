#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <iostream>
#include <map>

#include <sqlite3.h>
#include <utility>

int BLOSUM50Matrix[20][20]=
{
    {5,-2,-1,-2,-1,-1,-1,0,-2,-1,-1,-3,-1,1,0,-3,-2,0},
    {-2,7,-1,-2,-4,1,0,-3,0,-4,-3,3,-2,-3,-3,-1,-1,-3,-1,-3},
    {-1,-1,7,2,-2,0,0,0,1,-3,-4,0,-2,-4,-2,1,0,-4,-2,-3},
    {-2,-2,2,8,-4,0,2,-1,-1,-4,-4,-1,-4,-5,-1,0,-1,-5,3,-4},
    {-1,-4,-2,-4,13,-3,-3,-3,-3,-2,-2,-3,-2,-2,-4,-1,-1,-5,-3,-1},
    {-1,1,0,0,-3,7,2,-2,1,-3,-2,2,0,-4,-10,-1,-1,-1,-3},
    {-1,0,0,2,-3,2,6,-3,0,-4,-3,1,-2,-3,-1,-1,-1,-3,-2,-3},
    {0,-3,0,-1,-3,-2,-3,8,-2,-4,-4,-2,-3,-4,-2,0,-2,-3,-3,-4},
    {-2,0,1,-1,-3,1,0,-2,10,-4,-3,0,-1,-1,-2,-1,-2,-3,2,-4},
    {-1,-4,-3,-4,-2,-3,-4,-4,-4,5,2,-3,2,0,-3,-3,-1,-3,-1,4},
    {-2,-3,-4,-4,-2,-2,-3,-4,-3,2,5,-3,3,1,-4,-3,-1,-2,-1,1},
    {-1,3,0,-1,-3,2,1,-2,0,-3,-3,6,-2,-4,-1,0,-1,-3-2,-3},
    {-1,-2,-2,-4,-2,0,-2,-3,-1,2,3,-2,7,0,-3,-2,-1,-1,0,1},
    {-3,-3,-4,-5,-2,-4,-3,-4,-1,0,1,-4,0,8,-4,-3,-2,1,4,-1},
    {-1,-3,-2,-1,-4,-1,-1,-2,-2,-3,-4,-1,-3,-4,10,-1,-1,-4,-3,-3},
    {1,-1,1,0,-1,0,-1,0,-1,-3,-3,0,-2,-3,-1,5,2,-4,-2,-2},
    {0,-1,0,-1,-1,-1,-1,-2,-2,-1,-1,-1,-1,2,-1,2,5,-3,-2,0},
    {-3,-3,-4,-5,-5,-1,-3,-3,-3,-3,2,-3,1,1,-4,-4,3,15,2,-3},
    {-2,-1,-2,-3,-3,-1,-2,-3,2,-1,-1,-2,0,4,-3,-2,-2,2,8,-1},
    {0,-3,-3,-4,-1,-3,-3,4,-4,4,1,-3,1,-1,-3,-2,0,-3,-1,5}
};

std::map<int,char> charMap;

static int callback(void *NotUsed, int argc, char **argv, char **azColName)
{
    int i;
    for(i=0; i<argc; i++)
    {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
}
void WriteBLOSUM50ToDB(void)
{
    int i,j;
    sqlite3* connection;
    int rc;
    std::string sql;
    std::string sqlInsert;
    std::string subStr;
    char* errMsg;
    char protein;
    std::map<int,char>::iterator it;
    rc=sqlite3_open("BLOSUM50.db",&connection);
    if(rc)
    {
        fprintf(stderr,"Cannot open BLOSUM50 database");
        exit(0);
    }

    sql="create table if not exists BLOSUM50(protein varchar(1) primary key";
    it=charMap.begin();
    for(; it!=charMap.end(); it++)
    {
        subStr=it->second;
        sql+=", "+subStr+" integer";
    }
    sql+=");";

    rc=sqlite3_exec(connection,sql.c_str(),callback,0,&errMsg);
    std::cout<<sql<<std::endl;
    if(rc!=SQLITE_OK)
    {
        fprintf(stderr,"SQL error: %s\n",errMsg);
        sqlite3_free(errMsg);
    }

    for(i=0; i<20; i++)
    {
        protein=charMap[i];
        sqlInsert="insert into BLOSUM50 values(";
        subStr=protein;
        sqlInsert+="'"+subStr+"'";
        for(j=0; j<20; j++)
        {
            subStr=std::to_string(BLOSUM50Matrix[i][j]);
            sqlInsert+=", '"+subStr+"'";
        }
        sqlInsert+=");";
        std::cout<<sqlInsert<<std::endl;
        rc=sqlite3_exec(connection,sqlInsert.c_str(),callback,0,&errMsg);
        if(rc!=SQLITE_OK)
        {
            fprintf(stderr,"SQL error: %s\n",errMsg);
            sqlite3_free(errMsg);
        }
    }

    sqlite3_close(connection);
}

void InitBLOSUM50Map(void)
{
    charMap.insert(std::pair<int,char>(0,'A'));
    charMap.insert(std::pair<int,char>(1,'R'));
    charMap.insert(std::pair<int,char>(2,'N'));
    charMap.insert(std::pair<int,char>(3,'D'));
    charMap.insert(std::pair<int,char>(4,'C'));
    charMap.insert(std::pair<int,char>(5,'Q'));
    charMap.insert(std::pair<int,char>(6,'E'));
    charMap.insert(std::pair<int,char>(7,'G'));
    charMap.insert(std::pair<int,char>(8,'H'));
    charMap.insert(std::pair<int,char>(9,'I'));
    charMap.insert(std::pair<int,char>(10,'L'));
    charMap.insert(std::pair<int,char>(11,'K'));
    charMap.insert(std::pair<int,char>(12,'M'));
    charMap.insert(std::pair<int,char>(13,'F'));
    charMap.insert(std::pair<int,char>(14,'P'));
    charMap.insert(std::pair<int,char>(15,'S'));
    charMap.insert(std::pair<int,char>(16,'T'));
    charMap.insert(std::pair<int,char>(17,'W'));
    charMap.insert(std::pair<int,char>(18,'Y'));
    charMap.insert(std::pair<int,char>(19,'V'));
}

int main(void)
{
    InitBLOSUM50Map();
    WriteBLOSUM50ToDB();
}

