#include <stdio.h>
#include <stdlib.h>
#include <llist.h>

typedef struct _SNODE_X
{
   void *pv_data;
   struct _SNODE_X *px_next;

}SNODE_X;

typedef struct _LLIST_X
{
   unsigned int ui_size;
   unsigned int ui_max_size;

   SNODE_X *px_head;
   SNODE_X *px_tail;
   
   void (*pfn_delete)(void *pv_data);
   LLIST_RET_E (*pfn_debug)(void *pv_data);

}LLIST_X;

LLIST_RET_E llist_init(LLIST_HDL *phdl_list,
                       unsigned int ui_max_size,
                       void (*pfn_delete)(void *pv_data),
                       LLIST_RET_E (*pfn_debug)(void *pv_data))
{
   LLIST_X *px_list = NULL;
   LLIST_RET_E e_ret = eLLIST_FAILURE;

   if(NULL == phdl_list)
   {
      e_ret = eLLIST_INVALID_ARG; 
      goto LBL_LLIST_INIT_RET;
   }

   px_list = (LLIST_X *)malloc(sizeof(*px_list));
   if(NULL == px_list)
   {
      e_ret = eLLIST_MEM_FAILURE; 
      goto LBL_LLIST_INIT_RET;
   }

   px_list->ui_size = 0;
   px_list->ui_max_size = ui_max_size;
   px_list->px_head = NULL;
   px_list->px_tail = NULL;
   px_list->pfn_delete = pfn_delete;
   px_list->pfn_debug = pfn_debug;
   *phdl_list = px_list;

   e_ret = eLLIST_SUCCESS; 

LBL_LLIST_INIT_RET:
   return e_ret;
}
                     
LLIST_RET_E llist_deinit(LLIST_HDL *phdl_list)
{
   LLIST_X *px_list = NULL;
   SNODE_X *px_snode = NULL;
   LLIST_RET_E e_ret = eLLIST_FAILURE;
   unsigned int ui_i = 0;

   if((NULL == phdl_list)||
      (NULL == *phdl_list))
   {
      e_ret = eLLIST_INVALID_ARG; 
      goto LBL_LLIST_DEINIT_RET;
   }

   px_list = *phdl_list;

   for(ui_i = 0 ; ui_i < px_list->ui_size ; ui_i++) 
   {
      if(NULL == px_list->px_head)
      {
         e_ret = eLLIST_FAILURE; 
         goto LBL_LLIST_DEINIT_RET;
      }

      px_snode = px_list->px_head;
      px_list->px_head = px_list->px_head->px_next;
      if((NULL != px_snode->pv_data)&&
         (NULL != px_list->pfn_delete))
      {
         px_list->pfn_delete(px_snode->pv_data);
      }

      free(px_snode);
   }
   px_list->pfn_delete = NULL;

   px_list->px_head = NULL;
   px_list->px_tail = NULL;
   px_list->ui_size = 0;

   free(px_list);
   *phdl_list = NULL;

   e_ret = eLLIST_SUCCESS; 

LBL_LLIST_DEINIT_RET:
   return e_ret;
}

LLIST_RET_E llist_head(LLIST_HDL hdl_list,
                       SNODE_HDL *phdl_node)
{
   LLIST_X *px_list = NULL;
   LLIST_RET_E e_ret = eLLIST_FAILURE;
   SNODE_X *px_snode = NULL;

   if((NULL == hdl_list)||
      (NULL == phdl_node))
   {
      e_ret = eLLIST_INVALID_ARG; 
      goto LBL_LLIST_HEAD_RET;
   }

   px_list = hdl_list;
   *phdl_node = px_list->px_head;

   e_ret = eLLIST_SUCCESS; 

LBL_LLIST_HEAD_RET:
   return e_ret;
}

LLIST_RET_E llist_tail(LLIST_HDL hdl_list,
                       SNODE_HDL *phdl_node)
{
   LLIST_X *px_list = NULL;
   LLIST_RET_E e_ret = eLLIST_FAILURE;
   SNODE_X *px_snode = NULL;

   if((NULL == hdl_list)||
      (NULL == phdl_node))
   {
      e_ret = eLLIST_INVALID_ARG; 
      goto LBL_LLIST_TAIL_RET;
   }

   px_list = hdl_list;
   *phdl_node = px_list->px_tail;

   e_ret = eLLIST_SUCCESS; 

LBL_LLIST_TAIL_RET:
   return e_ret;
}

