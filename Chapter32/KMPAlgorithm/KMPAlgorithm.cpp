#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

}

int main(int argc,char* argv[])
{
    int idx;
    int len;
    int* PI;
    if(argc!=3)
    {
        printf("usage: <Path><String><Pattern>\n");
        return -1;
    }

    len=strlen(argv[2]);
    KMPCompute(argv[1],argv[2]);

    PI=ComputePrefix(argv[2]);
    for(idx=0; idx<len; idx++)
    {
        printf("|%c",argv[2][idx]);
    }
    printf("|\n");

    for(idx=1; idx<=len; idx++)
    {
        printf("|%d",PI[idx]);
    }
    printf("|\n");

    delete PI;

    return 1;

}
