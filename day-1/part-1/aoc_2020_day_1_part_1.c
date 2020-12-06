//Author: PlanckBit
//MIT License
//Copyright (c) 2020 PlanckBit
//Advent of Code --> 2020-Event-Day-1-Puzzle-Part-1
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

/* Find ----> y = 2020 - x*/
int FindSum(int x, int arrList[])
{
    int y = 2020 - x;

    for(int i=0; i < LINE_COUNT; i++)
    {
       if(arrList[i] == y)
       {
         printf("SUCCESS FOUND SUM 2020\n");
         printf("x=%d\n",x);
         printf("y=%d\n",y);
         int xy= arrList[i] * x;
         printf("x*y=%d\n",xy);
	 return 1; //found
       }
    }
    return 0; //not found
}

int main(int argc, char* argv[])
{
    int arrList[LINE_COUNT];
    readFile(argv[1], arrList);
    
    for(int i=0; i < LINE_COUNT; i++)
    {
        if(FindSum(arrList[i], arrList))
	    break;
    }
    return 0;
}
