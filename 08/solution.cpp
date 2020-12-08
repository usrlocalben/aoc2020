#include "../lib.hpp"
// 10:12:00
// 10:18:30
// 10:32:00
using namespace std;

constexpr int OP_NOP = 0;
constexpr int OP_ACC = 1;
constexpr int OP_JMP = 2;

int main() {
	string l;
	vs lines;
	vector<pair<int, int>> code;
	vs words;
	while (getline(cin, l)) {
		Split(l, ' ', words);
		auto& ins = words[0];
		int value = stoi(words[1]);
		if (ins == "nop") {
			code.push_back({ OP_NOP, value }); }
		else if (ins == "acc") {
			code.push_back({ OP_ACC, value }); }
		else if (ins == "jmp") {
			code.push_back({ OP_JMP, value }); }
		else {
			cerr << "unknown opcode [" << ins << "]\n";
			exit(1); }}

	uset<int> visited;
	auto Run = [&]() -> pair<bool, int> {
		visited.clear();
		int ax = 0;
		int ip = 0;
		while(1) {
			if (ip >= len(code)) {
				return { true, ax }; }
			if (visited.find(ip) != visited.end()) {
				return { false, ax }; }
			visited.insert(ip);

			auto [ opcode, value ] = code[ip];
			switch (opcode) {
			case OP_ACC:
				ax += value;
			case OP_NOP:
				ip++;
				break;
			case OP_JMP:
				ip += value;
				break;}}};

	auto [term, part1] = Run();
	tie(term, part1) = Run();
	cout << part1 << nl;

	int part2 = -1;
	for (int i=0; i<len(code); ++i) {
		// cout << ".";
		auto& op = code[i].first;
		if (op==OP_NOP || op==OP_JMP) {
			auto saved = op;
			op = (op==OP_NOP?OP_JMP:OP_NOP);
			auto [term, tmp] = Run();
			if (term) {
				part2 = tmp;
				break; }
			op = saved; }}

	cout << part2 << nl;
	return 0; }
