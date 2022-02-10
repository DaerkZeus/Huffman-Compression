#include <stdio.h>
#include <stdlib.h>

#ifndef HUFFMAN_H
#define HUFFMAN_H	 

#define ASCII_SIZE 256

// Binary Tree Stucture
typedef struct TreeNode {
   int val;
   long frequency;
   struct TreeNode *left;
   struct TreeNode *right;
} TreeNode;

// Linked list Structure 
typedef struct ListNode {
   TreeNode *ptr;
   struct ListNode *next;
} ListNode;

// Create a Binary tree node
TreeNode * createTreeNode(char val, long freq);

// Merge two TreeNodes into one
TreeNode * mergeTree(TreeNode * node1, TreeNode * node2);

// Print the binary tree
void printTree(TreeNode * root, FILE* fptr);

void freeTreeNode(TreeNode * t);
void freeTree(TreeNode *t);



// Build a node at the beggining of the linked list and returns the address
ListNode * createListNode(TreeNode *ptr);

// Insert a node based on the frequency of the node to insert
ListNode * insertNode(ListNode * head, ListNode * toInsert);

// Build the linked list based on the characters' frequencies
ListNode * buildList(long * frequencies);

//Print the linked list
void printList(ListNode *head, FILE *fptr);

// Free memory related to a linked list
void freeList(ListNode * head);

// Compare frequencies of characters
int compareFreq(ListNode * head, ListNode * toInsert);

void printTreeHelper(TreeNode * root, FILE * fptr);
#endif