/*
	find max between two inputs
	when executing -> ./test 35 72
	output 72
	
	argv array is a pointer to an array of strings (string is array of chars like c)
	argv[0] = ./test\0
	argv[1] = 35\0
	argv[2] = 72\0
	
	argc = 3 (number of strings pointed to by argv)
*/

#include <iostream>
#include <sstream>

using namespace std;

int max(int m, int n){
	return m > n ? m : n; //if a > b return a, else return b
}

int main(int argc, char *argv[]){
	int m, n;
	istringstream iss;
	
	if(argc != 3){
		cerr << "Usage: " << argv[0] << " <integer m> <integer n>" << endl;
		return 1; 
	}

	iss.str(argv[1]); //convert to int
	if(!(iss >> m)){
		cerr << "Error: The first argument is not a valid integer." << endl;
		return 1;
	}

	iss.clear();
	iss.str(argv[2]);
	if(!(iss >> n)){
		cerr << "Error: The second argument is not a valid integer." << endl;
		return 1;
	}
	cout << "max(" << m << ", " << n << ") = " << max(m, n) << endl;
	
	return 0;
}
