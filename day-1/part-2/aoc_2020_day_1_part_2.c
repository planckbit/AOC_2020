//Author: PlanckBit
//MIT License
//Copyright (c) 2020 PlanckBit
//Advent of Code --> 2020-Event-Day-1-Puzzle-Part-2
//Description: https://adventofcode.com/2020/day/1

#include <stdio.h>
#include <stdlib.h>

const int LINE_COUNT = 200;

void readFile(char const* const fileName, int arrList[])
{
    FILE* file = fopen(fileName, "r");
    char line[10];
    int lineCount = 0;

    while(fgets(line, sizeof(line), file))
    {
        //printf("%s", line);
        arrList[++lineCount] = atoi(line);
    }
    fclose(file);
}

/* Find ----> z = 2020 - x - y*/
int FindSum(int x, int y, int arrList[])
{
    int z = 2020 - x - y;

    for(int i=0; i < LINE_COUNT; i++)
    {
        if(arrList[i] == z)
        {
            printf("SUCCESS FOUND SUM 2020\n");
            printf("x=%d\n",x);
            printf("y=%d\n",y);
            printf("z=%d\n",z);
            int xyz= arrList[i] * x * y;
            printf("x*y*z=%d\n",xyz);
	    return 1; //found
        }
    }
    return 0; //not found
}

int main(int argc, char* argv[])
{
    int arrList[LINE_COUNT];
    readFile(argv[1], arrList);
    int bFound = 0;

    //O(n)^2 - Can be improved
    for(int i=0; i < LINE_COUNT; i++)
    {
        for(int p=0; p < LINE_COUNT; p++)
        {
            bFound = FindSum(arrList[i], arrList[p], arrList);
            if(bFound)
	        break;
        }
        if(bFound)
            break;
    }
    return 0;
}
