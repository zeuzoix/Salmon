#include <stdlib.h>
#include <single_linked_list.h>


int sll_init(struct sll *list, void (*free_memory)(void *data))
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


int sll_deinit(struct sll *list)
{
	int ret = -1;
	void *data = NULL;

	if(NULL == list) {
		ret = -2;
		goto END;
	}

	while (0 != sll_size(list))
	{
		if (0 == sll_remove_next(list, NULL, &data)) {
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

int sll_insert_next(struct sll *list, struct sll_node *node, void *data)
{
	int ret = -1;
	struct sll_node *new = NULL;

	if ((NULL == list) || (NULL == data)) {
		ret = -2;
		goto END;
	}

	new = (struct sll_node *)malloc(sizeof(*new));
	if (NULL == new) {
		ret = -3;
		goto END;
	}

	new->data = data;
	
	if (NULL == node) {
		/* Insert at head */
		new->next = list->head;
		list->head = new;

		if (0 == sll_size(list)) {
			list->tail = new;
		}
	}
	else {
		/* Insert after node */
		new->next = node->next;
		node->next = new;

		if (sll_tail(list) == node) {
			list->tail = new;
		}
	}

	list->size++;
	ret = 0;
END:
	return ret;
}

int sll_remove_next(struct sll *list, struct sll_node *node, void **data)
{
	int ret = -1;
	struct sll_node *temp = NULL;

	if ((NULL == list) || (NULL == data)) {
		ret = -2;
		goto END;
	}

	if (0 == sll_size(list)) {
		ret -3;
		goto END;
	}

	if (sll_tail(list) == node) {
		ret = -4;
		goto END;
	}

	if (NULL == node) {
		/*Remove the head of the list*/
		temp = list->head;
		list->head = temp->next;
		
		if (1 == sll_size(list)) {
			sll_tail(list) = NULL;
		}
	}
	else {
		/*Remove the next node*/
		temp = node->next;
		node->next = temp->next;

		if (temp == sll_tail(list)) {
			sll_tail(list) = node;
		}
	}

	*data = temp->data;
	if (NULL != temp) {
		free(temp);
		temp = NULL;
	}
	
	list->size--;
	ret = 0;
END:
	return ret;
}
