#pragma once
#include <algorithm>
#include <cassert>
#include <iostream>
#include <numeric>
#include <string>
#include <string_view>
#include <tuple>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using vs = std::vector<std::string>;
using vi = std::vector<int>;
using vii = std::vector<std::pair<int, int>>;
const int oo = 0x3f3f3f3f;
const std::string nl{"\n"};
#define ALL(x) begin(x), end(x)
#define B(x) begin(x)
#define E(x) end(x)


template <typename T>
auto len(const T& c) -> int {
	return static_cast<int>(c.size()); }


struct Int2 {
	int x, y;
	auto operator+=(Int2 rhs) -> Int2& { x+=rhs.x; y+=rhs.y; return *this; }
	auto operator-=(Int2 rhs) -> Int2& { x-=rhs.x; y-=rhs.y; return *this; } };


void Split(const std::string& str, char delim, std::vector<std::string>& out) {
	std::string src(str);
	auto nextmatch = src.find(delim);
	std::size_t cnt{0};
	while (true) {
		auto item = src.substr(0, nextmatch);
		if (cnt < out.size()) {
			out[cnt].assign(src.substr(0, nextmatch)); }
		else {
			out.emplace_back().assign(src.substr(0, nextmatch)); }
		++cnt;
		if (nextmatch == std::string::npos) { break; }
		src = src.substr(nextmatch + 1);
		nextmatch = src.find(delim); }
	out.resize(cnt); }


struct CharMap {
	std::vector<char> data;
	const int stride;
	const int height;

	auto at(Int2 coord) const -> char {
		assert(0 <= coord.y && coord.y <= height);
		assert(0 <= coord.x && coord.x <= stride);
		return data[coord.y*stride + coord.x]; } };


auto LoadCharMatrix(std::istream& is) -> CharMap {
	std::string l;
	std::vector<std::string> lines;
	while (getline(is, l)) {
		lines.push_back(l); }
	const int stride = len(lines[0]);
	const int height = len(lines);
	std::vector<char> map(stride*height);
	for (int y=0; y<height; ++y) {
		for (int x=0; x<stride; ++x) {
			map[y*stride + x] = lines[y][x]; }}
	return { move(map), stride, height }; };


auto IsHex(char ch) -> bool {
	return ('0'<=ch && ch <= '9') || ('a'<=ch && ch<='f'); }
