#include "../lib.hpp"
using namespace std;
int main() {
	string li;
	vs lines;
	while (getline(cin, li)) {
		lines.push_back(li); }
	return 0; }

/* 2d grid w/Int2 coord
	for (int y=0; y<h; ++y) {
	for (int x=0; x<w; ++x) {
		Int2 coord{x,y};
		...
		}}
*/

/* 2d grid print
	for (int y=0; y<h; ++y) {
		for (int x=0; x<w; ++x) {
			cerr << foo[y*stride+x]; }
		cerr << nl; }
*/

/* grid tools
array<char, 4> UDLRchar = {{ '^', 'v', '>', '<' }};
const array<ivec2, 4> nsewDirs = {{ {0,-1}, {0,1}, {1,0}, {-1,0} }};
const array<string, 4> nsewStrs = {{ "north", "south", "east", "west" }};
*/

/* BFS w reverse path & first step
	auto visited = umap<ivec2, ivec2>{};
	auto queue = deque<tuple<ivec2, ivec2, int>>{};
	queue.push_back({ pos_, ivec2{oo,oo}, 0 });
	ivec2 found{oo,oo};
	while (!queue.empty()) {
		auto [here, prev, dist] = queue.front(); queue.pop_front();
		// cerr << "E" << here;
		if (visited.find(here) != end(visited)) continue;
		visited[here] = prev;

		// destination check
		if (here == dest) {
			// dist..
			found = here;
			break; }

		// queue outlinks
		for (auto dir : nsewDirs) {
			if (Map(here*2+dir) == '.') {
				queue.push_back({ here+dir, here, dist+1 }); }}}
	if (found == ivec2{oo,oo}) {
		cerr << "explore complete?\n";
		exit(1); }
	ivec2 pm1{oo,oo};
	ivec2 p = found;
	while (p!=pos_) {
		// cerr << "PM1 " << pm1 << nl;
		pm1 = p, p=visited[p]; }
	auto dir = pm1 - pos_;
*/



/* dijkstra
	priority_queue<ii, vii, greater<ii>> queue;
	uset<int> visited;
	umap<int, int> dist;

	auto getDistance = [&](int key) {
		if (auto search = dist.find(key); search != dist.end()) {
			return search->second; }
		else {
			return oo; }};

	queue.push({ 0, INITIAL_POSITION });
	dist[INITIAL_POSITION] = 0;
	vector<pair<int, int>> outLinks;

	int answer = -1;
	while (!queue.empty()) {
		auto [hdist, hpos] = queue.top(); queue.pop();
		if (visited.find(hpos) != visited.end()) {
			continue;}
		visited.insert(hpos);

		// do something with hpos @ hdist
		if (hpos == DESTINATION) {
			//cout << "found target\n";
			answer = hdist;
			break;}

		// fill outlinks
		outLinks.clear();
		// outLinks.push_back({ COST, NEXT_NODE });

		for (const auto& link : outLinks) {
			const auto& cost = link.fi;
			const auto& nextPos = link.se;
			int thisCost = getDistance(hpos) + cost;
			if (getDistance(nextPos) > thisCost) {
				dist[nextPos] = thisCost;
				queue.push({ thisCost, nextPos }); }}}
*/
