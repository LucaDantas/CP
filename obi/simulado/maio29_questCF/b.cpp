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

int a[maxn], vzs[maxn], count1, mx, diff;

int main(){
	int n;
	scanf("%d", &n);
	read(a,0,n);
	int ans = 1;
	mx = 1;
	vzs[a[0]] = 1;
	count1 = 1;
	diff = 1;
	rep(i,1,n) {
		int & now = vzs[a[i]];
		if(now == 1)
			count1--;
		if(now == 0)
			diff++, count1++;
		mx = max(mx, now+1);
		now++;
		if(mx == 1)
			ans = i+1;
		else if(count1 == 1 && (diff-1) == (i)/mx && (i)%mx == 0)
			ans = i+1;
		else if(diff == (i)/(mx-1) && i%(mx-1) == 0)
			ans = i+1;
	}
	printf("%d\n", ans);
}
