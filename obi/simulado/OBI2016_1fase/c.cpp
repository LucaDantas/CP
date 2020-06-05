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
#define dec(i,a,b) for(int i=(a); i>=(b); i--)
#define trav(it, a) for(auto& it : a)
#define allin(it, a) for(auto it : a)
#define read(v, a, b) for(int i=(a); i<(b); i++) scanf("%d", &v[i]);
#define clr(a,v) memset(a, v, sizeof(a))
#define all(a) (a).begin(),(a).end()
#define FAST cin.tie(0), cout.tie(0), ios::sync_with_stdio(0)
#define db(x) cerr << #x << " == " << x << endl

const int maxn = 1e5 + 100;

int main(){
	int n; scanf("%d", &n);
	vi a(n), l(n), r(n), bad(n);
	read(a,0,n);
	int maior = 0, ans = 0;
	rep(i,0,n)
		if(a[i] >= maior) bad[i] = 1, maior = a[i];
	maior = 0;
	dec(i,n-1,0)
		if(a[i] >= maior) bad[i] = 1, maior = a[i];
	rep(i,0,n) if(!bad[i]) ans++;
	printf("%d\n", ans);
}
