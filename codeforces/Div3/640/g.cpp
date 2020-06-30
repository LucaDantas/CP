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

const int maxn = 1e5 + 100;

int main(){
	//FAST;
	int t; scanf("%d", &t);
	while(t--){
		int n; scanf("%d", &n);
		if(n < 4) {puts("-1"); continue;}
		// case odd
		if(n&1){
			for(int i = 1; i <= n; i+=2) printf("%d ", i);
			printf("%d %d%c", n-3, n-1, " \n"[n==5]);
			for(int i = n-5; i >= 2; i-=2) printf("%d%c", i, " \n"[i==2]);
		}
		//case even
		else{
			for(int i = 1; i <= n-5; i += 2) printf("%d ", i);
			printf("%d %d ", n-1, n-3);
			for(int i = n; i >= 2; i -= 2) printf("%d%c", i, " \n"[i==2]);
		}
	}
}
