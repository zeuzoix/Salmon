#ifndef _SORT_H_
#define _SORT_H_

typedef enum _SORT_RET_E
{
   eSORT_SUCCESS        = 0,
   eSORT_FAILURE        = 1,
   eSORT_INVALID_ARG    = 2,
   eSORT_MEM_FAILURE    = 3,
   eSORT_GREATER        = 4,
   eSORT_LESSER         = 5,
   eSORT_EQUAL          = 6,
   eSORT_BUG            = 7
      
}SORT_RET_E;

typedef enum _SORT_DIRECTION_E
{
   eSORT_DESCENDING     = 0,
   eSORT_ASCENDING      = 1

}SORT_DIRECTION_E;

SORT_RET_E sort_insertion(void *pv_array, 
                          unsigned int ui_ele_num,
                          unsigned int ui_ele_size,
                          SORT_DIRECTION_E e_dir,
                          SORT_RET_E (*pfn_compare)(const void *pv_ele1, const void *pv_ele2));

SORT_RET_E sort_quick(void *pv_array,
                      unsigned int ui_ele_num,
                      unsigned int ui_ele_size,
                      SORT_DIRECTION_E e_dir,
                      SORT_RET_E (*pfn_compare)(const void *pv_ele1, const void *pv_ele2));

SORT_RET_E sort_merge(void *pv_array, 
                      unsigned int ui_ele_num,
                      unsigned int ui_ele_size,
                      SORT_DIRECTION_E e_dir,
                      SORT_RET_E (*pfn_compare)(const void *pv_ele1, const void *pv_ele2));

SORT_RET_E sort_counting(int *pi_data,
                         unsigned int ui_data_sz,
                         int i_min_data,
                         int i_max_data);

SORT_RET_E sort_radix(int *pi_data,
                      unsigned int ui_data_sz,
                      unsigned int ui_num_digits,
                      unsigned int ui_radix);
#endif /*_SORT_H_*/
