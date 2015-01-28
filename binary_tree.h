#ifndef _BINARY_TREE_H_
#define _BINARY_TREE_H_

struct bt_node {
	void *data;
	struct bt_node *left;
	struct bt_node *right;
};

struct bt {
	struct bt_node *root;
	unsigned int size;
	void (*free_memory)(void *data);
};

#define bt_node_is_eob(node) (NULL == (node))
#define bt_node_is_leaf(node) (((node)->right == NULL) && ((node)->left == NULL))
#define bt_node_data(node) ((node)->data)
#define bt_node_left(node) ((node)->left)
#define bt_node_right(node) ((node)->right)

#define bt_size(tree) ((tree)->size)
#define bt_root(tree) ((tree)->root)

int bt_init(struct bt *tree, void (*free_memory)(void *data));
int bt_destroy(struct bt *tree);
int bt_insert_left(struct bt *tree, struct bt_node *node, void *data);
int bt_insert_right(struct bt *tree, struct bt_node *node, void *data);
int bt_remove_left(struct bt *tree, struct bt_node *node);
int bt_remove_right(struct bt *tree, struct bt_node *node);
int bt_merge(struct bt *merge, struct bt *left, struct bt *right, void *data);

#endif
