#include<bits/stdc++.h>
using namespace std;

#define sz(a) (int)a.size()
#define int long long
typedef long long ll;

int32_t main() {
    string s ;int n;
    
    cin >> s >> n;
    queue<char> q;
    int ECounter = 0;

    for (int i = 0; i < sz(s); i++) {
        q.push(s[i]);
        if (s[i] == 'E') ECounter++;
    }
    ll ans = 1ll * sz(s) * n;
    if (ECounter == 0) {
        cout << 0 << '\n';
        return 0;
    }

    while (q.front() == 'P') {
        q.push(q.front());
        q.pop();
    }

    vector<char> v;
    for (int i = 0; i < sz(s); i++) {
        v.push_back(q.front());
        q.pop();
    }
    
    int counter = 0;
    
    for (int i = 1; i < sz(s); i++) {
        if (v[i] == 'P') {
            counter++;
            ans -= min(counter, n);
        } if (v[i] == 'E') {
            counter = 0;
        }
    }

    cout << ans <<'\n';
    return 0;
}