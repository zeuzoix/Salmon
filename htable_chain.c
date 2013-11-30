#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <llist.h>
#include <htable.h>

typedef struct _HTABLE_CHAIN_X
{
   unsigned int ui_num_buckets;
   unsigned int ui_num_elements;
   unsigned int ui_max_elements_per_bucket;
   LLIST_HDL *phdl_table;
   HTABLE_RET_E (*pfn_compare)(const void *pv_ele1, const void *pv_ele2);
   void (*pfn_delete)(void *pv_data);
   HTABLE_RET_E (*pfn_hash)(const void *pv_key, unsigned int *pui_hash, unsigned int ui_table_size);

}HTABLE_CHAIN_X;

HTABLE_RET_E htable_chain_init(HTABLE_CHAIN_HDL *phdl_htable,
                               unsigned int ui_num_buckets,
                               unsigned int ui_max_elements_per_bucket,
                               HTABLE_RET_E (*pfn_compare)(const void *pv_ele1, const void *pv_ele2),
                               void (*pfn_delete)(void *pv_data),
                               HTABLE_RET_E (*pfn_hash)(const void *pv_key, unsigned int *pui_hash, unsigned int ui_table_size))
{
   HTABLE_RET_E e_ret = eHTABLE_INVALID_ARG;
   HTABLE_CHAIN_X *px_htable = NULL;
   LLIST_RET_E e_llist_ret = eLLIST_FAILURE;
   LLIST_HDL *phdl_temp = NULL;
   unsigned int ui_i = 0;

   if((NULL == phdl_htable)||
      (0 == ui_num_buckets)||
      (0 == ui_max_elements_per_bucket)||
      (NULL == pfn_compare)||
      (NULL == pfn_hash))
   {
      e_ret = eHTABLE_INVALID_ARG;
      goto LBL_HTABLE_CHAIN_INIT_RET;
   }

   px_htable = (HTABLE_CHAIN_X *)malloc(sizeof(*px_htable));
   if(NULL == px_htable)
   {
      e_ret = eHTABLE_MEM_FAILURE;
      goto LBL_HTABLE_CHAIN_INIT_RET;
   }

   px_htable->ui_num_buckets = ui_num_buckets;
   px_htable->ui_num_elements = 0;
   px_htable->ui_max_elements_per_bucket = ui_max_elements_per_bucket;
   px_htable->pfn_compare = pfn_compare;
   px_htable->pfn_hash = pfn_hash;
   px_htable->pfn_delete = pfn_delete;

   px_htable->phdl_table = (LLIST_HDL *)malloc(ui_num_buckets * sizeof(*(px_htable->phdl_table)));
   if(NULL == px_htable->phdl_table)
   {
      e_ret = eHTABLE_MEM_FAILURE;
      goto LBL_HTABLE_CHAIN_INIT_RET;
   }

   phdl_temp = px_htable->phdl_table;
   for(ui_i = 0 ; ui_i < ui_num_buckets ; ui_i++)
   {
      e_llist_ret = llist_init(&phdl_temp[ui_i],
                               ui_max_elements_per_bucket,
                               pfn_delete,
                               NULL);
      if(eLLIST_SUCCESS != e_llist_ret)
      {
         e_ret = eHTABLE_FAILURE;
         goto LBL_HTABLE_CHAIN_INIT_RET;
      }
   }

   e_ret = eHTABLE_SUCCESS;
LBL_HTABLE_CHAIN_INIT_RET:
   return e_ret;
}


static HTABLE_RET_E htable_chain_private_lookup(HTABLE_CHAIN_HDL hdl_htable,
                                                LLIST_HDL *phdl_llist,
                                                SNODE_HDL *phdl_node,
                                                void **ppv_data)
{
   HTABLE_RET_E e_ret = eHTABLE_FAILURE;
   HTABLE_CHAIN_X *px_htable = NULL;
   unsigned int ui_hash_key = 0;
   LLIST_HDL hdl_llist = NULL;
   SNODE_HDL hdl_cur_node = NULL;
   SNODE_HDL hdl_next_node = NULL;
   SNODE_HDL hdl_found_node = NULL;
   LLIST_RET_E e_llist_ret = eLLIST_FAILURE;
   void *pv_node_data = NULL;

   if((NULL == hdl_htable)||
      (NULL == phdl_llist)||
      (NULL == phdl_node)||
      (NULL == ppv_data))
   {
      e_ret = eHTABLE_INVALID_ARG;
      goto LBL_HTABLE_CHAIN_PRIVATE_LOOKUP_RET;
   }

   px_htable = hdl_htable;

   e_ret = px_htable->pfn_hash(*ppv_data,
                               &ui_hash_key,
                               px_htable->ui_num_buckets); 
   if(eHTABLE_SUCCESS != e_ret)
   {
      e_ret = eHTABLE_FAILURE;
      goto LBL_HTABLE_CHAIN_PRIVATE_LOOKUP_RET;
   }

   hdl_llist = px_htable->phdl_table[ui_hash_key];
   *phdl_llist = hdl_llist;
   e_llist_ret = llist_head(hdl_llist,
                            &hdl_cur_node); 
   if(eLLIST_SUCCESS != e_llist_ret)
   {
      e_ret = eHTABLE_FAILURE;
      goto LBL_HTABLE_CHAIN_PRIVATE_LOOKUP_RET;
   }

   while(NULL != hdl_cur_node)
   { 
      e_llist_ret = llist_node_data(hdl_cur_node,
                                    &pv_node_data);
      if(eLLIST_SUCCESS != e_llist_ret)
      {
         e_ret = eHTABLE_FAILURE;
         goto LBL_HTABLE_CHAIN_PRIVATE_LOOKUP_RET;
      }
      e_ret = px_htable->pfn_compare(pv_node_data,
                                     *ppv_data);
      if(eHTABLE_DATA_SAME == e_ret)
      {
         hdl_found_node = hdl_cur_node;
         break;
      }

      e_llist_ret = llist_node_next(hdl_cur_node,
                                    &hdl_next_node);
      if(eLLIST_SUCCESS != e_llist_ret)
      {
         e_ret = eHTABLE_FAILURE;
         goto LBL_HTABLE_CHAIN_PRIVATE_LOOKUP_RET;
      }

      hdl_cur_node = hdl_next_node;
   }

   if(NULL != hdl_found_node)
   {
      *phdl_node = hdl_found_node;
      *ppv_data = pv_node_data;
      e_ret = eHTABLE_EXIST;
   }
   else
   {
      *phdl_node = NULL;
      *ppv_data = NULL;
      e_ret = eHTABLE_NOT_EXIST;
   }


LBL_HTABLE_CHAIN_PRIVATE_LOOKUP_RET:
   return e_ret;
}

