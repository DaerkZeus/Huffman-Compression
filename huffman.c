#include "huffman.h"

ListNode * createHuffmanTree(long * frequencies, ListNode * head)
{
    if (head == NULL)
    {
        printf("The list is empty.\n");
        return head;
    }
    while (head -> next != NULL)
    {
        ListNode *second = head -> next; // 2nd node in the list
        ListNode *third = second -> next; // 3rd node in the list (may be empty)
        TreeNode * tn1 = head -> ptr;
        TreeNode * tn2 = second ->ptr;

        free(head); 
        free(second);
        head = third; //New head
        
        TreeNode * merged = mergeTree(tn1, tn2); 
        ListNode * mergedListNode = createListNode(merged);
        head = insertNode(head, mergedListNode); 
    }
    return head; // A single listNode that points to a Huffman binary tree
}

long treeDepth(TreeNode *tn)
{
    if (tn == NULL)
    {
        return 0;
    }
    long hLeft = treeDepth(tn->left);
    long hRight = treeDepth(tn->right);
    long height;
    if (hLeft > hRight)
    {
        height = hLeft;
    }
    else
    {
        height = hRight;
    }
    return (height + 1);
}

long numLeaf(TreeNode * tn)
{
    long num = 0;
    numLeafHelper(tn, &num);
    return num;
}

void numLeafHelper(TreeNode * tn, long * num)
{
    if (tn == NULL)
    {
        return;
    }
    TreeNode *lc = tn -> left;
    TreeNode *rc = tn -> right;
    if ((lc == NULL) && (rc == NULL))
    {
        (*num)++;
        return;
    }
    numLeafHelper(lc, num);
    numLeafHelper(rc, num);
}

int ** createCodeBook(ListNode * head, long * numRows)
{
    TreeNode * root = head -> ptr;
    long totalRows = numLeaf(root);
    (*numRows) = totalRows;
    long totalCols = treeDepth(root);
    totalCols++; // Takes into account the ending(-1 to define the end of the code)
    int ** codebook = malloc(sizeof(int * ) * totalRows);
    for (int row = 0; row < totalRows; row++)
    {
        codebook[row] = malloc(sizeof(int) * totalCols);
        for (int col = 0; col < totalCols; col++)
        {
            codebook[row][col] = -1;
        }
    }
    return codebook;
}

void buildCodeBook(TreeNode * root, int ** codebook)
{
    long row = 0;
    long col = 1;
    codebookHelper(root, codebook, &row, col); // 0 stores the character, 1 is the start of the book
}

void codebookHelper(TreeNode * tn, int ** codebook, long * row, long col)
{
    if (tn == NULL)
    {
        return;
    }
    // Check if leaf node. If yes, create the code for that character
    TreeNode * lc = tn -> left;
    TreeNode * rc = tn -> right;
    if ((lc == NULL) && (rc == NULL))
    {
        codebook[*row][0] = tn -> val;
        (*row)++; //Go to the next character
        return;
    } 
    if (lc != NULL) // Going to the left child -> translates to a '0' in the codebook
    { //This node fill the colum of the entire subtree of 0
        long numRow = numLeaf(lc);
        long index; 
        for (index = *row; index < (*row) + numRow; index++)
        {
            codebook[index][col] = 0; 
        }
        codebookHelper(lc, codebook, row, col + 1);
    }
    if (rc != NULL)
    {
        long numRow = numLeaf(rc);
        long index; 
        for (index = (*row); index < (*row) + numRow; index++)
        {
            codebook[index][col] = 1;
        }
        codebookHelper(rc, codebook, row, col + 1);
    }
}

void printCodeBook(int ** codebook, long totalRows, FILE * fptr)
{
    for (int row = 0; row < totalRows; row++)
    {
        fprintf(fptr, "%c:", codebook[row][0]);
        int col = 1;
        while (codebook[row][col] != -1)
        {
            fprintf(fptr, "%d", codebook[row][col]);
            col++;
        }
        fprintf(fptr, "\n");
    }

}