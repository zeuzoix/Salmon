#ifndef _HASH_H_
#define _HASH_H_

typedef struct _HASH_STRING_DATA_X
{
   char *pc_key;

}HASH_STRING_DATA_X;

HTABLE_RET_E hash_string(const void *pv_data, unsigned int *pui_hash);

typedef struct _HASH_INT_DIV_DATA_X
{
   int i_key;
   unsigned int ui_table_size;

}HASH_INT_DIV_DATA_X;

HTABLE_RET_E hash_int_div(const void *pv_data, unsigned int *pui_hash); 

typedef struct _HASH_INT_MULT_DATA_X
{
   int i_key;
   unsigned int ui_table_size;

}HASH_INT_MULT_DATA_X;

HTABLE_RET_E hash_int_mult(const void *pv_data, unsigned int *pui_hash);

#endif
