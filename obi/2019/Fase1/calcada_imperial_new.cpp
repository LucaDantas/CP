#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<int, pii> piii;
typedef vector<int> vi;
typedef vector<ll> vll;

#define pb push_back
#define mp make_pair
#define ff first
#define ss second
#define sz(a) ((int)(a).size())
#define rep(i,a,b) for(int i=(a); i<(b); i++)
#define trav(it, a) for(auto& it : a)
#define allin(it, a) for(auto it : a)
#define read(v, a, b) for(int i=(a); i<(b); i++) scanf("%d", &v[i]);
#define clr(a,v) memset(a, v, sizeof(a))
#define all(a) (a).begin(),(a).end()
#define FAST cin.tie(0), cout.tie(0), ios::sync_with_stdio(0)
#define db(x) cerr << #x << " == " << x << endl

const int maxn = 550;

int a[maxn], n;

int cnt(int x, int y) {
	int last = -1, ans = 0;
	rep(i,0,n) {
		if((a[i] != x && a[i] != y) || a[i] == last) continue;
		ans++;
		last = a[i];
	}
	return ans;
}

int main(){
	int ans = -1;
	scanf("%d", &n);
	read(a,0,n);
	rep(i,1,n+1) rep(j,i,n+1) ans = max(ans, cnt(i,j));
	printf("%d\n", ans);
}
