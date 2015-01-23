#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <llist.h>
#include <stack.h>
#include <sort.h>
#define MAX_STACK_SIZE 100

typedef struct _INDEX_PAIR_X
{
   unsigned int ui_low;
   unsigned int ui_high;

}INDEX_PAIR_X;

static SORT_RET_E sort_quick_compare_unsigned_int(const void *pv_ele1, const void *pv_ele2);

static STACK_RET_E sort_quick_index_pair_debug(void *pv_data);

static STACK_RET_E sort_quick_partition(void *pv_array,
                                        unsigned int ui_ele_size,
                                        unsigned int ui_low_index,
                                        unsigned int ui_high_index,
                                        SORT_DIRECTION_E e_dir,
                                        SORT_RET_E (*pfn_compare)(const void *pv_ele1, const void *pv_ele2),
                                        unsigned int *pui_partition_index);

static SORT_RET_E sort_quick_partition_median(unsigned int ui_low_index,
                                              unsigned int ui_high_index,
                                              unsigned int *pui_median_index);

static SORT_RET_E sort_quick_swap_ele(void *pv_ele1, 
                                      void *pv_ele2,
                                      unsigned int ui_ele_size);

SORT_RET_E sort_quick(void *pv_array,
                      unsigned int ui_ele_num,
                      unsigned int ui_ele_size,
                      SORT_DIRECTION_E e_dir,
                      SORT_RET_E (*pfn_compare)(const void *pv_ele1, const void *pv_ele2))
{
   SORT_RET_E e_ret = eSORT_FAILURE;
   STACK_RET_E e_stack_ret = eSTACK_FAILURE;
   STACK_HDL hdl_stack = NULL;
   INDEX_PAIR_X *px_indices = NULL; 
   void *pv_data = NULL;
   unsigned int ui_stack_size = 0;
   unsigned int ui_partition_index = 0;
   unsigned int ui_low_index = 0;
   unsigned int ui_high_index = 0;

   if((NULL == pv_array)||
      (0 == ui_ele_num)||
      (0 == ui_ele_size)||
      (NULL == pfn_compare))
   {
      e_ret = eSORT_INVALID_ARG;
      goto LBL_SORT_QUICK_RET;
   }

   px_indices  = (INDEX_PAIR_X *)malloc(sizeof(*px_indices));
   if(NULL == px_indices)
   {
      e_ret = eSORT_MEM_FAILURE;
      goto LBL_SORT_QUICK_RET;
   }

   px_indices->ui_low = 0;
   px_indices->ui_high = ui_ele_num - 1;

/*TBD:Improve implementation of MAX_STACK_SIZE*/
   e_stack_ret = stack_init(&hdl_stack,
                            MAX_STACK_SIZE,
                            free,
                            sort_quick_index_pair_debug);
   if(eSTACK_SUCCESS != e_stack_ret)
   {
      e_ret = eSORT_FAILURE;
      goto LBL_SORT_QUICK_RET;
   }

   e_stack_ret = stack_push(hdl_stack,
                            px_indices);
   if(eSTACK_SUCCESS != e_stack_ret)
   {
      e_ret = eSORT_FAILURE;
      goto LBL_SORT_QUICK_RET;
   }
   ui_stack_size = 1;

   while(0 != ui_stack_size)
   {
      pv_data = NULL;
      e_stack_ret = stack_pop(hdl_stack,
                              &pv_data);
      if((eSTACK_SUCCESS != e_stack_ret)||
         (NULL == pv_data))
      {
         e_ret = eSORT_FAILURE;
         goto LBL_SORT_QUICK_RET;
      }
      px_indices = (INDEX_PAIR_X *)pv_data;
      e_ret = sort_quick_partition(pv_array,
                                   ui_ele_size,
                                   px_indices->ui_low,
                                   px_indices->ui_high,
                                   e_dir,
                                   pfn_compare,
                                   &ui_partition_index);
      if(eSORT_SUCCESS != e_ret)
      {
         e_ret = eSORT_FAILURE;
         goto LBL_SORT_QUICK_RET;
      }

      ui_low_index = px_indices->ui_low;
      ui_high_index = px_indices->ui_high;

      if(NULL != px_indices)
      {
         free(px_indices);
         px_indices = NULL;
      }

      if((ui_partition_index - ui_low_index) > 1)
      {
         px_indices  = (INDEX_PAIR_X *)malloc(sizeof(*px_indices));
         if(NULL == px_indices)
         {
            e_ret = eSORT_MEM_FAILURE;
            goto LBL_SORT_QUICK_RET;
         }
         px_indices->ui_low = ui_low_index;
         px_indices->ui_high = ui_partition_index -1;

         e_stack_ret = stack_push(hdl_stack,
                                  px_indices);
         if(eSTACK_SUCCESS != e_stack_ret)
         {
            e_ret = eSORT_FAILURE;
            goto LBL_SORT_QUICK_RET;
         }
      }

      if((ui_high_index - ui_partition_index ) > 1)
      {
         px_indices  = (INDEX_PAIR_X *)malloc(sizeof(*px_indices));
         if(NULL == px_indices)
         {
            e_ret = eSORT_MEM_FAILURE;
            goto LBL_SORT_QUICK_RET;
         }
         px_indices->ui_low =  ui_partition_index +1;
         px_indices->ui_high = ui_high_index;

         e_stack_ret = stack_push(hdl_stack,
                                  px_indices);
         if(eSTACK_SUCCESS != e_stack_ret)
         {
            e_ret = eSORT_FAILURE;
            goto LBL_SORT_QUICK_RET;
         }
      }
      e_stack_ret = stack_size(hdl_stack,
                               &ui_stack_size);
      if(eSTACK_SUCCESS != e_stack_ret)
      {
         e_ret = eSORT_FAILURE;
         goto LBL_SORT_QUICK_RET;
      }
   }
   
   e_ret = eSORT_SUCCESS;
LBL_SORT_QUICK_RET:
   if(NULL != hdl_stack)
   {
      e_ret = stack_deinit(&hdl_stack);
      hdl_stack = NULL;
   }
   return e_ret;
}

