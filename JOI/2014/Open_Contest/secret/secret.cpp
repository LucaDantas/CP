#include "secret.h"
#include<bits/stdc++.h>
using namespace std;

using pii = pair<int,int>;

#define ff first
#define ss second

constexpr int maxn = 1e3+10;

int a[maxn], n;

struct SegmentTree
{
	int pref[4*maxn][maxn], suf[4*maxn][maxn];
	void build(int node, int i, int j) {
		if(j - i <= 1) return;
		int m = (i+j) >> 1;

		pref[node][m] = a[m];
		for(int pos = m-1; pos >= i; pos--)
			pref[node][pos] = Secret(a[pos], pref[node][pos+1]);

		suf[node][m+1] = a[m+1];
		for(int pos = m+2; pos <= j; pos++)
			suf[node][pos] = Secret(suf[node][pos-1], a[pos]);

		build(2*node, i, m); build(2*node+1, m+1, j);
	}
	int query(int node, int i, int j, int l, int r) {
		if(i == j) return a[i];
		if(i+1 == j) return Secret(a[i], a[j]);
		int m = (i+j) >> 1;
		if(r <= m) return query(2*node, i, m, l, r);
		if(l > m) return query(2*node+1, m+1, j, l, r);
		return Secret(pref[node][l], suf[node][r]);
	}
} seg;

void Init(int N, int A[]) {
	for(int i = 0; i < N; i++)
		a[i] = A[i];
	n = N;
	seg.build(1, 0, n);
}

int Query(int L, int R) {
	if(L == R) return a[L];
	return seg.query(1, 0, n, L, R);
}
