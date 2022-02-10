#include "header.h"
#include "utility.h"

static void headerHelper(TreeNode * tn, FILE * fptrOut, unsigned char * currentBit, unsigned char * currentByte)
{
    if (tn == NULL)
    {
        return; 
    }
    TreeNode *lc = tn -> left;
    TreeNode *rc = tn -> right;
    unsigned char currentChar = tn->val;
    unsigned char temp;
    unsigned char mask = 0b10000000; // Bit mask
    if ((lc == NULL) && (rc == NULL))
    {
        writeBit(fptrOut, 1, currentBit, currentByte);
        for (int i = 0; i < 8; i++)
        {
            // Bitwise comparaison to determine equivalent binary value to write
            temp = currentChar & mask;
            temp = temp >> (7 - i); 
            mask = mask >> 1;
            if (temp > 0)
            {
                writeBit(fptrOut, 1, currentBit, currentByte);
            }  
            else
            {
                writeBit(fptrOut, 0, currentBit, currentByte);
            }
        }
        return;
    }
    writeBit(fptrOut, 0, currentBit, currentByte);
    headerHelper(lc, fptrOut, currentBit, currentByte);
    headerHelper(rc, fptrOut, currentBit, currentByte);
}

void preOrderHeader(TreeNode *tn, FILE * fptrOut)
{
    unsigned char currentBit = 0;
    unsigned char currentByte = 0;
    if (fptrOut == NULL)
    {
        return;
    }
    // Encode binary tree
    headerHelper(tn, fptrOut, &currentBit, &currentByte);
    // Pad zero value bit to last byte
    padZero(fptrOut, &currentBit, &currentByte);
}