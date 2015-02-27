#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>

static int* ComputePrefix(char* str)
{
    int q;
    int m=strlen(str);
    int k=0;
    int* PI=new int[m+1];
    PI[1]=0;

    for(q=2; q<=m; q++)
    {
        while(k>0&&str[k]!=str[q-1])
        {
            k=PI[k];
        }

        if(str[k]==str[q-1])
        {
            k++;
        }

        PI[q]=k;
    }

    return PI;
}

void KMPCompute(char* text, char* pattern)
{
    int i;
    int* PI;
    int kLength=0;
    int textLength=strlen(text);;
    int patternLength=strlen(pattern);
    PI=ComputePrefix(pattern);
    for(i=0; i<patternLength; i++)
    {
        printf("|%c",pattern[i]);
    }
    printf("|\n");

    for(i=1; i<=patternLength; i++)
    {
        printf("|%d",PI[i]);
    }
    printf("|\n");


    for(i=0; i<textLength; i++)
    {
        while(kLength>0&&pattern[kLength]!=text[i])
        {
            kLength=PI[kLength];
        }

        if(text[i]==pattern[kLength])
        {
            kLength++;
        }

        if(kLength==patternLength)
        {
            printf("The %s is occured in pos %d\n",pattern,i-kLength+1);
        }
    }

    delete PI;

}

void KMPComputeByIndex(char* text, char* pattern)
{
    int i;
    int* PI;
    int textLength=strlen(text);;
    int patternLength=strlen(pattern);
    std::string P(pattern);
    std::string T(text);
    std::string PT=P+"@"+T;
    PI=ComputePrefix((char*)PT.c_str());
    for(i=0; i<PT.length(); i++)
    {
        printf("|%c",PT[i]);
    }
    printf("|\n");

    for(i=1; i<=PT.length(); i++)
    {
        printf("|%d",PI[i]);
    }
    printf("|\n");

    for(i=patternLength+2; i<patternLength+2+textLength; i++)
    {
        if(PI[i]==patternLength)
        {
            printf("The %s is occured in pos %d\n",pattern,i-patternLength+1-(patternLength+2));
        }
    }

    delete PI;

}

int main(int argc,char* argv[])
{
    int idx;
    int len;
    if(argc!=3)
    {
        printf("usage: <Path><String><Pattern>\n");
        return -1;
    }

    KMPCompute(argv[1],argv[2]);
    KMPComputeByIndex(argv[1],argv[2]);

    return 1;
}
