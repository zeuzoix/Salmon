#include <stdlib.h>
#include <string.h>
#include <binary_tree.h>

int bt_init(struct bt *tree, void (*free_memory)(void *data))
{
	int ret = -1;

	if (NULL == tree) {
		ret = -1;
		goto END;
	}

	/*Initialize the binary tree*/
	tree->root = NULL;
	tree->size = 0;
	tree->free_memory = free_memory;

	ret = 0;
END:
	return ret;
}

int bt_destroy(struct bt *tree)
{
	int ret = -1;

	if (NULL == tree) {
		ret = -2;
		goto END;
	}

	/*Remove all nodes from the tree*/
	if (0 != bt_remove_left(tree, NULL)) {
		ret = -3;
		goto END;
	}

	/*Reset the tree structure*/
	memset(tree, 0, sizeof(*tree));

	ret = 0;
END:
	return ret;
}

int bt_insert_left(struct bt *tree, struct bt_node *node, void *data)
{
	int ret = -1;
	struct bt_node **position = NULL;

	if ((NULL == tree) || (NULL == data)) {
		ret = -1;
		goto END;
	}

	if (NULL == node) {
		if (0 != bt_size(tree)) {
			ret = -2;
			goto END;
		}
		position = &tree->root;
	}
	else {
		if(!bt_node_is_eob(node->left)) {
			ret = -3;
			goto END;
		}
		position = &node->left;
	}

	*position = malloc(sizeof(**position));
	if (NULL == *position) {
		ret = -4;
		goto END;
	}

	(*position)->data = data;
	(*position)->left = NULL;
	(*position)->right = NULL;
	tree->size += 1;

	ret = 0;
END:
	return ret;
}

int bt_insert_right(struct bt *tree, struct bt_node *node, void *data)
{
	int ret = -1;
	struct bt_node **position = NULL;

	if ((NULL == tree) || (NULL == data)) {
		ret = -1;
		goto END;
	}

	if(NULL == node) {
		if(0 != bt_size(tree)) {
			ret = -2;
			goto END;
		}
		position = &tree->root;
	}
	else {
		if(!bt_node_is_eob(node->right)) {
			ret = -3;
			goto END;
		}
		position = &node->right;
	}

	*position = malloc(sizeof(**position));
	if (NULL == *position) {
		ret = -4;
		goto END;
	}

	(*position)->data = data;
	(*position)->left = NULL;
	(*position)->right = NULL;
	tree->size += 1;

	ret = 0;
END:
	return ret;
}

int bt_remove_left(struct bt *tree, struct bt_node *node)
{
	int ret = -1;
	struct bt_node **position = NULL;

	if ((NULL == tree) || (0 == bt_size(tree))) {
		ret = -2;
		goto END;
	}

	if (NULL == node)
		position = &tree->root;
	else
		position = &node->left;

	if (NULL != *position) {
		if (0 != bt_remove_left(tree, (*position))) {
			ret = -3;
		}
		if (0 != bt_remove_right(tree, (*position))) {
			ret = -4;
		}

		if (NULL != tree->free_memory) {
			if (NULL != (*position)->data)
				tree->free_memory((*position)->data);
			else {
				ret = -5;
				goto END;
			}
		}

		free(*position);
		*position = NULL;
		tree->size -= 1;
	}

	ret = 0;
END:
	return ret;
}


int bt_remove_right(struct bt *tree, struct bt_node *node)
{
	int ret = -1; 
	struct bt_node **position = NULL;

	if (NULL == tree) {
		ret = -2;
		goto END;
	}

	if (NULL == node)
		position = &tree->root;
	else
		position = &node->right;

	if (NULL != *position) {
		if (0 != bt_remove_left(tree, *position)) {
			ret = -3;
			goto END;
		}

		if (0 != bt_remove_right(tree, *position)) {
			ret = -4;
			goto END;
		}

		if (NULL != tree->free_memory) {
			if (NULL != (*position)->data)
				tree->free_memory((*position)->data);
			else {
				ret = -5;
				goto END;
			}
		}

		free(*position);
		*position = NULL;
		tree->size -= 1;

	}
	ret = 0;
END:
	return ret;
}

int bt_merge(struct bt *merge, struct bt *left, struct bt *right, void *data)
{
	int ret = -1;

	if ((NULL == merge) || (NULL == left) ||
			(NULL == right) || (NULL == data)) {
		ret = -1;
		goto END;
	}

	if(left->free_memory != right->free_memory) {
		ret = -2;
		goto END;
	}

	bt_init(merge, left->free_memory);

	if(0 != bt_insert_left(merge, NULL, data)) {
		ret = -3;
		goto END;
	}

	bt_node_left(bt_root(merge)) = bt_root(left);
	bt_root(left) = NULL;
	bt_node_right(bt_root(merge)) = bt_root(right);
	bt_root(right) = NULL;

	bt_size(merge) = bt_size(left) + bt_size(right);
	bt_size(left) = 0;
	bt_size(right) = 0;

	ret = 0;
END:
	return ret;
}
