#include<bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0);
    cout.tie(0);
    ios_base::sync_with_stdio(0);

    int n, k;
    cin >> n >> k;
    string dummy;
    getline(cin, dummy);

    map<string, int> cnt;
    map<string, int> last;

    for (int i = 0; i < 3 * n; i++) {
        string s;
        getline(cin, s);
        cnt[s]++;
        last[s] = i;
    }

    vector<string> v;

    for (pair<string, int> ss : cnt) {
        v.push_back(ss.first);
    }

    // for (int i = 0; i < v.size(); i++) {
    //     cout << v[i] << ' ' << i << ' ' << cnt[v[i]] << ' ' << last[v[i]] << '\n';
    // }

    sort(v.begin(), v.end(), [&](string a, string b) { return ((cnt[a] != cnt[b]) ? (cnt[a] > cnt[b]) : (last[a] > last[b]));});

    for (int i = 0; i < min(k, (int)v.size()); i++) {
        cout << v[i] << '\n';
    }
//     cout << "what\n";
}
