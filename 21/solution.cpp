#include "../lib.hpp"
using namespace std;

vector<string> alergs{};
umap<string, vector<int>> bads{};
vector<uss> foods{};
vector<pair<string, string>> resolved{};


uss inuse{};
bool BT(int bi=0) {
	if (bi == len(alergs)) return true;
	const auto& alerg = alergs[bi];

	auto& fids = bads[alerg];

	auto xa = foods[fids.front()];
	for (int i=1; i<len(fids); ++i) {
		xa = Intersect(xa, foods[fids[i]]); }

	for (auto& w : xa) {
		if (inuse.find(w) != end(inuse)) continue;
		inuse.insert(w);

		if (BT(bi+1)) {
			resolved.eb(alerg, w);
			return true; }

		inuse.erase(w); }
	return false; }


int main() {
	string li;
	vs lines;
	while (getline(cin, li)) {
		auto chunks = Split(li, " (contains ");
		auto& contains = chunks[1];
		contains = contains.substr(0, len(contains)-1);
		auto bad = Split(contains, ", ");
		auto words = Split(chunks[0], " ");

		int fi = len(foods);
		foods.emplace_back();
		auto& ingr = foods.back();
		for (auto w : words) {
			ingr.insert(w); }

		for (auto w : bad) {
			bads[w].push_back(fi); }}

	for (auto& [name, _] : bads) {
		alergs.push_back(name); }

	uss maybes;
	for (auto& [w, fids] : bads) {
		auto xa = foods[fids[0]];
		for (int i=1; i<len(fids); ++i) {
			xa = Intersect(xa, foods[fids[i]]); }
		for (auto& w:xa) {
			maybes.insert(w); }}

	int part1=0;
	for (auto& food :foods) {
		auto tmp = food;
		for (auto& w : food) {
			if (maybes.find(w) == end(maybes)) {
				part1++;
				tmp.erase(w); }}
		food.swap(tmp); }

	cout << part1 << nl;
	BT();

	sort(ALL(resolved));
	bool first = true;
	for (auto [_, w] : resolved) {
		if (first) {
			first = false; }
		else {
			cout << ","; }
		cout << w; }
	cout << nl;

	return 0; }
