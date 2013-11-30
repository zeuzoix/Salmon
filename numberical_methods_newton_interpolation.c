#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <numerical_methods.h>


NMETHODS_RET_E newtons_interpolation(double *pd_x,
                                     double *pd_fx,
                                     unsigned int ui_num_x,
                                     double *pd_z,
                                     double *pd_fz,
                                     unsigned int ui_num_z) 
{
   NMETHODS_RET_E e_ret = eNMETHODS_FAILURE;
   unsigned int ui_i = 0;
   unsigned int ui_j = 0;
   double d_k = 0;
   double *pd_table = NULL;
   double *pd_coef = NULL;
   void *pv_dest = NULL;

   if((NULL == pd_x)||
      (NULL == pd_fx)||
      (0 == ui_num_x)||
      (NULL == pd_z)||
      (NULL == pd_fz)||
      (0 == ui_num_z))
   {
      e_ret = eNMETHODS_INVALID_ARG;
      goto LBL_NEWTONS_INTERPOLATION_RET;
   }

   pd_table = (double *)malloc(sizeof(*pd_table) * ui_num_x);
   if(NULL == pd_table)
   {
      e_ret = eNMETHODS_MEM_FAILURE;
      goto LBL_NEWTONS_INTERPOLATION_RET;
   }

   pd_coef = (double *)malloc(sizeof(*pd_coef) * ui_num_x);
   if(NULL == pd_table)
   {
      e_ret = eNMETHODS_MEM_FAILURE;
      goto LBL_NEWTONS_INTERPOLATION_RET;
   }

   pv_dest = memset(pd_fz, 0 , sizeof(*pd_fz) * ui_num_z);
   if(pv_dest != pd_fz)
   {
      e_ret = eNMETHODS_MEM_FAILURE;
      goto LBL_NEWTONS_INTERPOLATION_RET;
   }

   for(ui_i = 0 ; ui_i < ui_num_x ; ui_i++)
   {
      for(ui_j = 0 ; ui_j < (ui_num_x - ui_i) ; ui_j++)
      {
         if(0 == ui_i)
         {
            pd_table[ui_j] = pd_fx[ui_j];
         }
         else
         {
            pd_table[ui_j] = (pd_table[ui_j + 1] - pd_table[ui_j])/(pd_x[ui_j + ui_i] - pd_x[ui_j]);
         }
      }
      pd_coef[ui_i] = pd_table[0];
   }

   for(ui_i = 0 ; ui_i < ui_num_z ; ui_i++)
   {
      d_k = 1;
      for(ui_j = 0 ; ui_j < ui_num_x ; ui_j++)
      {
         pd_fz[ui_i] += (pd_coef[ui_j] * d_k);
         d_k *= (pd_z[ui_i] - pd_x[ui_j]);
      }
   }

   e_ret = eNMETHODS_SUCCESS;
LBL_NEWTONS_INTERPOLATION_RET:
   if(NULL != pd_table)
   {
      free(pd_table);
      pd_table = NULL;
   }

   if(NULL != pd_coef)
   {
      free(pd_coef);
      pd_coef = NULL;
   }

   return e_ret;
}
