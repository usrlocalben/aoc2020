#include "../lib.hpp"
using namespace std;

umap<string, vector<psi>> rules;
umap<string, uset<string>> invrules;

uset<string> visited;
void Part1(const string& id) {
	visited.insert(id);
	if (auto match = invrules.find(id); match!=end(invrules)) {
		auto edges = match->second;
		for (const auto& nextId : edges) {
			// cout << id << " -> " << nextId << nl;
			Part1(nextId); }}}


auto Part2(const string& id) -> int {
	int cnt = 1;
	if (auto match = rules.find(id); match!=end(rules)) {
		auto edges = match->second;
		if (edges.size() == 0) {
			/*cerr << id << " contain no other\n";*/ }
		else {
			for (const auto& edge : edges) {
				auto& depId = edge.first;
				auto& qty = edge.second;
				// cerr << id << " contain " << qty << " " << depId << " bags\n";
				cnt += qty * Part2(depId); }}}
	return cnt; }


int main() {
	string l;
	vs words{};
	vector<psi> tmp{};
	while (getline(cin, l)) {
		Split(l, ' ', words);
		auto bagId = words[0] + " " + words[1];
		tmp.clear();
		for (int i=3; i<words.size(); ++i) {
			auto& word = words[i];
			auto& wm1 = words[i-1];
			auto& wm2 = words[i-2];
			auto& wm3 = words[i-3];
			if (word.find("bag") != string::npos) {
				if (wm2=="no" && wm1=="other") {
					// cerr << bagId << " TERMINATES\n";
					continue; }
				auto qty = stoi(wm3);
				auto innerId = wm2 + " " + wm1;
				tmp.push_back({ innerId, qty });

				// cerr << bagId << " -> " << innerId << " (" << qty << ")\n";

				invrules[innerId].insert(bagId); }}
		rules[bagId] = tmp; }

	Part1("shiny gold");
	auto part1 = visited.size() - 1;
	cout << part1 << nl;

	auto part2 = Part2("shiny gold") - 1;
	cout << part2 << nl;

	return 0; }
