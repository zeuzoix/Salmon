#ifndef _SINGLE_LINKED_LIST_H_
#define _SINGLE_LINKED_LIST_H_

struct sll {
   struct sll_node *head;
   struct sll_node *tail;
   int size;
   void (*free_memory)(void *);

};

struct sll_node {
   void *data;
   struct sll_node *next;
};

#define sll_node_next(node) ((node)->next)
#define sll_node_data(node) ((node)->data)

#define sll_head(list) ((list)->head)
#define sll_tail(list) ((list)->tail)
#define sll_size(list) ((list)->size)
#define sll_is_head(list, node) ((node) == (list)->head? 1 : 0)
#define sll_is_tail(list, node) ((node) == (list)->tail? 1 : 0)

int sll_init(struct sll *list, void (*free_memory)(void *));
int sll_deinit(struct sll *list);
int sll_insert_next(struct sll *list, struct sll_node *node, void *data);
int sll_remove_next(struct sll *list, struct sll_node *node, void **data);


#endif
