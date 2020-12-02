#include <algorithm>
#include <cassert>
#include <iostream>
#include <numeric>
#include <string>
#include <string_view>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

template <typename T>
auto len(const T& c) -> int {
	return static_cast<int>(c.size()); }

void Split(const std::string& str, char delim, std::vector<std::string>& out);

int main() {

	int part1{0};
	int part2{0};
	string l;
	vector<string> segs;
	vector<string> s2;
	while (getline(cin, l)) {
		Split(l, ' ', segs);
		Split(segs[0], '-', s2);
		// cerr << s2[0] << ":" << s2[1] << ":" << segs[1][0] << ":" << segs[2] << endl;
		int rl = stoi(s2[0]);
		int rh = stoi(s2[1]);
		char ch = segs[1][0];
		auto& word = segs[2];

		int many = accumulate(begin(word), end(word),
							  0, [&](auto ax, auto item) { return ax + (item==ch); });
		part1 += (rl <= many && many <= rh);

		part2 += (word[rl-1]!=word[rh-1]) && (word[rl-1]==ch || word[rh-1]==ch); }

	cout << part1 << endl;
	cout << part2 << endl;
	return 0; }


void Split(const std::string& str, char delim, std::vector<std::string>& out) {
	std::vector<std::string> items;
	std::string src(str);
	auto nextmatch = src.find(delim);
	std::size_t cnt{0};
	while (true) {
		auto item = src.substr(0, nextmatch);
		if (cnt < out.size()) {
			out[cnt].assign(src.substr(0, nextmatch)); }
		else {
			out.emplace_back().assign(src.substr(0, nextmatch)); }
		++cnt;
		if (nextmatch == std::string::npos) { break; }
		src = src.substr(nextmatch + 1);
		nextmatch = src.find(delim); }
	out.resize(cnt); }
