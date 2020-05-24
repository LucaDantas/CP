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
	while(T--){
		int n; scanf("%d", &n);
		vi a(n);
		read(a,0,n);
		int even = 0, odd = 0;
		allin(it, a){
			if(it&1) odd++;
			else even++;
		}
		if(odd&1){
			bool broke = false;
			rep(i,0,n)
				rep(j,0,n)
					if(i != j)
						if(abs(a[i] - a[j]) == 1){
							broke = true;
							//break;
						}
			if(broke) puts("YES");
			else puts("NO");
		}
		else puts("YES");
	}
}
