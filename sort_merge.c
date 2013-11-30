#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sort.h>

static SORT_RET_E sort_merge_array(void *pv_array,
                                   void *pv_array_spare,
                                   unsigned int ui_low,
                                   unsigned int ui_high,
                                   unsigned int ui_ele_size,
                                   SORT_DIRECTION_E e_dir,
                                   SORT_RET_E (*pfn_compare)(const void *pv_ele1, const void *pv_ele2));

static SORT_RET_E sort_merge_array_merge(void *pv_array,
                                         void *pv_array_spare,
                                         unsigned int ui_low,
                                         unsigned int ui_mid,
                                         unsigned int ui_high,
                                         unsigned int ui_ele_size,
                              SORT_DIRECTION_E e_dir,
                              SORT_RET_E (*pfn_compare)(const void *pv_ele1, const void *pv_ele2));

SORT_RET_E sort_merge(void *pv_array, 
                      unsigned int ui_ele_num,
                      unsigned int ui_ele_size,
                      SORT_DIRECTION_E e_dir,
                      SORT_RET_E (*pfn_compare)(const void *pv_ele1, const void *pv_ele2))
{
   SORT_RET_E e_ret = eSORT_FAILURE;
   unsigned int ui_low = 0;
   unsigned int ui_high = 0;
   void *pv_temp_array = NULL;

   if((NULL == pv_array)||
      (1 >= ui_ele_num)||
      (0 == ui_ele_size)||
      (NULL == pfn_compare))
   {
      e_ret = eSORT_INVALID_ARG;
      goto LBL_SORT_MERGE_RET;
   }

   ui_low = 0;
   ui_high = ui_ele_num - 1; 

   pv_temp_array = malloc(ui_ele_num * ui_ele_size);
   if(NULL == pv_temp_array)
   {
      e_ret = eSORT_MEM_FAILURE;
      goto LBL_SORT_MERGE_RET;
   }
   
   e_ret = sort_merge_array(pv_array,
                            pv_temp_array,
                            ui_low,
                            ui_high,
                            ui_ele_size,
                            e_dir,
                            pfn_compare);

LBL_SORT_MERGE_RET:
   return e_ret;

}

static SORT_RET_E sort_merge_array(void *pv_array,
                                   void *pv_array_spare,
                                   unsigned int ui_low,
                                   unsigned int ui_high,
                                   unsigned int ui_ele_size,
                                   SORT_DIRECTION_E e_dir,
                                   SORT_RET_E (*pfn_compare)(const void *pv_ele1, const void *pv_ele2))
{
   SORT_RET_E e_ret = eSORT_FAILURE;
   unsigned int ui_mid = 0;

   if((NULL == pv_array)||
      (NULL == pv_array_spare)||
      (0 == ui_ele_size)||
      (NULL == pfn_compare))
   {
      e_ret = eSORT_INVALID_ARG;
      goto LBL_SORT_MERGE_ARRAY_RET;
   }

   if(ui_low < ui_high)
   {
      ui_mid = ui_low + ((ui_high - ui_low) / 2);

      e_ret = sort_merge_array(pv_array,
                               pv_array_spare,
                               ui_low,
                               ui_mid,
                               ui_ele_size,
                               e_dir,
                               pfn_compare);
      if(eSORT_SUCCESS != e_ret)
      {
         goto LBL_SORT_MERGE_ARRAY_RET;
      }

      e_ret = sort_merge_array(pv_array,
                               pv_array_spare,
                               (ui_mid + 1),
                               ui_high,
                               ui_ele_size,
                               e_dir,
                               pfn_compare);
      if(eSORT_SUCCESS != e_ret)
      {
         goto LBL_SORT_MERGE_ARRAY_RET;
      }

      e_ret = sort_merge_array_merge(pv_array,
                                     pv_array_spare,
                                     ui_low,
                                     ui_mid,
                                     ui_high,
                                     ui_ele_size,
                                     e_dir,
                                     pfn_compare);
      if(eSORT_SUCCESS != e_ret)
      {
         goto LBL_SORT_MERGE_ARRAY_RET;
      }
   }

   e_ret = eSORT_SUCCESS;
LBL_SORT_MERGE_ARRAY_RET:
   return e_ret;
}


