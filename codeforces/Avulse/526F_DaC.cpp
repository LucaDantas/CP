/*
	Here's a brief description of the solution because the code
	is not so easy to understand

	We divide the merge process in 4 cases
	
	1-2: Both maximum and minimum are on the same side and
	we make sure that we are taking someone from the other
	side to compose the answer. (1 == l, 2 == r)
	
	Just maintain a pointer on the opposite site to know what
	is the last that ensures the property we want
	(Mx and Mn on the same side)

	3-4: Maximum and minimum values we want to take are
	on different intervals

	Now you'll have to mantain two pointers on the other side:
	the first one to know what's the first value smaller than
	my Min, and the other pointer is similar but for the Max

	If you want the Mx to be on the left interval, the interval
	on the other side that satisfies this property is [ptr_mn..ptr_mx-1]
	and it works similarly if you want the other way around
	Now you just creat some counting array to know how many
	values r+Mn or r-Mx on the other side match your value
	l+Mx or l-Mn

*/

#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;

constexpr int maxn = 3e5+10, inf = 0x3f3f3f3f;

int a[maxn], qtd[2*maxn];
long long ans;

void solve(int l, int r) {
	if(l == r) return (void)(++ans);
	int m = (l+r) >> 1;
	solve(l, m); solve(m+1, r);
	// Caso 1: Mx e Mn em [l..m]
	int Mn = inf, Mx = 0;
	for(int i = m, ptr = m+1; i >= l; i--) {
		bool trocou = 0;
		if(a[i] > Mx || a[i] < Mn) trocou = 1;
		Mx = max(Mx, a[i]);
		Mn = min(Mn, a[i]);
		for(; ptr <= r && a[ptr] < Mx && a[ptr] > Mn; ptr++);
		if(trocou && ptr > m+1)
			ans += ptr-i >= Mx - Mn + 1; // ptr já é dps do ultimo
		else if(ptr > m+1)
			ans += ptr-i == Mx-Mn+1;
	}

	// Caso 2: Mx e Mn em [m+1..r]
	Mn = inf, Mx = 0;
	for(int i = m+1, ptr = m; i <= r; i++) {
		bool trocou = 0;
		if(a[i] > Mx || a[i] < Mn) trocou = 1;
		Mx = max(Mx, a[i]);
		Mn = min(Mn, a[i]);
		for(; ptr >= l && a[ptr] < Mx && a[ptr] > Mn; ptr--);
		if(trocou && ptr < m)
			ans += i-ptr >= Mx - Mn + 1;
		else if(ptr < m)
			ans += i-ptr == Mx-Mn+1;
	}

	// Caso 3: Mx em [l..m] e Mn em [m+1..r]
	Mn = inf, Mx = 0;
	int MnR1 = inf, MnR2 = inf, ptr_mx = m+1, ptr_mn = m+1;
	for(int i = m; i >= l; i--) {
		Mx = max(Mx, a[i]);
		Mn = min(Mn, a[i]);
		for(; ptr_mn <= r && a[ptr_mn] > Mn; ptr_mn++)
			MnR1 = min(MnR1, a[ptr_mn]), qtd[MnR1 + ptr_mn]--;
		for(; ptr_mx <= r && a[ptr_mx] < Mx; ptr_mx++)
			MnR2 = min(MnR2, a[ptr_mx]), qtd[MnR2 + ptr_mx]++;
		ans += max(0, qtd[Mx + i]);
	}
	// Zerar as coisas
	for(; ptr_mn < ptr_mx; ptr_mn++)
		MnR1 = min(MnR1, a[ptr_mn]), qtd[MnR1 + ptr_mn]--;
	for(; ptr_mx < ptr_mn; ptr_mx++)
		MnR2 = min(MnR2, a[ptr_mx]), qtd[MnR2 + ptr_mx]++;

	// Caso 4: Mn em [l..m] e Mx em [m+1..r]
	Mn = inf, Mx = 0, ptr_mx = m+1, ptr_mn = m+1;
	int MxR1 = 0, MxR2 = 0;
	for(int i = m; i >= l; i--) {
		Mx = max(Mx, a[i]);
		Mn = min(Mn, a[i]);
		for(; ptr_mn <= r && a[ptr_mn] > Mn; ptr_mn++)
			MxR1 = max(MxR1, a[ptr_mn]), qtd[ptr_mn - MxR1 + maxn]++;
		for(; ptr_mx <= r && a[ptr_mx] < Mx; ptr_mx++)
			MxR2 = max(MxR2, a[ptr_mx]), qtd[ptr_mx - MxR2 + maxn]--;
		ans += max(0, qtd[i - Mn + maxn]);
	}
	// Zerar as coisas
	for(; ptr_mn < ptr_mx; ptr_mn++)
		MxR1 = max(MxR1, a[ptr_mn]), qtd[ptr_mn - MxR1 + maxn]++;
	for(; ptr_mx < ptr_mn; ptr_mx++)
		MxR2 = max(MxR2, a[ptr_mx]), qtd[ptr_mx - MxR2 + maxn]--;

}

int main() {
	int n; scanf("%d", &n);
	for(int i = 0, x, y; i < n; i++)
		scanf("%d %d", &x, &y), a[x] = y;
	solve(1, n);
	printf("%lld\n", ans);
}