#include "../lib.hpp"
using namespace std;

umap<int, array<array<int,4>,2>> tk;
umap<int, array<vs,2>> tiles;


const array<Int2, 4> dirs = {{ {0,-1}, {-1,0}, {0,1}, {1,0} }};

int Rev(int a) {
	int out = 0;
	for (int i=0; i<10; ++i) {
		out |= ((a&(1<<i))!=0) << (9-i); }
	return out; }

int Mod(int a, int b) {
	int tmp = a%b;
	return tmp < 0 ? tmp+b : tmp; }

constexpr int dim=12;

array<pair<short, pair<char,char>>, dim*dim> board{};
uset<short> used{};

bool OOB(Int2 a) {
	return a.x<0 || a.x>=dim || a.y<0 || a.y>=dim; }

int Idx(Int2 a) {
	return a.y*dim+a.x; }

vector<char> map;

constexpr int mdim = 12*8;

auto foorotate(Int2 coord, int rot, int dim) -> Int2 {
	coord.x =   coord.x *2 - (dim-1);
	coord.y = (-coord.y)*2 + (dim-1);
	for (int n=0; n<rot; ++n) {
		coord = rot90(coord, -1); }
	coord.y = -(coord.y-(dim-1))/2;
	coord.x =   (coord.x+(dim-1))/2;
	return coord; }


void DumpBoard() {
	for (int ty=0; ty<dim; ty++) {
		for (int y=0; y<10; ++y) {
			for (int tx=0; tx<dim; tx++) {
				for (int x=0; x<10; x++) {

					int pos = ty*dim+tx;
					auto [tid, config] = board[pos];
					auto [flip, rot] = config;

					auto coord = foorotate({x,y}, rot, 10);
					cout << tiles[tid][flip][coord.y][coord.x]; }
				cout << ' '; }
			cout << nl; }
		cout << nl; }}


auto Materialize() -> vector<char> {
	int od=12*8;
	vector<char> out(od*od, 0);

	for (int ty=0; ty<dim; ty++) {
		for (int y=0; y<10; ++y) {
			for (int tx=0; tx<dim; tx++) {
				for (int x=0; x<10; x++) {

					if (1<=y && y<9 &&
						1<=x && x<9) {

					int pos = ty*dim+tx;
					auto [tid, config] = board[pos];
					auto [flip, rot] = config;

					auto coord = foorotate({x,y}, rot, 10);
					char px = tiles[tid][flip][coord.y][coord.x];

					Int2 oc{ tx*8+x-1, ty*8+y-1 };
					out[oc.y*od+oc.x] = px; }}}}}
	return out; }


int Top   (int r) { return Mod(0-r,4); }
int Left  (int r) { return Mod(1-r,4); }
int Bottom(int r) { return Mod(2-r,4); }
int Right (int r) { return Mod(3-r,4); }


bool BT(int pos) {
	if (pos >= (dim*dim)) return true;
	Int2 coord{ pos%dim, pos/dim };
	for (const auto& [tid, flips] : tk) {
		if (used.find(tid) != end(used)) continue; // inuse
		used.insert(tid);

		for (int f=0; f<2; ++f) {
			auto& keys = flips[f];
			for (int r=0; r<4; ++r) {

				// top edge
				Int2 other = coord + Int2{0, -1};
				if (!OOB(other)) {
					auto [oid, setup] = board[Idx(other)];
					auto [oflip, orot] = setup;
					auto okey = tk[oid][oflip][Bottom(orot)];
					if (Rev(okey) != keys[Top(r)]) {
						continue; }}

				// left edge
				other = coord + Int2{-1, 0};
				if (!OOB(other)) {
					auto [oid, setup] = board[Idx(other)];
					auto [oflip, orot] = setup;
					auto okey = tk[oid][oflip][Right(orot)];
					if (Rev(okey) != keys[Left(r)]) {
						continue; }}

				board[pos] = { tid, {f,r} };
				if (BT(pos+1)) return true; }}

		used.erase(tid); }
	return false; }


