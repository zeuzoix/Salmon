#include <stdlib.h>
#include <circular_linked_list.h>

int cll_init(struct cll *list, void (*free_memory)(void *))
{
	int ret = -1;

	if (NULL == list) {
		ret = -2;
		goto END;
	}

	list->head = NULL;
	list->size = 0;
	list->free_memory = free_memory;

	ret = 0;
END:
	return ret;
}

int cll_deinit(struct cll *list)
{
	int ret = -1;
	void *data = NULL;

	if (NULL == list) {
		ret = -2;
		goto END;
	}

	while(0 != cll_size(list))
	{
		if(0 == cll_remove_next(list, cll_head(list), &data)) {
			if(NULL != list->free_memory) {
				list->free_memory(data);
			}
		}
		else {
			ret = -3;
			goto END;
		}
	}

	ret = 0;
END:
	return ret;
}

int cll_insert_next(struct cll *list, struct cll_node *node, void *data)
{
	int ret = -1;
	struct cll_node *new = NULL;

	if ((NULL == list) || (NULL == data)) {
		ret = -2;
		goto END;
	}

	if ((NULL == node) && (0 != cll_size(list))) ||
		ret = -3;
		goto END;
	}

	if ((NULL != node) && (0 == cll_size(list))) {
		ret = -4;
		goto END;
	}

	new = (struct cll *)malloc(sizeof(*new));
	if (NULL == new) {
		ret = -5;
		goto END;
	}

	new->data = data;
	
	if (0 == cll_size(list)) {

		new->next = new;
		list->head = new;
	}
	else {
		new->next = node->next;
		node->next = new;
	}
	
	list->size += 1;
	ret = 0;
END:
	return ret;
}

int cll_remove_next(struct cll *list, struct cll_node *node, void **data)
{
	int ret = -1;
	struct cll_node *temp = NULL;

	if ((NULL == list) || (NULL == data)) {
		ret = -2;
		goto END;
	}

	if (0 == cll_size(list)) {
		ret = -3;
		goto END;
	}

	if (1 == cll_size(list)) {
		temp = list->head;
		list->head = NULL;
	}
	else {
		temp = node->next;
		node->next = temp->next;
	}


	*data = temp->data;
	free(temp);
	list->size -= 1;

	ret = 0;
END:
	return ret;
}
