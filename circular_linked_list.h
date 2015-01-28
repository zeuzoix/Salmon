#ifndef _CIRCULAR_LINKED_LIST_H_
#define _CIRCULAR_LINKED_LIST_H_

struct cll {
	struct cll_node *head;
	unsigned int size;
	void (*free_memory)(void *);
};

struct cll_node {
	void *data;
	struct cll_node *next;
};

#define cll_node_next(node) ((node)->next)
#define cll_node_data(node) ((node)->data)
#define cll_size(list) ((list)->size)
#define cll_head(list) ((list)->head)
#define cll_is_head(list, node) ((list)->head == node ? 1 : 0)

int cll_init(struct cll *list, void (*free_memory)(void *));
int cll_deinit(struct cll *list);
int cll_insert_next(struct cll *list, struct cll_node *node, void *data);
int cll_remove_next(struct cll *list, struct cll_node *node, void **data);

#endif
