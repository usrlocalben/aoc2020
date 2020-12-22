#include "../lib.hpp"
using namespace std;
array<deque<char>,2> decks;

void Round1() {
	int a = take_front(decks[0]);
	int b = take_front(decks[1]);
	int t = a > b ? 0 : 1;
	if (a<b) swap(a,b);
	decks[t].push_back(a);
	decks[t].push_back(b); }


auto Round2(array<string,2> d, int rd=0) -> pii {
	static string key;
	uset<string> visited{};

	while (1) {
		key.assign(d[0]); key += "."; key += d[1];
		if (visited.find(key) != end(visited)) {
			return {0,0}; }
		visited.insert(key);

		int c0 = d[0][0]; d[0] = d[0].substr(1);
		int c1 = d[1][0]; d[1] = d[1].substr(1);
		int w;
		if (len(d[0])>=c0 && len(d[1])>=c1) {
			int _;
			tie(w,_) = Round2({ d[0].substr(0,c0), d[1].substr(0,c1) }, rd+1); }
		else {
			w = c1 > c0; }
		if (w == 1) swap(c0,c1);
		d[w] += char(c0);
		d[w] += char(c1);

		if (len(d[0])==0 || len(d[1])==0) {
			w = len(d[0])==0;
			int f=1, ax=0;
			for (int i=len(d[w])-1; i>=0; --i, ++f) {
				ax += d[w][i]*f; }
			return { w, ax }; }}}


int main() {
	string li;
	vs lines;
	int p=0;
	array<string, 2> d2;
	while (getline(cin, li)) {
		if (li.empty()) {
			p++; }
		else if (li.find("Player")==0) {
		}
		else {
			d2[p] += char(stoi(li));
			decks[p].push_back(stoi(li)); }}

	while ((!decks[0].empty()) && (!decks[1].empty())) {
		Round1(); }

	int64_t p1=0;
	int f=1;

	auto& winner = decks[0].empty() ? decks[1] : decks[0];
	for (int i=len(winner)-1; i>=0; --i, f++) p1 += winner[i]*f;
	cout << p1 << nl;

	auto [w, part2] = Round2(d2);
	cout << part2 << nl;

	return 0; }
