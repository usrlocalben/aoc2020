#include "../lib.hpp"
using namespace std;

int main() {
	string l;
	vi ids;
	ids.reserve(1000);
	int range[2];
	while (getline(cin, l)) {

		range[0] = 0, range[1] = 128;
		for (int i=0; i<7; ++i) {
			int mid = (range[0]+range[1])/2;
			range[l[i]=='F'] = mid; }
		int row = range[0];

		range[0] = 0, range[1] = 8;
		for (int i=7; i<10; ++i) {
			int mid = (range[0]+range[1])/2;
			range[l[i]=='L'] = mid; }
		int col = range[0];

		int id = row*8 + col;
		ids.push_back(id); }

	sort(ALL(ids));

	int i;
	for (i=0; i<ids.size()-1; ++i) {
		if (ids[i]+1 != ids[i+1]) {
			break; }}

	cout << ids.back() << nl;
	cout << ids[i]+1 << nl;
	return 0; }
