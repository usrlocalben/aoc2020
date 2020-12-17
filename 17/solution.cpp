#include "../lib.hpp"
using namespace std;
int main() {
	constexpr int dim = 8/*input*/ + (6*2)/*growth*/ + 2/*oob margin*/;
	vector<char> za(    dim*dim*dim, 0); auto zb = za;
	vector<char> wa(dim*dim*dim*dim, 0); auto wb = wa;

	string l;
	int c=dim/2;
	int o=(dim-8)/2;
	for (int z=6; getline(cin, l); ++z) {
		for (int x=0; x<len(l); ++x) {
			za[                c*dim*dim + z*dim + x+o] = l[x]=='#';
			wa[c*dim*dim*dim + c*dim*dim + z*dim + x+o] = l[x]=='#'; }}

	auto Calc = [&]() {
		for (int x=1; x<dim-1; ++x)
		for (int y=1; y<dim-1; ++y)
		for (int z=1; z<dim-1; ++z) {
			bool lit = za[y*dim*dim + z*dim + x]!=0;

			int ax=0;
			for (int cx=-1; cx<=1; ++cx)
			for (int cy=-1; cy<=1; ++cy)
			for (int cz=-1; cz<=1; ++cz) {
				if (cx==0 && cy==0 && cz==0) continue;
				ax += za[(y+cy)*dim*dim + (z+cz)*dim + (x+cx)]; }

			bool result = lit ? (ax==2||ax==3) : (ax==3);
			zb[y*dim*dim + z*dim + x] = result;

			// p2
			for (int w=1; w<dim-1; ++w) {
				bool lit = wa[w*dim*dim*dim + y*dim*dim + z*dim + x]!=0;

				int ax=0;
				for (int cx=-1; cx<=1; ++cx)
				for (int cy=-1; cy<=1; ++cy)
				for (int cz=-1; cz<=1; ++cz)
				for (int cw=-1; cw<=1; ++cw) {
					if (cx==0 && cy==0 && cz==0 && cw==0) continue;
					ax += wa[(w+cw)*dim*dim*dim + (y+cy)*dim*dim + (z+cz)*dim + (x+cx)]; }

				bool result = lit ? (ax==2||ax==3) : (ax==3);
				wb[w*dim*dim*dim + y*dim*dim + z*dim + x] = result; }}
		swap(za,zb);
		swap(wa,wb); };

	for (int n=0; n<6; ++n) Calc();
	int part1 = accumulate(ALL(za), 0, [](auto ax, auto item) { return ax + (item!=0); });
	int part2 = accumulate(ALL(wa), 0, [](auto ax, auto item) { return ax + (item!=0); });
	cout << part1 << nl;
	cout << part2 << nl;
	return 0; }

