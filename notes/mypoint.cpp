#include <iostream>
#include <iomanip> //for manipulating i/o
#include <vector> //like arrayList (resizeable array)

using namespace std;

class MyPoint{
public:
	//Constructor that uses an initializer list
	//the order that the member variables are declared is the same exact order that they must be intialized in the initializer list
 	//all member variables must be intialized in construcctor
	MyPoint(int x, int y, float z) : x_{x}, y_{y}, z_{z} { } //?????? there is no super() so it needs to be done this way
	
	//Methods that do not modify member variables should be declared const
	void print_cords() const {
		cout << "(x, y, z) = (" << x_ << ", " << y_ << ", " << fixed << setprecision(2) << z_ << ")" << endl;
	}
	
	//Mutator
	void set_x(int x){
		x_ = x;
	}
	
	//Accessor
	int get_x() const{
		return x_;	
	}
private:
	//Member Variables go here. use trailing _ for these variables.
	int x_, y_;
	float z_;
};

void display_points(const vector<MyPoint> &points){
	for(auto it = points.cbegin(); it != points.cend(); ++it){
		it->print_cords();
	}
} 

int main(){
	int x, y;

	MyPoint point1 (5, 7, 1.98324523);
	MyPoint point2 (1, 2, 3.95324523);
	MyPoint point3 (4, 5, 6.78324523);

	vector<MyPoint> points;
	
	points.push_back(point1); //If the object is on the stack use dot notation to call functions
	points.push_back(point2);
	points.push_back(point3);
				  
	vector<MyPoint> points_above_two;
	for(const auto &point : points){
		if(point.get_x() > 2){
			points_above_two.push_back(point); 
		}
	}
	
	display_points(points_above_two);

	//Practice using standard in STDIN:
	cout << "Input x: ";
	cin >> x;
	cout << "Input y: ";
	cin >> y;


	MyPoint *point4 = new MyPoint(x, y, 7); //Use -> for objects on the heap
	point4 -> print_cords();
	delete point4;
	
	return 0;
}
