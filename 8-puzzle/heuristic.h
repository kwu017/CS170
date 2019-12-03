#include <iostream>

using namespace std;

vector<vector<int> > answer2 = { {1, 2, 3},
								{4, 5, 6},
								{7, 8, 0} };

class Heuristic {
	public:
		Heuristic() {}
		virtual void heur(Node* ok) = 0;
};

class uniform_cost : public Heuristic {
	public:
		uniform_cost() {}
		void heur(Node* ok) {
			ok->h = 0;
		}
};

class misplaced : public Heuristic {
	public:
		misplaced() {}
		void heur(Node* ok) {
			int score = 0;
			for (unsigned i = 0; i < 3; i++) {
				for (unsigned j = 0; j < 3; j++) {
					if (ok->s[i][j] != answer2[i][j]) {
						score++;
					}
				}
			}
			ok->h = score;
		}
};

class manhattan : public Heuristic {
	public:
		manhattan() {}
		void heur(Node* ok) {
			int score = 0;
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 3; j++) {
					if (ok->s[i][j] == 1 && (i != 0 || j != 0)) {
						score = score + i + j;
					}
					else if (ok->s[i][j] == 2 && (i != 0 || j != 1)) {
						score = score + i + abs(j - 1); 
					}
					else if (ok->s[i][j] == 3 && (i != 0 || j != 2)) {
						score = score + i + abs(j - 2);
					}
					else if (ok->s[i][j] == 4 && (i != 1 || j != 0)) {
						score = score + abs(i - 1) + j;
					}
					else if (ok->s[i][j] == 5 && (i != 1 || j != 1)) {
						score = score + abs(i - 1) + abs(j - 1);
					}
					else if (ok->s[i][j] == 6 && (i != 1 || j != 2)) {
						score = score + abs(i - 1) + abs(j - 2);
					}
					else if (ok->s[i][j] == 7 && (i != 2 || j != 0)) {
						score = score + abs(i - 2) + j;
					}
					else if (ok->s[i][j] == 8 && (i != 2 || j != 1)) {
						score = score + abs(i - 2) + abs(j - 1);
					}
				}
			}
			ok->h = score;
		}
};

