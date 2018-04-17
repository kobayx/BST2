#include "BST.h"
#include <iostream>

using namespace std;

int main() {
	BST<string, int> count;
	string word;
	while (cin >> word) { ++count[word]; }
	for (auto& item : count) {
		cout << item.second << "  " << item.first << endl;
	}
	return 0;
}