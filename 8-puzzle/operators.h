#include <iostream>
#include <vector>

using namespace std;

Node* up(Node* no) { //moving it up
	if (no->s[0][0] == 0 || no->s[0][1] == 0 || no->s[0][2] == 0) {
		return no;
	}

	else {
		if (no->s[1][0] == 0) {
			no->s[1][0] = no->s[0][0];
			no->s[0][0] = 0;
			return no;
		}

		else if (no->s[1][1] == 0) {
			no->s[1][1] = no->s[0][1];
			no->s[0][1] = 0;
			return no;
		}

		else if (no->s[1][2] == 0) {
			no->s[1][2] = no->s[0][2];
			no->s[0][2] = 0;
			return no;
		}

		else if (no->s[2][0] == 0) {
			no->s[2][0] = no->s[1][0];
			no->s[1][0] = 0;
			return no;
		}

		else if (no->s[2][1] == 0) {
			no->s[2][1] = no->s[1][1];
			no->s[1][1] = 0;
			return no;
		}

		else if (no->s[2][2] == 0) {
			no->s[2][2] = no->s[1][2];
			no->s[1][2] = 0;
			return no;
		}
	}

	return no;
}

Node* down(Node* no) { //moving it down
	if (no->s[2][0] == 0 || no->s[2][1] == 0 || no->s[2][2] == 0) {
		return no;
	}

	else {
		if (no->s[0][0] == 0) {
			no->s[0][0] = no->s[1][0];
			no->s[1][0] = 0;
			return no;
		}

		else if (no->s[0][1] == 0) {
			no->s[0][1] = no->s[1][1];
			no->s[1][1] = 0;
			return no;
		}

		else if (no->s[0][2] == 0) {
			no->s[0][2] = no->s[1][2];
			no->s[1][2] = 0;
			return no;
		}

		else if (no->s[1][0] == 0) {
			no->s[1][0] = no->s[2][0];
			no->s[2][0] = 0;
			return no;
		}

		else if (no->s[1][1] == 0) {
			no->s[1][1] = no->s[2][1];
			no->s[2][1] = 0;
			return no;
		}

		else if (no->s[1][2] == 0) {
			no->s[1][2] = no->s[2][2];
			no->s[2][2] = 0;
			return no;
		}
	}

	return no;
}

Node* left(Node* no) { //moving it left
	if (no->s[0][0] == 0 || no->s[1][0] == 0 || no->s[2][0] == 0) {
		return no;
	}

	else {
		if (no->s[0][1] == 0) {
			no->s[0][1] = no->s[0][0];
			no->s[0][0] = 0;
			return no;
		}

		else if (no->s[1][1] == 0) {
			no->s[1][1] = no->s[1][0];
			no->s[1][0] = 0;
			return no;
		}

		else if (no->s[2][1] == 0) {
			no->s[2][1] = no->s[2][0];
			no->s[2][0] = 0;
			return no;
		}

		else if (no->s[0][2] == 0) {
			no->s[0][2] = no->s[0][1];
			no->s[0][1] = 0;
			return no;
		}

		else if (no->s[1][2] == 0) {
			no->s[1][2] = no->s[1][1];
			no->s[1][1] = 0;
			return no;
		}

		else if (no->s[2][2] == 0) {
			no->s[2][2] = no->s[2][1];
			no->s[2][1] = 0;
			return no;
		}
	}

	return no;
}

Node* right(Node* no) {	//moving it right
	if (no->s[0][2] == 0 || no->s[1][2] == 0 || no->s[2][2] == 0) {
		return no;
	}

	else {
		if (no->s[0][0] == 0) {
			no->s[0][0] = no->s[0][1];
			no->s[0][1] = 0;
			return no;
		}

		else if (no->s[1][0] == 0) {
			no->s[1][0] = no->s[1][1];
			no->s[1][1] = 0;
			return no;
		}

		else if (no->s[2][0] == 0) {
			no->s[2][0] = no->s[2][1];
			no->s[2][1] = 0;
			return no;
		}

		else if (no->s[0][1] == 0) {
			no->s[0][1] = no->s[0][2];
			no->s[0][2] = 0;
			return no;
		}

		else if (no->s[1][1] == 0) {
			no->s[1][1] = no->s[1][2];
			no->s[1][2] = 0;
			return no;
		}

		else if (no->s[2][1] == 0) {
			no->s[2][1] = no->s[2][2];
			no->s[2][2] = 0;
			return no;
		}
	}

	return no;
}