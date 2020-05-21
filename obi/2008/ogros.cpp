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

int n, a[maxn], f[maxn], o[maxn];

int bs(int forca){
	int l = 1, r = n-1, ans = 0;
	while(l <= r){
		int m = (l + r) >> 1;
		//db(m); db(a[m]);
		if(forca >= a[m])
			ans = m, l = m+1;
		else
			r = m-1;
	}
	return ans;
}

int main(){
	int m;
	scanf("%d %d", &n, &m);
	rep(i,1,n)
		scanf("%d", &a[i]);
	rep(i,0,n)
		scanf("%d", &f[i]);
	rep(i,1,m+1)
		scanf("%d", &o[i]);
		
	rep(i,1,m+1){
		printf("%d%c", f[ bs(o[i]) ], " \n"[i==m]);
		//printf("%d%c", bs(o[i]), " \n"[i==m]);
		//printf("%d\n", bs(o[i]));
	}
}
