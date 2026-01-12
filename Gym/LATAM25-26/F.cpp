#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

map<ll, int> factorize(ll n) {
    map<ll, int> factors;
    for(ll i = 2; i*i <= n; i++)
        while(!(n % i))
            ++factors[i], n /= i;
    if(n > 1)
        ++factors[n];
    return factors;
}

int main() {
    string s; cin >> s;
    ll n = stoll(s.substr(0, 10));
    map<ll, int> factors = factorize(n);
    if(s.size() > 10) {
        int fillers = (int)s.size() - 10;
        factors[2] += fillers;
        factors[5] += fillers;
    }
    cout << factors.size() << "\n";
    for(auto [p, cnt] : factors)
        cout << p << " " << cnt << "\n";
}
