//I pledge my honor that I have abided by the Stevens Honor System.
//Zachary Talarick

#include <iostream>
#include <sstream>
#include <cstdlib>

using namespace std;

int gcd_iterative(int m, int n){
	int r = 0;
	while(n != 0){
		r = m % n;
		m = n;
		n = r;
	}
	return abs(m);
}

int gcd_recursive(int m, int n){
	int r = 0;
	if(n == 0){
		return abs(m);
	}
	r = m % n;
	return gcd_recursive(n, r);
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
	cout << "Iterative: gcd(" << m << ", " << n << ") = " << gcd_iterative(m, n) << endl;
	cout << "Recursive: gcd(" << m << ", " << n << ") = " << gcd_recursive(m, n) << endl;
	return 0;
}
