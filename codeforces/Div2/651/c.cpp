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

bool prime(int n) {
	for(int i = 2; i <= sqrt(n); i++) {
		if(n%i == 0) return false;
	}
	return true;
}

bool test(int n) {
	if(n == 1) return false;
	if(n == 2) return true;
	if(n%2) return true;
	int cnt = 0;
	while(n%2 == 0) n /= 2, cnt++;
	if(n == 1) return false; // pot de 2
	if(cnt == 1) {
		if(prime(n)) return false;
		else return true;
	}
	else return true;
}

int main(){
	int t; scanf("%d", &t);
	while(t--) {
		int n; scanf("%d", &n);
		puts(test(n)? "Ashishgup" : "FastestFinger");
	}
}
