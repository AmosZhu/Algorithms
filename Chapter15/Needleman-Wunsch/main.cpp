#include "NeedlemanWunsch.hpp"
#include <iostream>


static bool readOneUnsignedInt(unsigned int &input)
{
    std::string temp;
    while (temp.length() == 0)
    {
        getline(std::cin, temp);
    }
    if (temp.find_first_not_of("0123456789") != std::string::npos)
    {
        return false;
    }
    char **ptr(0);
    input = std::strtoul(temp.c_str(), ptr, 0);

    return true;
}

int main(int argc,char* argv[])
{
    std::string xSequence,ySequence;
    unsigned int sel;
    bool qFlag=false;

    while(!qFlag)
    {
        std::cout<<"1.Global Alignment"<<std::endl;
        std::cout<<"2.Repeat Alignment"<<std::endl;
        std::cout<<"9.Quit"<<std::endl;

        std::cout<<"Your Selection>>";
        if(!readOneUnsignedInt(sel))
        {
            continue;
        }

        switch(sel)
        {
            case 1:
            {
                std::cout<<"Enter x sequence: ";
                std::cin>>xSequence;
                std::cout<<"Enter y sequence: ";
                std::cin>>ySequence;
                CNeedlemanWunsch needleman(xSequence,ySequence);
                needleman.SetPenalty(-8);
                needleman.GlobalAlignment();
                needleman.GlobalAlignmentPrintOut();
            }
            break;
            case 2:
            {
                std::cout<<"Enter x sequence: ";
                std::cin>>xSequence;
                std::cout<<"Enter y sequence: ";
                std::cin>>ySequence;
                CNeedlemanWunsch needleman(xSequence,ySequence);
                needleman.SetPenalty(-8);
                needleman.RepeatAlignment(20);
                needleman.RepeatAlignmentPrintOut();
            }
            break;
            case 9:
            {
                qFlag=true;
            }
            break;
            default:
                break;
        }
    }

}
