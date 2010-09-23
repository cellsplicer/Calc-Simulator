/*-
* Copyright (c) 2010, Raymond Tran <raymond.tran@student.adelaide.edu.au>
* All rights reserved. 
*
* Redistribution and use in source and binary forms, with or without 
* modification, are permitted provided that the following conditions are met: 
*
*  - Redistributions of source code must retain the above copyright notice, 
*    this list of conditions and the following disclaimer. 
*  - Redistributions in binary form must reproduce the above copyright 
*    notice, this list of conditions and the following disclaimer in the 
*    documentation and/or other materials provided with the distribution. 
*
* THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND ANY 
* EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED 
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE 
* DISCLAIMED. IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE FOR ANY 
* DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES 
* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR 
* SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER 
* CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT 
* LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY 
* OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH 
* DAMAGE. 
*/

#include <string.h>
#include "calc.h"

char delims[] = " ";    /* Possible delimiter characters */

/* Randomise memory array
 * A simple loop to randomise the memory at every address.
 */
int rand_mem(void)
{
   int i = 0;
   for(i = 0; i < MEMSIZE; i++) {
      calc_mem[i] = rand() % WORD;
   }
   return 0;
}

/* Load program into memory
 * This function tokenises a buffered line of input that was read from the
 * source file. It is assumed in this case that the line contains a memory
 * address token, followed by the data token. If the memory address is a
 * valid value, the data is assigned to the corresponding value in the
 * memory array.
 */
int load_mem(void)
{
   int addr;
   char *token;

   token = strtok(buffer, delims);
   addr = atoi(token);
   if(addr >= 0 && addr < MEMSIZE) {               /* Ensure data is at valid mem address */
      token = strtok(NULL, delims);
      calc_mem[addr] = atoi(token) % WORD;

   }
   return 0;
}

/* Print memory contents
 * This is a simple loop to print the contents of the calc machine's memory.
 */
int print_mem(void)
{
   int i = 0;
   int j = 0;
   for(i = 0; i < MEMSIZE; i += 10) {
      printf("%4d: ", i);
      for(j = 0; j < 10; j++) {
         printf("%4d ", calc_mem[i + j]);
      }
      printf("\n");
   }
   return 0;
}
