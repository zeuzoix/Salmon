#include <numerical_methods.h>


int main (int argc, char *argv[])
{
   double da_x[] = {-4.0, -3.5, -2.5, -1.5, 0.0, 1.5, 2.5, 3.5, 4.0};
   double da_fx[] = {-3.0, 1.5, 2.5, 1.5, 1.5, 1.5, 2.5, 1.5, -3.0};
   double da_z[3] = {-3.0, -2.0, -1.0};
   double da_fz[3] = {0.0, 0.0, 0.0};
   NMETHODS_RET_E e_ret = eNMETHODS_FAILURE;
   int i_ret = -1;

   e_ret = newtons_interpolation(da_x,
                                 da_fx,
                                 sizeof(da_x)/sizeof(da_x[0]),
                                 da_z,
                                 da_fz,
                                 sizeof(da_x)/sizeof(da_x[0]));
   if(eNMETHODS_SUCCESS != e_ret)
   {
      i_ret = -1;
   }
   else
   {
      i_ret = 0;
   }

   return i_ret;
}
