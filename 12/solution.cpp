#include "../lib.hpp"
using namespace std;
int main() {
	vector<pair<char, int>> cmd;
	string l;
	while (getline(cin, l)) {
		auto a = l[0];
		auto b = stoi(l.substr(1));
		cmd.push_back({ a, b }); }

	const Int2 init{0,0};
	Int2 pos = init;
	Int2 heading{1,0};
	for (const auto& c : cmd) {
		auto [ch, amt] = c;
		switch (ch) {
		case 'N': pos += Int2{ 0, 1} * amt; break;
		case 'S': pos += Int2{ 0,-1} * amt; break;
		case 'E': pos += Int2{ 1, 0} * amt; break;
		case 'W': pos += Int2{-1, 0} * amt; break;
		case 'R': while (amt) { heading=rot90(heading, -1); amt-=90; } break;
		case 'L': while (amt) { heading=rot90(heading,  1); amt-=90; } break;
		case 'F': pos += heading * amt; break;
		default: cout << "bad ch " << ch << nl; exit(1); }}
	cout << pos.md() << nl;

	pos = init;
	Int2 wp{10,1};
	for (const auto& c : cmd) {
		auto [ch, amt] = c;
		switch (ch) {
		case 'N': wp += Int2{ 0, 1} * amt; break;
		case 'S': wp += Int2{ 0,-1} * amt; break;
		case 'E': wp += Int2{ 1, 0} * amt; break;
		case 'W': wp += Int2{-1, 0} * amt; break;
		case 'R': while (amt) { wp=rot90(wp, -1); amt-=90; } break;
		case 'L': while (amt) { wp=rot90(wp,  1); amt-=90; } break;
		case 'F': pos += wp * amt; break;
		default: cout << "bad ch " << ch << nl; exit(1); }}
	cout << pos.md() << nl;
	return 0; }
