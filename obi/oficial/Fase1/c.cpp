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

const int maxn = 1e3 + 100;

bool infected[maxn]; // No one is infected at the beginning

int main(){
	int n, m;
	scanf("%d %d", &n, &m);

	int v, r;
	scanf("%d %d", &v, &r);
	infected[v] = 1;

	rep(k,1,m+1) {
		int tam;
		scanf("%d", &tam);

		vi reuniao(tam);
		for(auto &it : reuniao)
			scanf("%d", &it);

		if(k < r) continue; // Ainda não foi ninguém infectado

		allin(it, reuniao) { // Checo se tem alguém infectado
			if(infected[it]) {
				// Contamino todos os outros e paro
				allin(p, reuniao) {
					infected[p] = 1;
				}
				break;
			}
		}
	}

	int ans = 0;
	rep(i,1,n+1)
		ans += infected[i];
	printf("%d\n", ans);
}
