#include <iostream>
#include <map>
#include <algorithm>
#include <cmath>

#include "Node.h"
#include "heuristic.h"
#include "operators.h"

using namespace std;

/*---------------------------------global variables-----------------------------------*/
vector<vector<int> > answer = { {1, 2, 3},
								{4, 5, 6},
								{7, 8, 0} };	//defined to compare current state with goal state
Heuristic* yes = new manhattan();	//creating a random Heuristic called yes to use in main()...it's set to new manhattan() as a placeholder
int totalexpansion = 0;		//used to track the total number of nodes expanded before reaching the goal
int goaldepth = 0;			//used to track the depth at which the goal node was found
unsigned long largestqueuenum = 0;	//used to track the largest amount of nodes in the queue

/*--------------------------------print function--------------------------------------*/
void print(Node* hi) {
	for (unsigned i = 0; i < 3; i++) {
		for (unsigned j = 0; j < 3; j++) {
			cout << hi->s[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

/*-----------------------------generic search function--------------------------------*/
void generic_search(vector<vector<int> > original) {
	map<vector<vector<int> >,bool> visited;		//used to store all the different states visited
	auto cmp = [](Node* pipi, Node* pupu) {return (pipi->g + pipi->h) > (pupu->g + pupu->h);};	//tells priority queue which order to sort
	priority_queue<Node*, vector<Node*>, decltype(cmp)> statestuff(cmp);	//priority queue
	statestuff.push(new Node(original));	//pushing original state onto queue
	Node* v;								
	vector<Node*> expandedthings;		

	while (statestuff.size() > 0) {	
		if (statestuff.size() > largestqueuenum) {	
			largestqueuenum = statestuff.size();	//setting and updating largest queue size
		}

		v = statestuff.top();	//Node to be expanded
		statestuff.pop();		//Pop node off queue b/c going to expand

		if (v->s == answer) {	//if answer, then hooray!
			goaldepth = v->g;	//update depth where goal was found
			cout << "gottem at depth g(n) = " << v->g << " and h(n) = " << v->h << endl;
			print(v);
			return;
		}

		else if (v->s != answer && visited.find(v->s) == visited.end()) { //if not answer and not in map yet, go here
			visited.insert(pair<vector<vector<int> >, bool>(v->s, true)); //now put the state you're expanding in map
			totalexpansion++;	//counter for how many states already expanded
			cout << "The best state to expand with a g(n) = " << v->g << " and h(n) = " << v->h << " is ... " << endl;
			print(v);
			v->g = v->g + 1;	//updating g(n) to next level
			expandedthings.clear();	//clearing so that won't expand same states that were already expanded last time
			expandedthings.push_back(new Node(v)); //puts it through copy constructor so can reuse for later for other moves
			up(expandedthings[0]);	//move piece up
			if (expandedthings[0]->s != v->s) { //if it's possible to move it
				yes->heur(expandedthings[0]);	//calls whatever heuristic wsa chosen in the beginning to update h(n)
				if (expandedthings[0]->s == answer) { //if its the answer then just put answer in queue
					while (statestuff.size() != 0) {
						statestuff.pop();
					}
				}
				statestuff.push(expandedthings[0]); //push the expanded state onto queue
			}
			expandedthings.push_back(new Node(v)); //same as up() except with down
			down(expandedthings[1]);
			if (expandedthings[1]->s != v->s) {
				yes->heur(expandedthings[1]);
				if (expandedthings[1]->s == answer) {
					while (statestuff.size() != 0) {
						statestuff.pop();
					}
				}
				statestuff.push(expandedthings[1]);
			}
			expandedthings.push_back(new Node(v)); //same as up() except with left
			left(expandedthings[2]);
			if (expandedthings[2]->s != v->s) {
				yes->heur(expandedthings[2]);
				if (expandedthings[2]->s == answer) {
					while (statestuff.size() != 0) {
						statestuff.pop();
					}
				}
				statestuff.push(expandedthings[2]);
			}
			expandedthings.push_back(new Node(v));	//same as up() except with right
			right(expandedthings[3]);
			if (expandedthings[3]->s != v->s) {
				yes->heur(expandedthings[3]);
				if (expandedthings[3]->s == answer) {
					while (statestuff.size() != 0) {
						statestuff.pop();
					}
				}
				statestuff.push(expandedthings[3]);
			}
		}

		else {	//if it's not the answer and already in the map then ignore and continue
			continue;
		}
	}
	return;
}

/*-----------------------------------main stuff-------------------------------------*/
int main() {
	int puzzlechoice;
	int num;
	int algorithm;
	vector<int> top;
	vector<int> middle;
	vector<int> bottom;
	vector<vector<int> > puzzle;

	cout << "Welcome to Kim's 8-puzzle solver!" << endl;
	cout << "Type \"1\" to use a default puzzle or \"2\" to enter your own puzzle: ";
	cin >> puzzlechoice;
	cout << endl;

	if (puzzlechoice == 2) {
		cout << "Enter your puzzle, use a zero to represent the blank" << endl;
		cout << "Enter the first row; hit enter after each number: ";
		for (unsigned i = 0; i < 3; i++) {
			cin >> num;
			top.push_back(num);
		}
		cout << endl;
		cout << "Enter the second row; hit enter after each number: ";
		for (unsigned i = 0; i < 3; i++) {
			cin >> num;
			middle.push_back(num);
		}
		cout << endl;
		cout << "Enter the third row; hit enter after each number: ";
		for (unsigned i = 0; i < 3; i++) {
			cin >> num;
			bottom.push_back(num);
		}
		cout << endl;

		puzzle.push_back(top);
		puzzle.push_back(middle);
		puzzle.push_back(bottom);
	}

	else if (puzzlechoice == 1) {
		puzzle = { {8, 5, 6},
				   {4, 0, 1},
				   {2, 3, 7} };
	}

	cout << "Original puzzle: " << endl;
	for (unsigned i = 0; i < puzzle.size(); i++) {
		for (unsigned j = 0; j < 3; j++) {
			cout << puzzle.at(i).at(j)<< " ";
		}
		cout << endl;
	}
	cout << endl;

	cout << "Enter your choice of algorithm" << endl;
	cout << "1. Uniform Cost" << endl;
	cout << "2. A* with misplaced tile heuristic" << endl;
	cout << "3. A* with Manhattan distance heuristic" << endl;
	cin >> algorithm;
	cout << endl;

	if (algorithm == 1) {
		yes = new uniform_cost();
	}

	if (algorithm == 2) {
		yes = new misplaced();
	}

	if (algorithm == 3) {
		yes = new manhattan();
	}

	if (algorithm < 1 || algorithm > 3) {
		cout << "das not a real option restart this program >:(" << endl;
	}
	generic_search(puzzle);

	cout << "Goal!!\n" << endl;
	cout << "To solve this problem the search algorithm expanded a total of " << totalexpansion << " nodes." << endl;
	cout << "The maximum number of nodes in the queue at any one time was " << largestqueuenum << "." << endl;
	cout << "The depth of the goal node was " << goaldepth << endl;

	return 0;
}