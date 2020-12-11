#include "../lib.hpp"
using namespace std;
int main() {
	string l;
	vs lines;
	while (getline(cin, l)) {
		lines.push_back(l); }

	const int w = len(lines[0]);
	const int h = len(lines);
	vector<char> ma(w*h, '.');
	auto mb = ma;

	auto Init = [&]() {
	for (int y=0; y<h; ++y) {
		for (int x=0; x<w; ++x) {
		ma[y*w+x] = lines[y][x]; }}};

	auto At = [&](Int2 c) -> char {
		if (0 <= c.x && c.x < w &&
			0 <= c.y && c.y < h) {
			return ma[c.y*w+c.x]; }
		return '.'; };

	auto Compute1 = [&]() -> void {
		for (int y=0; y<h; ++y) {
			for (int x=0; x<w; ++x) {
				Int2 coord{x, y};

				char seat = At(coord);
				if (seat == '.') continue;

				int cnt =0;
				for (int ax=-1; ax<=1; ++ax) {
					for (int ay=-1; ay<=1; ++ay) {
						if (ax==0 && ay==0) continue;
						Int2 dir{ ax, ay };
						cnt += At(coord+dir)=='#'; }}

				char out;
				if (seat == 'L' && cnt==0) {
					out = '#'; }
				else if (seat == '#' && cnt>=4) {
					out = 'L'; }
				else {
					out = seat; }
				mb[coord.y*w+coord.x] = out;}}};

	Init();
	while(1) {
		Compute1();
		if (ma == mb) {
			break; }
		swap(ma, mb); }
	int part1 = 0;
	for (const auto& ch : ma) {
		part1 += ch=='#'; }
	cout << part1 << nl;


	auto Compute2 = [&]() -> void {
		int dist = max(w,h);
		for (int y=0; y<h; ++y) {
			for (int x=0; x<w; ++x) {
				Int2 coord{x, y};

				char seat = At(coord);
				if (seat == '.') continue;

				int cnt =0;
				for (int ax=-1; ax<=1; ++ax) {
					for (int ay=-1; ay<=1; ++ay) {
						if (ax==0 && ay==0) continue;
						Int2 dir{ ax, ay };

						bool oc = false;
						for (int d=1; d<max(w,h); ++d) {
							char nextSeat = At(coord+dir*d);
							if (nextSeat == 'L') {
								break; }
							else if (nextSeat == '#') {
								oc = true;
								break; }}
						cnt += oc; }}

				char out;
				if (seat == 'L' && cnt==0) {
					out = '#'; }
				else if (seat == '#' && cnt>=5) {
					out = 'L'; }
				else {
					out = seat; }
				mb[coord.y*w+coord.x] = out;}}};


	Init();
	while(1) {
		Compute2();
		if (ma == mb) {
			break; }
		swap(ma, mb); }
	int part2 = 0;
	for (const auto& ch : ma) {
		part2 += ch=='#'; }
	cout << part2 << nl;

	return 0; }
