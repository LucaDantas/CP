#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

#ifdef MY_DEBUG_FLAG
template<typename T> void debug(T a) { cerr << a << ' '; }
template<typename T, typename U> void debug(pair<T, U> a) { cerr << a.first << ' ' << a.second << ' '; }
template<typename T> void debug(vector<T> a) { for(auto it : a) debug(it);}
template<typename T> void debug(set<T> a) { for(auto it : a) debug(it);}
#define db(a) cerr << "DEBUG ( " << #a << " == "; debug(a); cerr << ")\n"
#else
#define db(...)
#endif

#define pb push_back
#define ff first
#define ss second
#define fast ios_base::sync_with_stdio(false), cout.tie(nullptr), cin.tie(nullptr)
#define sz(a) ((int)(a).size())
#define rep(i,a,b) for(int i=(a); i<(b); i++)
#define dec(i,n,a) for(int i=(n); i>=(a); i--)
#define clr(a,v) memset(a, v, sizeof(a))
#define all(a) (a).begin(),(a).end()

constexpr int inf = 0x3f3f3f3f;
constexpr int MAXN = 1e5 + 10;
constexpr int LOGN = 20;
constexpr int mod = 1000000007;

int n, root;

int pai[MAXN][LOGN], menor[MAXN], in[MAXN], out[MAXN], aux = 0;

bool act[MAXN];

vi g[MAXN]; // contains only the children of a node

void calc_menor(int u) {
	menor[u] = u;
	for(auto v : g[u]) {
		calc_menor(v);
		menor[u] = min(menor[u], menor[v]);
	}
}

void dfs(int u) {
	in[u] = aux++;
	sort(all(g[u]), [](const int& a, const int& b) {
		return menor[a] < menor[b];
	});
	for(auto v : g[u]) {
		dfs(v);
	}
	out[u] = aux++;
}

struct comp {
	bool operator()(const int& a, const int& b) {
		return out[a] > out[b];
	}
};

priority_queue<int, vector<int>, comp> q;

void binary_parents() {
	for(int j = 1; j < LOGN; j++) {
		for(int i = 1; i <= n; i++) {
			if(pai[i][j-1] == 0) continue;
			pai[i][j] = pai[pai[i][j-1]][j-1];
		}
	}
}

int bit[2*MAXN];

void upd(int x, int v) {
	for(x++; x < 2*MAXN; x += x&-x)
		bit[x] += v;
}

int query(int x) {
	int ans = 0;
	for(x++; x > 0; x -= x&-x)
		ans += bit[x];
	return ans;
}

int add() {
	int now = q.top();
	q.pop();
	act[now] = 1;
	upd(in[now], 1);
	upd(out[now], -1);
	return now;
}

void remove(int k) {
	dec(i,LOGN-1,0) {
		if(pai[k][i] == 0) continue;
		if(act[pai[k][i]]) k = pai[k][i];
	}
	act[k] = 0;
	q.push(k);
	upd(in[k], -1); upd(out[k], 1);
}

int main() {
	int Q;
	scanf("%d %d", &n, &Q);
	rep(i,1,n+1) {
		int p; scanf("%d", &p);
		pai[i][0] = p;
		if(p == 0) root = i;
		else g[p].pb(i);
	}

	binary_parents();
	calc_menor(root);
	dfs(root);

	rep(i,1,n+1) q.push(i);

	while(Q--) {
		int type, k;
		scanf("%d %d", &type, &k);
		if(type == 1) {
			rep(i,0,k) {
				if(i == k-1) printf("%d\n", add());
				else add(); // returns the position that was added
			}
		}
		else {
			printf("%d\n", query(in[k])-1); // how many active parents he has
			remove(k); // removes the last parent of this guy 
		}
	}
}
