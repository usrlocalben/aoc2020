#include <algorithm>
#include <cassert>
#include <iostream>
#include <string>
#include <string_view>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

template <typename T>
auto len(const T& c) -> int {
	return static_cast<int>(c.size()); }

int main() {

	vector<int> nums;
	nums.reserve(1000);
	std::string l;
	while (getline(cin, l)) {
		nums.push_back(stoi(l)); }

	sort(begin(nums), end(nums));

	int a, b, c;

	a = b = -1;
	for (int i=0; i<len(nums)-1; ++i) {
		a = nums[i];
		int diff = 2020 - a;
		if (binary_search(begin(nums)+i+1, end(nums), diff)) {
			b = diff;
			break; }}
	assert(b != -1);
	std::cout << (a*b) << endl;


	a = b = c = -1;
	for (int i=0; i<len(nums)-1; ++i) {
		a = nums[i];
		for (int j=i+1; j<len(nums)-1; ++j) {
			b = nums[j];
			int diff = 2020 - a - b;
			if (diff>=0 && binary_search(begin(nums)+j+1, end(nums), diff)) {
				c = diff;
				goto found; }}}
found:
	std::cout << (a*b*c) << endl;

	return 0; }
