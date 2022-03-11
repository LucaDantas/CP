#include <bits/stdc++.h>
using namespace std;

using ld = long double;

#define int long long

constexpr int maxt = 1e3+10;

ld f[maxt], choose[maxt];
ld suf[maxt], pref[maxt];

void pre(int T) {
	f[0] = 1;
	for(int i = 1; i <= T; i++)
		f[i] = f[i-1] * i;

	for(int i = 0; i <= T; i++)
		choose[i] = f[T] / (f[T-i] * f[i]);

	ld pot = pow(2, T);
	suf[T] = (ld) T * choose[T] / pot;
	for(int i = T-1; i >= 0; i--)
		suf[i] = (ld) i * choose[i] / pot + suf[i+1];
	
	pref[0] = choose[0] / pot;
	for(int i = 1; i <= T; i++)
		pref[i] = choose[i] / pot + pref[i-1];
}

int32_t main() {
	int T, K; scanf("%lld %lld", &T, &K); --T;
	pre(T);

	int l = 2, r = K, last = 1;
	int prox = ceil((ld) T / 2);
	ld x = suf[prox], y = pref[prox-1];
	ld last_dp = (ld) T / 2;
	int ans = 0;

	while(1) {

		{
			int m = K;
			int sz = m - last;
			ld new_y = pow(2, sz*log2(y)), new_x = x * (pow(2, sz*log2(y)) - 1) / (y-1);
			if(ceil(last_dp*new_y + new_x) == prox) {
				cout << setprecision(6) << fixed << (1 + last_dp * new_y + new_x) << endl;
				return 0;
			}
		}

		while(l <= r) {
			int m = (l+r) >> 1;
			int sz = m - last;
			ld new_y = pow(2, sz*log2(y)), new_x = x * (pow(2, sz*log2(y)) - 1) / (y-1);
			if(ceil(last_dp*new_y + new_x) != prox)
				ans = m, r = m-1;
			else l = m+1;
		}

		int m = ans;
		int sz = m - last;
		ld new_y = pow(y, sz), new_x = x * (pow(y, sz) - 1) / (y-1);

		last_dp = last_dp * new_y + new_x; // dando update na dp
		l = m+1, r = K;
		last = m;
		prox = ceil(last_dp);
		x = suf[prox], y = pref[prox-1];

		ans = 0;
	}
}
