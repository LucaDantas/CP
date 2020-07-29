#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

template<typename T> ostream& operator<<(ostream &os, const vector<T> &v) { os << '['; string sep = ""; for (const auto &x : v) os << sep << x, sep = ", "; return os << ']'; }
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }
template<typename A> ostream& operator<<(ostream &os, const set<A> &s) { os << '{'; string sep = ""; for (const auto &x : s) os << sep << x, sep = ", "; return os << '}'; }
template<typename A, typename B> ostream& operator<<(ostream &os, const map<A, B> &m) { os << '{'; string sep = ""; for (const auto &x : m) os << sep << x.first << " -> " << x.second, sep = ", "; return os << '}'; }

#ifdef MY_DEBUG_FLAG
void debug() { cerr << '\n'; }
template<typename Ini, typename... Fim> void debug(Ini I, Fim... F) { cerr << " " << I; debug(F...); }
#define db(...) cerr << "DEBUG (" << #__VA_ARGS__ << ") ==", debug(__VA_ARGS__)
#else
#define db(...)
#endif

#define pb push_back
#define eb emplace_back
#define ff first
#define ss second
#define fast ios_base::sync_with_stdio(false), cout.tie(nullptr), cin.tie(nullptr)
#define sz(a) ((int)(a).size())
#define rep(i,a,b) for(int i=(a); i<(b); i++)
#define dec(i,n,a) for(int i=(n); i>=(a); i--)
#define clr(a,v) memset(a, v, sizeof(a))
#define all(a) (a).begin(),(a).end()

constexpr int inf = 0x3f3f3f3f;
constexpr int maxn = 2e6 + 10;
constexpr int logn = 20;
constexpr int mod = 1000000007;

int bit[maxn];

void fill() {rep(i,1,maxn) bit[i] = i&-i;}

void upd(int x, int v) {
	for(x++; x < maxn; x += x&-x)
		bit[x] += v;
}

int query(int x) {
	int ans = 0;
	for(x++; x > 0; x -= x&-x)
		ans += bit[x];
	return ans;
}

int bs(int x) {
	int pos = 0;
	dec(i, logn, 0) {
		if(pos + (1 << i) >= maxn) continue;
		if(bit[pos + (1 << i)] < x)
			pos += (1 << i), x -= bit[pos];
	}
	return pos;
}

int a[maxn], tree[4*maxn];

void build(int node, int i, int j) {
	if(i == j) {
		tree[node] = a[i];
		return;
	}
	int m = (i+j) >> 1;
	build(2*node, i, m); build(2*node+1, m+1, j);

	tree[node] = max(tree[2*node], tree[2*node+1]);
}

void update(int node, int i, int j, int pos, int val) {
	if(i == j) {
		tree[node] = a[i] = val;
		return;
	}

	int m = (i+j) >> 1;
	if(pos <= m)
		update(2*node, i, m, pos, val);
	else
		update(2*node+1, m+1, j, pos, val);

	tree[node] = max(tree[2*node], tree[2*node+1]);
}

int find(int node, int i, int j, int val, int limit) {
	if(i > limit || tree[node] <= val) return 0;

	if(i == j) return i;

	int m = (i+j) >> 1;

	int r = find(2*node+1, m+1, j, val, limit);

	if(r) return r;
	return find(2*node, i, m, val, limit);
}

int main() {
	fill();

	int n;
	scanf("%d", &n);
	
	vi add(n);
	rep(i,0,n)
		scanf("%d", &add[i]);

	vector<pair<int, pii>> q;
	
	int Q, cnt = 0;
	scanf("%d", &Q);
	
	rep(i,0,Q) {
		int op, x, y;
		scanf("%d %d %d", &op, &x, &y);

		q.pb({op, {x, y}});
	}

	dec(i, Q-1, 0) {
		int op = q[i].ff;
		int &x = q[i].ss.ff; 

		if(!op) {
			cnt++;
			int pos = bs(x+1);
			x = pos+1;
			upd(pos, -1);
		} else {
			x = bs(x)+1;
		}
	}

	dec(i,n-1,0) {
		int pos = bs(i+1)+1;
		a[pos] = add[i];
		add[i] = pos;
		upd(pos-1, -1);
	}

	clr(bit, 0);
	rep(i,0,n) upd(add[i], 1);

	n += cnt;

	build(1, 1, n);

	rep(i,0,Q) {
		int op = q[i].ff, x = q[i].ss.ff, y = q[i].ss.ss;

		if(!op) {
			update(1, 1, n, x, y);
			upd(x, 1);
		} else {
			printf("%d\n", query(find(1, 1, n, a[x] + y, x)));
		}
	}
}
