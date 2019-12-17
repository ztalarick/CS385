/*******************************************************************************
 * Name        : stairclimber.cpp
 * Author      : Zachary Talarick
 * Date        : 2/26/19
 * Description : Lists the number of ways to climb n stairs.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>

using namespace std;

int numstairs = 0;
int num_digits(int num){
	int result = 0; 
	while(num > 0){	//increments result until num < 1, should increment the number of digits 
		num /= 10; //reduce 1 digit
		result++; 
	}
	return result;
}

vector< vector<int> > get_ways(int num_stairs) {
    // TODO: Return a vector of vectors of ints representing
    // the different combinations of ways to climb num_stairs
    // stairs, moving up either 1, 2, or 3 stairs at a time.

	vector< vector<int> > ways; //empty vector
	if(num_stairs <= 0){
		ways.insert(ways.begin(), vector<int>());	
	}else{
		for(int i = 1; i < 4; i++){
			if(num_stairs >= i){
				vector< vector<int> > result = get_ways(num_stairs - i);
				int resSize = result.size();
				for(int j = 0; j < resSize; j++){ //inefficient to check for result.size() every iteration
					result[j].insert(result[j].begin(), i);
					
				}
				ways.insert(ways.end(), result.begin(), result.end());
			}

		}
	}
	return ways;
}

void display_ways(const vector< vector<int> > &ways) {
    // TODO: Display the ways to climb stairs by iterating over
    // the vector of vectors and printing each combination.
	int count = 1;
	unsigned int waysSize = ways.size();

	if(numstairs == 1){
		cout << waysSize << " way to climb " << numstairs << " stair." << endl;
	}else{
		cout << waysSize << " ways to climb " << numstairs << " stairs." << endl;	
	}
	 //fix check if 1 for multiple stair/s 

	for(unsigned int i = 0; i < waysSize; i++){
		if(num_digits(waysSize) > num_digits(count)){
			cout << " ";		
		}
		cout << count << ". [";
		count++;
		unsigned int size2 = ways[i].size();
		for(unsigned int j = 0; j < size2 - 1; j++){
			cout << ways[i][j] << ", ";
		}
		cout << ways[i][ways[i].size() - 1] << "]" << endl;
	}
	cout << endl;
	
}

int main(int argc, char * const argv[]) {
	int num_stairs;
	istringstream iss;
	if(argc != 2){
		cerr << "Usage: ./stairclimber <number of stairs>" << endl;
		return 1;
	}
	iss.str(argv[1]);
	if((iss >> num_stairs).fail() || num_stairs <= 0){
		cerr <<	"Error: Number of stairs must be a positive integer." << endl;
		return 1;
	}
	numstairs = num_stairs;
	display_ways(get_ways(num_stairs));
	
	return 0;
}
