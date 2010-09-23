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

#include <stdlib.h>

#include "cpu.h"
#include "calc.h"

int ac = 0;           /* Accumulator */
int ir = 0;           /* Instruction register */
int pc = 0;          /* Program counter */
int fetches = 0;

/* Fetch stage 
 * The instruction register is first set to the memory location referred
 * to by the program counter. The program counter is subsequently
 * incremented by one.
 */
int fetch(void)
{
   ir = calc_mem[pc];
   pc++;
   fetches++;
   printf("Fetch %d \n", fetches);
   printf("pc=%u ir=%u ac=%u \n", pc, ir, ac);
   return 0;
}

/* Decode / execution stage 
 * The opcode is extracted from first digit contained in the instruction
 * register. Similarly, the operand is extracted from the final 3 digits. 
 * The execution is then performed, the action depending on the opcode.
 * If a LOD is performed on address 998, input is read from the standard
 * input. The input is then stored in the accumulator.
 * If a STO is performed on address 999, the contents of ac are printed
 * to the standard output.
 * Refer to the Calc machine notes for a detailed explanation of each
 * instruction.
 */
int execute(void)
{
   int opcode = 0;
   int operand = 0;
   opcode = ir / MEMSIZE;           /* Extract opcode */
   operand = ir % MEMSIZE;          /* Extact operand */
   printf("Execute: %u %u \n", opcode, operand);

   /* Perform execution */
   switch(opcode) {
      case HLT:
         return 1;
         break;
      case LOD:
         ac = calc_mem[operand];
         /* Trap LOD from 998 as this is the keypad */
         if(operand == 998) {
            ac = int_read() % WORD;
         }
         return 0;
         break;
      case STO:
         calc_mem[operand] = ac;
         /* Trap STO to 999 as this is the display */
         if(operand == 999) {
            int_print(operand);
         }
         return 0;
         break;
      case ADD:   /* Ensure that ac wraps in event of overflow */
         ac = (ac + calc_mem[operand]) % WORD;
         return 0;
         break;
      case SUB:
         ac = (ac - calc_mem[operand]);
         if(ac < 0) {
            ac = WORD - abs(ac);    /* AC can't be under 0 */
         }
         return 0;
         break;
      case JMP:
         pc = operand;
         return 0;
         break;
      case JEQ:
         if(ac == 0) {
            pc = operand;
         }
         return 0;
         break;
      case JGE:
         if(ac >= 0) {
            pc = operand;
         }
         return 0;
         break;
      case JGT:
         if(ac > 0) {
            pc = operand;
         }
         return 0;
         break;
      case DSZ:
         calc_mem[operand] = calc_mem[operand] - 1;
         if(calc_mem[operand] == 0) {
               pc++;
         }
         if(calc_mem[operand] < 0) {
            calc_mem[operand] = WORD - abs(calc_mem[operand]);
         }
         return 0;
         break;
   }
   return 0;
}

