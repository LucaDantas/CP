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

		// db(now, last);

		long long ans = 0x3f3f3f3f3f3f3f3f, extra = 0;
		for(int i = tam; i < sz(last); i++)
			extra += d - last[i];
		for(int i = 0; i + tam <= sz(last); i++) {
			long long aq = extra;
			for(int j = 0; j < tam; j++)
				aq += abs(last[i+j]-now[j]);
			ans = min(ans, aq);
			// fprintf(stderr, "bruh %d == %lld %lld\n", i, aq, extra);
			if(i + tam < sz(last))
				extra += last[i] - (d - last[i+tam]);
		}
		// fprintf(stderr, "%lld %lld\n\n", ans, extra);

		last = now;
		printf("%lld\n", ans);
	}
}
