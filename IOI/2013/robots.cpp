#include "robots.h"
#include<bits/stdc++.h>
using namespace std;

#define ff first
#define ss second

constexpr int maxn = 1e6+10;

using pii = pair<int,int>;

pii toy[maxn];

int x[maxn], y[maxn], a, b, n;

priority_queue<pii> q;

bool check(int k) {
	while(q.size()) q.pop();
	int ptr = 0;
	for(int i = 0; i < a; i++) {
		for(; ptr < n && toy[ptr].ff < x[i]; ++ptr)
			q.push({toy[ptr].ss, toy[ptr].ff});
		for(int j = 0; j < k && q.size(); j++)
			q.pop();
	}
	for(; ptr < n; ++ptr)
		q.push({toy[ptr].ss, toy[ptr].ff});
	for(int i = b-1; i >= 0; i--)
		for(int j = 0; j < k && q.size() && q.top().ff < y[i]; j++)
			q.pop();
	return !q.size();
}

int putaway(int A, int B, int T, int X[], int Y[], int W[], int S[]) {
	a = A; b = B; n = T;
	for(int i = 0; i < a; i++)
		x[i] = X[i];
	for(int i = 0; i < b; i++)
		y[i] = Y[i];
	for(int i = 0; i < T; i++)
		toy[i] = {W[i], S[i]};
	sort(x, x+a);
	sort(y, y+b);
	sort(toy, toy+n);
	int l = 1, r = T, ans = -1;
	while(l <= r) {
		int m = (l+r) >> 1;
		if(check(m)) ans = m, r = m-1;
		else l = m+1;
	}
	return ans;
}
