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



    int frequencies[256]={0};
    int i;
    while ((i = ifs.get()) != EOF){
        int c = i;
        //cout << c << endl;
        frequencies[c]++;
    }

     for (int c = 0; c <= 255; c++){
        char b = c;
        cout << b << " : " << frequencies[c] << endl;
    }

    ifs.close();              // Close 

	return 0;
}


