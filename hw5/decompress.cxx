// decompress.cxx: Read input from file containing prefix tree,
// newline, and Bit_Vector of encoded data. Write decoded data to new
// file.

#include <fstream>
#include <iostream>
#include <iomanip>
#include <string>
#include <cassert>
#include <cstdlib>
#include "Bit_Vector.h"

using namespace std;

struct Tree {
    char data;
    Tree *left;
    Tree *right;
};

// Print tree at which root points in backwards inorder, which leads
// to a tree a person can read in the shell by turning his or her head
// to the left. Start by indenting level spaces.
void print(const Tree *root, int level) {
    const int INDENTATION = 5;

    if (root) {
        print(root->right, level + 1);
        cerr << setw(level * INDENTATION) << " " << root->data << endl;
        print(root->left, level + 1);
    }
}

// Recursively build a tree by reading characters (where the
// two-character sequence "\*" denotes an internal node and any other
// character denotes a leaf) from stream ifs. Return a pointer to the
// tree's root. (Hint: Do not use a loop! Trust recursion.)
Tree * maketree(ifstream &ifs) {
    bool leaf = true;
    char ch = ifs.get();

    if (ch == '\n')
        return 0;

    Tree *p = new Tree(); // 0 is wrong, but I want this program to compile.

    if (ch == '\\')
    {
        ch = ifs.get();
        if (ch == '*') leaf = false;
    }

    if (leaf)
    {
        p->data = ch;
        p->left = 0;
        p->right = 0;
    }
    else
    {
        p->left = maketree(ifs);
        p->right = maketree(ifs);
    }

    return p;
}

// Given the Huffman code tree at which root points, read a compressed
// file from stream ifs and write its decompressed version to ofs.
void decompress(const Tree *root, ifstream &ifs, ofstream &ofs) {
    Bit_Vector bits;
    bits.read(ifs);

    const Tree* p = root;
    for (size_t i = 0; i < bits.size();i++)
    {
        if (bits[i] == 0)
        {
            p = p->left;
        }
        else
        {
            p = p->right;
        }

        if (p->left == 0 && p->right == 0) // leaf
        {
            ofs << p->data;
            cout << p->data;
            p = root;
        }
    }
}

// Recursively de-allocate memory used by tree at which root points.
void destroy_tree(Tree *root) {
    if (root) {
        destroy_tree(root->left);
        destroy_tree(root->right);
        delete root;
    }
}

// (This comment is repeated from the top of the file, which is not a
// great idea.)
//
// Read input from file containing prefix tree, newline, and
// Bit_Vector of encoded data. Write decoded data to new file.
int main(int argc, char *argv[]) {
    if (argc != 3) {
        cerr << "usage: " << argv[0] << " <infile> <outfile>" << endl;
        exit(0);
    }

    ifstream ifs(argv[1]);
    assert(ifs);
    ofstream ofs(argv[2]);
    assert(ofs);

    Tree *root = maketree(ifs);

    decompress(root, ifs, ofs);

    ifs.close();
    ofs.close();

    destroy_tree(root);
    //system("pause");
    return 0;
}