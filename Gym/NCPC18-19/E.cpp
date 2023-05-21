#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 800;

map<vector<int>,int> ids;

vector<int> g1[maxn], g2[maxn];

int n, m;

void brute1(vector<int> aq) {
	if(ids.count(aq)) return;
	ids[aq] = ids.size()+1;
	
	if((int)aq.size() == n) return;

	for(int i = aq.back(); i <= 6; i++) {
		aq.push_back(i);
		brute1(aq);
		aq.pop_back();
	}
}

void brute2(vector<int> aq) {
	if(ids.count(aq)) return;
	ids[aq] = ids.size()+1;
	
	if((int)aq.size() == m) return;

	for(int i = aq.back(); i <= 6; i++) {
		aq.push_back(i);
		brute2(aq);
		aq.pop_back();
	}
}

int TOT1[maxn], TOT2[maxn];

void transicao1() {
	for(auto [a,val] : ids) {
		for(int i = 0; i < a.size(); i++) {
			if(a[i] != 0) {
				vector<int> b=a;
				b[i]--;
				sort(b.begin(), b.end());
				g1[val].push_back(ids[b]);
				TOT1[val]++;
			}
		}
	}
}

void transicao2() {
	for(auto [a,val] : ids) {
		for(int i = 0; i < a.size(); i++) {
			if(a[i] != 0) {
				vector<int> b=a;
				b[i]--;
				sort(b.begin(), b.end());
				g2[val].push_back(ids[b]);
				TOT2[val]++;
			}
		}
	}
}

double dp[2][maxn][maxn];

int main() {
	int d; scanf("%d %d %d", &n, &m, &d);
	vector<int> va(n), vb(m);
	
	for(int i = 0; i < n; i++)
		scanf("%d", &va[i]);
	sort(va.begin(), va.end());
	for(int i = 0; i < m; i++)
		scanf("%d", &vb[i]);
	sort(vb.begin(), vb.end());
	
	for(int i = 0; i <= 6; i++)
		brute1({i});
	transicao1();
	int idva = ids[va];
	ids.clear();

	for(int i = 0; i <= 6; i++)
		brute2({i});
	transicao2();
	int idvb = ids[vb];
	ids.clear();

	for(int d1 = 0; d1 < maxn; d1++) for(int d2 = 0; d2 < maxn; d2++)
		if(TOT2[d2] == 0) dp[0][d1][d2] = 1;

	for(int poder = 1; poder <= min(d, 60); poder++) {
		for(int d1 = 0; d1 < maxn; d1++) for(int d2 = 0; d2 < maxn; d2++) {
			double& aq = dp[1][d1][d2];
			if(TOT2[d2] == 0) { aq = 1; continue; }
			for(auto v : g1[d1])
				aq += dp[0][v][d2] / (TOT1[d1] + TOT2[d2]);
			for(auto v : g2[d2])
				aq += dp[0][d1][v] / (TOT1[d1] + TOT2[d2]);
		}
		
		for(int d1 = 0; d1 < maxn; d1++) for(int d2 = 0; d2 < maxn; d2++)
			dp[0][d1][d2] = dp[1][d1][d2], dp[1][d1][d2] = 0;
	}

	printf("%.10lf\n", dp[0][idva][idvb]);
}
