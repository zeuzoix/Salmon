#ifndef _LLIST_H_
#define _LLIST_H_

typedef struct _LLIST_X *LLIST_HDL;
typedef struct _SNODE_X *SNODE_HDL;

typedef enum _LLIST_RET_E
{
   eLLIST_SUCCESS       = 0,
   eLLIST_FAILURE       = 1,
   eLLIST_INVALID_ARG   = 2,
   eLLIST_MEM_FAILURE   = 3,
   eLLIST_EMPTY         = 4,
   eLLIST_FULL          = 5,
   eLLIST_BUG           = 6

}LLIST_RET_E;

LLIST_RET_E llist_init(LLIST_HDL *phdl_list,
                       unsigned int ui_max_size,
                       void (*pfn_delete)(void *pv_data),
                       LLIST_RET_E (*pfn_debug)(void *pv_data));

LLIST_RET_E llist_deinit(LLIST_HDL *phdl_list);

LLIST_RET_E llist_head(LLIST_HDL hdl_list,
                       SNODE_HDL *phdl_node);
LLIST_RET_E llist_tail(LLIST_HDL hdl_list,
                       SNODE_HDL *phdl_node);

LLIST_RET_E llist_is_head(LLIST_HDL hdl_list,
                          SNODE_HDL hdl_node);
LLIST_RET_E llist_is_tail(LLIST_HDL hdl_list,
                          SNODE_HDL hdl_node);

LLIST_RET_E llist_add_next(LLIST_HDL hdl_list,
                           SNODE_HDL hdl_node,
                           void *pv_data);

LLIST_RET_E llist_rem_next(LLIST_HDL hdl_list,
                           SNODE_HDL hdl_node,
                           void **ppv_data);

LLIST_RET_E llist_node_next(SNODE_HDL hdl_node,
                            SNODE_HDL *phdl_node);
LLIST_RET_E llist_node_data(SNODE_HDL hdl_node,
                            void **ppv_data);

LLIST_RET_E llist_size(LLIST_HDL hdl_list,
                       unsigned int *pui_size);

LLIST_RET_E llist_print_all(LLIST_HDL hdl_list);

LLIST_RET_E llist_print_node(LLIST_HDL hdl_list,
                             SNODE_HDL hdl_node);
                        

#endif /*_LLIST_H_*/
