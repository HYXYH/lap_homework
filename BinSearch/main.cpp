#include <iostream>
#include <vector>
#include "bin_search.h"

using namespace std;


int main() {
	int toFind;
	vector<int> data = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	cout << "input number to find:" << std::endl;
	cin >> toFind;

	bool isFound = bin_search(data, toFind);
	if(isFound){
		cout << "Yep, " << toFind << " is found";
	}
	else {
		cout << "Сорян, " << toFind << " is not found";
	}

	return 0;
}