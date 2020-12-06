#include "../lib.hpp"
using namespace std;

int main() {
	string l;
	int p1{0};
	int p2{0};
	int set1{0};
	int set2{0};
	while (getline(cin, l)) {
		if (l.empty()) {
			p1 += __builtin_popcount(set1);
			p2 += __builtin_popcount(set2);
			set1 = 0;
			set2 = 0x3ff'ffff; }
		else {
			int bits = 0;
			for (const auto ch : l) {
				bits |= 1<<(ch - 'a'); }
			set1 |= bits;
			set2 &= bits; }}
	p1 += __builtin_popcount(set1);
	p2 += __builtin_popcount(set2);
	cout << p1 << nl;
	cout << p2 << nl;
	return 0; }