static SORT_RET_E sort_merge_array_merge(void *pv_array,
                                         void *pv_array_spare,
                                         unsigned int ui_low,
                                         unsigned int ui_mid,
                                         unsigned int ui_high,
                                         unsigned int ui_ele_size,
                                         SORT_DIRECTION_E e_dir,
                                         SORT_RET_E (*pfn_compare)(const void *pv_ele1, const void *pv_ele2))
{
   SORT_RET_E e_ret = eSORT_FAILURE;
   SORT_RET_E e_comp_ret = eSORT_FAILURE;
   SORT_RET_E e_order_ret = eSORT_FAILURE;
   unsigned int ui_i = 0;
   unsigned int ui_j = 0;
   unsigned int ui_index = 0;
   void *pv_dest = NULL;

   if((NULL == pv_array)||
      (NULL == pv_array_spare)||
      (0 == ui_ele_size)||
      (NULL == pfn_compare))
   {
      e_ret = eSORT_INVALID_ARG;
      goto LBL_SORT_MERGE_ARRAY_MERGE_RET;
   }
      
   if(eSORT_ASCENDING == e_dir)
   {
      e_order_ret = eSORT_LESSER;
   }
   else
   {
      e_order_ret = eSORT_GREATER;
   }

   ui_i = ui_low;
   ui_j = ui_mid + 1;

   while((ui_i <= ui_mid)||
         (ui_j <= ui_high)) 
   {
      if(ui_i > ui_mid)
      {
         while(ui_j <= ui_high)
         {
            pv_dest = memmove((char *)pv_array_spare + (ui_index*ui_ele_size),
                              (char *)pv_array + (ui_j*ui_ele_size),
                              ui_ele_size);
            if(((char *)pv_array_spare + (ui_index*ui_ele_size)) != pv_dest)
            {
               e_ret = eSORT_MEM_FAILURE;
               goto LBL_SORT_MERGE_ARRAY_MERGE_RET;
            }

            ui_index++;
            ui_j++;
         }
         break;
      }

      if(ui_j > ui_high)
      {
         while(ui_i <= ui_mid)
         {
            pv_dest = memmove((char *)pv_array_spare + (ui_index*ui_ele_size),
                              (char *)pv_array + (ui_i*ui_ele_size),
                              ui_ele_size);
            if(((char *)pv_array_spare + (ui_index*ui_ele_size)) != pv_dest)
            {
               e_ret = eSORT_MEM_FAILURE;
               goto LBL_SORT_MERGE_ARRAY_MERGE_RET;
            }

            ui_index++;
            ui_i++;
         }
         break;
      }

      e_comp_ret = pfn_compare((char *)pv_array + (ui_i*ui_ele_size),
                               (char *)pv_array + (ui_j*ui_ele_size));
      if((eSORT_LESSER != e_comp_ret)&&
         (eSORT_GREATER != e_comp_ret)&&
         (eSORT_EQUAL != e_comp_ret))
      {
         e_ret = eSORT_BUG;
         goto LBL_SORT_MERGE_ARRAY_MERGE_RET;
      }

      if(e_comp_ret != e_order_ret)
      {
         pv_dest = memmove((char *)pv_array_spare + (ui_index*ui_ele_size),
                           (char *)pv_array + (ui_i*ui_ele_size),
                           ui_ele_size);
         if(((char *)pv_array_spare + (ui_index*ui_ele_size)) != pv_dest)
         {
            e_ret = eSORT_MEM_FAILURE;
            goto LBL_SORT_MERGE_ARRAY_MERGE_RET;
         }
         ui_i++;
      }
      else
      {
         pv_dest = memmove((char *)pv_array_spare + (ui_index*ui_ele_size),
                           (char *)pv_array + (ui_j*ui_ele_size),
                           ui_ele_size);
         if(((char *)pv_array_spare + (ui_index*ui_ele_size)) != pv_dest)
         {
            e_ret = eSORT_MEM_FAILURE;
            goto LBL_SORT_MERGE_ARRAY_MERGE_RET;
         }
         ui_j++;
      }

      ui_index++;
   }

   pv_dest = memmove((char *)pv_array + (ui_low*ui_ele_size),
                     pv_array_spare,
                     (ui_ele_size*(ui_high - ui_low + 1)));
   if((char *)pv_array + (ui_low*ui_ele_size) != pv_dest)
   {
      e_ret = eSORT_MEM_FAILURE;
      goto LBL_SORT_MERGE_ARRAY_MERGE_RET;
   }

   e_ret = eSORT_SUCCESS;
LBL_SORT_MERGE_ARRAY_MERGE_RET:
   return e_ret;

}
