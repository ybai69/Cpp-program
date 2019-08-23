all: io bits c d test1 test2 

io: iostreamExample.cxx
	g++ -Wall -g -o io iostreamExample.cxx

Bit_Vector.o: Bit_Vector.h Bit_Vector.cxx
	g++ -Wall -g -c Bit_Vector.cxx

bitsExample.o: bitsExample.cxx
	g++ -Wall -g -c bitsExample.cxx

bits: Bit_Vector.o bitsExample.o
	g++ -Wall -g -o bits Bit_Vector.o bitsExample.o

decompress.o: decompress.cxx
	g++ -Wall -g -c decompress.cxx

d: Bit_Vector.o decompress.o
	g++ -Wall -g -o d Bit_Vector.o decompress.o

compress.o: compress.cxx
	g++ -Wall -g -c compress.cxx

c: Bit_Vector.o compress.o
	g++ -Wall -g -o c Bit_Vector.o compress.o
   
# ... you should write make commands to compile "c" and "d" ...

test1: c d data/simple
	cp data/simple test1  # Note: make requires TAB before each command
	./c test1 test1.huf
	./d test1.huf test1.huf.d
	cmp test1 test1.huf.d
	rm -f test1 test1.huf test1.huf.d


test2: c d data/unique_tree.huf
	cp data/unique_tree.huf test2.huf  # Note: make requires TAB before each command
	./d test2.huf test2.d
	./c test2.d test2.d.huf
	cmp test2.huf test2.d.huf
	rm -f test2.huf test2.d test2.d.huf


clean:
	rm -f io bits c d core *.o  	