/*******************************************************************************
 * Name        : unique.cpp
 * Author      : Zachary Talarick
 * Date        : 2/20/19
 * Description : Determining uniqueness of chars with int as bit vector.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/

#include <iostream>
#include <cctype>

using namespace std;

bool is_all_lowercase(const string &s) {
    // TODO: returns true if all characters in string are lowercase
    // letters in the English alphabet; false otherwise.
	int i = 0;
	while(s[i]){ //iterate over entire string
		if(!islower(s[i])){ //check if each letter is lowercase
			return false;		
		}
		i++;
	}
	return true;
}

bool all_unique_letters(const string &s) {
    // TODO: returns true if all letters in string are unique, that is
    // no duplicates are found; false otherwise.
    // You may use only a single int for storage and work with bitwise
    // and bitshifting operators.
    // No credit will be given for other solutions.
	unsigned int vector = 0;
	int i = 0;
	while(s[i]){
		if((vector & (1 << (s[i] - 'a'))) > 0){ //shifting s[i] - 'a' by 1 gives it the appropriate value, 
			return false; 
		}
		vector |= (1 << (s[i] - 'a')); //checks if letters are still unique, records previous chars
		i++;
	}
	return true;
}

int main(int argc, char * const argv[]) {
    // TODO: reads and parses command line arguments.
    // Calls other functions to produce correct output.
	if(argc != 2){ //improper argument number
		cout << "Usage: ./unique <string>" << endl;
		return -1;
	}	
	if(!is_all_lowercase(argv[1])){ //not all lowercase letters
		cout << "Error: String must contain only lowercase letters." << endl;
		return -1;
	}
	if(all_unique_letters(argv[1])){
		cout << "All letters are unique." << endl;	
	}else{
		cout << "Duplicate letters found." << endl;
	}
		
	return 0;
}