static STACK_RET_E sort_quick_partition(void *pv_array,
                                        unsigned int ui_ele_size,
                                        unsigned int ui_low_index,
                                        unsigned int ui_high_index,
                                        SORT_DIRECTION_E e_dir,
                                        SORT_RET_E (*pfn_compare)(const void *pv_ele1, const void *pv_ele2),
                                        unsigned int *pui_partition_index)
{
   SORT_RET_E e_ret = eSORT_FAILURE;
   SORT_RET_E e_comp_ret = eSORT_FAILURE;
   STACK_RET_E e_stack_ret = eSTACK_FAILURE;
   unsigned int ui_key_index = 0;
   unsigned int ui_up = 0;
   unsigned int ui_down = 0;
   void *pv_ele1 = NULL;
   void *pv_ele2 = NULL;
   void *pv_key = NULL;
   void *pv_dest = NULL;
   unsigned char uc_down_flag = 0;
   unsigned char uc_up_flag = 0;
   SORT_RET_E e_down = eSORT_FAILURE;
   SORT_RET_E e_up = eSORT_FAILURE;

   if((NULL == pv_array)||
      (0 == ui_ele_size)||
      (NULL == pfn_compare)||
      (0 == pui_partition_index))
   {
      e_ret = eSORT_INVALID_ARG;
      goto LBL_SORT_QUICK_PARTITION_RET;
   }

   pv_key = malloc(ui_ele_size);
   if(NULL == pv_key)
   {
      e_ret = eSORT_MEM_FAILURE;
      goto LBL_SORT_QUICK_PARTITION_RET;
   }

   e_ret = sort_quick_partition_median(ui_low_index,
                                       ui_high_index,
                                       &ui_key_index);
   if(eSORT_SUCCESS != e_ret)
   {
      e_ret = eSORT_FAILURE;
      goto LBL_SORT_QUICK_PARTITION_RET;
   }

   (void)memmove(pv_key, 
                 (char *)pv_array + (ui_key_index * ui_ele_size),
                 ui_ele_size);
   ui_down = ui_low_index;
   ui_up = ui_high_index;

   if(eSORT_DESCENDING == e_dir)
   {
      e_down = eSORT_GREATER;
      e_up = eSORT_LESSER;
   }
   else if(eSORT_ASCENDING == e_dir)
   {
      e_down = eSORT_LESSER;
      e_up = eSORT_GREATER;
   }
   else
   {
      e_ret = eSORT_FAILURE;
      goto LBL_SORT_QUICK_PARTITION_RET;
   }
   ui_down--;
   ui_up++;

   while(1)
   {

      do
      {
         ui_down++;

         pv_ele1 = (char *)pv_array + (ui_ele_size * ui_down);
         e_comp_ret = pfn_compare(pv_key,
                                  pv_ele1);
         if((eSORT_LESSER != e_comp_ret)&&
            (eSORT_GREATER != e_comp_ret)&&
            (eSORT_EQUAL != e_comp_ret))
         {
            e_ret = eSORT_FAILURE;
            goto LBL_SORT_QUICK_PARTITION_RET;
         }

      }while(e_down == e_comp_ret);

      do
      {
         ui_up--;

         pv_ele2 = (char *)pv_array + (ui_ele_size*ui_up);
         e_comp_ret = pfn_compare(pv_key,
                                  pv_ele2);
         if((eSORT_LESSER != e_comp_ret)&&
            (eSORT_GREATER != e_comp_ret)&&
            (eSORT_EQUAL != e_comp_ret))
         {
            e_ret = eSORT_FAILURE;
            goto LBL_SORT_QUICK_PARTITION_RET;
         }

      }while(e_up == e_comp_ret);
#if 0

      uc_down_flag = 0;
      while((0 == uc_down_flag)&&
            (ui_down != ui_high_index))
      {
         pv_ele1 = (char *)pv_array + (ui_ele_size * ui_down);
         e_comp_ret = pfn_compare(pv_key,
                                  pv_ele1);
         if(e_down == e_comp_ret)
         {
            uc_down_flag = 0;
            ui_down++;
         }
         else if((e_up == e_comp_ret)||
                (eSORT_EQUAL == e_comp_ret))
         {
            uc_down_flag = 1;
         }
         else
         {
            e_ret = eSORT_FAILURE;
            goto LBL_SORT_QUICK_PARTITION_RET;
         }
      }

      uc_up_flag = 0;
      while((0 == uc_up_flag)&&
            (ui_up != ui_low_index))
      {
         pv_ele2 = (char *)pv_array + (ui_ele_size*ui_up);
         e_comp_ret = pfn_compare(pv_key,
                                  pv_ele2);
         if(e_up == e_comp_ret)
         {
            uc_up_flag = 0;
            ui_up--;
         }
         else if((e_down == e_comp_ret)||
                 (eSORT_EQUAL == e_comp_ret))
         {
            uc_up_flag = 1;
         }
         else
         {
            e_ret = eSORT_FAILURE;
            goto LBL_SORT_QUICK_PARTITION_RET;
         }
      }
#endif

      if(ui_down < ui_up)
      {
         e_ret = sort_quick_swap_ele(pv_ele1,
                                     pv_ele2,
                                     ui_ele_size);
         if(eSORT_SUCCESS != e_ret)
         {
            e_ret = eSORT_FAILURE;
            goto LBL_SORT_QUICK_PARTITION_RET;
         }
      }
      else
      {
         break;
      }
   }

   *pui_partition_index = ui_up;
   e_ret = eSORT_SUCCESS;
   
LBL_SORT_QUICK_PARTITION_RET:
   return e_ret;
}

