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

int cnt[30], odd;

char lombra = '#';

int main(){
	string s; cin >> s;
	allin(c, s) cnt[c-'a']++;
	if(sz(s)&1) odd = 1;
	vi trocar;
	rep(i,0,26) if(cnt[i]&1) trocar.pb(i);
	if(odd) lombra = (char)trocar[sz(trocar)/2]+'a';
	rep(i,0,sz(trocar)/2) cnt[trocar[i]]++;
	string mid = "";
	rep(i,0,26) {
		rep(k,0,cnt[i]/2) mid.pb((char)(i+'a'));
	}
	cout << mid; if(lombra != '#') cout << lombra;
	reverse(all(mid)); cout << mid << "\n";
}
