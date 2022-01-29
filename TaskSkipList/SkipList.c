#include <stdlib.h>
#include "SkipList.h"

static skipListElement *s_listHead;
static int s_curLevel; 
static int s_maxLevel;
static double s_probability;

void _initMasNodeByNULL(node **masNode);
skipListElement* _createElement(int levels, int key);
void _destroyElement(skipListElement *element);
void _copySkipListElemt(skipListElement *from, skipListElement *to);
int _randomLevel();


void CreateSkipList(int maxLevel, double probability){
  s_maxLevel = maxLevel;
  s_curLevel = 0;
  s_probability = probability;

  s_listHead = _createElement(maxLevel, -1);
}

myBool Search(int searchKey){
  skipListElement *elIter = s_listHead;
  myBool isKeyInList = true;

  for (int i = s_curLevel; i >= 0; i--){
    while (elIter->masNode[i].next != NULL && elIter->masNode[i].next->key < searchKey){
      elIter = elIter->masNode[i].next;
    }

    if (i == 0){
      if (elIter->masNode[i].next == NULL || elIter->masNode[i].next->key != searchKey){
        isKeyInList = false;
      }
    }
  }

  return isKeyInList;
}

int NumOfElementsOnLevel(int level){
  skipListElement *iterEl = s_listHead;
  int counterLevel = 0;
  while (iterEl->masNode[level].next != NULL){
    iterEl = iterEl->masNode[level].next;
    counterLevel++;
  }
  return counterLevel;
}

void Insert(int key){
  node *masIter = s_listHead->masNode;
  node **update = (node**)malloc(sizeof(node*) * s_maxLevel);
  myBool isKeyInList = true;

  for (int i = s_curLevel; i >= 0; i--){
    while (masIter[i].next != NULL && masIter[i].next->key < key){
      masIter = masIter[i].next->masNode;
    }
    update[i] = &(masIter[i]);
  
    if (i == 0){
      if (masIter[i].next == NULL || masIter[i].next->key != key){
        isKeyInList = false;
      }
    }
  }

  if (!isKeyInList){
    int newLevel = _randomLevel();
    if (newLevel > s_curLevel){
      for (int i = s_curLevel + 1; i < newLevel; i++){
        update[i] = &(s_listHead->masNode[i]);
      }
      s_curLevel = newLevel - 1;
    }
   
    skipListElement *newEl = _createElement(newLevel, key);

    for (int i = 0; i < newLevel; i++){
      newEl->masNode[i].next = update[i]->next;
      update[i]->next = newEl;
    }
  }
  
  free(update);
  return;
}

void Delete(int key){
  node **update = (node**)malloc(sizeof(node*) * s_maxLevel);
  _initMasNodeByNULL(update);

  skipListElement *elIter = s_listHead;
  myBool isKeyInList = true;
  
  for (int i = s_curLevel; i >= 0; i--){
    while (elIter->masNode[i].next != NULL && elIter->masNode[i].next->key < key){
      elIter = elIter->masNode[i].next;
    }
    update[i] = &(elIter->masNode[i]);

    if (i == 0){
      if (elIter->masNode[i].next == NULL || elIter->masNode[i].next->key != key){
        isKeyInList = false;
      }
    }
  }

  if (isKeyInList){
    elIter = elIter->masNode[0].next;

    for (int i = 0; i <= s_curLevel; i++){
      if (update[i] != NULL && update[i]->next == elIter){
        update[i]->next = elIter->masNode[i].next;
      }
    }

    _destroyElement(elIter);

    while (s_listHead->masNode[s_curLevel].next == NULL && s_curLevel > 0){
      s_curLevel -= 1;
    }
    
  }
  free(update);
}

void DestroySkipList(){
  skipListElement *elIter = s_listHead;
  skipListElement *nextEl = NULL;

  while (elIter != NULL){
    nextEl = elIter->masNode[0].next;
    _destroyElement(elIter);
    elIter = nextEl;
  }
}



void _initMasNodeByNULL(node **masNode){
  for (int i = 0; i < s_maxLevel; i++){
    masNode[i] = NULL;
  }
}

void _destroyElement(skipListElement *element){
  free(element->masNode);
  free(element);
}

skipListElement* _createElement(int levels, int key){
  skipListElement *newEl = (skipListElement*)malloc(sizeof(skipListElement));
  
  newEl->masNode = (node*)malloc(levels * sizeof(node));
  newEl->key = key;

  for (int i = 0; i < levels; i++){
    newEl->masNode[i].next = NULL;
  }

  return newEl;
}

int _randomLevel(){
  int resultLevel = 1;

  double randNum = rand() / (double)RAND_MAX;

  while (randNum  < s_probability && resultLevel < s_maxLevel){
    resultLevel++;
    randNum = rand() / (double)RAND_MAX;
  }
  return resultLevel;
}