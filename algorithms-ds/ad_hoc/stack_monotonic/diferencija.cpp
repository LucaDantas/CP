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
#define trav(it, a) for(auto& it : a)

const int maxn = 3e5 + 100;

int n;

vi a;

int l1[maxn], r1[maxn], l2[maxn], r2[maxn];

void calc1(){
	stack<pii> s;

	for(int i = 1; i <= n; i++){
		
		while(!s.empty() && a[i] > s.top().ff)
			s.pop();
		
		if(s.empty())
			l1[i] = 1;
		else
			l1[i] = s.top().ss + 1;
	
		s.push(mp(a[i],i));
	}
	
	while(!s.empty())
		s.pop();
	
	for(int i = n; i >= 1; i--){
		
		while(!s.empty() && a[i] >= s.top().ff)
			s.pop();
		
		if(s.empty())
			r1[i] = n;
		else
			r1[i] = s.top().ss - 1;
	
		s.push(mp(a[i],i));
	}
}

void calc2(){
	stack<pii> s;

	for(int i = 1; i <= n; i++){
		
		while(!s.empty() && a[i] < s.top().ff)
			s.pop();
		
		if(s.empty())
			l2[i] = 1;
		else
			l2[i] = s.top().ss + 1;
	
		s.push(mp(a[i],i));
	}
	
	while(!s.empty())
		s.pop();
	
	for(int i = n; i >= 1; i--){
		
		while(!s.empty() && a[i] <= s.top().ff)
			s.pop();
		
		if(s.empty())
			r2[i] = n;
		else
			r2[i] = s.top().ss - 1;
	
		s.push(mp(a[i],i));
	}
}

int main(){
	scanf("%d", &n);
	
	a.resize(n+1);
	read(a,1,n+1);
	
	calc1();
	calc2();
		
	ll ans = 0;
	
	rep(i,1,n+1){
		ans += 1ll*a[i]*(i - l1[i] + 1)*(r1[i] - i + 1);
		ans -= 1ll*a[i]*(i - l2[i] + 1)*(r2[i] - i + 1);
	}
	printf("%lld\n", ans);
}
