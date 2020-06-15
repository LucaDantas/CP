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

const int mod = 998244353;

int main(){
	int n, m;
	scanf("%d %d", &n, &m);
	
	vector<int> a(n), b(m);

	for(auto &it : a)
		scanf("%d", &it);

	for(auto &it : b)
		scanf("%d", &it);
	
	for(int i = n-2; i >= 0; i--) {
		a[i] = min(a[i], a[i+1]);
	}
	
	if(a[0] != b[0]){
		printf("0\n");
		return 0;
	}

	int ans = 1;

	for(int i = 1; i < m; i++) {
		// We jump 0 because we can't split it, it has to be considered completely
		int qtd = upper_bound(all(a), b[i]) - lower_bound(all(a), b[i]);
		ans = (int)((1ll*ans*qtd)%mod);
	}

	printf("%d\n", ans);
}
