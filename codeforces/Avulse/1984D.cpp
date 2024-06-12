#include <bits/stdc++.h>
using namespace std;

#define sz(a) (int)(a.size())
#define rep(i,a,b) for(int i = a; i < b; i++)

typedef long long ll;
typedef uint64_t ull;
struct H {
    ull x; H(ull _x=0) : x(_x) {}
    H operator+(H o) { return x + o.x + (x + o.x < x); }
    H operator-(H o) { return *this + ~o.x; }
    H operator*(H o) { auto m = (__uint128_t)x * o.x;
        return H((ull)m) + (ull)(m >> 64); }
    ull get() const { return x + !~x; }
    bool operator==(H o) const { return get() == o.get(); }
    bool operator<(H o) const { return get() < o.get(); }
};
static const H C = 2856937867L; // (order ~ 3e9; random also ok)

struct HashInterval {
    vector<H> ha, pw;
    HashInterval(string& str) : ha(sz(str)+1), pw(ha) {
        pw[0] = 1;
        rep(i,0,sz(str))
            ha[i+1] = ha[i] * C + str[i],
            pw[i+1] = pw[i] * C;
    }
    H hashInterval(int a, int b) { // hash [a, b)
        return ha[b] - ha[a] * pw[b - a];
    }
};

H hashString(string& s){H h{}; for(char c:s) h=h*C+c;return h;}

int main() {
    int t; cin >> t;
    while(t--) {
        string s;
        cin >> s;
        HashInterval stringHash(s);

        int n = sz(s);
        vector<int> primeiro(n+1);

        primeiro[n] = n;
        for(int i = n-1; i >= 0; i--) {
            if(s[i] != 'a')
                primeiro[i] = i;
            else
                primeiro[i] = primeiro[i+1];
        }

        if(primeiro[0] == n) {
            // special case
            printf("%d\n", n-1);
            continue;
        }

        long long ans = 0;
        for(int start = primeiro[0], sz = 1; start + sz <= n; sz++) {
            int menor = 0x3f3f3f3f;

            H hashPattern = stringHash.hashInterval(start, start + sz);

            for(int i = 0; primeiro[i] < n; i += sz) {
                menor = min(menor, primeiro[i] - i);

                i = primeiro[i];

                if(i+sz > n || !(hashPattern == stringHash.hashInterval(i, i + sz))) {
                    menor = -1;
                    break;
                }
            }

            ans += menor + 1;
        }

        printf("%lld\n", ans);
    }
}
