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
	int t; scanf("%d", &t);
	while(t--) {
		int n, x;
		scanf("%d %d", &n, &x);
		vi a(n);
		read(a,0,n);
		int sum = accumulate(all(a),0);
		int left = -1, right = -1;
		rep(i,0,n) {
			if(a[i] % x) {
				left = i;
				break;
			}
		}
		for(int i = n-1; i >= 0; i--) {
			if(a[i] % x) {
				right = i;
				break;
			}
		}
		if(sum % x) printf("%d\n", n);
		else if(left != -1) printf("%d\n", n-min(left+1,n-right));
		else puts("-1");
	}
}
