#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sort.h>

SORT_RET_E sort_counting(int *pi_data,
                         unsigned int ui_data_sz,
                         int i_min_data,
                         int i_max_data)
{
   SORT_RET_E e_ret = eSORT_FAILURE;
   unsigned int *pui_counting_arr = NULL;
   unsigned int ui_counting_sz = 0;
   unsigned int ui_i = 0;
   int *pi_data_temp = NULL;
   void *pv_dest = NULL;

   if((NULL == pi_data)||
      (0 == ui_data_sz))
   {
      e_ret = eSORT_INVALID_ARG;
      goto LBL_SORT_COUNTING_RET;
   }

   ui_counting_sz = i_max_data - i_min_data + 1;
   pui_counting_arr = (unsigned int *)calloc(ui_counting_sz, sizeof(unsigned int));
   if(NULL == pui_counting_arr)
   {
      e_ret = eSORT_MEM_FAILURE;
      goto LBL_SORT_COUNTING_RET;
   }

   pi_data_temp = (int *)calloc(ui_data_sz, sizeof(*pi_data));
   if(NULL == pi_data_temp)
   {
      e_ret = eSORT_MEM_FAILURE;
      goto LBL_SORT_COUNTING_RET;
   }

   for(ui_i = 0 ; ui_i < ui_data_sz ; ui_i++)
   {
      pui_counting_arr[pi_data[ui_i] - i_min_data] += 1;
   }

   for(ui_i = 1 ; ui_i < ui_counting_sz ; ui_i++)
   {
      pui_counting_arr[ui_i] += pui_counting_arr[ui_i - 1];
   }

   for(ui_i = (ui_data_sz - 1) ; ui_i != (0 - 1) ; ui_i--)
   {
      pi_data_temp[pui_counting_arr[pi_data[ui_i] - i_min_data] - 1] = pi_data[ui_i];
      pui_counting_arr[pi_data[ui_i] - i_min_data] -= 1;
   }

   pv_dest = memcpy(pi_data, pi_data_temp, ui_data_sz * sizeof(*pi_data));
   if(pv_dest != pi_data)
   {
      e_ret = eSORT_MEM_FAILURE;
      goto LBL_SORT_COUNTING_RET;
   }

   e_ret = eSORT_SUCCESS;
LBL_SORT_COUNTING_RET:
   return e_ret;
}
#if 0
SORT_RET_E sort_counting(int *pi_data,
                         unsigned int ui_data_sz,
                         int i_min_data,
                         int i_max_data)
{
   SORT_RET_E e_ret = eSORT_FAILURE;
   unsigned int *pui_counting_arr = NULL;
   unsigned int ui_counting_sz = 0;
   unsigned int ui_i = 0;
   unsigned int ui_j = 0;

   if((NULL == pi_data)||
      (0 == ui_data_sz))
   {
      e_ret = eSORT_INVALID_ARG;
      goto LBL_SORT_COUNTING_RET;
   }

   ui_counting_sz = i_max_data - i_min_data + 1;
   pui_counting_arr = (unsigned int *)calloc(ui_counting_sz,sizeof(unsigned int));
   if(NULL == pui_counting_arr)
   {
      e_ret = eSORT_MEM_FAILURE;
      goto LBL_SORT_COUNTING_RET;
   }

   for(ui_i = 0 ; ui_i < ui_data_sz ; ui_i++)
   {
      pui_counting_arr[pi_data[ui_i] - i_min_data] += 1;
   }

   for(ui_i = 0, ui_j = 0 ; ui_i < ui_counting_sz ; ui_i++)
   {
      while(0 != pui_counting_arr[ui_i])
      {
         pi_data[ui_j] = ui_i + i_min_data;
         pui_counting_arr[ui_i]--;
         ui_j++;
      }

   }

   e_ret = eSORT_SUCCESS;
LBL_SORT_COUNTING_RET:
   return e_ret;
}
#endif
