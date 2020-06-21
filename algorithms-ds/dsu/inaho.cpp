#include <bits/stdc++.h>
#include "inaho.h"
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

#define pb push_back
#define mp make_pair
#define ff first
#define ss second
#define sz(a) ((int)(a).size())
#define rep(i,a,b) for(int i=(a); i<(b); i++)
#define dec(i,a,b) for(int i=(a); i>=(b); i--)
#define trav(it, a) for(auto& it : a)
#define allin(it, a) for(auto it : a)
#define clr(a,v) memset(a, v, sizeof(a))
#define all(a) (a).begin(),(a).end()
#define db(x) cerr << #x << " == " << x << endl

// Link to the problem on dmoj -> https://dmoj.ca/problem/mmcc15p1

// Simple dsu roolback application problem but with interactive judge

const int maxn = 5e5+10;

struct Op
{
	int x, y, pesoX, pesoY;
};

stack<Op> s; // saves the last state of the changed nodes

int pai[maxn], peso[maxn];

void Init(int n) {
	rep(i,0,n+1) {
		pai[i] = i;
		peso[i] = 1;
	}
}

int find(int u) {
	if(pai[u] == u) return u;
	return find(pai[u]); // We can't compress the path due to the rollback
}

void AddEdge(int u, int v) {
	u = find(u);
	v = find(v);
	
	if(peso[u] < peso[v]) swap(u,v);

	Op now = {u,v,peso[u],peso[v]};
	s.push(now);

	if(u == v) return;
	
	peso[u] += peso[v];
	pai[v] = u;
}

void RemoveLastEdge(){
	Op now = s.top();
	s.pop();
	peso[now.x] = now.pesoX;
	peso[now.y] = now.pesoY;
	pai[now.x] = now.x;
	pai[now.y] = now.y;
}

int GetSize(int u) {
	return peso[find(u)];
}