static SORT_RET_E sort_quick_partition_median(unsigned int ui_low_index,
                                              unsigned int ui_high_index,
                                              unsigned int *pui_median_index)
{
   unsigned int uia_key_index[3] = {0};
   unsigned int ui_rand = 0;
   unsigned int ui_i = 0;
   SORT_RET_E e_ret = eSORT_FAILURE;

   if(NULL == pui_median_index)
   {
      e_ret = eSORT_INVALID_ARG;
      goto LBL_SORT_QUICK_PARTITION_MEDIAN_RET;
   }

   for(ui_i = 0 ; ui_i < 3 ; ui_i++) 
   {
      ui_rand = (unsigned int)rand();
      /*Rand % difference gives a random offset in the range hence must be added to the lower index*/
      uia_key_index[ui_i] = ui_low_index + (ui_rand % (ui_high_index - ui_low_index + 1));
   }

   e_ret = sort_insertion(uia_key_index, 
                          3, 
                          sizeof(uia_key_index[0]), 
                          eSORT_ASCENDING, 
                          sort_quick_compare_unsigned_int);
   if(eSORT_SUCCESS != e_ret)
   {
      e_ret = eSORT_FAILURE;
      goto LBL_SORT_QUICK_PARTITION_MEDIAN_RET;
   }

   *pui_median_index = uia_key_index[1];
   e_ret = eSORT_SUCCESS;
LBL_SORT_QUICK_PARTITION_MEDIAN_RET:
   return e_ret;
}

