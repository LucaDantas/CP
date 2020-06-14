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

struct square
{
	int x1, y1, x2, y2;
};

int main(){
	int a, b, c, d; scanf("%d %d %d %d", &a, &b, &c, &d);
	if(a > c) swap(a,c);
	if(b > d) swap(b,d);
	square m = {a,b,c,d};
	scanf("%d %d %d %d", &a, &b, &c, &d);
	if(a > c) swap(a,c);
	if(b > d) swap(b,d);
	square n = {a,b,c,d};
	if(m.x1 >= n.x2 || n.x1 >= m.x2 || m.y1 >= n.y2 || n.y1 >= m.y2) {printf("0\n"); return 0;}
	square ans;
	ans.x1 = max(n.x1, m.x1);
	ans.x2 = min(n.x2, m.x2);
	ans.y1 = max(n.y1, m.y1);
	ans.y2 = min(n.y2, m.y2);
	printf("%lld\n", 1ll*(ans.x2-ans.x1)*(ans.y2-ans.y1));
}
