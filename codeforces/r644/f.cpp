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

int difference(string a, string b){
	int m = sz(a);
	int ans = 0;
	rep(i,0,m)
		ans += (a[i] != b[i]);
	return ans;
}

int main(){
	FAST;
	int T; cin >> T;
	while(T--){
		int n, m; cin >> n >> m;
		vector<string> s(n);
		rep(i,0,n)
			cin >> s[i];
		rep(i,0,m){
			rep(letra,0,26){
				string now = s[0];
				now[i] = (char)('a'+letra);
				bool good = true;
				rep(id,0,n){
					if(difference(now, s[id]) > 1) good = false;
				}
				if(good){ cout << now << '\n'; goto done;}
			}
		}
		cout << "-1\n";
		done:
		;
	}
}
