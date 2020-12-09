#include "../lib.hpp"
using namespace std;
int main() {
	string l;
	vector<int64_t> nums;
	while (getline(cin, l)) {
		nums.push_back(stol(l)); }

	int64_t part1=-1;
	deque<int64_t> buf;
	int n;
	for (n=0; n<25; ++n) {
		buf.push_back(nums[n]); }
	for (; n<len(nums); ++n) {
		auto num = nums[n];

		bool found = false;
		for (int j=0; j<len(buf)-1; ++j) {
			for (int k=j+1; k<len(buf); ++k) {
				if (buf[j]+buf[k] == num) {
					found = true;
					break; }}
			if (found) break; }
		if (!found) {
			part1 = num;
			break; }

		buf.pop_front();
		buf.push_back(num); }
	cout << part1 <<nl;

	int64_t part2 = -1;
	int64_t rmin, rmax, ax;
	for (int j=0; j<len(nums)-1; ++j) {
		rmin = rmax = ax = nums[j];
		for (int k=j+1; k<len(nums); ++k) {
			ax += nums[k];
			rmin = min(rmin,nums[k]);
			rmax = max(rmax,nums[k]);
			if (ax == part1) {
				part2 = rmin+rmax;
				break; }}}
	cout << part2 << nl;

	return 0; }
