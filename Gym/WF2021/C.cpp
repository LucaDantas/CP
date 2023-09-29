#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
ll k, n;

ll root(ll num) {
    if (k-1 >= 60) return 1;

    ll l = 1, r = num;
    while (l < r) {
        ll mid = (l + r + 1) / 2;
        ll cur = 1;

        bool exceed = false;
        for (int i = 0; i < k-1; i++) {
            cur *= mid;
            if (i < k - 2 && (num / cur) < mid) {
                exceed = true;
                break; 
            } 
        }
        
        if (exceed) {
            r = mid - 1;
        } else {
            l = mid;
        }
    }

    return l;
}

ll po(ll base) {
    ll ans = 1;
    for (int i = 0; i < k-1; i++) {
        ans *= base;
    }
    return ans;
}

int main() {
    cin >> k >> n;

    for (ll q = 2; q <= root(n); q++) {
        ll q_to_k_1 = po(q);    

        for (ll p = 1; p < q; p++) {
            ll div = 0; 
            // cout << q << ' ' << p << ' ' << div << '\n';
            ll cur = q_to_k_1;
            bool div_exceeded = false;
            for (int i = 0; i < k; i++) {
                div += cur;
                if (div > n) {
                    div_exceeded = true;
                    break;
                }
                cur = cur / q * (q-p);
            }
            if (div_exceeded) {
                continue;
            } else {
                if (n % div == 0) {
                    cout << p << ' ' << q << '\n';
                    return 0;
                }
            }
        }

    }

    cout << "impossible\n";
}
