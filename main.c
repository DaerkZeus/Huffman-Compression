#include <stdio.h>
#include <stdlib.h>
#include "struct.h"
#include "huffman.h"
#include "header.h"

/* count the occurrences in a file */

long *countLetters(FILE *fp)
{
   long *asciiCount = (long *)malloc(sizeof(long)*ASCII_SIZE);
   if (asciiCount == NULL) {
      return NULL;
   }
   int ch;
   for (ch = 0; ch < ASCII_SIZE; ch++) {
      asciiCount[ch] = 0;
   }
   fseek(fp, 0, SEEK_SET);
   while ((ch = fgetc(fp)) != EOF) {
      asciiCount[ch] += 1;
   }
   return asciiCount;
}

int main(int argc, char **argv)
{
   if (argc != 5) {
    printf("Not enough arguments");
    return EXIT_FAILURE;
   }
   FILE * inFile = fopen(argv[1], "r");
   if (inFile == NULL) {
      fprintf(stderr, "can't open the input file.  Quit.\n");
      return EXIT_FAILURE;
   }

// Array of ASCII values containing frequencies of each character, ex: asciiCount[97] gives count of letter 'a'
   long *asciiCount = countLetters(inFile);
   fclose(inFile);

   if (asciiCount == NULL) {
      fprintf(stderr, "cannot allocate memory to count the characters in input file.  Quit.\n");
      return EXIT_FAILURE;
   }
 
   ListNode * head = buildList(asciiCount);
   FILE *out1 = fopen(argv[2], "w");
   if (out1 == NULL)
   {
      printf("The output file cannot be opened.\n");
      return 0;
   }
   FILE *out2 = fopen(argv[3], "w");
   if (out2 == NULL)
   {
      printf("The output file cannot be opened.\n");
      return 0;
   }
   FILE *out3 = fopen(argv[4], "w");
   if (out3 == NULL)
   {
      printf("The output file cannot be opened.\n");
      return 0;
   }
   
   // Huffman Tree Creation 
   printList(head, out1);
   head = createHuffmanTree(asciiCount, head);

   // Codebook of the Huffman Tree
   long numRows; 
   int ** codebook = createCodeBook(head, &numRows);
   buildCodeBook(head->ptr, codebook);
   printCodeBook(codebook, numRows, out2);

   // Binary header of Huffman Tree
   preOrderHeader(head->ptr, out3);
   
   fclose(out1);
   fclose (out2);
   fclose (out3);

   freeList(head);
   free(asciiCount);
   for (int i = 0; i < numRows; i++)
   {
      free(codebook[i]);
   }
   free(codebook);
   return 0;
}
