#include "../lib.hpp"
using namespace std;
int main() {
	string li;
	getline(cin, li);
	auto init = li;

	auto Turn = [&]() {
		int cc = li[0] - '0';
		int dc = cc - 1;
		if (dc < 1) dc=9;

		rotate(begin(li)+1, begin(li)+4, end(li));

		bool found = false;
		while (!found) {
			for (int i=1; i<len(li)-3; ++i) {
				if (dc == (li[i]-'0')) {
					found=true;
					break; }}
				if (!found) {
					dc--;
					if (dc < 1) dc=9; }}

		auto dcpos = li.find(char(dc+'0'));

		rotate(begin(li)+dcpos+1, end(li)-3, end(li));
		rotate(begin(li), begin(li)+1, end(li)); };

	for (int n=0; n<100; ++n) Turn();
	int x = li.find('1');
	rotate(begin(li), begin(li)+x, end(li));
	cout << li.substr(1) << nl;


	// part2
	const int many = 1'000'000;
	vi after(many+1), before(many+1);
	for (int i=1; i<=many; ++i) {
		after[i] = i+1;
		before[i] = i-1; }
	before[1] = many;
	after[many] = 1;
	int front=1;

	auto RemoveAndInsertBefore = [&](int x, int p) {
		if (x==p) return;

		// unlink
		after[before[x]] = after[x];
		before[after[x]] = before[x];

		// relink
		after[x] = p;
		before[x] = before[p];
		before[p] = x;
		after[before[x]] = x;
		if (front==p) front = x;
		return; };

	// {int pos = head; for (int n=0; n<many; ++n) { cerr << pos << ", "; pos = after[pos]; } cerr << nl;}

	for (int i=len(init)-1; i>=0; --i) {
		int x = init[i]-'0';
		RemoveAndInsertBefore(init[i]-'0', front); }

	int cur = front;
	auto Turn2 = [&]() {
		const int p1 = after[cur];
		const int p2 = after[p1];
		const int p3 = after[p2];

		// remove p1/p2/p3
		after[cur] = after[p3];
		before[after[p3]] = cur;

		// select dc
		int dc = cur - 1; if (dc==0) dc = many;
		while (dc==p1 || dc==p2 || dc==p3) { dc--; if (dc==0) dc = many; }

		RemoveAndInsertBefore(p3, after[dc]);
		RemoveAndInsertBefore(p2, p3);
		RemoveAndInsertBefore(p1, p2);

		cur = after[cur]; };

	for (int n=0; n<10'000'000; ++n) Turn2();
	auto part2 = int64_t(after[1])*after[after[1]];
	cout << part2 << nl;
	return 0; }
