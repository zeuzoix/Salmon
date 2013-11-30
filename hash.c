#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <htable.h>
#include <hash.h>


HTABLE_RET_E hash_string(const void *pv_data, unsigned int *pui_hash)
{
   HTABLE_RET_E e_ret = eHTABLE_FAILURE;
   const HASH_STRING_DATA_X *px_data = pv_data;
   unsigned int ui_val = 0;
   unsigned int ui_tmp_val = 0;
   const char *pc_temp = NULL;

   if((NULL == pv_data)||
      (NULL == pui_hash))
   {
      e_ret = eHTABLE_INVALID_ARG;
      goto LBL_RET;
   }
   
   pc_temp = px_data->pc_key;
   while('\0' != *pc_temp)
   {
      ui_val = *pc_temp + (ui_val << 4);
      ui_tmp_val = ui_val & 0xF0000000;
      if(0 != ui_tmp_val)
      {
         ui_val = ui_val ^ (ui_tmp_val>>24);
         ui_val = ui_val ^ ui_tmp_val;
      }
      pc_temp++;
   }

   *pui_hash = ui_val;

   e_ret = eHTABLE_SUCCESS;
LBL_RET:
   return e_ret;
}

HTABLE_RET_E hash_int_div(const void *pv_data, unsigned int *pui_hash)
{
   HTABLE_RET_E e_ret = eHTABLE_FAILURE;
   const HASH_INT_DIV_DATA_X *px_data = pv_data;

   if((NULL == pv_data)||
      (NULL == pui_hash))
   {
      e_ret = eHTABLE_INVALID_ARG;
      goto LBL_RET;
   }

   if(0 == px_data->ui_table_size)
   {
      e_ret = eHTABLE_INVALID_ARG;
      goto LBL_RET;
   }

   *pui_hash = px_data->i_key % px_data->ui_table_size;

   e_ret = eHTABLE_SUCCESS;
LBL_RET:
   return e_ret;
}

HTABLE_RET_E hash_int_mult(const void *pv_data, unsigned int *pui_hash)
{
   HTABLE_RET_E e_ret = eHTABLE_FAILURE;
   const HASH_INT_MULT_DATA_X *px_data = pv_data;
   double d_temp = 0.0;
   double d_decimal = 0.0;

   if((NULL == pv_data)||
      (NULL == pui_hash))
   {
      e_ret = eHTABLE_INVALID_ARG;
      goto LBL_RET;
   }

   if(0 == px_data->ui_table_size)
   {
      e_ret = eHTABLE_INVALID_ARG;
      goto LBL_RET;
   }

   d_temp = px_data->i_key * 0.618;
   d_decimal = (double)((int)(px_data->i_key * 0.618)/1);
   d_temp = d_temp - d_decimal;
   
   *pui_hash = (unsigned int)(px_data->ui_table_size * d_temp);

   e_ret = eHTABLE_SUCCESS;
LBL_RET:
   return e_ret;
}

