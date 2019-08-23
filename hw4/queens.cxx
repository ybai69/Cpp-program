// Last name: Bai 
// First name: Yue
// NetID: bai42

// queens.cxx: runs stack-based backtracking search to solve n-queens
// problem.

#include <iostream>
#include <cstdlib>
#include "Stack.h"

using namespace std;

// ... You're welcome to add function prototypes of your own design
// here.  Put corresponding implementations below main().

// Runs n-queens search.  Prints queen configuration if there's a
// solution; otherwise prints "no solution exists".  If "debug" is
// true, also prints each configuration of queens encountered during
// the search.
bool isSafe(int n, Stack<int> &s);
void queens_search(int n, bool debug);
void printBoard(int n, Stack<int> &s,int k);

// I've written main() for you.

int main(int argc, char *argv[]) {
   
    int n_queens;
    bool debug = false;

    if (!(argc == 2 || argc == 3)) {
	cerr << "usage: " << argv[0]
	     << " <n_queens> [<optional 'd' means debug>]"
	     << endl;
	return 0;
    }

    n_queens = atoi(argv[1]);
    if (argc == 3) {
	debug = (argv[2][0] == 'd');
    }
  
    queens_search(n_queens, debug);

    return 0;
}


/*
int main(){
  int n_queens;
  cin >> n_queens;
  bool debug = true;
  queens_search(n_queens, debug);
}
*/

// Check if a position is safe

// n means n_th queen
// position means n_the queen's column position

bool isSafe(int n, Stack<int> &s)
{
	// Check each queen before this ones
	int position = s[n];
	for (int i = 0; i < n; i++)
	{
		// Get another queen's position
		int other_pos = s[i];

		// Now check if they're in the same column or diagonals
		if (other_pos == position || // Same column
			other_pos == position - (n - i) || // Same diagonal
			other_pos == position + (n - i))   // Same diagonal
			return false;
	}
	return true;
}


void queens_search(int n, bool debug) {
  Stack<int> s;
  if (debug) {
	cerr << "n=" << n << ", debug=" << debug << endl;
    }
    
    // ... your code here ...
    int k = 0;
    s.push(0);
    if(debug){
          s.debug();
          printBoard(n,s,k);
        }
    int step = 1;
    do{
      if(isSafe(k,s)){
        if (k == n - 1)
          break;
        s.push(0);
        k++;
        if(debug){
          s.debug();
          printBoard(n,s,k);
        }
        step ++;
        
      }else{
        int move;
        do{
          if(s.empty()){
            cout << "no solution" <<endl;
            return;
          }
          move = s.pop();
          k--;
          
        }while(move >= (n-1));
        s.push(move+1);
        k++;
        if(debug){
          s.debug();
          printBoard(n,s,k);
        }
        step ++;
        
      }
      //cout << k << endl;
    }while(k <= (n-1));
    s.debug();
    printBoard(n,s,k);
    cout << "total steps: " <<step <<endl;

  
}



void printBoard(int n, Stack<int> &s, int k){
  
  int n_line = 4*n+1;
  cout <<"   ";
  for(int i = 0 ; i < n; i++){
    cout <<" ";
    cout <<" " <<i;
    cout <<" ";
  }
  cout << endl;
  cout <<"   ";
  for (int i = 0 ;i< n_line; i++){
    cout << "-";
    //int line[i]=
  }
  //cout << line_1;
  cout << endl;
  for ( int i =0; i < n; i++){
    int pos = -1;
    if (i <= k) {
      pos = 4*s[i]+2;
    }
    cout<< i << "  ";
    //cout << "pos" <<pos ;
    for ( int j =0; j < n_line; j ++){
      if ( j != pos && j%4==0  ){
        cout << "|";
      }else if ( j != pos && j%4!=0  ){
        cout << " ";
      }else if(i <= k){
        cout << "Q";
      }else{
        cout << " ";
      }
    }
    cout <<endl;
    
    cout<< "   ";
    for (int i = 0 ;i< n_line; i++){
    cout << "-";
    }
    cout << endl;
  }
}