#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <crtdbg.h>
#include <windows.h>
#include "ISkipList.h"

int main(void){
  FILE *Felements = NULL, *Ftime = NULL, *FnumPerLevel = NULL;

  Felements = fopen("NumOfEl.txt","w");
  Ftime = fopen("Time.txt", "w");
  FnumPerLevel = fopen("NumPerLevel.txt", "w");

  srand(time(NULL));
  int maxLevel = 32;
  double probability = 0.5;
  CreateSkipList(maxLevel, probability);

  int numOfElements = 10000;
  

  for (int j = 0; j < numOfElements; j++){

    fprintf(Felements, "%i\n", j);
    __int64 start, end, tps;
    int num = rand();

    QueryPerformanceFrequency((LARGE_INTEGER *)&tps);
    QueryPerformanceCounter((LARGE_INTEGER *)&start);
    Insert(num);
    QueryPerformanceCounter((LARGE_INTEGER *)&end);

    double result = ((double)(end - start));
    fprintf(Ftime, "%lf\n", result);
  }
    
  for (int i = 0; i < maxLevel; i++){
    int num = NumOfElementsOnLevel(i);
    fprintf(FnumPerLevel, "%i\n", num);
  }
  DestroySkipList();
  
  _CrtDumpMemoryLeaks();

  fclose(Ftime);
  fclose(Felements);
  fclose(FnumPerLevel);
  return 0;
}