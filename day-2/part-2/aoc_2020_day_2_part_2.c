//Author: PlanckBit
//MIT License
//Copyright (c) 2020 PlanckBit
//Advent of Code --> 2020-Event-Day-2-Puzzle-Part-2
//Description: https://adventofcode.com/2020/day/2

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//our array structures and string sizes.
#define LINE_COUNT 1000
#define STR_SIZE 50

//used for keeping count of how many times
// a given character appears in a string policy file line
int occurrCharCount = 0;

//used for keeping count of valid and invalid passwords
int validPasswordCount = 0;
int inValidPasswordCount = 0;

//Used for keeping track of invalid total count positions 
int validCountPosition = 0;
int invalidCountPosition = 0;

//*Used for determining first and second occurrence rule.
int bFirstOccurr = 0;
int bSecondOccurr = 0;

//Used for keeping track of position of string being scan.
char arryPass[STR_SIZE];

void readFile(char const* const fileName, char arrList[][STR_SIZE])
{
    FILE* file = fopen(fileName, "r");
    char line[STR_SIZE];
    int lineCount = 0;
    
    while(fgets(line, sizeof(line), file))
    {
        //printf("%s", line);
        strcpy(arrList[lineCount++],line);
    }
    fclose(file);
}

/*This function can be improved*/
void scanString(int min, int max, char *n, char *s)
{
  char *subStr = strchr(s,*n);
  int position = 0;
  
  if(subStr != NULL && occurrCharCount <= max )
  {
        occurrCharCount++;
        position = strlen(arryPass) - strlen(subStr);
        position++;
        //printf("position found=%d\n",position);
        if(min == position)
        {
           bFirstOccurr=1;
           //printf("min found\n");
        }

        if(max == position)
        {
           bSecondOccurr=1;
           //printf("max found\n");
        }
        
        //printf("subStr=%s", subStr);
        scanString(min, max, n, subStr+1);
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
   //printf("min=%d\n",minTimes);
   //printf("max=%d\n",maxTimes);   

   //Parse the Letter to search
   char *searchChar = strtok(strChar, ":");
   //printf("searchChar=%s\n",searchChar);

   //Init our char count and first/second occurrences
   occurrCharCount = 0;
   bFirstOccurr = 0;
   bSecondOccurr = 0;
   //Used for keeping track of position when we recursively do in scanString.
   strcpy(arryPass, strPass);
   scanString(minTimes, maxTimes, searchChar, strPass);
   //printf("occurrCharCount=%d\n",occurrCharCount);

   //Keep track of valid/invalid as part of part-1
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

   //keep track of valid/invalid as part of part-2
   if( (bFirstOccurr == 1 && bSecondOccurr == 0) || (bFirstOccurr == 0 && bSecondOccurr == 1))
   {
   	validCountPosition++;
        //printf("GOOD PASSWORD POSITION\n");
   }
   else
   {
        invalidCountPosition++;
	//printf("BAD PASSWORD POSITION\n");
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
    printf("\n\nValid Passwords(Part-1)=%d\n",validPasswordCount);
    printf("Invalid Passwords(Part-1)=%d\n",inValidPasswordCount);
    printf("ANSWER--->Valid Passwords with Valid Positions(Part-2)=%d\n",validCountPosition);
    printf("Invalid Passwords with Invalid Position(Part-2)=%d\n", invalidCountPosition);
    
    return 0;
}
