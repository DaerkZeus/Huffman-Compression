CFLAGS = -std=c99 -g -Wall -Wshadow -Wvla -Werror
GCC = gcc $(CFLAGS)
EXEC = test_huffman
OBJS =  main.o huffman.o struct.o header.o utility.o
VALGRIND = valgrind --tool=memcheck --leak-check=yes --verbose --leak-check=full --show-leak-kinds=all

all: $(OBJS) huffman.h struct.h header.h utility.h
	$(GCC) $(OBJS) -o $(EXEC)

huffman: all
	./$(EXEC) inputs/basic basic_sorted basic_huffman basic_header

	./$(EXEC) inputs/gophers gophers_sorted gophers_huffman gophers_header

	./$(EXEC) inputs/para para_sorted para_huffman para_header

	./$(EXEC) inputs/prideandprejudice prideandprejudice_sorted prideandprejudice_huffman prideandprejudice_header

	./$(EXEC) inputs/woods woods_sorted woods_huffman woods_header
	
memory: all
	$(VALGRIND) --log-file=log1 ./$(EXEC) inputs/basic basic_sorted basic_huffman basic_header
	$(VALGRIND) --log-file=log2 ./$(EXEC) inputs/gophers gophers_sorted gophers_huffman gophers_header
	$(VALGRIND) --log-file=log3 ./$(EXEC) inputs/para para_sorted para_huffman para_header
	$(VALGRIND) --log-file=log4 ./$(EXEC) inputs/prideandprejudice prideandprejudice_sorted prideandprejudice_huffman prideandprejudice_header
	$(VALGRIND) --log-file=log5 ./$(EXEC) inputs/woods woods_sorted woods_huffman woods_header


%.o : %.c
	$(GCC) -c $<

clean:
	/bin/rm -f *.o
	/bin/rm -f $(EXEC)
	/bin/rm -f basic* gophers* para* prideandprejudice* woods* log?