#include "../lib.hpp"
using namespace std;

auto main() -> int {
	string_view fields{"cid pid ecl hcl hgt eyr iyr byr"};

	using valfun = bool(*)(const string&);
	array<valfun, 8> validators = {{
		// cid always valid
		[](const string& s) -> bool { return true; },

		// pid
		[](const string& s) -> bool {
			return s.size() == 9 &&
			       all_of(ALL(s), [](auto ch) { return isdigit(ch); }); },

		// ecl
		[](const string& s) -> bool {
			return string_view{"amb blu brn gry grn hzl oth"}.find(s) != string::npos; },

		// hcl
		[](const string& s) -> bool {
			return s.size()==7 &&
			       s[0]=='#' &&
			       all_of(begin(s)+1, end(s), [](auto ch) { return isxdigit(ch); }); },

		// hgt
		[](const string& s) -> bool {
			if (s.size() >= 4) {
				auto m1 = s[s.size()-1];
				auto m2 = s[s.size()-2];
				auto m3 = s[s.size()-3];
				if (isdigit(m3)) {
					if (m2=='c' && m1=='m') {
						return inrange(stoi(s), 150, 193); }
					else if (m2=='i' && m1=='n') {
						return inrange(stoi(s), 59, 76); }}}
			return false; },

		// eyr
		[](const string& s) -> bool {
			return inrange(stoi(s), 2020, 2030); },

		// iyr
		[](const string& s) -> bool {
			return inrange(stoi(s), 2010, 2020); },

		// byr
		[](const string& s) -> bool {
			return inrange(stoi(s), 1920, 2002); }, }};


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
