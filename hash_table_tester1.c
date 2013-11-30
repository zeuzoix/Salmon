#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>
#include <htable.h>

int main(int argc, char *argv[])
{
   int i_ret = -1;
   char *pc_endptr = NULL;
   long int l_val = 0;
   unsigned int ui_hash = 0;
   unsigned int ui_table_size = 10;
   HTABLE_RET_E e_ret = eHTABLE_FAILURE;

   if(2 != argc)
   {
      fprintf(stderr,"%s: Incorrect number of arguments\n",argv[0]);
      i_ret = -1;
      goto LBL_MAIN_RET;
   }

   errno = 0;    /* To distinguish success/failure after call */
   l_val = (int)strtol(argv[1],&pc_endptr, 10);
   if(('\0' != *pc_endptr)||
      (pc_endptr == argv[1])) 
   {
      fprintf(stderr,"%s: strtol failure\n",argv[0]);
      i_ret = -2;
      goto LBL_MAIN_RET;
   }

   /* Check for various possible errors */
   if ((errno == ERANGE && (l_val == LONG_MAX || l_val == LONG_MIN))
         || (errno != 0 && l_val == 0)) 
   {
      fprintf(stderr,"%s: strtol failure\n",argv[0]);
      i_ret = -3;
      goto LBL_MAIN_RET;
   }

   if((l_val > INT_MAX)||
      (l_val < INT_MIN))
   {
      fprintf(stderr,"%s: Long int value larger than int\n",argv[0]);
      i_ret = -4;
      goto LBL_MAIN_RET;
   }

   e_ret = htable_hash_int_division_method(&l_val,
                                           &ui_hash,
                                           ui_table_size);
   if(eHTABLE_SUCCESS != e_ret)
   {
      fprintf(stderr,"%s: Failed to get hash from hash_table_hash_int_division_method\n",argv[0]);
      i_ret = -5;
      goto LBL_MAIN_RET;
   }

   fprintf(stdout,"%s: Hash value from hash_table_hash_int_division_method is %u\n",argv[0],ui_hash);

   e_ret = htable_hash_int_multiplication_method(&l_val,
                                                 &ui_hash,
                                                 ui_table_size);
   if(eHTABLE_SUCCESS != e_ret)
   {
      fprintf(stderr,"%s: Failed to get hash from hash_table_hash_int_multiplication_method\n",argv[0]);
      i_ret = -5;
      goto LBL_MAIN_RET;
   }

   fprintf(stdout,"%s: Hash value from hash_table_hash_int_multiplication_method is %u\n",argv[0],ui_hash);

   i_ret = 0;
   
LBL_MAIN_RET:
   return i_ret;
}
