#include<bits/stdc++.h>
using namespace std;

constexpr long long mod = 1000000004257, p = 5;

vector<string> s(3);
int n;
int anss = INT_MAX;

char derive(char c1, char c2) {
    char luca = 'A' + 'B' + 'C' - c1 - c2;
    return luca;
}

int val(char c) { return c - 'A' + 1; }

vector<int> fstr(string a, string b) {
    int n = (int)(a.size());
    long long pn = 1;
    for(int i = 0; i < n; i++)
        pn = pn * p % mod;
    long long hash_b = 0, hash_a = 0;
    for(int i = 0; i < n; i++) {
        hash_a = (hash_a * p + val(a[i])) % mod;
        hash_b = (hash_b * p + val(b[i])) % mod;
    }
    vector<int> ans;
    for(int i = 0; i < n; i++) {
        if(hash_a == hash_b) ans.push_back(i);
        hash_a = (hash_a * p + val(a[i]) - pn * val(a[i]) % mod + mod) % mod;
    }
    return ans;
}

void solve() {
    swap(s[0], s[1]);
    swap(s[1], s[2]);

    for (int i = 0; i < n; i++) {
        int firstRot = min(i, n - i);
        string ss = "";  

        bool broken = 0;

        for (int j = 0; j < n; j++) {
            if (s[0][j] != s[1][(j + i) % n])
                ss.push_back(derive(s[0][j], s[1][(j + i) % n]));
            else {
                broken = 1;
                break;
            }
        }

        if (!broken) {
            string bigger = s[2] + s[2].substr(0, n - 1);
            vector<int> v = fstr(ss, bigger);
            sort(v.begin(), v.end());
            if (!v.empty()) 
                anss = min(anss, firstRot + min(v[0], n - v.back()));
        }
    }
}

int main() {
    for (int i = 0; i < 3; i++) {
        cin >> s[i];
    }
    n = s[0].size();

    
    
    for (int i = 0; i < 3; i++) {
        solve();
    }

    if (anss == INT_MAX) {
        cout << -1 << '\n';
    } else {
        cout << anss << '\n';
    }
}