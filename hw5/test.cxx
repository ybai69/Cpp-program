#include <fstream>
#include <iostream>
#include <iomanip>
#include <string>
#include <cassert>
#include <cstdlib>
#include "Bit_Vector.h"

using namespace std;


int main () {
	char str[256];
	std::cout << "Enter the name of an existing text file: ";
	std::cin.get (str,256);    // get c-string, file names
	// We already know three input/output streams: the input stream
    // cin and the output streams cout and cerr. Here we use file
    // streams for reading from and writing to files.
    ifstream ifs;             // Declare an input file stream variable, ifs.
    ifs.open(str); // Open ifs to read from the file helloIn.txt.
    assert(ifs.good());       // Stop program if open() failed.

    ofstream ofs;             // Declare an output file stream variable, ofs.
    ofs.open("Out.txt"); // Open ofs to write to the file helloOut.txt.
    assert(ofs.good());
    int i;                    // The input stream function get()
                              // returns an int, not a char, to be able
                              // to encode any char, plus the
                              // additional value EOF (end of file).
    // This loop runs while we can read a character i from helloIn.txt
    // and we have not reached the end-of-file.)
//  while ((i = ifs.get()) && !ifs.eof()) { // JOHN HAD THIS WRONG.
    while ((i = ifs.get()) != EOF) {
	char c = i;
	ofs << c << endl;     // Write c and a newline to helloOut.txt.
    }
    ifs.close();              // Close 
    ofs.close();



	return 0;
}