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
#define db(x) cerr << #x << " == " << x << endl
#define _ << " " <<

const int maxn = 1e5 + 100;

int main(){
	FAST;
	int k[3];
	for(int i = 0; i < 3; i++)
		cin >> k[i];
	int n = k[0] + k[1] + k[2];
	vi a(n);
	for(int i = 0; i < 3; i++){
		for(int j = 0, t; j < k[i]; j++){
			cin >> t;
			a[t-1] = i;
		}
	}
	//start from the left with r = 0, which means that r everyone is on the r category
	vi cntr(3), cntl(3);
	for(int i = 0; i < n; i++){
		cntr[a[i]]++;
	}
	int ans = 0, best = 0;
	for(int i = 0; i < n; i++){
		if(a[i] != 2)
			ans++;
	}
	for(int i = 0; i < n; i++){
		cntr[a[i]]--;
		cntl[a[i]]++;
		best = max(best, cntl[0] - cntl[1]);
		int curans = cntr[0] + cntr[1] + cntl[2] + cntl[0] - best;
		//cout << curans << endl;
		ans = min(ans, curans);
	}
	
	cout << ans << endl;
}
