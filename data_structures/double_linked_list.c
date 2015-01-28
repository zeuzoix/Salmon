#include <stdlib.h>
#include <double_linked_list.h>


int dll_init(struct dll *list, void (*free_memory)(void *data))
{
	int ret = -1;

	if (NULL == list) {
		ret = -2;
		goto END;
	}

	list->head = NULL;
	list->tail = NULL; 
	list->size = 0; 
	list->free_memory = free_memory;

	ret = 0;
END:
	return ret;
}


int dll_deinit(struct dll *list)
{
	int ret = -1;
	void *data = NULL;

	if(NULL == list) {
		ret = -2;
		goto END;
	}

	while (0 != dll_size(list))
	{
		if (0 == dll_remove(list, dll_head(list), &data)) {
			if (NULL != list->free_memory) 
				list->free_memory(data);
		}
		else {
			ret = -3;
			goto END;
		}
	}

	list->head = NULL; 
	list->tail = NULL; 
	list->size = 0; 
	list->free_memory = NULL;

	ret = 0;
END:
	return ret;
}

int dll_insert_next(struct dll *list, struct dll_node *node, void *data)
{
	int ret = -1;
	struct dll_node *new = NULL;

	if ((NULL == list) || (NULL == data)) {
		ret = -2;
		goto END;
	}

	if ((NULL == node) && (0 != dll_size(list))) {
		ret = -3;
		goto END;
	}

	new = (struct dll_node *)malloc(sizeof(*new));
	if (NULL == new) {
		ret = -4;
		goto END;
	}

	new->data = data;

	if (0 == dll_size(list)) {
		new->next = NULL;
		new->prev = NULL;
		list->head = new;
		list->tail = new;
	}
	else {
		new->next = node->next;
		new->prev = node;

		if (dll_tail(list) == node) {
			list->tail = new;
		}
		else {
			node->next->prev = new;
		}
		node->next = new;
	}

	list->size++;
	ret = 0;
END:
	return ret;
}

int dll_insert_prev(struct dll *list, struct dll_node *node, void *data)
{
	int ret = -1;
	struct dll_node *new = NULL;

	if ((NULL == list) || (NULL == data)) {
		ret = -2;
		goto END;
	}

	if ((NULL == node) && (0 != dll_size(list))) {
		ret = -3;
		goto END;
	}

	new = (struct dll_node *)malloc(sizeof(*new));
	if (NULL == new) {
		ret = -4;
		goto END;
	}

	new->data = data;
	
	if (0 == dll_size(list)) {
		new->next = NULL;
		new->prev = NULL;
		list->head = new;
		list->tail = new;
	}
	else {
		new->next = node;
		new->prev = node->prev;

		if(dll_head(list) == node) {
			list->head = new;
		}
		else {
			node->prev->next = new;
		}
		node->prev = new;
	}

	list->size++;
	ret = 0;
END:
	return ret;
}

int dll_remove(struct dll *list, struct dll_node *node, void **data)
{
	int ret = -1;
	struct dll_node *temp = NULL;

	if ((NULL == list) || (NULL == node) || (NULL == data)) {
		ret = -2;
		goto END;
	}

	if (0 == dll_size(list)) {
		ret = -3;
		goto END;
	}

	temp = node;
	*data = node->data;

	if (dll_head(list) != node) {
		node->prev->next = node->next;
	}
	else {
		list->head = node->next;
	}

	if (dll_tail(list) != node) {
		node->next->prev = node->prev;
	}
	else {
		list->tail = node->prev;
	}

	if (NULL != temp) {
		free(temp);
		temp = NULL;
	}

	list->size++;
	ret = 0;
			
END:
	return ret;
}
