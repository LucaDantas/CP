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

const int inf = 1e9 + 100;
const int maxn = 132700;

struct rect{
	int l, r, b, t;
	bool operator == (rect rec) const{
		if(l == rec.l && r == rec.r && t == rec.t && b == rec.b) return true;
		return false;
	}
	bool operator != (rect rec) const{
		if(l == rec.l && r == rec.r && t == rec.t && b == rec.b) return false;
		return true;
	}
};

rect pref[maxn], suf[maxn], ent[maxn], rinf = {inf, inf, inf, inf};

rect intersection(rect a, rect b){
	rect ans;
	ans.l = max(a.l, b.l);
	ans.r = min(a.r, b.r);
	ans.t = min(a.t, b.t);
	ans.b = max(a.b, b.b);
	if(a == rinf || b == rinf || ans.b > ans.t || ans.l > ans.r) return rinf;
	return ans;
}

int main(){
	FAST;
	int n;
	cin >> n;
	for(int i = 1, x1, y1, x2, y2; i <= n; i++){
		cin >> x1 >> y1 >> x2 >> y2;
		ent[i] = {x1, x2, y1, y2};
	}
	pref[1] = ent[1];
	suf[n] = ent[n];
	for(int i = 2; i <= n; i++){
		pref[i] = intersection(pref[i-1], ent[i]);
		suf[n-i+1] = intersection(suf[n-i+2], ent[n-i+1]);
	}
	if(pref[n-1] != rinf)
		cout << pref[n-1].l << ' ' << pref[n-1].b << endl;
	else if(suf[2] != rinf)
		cout << suf[2].l << ' ' << suf[2].t << endl;
	else{
		for(int i = 2; i <= n-1; i++){
			rect now = intersection(pref[i-1], suf[i+1]);
			if(now != rinf){
				cout << now.l << ' ' << now.t << endl;
				break;
			}
		}
	}
}
