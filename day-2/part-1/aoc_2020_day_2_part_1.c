//Author: PlanckBit
//MIT License
//Copyright (c) 2020 PlanckBit
//Advent of Code --> 2020-Event-Day-2-Puzzle-Part-1
//Description: https://adventofcode.com/2020/day/2

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int LINE_COUNT = 1000;
const int STR_SIZE = 50;

//used for keeping count of how many times
// a given character appears in a string policy file line
int occurrCharCount = 0;

//used for keeping count of valid and invalid passwords
int validPasswordCount = 0;
int inValidPasswordCount = 0;

void readFile(char const* const fileName, char arrList[][STR_SIZE])
{
    FILE* file = fopen(fileName, "r");
    char line[STR_SIZE];
    int lineCount = 0;
       
    while(fgets(line, sizeof(line), file))
    {
        //printf("%s", line);
        strcpy(arrList[lineCount++], line);
    }
    fclose(file);
}

void scanPasswordString(int min, int max, char *n, char *s)
{
  //*n is the character to search for in string s
  char *subStr = strchr(s,*n);
  
  if(subStr != NULL && occurrCharCount <= max )
  {
        occurrCharCount++;
        //printf("subStr=%s", subStr);
        //Use recurrsion to solve!
        scanPasswordString(min, max, n, subStr+1);
  }
}

int parsePasswordPolicy(char *strPassPolicy)
{
   //Minimum and Max times Letter in strPassPolicy rule.
   // Ex: 1-3 a: abcde  minTimes->1 , maxTimes->3
   int minTimes = 0;
   int maxTimes = 0;

   //Copy our strPassPolicy so we don't mess with original
   char strToken[STR_SIZE];
   strcpy(strToken, strPassPolicy);
   //printf("\nstrToken=%s", strToken);
   
   //Parse the first 3 tokens 
   char *strMinMax = strtok(strToken, " ");
   char *strChar = strtok(NULL, " ");
   char *strPass = strtok(NULL, " ");
   //printf("strMinMax=%s\n", strMinMax);
   //printf("strChar=%s\n", strChar);
   //printf("strPass=%s", strPass);   

   //Parse the min and max
   minTimes = atoi(strtok(strMinMax, "-"));
   maxTimes = atoi(strtok(NULL, "-"));
   //printf("minTimes=%d\n",minTimes);
   //printf("maxTimes=%d\n",maxTimes);   

   //Parse the Letter to search 
   char *searchChar = strtok(strChar, ":");
   //printf("searchChar=%s\n",searchChar);

   //Init our char count
   occurrCharCount = 0; 
   scanPasswordString(minTimes, maxTimes, searchChar, strPass);
   //printf("occurrCharCount=%d\n",occurrCharCount);

   if(occurrCharCount >= minTimes && occurrCharCount <= maxTimes)
   {
	validPasswordCount++;
        //printf("GOOD PASSWORD\n");
   }
   else
   {
        inValidPasswordCount++;
	//printf("BAD PASSWORD\n");
   }
}

int main(int argc, char* argv[])
{
    char arrList[LINE_COUNT][STR_SIZE];
    readFile(argv[1], arrList);

    for(int i=0; i < LINE_COUNT; i++)
    {
        //printf("%s", arrList[i]);
        parsePasswordPolicy(arrList[i]);
    }
    
    printf("\nValid Passwords=%d\n",validPasswordCount);
    printf("Invalid Passwords=%d\n",inValidPasswordCount);
    return 0;
}
