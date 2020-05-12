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

const int MAXN = 1e6 + 100; // linear

// minimum prime factors of numbers. init all 0
int min_prime_fact[MAXN];
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
        for(int j = 0; j < pr.size(); j++){
            if(pr[j] > min_prime_fact[i]) break; //
            if(i * pr[j] > n) break; // out of range
            min_prime_fact[i * pr[j]] = pr[j];
        }
    }
}

int main(){
	FAST;
	int t; cin >> t;
	sieve(MAXN-10);
	while(t--){
		int n, k; cin >> n >> k;
		for(auto it : pr)
			if(n%it == 0) {n += it; break;}
		n+= 2*(k-1);
		cout << n << endl;
	}
}
