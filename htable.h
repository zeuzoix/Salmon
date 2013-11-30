#ifndef _HASH_TABLE_H_
#define _HASH_TABLE_H_

typedef enum _HTABLE_RET_E
{
   eHTABLE_SUCCESS        = 0,
   eHTABLE_FAILURE        = 1,  
   eHTABLE_INVALID_ARG    = 2,  
   eHTABLE_MEM_FAILURE    = 3,
   eHTABLE_DATA_SAME      = 4,
   eHTABLE_DATA_DIFF      = 5,
   eHTABLE_EXIST          = 6,
   eHTABLE_NOT_EXIST      = 7,
   eHTABLE_BUG            = 8

}HTABLE_RET_E;

typedef struct _HTABLE_CHAIN_X *HTABLE_CHAIN_HDL;

HTABLE_RET_E htable_chain_init(HTABLE_CHAIN_HDL *phdl_htable,
                               unsigned int ui_num_buckets,
                               unsigned int ui_max_elements_per_bucket,
                               HTABLE_RET_E (*pfn_compare)(const void *pv_ele1, const void *pv_ele2),
                               void (*pfn_delete)(void *pv_data),
                               HTABLE_RET_E (*pfn_hash)(const void *pv_key, unsigned int *pui_hash, unsigned int ui_table_size));

HTABLE_RET_E htable_chain_insert(HTABLE_CHAIN_HDL hdl_htable,
                                 void *pv_data);

HTABLE_RET_E htable_chain_remove(HTABLE_CHAIN_HDL hdl_htable,
                                 void **ppv_data);

HTABLE_RET_E htable_chain_lookup(HTABLE_CHAIN_HDL hdl_htable,
                                 void **ppv_data);


HTABLE_RET_E htable_chain_deinit(HTABLE_CHAIN_HDL *phdl_htable);
                            
#endif
