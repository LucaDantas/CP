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

const int maxn = 1e5 + 100;

int a[maxn], vzs[maxn], cnt[maxn], mx;

int main(){
	int n;
	scanf("%d", &n);
	read(a,1,n+1);
	int ans;
	mx = 0;
	cnt[0] = n;
	rep(i,1,n+1) {
		int & now = vzs[a[i]];
		cnt[now]--;
		now++;
		cnt[now]++;
		mx = max(mx, now);
		if(cnt[1] == i || cnt[i] == 1)
			ans = i;
		else if(cnt[1] == 1 && mx * cnt[mx] == i - 1)
			ans = i;
		else if(cnt[mx] == 1 && cnt[mx-1] * (mx - 1) == i - mx)
			ans = i;
	}
	printf("%d\n", ans);
}
