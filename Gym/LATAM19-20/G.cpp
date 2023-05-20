#include<bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

struct SuffixArray {
    vi sa, lcp;
    SuffixArray(string& s, int lim=256) {
        int n = sz(s) + 1, k = 0, a, b;
        vi x(all(s) + 1), y(n), ws(max(n, lim)), rank(n);
        sa = lcp = y, iota(all(sa), 0);
        for (int j = 0, p = 0; p < n; j = max(1, j * 2) , lim = p) {
            p = j, iota(all(y), n - j);
            rep(i, 0, n) if (sa[i] >= j) y[p++] = sa[i] - j;
            fill(all(ws), 0);
            rep(i, 0, n) ws[x[i]]++;
            rep(i, 1, lim) ws[i] += ws[i -1];
            for (int i = n; i--;) sa[--ws[x[y[i]]]] = y[i];
            swap(x, y), p = 1, x[sa[0]] = 0;
            rep(i, 1, n) a = sa[i - 1], b = sa[i], x[b] = (y[a] == y[b]) && y[a+j] == y[b+j] ? p - 1 : p++;
        }
        rep(i, 1, n) rank[sa[i]] = i;
        for (int i = 0, j; i < n - 1; lcp[rank[i++]] = k) 
            for (k && k--, j = sa[rank[i]-1]; s[i+k] == s[j+k]; k++);
    }
};

int main() {
    cin.tie(0)->ios_base::sync_with_stdio(0);
    string s;
    cin >> s;

    SuffixArray su = SuffixArray(s);
    
    auto comp = [&] (int sufInd, int len, char ch) -> int {
        int pos = sufInd + len - 1;
        if (pos > sz(s) - 1) return -1;
        if (s[pos] < ch) return -1;
        if (s[pos] == ch) return 0;
        if (s[pos] > ch) return 1;
        return -2;
    };

    int q; cin >> q;
    while(q--) {
        string ss;
        cin >> ss;
        int l = 1, r = sz(s);
        int accum = 0;
        int ans = 0;
        bool broken = false;

        for (int i = 0; i < sz(ss); i++) {
            // cout << i << ' ' << l << ' ' << r << '\n';
            if (accum == 0) ans++;
            if (comp(su.sa[l], accum+1, ss[i]) > 0 || comp(su.sa[r], accum+1, ss[i]) < 0) {
                if (accum == 0) {
                    cout << -1 << '\n';
                    broken = 1;
                    break;
                } else {
                    accum = 0;
                    i--;
                    l = 1;
                    r = sz(s);
                }
            } else {
                // cout << ss << ' ' << "What" << '\n';
                int templ = l, tempr = r;
                while (templ < tempr) {
                    int mid = (templ + tempr) / 2;
                    // if (i == 0) 
                    //    cout << i << ' ' << mid << ' ' << accum + 1 << ' ' << ss[i] << ' ' << comp(su.sa[mid+1], accum+1, ss[i]) << '\n'; 
                    if (comp(su.sa[mid], accum + 1, ss[i]) < 0) templ = mid + 1;
                    else tempr = mid;
                }
                int newl = templ;
                templ = l, tempr = r;
                while (templ < tempr) {
                    int mid = (templ + tempr + 1) / 2;
                    if (comp(su.sa[mid], accum + 1, ss[i]) > 0) tempr = mid - 1;
                    else templ = mid;
                }
                int newr = templ;
                // cout << newl << ' ' << newr << '\n';
                if (newl > newr) {
                    if (accum == 0) {
                        cout << -1 << '\n';
                        broken = 1;
                        break;
                    } else {
                        accum = 0;
                        i--;
                        l = 1;
                        r = sz(s);
                    }
                } else {
                    accum++;
                    l = newl;
                    r = newr;
                }
            }
        }

        if (!broken) cout << ans << '\n';
    }
}