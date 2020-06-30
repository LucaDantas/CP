#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<int, pii> piii;
typedef vector<int> vi;
typedef vector<ll> vll;

#define pb push_back
#define mp make_pair
#define endl '\n'
#define ff first
#define ss second
#define sz(a) ((int)(a).size())
#define rep(i,a,b) for(int i=(a); i<(b); i++)
#define read(v, a, b) for(int i=(a); i<(b); i++) cin>>v[i]
#define clr(a,v) memset(a, v, sizeof(a))
#define all(a) (a).begin(),(a).end()
#define FAST cin.tie(0), cout.tie(0), ios::sync_with_stdio(0)
#define db(x) cerr << #x << " == " << x << endl
#define _ << " " <<

const int maxn = 1e5 + 100;

struct compara
{
    bool operator() (pii const &a, pii const &b) { 
		if(a.ss < b.ss) return true;
		if(a.ss == b.ss && a.ff > b.ff) return true;
		return false;	
	}
};

int main(){
	FAST;
	int t; cin >> t;
	while(t--){
		int n; cin >> n;
		vi ans(n);
		priority_queue<pii, vector<pii>, compara> q;
		q.push({0, n});
		int cont = 0;
		while(!q.empty()){
			cont++;
			int tam = q.top().ss;
			int beg = q.top().ff;
			q.pop();
			if(tam == 1) {ans[beg] = cont; continue;}
			if(tam == 2) {ans[beg] = cont; q.push({beg+1, 1}); continue;};
			//odd
			if(tam&1){
				int meio = beg + ((tam+1)>>1) - 1;
				ans[meio] = cont;
				q.push({beg, meio-beg});
				q.push({meio+1, meio-beg});
			}
			//even
			else{
				int meio = beg + ((tam)>>1) - 1;
				ans[meio] = cont;
				q.push({beg, meio-beg});
				q.push({meio+1, meio-beg+1});
			}
		}
		for(auto it : ans) cout << it << ' ';
		cout << '\n';
	}
}
