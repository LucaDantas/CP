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

int main(){
	//FAST;
	int t; scanf("%d", &t);
	while(t--){
		int a,b,c; scanf("%d %d %d", &a, &b, &c);
		if(b==0 && a==0){ rep(i,0,c+1) putchar('1'); puts(""); continue;}
		if(b==0 && c==0){ rep(i,0,a+1) putchar('0'); puts(""); continue;}
		rep(i,0,a+1) putchar('0');
		rep(i,0,c+1) putchar('1');
		rep(i,0,b-1){ if(i&1) putchar('1'); else putchar('0');}
		puts("");
	}
}
