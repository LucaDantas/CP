#include <bits/stdc++.h>
#include "teams.h"
using namespace std;

#define all(a) (a).begin(), (a).end()

constexpr int maxn = 5e5+10;

int n, ind[maxn];

struct Node
{
	Node *l, *r;
	int v;
	Node() : l(this), r(this), v(0) {}
} *root[maxn];

struct PersistentSegmentTree
{
	Node* upd(Node* base, int i, int j, int pos, int v) {
		Node *node = new Node();
		*node = *base;
		node->v += v;
		if(i == j) return node;
		int m = (i+j) >> 1;
		if(pos <= m) node->l = upd(node->l, i, m, pos, v);
		else node->r = upd(node->r, m+1, j, pos, v);
		return node;
	}
	int query(Node* prev, Node* now, int i, int j, int l, int r) {
		if(i > r || j < l) return 0;
		if(i >= l && j <= r) return now->v - prev->v;
		int m = (i+j) >> 1;
		return query(prev->l, now->l, i, m, l, r) + query(prev->r, now->r, m+1, j, l, r);
	}
	int get(int l, int r, int k) {
		return query(root[ind[l]], root[ind[r]], 1, n, k, n);
	}
} seg;

pair<int,int> ranges[maxn];

void init(int N, int A[], int B[]) {
	n = N;
	for(int i = 0; i < N; i++)
		ranges[i] = {A[i], B[i]};
	sort(ranges, ranges+N);
	root[0] = new Node();
	for(int i = 1, ptr = 0; i <= N; i++) {
		for(; ptr < N && ranges[ptr].first == i; ptr++)
			root[ptr+1] = seg.upd(root[ptr], 1, n, ranges[ptr].second, 1);
		ind[i] = ptr;
	}
}

int fq[maxn];

long long dp[maxn]; // qual o menor valor de |v(S)| - |S| pra um subset até i

int can(int M, int K[]) {
	vector<int> V(M);
	for(int i = 0; i < M; i++)
		V[i] = K[i], ++fq[K[i]];
	sort(all(V));
	V.erase(unique(all(V)), V.end());
	M = (int)V.size();

	bool ok = 1;
	for(int i = 0; i < M; i++) {
		int k = V[i];
		dp[i] = seg.get(0, k, k) - 1ll * fq[k] * k;

		for(int j = 0; j < i; j++)
			dp[i] = min(dp[i], dp[j] + seg.get(V[j], k, k) - 1ll * fq[k] * k);

		ok &= dp[i] >= 0;
		if(!ok) break;
	}

	for(int i = 0; i < M; i++)
		dp[i] = fq[V[i]] = 0;

	return ok;
}