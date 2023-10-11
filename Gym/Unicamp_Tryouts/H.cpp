#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

typedef uint64_t ull;
struct H {
	ull x; H(ull x=0) : x(x) {}
	H operator+(H o) { return x + o.x + (x + o.x < x); }
	H operator-(H o) { return *this + ~o.x; }
	H operator*(H o) { auto m = (__uint128_t)x * o.x;
		return H((ull)m) + (ull)(m >> 64); }
	ull get() const { return x + !~x; }
	bool operator==(H o) const { return get() == o.get(); }
	bool operator<(H o) const { return get() < o.get(); }
};
static const H C = (ll)1e11+3; // (order ~ 3e9; random also ok)

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

vector<H> getHashes(string& str, int length) {
	if (sz(str) < length) return {};
	H h = 0, pw = 1;
	rep(i,0,length)
		h = h * C + str[i], pw = pw * C;
	vector<H> ret = {h};
	rep(i,length,sz(str)) {
		ret.push_back(h = h * C + str[i] - pw * str[i-length]);
	}
	return ret;
}

int main() {
    string a, b; cin >> a >> b;
    int l = 1, r = sz(a), ans = -1;
    while(l <= r) {
        int m = (l+r)>>1;
        vector<H> p1 = getHashes(a, m), p2 = getHashes(b, m);
        sort(all(p1)), sort(all(p2));
        p1.erase(unique(all(p1)), p1.end());
        p2.erase(unique(all(p2)), p2.end());
        auto check = [&]() -> bool {
            for(int i = 0, ptr = 0; i < sz(p1); i++) {
                for(; ptr < sz(p2) && p2[ptr] < p1[i]; ptr++);
                if(ptr == sz(p2) || !(p1[i] == p2[ptr]))
                    return 1;
            }
            return 0;
        };
        if(check())
            ans = m, r = m-1;
        else
            l = m+1;
    }
    printf("%d\n", ans);
}
