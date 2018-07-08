// this is wrong code!
#include "stdafx.h"
#include<vector>
#include<iostream>
using namespace std;
int overHalf(const vector<int>&a) {
	int v, count;
	v = a[0]; count = 0;
	for (auto i : a) {
		if (count == -1)v = i, count = 0;
		else if (i == v) ++count;
		else --count;
	}
	if (count > 0) return v;
	else return -1;
}
int main() {
	cout << overHalf(vector<int>{1, 2, 1, 2, 3}) << endl;
	cout << overHalf(vector<int>{3, 3, 4, 1, 4}) << endl;
	cout << overHalf(vector<int>{3,3,3,4,1,4,3}) << endl;
	return 0;
}
