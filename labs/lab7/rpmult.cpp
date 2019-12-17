/*******************************************************************************
 * Name          : rpmult.cpp
 * Author        : Zachary Talarick
 * Version       : 1.0
 * Date          : 3/28/19
 * Description   : Performs Russian Peasant Multiplication.
 * Pledge        : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <algorithm>
#include <sstream>

using namespace std;

unsigned long russian_peasant_multiplication(unsigned int m, unsigned int n) {
//	if (m < n){
//		m = m ^ n;
//		n = m ^ n;
//		m = m ^ n;
//	}
	long m2 = m;
	long n2 = n;
	long result = 0;
	while(n2 >= 1){
		if((n2 % 2) != 0){
			result += m2;
		}
		n2 = n2 >> 1;
		m2 = m2 << 1;
	}
    return result;
}

int main(int argc, char* const argv[]) {
    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " <integer m> <integer n>" << endl;
        return 1;
    }

    int m, n;
    istringstream iss;

    iss.str(argv[1]);
    if ( !(iss >> m) || m < 0 ) {
        cerr << "Error: The first argument is not a valid nonnegative integer."
             << endl;
        return 1;
    }

    iss.clear();
    iss.str(argv[2]);
    if ( !(iss >> n) || n < 0 ) {
        cerr << "Error: The second argument is not a valid nonnegative integer."
             << endl;
        return 1;
    }

    // TODO - produce output
	cout << m << " x " << n << " = " << russian_peasant_multiplication(m, n) << endl;

    return 0;
}
