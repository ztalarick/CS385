/*******************************************************************************
 * Name        : sieve.cpp
 * Author      : Zachary Talarick
 * Date        : 2/11/19
 * Description : Sieve of Eratosthenes
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>


using namespace std;

class PrimesSieve {
public:
    PrimesSieve(int limit) : is_prime_{new bool[limit + 1]}, limit_{limit} { //when constructor completes all member variables must be intialized
        sieve();
	num_primes_ = count_num_primes();
	
	int i = limit + 1;
	while(is_prime_[i] == false){
		i--;
	}
	max_prime_ = i;
    }

    ~PrimesSieve() { //destructor, gets rid of heap stuff
        delete [] is_prime_;
    }

    inline int num_primes() const {
        return num_primes_;
    }

    void display_primes() const {
        // TODO: write code to display the primes in the format specified in the
        // requirements document.
	const int max_prime_width = num_digits(max_prime_);
	const int primes_per_row = 80 / (max_prime_width + 1);

	
	cout << endl;
	cout << "Number of primes found: " << count_num_primes() << endl;
	cout << "Primes up to " << limit_ << ":" << endl;

	if(primes_per_row >= num_primes_){ //if primes fit on one row
		for(int k = 2; k < max_prime_; k++){
			if(is_prime_[k]){
				cout << k << " "; //no need to worry about setw here
			}		
		}
		cout << max_prime_ << endl; //loop ends one iteration early so there is no " " after the last digit
	}else{
		int prime_count = 0;
		for(int i = 2; i < max_prime_; i++){ //on the end of every line there is an extra space	
			if(prime_count == primes_per_row - 1 && is_prime_[i]){
				prime_count++;
				cout << setw(max_prime_width) << i;
				//continue;
			}else if(prime_count == primes_per_row){ //when number of primes reaches the primes per row
				prime_count = 0; //reset count
				cout << endl; //make a new row
			}else if(is_prime_[i]){ 
				cout << setw(max_prime_width) << i << " "; //sets width and prints number
				prime_count++; //increment prime count
			}
		}
		cout << max_prime_ << endl; //loop ends one iteration early so there is no " " after the last digit
	}	
    }

private:
    bool * const is_prime_;
    const int limit_;
    int num_primes_, max_prime_;

    int count_num_primes() const { 
        // TODO: write code to count the number of primes found
	int result = 0;
	for(int i = 2; i < limit_ + 1; i++){
		if(is_prime_[i]){ //when a prime is found
			result++; //increment the total
		}		
	}

	return result;
    }

    int num_digits(int num) const {
        // TODO: write code to determine how many digits are in an integer
        // Hint: No strings are needed. Keep dividing by 10.
	int result = 0; 
	while(num > 0){	//increments result until num < 1, should increment the number of digits 
		num /= 10; //reduce 1 digit
		result++; 
	}
	return result;
    }

    void sieve() {
        // TODO: write sieve algorithm
	for (int j = 2; j < limit_ + 1; j++){
		is_prime_[j] = true;
	}
	for(int i = 2; i <= sqrt(limit_); i++){
		if(is_prime_[i]){
			for(int j = i * i; j <= limit_; j += i){
				is_prime_[j] = false;
			}
		}	
	}
    }
};



int main() {
    cout << "**************************** " <<  "Sieve of Eratosthenes" <<
            " ****************************" << endl;
    cout << "Search for primes up to: ";
    string limit_str;
    cin >> limit_str;
    int limit;

    // Use stringstream for conversion. Don't forget to #include <sstream>
    istringstream iss(limit_str);

    // Check for error.
    if ( !(iss >> limit) ) {
        cerr << "Error: Input is not an integer." << endl;
        return 1;
    }
    if (limit < 2) {
        cerr << "Error: Input must be an integer >= 2." << endl;
        return 1;
    }

    // TODO: write code that uses your class to produce the desired output.
	PrimesSieve sieve(limit); //initialize sieve class with user input
	sieve.display_primes(); 

	
    return 0;
}
