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

// O valor de (x,y) é 
// ele cresce em uma PA de 2º grau tanto nas linhas como nas colunas com razao 1
// 

int main(){
	int T; scanf("%d", &T);
	while(T--) {
		ll x1,y1,x2,y2;
		scanf("%lld %lld %lld %lld", &x1, &y1, &x2, &y2);
		printf("%lld\n", (y2-y1)*(x2-x1) + 1);
	}
}
