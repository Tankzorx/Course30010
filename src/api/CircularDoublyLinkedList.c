#include <stdlib.h>

#include "CircularDoublyLinkedList.h"


Node* singleton(void* data) {
  Node* node;
  node = malloc(sizeof(*node));

  node->data = data;
  node->next = node;
  node->prev = node;

  return node;
}


Node* insert(Node* tail, void* data) {
  Node* head;

  if(tail == NULL) {
    return singleton(data);
  }

  head = malloc(sizeof(*head));

  head->data = data;

  head->next = tail;
  head->prev = tail->prev;
  tail->prev->next = head;
  tail->prev = head;

  return tail;
}


Node* next(Node* tail){
  if(tail == NULL) {
    return NULL;
  }

  return tail->next;
}


Node* prev(Node* tail){
  if(tail == NULL) {
    return NULL;
  }

  return tail->prev;
}
