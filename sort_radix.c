#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sort.h>

/*
1>Allocate memory for counting positive and negative
1>Allocate memory for counting positive and negative
2>Iterate over number of digits
3>Iterate over array list
4>Extract digit starting from least significant digit
5>Increment counting array
6>Set counting to reflect indice positions in the array
7>
i
*/
SORT_RET_E sort_radix(int *pi_data,
                      unsigned int ui_data_sz,
                      unsigned int ui_num_digits,
                      unsigned int ui_radix)
{
   SORT_RET_E e_ret = eSORT_FAILURE;
   int *pi_data_temp = NULL;
   unsigned int *pui_counting = NULL;
   unsigned int ui_i = 0;
   unsigned int ui_j = 0;
   unsigned int ui_counting_sz = 1;
   unsigned int ui_radix_pval = 1;
   int i_digit = 0;
   int i_min_digit = 0;
   int i_max_digit = 0;
   void *pv_dest = NULL;

   if((NULL == pi_data)||
      (0 == ui_data_sz)||
      (0 == ui_num_digits)||
      (2 > ui_radix))
   {
      e_ret = eSORT_INVALID_ARG;
      goto LBL_SORT_RADIX_RET;
   }

   pi_data_temp = (int *)malloc(sizeof(int) * ui_data_sz);
   if(NULL == pi_data_temp)
   {
      e_ret = eSORT_MEM_FAILURE;
      goto LBL_SORT_RADIX_RET;
   }

   i_min_digit = -(ui_radix - 1);
   i_max_digit = (ui_radix - 1);
   ui_counting_sz = i_max_digit - i_min_digit + 1;
   pui_counting = (unsigned int *)malloc(sizeof(unsigned int) * ui_counting_sz);
   if(NULL == pui_counting)
   {
      e_ret = eSORT_MEM_FAILURE;
      goto LBL_SORT_RADIX_RET;
   } 


   for(ui_i = 0 ; ui_i < ui_num_digits ; ui_i++)
   {
      pv_dest = memset(pui_counting, 0, sizeof(unsigned int) * ui_counting_sz);
      if(pv_dest != pui_counting)
      {
         e_ret = eSORT_MEM_FAILURE;
         goto LBL_SORT_RADIX_RET;
      }

      for(ui_j = 0 ; ui_j < ui_data_sz ; ui_j++)
      {
         i_digit = (pi_data[ui_j] / (int)ui_radix_pval) % (int)ui_radix; 
         pui_counting[i_digit - i_min_digit] += 1;
      }

      for(ui_j= 1 ; ui_j < ui_counting_sz ; ui_j++)
      {
         pui_counting[ui_j] += pui_counting[ui_j - 1];
      }

      for(ui_j = (ui_data_sz - 1) ; ui_j != (0 - 1) ; ui_j--)
      {
         i_digit = (pi_data[ui_j] / (int)ui_radix_pval) % (int)ui_radix; 
         pi_data_temp[pui_counting[i_digit - i_min_digit] - 1] = pi_data[ui_j]; 
         pui_counting[i_digit - i_min_digit] -= 1;
      }

      pv_dest = memcpy(pi_data, pi_data_temp, ui_data_sz * sizeof(*pi_data));
      if(pv_dest != pi_data)
      {
         e_ret = eSORT_MEM_FAILURE;
         goto LBL_SORT_RADIX_RET;
      }

      ui_radix_pval *= ui_radix; 
   }

   e_ret = eSORT_SUCCESS;
LBL_SORT_RADIX_RET:
   return e_ret;
}

