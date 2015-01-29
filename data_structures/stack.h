#ifndef _STACK_H_
#define _STACK_H_


#define stack_init sll_init 
#define stack_deinit sll_deinit

int stack_push(struct sll *stack, void *data);
int stack_pop(struct sll *stack, void **data);

#define stack_peek(stack) ((NULL == (stack)->head) ? NULL : (stack)->head->data)
#define stack_size sll_size

#endif