HTABLE_RET_E htable_chain_insert(HTABLE_CHAIN_HDL hdl_htable,
                                 void *pv_data)
{
   HTABLE_RET_E e_ret = eHTABLE_FAILURE;
   LLIST_HDL hdl_llist = NULL;
   SNODE_HDL hdl_node = NULL;
   LLIST_RET_E e_llist_ret = eLLIST_FAILURE;
   void *pv_data_ref = NULL;

   if((NULL == hdl_htable)||
      (NULL == pv_data))
   {
      e_ret = eHTABLE_INVALID_ARG;
      goto LBL_HTABLE_CHAIN_INSERT_RET;
   }

   pv_data_ref = pv_data;

   e_ret = htable_chain_private_lookup(hdl_htable,
                                       &hdl_llist,
                                       &hdl_node,
                                       &pv_data_ref);
   if(eHTABLE_NOT_EXIST != e_ret)
   {
      if(eHTABLE_EXIST != e_ret)
      {
         e_ret = eHTABLE_FAILURE;
      }
      goto LBL_HTABLE_CHAIN_INSERT_RET;
   }

   e_llist_ret = llist_add_next(hdl_llist,
                                NULL,
                                pv_data);
   if(eLLIST_SUCCESS != e_llist_ret)
   {
      e_ret = eHTABLE_FAILURE;
   }
   else
   {
      e_ret = eHTABLE_SUCCESS;
   }
   
LBL_HTABLE_CHAIN_INSERT_RET:
   return e_ret;
}

HTABLE_RET_E htable_chain_remove(HTABLE_CHAIN_HDL hdl_htable,
                                 void **ppv_data)
{
   HTABLE_RET_E e_ret = eHTABLE_FAILURE;
   LLIST_HDL hdl_llist = NULL;
   SNODE_HDL hdl_node = NULL;
   SNODE_HDL hdl_cur_node = NULL;
   SNODE_HDL hdl_next_node = NULL;
   LLIST_RET_E e_llist_ret = eLLIST_FAILURE;
   void *pv_data_ref = NULL;

   if((NULL == hdl_htable)||
      (NULL == ppv_data))
   {
      e_ret = eHTABLE_INVALID_ARG;
      goto LBL_HTABLE_CHAIN_REMOVE_RET;
   }

   pv_data_ref = *ppv_data;

   e_ret = htable_chain_private_lookup(hdl_htable,
                                       &hdl_llist,
                                       &hdl_node,
                                       &pv_data_ref);
   if(eHTABLE_EXIST != e_ret)
   {
      if(eHTABLE_NOT_EXIST != e_ret)
      {
         e_ret = eHTABLE_FAILURE;
      }
      goto LBL_HTABLE_CHAIN_REMOVE_RET;
   }

   e_llist_ret = llist_head(hdl_llist,
                            &hdl_cur_node);
   if(eLLIST_SUCCESS != e_llist_ret)
   {
      e_ret = eHTABLE_FAILURE;
      goto LBL_HTABLE_CHAIN_REMOVE_RET;
   }

   hdl_next_node = NULL;
   while(NULL != hdl_cur_node)
   {
      if(hdl_cur_node == hdl_node)
      {
         break;
      }

      e_llist_ret = llist_node_next(hdl_cur_node,
                                    &hdl_next_node);
      if(eLLIST_SUCCESS != e_llist_ret)
      {
         e_ret = eHTABLE_FAILURE;
         goto LBL_HTABLE_CHAIN_REMOVE_RET;
      }

      hdl_cur_node = hdl_next_node;
   }

   e_llist_ret = llist_rem_next(hdl_llist,
                                hdl_next_node,
                                &pv_data_ref);
   if(eLLIST_SUCCESS != e_llist_ret)
   {
      e_ret = eHTABLE_FAILURE;
      goto LBL_HTABLE_CHAIN_REMOVE_RET;
   }

   *ppv_data = pv_data_ref;
   e_ret = eHTABLE_SUCCESS;

LBL_HTABLE_CHAIN_REMOVE_RET:
   return e_ret;
}
