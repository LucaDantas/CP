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

// int fib[maxn];

// void fib(){
// 	fib[0] = 1;
// 	fib[1] = 1;
// 	for(int i = 2; i < maxn; i++) {
// 		fib[i] = fib[i-1] + fib[i-2];
// 	}
// }

int main(){
	// fib();
	int t; scanf("%d", &t);
	while(t--) {
		int a, b, n;
		scanf("%d %d %d", &a, &b, &n);
		if(a < b) swap(a,b);
		int cnt = 0;
		while(a <= n) {
			cnt++;
			b += a;
			swap(a,b);
		}
		printf("%d\n", cnt);
	}
}
