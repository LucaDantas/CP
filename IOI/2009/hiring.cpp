#include<bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int,int>;

#define ff first
#define ss second

constexpr int maxn = 5e5+10, logn = 20;

struct Fraction
{
	ll p, q, id;
	Fraction() {}
	Fraction(ll a, ll b) : p(a), q(b) {}
	Fraction(ll a, ll b, ll c) : p(a), q(b), id(c) {}
	bool operator<(Fraction b) { return p*b.q < q*b.p; }
	bool operator>(Fraction b) { return p*b.q > q*b.p; }
	ll operator*(ll a) {return (a * q) / p;}
	void upd(Fraction a) {
		if(Fraction(p, q) > a)
			p = a.p, q = a.q;
	}
	bool operator==(Fraction a) {
		return p*a.q==q*a.p;
	}
} val[maxn], soma;

struct BIT
{
	ll bit[maxn];
	void upd(int x, int v) {
		for(; x < maxn; x += x&-x)
			bit[x] += v;
	}
	ll query(int x) {
		ll ans = 0;
		for(; x > 0; x -= x&-x)
			ans += bit[x];
		return ans;
	}
	int bs(ll val, ll& come) {
		int pos = 0;
		for(int l = logn; l >= 0; l--) {
			if(pos + (1 << l) >= maxn) continue;
			if(bit[pos + (1 << l)] <= val)
				pos += (1 << l), val -= bit[pos], come += bit[pos];
		}
		return pos;
	}
	void clear() {
		for(int i = 0; i < maxn; i++)
			bit[i] = 0;
	}
} bit, ligados;

int pos[maxn], state[maxn], back[maxn];
pii opa[maxn];

int main() {
	int n; ll w; scanf("%d %lld", &n, &w);
	for(int i = 0, a, b; i < n; i++)
		scanf("%d %d", &a, &b), val[i] = Fraction(a, b, i), opa[i] = {b, i};
	sort(opa, opa+n);
	for(int i = 0; i < n; i++)
		pos[opa[i].ss] = i+1, back[i+1] = opa[i].ss;
	sort(val, val+n);

	ll ans = 0;
	for(int i = 0; i < n; i++) {
		bit.upd(pos[val[i].id], val[i].q);
		ligados.upd(pos[val[i].id], 1);

		ll pay = (val[i] * w), come = 0;
		
		int p = bit.bs(pay, come);
		int here = ligados.query(p);

		if(here == ans)
			soma.upd(Fraction(1ll*come*val[i].p, val[i].q));
		if(here > ans) {
			ans = here;
			soma = Fraction(1ll*come*val[i].p,val[i].q);
		}	
	}

	bit.clear();
	ligados.clear();

	for(int i = 0; i < n; i++) {
		bit.upd(pos[val[i].id], val[i].q);
		ligados.upd(pos[val[i].id], 1);
		state[pos[val[i].id]] = 1;

		ll pay = val[i] * w, come = 0;
		
		int p = bit.bs(pay, come);
		int here = ligados.query(p);
		
		if(here == ans && (Fraction(1ll*come*val[i].p,val[i].q)) == soma) {
			printf("%lld\n", ans);
			for(int j = 1; j <= p; j++)
				if(state[j])
					printf("%d\n", back[j]+1);
			return 0;
		}
	}
}