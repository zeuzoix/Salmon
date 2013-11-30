#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sort.h>

SORT_RET_E sort_insertion(void *pv_array, 
                          unsigned int ui_ele_num,
                          unsigned int ui_ele_size,
                          SORT_DIRECTION_E e_dir,
                          SORT_RET_E (*pfn_compare)(const void *pv_ele1, const void *pv_ele2))
{
   SORT_RET_E e_ret = eSORT_FAILURE;
   SORT_RET_E e_comp_ret = eSORT_FAILURE;
   SORT_RET_E e_direction = eSORT_FAILURE;
   void *pv_ele_key = NULL;
   void *pv_ret = NULL;
   void *pv_src = NULL;
   void *pv_dst = NULL;
   unsigned int ui_i = 0;
   unsigned int ui_j = 0;

   if((NULL == pv_array)||
      (1 >= ui_ele_num)||
      (0 == ui_ele_size)||
      (NULL == pfn_compare))
   {
      e_ret = eSORT_INVALID_ARG;
      goto LBL_SORT_INSERTION_RET;
   }

   pv_ele_key = malloc(ui_ele_size);
   if(NULL == pv_ele_key)
   {
      e_ret = eSORT_MEM_FAILURE;
      goto LBL_SORT_INSERTION_RET;
   }

   if(eSORT_DESCENDING == e_dir)
   {
      e_direction = eSORT_LESSER;
   }
   else
   {
      e_direction = eSORT_GREATER;
   }
   
   for(ui_i = 1 ; ui_i < ui_ele_num ; ui_i++)
   {
      pv_ret = memmove(pv_ele_key, 
                      ((char *)pv_array + (ui_i * ui_ele_size)), 
                      ui_ele_size);
      if(pv_ret != pv_ele_key)
      {
         e_ret = eSORT_FAILURE;
         goto LBL_SORT_INSERTION_RET;
      }

      for(ui_j = (ui_i - 1) ; ui_j != (unsigned int)(0 - 1) ; ui_j--)
      {
         e_comp_ret = pfn_compare(pv_ele_key,
                                  ((char *)pv_array + (ui_j * ui_ele_size)));
         if(e_direction == e_comp_ret)
         {
            pv_dst = (char *)pv_array + ((ui_j + 1) * ui_ele_size);
            pv_src = (char *)pv_array + (ui_j * ui_ele_size);
            pv_ret = memmove(pv_dst,
                             pv_src,
                             ui_ele_size);
            if(pv_ret != pv_dst) 
            {
               e_ret = eSORT_FAILURE;
               goto LBL_SORT_INSERTION_RET;
            }
         }
         else
         {
            break;
         }
      }

      pv_dst = (char *)pv_array + ((ui_j + 1) * ui_ele_size);
      pv_src = pv_ele_key;
      if(pv_src != pv_dst)
      {
         pv_ret = memmove(pv_dst,
               pv_src,
               ui_ele_size);
         if(pv_ret != pv_dst)
         {
            e_ret = eSORT_FAILURE;
            goto LBL_SORT_INSERTION_RET;
         }
      }
   }

   e_ret = eSORT_SUCCESS;
LBL_SORT_INSERTION_RET:
   if(NULL != pv_ele_key)
   {
      free(pv_ele_key);
      pv_ele_key = NULL;
   }

   return e_ret; 

}