LLIST_RET_E llist_is_head(LLIST_HDL hdl_list,
                          SNODE_HDL hdl_node)
{
   LLIST_RET_E e_ret = eLLIST_FAILURE;
   LLIST_X *px_list = NULL;
   SNODE_X *px_node = NULL;

   if((NULL == hdl_list)||
      (NULL == hdl_node))
   {
      e_ret = eLLIST_INVALID_ARG; 
      goto LBL_LLIST_IS_HEAD_RET;
   }

   px_list = hdl_list;
   px_node = hdl_node;

   if(px_node == px_list->px_head)
   {
      e_ret = eLLIST_SUCCESS;
   }
   else
   {
      e_ret = eLLIST_FAILURE;
   }
   
LBL_LLIST_IS_HEAD_RET:
   return e_ret;
}

LLIST_RET_E llist_is_tail(LLIST_HDL hdl_list,
                          SNODE_HDL hdl_node)
{
   LLIST_RET_E e_ret = eLLIST_FAILURE;
   LLIST_X *px_list = NULL;
   SNODE_X *px_node = NULL;

   if((NULL == hdl_list)||
      (NULL == hdl_node))
   {
      e_ret = eLLIST_INVALID_ARG; 
      goto LBL_LLIST_IS_TAIL_RET;
   }

   px_list = hdl_list;
   px_node = hdl_node;

   if(px_node == px_list->px_tail)
   {
      e_ret = eLLIST_SUCCESS;
   }
   else
   {
      e_ret = eLLIST_FAILURE;
   }

LBL_LLIST_IS_TAIL_RET:
   return e_ret;
}


LLIST_RET_E llist_add_next(LLIST_HDL hdl_list,
                           SNODE_HDL hdl_node,
                           void *pv_data)
{
   LLIST_X *px_list = NULL;
   SNODE_X *px_node = NULL;
   SNODE_X *px_node_new = NULL;
   LLIST_RET_E e_ret = eLLIST_FAILURE;

   if((NULL == hdl_list)||
      (NULL == pv_data))
   {
      e_ret = eLLIST_INVALID_ARG;
      goto LBL_LLIST_ADD_NEXT_RET;
   }

   px_list = hdl_list;
   px_node = hdl_node;

   if(px_list->ui_size == px_list->ui_max_size)
   {
      e_ret = eLLIST_FULL;
      goto LBL_LLIST_ADD_NEXT_RET;
   }

   px_node_new = (SNODE_X *)malloc(sizeof(*px_node_new));
   if(NULL == px_node_new)
   {
      e_ret = eLLIST_MEM_FAILURE;
      goto LBL_LLIST_ADD_NEXT_RET;
   }

   px_node_new->pv_data = pv_data;

   if(NULL == px_node)
   {
      px_node_new->px_next = px_list->px_head;
      px_list->px_head = px_node_new;

   }/*Insert at head*/
   else
   {
      px_node_new->px_next = px_node->px_next;
      px_node->px_next = px_node_new;
   }/*Insert after node*/

   if(px_list->px_tail == px_node)
   {
      px_list->px_tail = px_node_new;
   }/*Update the tail if the new node is the tail node*/

   px_list->ui_size += 1;
   e_ret = eLLIST_SUCCESS;

LBL_LLIST_ADD_NEXT_RET:
   return e_ret;
}

LLIST_RET_E llist_rem_next(LLIST_HDL hdl_list,
                           SNODE_HDL hdl_node,
                           void **ppv_data)
{
   LLIST_RET_E e_ret = eLLIST_FAILURE;
   LLIST_X *px_list = NULL;
   SNODE_X *px_node = NULL;
   SNODE_X *px_temp = NULL;

   if((NULL == hdl_list)||
      (NULL == ppv_data))
   {
      e_ret = eLLIST_INVALID_ARG;
      goto LBL_LLIST_REM_NEXT_RET;
   }

   px_list = hdl_list;
   px_node = hdl_node;

   if(0 == px_list->ui_size)
   {
      e_ret = eLLIST_EMPTY;
      goto LBL_LLIST_REM_NEXT_RET;
   }

   *ppv_data = NULL;
   if(px_node == px_list->px_tail)
   {
      e_ret = eLLIST_FAILURE;
      goto LBL_LLIST_REM_NEXT_RET;
   }

   if(NULL == px_node)
   {
      px_temp = px_list->px_head;
      px_list->px_head = px_list->px_head->px_next;
   }/*Remove Head*/
   else
   {
      px_temp = px_node->px_next;
      px_node->px_next = px_node->px_next->px_next;
   }/*Remove next node*/

   *ppv_data = px_temp->pv_data;
   if(NULL != px_temp)
   {
      free(px_temp);
      px_temp = NULL;
   }

   px_list->ui_size -= 1;
   e_ret = eLLIST_SUCCESS;

LBL_LLIST_REM_NEXT_RET:
   return e_ret;   
}

