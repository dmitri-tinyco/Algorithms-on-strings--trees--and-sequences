typedef struct Node {
  void *data;
  struct Node *next;
} Node;
Node *ll_create(void *data);
void release(Node *start);
Node *insert_after(Node *n, void *data);
int ll_for_each(Node *n, int(*func)(void*));
