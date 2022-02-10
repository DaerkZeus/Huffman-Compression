# Huffman-Compression

This Huffman Compression model is used for lossless compression for text files. It greatly reduces the amount of memory necessary to represent a file and therefore can be used to compress files for various beneficial reasons. The files are written in C and make use of data structures such as linked list and binary trees.

From a file as input, Huffman Compression is used to create 3 files with: 
- a list of characters and their frequencies
- a codebook with the binary code associated with each character
- a binary code that represents the header input file using pre-order traversal on the Huffman Tree 

The list of characters is simply defined by the _countLetters_ function in the main.c file. 

The codebook is defined by huffman.c file. A Huffman tree is first created and then traversed to create a 2D array containing the characters and the binary code used to represent it. The code is essentialy with path is the character at in the Huffman Tree.

Finally, the binary code to represent the header of the input file is defined in the header.c file. A simple binary mask is used and applied using bitwise operations with the values in the Huffman Tree. The resulting values are then converted to single bits that are written to a new file. 

If needed the header.c file can be reused using the same logic to convert an entire text file into its binary equivalent. 


Note: The main function is built to work with a Makefile file and the functions expect an ouput file as argument. For reference, test inputs files, expected ouputs and a Makefile are provided. Feel free to modify the Makefile for your own input files.


Commands for the program using the provided Makefile are:
```
make huffman // Compile and run
make memory // Memory report for debugging using Valgrind
make clean // Clear output files and object files
```


