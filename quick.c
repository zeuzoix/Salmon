#include <stdio.h>
#include <stdint.h>

int8_t quicksort(int8_t *pc_arr, uint8_t uc_low_index, uint8_t uc_high_index);
int8_t partition(int8_t *pc_arr, uint8_t uc_low_index, uint8_t uc_high_index, uint8_t *puc_pivot);
void print_array(int8_t *pc_arr, uint8_t uc_low_index, uint8_t uc_high_index);

int main()
{

   int8_t ca_array[] = {10, 2, 3 ,15, 15, 18, 40, 23, 25, 1, 5, 99, 87, 43, 22, 45, 83, 67};   
   int8_t c_ret = -1;
   int8_t c_ret0 = -1;
   uint8_t uc_array_size = 0;

   uc_array_size = sizeof(ca_array)/sizeof(ca_array[0]);

   c_ret = quicksort(ca_array, 0, (uc_array_size - 1));
   if(0 != c_ret)
   {
      printf("%s:Error in quicksort\n",__FUNCTION__);
      c_ret0 = -1;
      goto LBL_MAIN_RET;
   }
   print_array(ca_array, 0, (uc_array_size - 1));
   
LBL_MAIN_RET:
   return c_ret0;
}

int8_t quicksort(int8_t *pc_arr, uint8_t uc_low_index, uint8_t uc_high_index)
{
   int8_t c_ret = -1;
   int8_t c_ret0 = -1;
   uint8_t uc_pivot = 0;
   
   if(uc_low_index >= uc_high_index)
   {
      c_ret0 = 0;
      printf("Exit\n");
      goto LBL_QUICKSORT_RET;
   }

   c_ret = partition(pc_arr, uc_low_index, uc_high_index, &uc_pivot);
   if(0 != c_ret)
   {
      printf("%s:Error in partition\n",__FUNCTION__);
      c_ret0 = -1;
      goto LBL_QUICKSORT_RET;
   }

   if(uc_pivot > uc_low_index)
   {
      c_ret = quicksort(pc_arr, uc_low_index, (uc_pivot - 1));
      if(0 != c_ret)
      {
         printf("%s:Error in quicksort\n",__FUNCTION__);
         c_ret0 = -1;
         goto LBL_QUICKSORT_RET;
      }
   }

   if(uc_pivot < uc_high_index)
   {
      c_ret = quicksort(pc_arr, (uc_pivot + 1), uc_high_index);
      if(0 != c_ret)
      {
         printf("%s:Error in quicksort\n",__FUNCTION__);
         c_ret0 = -1;
         goto LBL_QUICKSORT_RET;
      }
   }

   c_ret0 = 0;
LBL_QUICKSORT_RET:
   return c_ret0;
}

int8_t partition(int8_t *pc_arr, uint8_t uc_low_index, uint8_t uc_high_index, uint8_t *puc_pivot)
{
   int8_t c_ret0 = -1;
   uint8_t uc_up = uc_high_index;
   uint8_t uc_down = uc_low_index;
   int8_t c_elmnt = 0;
   int8_t c_tmp = 0;

   if((NULL == pc_arr)||
      (NULL == puc_pivot))
   {
      printf("%s:Invalid Arguments\n",__FUNCTION__);
      c_ret0 = -1;
      goto LBL_PARTITION_RET;
   }

   c_elmnt = pc_arr[uc_low_index];

   while(uc_down < uc_up)
   {
      while((c_elmnt >= pc_arr[uc_down])&&
            (uc_down <= uc_high_index))
      {
         uc_down++;
      }
      
      while((c_elmnt < pc_arr[uc_up])&&
            (uc_up >= uc_low_index))
      {
         uc_up--;
      }

      if(uc_down < uc_up)
      {
         c_tmp = pc_arr[uc_up];
         pc_arr[uc_up] = pc_arr[uc_down];
         pc_arr[uc_down] = c_tmp;
      }
   }

   c_tmp = pc_arr[uc_up];
   pc_arr[uc_up] = pc_arr[uc_low_index];
   pc_arr[uc_low_index] = c_tmp;

   *puc_pivot = uc_up;
   print_array(pc_arr, uc_low_index, uc_high_index);

   c_ret0 = 0;

LBL_PARTITION_RET:
   return c_ret0;
}

void print_array(int8_t *pc_arr, uint8_t uc_low_index, uint8_t uc_high_index)
{
   uint8_t uc_i = 0;

   for(uc_i = uc_low_index ; uc_i <= uc_high_index ; uc_i++)
   {
      printf("%u\t", pc_arr[uc_i]);
   }

   printf("\n");
   return;
}
