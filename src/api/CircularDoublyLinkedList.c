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


void insert(Node* tail, void* data) {
  Node* head;
  head = malloc(sizeof(*head));

  head->data = data;

  head->next = tail;
  head->prev = tail->prev;
  tail->prev->next = head;
  tail->prev = head;
}
