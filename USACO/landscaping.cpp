#include <cstdio>
#include <deque>

FILE *in, *out;

int x, y, z, difl, difr;
std::deque<int> l, r;

long long ans = 0;

int min(int a, int b) { return a < b ? a : b; }
int max(int a, int b) { return a > b ? a : b; }

void sr() {
	if(!l.size()) l.push_back(-y - difl);
	int passar = max(l.back() + difl, -y); l.pop_back();
	r.push_front(passar - difr);
	ans -= passar;
}

void sl() {
	if(!r.size()) r.push_front(x - difr);
	int passar = min(x, r.front() + difr); r.pop_front();
	l.push_back(passar - difl);
	ans += passar;
}

int main() {
	in = fopen("landscape.in", "r");
	out = fopen("landscape.out", "w");

	int n; fscanf(in, "%d %d %d %d", &n, &x, &y, &z);

	for(int i = 0; i < n; i++) {
		int a, b; fscanf(in, "%d %d", &a, &b);
		for(int j = 0; j < a; j++) sr();
		for(int j = 0; j < b; j++) sl();
		difl -= z, difr += z;
	}

	fprintf(out, "%lld\n", ans);
}