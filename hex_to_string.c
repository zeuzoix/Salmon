#include <stdio.h>

int convert_char_unsigned_int(unsigned int *pui_char_val, char pc_str);

int main(int argc, char *argv[])
{
   char *pc_str = NULL;
   int i_ret = -1;
   unsigned int ui_val = 0;
   unsigned int ui_char_val = 0;
   unsigned int ui_max_chars = sizeof(ui_val);
   unsigned int ui_chars = 0;

   if(2 != argc)
   {
      printf("Invalid number of arguments!\n");
      return -1;
   }

   pc_str = argv[1];
   while(('\0' != *pc_str)&&
         (ui_chars < ui_max_chars))
   {
      i_ret = convert_char_unsigned_int(&ui_char_val, *pc_str); 
      if(0 != i_ret)
      {
         printf("Invalid character: %c\n",*pc_str);
      }
      else
      {
         ui_val = ui_val<<4;
         ui_val |= ui_char_val; 
         ui_chars++;
      }
      pc_str++;
   }

   printf("Value is : %u\n",ui_val);

   return 0;
   
}

int convert_char_unsigned_int(unsigned int *pui_char_val, char c_val)
{
   int i_ret = -1;

   if(NULL == pui_char_val)
   {
      i_ret = -1;
      return i_ret;
   }

   if((c_val <= 'f')&&(c_val >= 'a'))
   {
      *pui_char_val = c_val - 'a' + 10;
      i_ret = 0;
   }
   else if((c_val <= 'F')&&(c_val >= 'A'))
   {
      *pui_char_val = c_val - 'A' + 10;
      i_ret = 0;
   }
   else if((c_val <= '9')&&(c_val >= '0'))
   {
      *pui_char_val = c_val - '0';
      i_ret = 0;
   }
   else
   {
      i_ret = -2;
   }

   return i_ret;
}
