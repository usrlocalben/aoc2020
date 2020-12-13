#include "../lib.hpp"
using namespace std;
int main() {
	string l;
	getline(cin,l);
	int T = stoi(l);
	getline(cin,l);
	vs words;
	Split(l, ',', words);
	vii nums;
	nums.reserve(len(words));
	int i=0; 
	for (auto& word: words) {
		if (word[0] != 'x') {
			nums.push_back({ i, stoi(word) }); }
		i++; }

	int bestTime = oo;
	int bestBus = -1;
	for (auto [seq, id] : nums) {
		int rem = id-(T%id);
		if (rem < bestTime) {
			bestTime = rem;
			bestBus = id; }}
	cout << (bestTime*bestBus) << nl;


	int64_t t=0, m1=nums[0].se;
	for (int i=1; i<len(nums); ++i) {
		auto [d2,m2] = nums[i];
		while ((t+d2)%m2) t+= m1;
		int64_t tc = t+m1;
		while ((tc+d2)%m2) tc+=m1;
		m1 = tc-t; }
	cout << t << nl;

	return 0; }
