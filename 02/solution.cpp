#include "../lib.hpp"
using namespace std;

int main() {

	int part1{0};
	int part2{0};
	string l;
	vs segs;
	vs s2;
	while (getline(cin, l)) {
		Split(l, ' ', segs);
		Split(segs[0], '-', s2);
		// cerr << s2[0] << ":" << s2[1] << ":" << segs[1][0] << ":" << segs[2] << endl;
		int rl = stoi(s2[0]);
		int rh = stoi(s2[1]);
		char ch = segs[1][0];
		auto& word = segs[2];

		int many = accumulate(ALL(word), 0, [&](auto ax, auto item) {
		                      return ax + (item==ch); });
		part1 += (rl <= many && many <= rh);

		part2 += (word[rl-1]!=word[rh-1]) && (word[rl-1]==ch || word[rh-1]==ch); }

	cout << part1 << nl;
	cout << part2 << nl;
	return 0; }
