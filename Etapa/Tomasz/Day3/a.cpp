#include <cstdio>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

template<typename T> ostream& operator<<(ostream &os, const vector<T> &v) { os << '['; string sep = ""; for (const auto &x : v) os << sep << x, sep = ", "; return os << ']'; }

#ifdef MY_DEBUG_FLAG
void debug() { cerr << endl; }
template<typename Ini, typename... Fim> void debug(Ini I, Fim... F) { cerr << I; if(sizeof...(F)) cerr << ", "; debug(F...);}
#define db(...) cerr << "DEBUG (" << #__VA_ARGS__ << ") == ", debug(__VA_ARGS__)
#else
#define db(...)
#endif

#define sz(a) (int)(a.size())
#define all(a) (a).begin(), (a).end()

constexpr int maxn = 5e5+10;

int Tcima[maxn], Tbaixo[maxn];
vector<int> troca[maxn];

int main() {
	int n; long long d; scanf("%d %lld", &n, &d);
	vector<long long> last, now;
	for(int rep = 0; rep < n; rep++) {
		int tam; scanf("%d", &tam);
		now.resize(tam);
		for(long long& x : now)
			scanf("%lld", &x);

		if(!rep) {last = now; continue;}

		for(int i = 0; i < tam; i++)
			last.push_back(d);
		reverse(all(last));
		for(int i = 0; i < tam; i++)
			last.push_back(0);
		reverse(all(last));

		vector<long long> meio(sz(last) + 1);

		auto add = [&](int l, int r, long long v) { if(l > r) return; meio[l] += v, meio[r+1] -= v; };
		auto go = [&]() { for(int i = 1; i < sz(meio); i++) meio[i] += meio[i-1]; };

		// tempo dos caras antigos
		for(int i = tam, ptr = 0; i < sz(last); i++) {
			while(ptr < sz(now) && now[ptr] <= last[i]) ++ptr;
			int ini = max(0, i-(tam-1)), final = i, passa = ini + (tam - ptr);
			add(ini, passa-1, -last[i]);
			add(passa, final, last[i]);
		}

		// tempos dos caras novos
		for(int i = 0, ptr = 0; i < sz(now); i++) {
			while(ptr < sz(last) && last[ptr] < now[i]) ++ptr;
			int ini = 0, final = sz(meio)-2, passa = max(0, ptr - i);
			add(ini, passa-1, now[i]);
			add(passa, final, -now[i]);
		}

		go();
		// db(now, last);
		// db(meio);
		// debug();

		long long ans = 0x3f3f3f3f3f3f3f3f, extra = 0;

		for(int i = tam; i < sz(last); i++)
			extra += d - last[i];

		for(int i = 0; i + tam <= sz(last); i++) {
			ans = min(ans, extra + meio[i]);
			if(i + tam < sz(last))
				extra += last[i] - (d - last[i+tam]);
		}

		last = now;
		printf("%lld\n", ans);
	}
}
