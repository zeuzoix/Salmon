#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sort.h>

static int test1(unsigned int ui_trials,
                 unsigned int ui_arr_max_size);

int main(int argc, char *argv[])
{
   unsigned int ui_arr_max_size = 0;
   unsigned int ui_trials = 0;
   char *pc_ptr = NULL;
   int i_ret = -1;

   if(3 != argc)
   {
      printf("Usage: %s <max size of array> <no. of iterations>\n",argv[0]);
      i_ret = -2;
      goto LBL_MAIN_RET;
   }

   ui_arr_max_size = strtoul(argv[1], &pc_ptr, 10);
   if((NULL == pc_ptr)||
      ('\0' != *pc_ptr)||
      (0 == ui_arr_max_size))
   {
      printf("Usage: %s <max size of array> <no. of iterations>\n",argv[0]);
      printf("First argument %s inappropriate\n", argv[1]);
      i_ret = -2;
      goto LBL_MAIN_RET;
   }

   pc_ptr = NULL;
   ui_trials = strtoul(argv[2], &pc_ptr, 10);
   if((NULL == pc_ptr)||
      ('\0' != *pc_ptr)||
      (0 == ui_trials))
   {
      printf("Usage: %s <max size of array> <no. of iterations>\n",argv[0]);
      printf("Second argument %s inappropriate\n", argv[2]);
      i_ret = -3;
      goto LBL_MAIN_RET;
   }

   i_ret = test1(ui_trials,
                 ui_arr_max_size);

   i_ret = 0;
LBL_MAIN_RET:
   return i_ret;
}

static int test1(unsigned int ui_trials,
                 unsigned int ui_arr_max_size)
{
   int i_ret = -1;
   int i_min_data = 0;
   int i_max_data = 0;
   unsigned int ui_i = 0;
   unsigned int ui_k = 0;
   unsigned int ui_arr_size = 0;
   int *pi_arr_src = NULL;
   int *pi_arr_dst[2] = {NULL, NULL};
   SORT_RET_E e_sort = eSORT_FAILURE;

   if((0 == ui_arr_max_size)||
      (0 == ui_trials))
   {
      i_ret = -1;
      goto LBL_TEST2;
   }

   for(ui_i = 0 ; ui_i < ui_trials ; ui_i++)
   {
      do 
      {
         ui_arr_size = (unsigned int)rand() % (ui_arr_max_size + 1);
      }while(ui_arr_size <= 1);
      
      printf("Size of the array is %u iteration %u\n",ui_arr_size, ui_i);

      /*Allocate memory for the source array + arrays to be sorted with different algos*/
      pi_arr_src = (int *)calloc(ui_arr_size * sizeof(int) , 3);
      if(NULL == pi_arr_src)
      {
         printf("Can't allocate memory for sorting all\n");
         i_ret = -4;
         goto LBL_TEST2;
      }
      pi_arr_dst[0] = pi_arr_src + ui_arr_size;
      pi_arr_dst[1] = pi_arr_dst[0] + ui_arr_size;

      for(ui_k = 0 ; ui_k < ui_arr_size ; ui_k++)
      {
         pi_arr_src[ui_k] = (short)rand();
         pi_arr_dst[0][ui_k] = pi_arr_src[ui_k];
         pi_arr_dst[1][ui_k] = pi_arr_src[ui_k];
         if((i_min_data > pi_arr_src[ui_k])||
            (0 == ui_k))
         {
            i_min_data = pi_arr_src[ui_k];
         }

         if((i_max_data < pi_arr_src[ui_k])||
            (0 == ui_k))
         {
            i_max_data = pi_arr_src[ui_k];
         }
      }

      printf("Source:\n");
      for(ui_k = 0 ; ui_k < ui_arr_size ; ui_k++)
      {
         printf("%d%s",
                pi_arr_src[ui_k],
                (ui_k == (ui_arr_size - 1))?"\n":", ");
      }
      printf("Minimum value is :%d\n",i_min_data);
      printf("Maximum value is :%d\n",i_max_data);
      printf("Difference is :%d\n",(i_max_data - i_min_data));

      e_sort = sort_counting(pi_arr_dst[0],
                             ui_arr_size,
                             i_min_data,
                             i_max_data);
      if(eSORT_SUCCESS != e_sort)
      {
         printf("Iteration %u Counting Sort failed\n", ui_i);
      }

      printf("Counting Sort:\n");
      for(ui_k = 0 ; ui_k < ui_arr_size ; ui_k++)
      {
         printf("%d%s",
                pi_arr_dst[0][ui_k],
               (ui_k == (ui_arr_size - 1))?"\n":", "); 
      }

      e_sort = sort_radix(pi_arr_dst[1],
                          ui_arr_size,
                          5,
                          10);
      if(eSORT_SUCCESS != e_sort)
      {
         printf("Iteration %u Radix Sort failed\n", ui_i);
      }

      printf("Radix Sort:\n");
      for(ui_k = 0 ; ui_k < ui_arr_size ; ui_k++)
      {
         printf("%d%s",
                pi_arr_dst[1][ui_k],
               (ui_k == (ui_arr_size - 1))?"\n":", "); 
      }
      printf("----------------------------------------\n");

      if(NULL != pi_arr_src)
      {
         free(pi_arr_src);
         pi_arr_src = NULL;
      }

   }

   i_ret = 0;
LBL_TEST2:
   if(NULL != pi_arr_src)
   {
      free(pi_arr_src);
      pi_arr_src = NULL;
   }
   return i_ret;

}
