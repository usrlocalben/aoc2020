#include "../lib.hpp"
using namespace std;
constexpr int64_t M = 20201227;

int main() {
	string li;
	getline(cin, li); const int64_t a = stol(li);
	getline(cin, li); const int64_t b = stol(li);

	// find cycle-begin and cycle-length
	// for the pk-gen stage
	int64_t n = 1;
	int64_t s = 7;
	int lc=0;
	int a1,a2,b1,b2;
	a1=a2=b1=b2=-1;
	while (a1==-1 || a2==-1 || b1==-1 || b2==-1) {
		n = (n*s)%M;
		lc++;

		if (n==a) {
			if (a1==-1) {
				a1 = lc; }
			else {
				a2 = lc; }}
		else if (n==b) {
			if (b1==-1) {
				b1 = lc; }
			else {
				b2 = lc; }}}

	auto acl = a2-a1;
	auto bcl = b2-b1;

	// find cycle-length for ek-gen stage
	n=1, lc=0;
	vector<int64_t> pseen(M, -1);
	auto seen = pseen;
	while (pseen[n]==-1) {
		pseen[n] = seen[n], seen[n] = lc;
		n = (n*a)%M;
		lc++; }
	const int akp = seen[n] - pseen[n];

	n=1, lc=0;
	fill(ALL(pseen), -1);
	fill(ALL(seen), -1);
	while (pseen[n]==-1) {
		pseen[n] = seen[n], seen[n] = lc;
		n = (n*b)%M;
		lc++; }
	const int bkp = seen[n] - pseen[n];

	// cerr << "akp: " << akp << nl;
	// cerr << "bkp: " << bkp << nl;


	// find first match when loop-counts
	// are symmetric (n^2) using the cycle-
	// lengths to reduce the work.
	int ekey = -1;
	for (int64_t loopa=a1; ekey==-1; loopa+=acl) {
		// a-side processing b-pubkey
		auto ra = loopa % bkp;
		int64_t ak = 1;
		for (int n=0; n<ra; ++n) ak = ak*b%M;

		for (int64_t loopb=b1; loopb<loopa; loopb+=bcl) {
			// b-side processing a-pubkey
			auto rb = loopb % akp;
			int64_t bk = 1;
			for (int n=0; n<rb; ++n) bk = bk*a%M;

			if (ak==bk) {
				ekey = ak;
				break; }}}

	cout << ekey << nl;
	return 0; }
