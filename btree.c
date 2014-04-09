#include <string.h>
#include <btree.h>

void btree_init(struct btree *tree, void (*destroy)(void *data))
{
	if(NULL == tree)
		goto LBL_RET;

	/*Initialize the binary tree*/
	tree->root = NULL;
	tree->size = 0;
	tree->destroy = destroy;

LBL_RET:
	return;
}

void btree_destroy(struct btree *tree)
{
	if(NULL == tree)
		goto LBL_RET;

	/*Remove all nodes from the tree*/
	btree_remove_left(tree, NULL);

	/*Reset the tree structure*/
	memset(tree, 0, sizeof(*tree));

LBL_RET:
	return
}

int btree_node_insert_left(struct btree *tree, struct btree_node *node, 
				void *data)
{
	int ret = -1;
	struct btree_node **position = NULL;

	if((NULL == tree)||(NULL == data)) {
		ret = -1;
		goto LBL_RET;
	}

	if(NULL == node) {
		if(0 != btree_size(tree)) {
			ret = -2;
			goto LBL_RET;
		}
		position = &tree->root:
	}
	else {
		if(!btree_node_is_eob(node->left)) {
			ret = -3;
			goto LBL_RET;
		}
		position = &node->left
	}

	*position = malloc(sizeof(**position));
	if(NULL == *position) {
		ret = -4;
		goto LBL_RET;
	}

	(*position)->data = data;
	(*position)->left = NULL;
	(*position)->right = NULL;
	tree->size += 1;

	ret = 0;

LBL_RET:
	return ret;
}

int btree_node_insert_right(struct btree *tree, struct btree_node *node,
				void *data)
{
	int ret = -1;
	struct btree_node **position = NULL;

	if((NULL == tree)||(NULL == data)) {
		ret = -1;
		goto LBL_RET;
	}

	if(NULL == node) {
		if(0 != btree_size(tree)) {
			ret = -2;
			goto LBL_RET;
		}
		position = &tree->root:
	}
	else {
		if(!btree_node_is_eob(node->left)) {
			ret = -3;
			goto LBL_RET;
		}
		position = &node->left
	}

	*position = malloc(sizeof(**position));
	if(NULL == *position) {
		ret = -4;
		goto LBL_RET;
	}

	(*position)->data = data;
	(*position)->left = NULL;
	(*position)->right = NULL;
	tree->size += 1;

	ret = 0;

LBL_RET:
	return ret;
}

void btree_remove_left(struct btree *tree, struct btree_node *node)
{
	struct btree_node **position = NULL;

	if((NULL == tree) || (0 == btree_size(tree)))
		goto LBL_RET;

	if(NULL == node) 
		*position = &tree->root;
	else
		*position = &node->left;

	if(NULL != *position) {
		btree_remove_left(tree, (*position));
		btree_remove_right(tree, (*position));

		if((NULL != tree->destroy) && (NULL != (*position)->data))
			tree->destroy((*position)->data);

		free(*position);
		*position = NULL;
		tree->size -= 1;
	}

LBL_RET:
	return;
}


void btree_remove_right(struct btree *tree, struct btree_node *node)
{
	struct btree_node **position = NULL;

	if((NULL == tree) || (0 == btree_size(tree)))
		goto LBL_RET;

	if(NULL == node)
		*position = &tree->root;
	else
		*position = &node->right;

	if(NULL != *position) {
		btree_remove_left(tree, (*position));
		btree_remove_right(tree, (*position));

		if((NULL != tree->destroy) && (NULL != (*position)->data))
			tree->destroy((*position)->data);

		free(*position);
		*position = NULL;
		tree->size -= 1;
	}

LBL_RET:
	return;
}

int btree_merge(struct btree *merge, struct btree *left, 
			struct btree *right, void *data)
{

}
