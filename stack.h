#ifndef _STACK_H_
#define _STACK_H_
typedef LLIST_HDL STACK_HDL;

typedef enum _STACK_RET_E
{
   eSTACK_SUCCESS       = 0,
   eSTACK_FAILURE       = 1,
   eSTACK_INVALID_ARG   = 2,
   eSTACK_MEM_FAILURE   = 3,
   eSTACK_EMPTY         = 4,
   eSTACK_FULL          = 5,
   eSTACK_BUG           = 6

}STACK_RET_E;

STACK_RET_E stack_init(STACK_HDL *phdl_stack,
                       unsigned int ui_max_size,
                       void (*pfn_delete)(void *pv_data),
                       STACK_RET_E (*pfn_debug)(void *pv_data));

STACK_RET_E stack_deinit(STACK_HDL *phdl_stack);

STACK_RET_E stack_push(STACK_HDL hdl_stack,
                       void *pv_data);

STACK_RET_E stack_pop(STACK_HDL hdl_stack,
                      void **ppv_data);

STACK_RET_E stack_peek(STACK_HDL hdl_stack,
                       void **ppv_data);

STACK_RET_E stack_size(STACK_HDL hdl_stack,
                       unsigned int *pui_size);
#endif /*_STACK_H_*/
