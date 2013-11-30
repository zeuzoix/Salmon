#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sort.h>
static SORT_RET_E compare_sort(const void *pv_ele1, const void *pv_ele2);
typedef struct _SORT_NODE_1_X
{
   char *pc_name;
   SORT_RET_E ( *pfn_sort)(void *,
                           unsigned int,
                           unsigned int,
                           SORT_DIRECTION_E,
                           SORT_RET_E (*pfn_compare)(const void *pv_ele1, const void *pv_ele2));
   char *pc_arr;
}SORT_NODE_1_X;

typedef struct _SORT_NODE_2_X
{
   char *pc_name;
   SORT_RET_E ( *pfn_sort)(int *,
                           unsigned int,
                           SORT_DIRECTION_E,
                           int,
                           int);
   int *pi_arr;
}SORT_NODE_2_X;

static int test1(unsigned int ui_trials,
                 unsigned int ui_arr_max_size,
                 unsigned int ui_sort_list_size,
                 SORT_NODE_1_X *px_sort_node);

int main(int argc, char *argv[])
{
   unsigned int ui_arr_max_size = 0;
   unsigned int ui_trials = 0;
   SORT_NODE_1_X xa_sort_list[] = {  {"Insertion sort" , sort_insertion   , NULL},
                                     {"Quick sort"     , sort_quick       , NULL},
                                     {"Merge sort"     , sort_merge       , NULL},
                                     { NULL            , NULL             , NULL}
                                  };
   unsigned int ui_sort_list_size = 0; 
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


   ui_sort_list_size = sizeof(xa_sort_list)/sizeof(xa_sort_list[0]);
   i_ret = test1(ui_trials,
                 ui_arr_max_size,
                 ui_sort_list_size,
                 xa_sort_list);

   i_ret = 0;
LBL_MAIN_RET:
   return i_ret;
}

static int test1(unsigned int ui_trials,
                 unsigned int ui_arr_max_size,
                 unsigned int ui_sort_list_size,
                 SORT_NODE_1_X *px_sort_node)
{
   int i_ret = -1;
   int i_cmp_ret = -1;
   unsigned int ui_i = 0;
   unsigned int ui_j = 0;
   unsigned int ui_k = 0;
   unsigned int ui_arr_size = 0;
   char *pc_arr_src = NULL;
   SORT_RET_E e_sort = eSORT_FAILURE;
   SORT_DIRECTION_E e_dir = eSORT_ASCENDING;

   if((NULL == px_sort_node)||
      (0 == ui_sort_list_size)||
      (0 == ui_arr_max_size)||
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

      if(0 == (rand()%2))
      {
         e_dir = eSORT_ASCENDING;
         printf("Sorting ascending\n");
      }
      else
      {
         e_dir = eSORT_DESCENDING;
         printf("Sorting descending\n");
      }

      /*Allocate memory for the source array + arrays to be sorted with different algos*/
      pc_arr_src = (char *)malloc(ui_arr_size * (ui_sort_list_size));
      if(NULL == pc_arr_src)
      {
         printf("Can't allocate memory for sorting all\n");
         i_ret = -4;
         goto LBL_TEST2;
      }

      for(ui_j = 0 ; ui_j < (ui_sort_list_size - 1) ; ui_j++)
      {
         px_sort_node[ui_j].pc_arr = pc_arr_src + ((ui_j + 1) * ui_arr_size);
      }

      for(ui_k = 0 ; ui_k < ui_arr_size ; ui_k++)
      {
         pc_arr_src[ui_k] = (char)rand();
         for(ui_j = 0 ; ui_j < (ui_sort_list_size - 1) ; ui_j++)
         {
            px_sort_node[ui_j].pc_arr[ui_k] = pc_arr_src[ui_k];
         }
      }

      printf("Source:\n");
      for(ui_k = 0 ; ui_k < ui_arr_size ; ui_k++)
      {
         printf("%d%s",
                pc_arr_src[ui_k],
                (ui_k == (ui_arr_size - 1))?"\n":", ");
      }

      for(ui_j = 0 ; ui_j < (ui_sort_list_size - 1) ; ui_j++)
      {
         e_sort = px_sort_node[ui_j].pfn_sort(px_sort_node[ui_j].pc_arr,
                                              ui_arr_size,
                                              sizeof(px_sort_node[ui_j].pc_arr[0]),
                                              e_dir,
                                              compare_sort);
         if(eSORT_SUCCESS != e_sort)
         {
            printf("Iteration %u %s failed\n", ui_i,  px_sort_node[ui_j].pc_name);
         }

         printf("%s:\n", px_sort_node[ui_j].pc_name);
         for(ui_k = 0 ; ui_k < ui_arr_size ; ui_k++)
         {
            printf("%d%s",
                   px_sort_node[ui_j].pc_arr[ui_k],
                  (ui_k == (ui_arr_size - 1))?"\n":", "); 
         }
      }

      for(ui_j = 1 ; ui_j < (ui_sort_list_size - 1) ; ui_j++)
      {
         i_cmp_ret = memcmp(px_sort_node[ui_j - 1].pc_arr,
                            px_sort_node[ui_j].pc_arr , 
                            ui_arr_size);
         if(0 != i_cmp_ret)
         {
            printf("Iteration %u yields different results for %s and %s\n",
                   ui_i,
                   px_sort_node[ui_j - 1].pc_name,
                   px_sort_node[ui_j].pc_name);
         }
      }
      printf("----------------------------------------\n");

      if(NULL != pc_arr_src)
      {
         free(pc_arr_src);
         pc_arr_src = NULL;
      }
   }

   i_ret = 0;
LBL_TEST2:
   if(NULL != pc_arr_src)
   {
      free(pc_arr_src);
      pc_arr_src = NULL;
   }
   return i_ret;

}


static SORT_RET_E compare_sort(const void *pv_ele1, const void *pv_ele2)
{
   SORT_RET_E e_ret = eSORT_FAILURE;

   if((NULL == pv_ele1)||
      (NULL == pv_ele2))
   {
      e_ret = eSORT_INVALID_ARG;
      goto LBL_COMARE_SORT_RET;
   }

   if(*((char *)pv_ele1) > *((char *)pv_ele2))
   {
      e_ret = eSORT_LESSER;
   }
   else if(*((char *)pv_ele1) < *((char *)pv_ele2))
   {
      e_ret = eSORT_GREATER;
   }
   else
   {
      e_ret = eSORT_EQUAL;
   }

LBL_COMARE_SORT_RET:
   return e_ret;
}
