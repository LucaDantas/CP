#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;

#define pb push_back
#define mp make_pair
#define endl '\n'
#define f first
#define s second
#define sz(a) ((int)(a).size())
#define rep(i,a,b) for(int i=(a); i<(b); i++)
#define read(v, a, b) for(int i=(a); i<(b); i++) cin>>v[i]
#define printv(v, a, b) for(int i=(a); i < (b); i++) cout << v[i] << ' '
#define clr(a,v) memset(a, v, sizeof(a))
#define all(a) (a).begin(),(a).end()
#define FAST cin.tie(0), cout.tie(0), ios::sync_with_stdio(0)
#define db(x) cerr << #x << " == " << x << endl
#define _ << " " <<

const int maxn = 1e5 + 100;

int main(){
	FAST;
	int T; cin >> T;
	while(T--){
		int n; cin >> n;
		ll a = 0, b = 0;
		for(int i = 1; i <= n/2; i++){
			if(a <= b){
				a += (1ll<<(i+1));
				b += (1ll<<i);
			}
			else{
				b += (1ll<<i);
				a += (1ll<<(i+1));
			}
		}
		cout << max(a, b) - min(a,b) << '\n';
	}
}
