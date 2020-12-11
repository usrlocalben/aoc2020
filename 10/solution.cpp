#include "../lib.hpp"
using namespace std;
int main() {
	string l;
	vs lines;
	vi nums;
	while (getline(cin, l)) {
		nums.push_back(stoi(l)); }
	sort(ALL(nums));

	int j=0;
	array <int, 5> ds{};
	for (const auto& num : nums) {
		int d = num - j;
		ds[d]++;
		j=num; }
	int part1 = ds[1]*(ds[3]+1);
	cout << part1 << nl;

	array<int64_t, 4> tab{{ 1, 0, 0, 0 }};
	int a = nums.back();
	nums.insert(begin(nums), 0);
	for (int i=len(nums)-2; i>=0; --i) {
		int b = nums[i];
		if (a-b == 1) {
			swap(tab[2],tab[3]);
			swap(tab[1],tab[2]);
			swap(tab[0],tab[1]); }
		else {
			tab[3] = tab[0];
			tab[1] = tab[2] = 0; }
		tab[0] = tab[1]+tab[2]+tab[3];
		a = b; }

	cout << tab[0] << nl;
	return 0; }
