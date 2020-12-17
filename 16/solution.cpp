#include "../lib.hpp"
using namespace std;

using Ticket = array<short, 20>;
vector<pair<pii, pii>> ranges;
vector<Ticket> tickets{};
array<int, 20> fit{};

uset<int> memo{};
array<int, 20> fieldCol{};
bool BT(int f, int inuse) {
	if (f==20) return true;
	int key = inuse<<5|f;
	if (memo.find(key) == memo.end()) {
		for (int c=0; c<20; ++c) {
			if (!(inuse&(1<<c))) {
				bool good = fit[c]&(1<<f);
				if (good && BT(f+1, inuse|(1<<c))) {
					fieldCol[f] = c;
					return true; }}}
		memo.insert(key); }
	return false; }

int main() {
	string l;
	vs kvseg, words, lohi;
	int section{0};
	vs names;

	int part1{0};

	Ticket self;

	while (getline(cin, l)) {
		if (l.empty()) {
			section++;
			continue; }
		if (section == 0) {
			// ranges
			Split(l, ':', kvseg);
			names.push_back(kvseg[0]);
			Split(kvseg[1], ' ', words);
			// " n-n or n-n";
			Split(words[1], '-', lohi);
			int r1a = stoi(lohi[0]);
			int r1b = stoi(lohi[1]);
			Split(words[3], '-', lohi);
			int r2a = stoi(lohi[0]);
			int r2b = stoi(lohi[1]);
			ranges.push_back({ {r1a, r1b}, {r2a,r2b} }); }
		else if (section == 1) {
			if (l[0] == 'y') continue;
			Split(l, ',', words);
			for (int i=0; i<20; ++i) {
				self[i] = stoi(words[i]); }}
		else if (section == 2) {
			if (l[0] == 'n') continue;
			Split(l, ',', words);
			Ticket t;
			bool valid = true;
			for (int i=0; i<20; ++i) {
				int n = stoi(words[i]);
				bool bad = true;
				for (const auto& [r1, r2] : ranges) {
					if ((r1.fi<=n && n<=r1.se) || (r2.fi<=n && n<=r2.se)) {
						bad = false;
						break; }}
				part1 += n * bad;
				valid = valid && (!bad);
				t[i] = n; }
			if (valid) {
				tickets.push_back(t); }}}

	cout << part1 << nl;

	for (int ri=0; ri<len(ranges); ++ri) {
		int bit = 1<<ri;
		auto Fit = [&](int n) {
			auto& [r1, r2] = ranges[ri];
			return (r1.fi<=n && n <=r1.se)||(r2.fi<=n && n <= r2.se); };
		for (int c=0; c<20; ++c) {
			bool v=true;
			for (const auto& t : tickets) {
				if (!Fit(t[c])) {
					v=false;
					break; }}
			if (v) {
				fit[c]|=bit; }}};

	BT(0,0);
	int64_t part2=1;
	for (int i=0; i<len(names); ++i) {
		if (names[i].find("departure") != string::npos) {
				part2 *= self[fieldCol[i]]; }}
	cout << part2 << nl;
	return 0; }
