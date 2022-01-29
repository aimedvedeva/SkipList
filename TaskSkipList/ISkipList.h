#pragma once

typedef enum {
  false,
  true,
}myBool;

void CreateSkipList(int maxLevel, double probability);
int NumOfElementsOnLevel(int level);
myBool Search(int searchKey);
void Insert(int key);
void Delete(int key);
void DestroySkipList();