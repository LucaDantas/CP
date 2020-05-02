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
#define read(v, a, b) for(int i=(a); i<(b); i++) cin>>v[i]
#define printv(v, a, b) for(int i=(a); i < (b); i++) cout << v[i] << ' '
#define clr(a,v) memset(a, v, sizeof(a))
#define all(a) (a).begin(),(a).end()
#define FAST cin.tie(0), cout.tie(0), ios::sync_with_stdio(0)
#define db(x) cerr << #x << " == " << x << endl
#define _ << " " <<

const int maxn = 2e5 + 100;

ll power[maxn], sum=0;
string names[maxn];
map<string, ll> m;

int main(){
	FAST;
	int n; cin >> n;
	for(int i = 0; i < n; i++){
		string s; cin >> s;
		if(m.find(s) == m.end())
			m[s] = 1;
		else
			m[s]++;
	}
	int cont = 1;
	for(auto it : m){
		names[cont] = it.f;
		sum += it.s;
		power[cont] = it.s;
		cont++;
	}
	for(int i = 1; i < cont; i++){
		if(power[i] > sum-power[i]){
			cout << names[i] << endl;
			return 0;
		}
	}
	cout << "NONE" << endl;
}
