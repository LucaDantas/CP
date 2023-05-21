#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 1e4 * 12 * 26 + 10;

struct Trie {
    int t;
    struct Node {
        int child[26], cnt;
    } trie[maxn];
    void add(const string& s, int l, int node) {
        trie[node].cnt++;
        if(l == s.size()) return;
        if(s[l] == '*') {
            for(int i = 0; i < 26; i++) {
                if(!trie[node].child[i])
                    trie[node].child[i] = ++t;
                add(s, l+1, trie[node].child[i]);
            }
        } else {
            if(!trie[node].child[s[l]-'a'])
                trie[node].child[s[l]-'a'] = ++t;
            add(s, l+1, trie[node].child[s[l]-'a']);
        }
    }
    pair<int, string> get(int node, char lt) {
        pair<int, string> ans;
        for(int i = 0; i < 26; i++)
            if(trie[node].child[i]) {
                auto here = get(trie[node].child[i], (char)('a'+i));
                if(here.first > ans.first)
                    ans = here;
            }
        if(lt != '*')
            ans.second.push_back(lt);
        if(!ans.first)
            ans.first = trie[node].cnt;
        return ans;
    }
} t;

int main() {
    int n, c; scanf("%d %d", &n, &c);
    string s;
    for(int i = 0; i < n; i++) {
        cin >> s;
        int index = s.find('*');
        t.add(s, 0, 0);
    }
    auto ans = t.get(0, '*');
    reverse(ans.second.begin(), ans.second.end());
    cout << ans.second << ' ' << ans.first << endl;
}
