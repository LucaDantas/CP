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
 
const int maxn = 1e7+100; // Queremos todos os primos até ai - raiz de 10⁷
 
int fat[maxn];
 
int main(){
	int n; scanf("%d", &n);
	vi a(n); read(a,0,n);
 
	// Sieve
	for(int i = 2; i*i < maxn; i++) {
		if(fat[i] == 0) {
			for(int k = i+i; k < maxn; k+=i)
				fat[k] = i;
		}
	}
 
	pii ans[n];
	rep(i,0,n) {
		if(fat[a[i]] == 0) ans[i] = {-1,-1};
		else {
			int div = fat[a[i]], cp = a[i];
			while(cp % div == 0) cp /= div;
			if(cp > 1) ans[i] = {div, cp};
			else ans[i] = {-1,-1};
		}
	}
 
	rep(i,0,n) printf("%d%c", ans[i].ff, " \n"[i==n-1]);
	rep(i,0,n) printf("%d%c", ans[i].ss, " \n"[i==n-1]);
}