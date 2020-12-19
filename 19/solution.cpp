#include "../lib.hpp"
using namespace std;

constexpr int R_OR = 1<<9;
constexpr int R_CHAR = 1<<8;
constexpr int R_RULE = 1<<10;
constexpr int R_DATA = 0xff;

umap<short, vector<int>> rules;

int R(string_view s, int rid, int j, int d=0) {
	auto& r = rules[rid];
	if (d>200) return -1;
	// cerr << rid << "," << j << nl;
	if (j>=s.size()) return -1;
	if (r[0]&R_CHAR) {
		char c = r[0]&R_DATA;
		return s[j]==c ? j+1 : -1; }
	else {
		int initJ{j};
		bool match=true;
		for (int i=0; i<r.size(); ++i) {
			if (r[i]&R_RULE) {
				int result = R(s, r[i]&R_DATA, j, d+1);
				if (result < 0) {
					match = false; }
				else {
					j = result; }}
			else if (r[i]&R_OR) {
				if (match) return j;
				match = true;
				j=initJ; }}
		return match ? j : -1; }}

int main() {
	string li;
	vs lines;
	char state = 'R';
	while (getline(cin,li)) {
		if (li.empty()) { state = 'M'; continue; }
		if (state=='R') {
			auto segs = Split(li, ": ");
			int rn = stoi(segs[0]);
			auto words = Split(segs[1], " ");
			vector<int> tmp;
			for (auto w : words) {
				if (w[0] == '|') {
					tmp.push_back(R_OR); }
				else if (w[0] == '"') {
					tmp.push_back(w[1]|R_CHAR); }
				else {
					tmp.push_back(stoi(w)|R_RULE); }}
			rules[rn] = move(tmp);}
		else {
			lines.push_back(li); }}

	int part1{0};
	vs rem;
	for (auto l : lines) {
		int result = R(l, 0, 0);
		if (result == len(l)) {
			part1++; }
		else {
			rem.push_back(l); }}
	cout << part1 << nl;

	lines = rem;
	rem.clear();
	int part2{0};
	for (int ra=1; ra<20; ++ra) {
	for (int rb=1; rb<20; ++rb) {

		auto& v8 = rules[8]; v8.clear();
		for (int n=0; n<ra; ++n) { v8.push_back(42|R_RULE); }

		auto& v11 = rules[11]; v11.clear();
		for (int n=0; n<rb; ++n) { v11.push_back(42|R_RULE); }
		for (int n=0; n<rb; ++n) { v11.push_back(31|R_RULE); }

		for (auto l : lines) {
			int result = R(l, 0, 0);
			if (result == len(l)) {
				part2++; }
			else {
				rem.push_back(l); }}
		// cerr << ".";
		lines=rem;
		rem.clear(); }}
	cout << part1+part2 << nl;
	return 0;}