int main() {
	string li;
	vs lines;
	int tid=-1;
	vs words;
	while (getline(cin, li)) {
		if (li.empty()) continue;
		if (li[0] == 'T') {
			Split(li, ' ', words);
			tid = stoi(words[1]); }
		else {
			tiles[tid][0].push_back(li);
			reverse(ALL(li));
			tiles[tid][1].push_back(li); }}

	for (auto [tid, maps] : tiles) {
		for (int f=0; f<2; ++f) {
			auto&m = maps[f];
			int k;

			k=0;
			for (int x=0; x<10; ++x) {
				if (m[0][x]=='#') k|= 1<<(9-x); }
			tk[tid][f][0] = k;

			k=0;
			for (int y=0; y<10; ++y) {
				if (m[y][0]=='#') k|= 1<<y; }
			tk[tid][f][1] = k;

			k=0;
			for (int x=0; x<10; ++x) {
				if (m[9][x]=='#') k|= 1<<x; }
			tk[tid][f][2] = k;

			k=0;
			for (int y=0; y<10; ++y) {
				if (m[y][9]=='#') k|= 1<<(9-y); }
			tk[tid][f][3] = k; }}

	if (!BT(0)) {
		cerr << "no solution\n";
		exit(1); }

	int64_t itl = 0;
	int64_t itr = itl + dim - 1;
	int64_t ibl = (dim-1)*dim;
	int64_t ibr = ibl + dim - 1;

	itl = board[itl].fi;
	itr = board[itr].fi;
	ibl = board[ibl].fi;
	ibr = board[ibr].fi;

	cout << (itl*itr*ibl*ibr) <<nl;

	//DumpBoard();
	map = Materialize();

	auto At = [&](Int2 coord, int f, int r) -> char {
		if (f=1) coord.x = mdim-coord.x-1;
		coord = foorotate(coord, r, mdim);
		return map[coord.y*mdim+coord.x]; };

	// 20x3
	char sm[20*3+1] = "                  # "
	                  "#    ##    ##    ###"
	                  " #  #  #  #  #  #   ";

	int f, r;
	for (f=0; f<2; ++f) {
		for (r=0; r<4; ++r) {
			for (int y=0; y<mdim-3; ++y) {
				for (int x=0; x<mdim-20; ++x) {
					bool hit{true};
					for (int sy=0; sy<3; ++sy) {
						for (int sx=0; sx<20; ++sx) {
							Int2 coord{ x+sx, y+sy };
							if (sm[sy*20+sx]=='#' && At(coord,f,r)!='#') {
								hit = false;
								break; }}
						if (!hit) break; }
					if (hit) {
						goto good; }}}}}
good:
	// f,r are setup
	// cerr << "f: " << f <<", r: " << r << nl;

	vector<char> hits(mdim*mdim, ' ');
	for (int y=0; y<mdim-3; ++y) {
		for (int x=0; x<mdim-20; ++x) {
			bool hit{true};
			for (int sy=0; sy<3; ++sy) {
				for (int sx=0; sx<20; ++sx) {
					Int2 coord{ x+sx, y+sy };
					if (sm[sy*20+sx]=='#' && At(coord,f,r)!='#') {
						hit = false;
						break; }}
				if (!hit) break; }
			if (hit) {
				for (int sy=0; sy<3; ++sy) {
					for (int sx=0; sx<20; ++sx) {
						hits[(y+sy)*mdim+x+sx] = sm[sy*20+sx]; }}}}}

	int part2{0};
	for (int y=0; y<mdim; ++y) {
		for (int x=0; x<mdim; ++x) {
			part2 += hits[y*mdim+x]!='#' && At(Int2{x,y},f,r)=='#'; }}
	cout << part2 << nl;
	return 0; }
