#include <bits/stdc++.h>
using namespace std;

struct Line {
	long long a, b;
	Line(long long _a, long long _b) : a(_a), b(_b) {}
	bool operator <(const Line& o) const { return a > o.a; }
	long long eval(long long x) const { return a*x + b; }
};

// queries are decreasing so we can always query the last value
struct CHT : multiset<Line> {
	bool hasNext(iterator it) { return next(it) != end(); }
	bool hasPrev(iterator it) { return it != begin(); }
	long double intersect(Line x, Line y) { return ((long double)(y.b-x.b)) / (x.a-y.a); }
	bool bad(Line a, Line b, Line c) { return intersect(a, c) <= intersect(a, b); }
	
	void add(Line l) {
		auto it = lower_bound(l);
		if(it != end() && it->a == l.a) {
			if(it->b < l.b) return;
			erase(it);
		}

		it = insert(l);
		
		if(hasNext(it) && hasPrev(it) && bad(*prev(it), *it, *next(it)))
			return (void)(erase(it));
		
		while(hasNext(it) && hasNext(next(it)) && bad(*it, *next(it), *next(next(it))))
			erase(next(it));

		while(hasPrev(it) && hasPrev(prev(it)) && bad(*prev(prev(it)), *prev(it), *it))
			erase(prev(it));
	}

	long long query(long long x) {
		if((size()) == 0) return 0x3f3f3f3f3f3f3f3f;

		// while(size() >= 2 && prev(end())->eval(x) >= prev( prev(end()) )->eval(x))
		while(size() >= 2 && intersect(*prev(end()), *prev(prev(end()))) >= x)
			erase(prev(end()));
		return prev(end())->eval(x);
	}
} cht;

constexpr int maxn = 2e5+10;

int nxt[maxn]; // next living guy after a water refill

long long X, N, M, W, T;

long long refill[maxn], time_person[maxn], kill_person[maxn], dp[maxn];

int main() {
	scanf("%lld %lld %lld %lld %lld", &X, &N, &M, &W, &T);
	for(int i = 1; i <= N; i++)
		scanf("%lld", &refill[i]);
	refill[++N] = X;

	sort(refill+1, refill+1+N, [&](long long x1, long long x2) { return x1%T > x2%T; });

	for(int i = 1; i <= M; i++)
		scanf("%lld %lld", &time_person[i], &kill_person[i]);

	vector<pair<long long, long long>> tempos; // o tempo T é o fim
	for(int i = 1; i <= M; i++)
		tempos.push_back({time_person[i], kill_person[i]});
	sort(tempos.begin(), tempos.end());

	for(int i = 0; i < M; i++)
		time_person[i+1] = tempos[i].first, kill_person[i+1] = tempos[i].second;
	time_person[M+1] = T; // setto o valor do piloto

	for(int i = 1; i <= N; i++)
		nxt[i] = lower_bound(time_person+1, time_person+1+M, refill[i] % T) - time_person; // ID do proximo cara vivo dps de mim

	for(int i = 2; i <= M; i++)
		kill_person[i] += kill_person[i-1];

	auto qtd = [&](long long tempo) { return X / T + (tempo < X%T); };

	dp[M+1] = W * (X/T + 1);
	for(int i = M, j = 1; i >= 1; i--) {
		// cht
		// val[j] + pref[i-1] = {dp[nxt[j]] + pref[nxt[j]-1] + (refill[j]/T) * W * (r+1)} + l * {- (refill[j] / T) * W}

		for(; j <= N && refill[j] % T >= time_person[i]; j++)
			cht.add(Line(-1 * (refill[j] / T) * W, dp[nxt[j]] + kill_person[nxt[j]-1] + (refill[j]/T)*W*((nxt[j]-1)+1) ));

		// opção 1: fico vivo até o final
		// opção 2: uso alguem pra me matar
		dp[i] = min(dp[i+1] + W * qtd(time_person[i]), cht.query(i) - kill_person[i-1]);
	}

	printf("%lld\n", dp[1]);
}
