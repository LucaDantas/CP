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

int main(){
	int T; scanf("%d", &T);
	while(T--) {
		ll a, b, ans = 0;
		scanf("%lld %lld", &a, &b);
		if(a==b) { printf("0\n"); continue;}
		if(b < a) swap(a,b);
		while(b > a) {
			ans++;
			a <<= 1;
		}
		ll resp = ans/3 + (ans%3)/2 + (ans%3)%2;
		if(b == a) printf("%lld\n", resp);
		else printf("-1\n");
	}
}
