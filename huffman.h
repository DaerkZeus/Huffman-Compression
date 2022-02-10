#include <stdio.h>
#include <stdlib.h>
#include "struct.h"

// Creates a tree for Huffman encoding. Returns 1 if successfull 
ListNode * createHuffmanTree(long * frequencies, ListNode * head);

// Determine the height of the tree recursively
long treeDepth(TreeNode *tn);

// Determine the number of leafs in the tree
long numLeaf(TreeNode *tn);
void numLeafHelper(TreeNode *tn, long* num);

// Create a codebook for the Huffman Tree, 2D array with values in rows and its code in column
void buildCodeBook(TreeNode *root, int ** codebook);
void codebookHelper(TreeNode * tn, int ** codebook, long * row, long col);
int ** createCodeBook(ListNode * head, long * numRows);

// Print the codebook, char:code    ex: a:01
void printCodeBook(int ** codebook, long totalRows, FILE * fptr); 