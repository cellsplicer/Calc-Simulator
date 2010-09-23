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

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define MAXLEN 256      /* Maximum buffer length */
#define MEMSIZE 1000    /* Number of memory addresses */
#define WORD 10000      /* The maximum size of an instruction word or data */
#define WORDLEN 5       /* Maximum size of instruction in digits */

int calc_mem[MEMSIZE];     /* Memory of machine */
char buffer[MAXLEN];       /* Input buffer */

/* The cpu.c functions */
int fetch(void);
int execute(void);

/* The io.c functions */
int int_read(void);
int int_print(int operand);

/* The mem.c functions */
int rand_mem(void);
int load_mem(void);
int print_mem(void);

