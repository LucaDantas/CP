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

const int maxn = 1e6 + 100;
/*
 The idea of this approach is to first calculate offline using prefix sum
 the number of ways that we can get to that interval, which we do by adding
 to the interval [x + B .. x + C] with x oscilating in the range [A..B]
 and then having this number of ways to get to that value with x+y
 we'll do another prefix sum but this time to get then number of ways to
 have x+y in the range [0..i] for every i, and then for us to get the
 answer we oscillate z in the range [C..D] and using that prefix sum we 
 add the number of ways to have x+y in the range [z+1 .. max] (max = B + C)
 then the answer is the sum for every value of z
*/

int main(){
	int A, B, C, D;
	scanf("%d %d %d %d", &A, &B, &C, &D);
	vll pref(maxn+1);
	
	for (int x = A; x <= B; x++) {
		pref[x+B]++;
		pref[x+C+1]--;
	}
	for (int i = 1; i <= maxn; i++) {
		pref[i] += pref[i-1];
	} 
	
	for (int i = 1; i <= maxn; i++) {
		pref[i] += pref[i-1];
	}
	ll ans = 0;
	for (int z = C; z <= D; z++) {
		ans += pref[maxn] - pref[z];
	}
	printf("%lld\n", ans);
}
