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
constexpr int MAXN = 310;
constexpr int mod = 1000000007;

double p[MAXN][MAXN][MAXN], EV[MAXN][MAXN][MAXN];

int main() {
	int n; scanf("%d", &n);
	vi cnt(4);
	rep(i,0,n) {
		int t;
		scanf("%d", &t);
		cnt[t]++;
	}
	p[cnt[1]][cnt[2]][cnt[3]] = 1;

	for(int c = n ; c >= 0; c--) {
		for(int b = n; b >= 0; b--) {
			for(int a = n; a >= 0; a--) {
				if(a+b+c > n || !(a+b+c)) continue;
				double p_waste = (double) (n - a - b - c) / n;
				// pw + pw² + pw³ + ...
				double ev_waste = p_waste / (1 - p_waste);
				EV[a][b][c] += (ev_waste+1)*p[a][b][c];
				if(c) {
					double p_go = (double) c / (a+b+c);
					p[a][b+1][c-1] += p[a][b][c]*p_go;
					EV[a][b+1][c-1] += (EV[a][b][c])*p_go;
				}
				if(b) {
					double p_go = (double) b / (a+b+c);
					p[a+1][b-1][c] += p[a][b][c]*p_go;
					EV[a+1][b-1][c] += (EV[a][b][c])*p_go;
				}
				if(a) {
					double p_go = (double) a / (a+b+c);
					p[a-1][b][c] += p[a][b][c]*p_go;
					EV[a-1][b][c] += (EV[a][b][c])*p_go;
				}
			}
		}
	}
	printf("%.10lf\n", EV[0][0][0]);
}
