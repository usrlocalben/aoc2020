#include "../lib.hpp"
using namespace std;

int main() {
	string fields{"cid pid ecl hcl hgt eyr iyr byr"};

	using valfun = bool(*)(const string&);
	array<valfun, 8> validators = {{
		// cid always avlid
		[](const string& s) -> bool { return true; },

		// pid
		[](const string& s) -> bool {
			return (s.size() == 9 &&
			        9 == accumulate(ALL(s), 0,
			                        [](auto ax, auto ch) { return ax + ('0'<=ch&&ch<='9'); })); },

		// ecl
		[](const string& s) -> bool {
			return string{"amb blu brn gry grn hzl oth"}.find(s) != string::npos; },

		// hcl
		[](const string& s) -> bool {
			return s.size()==7 &&
			       s[0]=='#' &&
			       accumulate(begin(s)+1, end(s), true,
			                  [](auto ax, auto ch) { return ax && IsHex(ch); }); },

		// hgt
		[](const string& s) -> bool {
			if (s.size() < 4) return false;
			auto m1 = s[s.size()-1];
			auto m2 = s[s.size()-2];
			auto m3 = s[s.size()-3];
			if (!('0'<=m3 && m3<='9')) return false;
			if (m2=='c' && m1=='m') {
				auto dim = stoi(s);
				return 150<=dim && dim<=193; }
			else if (m2=='i' && m1=='n') {
				auto dim = stoi(s);
				return 59 <= dim && dim <= 76; }
			return false; },

		// eyr
		[](const string& s) -> bool {
			auto v = stoi(s);
			return 2020 <= v && v <= 2030; },

		// iyr
		[](const string& s) -> bool {
			auto v = stoi(s);
			return 2010 <= v && v <= 2020; },

		// byr
		[](const string& s) -> bool {
			auto v = stoi(s);
			return 1920 <= v && v <= 2002; },

		}};


	int part1{0};
	int part2{0};

	int presentBits{0};
	int validBits{0};

	auto finalize = [&]() {
		part1 += (presentBits >= 0xfe);
		part2 += (validBits >= 0xfe);
		presentBits = validBits = 0; };

	string l;
	vs segs;
	vs kv;
	while (getline(cin, l)) {
		if (!l.empty()) {
			Split(l, ' ', segs);
			for (const auto& seg : segs) {
				Split(seg, ':', kv);
				int fn = fields.find(kv[0])/4;
				presentBits |= 1 << fn;
				validBits   |= (validators[fn](kv[1])) << fn; }}
		else {
			finalize(); }}
	finalize();
	cout << part1 << nl;
	cout << part2 << nl;
	return 0; }
