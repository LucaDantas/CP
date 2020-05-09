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
	FAST;
	int t; cin >> t;
	while(t--){
		ll totA = 0, totB = 0, last = 0, cur = 0;
		int n; cin >> n;
		vi candy(n);
		for(auto &it : candy) cin >> it;
		int l = 0, r = n, cont=0;
		while(l<r){
			cont++;
			//db(totA + totB);
			//db(cont), db(l), db(r), db(totA), db(totB), db(cur), db(last);
			while(l < r && cur <= last) cur += candy[l++];
			totA += cur;
			last = cur;
			cur=0;
			if(l<r)cont++;
			while(l < r && cur <= last) cur += candy[--r];
			totB += cur;
			last = cur;
			cur=0;
			assert(cont <= n);
		}
		cout << cont << ' ' << totA << ' ' << totB << "\n";
	}
}
