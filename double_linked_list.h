#ifndef _DOUBLE_LINKED_LIST_H_
#define _DOUBLE_LINKED_LIST_H_

struct dll_node {
   void *data;
   struct dll_node *next;
   struct dll_node *prev;
};

struct dll {
   struct dll_node *head;
   struct dll_node *tail;
   unsigned int size;
   void (*free_memory)(void *);
};

#define dll_size(list) ((list)->size)
#define dll_head(list) ((list)->head)
#define dll_tail(list) ((list)->tail)
#define dll_is_tail(list, node) ((node) == (list)->tail? 1: 0)
#define dll_is_head(list, node) ((node) == (list)->head? 1: 0)
#define dll_node_next(node) ((node)->next)
#define dll_node_prev(node) ((node)->prev)
#define dll_node_data(node) ((node)->data)

int dll_init(struct dll *list, void (*free_memory)(void *));
int dll_deinit(struct dll *list);
int dll_insert_next(struct dll *list, struct dll_node *node, void *data);
int dll_insert_prev(struct dll *list, struct dll_node *node, void *data);
int dll_remove(struct dll *list, struct dll_node *node, void **data);

#endif
