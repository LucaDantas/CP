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
	int x1, y1, x2, y2; scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
	if(x1 > x2) swap(x1, x2);
	if(y1 > y2) swap(y1, y2);

	int x3, y3, x4, y4; scanf("%d %d %d %d", &x3, &y3, &x4, &y4);
	if(x3 > x4) swap(x3, x4);
	if(y3 > y4) swap(y3, y4);

	x1 = max(x1, x3);
	x2 = min(x2, x4);
	y1 = max(y1, y3);
	y2 = min(y2, y4);

	if(x1 >= x2 || y1 >= y2) {printf("0\n"); return 0;}

	printf("%lld\n", 1ll*(y2-y1)*(x2-x1));
}
