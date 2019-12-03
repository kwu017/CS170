#include <iostream>
#include <vector>

using namespace std;

vector<vector<int> > up(vector<vector<int> >& no) {
	if (no[0][0] == 0 || no[0][1] == 0 || no[0][2] == 0) {
		return no;
	}

	else {
		if (no[1][0] == 0) {
			no[1][0] = no[0][0];
			no[0][0] = 0;
			return no;
		}

		else if (no[1][1] == 0) {
			no[1][1] = no[0][1];
			no[0][1] = 0;
			return no;
		}

		else if (no[1][2] == 0) {
			no[1][2] = no[0][2];
			no[0][2] = 0;
			return no;
		}

		else if (no[2][0] == 0) {
			no[2][0] = no[1][0];
			no[1][0] = 0;
			return no;
		}

		else if (no[2][1] == 0) {
			no[2][1] = no[1][1];
			no[1][1] = 0;
			return no;
		}

		else if (no[2][2] == 0) {
			no[2][2] = no[1][2];
			no[1][2] = 0;
			return no;
		}
	}

	return no;
}

vector<vector<int> > down(vector<vector<int> >& no) {
	if (no[2][0] == 0 || no[2][1] == 0 || no[2][2] == 0) {
		return no;
	}

	else {
		if (no[0][0] == 0) {
			no[0][0] = no[1][0];
			no[1][0] = 0;
			return no;
		}

		else if (no[0][1] == 0) {
			no[0][1] = no[1][1];
			no[1][1] = 0;
			return no;
		}

		else if (no[0][2] == 0) {
			no[0][2] = no[1][2];
			no[1][2] = 0;
			return no;
		}

		else if (no[1][0] == 0) {
			no[1][0] = no[2][0];
			no[2][0] = 0;
			return no;
		}

		else if (no[1][1] == 0) {
			no[1][1] = no[2][1];
			no[2][1] = 0;
			return no;
		}

		else if (no[1][2] == 0) {
			no[1][2] = no[2][2];
			no[2][2] = 0;
			return no;
		}
	}

	return no;
}

vector<vector<int> > left(vector<vector<int> >& no) {
	if (no[0][0] == 0 || no[1][0] == 0 || no[2][0] == 0) {
		return no;
	}

	else {
		if (no[0][1] == 0) {
			no[0][1] = no[0][0];
			no[0][0] = 0;
			return no;
		}

		else if (no[1][1] == 0) {
			no[1][1] = no[1][0];
			no[1][0] = 0;
			return no;
		}

		else if (no[2][1] == 0) {
			no[2][1] = no[2][0];
			no[2][0] = 0;
			return no;
		}

		else if (no[0][2] == 0) {
			no[0][2] = no[0][1];
			no[0][1] = 0;
			return no;
		}

		else if (no[1][2] == 0) {
			no[1][2] = no[1][1];
			no[1][1] = 0;
			return no;
		}

		else if (no[2][2] == 0) {
			no[2][2] = no[2][1];
			no[2][1] = 0;
			return no;
		}
	}

	return no;
}

vector<vector<int> > right(vector<vector<int> >& no) {
	if (no[0][2] == 0 || no[1][2] == 0 || no[2][2] == 0) {
		return no;
	}

	else {
		if (no[0][0] == 0) {
			no[0][0] = no[0][1];
			no[0][1] = 0;
			return no;
		}

		else if (no[1][0] == 0) {
			no[1][0] = no[1][1];
			no[1][1] = 0;
			return no;
		}

		else if (no[2][0] == 0) {
			no[2][0] = no[2][1];
			no[2][1] = 0;
			return no;
		}

		else if (no[0][1] == 0) {
			no[0][1] = no[0][2];
			no[0][2] = 0;
			return no;
		}

		else if (no[1][1] == 0) {
			no[1][1] = no[1][2];
			no[1][2] = 0;
			return no;
		}

		else if (no[2][1] == 0) {
			no[2][1] = no[2][2];
			no[2][2] = 0;
			return no;
		}
	}

	return no;
}