LLIST_RET_E llist_node_next(SNODE_HDL hdl_node,
                            SNODE_HDL *phdl_node)
{
   LLIST_RET_E e_ret = eLLIST_FAILURE;
   SNODE_X *px_node = NULL;
   SNODE_X *px_node_next = NULL;

   if((NULL == hdl_node)||
      (NULL == phdl_node))
   {
      e_ret = eLLIST_INVALID_ARG;
      goto LBL_LLIST_NODE_NEXT_RET;
   }
   
   px_node = hdl_node;
   px_node_next = px_node->px_next;

   *phdl_node = px_node_next;
   e_ret = eLLIST_SUCCESS;

LBL_LLIST_NODE_NEXT_RET:
   return e_ret;
}

LLIST_RET_E llist_node_data(SNODE_HDL hdl_node,
                            void **ppv_data)
{
   LLIST_RET_E e_ret = eLLIST_FAILURE;
   SNODE_X *px_node = NULL;

   if((NULL == hdl_node)||
      (NULL == ppv_data))
   {
      e_ret = eLLIST_INVALID_ARG;
      goto LBL_LLIST_NODE_DATA_RET;
   }

   px_node = hdl_node;
   *ppv_data = px_node->pv_data;

   e_ret = eLLIST_SUCCESS;
LBL_LLIST_NODE_DATA_RET:
   return e_ret;
}

LLIST_RET_E llist_size(LLIST_HDL hdl_list,
                        unsigned int *pui_size)
{
   LLIST_RET_E e_ret = eLLIST_FAILURE;
   LLIST_X *px_list = NULL;

   if((NULL == hdl_list)||
      (NULL == pui_size))
   {
      e_ret = eLLIST_INVALID_ARG;
      goto LBL_LLIST_SIZE_RET;
   }

   px_list = hdl_list;
   *pui_size = px_list->ui_size;

   e_ret = eLLIST_SUCCESS;
LBL_LLIST_SIZE_RET:
   return e_ret;
}

LLIST_RET_E llist_print_all(LLIST_HDL hdl_list)
{
   LLIST_RET_E e_ret = eLLIST_FAILURE;
   LLIST_RET_E e_ret_1 = eLLIST_FAILURE;
   LLIST_X *px_list = NULL;
   SNODE_X *px_node = NULL;
   unsigned int ui_i = 0;

   if(NULL == hdl_list)
   {
      e_ret = eLLIST_INVALID_ARG;
      goto LBL_LLIST_PRINT_ALL_RET;
   }

   px_list = hdl_list;
   px_node = px_list->px_head;
   for(ui_i = 0 ; ui_i < px_list->ui_max_size ; ui_i++)
   {
      if(NULL == px_node)
      {
         e_ret = eLLIST_BUG;
         goto LBL_LLIST_PRINT_ALL_RET;
      }
      fprintf(stdout, "Node %u:\n", ui_i);
      (void)llist_print_node(px_list,
                             px_node);
      fprintf(stdout, "\n");
      px_node = px_node->px_next;
   }

   e_ret = eLLIST_SUCCESS;
LBL_LLIST_PRINT_ALL_RET:
   return e_ret;
}

LLIST_RET_E llist_print_node(LLIST_HDL hdl_list,
                             SNODE_HDL hdl_node)
{
   LLIST_RET_E e_ret = eLLIST_FAILURE;
   LLIST_RET_E e_ret_1 = eLLIST_FAILURE;
   LLIST_X *px_list = NULL;
   SNODE_X *px_node = NULL;

   if((NULL == hdl_list)||
      (NULL == hdl_node))
   {
      e_ret = eLLIST_INVALID_ARG;
      goto LBL_LLIST_PRINT_NODE_RET;
   }

   px_list = hdl_list;
   px_node = hdl_node;

   if(NULL == px_list->pfn_debug)
   {
      e_ret = eLLIST_FAILURE;
      goto LBL_LLIST_PRINT_NODE_RET;
   }

   e_ret_1 = px_list->pfn_debug(px_node->pv_data);
   if(eLLIST_SUCCESS != e_ret_1)
   {
      fprintf(stderr,"Debug failed\n");
      e_ret = eLLIST_FAILURE;
      goto LBL_LLIST_PRINT_NODE_RET;
   }

   e_ret = eLLIST_SUCCESS;

LBL_LLIST_PRINT_NODE_RET:
   return e_ret;
}