static SORT_RET_E sort_quick_swap_ele(void *pv_ele1, 
                                      void *pv_ele2,
                                      unsigned int ui_ele_size)
{
   void *pv_temp = NULL;
   void *pv_dest = NULL;
   SORT_RET_E e_ret = eSORT_FAILURE;

   if((NULL == pv_ele1)||
      (NULL == pv_ele2)||
      (0 == ui_ele_size))
   {
      e_ret = eSORT_INVALID_ARG;
      goto LBL_SORT_QUICK_SWAP_ELE_RET;
   }

   pv_temp = malloc(ui_ele_size);
   if(NULL == pv_temp)
   {
      e_ret = eSORT_MEM_FAILURE;
      goto LBL_SORT_QUICK_SWAP_ELE_RET;
   }

   pv_dest = memmove(pv_temp,
                     pv_ele2,
                     ui_ele_size);
   if(pv_dest != pv_temp)
   {
      e_ret = eSORT_FAILURE;
      goto LBL_SORT_QUICK_SWAP_ELE_RET;
   }

   pv_dest = memmove(pv_ele2,
                     pv_ele1,
                     ui_ele_size);
   if(pv_dest != pv_ele2)
   {
      e_ret = eSORT_FAILURE;
      goto LBL_SORT_QUICK_SWAP_ELE_RET;
   }

   pv_dest = memmove(pv_ele1,
                     pv_temp,
                     ui_ele_size);
   if(pv_dest != pv_ele1)
   {
      e_ret = eSORT_FAILURE;
      goto LBL_SORT_QUICK_SWAP_ELE_RET;
   }

   e_ret = eSORT_SUCCESS;
LBL_SORT_QUICK_SWAP_ELE_RET:
   if(NULL != pv_temp)
   {
      free(pv_temp);
      pv_temp = NULL;
   }
   return e_ret;
}

static SORT_RET_E sort_quick_compare_unsigned_int(const void *pv_ele1, const void *pv_ele2)
{
   SORT_RET_E e_ret = eSORT_FAILURE;
   unsigned int *pui_ele1 = NULL;
   unsigned int *pui_ele2 = NULL;

   if((NULL == pv_ele1)||
      (NULL == pv_ele2))
   {
      e_ret = eSORT_INVALID_ARG;
      goto LBL_COMPARE_UNSIGNED_INT_RET;
   }

   pui_ele1 = (unsigned int *)pv_ele1;
   pui_ele2 = (unsigned int *)pv_ele2;

   if(*pui_ele1 > *pui_ele2)
   {
      e_ret = eSORT_LESSER;
   }
   else if(*pui_ele1 < *pui_ele2)
   {
      e_ret = eSORT_GREATER;
   }
   else
   {
      e_ret = eSORT_EQUAL;
   }

LBL_COMPARE_UNSIGNED_INT_RET:
   return e_ret;
}

static STACK_RET_E sort_quick_index_pair_debug(void *pv_data)
{
   STACK_RET_E e_ret = eSTACK_FAILURE;
   INDEX_PAIR_X *px_index_pair = NULL;

   if(NULL == pv_data)
   {
      e_ret = eSTACK_INVALID_ARG;
      goto LBL_SORT_QUICK_INDEX_PAIR_DEBUG_RET;
   }

   px_index_pair = (INDEX_PAIR_X *)pv_data;
   fprintf(stdout,"{%u,%u}",px_index_pair->ui_low, px_index_pair->ui_high);

   e_ret = eSTACK_SUCCESS;
LBL_SORT_QUICK_INDEX_PAIR_DEBUG_RET:
   return e_ret;
}
