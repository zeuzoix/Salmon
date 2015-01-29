#include <stdlib.h>
#include <single_linked_list.h>
#include <stack.h>

int stack_push(struct sll *stack, void *data)
{
	int ret = -1;

	if ((NULL == stack) || (NULL == data)) {
		ret = -2;
		goto END;
	}

	if (0 != sll_insert_next(stack, NULL, data)) {
		ret = -3;
		goto END;
	}

	ret = 0;
END:
	return ret;
}

int stack_pop(struct sll *stack, void **data)
{
	int ret = -1;
	
	if ((NULL == stack) || (NULL == data)) {
		ret = -2;
		goto END;
	}

	if (0 != sll_remove_next(stack, NULL, data)) {
		ret = -3;
		goto END;
	}

	ret = 0;
END:
	return ret;
}
