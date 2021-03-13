#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int maxn = 1e5+10;
const ll inf = 1000000000ll;

int n;
int a[maxn];

bool ok(ll k)
{
	ll tenho = a[0] - 1, custo = 0, precisa = 0;
	if(k >= n) custo += (1ll << (k - n)) - 1, k = n;
	for(int i = k; i < n; i++)
		tenho += a[i];

	for(int i = k-1; i >= 1; i--) {
		if(custo > 1000001000ll * 1000000ll) return 0;
		tenho += max(0ll, (a[i]-1) - custo);
		if(a[i])
			custo += max(0ll, custo - (a[i]-1));
		else custo <<= 1, custo |= 1;
	}
	return tenho >= custo;
}

int main(void)
{
	scanf("%d", &n);

	ll s = 0;

	for (int i = 0; i < n; i++)
	{
		scanf("%d", &a[i]);
		s += 1ll*a[i];
	}

	// ok(11);

	if (s == 1)
	{
		for (int i = 0; i < n; i++)
		{
			if (a[i] == 1)
			{
				printf("%d\n", max(1, i));
				return 0;
			}
		}
	}

	int ini = 1, fim = n + 30, ans = 1;

	while (ini <= fim)
	{
		int mid = (ini+fim)>>1;

		if (ok(mid)) ans = mid, ini = mid+1;
		else fim = mid-1;
	}

	printf("%d\n", ans);
}
