#include "struct.h"

TreeNode * createTreeNode(char val, long frequency)
{
    TreeNode *newNode = malloc(sizeof(TreeNode));
    newNode -> frequency = frequency;
    newNode -> val = val;
    newNode -> left = NULL;
    newNode -> right = NULL;
    return newNode;
}

// Merge two nodes together with left child being the first argument
TreeNode * mergeTree(TreeNode * node1, TreeNode *node2)
{
    TreeNode * root = malloc(sizeof(TreeNode));
    root -> left = node1;
    root -> right = node2;
    root -> val = node1 -> val; //Does not matter
    root -> frequency = (node1 -> frequency) + (node2 -> frequency);
    return root;
}

void printList(ListNode * head, FILE * fptr)
{
    if (head == NULL)
    {
        return; 
    }
    printTree(head -> ptr, fptr);
    printList(head -> next, fptr);
}

void printTree(TreeNode * root, FILE * fptr)
{
    printTreeHelper(root, fptr);
}

void printTreeHelper(TreeNode * root, FILE * fptr)
{
    if (root == NULL)
    {
        return;
    }
    if (root->frequency > 0)
    {
        fprintf(fptr, "%c:%ld\n", root->val, root->frequency);
        printTreeHelper(root->left, fptr);
        printTreeHelper(root->right, fptr);
    }
}

void freeTreeNode(TreeNode * t) {
	free(t);
}

void freeTree(TreeNode * t) {
	if (t == NULL) return;
	freeTree(t->left);
	freeTree(t->right);
	freeTreeNode(t);
}

ListNode * createListNode(TreeNode * treePtr)
{
    ListNode * newNode = malloc(sizeof(ListNode));
    newNode -> ptr = treePtr;
    newNode -> next = NULL;
    return newNode;
}

ListNode * insertNode(ListNode * head, ListNode * toInsert)
{
    if (head == NULL)
    {
        return toInsert; // No head, toInsert is new head
    }
    if (toInsert == NULL)
    {
        printf("Error. ListNode to insert is NULL.\n");
        exit(1);
    }
    if ((toInsert -> next) != NULL)
    {
        printf("toInsert-> next must be NULL.\n");
        exit(1);
    }

    if (compareFreq(head, toInsert) == 1) // character frequency of the newNode is smaller than the head's
    {
        toInsert -> next = head;
        return toInsert;  // Return the head
    }
    head -> next = insertNode(head -> next, toInsert);
    return head;
}

int compareFreq(ListNode * head, ListNode * toInsert) //Return 1 if the new node needs to be inserted before
{
    long freq1 = (toInsert -> ptr) -> frequency;
    long freq2 = (head -> ptr) -> frequency;
    if (freq1 < freq2) // character frequency of the newNode is smaller than the head's
    {
        return 1;
    }
    else if (freq2 < freq1)
    {
        return 0;
    }
    else if (freq1 == freq2)
    {
        if ((toInsert->ptr->val < head->ptr->val) && (toInsert->ptr->left == NULL) && (toInsert->ptr->right == NULL) ) //Compare both ASCII values
        {
            return 1;
        }
    }
    return 0;
}

//Remake this function if error
ListNode * buildList(long * frequencies)
{
    int index = 0;
    while (frequencies[index] == 0)
    {
        index++;
    }
    if (index == ASCII_SIZE) //Amount of letters
    {
        return NULL; //No input
    }
    ListNode * head = NULL;
    while (index < ASCII_SIZE)
    {
        if (frequencies[index] > 0 && index != 13)
        {
            char character = index;
            TreeNode * tn = createTreeNode(character, frequencies[index]);
            ListNode * ln = createListNode(tn);
            head = insertNode(head, ln);
        }
        index++;
    }
    return head;
}

void freeList(ListNode * head)
{
    while (head != NULL)
    {
        ListNode *p = head -> next;
        freeTree(head->ptr);
        free(head);
        head = p;
    }
}