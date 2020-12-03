#include "../lib.hpp"
using namespace std;

int main() {

	vi nums;
	nums.reserve(1000);
	string l;
	while (getline(cin, l)) {
		nums.push_back(stoi(l)); }

	sort(ALL(nums));

	int a, b, c;

	a = b = -1;
	for (int i=0; i<len(nums)-1; ++i) {
		a = nums[i];
		int diff = 2020 - a;
		if (binary_search(B(nums)+i+1, E(nums), diff)) {
			b = diff;
			break; }}
	assert(b != -1);
	cout << (a*b) << nl;


	a = b = c = -1;
	for (int i=0; i<len(nums)-1; ++i) {
		a = nums[i];
		for (int j=i+1; j<len(nums)-1; ++j) {
			b = nums[j];
			int diff = 2020 - a - b;
			if (diff>=0 && binary_search(B(nums)+j+1, E(nums), diff)) {
				c = diff;
				goto found; }}}
found:
	cout << (a*b*c) << nl;

	return 0; }
