#include "../lib.hpp"
// p1 #162
using namespace std;
int main() {
	string tmp;
	vs lines;
	while (getline(cin, tmp)) {
		lines.push_back(tmp); }

	int64_t part1 = 0;
	for (const auto& l : lines) {
		deque<pair<char,int64_t>> s;
		int64_t ax{0};
		char op = '+';
		for (int i=0; i<len(l); ++i) {
			char c = l[i];
			if (c==' ') continue;
			if (c == '(') {
				s.push_back({op,ax});
				ax=0;
				op = '+'; }
			else if (c==')') {
				op = s.back().fi;
				if (op=='*') {
					ax *= s.back().se; }
				else {
					ax += s.back().se; }
				s.pop_back(); }
			else if (c=='+' || c=='*') {
				op = c; }
			else if ('0'<=c && c<='9') {
				int x = c-'0';
				if (op == '*') {
					ax = ax * x; }
				else {
					ax = ax + x; }}}
		part1 += ax; }
	cout << part1 << nl;

	int64_t part2 = 0;
	auto Level = [](char ch) {
		if (ch == '+') return 1;
		return 0; };
	for (const auto& l : lines) {
		deque<char> s;
		string p;
		for (const auto c : l) {
			if (c==' ') continue;
			else if ('0'<=c && c<='9') {
				p += c; }
			else if (c=='+' || c=='*') {
				while (!s.empty() && Level(c)<Level(s.back()) && s.back()!='(') {
					p += s.back(); s.pop_back(); }
				s.push_back(c); }
			else if (c=='(') {
				s.push_back(c); }
			else if (c==')') {
				while (s.back() != '(') {
					p += s.back(); s.pop_back(); }
				s.pop_back(); }}
		while (!s.empty()) {
			p += s.back(); s.pop_back(); }

		deque<int64_t> nums;
		for (auto ch : p) {
			if ('0'<=ch&&ch<='9') {
				nums.push_front(ch-'0'); }
			else if (ch=='+') {
				int64_t a = nums.front(); nums.pop_front();
				nums.front() += a; }
			else if (ch=='*') {
				int64_t a = nums.front(); nums.pop_front();
				nums.front() *= a; }}
		part2 += nums.front(); }
	cout << part2 << nl;



	return 0; }
