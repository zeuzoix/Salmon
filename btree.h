#ifndef _BITREE_H_
#define _BITREE_H_

struct btree_node {
	void *data;
	struct btree_node *left;
	struct btree_node *right;
};

struct btree {
	struct btree_node *root;
	int size;
	void (*destroy)(void *data);

};

void btree_init(struct btree *tree, void (*destroy)(void *data));

void btree_destroy(struct btree *tree);

int btree_insert_left(struct btree *tree, struct btree_node *node,
				void *data);

int btree_insert_right(struct btree *tree, struct btree_node *node,
				void *data);

void btree_remove_left(struct btree *tree, struct btree_node *node);

void btree_remove_right(struct btree *tree, struct btree_node *node);

int btree_merge(struct btree *merge, struct btree *left,
			struct btree *right, void *data);

#define btree_size(tree) ((tree)->size)

#define btree_root(tree) ((tree)->root)

#define btree_node_is_eob(node) (NULL == (node))

#define btree_node_is_leaf(node) (((node)->right == NULL) && ((node)->left == NULL))

#define btree_node_data(node) ((node)->data)

#define btree_node_left(node) ((node)->left)

#define btree_node_right(node) ((node)->right)


#endif
