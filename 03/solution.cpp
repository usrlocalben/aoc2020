#include <algorithm>
#include <array>
#include <cassert>
#include <iostream>
#include <numeric>
#include <string>
#include <string_view>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

template <typename T>
auto len(const T& c) -> int {
	return static_cast<int>(c.size()); }

struct Int2 {
	int x, y;
	auto operator+=(Int2 rhs) -> Int2& { x+=rhs.x; y+=rhs.y; return *this; }
	auto operator-=(Int2 rhs) -> Int2& { x-=rhs.x; y-=rhs.y; return *this; } };


int main() {

	string l;
	vector<string> lines;
	while (getline(cin, l)) {
		lines.push_back(l); }

	const auto stride = static_cast<int>(lines[0].size());
	const auto height = static_cast<int>(lines.size());

	vector<char> map( stride*height );
	for (int y=0; y<height; ++y) {
		for (int x=0; x<stride; ++x) {
			map[y*stride + x] = lines[y][x]; }}

	const auto probe = [&](Int2 coord) -> std::optional<char> {
		if (coord.y < 0) return nullopt;
		if (coord.x < 0) return nullopt;
		if (coord.y >= height) return nullopt;
		auto mx = coord.x % stride;
		return map[coord.y*stride + mx]; };

	const auto probePath = [&](const Int2 slope) -> int {
		Int2 pos{0,0};
		int t{0};
		while (1) {
			auto cell = probe(pos);
			if (!cell.has_value()) {
				break; }
			t += cell.value()=='#';
			pos += slope; }
		return t; };

	int p1 = probePath({ 3, 1 });
	cout << p1 << endl;

	array<Int2, 5> paths = { { {1,1}, {3,1}, {5,1}, {7,1}, {1,2} } };
	int64_t p2{1};
	for (auto path : paths) {
		p2 *= probePath(path); }
	cout << p2 << endl;

	return 0; }
