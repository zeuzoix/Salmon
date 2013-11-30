#include <stdio.h>
#include <llist.h>
#include <stack.h>


STACK_RET_E stack_init(STACK_HDL *phdl_stack,
                       unsigned int ui_max_size,
                       void (*pfn_delete)(void *pv_data),
                       STACK_RET_E (*pfn_debug)(void *pv_data))
{
   LLIST_HDL hdl_list = NULL;
   STACK_RET_E e_ret = eSTACK_FAILURE;
   LLIST_RET_E e_list_ret = eLLIST_FAILURE;
   LLIST_RET_E (*pfn_list_debug)(void *pv_data) = NULL;

   if(NULL == phdl_stack)
   {
      e_ret = eSTACK_INVALID_ARG;
      goto LBL_STACK_INIT_RET;
   }

   pfn_list_debug = (LLIST_RET_E (*)(void *))pfn_debug;

   e_list_ret = llist_init(&hdl_list,
                           ui_max_size,
                           pfn_delete,
                           pfn_list_debug);
   if(eLLIST_SUCCESS != e_list_ret)
   {
      e_ret = eSTACK_FAILURE;
      goto LBL_STACK_INIT_RET;
   }

   *phdl_stack = hdl_list;
   e_ret = eSTACK_SUCCESS;

LBL_STACK_INIT_RET:
   return e_ret;
}

STACK_RET_E stack_deinit(STACK_HDL *phdl_stack)
{
   STACK_RET_E e_ret = eSTACK_FAILURE;
   LLIST_RET_E e_list_ret = eLLIST_FAILURE;
   LLIST_HDL hdl_list = NULL;

   if(NULL == phdl_stack)
   {
      e_ret = eSTACK_INVALID_ARG;
      goto LBL_STACK_DEINIT_RET;
   }

   hdl_list = *phdl_stack;

   e_list_ret = llist_deinit(&hdl_list);
   if(eLLIST_SUCCESS != e_list_ret)
   {
      e_ret = eSTACK_FAILURE; 
      goto LBL_STACK_DEINIT_RET;
   }

   *phdl_stack = NULL;
   e_ret = eSTACK_SUCCESS;

LBL_STACK_DEINIT_RET:
   return e_ret;
}

STACK_RET_E stack_push(STACK_HDL hdl_stack,
                       void *pv_data)
{  
   STACK_RET_E e_ret = eSTACK_FAILURE;
   LLIST_RET_E e_list_ret = eLLIST_FAILURE;
   LLIST_HDL hdl_list = NULL;

   if((NULL == hdl_stack)||
      (NULL == pv_data))
   {
      e_ret = eSTACK_FAILURE; 
      goto LBL_STACK_PUSH_RET;
   }

   hdl_list = hdl_stack;

   e_list_ret = llist_add_next(hdl_list,
                               NULL,
                               pv_data);
   if(eLLIST_SUCCESS != e_list_ret)
   {
      if(eLLIST_FULL == e_list_ret)
      {
         e_ret = eSTACK_FULL;
      }
      else
      {
         e_ret = eSTACK_FAILURE;
      }

      goto LBL_STACK_PUSH_RET;
   }

   e_ret = eSTACK_SUCCESS;
LBL_STACK_PUSH_RET:
   return e_ret;
}


STACK_RET_E stack_pop(STACK_HDL hdl_stack,
                      void **ppv_data)
{
   STACK_RET_E e_ret = eSTACK_FAILURE;
   LLIST_RET_E e_list_ret = eLLIST_FAILURE;
   LLIST_HDL hdl_list = NULL;

   if((NULL == hdl_stack)||
      (NULL == ppv_data))
   {
      e_ret = eSTACK_INVALID_ARG;
      goto LBL_STACK_POP_RET;
   }

   hdl_list = hdl_stack;

   e_list_ret = llist_rem_next(hdl_list,
                              NULL,
                              ppv_data);
   if(eLLIST_SUCCESS != e_list_ret)
   {
      if(eLLIST_EMPTY == e_list_ret)
      {
         e_ret = eSTACK_EMPTY;
      }
      else
      {
         e_ret = eSTACK_FAILURE;
      }
      goto LBL_STACK_POP_RET;
   }

   e_ret = eSTACK_SUCCESS;
LBL_STACK_POP_RET:
   return e_ret;
}

STACK_RET_E stack_peek(STACK_HDL hdl_stack,
                       void **ppv_data)
{
   STACK_RET_E e_ret = eSTACK_FAILURE;
   LLIST_RET_E e_list_ret = eLLIST_FAILURE;
   LLIST_HDL hdl_list = NULL;
   SNODE_HDL hdl_node = NULL;

   if((NULL == hdl_stack)||
      (NULL == ppv_data))
   {
      e_ret = eSTACK_INVALID_ARG;
      goto LBL_STACK_PEEK_RET;
   }

   hdl_list = hdl_stack;

   e_list_ret = llist_head(hdl_list,
                           &hdl_node);
   if(eLLIST_SUCCESS != e_list_ret)
   {
      e_ret = eSTACK_FAILURE;
      goto LBL_STACK_PEEK_RET;
   }

   if(NULL == hdl_node)
   {
      e_ret = eSTACK_EMPTY;
      goto LBL_STACK_PEEK_RET;
   }

   e_list_ret = llist_node_data(hdl_node,
                                ppv_data); 
   if(eLLIST_SUCCESS != e_list_ret)
   {
      e_ret = eSTACK_FAILURE;
      goto LBL_STACK_PEEK_RET;
   }

   e_ret = eSTACK_SUCCESS; 
LBL_STACK_PEEK_RET:
   return e_ret;
}

STACK_RET_E stack_size(STACK_HDL hdl_stack,
                       unsigned int *pui_size)
{
   STACK_RET_E e_ret = eSTACK_FAILURE;
   LLIST_RET_E e_list_ret = eLLIST_FAILURE;
   LLIST_HDL hdl_list = NULL;

   if((NULL == hdl_stack)||
      (NULL == pui_size))
   {
      e_ret = eSTACK_INVALID_ARG;
      goto LBL_STACK_SIZE_RET;
   }

   hdl_list = hdl_stack;

   e_list_ret = llist_size(hdl_list,
                           pui_size);
   if(eLLIST_SUCCESS != e_list_ret)
   {
      e_ret = eSTACK_FAILURE;
      goto LBL_STACK_SIZE_RET;
   }

   e_ret = eSTACK_SUCCESS;
LBL_STACK_SIZE_RET:
   return e_ret;
}
