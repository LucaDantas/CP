#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

#ifdef MY_DEBUG_FLAG
template<typename T> void debug(T a) { cerr << a << ' '; }
template<typename T, typename U> void debug(pair<T, U> a) { cerr << a.first << ' ' << a.second << ' '; }
template<typename T> void debug(vector<T> a) { for(auto it : a) debug(it);}
template<typename T> void debug(set<T> a) { for(auto it : a) debug(it);}
#define db(a) cerr << "DEBUG ( " << #a << " == "; debug(a); cerr << ")\n"
#else
#define db(...)
#endif

#define pb push_back
#define eb emplace_back
#define ff first
#define ss second
#define fast ios_base::sync_with_stdio(false), cout.tie(nullptr), cin.tie(nullptr)
#define sz(a) ((int)(a).size())
#define rep(i,a,b) for(int i=(a); i<(b); i++)
#define dec(i,n,a) for(int i=(n); i>=(a); i--)
#define clr(a,v) memset(a, v, sizeof(a))
#define all(a) (a).begin(),(a).end()

constexpr int inf = 0x3f3f3f3f;
constexpr int MAXN = 1e5 + 10;
constexpr int mod = 1000000007;

// We have two situations, either the answer we'll get is by multiplying k+1
// times the base we have or the answer is this but in some iterations we add an
// extra value to the other part of the answer (that is when the value 'cycles')
// and we want to set a var to know when this happens because if it does the value
// in the dozens can't be greater than 8.

// What we want to find is a initial value for the unities such that the value
// without it (let's call it rem_v) -> rem_v === 0 mod k+1, which means that we
// we can complete the value that's left only with the dozens on.

// To find this we can do a bf on every possible ending digit and find if it is
// a valid solution (it has a remainder mod k+1 == 0)

pii pa(int k, int b) {
	int sum = 0, cycles = 0, extra = 0;
	rep(i,0,k+1) {
		if(b > 9) {
			cycles = 1;
			b = 0;
		}
		if(cycles) extra++;
		sum += b;
		b++;
	}
	return {sum + extra, cycles};
}

int main() {
	int t; scanf("%d", &t);
	while(t--) {
		int n, k;
		scanf("%d %d", &n, &k);

		if(k == 0) {
			string ans = "";
			while(n) {
				int coloca = min(9, n);
				ans += to_string(coloca);
				n -= coloca;
			}
			reverse(all(ans));
			cout << ans << "\n";
			continue;
		}

		vector<string> resp;
		
		rep(i,0,10) {
			pii now = pa(k, i);
			int soma = now.ff;
			int cycles = now.ss;

			if((n >= soma) && (n - soma)%(k+1) == 0) {
				string ans = "";

				if(cycles) ans += to_string(i);
				else ans += to_string(i);

				int dif = (n - soma)/(k+1);

				if(cycles && dif) {
					int coloca = min(8, dif);
					ans += to_string(coloca);
					dif -= coloca;
				}

				while(dif) {
					int coloca = min(9, dif);
					ans += to_string(coloca);
					dif -= coloca;
				}

				reverse(all(ans));

				resp.pb(ans);
			}
		}
		if(!sz(resp)) puts("-1");
		else {
			string final = resp[0];
			rep(i,1,sz(resp)) {
				if(resp[i].size() < final.size()) final = resp[i];
				else if(resp[i].size() == final.size() && resp[i] < final) final = resp[i];
			}
			cout << final << '\n';
		}
	}
}
