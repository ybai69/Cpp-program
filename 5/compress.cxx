// compress.cxx: Collect character frequencies from infile, make
// Huffman code tree from frequencies, make code from tree, use code
// to compress infile. Write tree, newline, and Bit_Vector of
// compressed infile to outfile.

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <cassert>
#include <string>
#include <queue>      // STL, has priority_queue<T>
#include "Bit_Vector.h"

using namespace std;

//const int N_ASCII_VALUES = 128;
const size_t N_ASCII_VALUES = 256;

struct Tree {
    unsigned char data;
    int count; // sum of counts of char's in this subtree
    Tree *left;
    Tree *right;
};

// An instantiation of this struct is a "function object"; I don't
// quite understand this, but it's in Stroustrup's book and the STL.
struct Tree_priority {
    bool operator()(const Tree *x, const Tree *y) {
    return x->count > y->count;
    }
};

// Print tree at which root points in backwards inorder, which leads
// to a tree a person can read in the shell by turning his or her head
// to the left. Start by indenting level spaces.
void print(Tree *root, int level) {
    const int INDENTATION = 5;

    if (root) {
    print(root->right, level + 1);
    cerr << setw(level * INDENTATION) << " " << root->data << endl;
    print(root->left, level + 1);
    }
}

// Collect character counts from file, storing them in frequencies, an
// array of length n.
void collect_frequencies(int frequencies[], int n, const char *file) {
    // ...
    //frequencies[n]={0};
    int i;
    ifstream ifs;             // Declare an input file stream variable, ifs.
    ifs.open(file); // Open ifs to read from the file helloIn.txt.
    assert(ifs.good());       // Stop program if open() failed.
    while ((i = ifs.get()) != EOF){
        int c = i;
        frequencies[c]++;
    }

    //for (int c = 0; c < n; ++c){
    //    cout << c << " : " << frequencies[c] << endl;
    //}

}

//add a new function
Tree* makeNode(char ch, int count)
{
    Tree* tmp = new Tree();
    tmp->data = ch;
    tmp->count = count;
    tmp->left = NULL;
    tmp->right = NULL;
    return tmp;
};

// Return pointer to root of Huffman code tree made from character
// counts in frequencies, an array of size n.
Tree * build_tree_from_frequencies(int frequencies[], int n) {
    priority_queue<Tree *, vector<Tree *>, Tree_priority> pq;
    //Tree *root = new Tree(); // 0 is wrong, but I want this program to compile.

    // ...
    for(int i = 0; i < n; ++i){
        if (frequencies[i] > 0)
        {
            Tree* tmp = makeNode(i, frequencies[i]);
            pq.push(tmp);
        }
    }

    while(pq.size() > 1)
    {
        Tree* left = pq.top(); 
        pq.pop();
        Tree* right = pq.top();
        pq.pop();
        
        Tree* tmp = makeNode(0, left->count + right->count);
        tmp->left = left;
        tmp->right = right;
        
        pq.push(tmp);
    }
    
    return pq.top();
}

// Recursively traverse tree at which root points, building up code by
// adding '0' at each left branch or '1' at each right branch. At each
// leaf, write code into code_words[], an array of length n.
void write_code(const Tree *root, string code_words[], size_t n, string code) {
    // ...
    if(!root->left && !root->right)
    {
        code_words[root->data] = code;
    }
    if (root->right != NULL)
    {
        write_code(root->right,code_words,n,code+"1");
    }
    if (root->left != NULL)
    {
        write_code(root->left,code_words,n,code+"0");
    }

}

// Recursively dump tree at which root points to stream ofs.
void preorder(Tree *root, ostream &ofs) {
    // ...
    if (root == NULL)
          return;
 
     /* first print data of node */
    //printf(root->data); 
    if(int (root->data) ==0){
        ofs <<"\\*";
    }else{
        ofs << root->data;
    }
    
    //cout << root ->data;
 
     /* then recur on left sutree */
    preorder(root->left,ofs);  
 
     /* now recur on right subtree */
    preorder(root->right,ofs);
}

// Use the Huffman code tree at which root points to compress data in
// infile. Write tree and bits into outfile.
void compress_data(Tree *root, const char *infile, const char *outfile) {
    string code_words[N_ASCII_VALUES];
    // ...
    ifstream ifs;
    ifs.open(infile);
    assert(ifs.good()); 
    write_code(root, code_words, N_ASCII_VALUES, "");
    // cerr << code_words[97] << endl;
    // cerr << code_words[98] << endl;
    // cerr << code_words[99] << endl;
    // cerr << code_words[100] << endl;
    // cerr << code_words[101] << endl;
    // cerr << code_words[102] << endl;
    // ...

    Bit_Vector bits;
    ofstream ofs;
    ofs.open(outfile);
    assert(ofs.good());

    preorder(root,ofs);
    ofs << endl;


    int i;
    //while ((i = ifs.get()) != EOF){
    //    ofs << code_words[i];
    //}
    //ofs << endl;
    //ifs.open(infile);
    while ((i = ifs.get()) != EOF){
        string c = code_words[i];
        //cout << c<< endl;
        //cout << c.length()<< endl;
        for(size_t j=0; j < c.length(); ++j){
            bits.push_back(code_words[i][j]-'0');
        }    
    }
    bits.write(ofs);
    ofs.close();  
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
//  Collect character frequencies from infile, make Huffman code tree
// from frequencies, make code from tree, use code to compress
// infile. Write tree, newline, and Bit_Vector of compressed infile to
// outfile.
int main(int argc, char *argv[]) {
    int frequencies[N_ASCII_VALUES]={0};
    const char *infile, *outfile;

    if (argc != 3) {
    cerr << "usage: " << argv[0] << " <infile> <outfile>" << endl;
    exit(0);
    }
    infile = argv[1];
    outfile = argv[2];
    collect_frequencies(frequencies, N_ASCII_VALUES, infile);
    Tree *root = build_tree_from_frequencies(frequencies, N_ASCII_VALUES);
    //print(root, 0); // for debugging
    compress_data(root, infile, outfile);
    destroy_tree(root);

    return 0;
}