#include "../lib.hpp"
using namespace std;

auto TakeDir(string_view t) -> pair<string_view, string_view> {
	if (t[0] == 'n' || t[0]=='s') {
		return { t.substr(0,2), t.substr(2) }; }
	return { t.substr(0,1), t.substr(1) }; }

const array<string_view, 6> dirs = {{ "e", "w", "se", "sw", "ne", "nw" }};

auto Go(Int2 a, string_view dir) -> Int2 {
	     if (dir=="e")  { return a + Int2{1,0}; }
	else if (dir=="w")  { return a + Int2{-1,0}; }
	else if (dir=="nw") { return a + Int2{a.y%2==0?-1:0,1}; }
	else if (dir=="sw") { return a + Int2{a.y%2==0?-1:0,-1}; }
	else if (dir=="ne") { return a + Int2{a.y%2!=0?1:0,1}; }
	else if (dir=="se") { return a + Int2{a.y%2!=0?1:0,-1}; }
	cerr << "Bad dir " << dir << nl;
	exit(1); }


int main() {
	Int2 btr{0,0};
	Int2 bbl{0,0};
	umap<Int2, bool> map{};

	string li;
	while (getline(cin, li)) {
		Int2 pos{0,0};
		string_view rem{li};
		string_view cmd;
		while (len(rem)) {
			tie(cmd, rem) = TakeDir(rem);
			pos = Go(pos, cmd);
			btr = vmax(btr, pos);
			bbl = vmin(bbl, pos); }
		map[pos] = !map[pos]; }

	// cerr << "extents " << btr << " -> " << bbl << nl;

	vector<char> lmap(256*256,0);
	auto tmap = lmap;

	auto At = [&](Int2 c) -> char& {
		return lmap[(-c.y + 128)*256 + (c.x+128)]; };
	auto Poke = [&](Int2 c, char x) -> void {
		tmap[(-c.y + 128)*256 + (c.x+128)] = x; };

	int p1=0;
	for (const auto& [coord, b] : map) {
		if (b) {
			p1++;
			At(coord) = 1; }}
	cout << p1 << nl;
	
	auto Turn = [&]() {
		for (int y=2; y<254; ++y) {
			for (int x=2; x<254; ++x) {
				Int2 coord{x-128,y-128};
				auto tile = At(coord);

				int ab=0;
				for (auto& dir : dirs) {
					auto c2 = Go(coord, dir);
					if (At(c2) == 1) ab++; }
				char result;
				if (tile==1) {
					result = !((ab==0) || (ab>2)); }
				else {
					result = ab==2?1:0; }
				Poke(coord, result); }}
		swap(lmap,tmap); };

	for (int n=0; n<100; ++n) Turn();

	auto p2 = accumulate(ALL(lmap), 0,
	                     [](auto ax, auto c) { return ax + bool(c); });
	cerr << p2 << nl;
	return 0; }
