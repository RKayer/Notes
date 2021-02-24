/**æÿ’Ûº¸≈Ãº¸÷µ…®√Ë
 *------------------------------
   P27 | K11 | K12 | K13 | K14 
  ------------------------------
   P26 | K21 | K22 | K23 | K24      
  ------------------------------
   P25 | K31 | K32 | K33 | K34      
  ------------------------------
   P24 | K41 | K42 | K43 | K44      
  ------------------------------
  -----| P23 | P22 | P21 | P20      
  ------------------------------
*/


#ifndef _C51_MATRIX_KEY_H
#define _C51_MATRIX_KEY_H

#include <reg52.h>
#include "delay.h"

#define uint8_t  unsigned char
#define uint16_t unsigned int

#define GPIO_KEY P2

uint8_t Matrix_Key_Scan();
/**************************************/

#endif