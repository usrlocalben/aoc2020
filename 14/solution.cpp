#include "../lib.hpp"
using namespace std;

umap<uint64_t, uint64_t> mem{};

void R(uint64_t value, uint64_t addr, uint64_t f) {
	if (!f) {
		mem[addr] = value; }
	else {
		auto fbit = uint64_t(1) << (__builtin_ffsll(f)-1);
		R(value, addr&(~fbit), f&(~fbit));
		R(value, addr|fbit,    f&(~fbit)); }}

int main() {
	string tmp;
	vs lines;
	while (getline(cin, tmp)) {
		lines.push_back(tmp); }

	uint64_t passMask, diffMask, floatMask;

	vs words;
	for (const auto& l : lines) {
		Split(l, ' ', words);
		if (words[0] == "mask") {
			auto& m = words[2];
			passMask = 0;
			diffMask = 0;
			for (int i=0; i<len(m); ++i) {
				passMask <<= 1;
				diffMask <<= 1;
				int pb, db;
				if (m[i]=='0') {
					pb=0, db=0; }
				else if (m[i]=='1') {
					pb=0, db=1; }
				else {
					pb=1, db=0; }
				passMask |= pb;
				diffMask |= db; }}
		else {
			int addr = stoi(words[0].substr(4));
			uint64_t value = stol(words[2]);
			mem[uint64_t(addr)] = (value&passMask) | diffMask; }}

	auto part1 = accumulate(ALL(mem), int64_t(0),
	                        [](auto ax, auto item) { return ax+item.se; });
	cout << part1 <<nl;

	mem.clear();
	for (const auto& l : lines) {
		Split(l, ' ', words);
		if (words[0] == "mask") {
			auto& m = words[2];
			passMask = 0;
			diffMask = 0;
			floatMask = 0;
			for (int i=0; i<len(m); ++i) {
				passMask <<= 1;
				diffMask <<= 1;
				floatMask <<= 1;
				int pb, db, fb;
				if (m[i]=='0') {
					pb=1, db=0, fb=0; }
				else if (m[i]=='1') {
					pb=0, db=1, fb=0; }
				else {
					pb=0, db=0, fb=1; }
				passMask |= pb;
				diffMask |= db;
				floatMask |= fb; }}
		else {
			uint64_t addr = stol(words[0].substr(4));
			uint64_t value = stol(words[2]);
			addr = (addr&passMask) | diffMask;
			R(value, addr, floatMask); }}

	auto part2 = accumulate(ALL(mem), int64_t(0),
	                        [](auto ax, auto item) { return ax+item.se; });
	cout << part2 << nl;
	return 0; }
