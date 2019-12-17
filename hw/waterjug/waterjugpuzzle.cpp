//We pledge our honor that we have abided by the Stevens Honor System.
//Ryan Byrne
//Zach Talarick

#include <iostream>
#include <sstream>
#include <vector>
#include <ctype.h>
#include <string>

using namespace std;

struct State {
    int a, b, c;
    string direction = "NULL";
    State(int _a, int _b, int _c) : a(_a), b(_b), c(_c) { }

    // String representation of state in tuple form.
    string to_string() {
        ostringstream oss;
        oss << "(" << a << ", " << b << ", " << c << ")";
        return oss.str();
    }
};

int pour(State *state, int *jug_0, int *jug_1, int max_jug_1) {
  //pours jug_0 to jug_1 and returns the gallons moved
  if (*jug_0 <= 0 || *jug_1 == max_jug_1) {
    return -1;
  }

  int init = *jug_1;

  if (*jug_1 + *jug_0 >= max_jug_1){
    *jug_0 = *jug_0 - (max_jug_1 - *jug_1);
    *jug_1 = max_jug_1;
  }
  else {
    *jug_1 = *jug_0 + *jug_1;
    *jug_0 = 0;
  }

  int gallons =  *jug_1 - init;
  return gallons;
}

vector<State> getChildren(int max_a, int max_b, int max_c, State parent) {
  //returns all possible pours from given state
  vector<State> children;
  string s1 = " gallon";
  string s2 = " gallons";
  State child1(parent.a, parent.b, parent.c);
  State child2(parent.a, parent.b, parent.c);
  State child3(parent.a, parent.b, parent.c);
  State child4(parent.a, parent.b, parent.c);
  State child5(parent.a, parent.b, parent.c);
  State child6(parent.a, parent.b, parent.c);

  int gallons = pour(&child1, &(child1.c), &(child1.a), max_a);
  if (gallons == 1)
    child1.direction = "Pour " + to_string(gallons) + s1 + " from C to A. " + child1.to_string();
  else
    child1.direction = "Pour " + to_string(gallons) + s2 + " from C to A. " + child1.to_string();

  gallons = pour(&child2, &(child2.b), &(child2.a), max_a);
  if (gallons == 1)
    child2.direction = "Pour " + to_string(gallons) + s1 + " from B to A. " + child2.to_string();
  else
    child2.direction = "Pour " + to_string(gallons) + s2 + " from B to A. " + child2.to_string();

  gallons = pour(&child3, &(child3.c), &(child3.b), max_b);
  if (gallons == 1)
    child3.direction = "Pour " + to_string(gallons) + s1 + " from C to B. " + child3.to_string();
  else
    child3.direction = "Pour " + to_string(gallons) + s2 + " from C to B. " + child3.to_string();

  gallons = pour(&child4, &(child4.a), &(child4.b), max_b);
  if (gallons == 1)
    child4.direction = "Pour " + to_string(gallons) + s1 + " from A to B. " + child4.to_string();
  else
    child4.direction = "Pour " + to_string(gallons) + s2 + " from A to B. " + child4.to_string();

  gallons = pour(&child5, &(child5.b), &(child5.c), max_c);
  if (gallons == 1)
    child5.direction = "Pour " + to_string(gallons) + s1 + " from B to C. " + child5.to_string();
  else
    child5.direction = "Pour " + to_string(gallons) + s2 + " from B to C. " + child5.to_string();

  gallons = pour(&child6, &(child6.a), &(child6.c), max_c);
  if (gallons == 1)
    child6.direction = "Pour " + to_string(gallons) + s1 + " from A to C. " + child6.to_string();
  else
    child6.direction = "Pour " + to_string(gallons) + s2 + " from A to C. " + child6.to_string();

  children.push_back(child1);
  children.push_back(child2);
  children.push_back(child3);
  children.push_back(child4);
  children.push_back(child5);
  children.push_back(child6);

  return children;
}

vector<State> getParents(State state, vector<vector<State*>> matrix) {
  //goes through matrix and receives the lineage of states to get to end goal
  vector<State> states;
  states.push_back(state);
  State * parent_pointer = matrix[state.a][state.b];
  State parent = *parent_pointer;

  while (!(parent.a == 0 && parent.b == 0)) {
    states.push_back(parent);
    parent_pointer = matrix[parent.a][parent.b];
    parent = * parent_pointer;
  }
  return states;
}

