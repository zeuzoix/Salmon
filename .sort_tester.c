#include <stdio.h>
#include <sort.h>

static SORT_RET_E compare_sort(const void *pv_ele1, const void *pv_ele2);

int main(int argc, char *arv[])
{
   char ca_arr[] ={5,4,3,2,1,0};
   unsigned int ui_arr_size = sizeof(ca_arr)/sizeof(ca_arr[0]);
   SORT_RET_E e_ret = eSORT_FAILURE;


   e_ret = sort_insertion(ca_arr, 
                          sizeof(ca_arr[0]),
                          ui_arr_size,
                          eSORT_ASCENDING,
                          compare_sort);

   
   return e_ret;
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
