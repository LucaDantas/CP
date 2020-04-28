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

//SIEVE STARTS NOW

// minimum prime factors of numbers. init all 0
int min_prime_fact[1010];
vector<int> pr; // list of prime numbers

// one can use min_prime_fact for factorization
// while(x != 1) x /= min_prime_fact[x]

void sieve(int n){

    for(int i = 2; i <= n; ++i){
        if(min_prime_fact[i] == 0){ // prime!
            min_prime_fact[i] = i; // itself
            pr.push_back(i);
        }
        // for all primes less than or eq i, fill their product by i into min_prime_fact
        for(int j = 0; j < (int)pr.size(); j++){
            if(pr[j] > min_prime_fact[i]) break; //
            if(i * pr[j] > n) break; // out of range
            min_prime_fact[i * pr[j]] = pr[j];
        }
    }
}

//SIEVE ENDS NOW

int divisors(int n){
	for(auto p : pr){
		if(n%p == 0) return p;
	}
	return 1;
}


const int maxn = 1e3 + 100;
int a[maxn];
map<int, vi> s;
int ans[maxn];

int main(){
	FAST;
	sieve(1000);
	int T;
	cin >> T;
	while(T--){
		int n;
		cin >> n;
		read(a, 0, n);
		for(int i = 0; i < n; i++){
			int divn = divisors(a[i]);
			s[divn].pb(i);
		}
		//cout << ans << endl;
		cout << s.size() << endl;
		int pos = 0;
		for(auto it : s){
			pos++;
			for(auto k : it.s)
				ans[k] = pos;
		}
		for(int i = 0; i < n; i++){
			cout << ans[i] << ' ';
		}
		cout << endl;
		clr(ans, 0);
		s.clear();
	}
}
