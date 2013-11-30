#ifndef _NMETHODS_H_
#define _NMETHODS_H_

typedef enum _NMETHODS_RET_E
{
   eNMETHODS_SUCCESS       =0,
   eNMETHODS_FAILURE       =1,
   eNMETHODS_INVALID_ARG   =2,
   eNMETHODS_MEM_FAILURE   =3,
   eNMETHODS_BUG           =4

}NMETHODS_RET_E;

NMETHODS_RET_E newtons_interpolation(double *pd_x,
                                     double *pd_fx,
                                     unsigned int ui_num_x,
                                     double *pd_z,
                                     double *pd_fz,
                                     unsigned int ui_num_z); 

#endif
