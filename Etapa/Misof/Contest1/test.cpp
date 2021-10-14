#include <bits/stdc++.h>
using namespace std;

using pii = pair<int,int>;

#define pb push_back

constexpr int maxn = 1e7+10;

int f[maxn];

vector<int> pr;

void sieve() {
	for(int i = 2; i < maxn; i++) {
		if(!f[i])
			f[i] = i, pr.pb(i);
		for(int j = 0; j < (int)pr.size() && pr[j] <= f[i] && 1ll*i*pr[j] < maxn; j++)
			f[i*pr[j]] = pr[j];
	}
}

vector<pii> dv(int n) {
	vector<pii> ans;
	while(n > 1) {
		if(ans.size() && ans.back().first == f[n])
			++ans.back().second;
		else ans.pb({f[n], 1});
		n /= f[n];
	}
	return ans;
}

long long gcd(long long a, long long b) { return !b ? a : gcd(b, a%b); }

long long val[maxn], pre[maxn];
map<long long, vector<long long>> dvs;
set<long long> st;

const int sla = 35, linha = 1000/sla;
//const int sla = 25, linha = 1000/sla;
//const int sla = 5, linha = 4;
int main() {
	sieve();
	int n = sla*linha;
	//long long m; scanf("%lld", &m);
	long long m = 1243194872394ll;
	for(int i = 0; i < linha; i++)
		for(int j = 0; j < sla; j++)
			pre[i*sla + j] = m*i + j;

	int t = 0;
	for(int i = 0; i < n; i++)
		for(int j = i+1; j < n; j++)
			val[t++] = abs(pre[i] - pre[j]), st.insert(val[t-1]);

	sort(val, val+t);
	t = (int)(unique(val, val+t)-val);
	
	printf("%d %d %d | %d\n", linha, sla, linha*sla, t);

	for(int i = 0; i < t; i += 2*sla) {
		for(int p : pr) {
			int add = (p - (val[i] % p)) % p;
			while(st.count(add+val[i])) assert((val[i] + add) % p == 0),
				dvs[val[i]+add].push_back(p), add+=p;
		}
		for(int j = 0; j < 2*sla; j++)
			if(val[i+j] > 1) dvs[i+j].push_back(val[i+j]);
	}
}
