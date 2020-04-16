#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define mp make_pair
#define endl '\n'
#define ll long long
#define f first
#define s second
#define FAST cin.tie(0), cout.tie(0), ios::sync_with_stdio(0)
#define debug(x) cout << "DEBUG " << x << endl
#define debug2(x, y) cout << "DEBUG " << x << " " << y << endl
#define debug3(x, y, z) cout << "DEBUG " << x << " " << y << " " << z<< endl
#define debug4(x, y, z, o) cout << "DEBUG " << x << " " << y << " " << z<< " " << o << endl
#define max3(x, y, z) max(x, max(y, z))

const int maxn = 1e5 + 100;

vector<pair<int, int> > edges(maxn);
//vector<int> ans(maxn);
int ans[maxn];
vector< pair<int, vector<int>> > grau(maxn);

int main(){
	FAST;
	int n;
	bool top = false;
	cin >> n;
	memset(ans, -1, sizeof ans);
	for(int i = 1, a, b; i < n; i++){
		cin >> a >> b;
		edges[i] = mp(a,b);
		grau[a].f++, grau[a].s.pb(i);
		grau[b].f++, grau[b].s.pb(i);
	}
	for(int i = 1; i <= n; i++){
		if(grau[i].f > 2){
			for(int k = 0; k < 3; k++){
				ans[grau[i].s[k]] = k;
			}
			top = true;
			break;
		}
	}
	int now = (top)? 3 : 0;
	for(int i = 1; i < n; i++){
		if(ans[i] == -1) ans[i] = now++;
	}
	for(int i = 1; i < n; i++){
		cout << ans[i] << endl;
	}
}
