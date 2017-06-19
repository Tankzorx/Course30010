#ifndef _DTU_CIRCULARDOUBLYLINKEDLIST_
#define _DTU_CIRCULARDOUBLYLINKEDLIST_


struct lnode {
	void* data;
	struct lnode* next;
  struct lnode* prev;
};

typedef struct lnode Node;


Node* singleton(void* data);

Node* insert(Node* tail, void* data);

Node* next(Node* tail);

Node* prev(Node* tail);


#endif /*! _DTU_CIRCULARDOUBLYLINKEDLIST_ */
