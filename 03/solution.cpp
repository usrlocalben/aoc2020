#include "../lib.hpp"
using namespace std;

int main() {

	const auto map = LoadCharMatrix(cin);

	auto probe = [&](Int2 coord) -> std::optional<char> {
		if (coord.y < 0) return nullopt;
		if (coord.x < 0) return nullopt;
		if (coord.y >= map.height) return nullopt;
		auto mx = coord.x % map.stride;
		auto modcoord = Int2{ coord.x % map.stride, coord.y };
		return map.at(modcoord); };

	auto probePath = [&](const Int2 slope) -> int {
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
	cout << p1 << nl;

	const array<Int2, 5> dirs = {{
		{1,1}, {3,1}, {5,1}, {7,1}, {1,2} }};
	auto p2 = accumulate(ALL(dirs), int64_t(1), [&](int64_t ax, auto item) {
	                     return ax * probePath(item); });
	cout << p2 << nl;

	return 0; }
