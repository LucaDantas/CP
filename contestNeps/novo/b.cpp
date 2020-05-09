#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<int, pii> piii;
typedef vector<int> vi;
typedef vector<ll> vll;

#define pb push_back
#define mp make_pair
#define endl '\n'
#define ff first
#define ss second
#define sz(a) ((int)(a).size())
#define rep(i,a,b) for(int i=(a); i<(b); i++)
#define read(v, a, b) for(int i=(a); i<(b); i++) cin>>v[i]
#define clr(a,v) memset(a, v, sizeof(a))
#define all(a) (a).begin(),(a).end()
#define FAST cin.tie(0), cout.tie(0), ios::sync_with_stdio(0)
#define db(x) cerr << #x << " == " << x << endl
#define _ << " " <<

const int maxn = 1e7 + 100;

vi fib = {1,1};

void calcfib(void){
	for(int i = 2; fib[i-1] <= maxn; i++)
		fib.pb(fib[i-1] + fib[i-2]);
}

int main(){
	//FAST;
	int n; scanf("%d", &n);
	vi ans(n,1);
	calcfib();
	auto it = lower_bound(all(fib),n);
	int falta = *it - n;
	//cout << falta << endl;
	for(int i = n-1; i >= 0 && falta > 0; i--){
		db(falta);
		ans[i] += min(8,falta);
		falta -= min(8,falta);
	}
	rep(i, 0, sz(ans)) printf("%d", ans[i]);
	puts("");
}
