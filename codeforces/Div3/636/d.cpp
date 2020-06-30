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
#define dec(i,n,a) for(int i=(n); i>=(a); i--)
#define read(v, a, b) for(int i=(a); i<(b); i++) cin>>v[i]
#define printv(v, a, b) for(int i=(a); i < (b); i++) cout << v[i] << ' '
#define clr(a,v) memset(a, v, sizeof(a))
#define all(a) (a).begin(),(a).end()
#define FAST cin.tie(0), cout.tie(0), ios::sync_with_stdio(0)
#define max3(x, y, z) max(x, max(y, z))
#define db(x) cerr << #x << " == " << x << endl
#define _ << " " <<

const int maxn = 2e5 + 100, inf = 1e9+100;
int a[maxn], sump[maxn], numsums[2*maxn];
vi upb, lowb;

int main(){
	FAST;
	int t;
	cin >> t;
	while(t--){
		int n, k;
		cin >> n >> k;
		read(a,1,n+1);
		for(int i = 1; i <= n/2; i++){
			sump[i] = a[i] + a[n-i+1];
			upb.pb(k + max(a[i], a[n-i+1]) + 1);//It breaks if we want to get this sum
			lowb.pb(min(a[i], a[n-i+1]));//it breaks if we want to get this sum
		}
		sort(all(upb)); 
		sort(all(lowb)); 
		for(int i = 1; i <= n/2; i++){
			numsums[sump[i]]++;
		}
		
		int ans = inf;
		for(int i = 2; i <= 2*k; i++){
			int breaksup = upper_bound(all(upb), i) - upb.begin();
			int breaksdown = lowb.end()-lower_bound(all(lowb), i);
			ans = min(ans, (n/2 - numsums[i] + breaksup + breaksdown));
		}
		cout << ans << endl;
		upb.resize(0);
		lowb.resize(0);
		clr(numsums,0);
	}
}
