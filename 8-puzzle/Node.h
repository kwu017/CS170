#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class Node {
	public:
		vector<vector<int> > s; //current state
		int g, h;

		Node(vector<vector<int> > state) { //default constructor
			s = state;
			g = 0;
			h = 0;
		}

		Node(Node* k) { //copy constructor
			s = k->s;
			g = k->g;
			h = k->h;
			//cout << "copied :)" << endl;
		}
};