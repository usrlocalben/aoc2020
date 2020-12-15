#include "../lib.hpp"
using namespace std;
int main() {
	vi nums;
	string l;
	vs words;
	getline(cin, l);
	Split(l, ',', words);
	for (const auto& w : words) nums.push_back(stoi(w));
	// nums = {{ 0, 3, 6 }};

	umap<int, pii> tab{};
	int si=0;
	int t=0;
	int last = -1;
	int part1 = -1;
	while (t < 30000000) {
		/*if (t%1000==0) {
			cerr << "   " << t << "   \r"; }*/
		int speak = -1;
		if (si < len(nums)) {
			speak = nums[si++]; }
		else {
			auto [lt1, lt2] = tab[last];
			speak = lt2-lt1; }
		if (auto item = tab.find(speak); item==end(tab)) {
			tab[speak] = { t, t }; }
		else {
			auto& data = item->second;
			data.fi = data.se;
			data.se = t; }

		//cerr << t << ", " << speak << nl;
		last = speak;
		t++;

		if (part1==-1 && t==2020) {
			part1 = last; }}
	// cout << nl;
	cout << part1 << nl;
	cout << last << nl;
	return 0; }
