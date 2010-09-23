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

#include "calc.h"

#define MAXCYCLES 1000  /* Maximum CPU cycles */

void printerr(char *);
int eval_arg(int argc, char *argv[]);

FILE *inFile;

int main(int argc, char *argv[])
{

   /* Randomise memory array */
   rand_mem();

   /* Open the specified source file */
   eval_arg(argc, *&argv);

   /* Read lines from the source and load into memory */
   while(fgets(buffer, MAXLEN, inFile) != NULL) {
      int load = 1;
      if(strcmp(buffer, "\n") == 0) {     /* Skip line feed */
         load = 0;
      }
      if(buffer[0] == ';') {              /* Skip comments */
         load = 0;
      }
      if(load) {
         load_mem();
      }
   }
   fclose(inFile);

   /* Print memory contents */
   printf("Initial memory contents: \n");
   print_mem();

   /* Perform the fetch and execute cycle until HLT is encountered. At this
    * stage, the execute function will return 1. Additionally, there is a
    * cycle limit of 1000 to prevent an infinite loop condition.
    */
   int cycles = 0;
   int status = 0;
   while (status == 0 && cycles < MAXCYCLES) {
      fetch();
      status = execute();
      cycles++;
   }
   printf("Execution complete\n");

   return 0;
}

/* Argument parser */
int eval_arg(int argc, char *argv[])
{
   switch(argc)
   {
      case 1:     /* No parameters */
         printerr("no input files");
         break;
      case 2:     /* Two parameters */
         if((inFile = fopen(argv[1], "r")) == NULL) {
            printerr(strerror(errno));
         }
         break;
      default:    /* User entered something dodgy */
         printerr("usage: calc source.calc");
         break;
   }
   return 0;
}

/* Print error 
 * Simply print an error to the stderr, and end the program in the event
 * of a fatal error.
 */
void printerr(char *error)
{
   fprintf(stderr,"calc: %s \n", error);
   exit(1);
}
