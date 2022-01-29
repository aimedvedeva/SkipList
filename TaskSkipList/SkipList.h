#pragma once

typedef enum {
  false,
  true,
}myBool;

struct tag_skipListElement;

typedef struct tag_node{
  struct tag_skipListElement *next;
}node;

typedef struct tag_skipListElement{
  node *masNode;
  int key;
}skipListElement;

