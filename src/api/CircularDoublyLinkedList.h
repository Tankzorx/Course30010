#ifndef _DTU_CIRCULARDOUBLYLINKEDLIST_
#define _DTU_CIRCULARDOUBLYLINKEDLIST_


struct lnode {
	void* data;
	struct lnode* next;
  struct lnode* prev;
};

typedef struct lnode Node;


Node* singleton(void* data);

void insert(Node* tail, void* data);


#endif /*! _DTU_CIRCULARDOUBLYLINKEDLIST_ */