void printDirs(State state, vector<vector<State*>> matrix, State first_state) {
  //prints the lineage of states' directions
  cout << "Initial state. "<< first_state.to_string() << endl;
  vector<State> states = getParents(state, matrix);
  while (!states.empty()) {
    cout << states.back().direction << endl;
    states.pop_back();
  }
}


void search(vector<State> states, vector<vector<State*>> matrix, int max_a, int max_b, int max_c, int goal_a, int goal_b, State first) {
  //main function... searches for optimal path to goal
  if (states.empty()) {
    cout << "No solution." << endl;
    return;
  }

  vector<State> all_children;

  for (unsigned int i = 0; i<states.size(); i++){
    State *current = &(states[i]);

    if (current->a == goal_a && current->b == goal_b) {
      cout << "Initial state. " << current->to_string() << endl;
      return;
    }

    vector<State> children = getChildren(max_a, max_b, max_c, *current);

    for (unsigned int j=0; j<children.size(); j++) {
      State child = children[j];

      if (matrix[child.a][child.b]) {
        continue;
      }

      matrix[child.a][child.b] = current;

      all_children.push_back(child);
      if (child.a == goal_a && child.b == goal_b) {
        printDirs(child, matrix, first);
        return;
      }
    }
  }

  return search(all_children, matrix, max_a, max_b, max_c, goal_a, goal_b, first);
}

bool isnumber(string s) {
  for (unsigned int i=0; i<s.length(); i++) {
    if (!isdigit(s[i]))
      return false;
  }
  return true;
}


int main(int argc, char * argv[]) {
    // **[ARGUMENT CHECKING]**

    //Check if number of arguments is correct
    if (argc != 7) {
      cout << "Usage: " << argv[0] << " <cap A> <cap B> <cap C> <goal A> <goal B> <goal C>" << endl;
      return 1;
    }

    //Check if argument types are correct
    vector<string> args;
    args.push_back("jug A");
    args.push_back("jug B");
    args.push_back("jug C");

    for (int i=1; i<argc; i++) {


      if (i < 4) {
        if (!isnumber(argv[i]) || atoi(argv[i]) < 1) {
          cout << "Error: Invalid capacity '" << argv[i] << "' for " << args.at((i-1)%3) << "." << endl;
          return 1;
        }
        if (atoi(argv[i]) < 0) {
          cout << "Invalid goal '" << argv[i] << "' for " << args[i-3] << "." << endl;
          return 1;
        }
      }
      else {
        if (!isnumber(argv[i])) {
          cout << "Error: Invalid goal '" << argv[i] << "' for " << args.at((i-1)%3) << "." << endl;
          return 1;
        }
        if (atoi(argv[i]) < 0) {
          cout << "Invalid capacity '" << argv[i] << "' for " << args[i-3] << "." << endl;
          return 1;
        }
      }
    }

    //initialize arguments
    const int max_a = atoi(argv[1]);
    const int max_b = atoi(argv[2]);
    const int max_c = atoi(argv[3]);
    const int goal_a = atoi(argv[4]);
    const int goal_b = atoi(argv[5]);
    const int goal_c = atoi(argv[6]);

    //more arg checking
    if (goal_a > max_a) {
      cout << "Error: Goal cannot exceed capacity of jug A." << endl;
      return 1;
    }
    if (goal_b > max_b) {
      cout << "Error: Goal cannot exceed capacity of jug B." << endl;
      return 1;
    }
    if (goal_c > max_c) {
      cout << "Error: Goal cannot exceed capacity of jug C." << endl;
      return 1;
    }


    if (goal_a + goal_b + goal_c != max_c) {
      cout << "Error: Total gallons in goal state must be equal to the capacity of jug C." << endl;
      return 1;
    }

    //initialize matrix
    vector<vector<State*>> matrix;
    matrix.resize(max_a + 1);
    for (unsigned int i=0; i<matrix.size(); i++){
      matrix[i].resize(max_b + 1);
    }


    State init(0, 0, max_c);
    vector<State> states;
    states.push_back(init);

    matrix[0][0] = &init;
    // **[ ANALYSIS ]**

    //begin analyzing
    search(states, matrix, max_a, max_b, max_c, goal_a, goal_b, init);


    return 0;

}
