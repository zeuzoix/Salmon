#include <stdio.h>
#include <llist.h>

static LLIST_RET_E app_debug(void *pv_data);

int main(int argc, char *argv[])
{
   int i_ret = -1;
   unsigned int ui_i = 0;
   LLIST_RET_E e_ret = eLLIST_FAILURE;
   LLIST_HDL hdl_list = NULL;
   SNODE_HDL hdl_node_temp = NULL;
   SNODE_HDL hdl_node_next = NULL;
   SNODE_HDL hdl_node_head = NULL;
   SNODE_HDL hdl_node_tail = NULL;
   unsigned int uia_uns_ints[] = { 12, 23, 34, 56, 167, 90};
   char ca_chars[] = { 'A', 'c', 'w', 'f', 'Q', 'G'};
   char *pc_chars = NULL;
   char *pui_uns_ints = NULL;
   unsigned int ui_size = 0;

   e_ret = llist_init(&hdl_list,
                      10,
                      NULL,
                      app_debug);
   if(eLLIST_SUCCESS != e_ret)
   {
      fprintf(stderr,"llist_init :%d", e_ret);
      i_ret = -2;
      goto LBL_MAIN_RET;
   }

   for(ui_i = 0 ; ui_i < 5 ; ui_i++)
   {
      e_ret = llist_add_next(hdl_list,
                             NULL,
                             &uia_uns_ints[ui_i]);
      if(eLLIST_SUCCESS != e_ret)
      {
         fprintf(stderr,"Error adding %uth of uia_uns_ints\n", ui_i);
         fprintf(stderr,"Value :%u\n", uia_uns_ints[ui_i]);
         fprintf(stderr,"llist_add_next :%d\n", e_ret);
         i_ret = -3;
         goto LBL_MAIN_RET;
      }
   }

   for(ui_i = 0 ; ui_i < 5 ; ui_i++)
   {
      e_ret = llist_add_next(hdl_list,
                             NULL,
                             &ca_chars[ui_i]);
      if(eLLIST_SUCCESS != e_ret)
      {
         fprintf(stderr,"Error adding %uth of ca_chars\n", ui_i);
         fprintf(stderr,"Value :%c\n", ca_chars[ui_i]);
         fprintf(stderr,"llist_add_next :%d\n", e_ret);
         i_ret = -4;
         goto LBL_MAIN_RET;
      }
   }

   ui_i = 0;
   e_ret = llist_add_next(hdl_list,
                          NULL,
                          &ca_chars[ui_i]);
   if(eLLIST_SUCCESS != e_ret)
   {
      fprintf(stderr,"Error adding %uth of ca_chars\n", ui_i);
      fprintf(stderr,"Value :%c\n", ca_chars[ui_i]);
      fprintf(stderr,"llist_add_next :%d\n", e_ret);
//    i_ret = -5;
//    goto LBL_MAIN_RET;
   }

   fprintf(stdout,"All the nodes:\n");
   llist_print_all(hdl_list);

   e_ret = llist_tail(hdl_list,
                      &hdl_node_tail);
   if(eLLIST_SUCCESS != e_ret)
   {
      fprintf(stderr,"Error %d\n", e_ret);
      i_ret = -6;
      goto LBL_MAIN_RET;
   }

   fprintf(stdout,"Tail node:\n");
   (void)llist_print_node(hdl_list,
                          hdl_node_tail);

   hdl_node_head = NULL;
   e_ret = llist_head(hdl_list,
                      &hdl_node_head);
   if(eLLIST_SUCCESS != e_ret)
   {
      fprintf(stderr,"Error %d\n", e_ret);
      i_ret = -6;
      goto LBL_MAIN_RET;
   }

   fprintf(stdout,"Head node:\n");
   (void)llist_print_node(hdl_list,
                          hdl_node_head);

   fprintf(stdout,"Removing Head node:\n");
   e_ret = llist_rem_next(hdl_list,
                          NULL,
                          (void **)&pc_chars);
   if(eLLIST_SUCCESS != e_ret)
   {
      fprintf(stderr,"Error adding %uth of ca_chars\n", ui_i);
      fprintf(stderr,"Value :%c\n", ca_chars[ui_i]);
      fprintf(stderr,"llist_add_next :%d\n", e_ret);
      i_ret = -5;
      goto LBL_MAIN_RET;
   }

   fprintf(stdout,"All the nodes:\n");
   llist_print_all(hdl_list);

   hdl_node_next = hdl_node_head;
   while(hdl_node_next != hdl_node_tail)
   {
      hdl_node_temp = hdl_node_next;
      (void)llist_node_next(hdl_node_temp,
                            &hdl_node_next);
   }

   fprintf(stdout,"Removing Tail node:\n");
   e_ret = llist_rem_next(hdl_list,
                          hdl_node_temp,
                          (void **)&pc_chars);
   if(eLLIST_SUCCESS != e_ret)
   {
      i_ret = -6;
      goto LBL_MAIN_RET;
   }

   fprintf(stdout,"All the nodes:\n");
   llist_print_all(hdl_list);

   e_ret = llist_deinit(&hdl_list);
   if(eLLIST_SUCCESS != e_ret)
   {
      fprintf(stderr,"llist_init :%d", e_ret);
      i_ret = -7;
      goto LBL_MAIN_RET;
   }

   i_ret = 0;
LBL_MAIN_RET:
   return i_ret;
}


static LLIST_RET_E app_debug(void *pv_data)
{
   LLIST_RET_E e_ret = eLLIST_FAILURE;

   fprintf(stdout, "Unsigned int val: %u\n", *(unsigned int *)pv_data);
   fprintf(stdout, "Char val: %c\n", *(char *)pv_data);

   e_ret = eLLIST_SUCCESS;
   return e_ret;
}
