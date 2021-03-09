#include<cstdio>
#include<algorithm>

constexpr int maxn = 4010, inf = 0x3f3f3f3f;

int a[maxn][maxn], cost[maxn][maxn], cost_me[maxn][maxn], dp[maxn][2];

void solve(int l, int r, int l2, int r2) {
	if(l > r) return;
	int m = (l+r) >> 1;
	int opt = -1;
	for(int i = l2; i <= std::min(m, r2); i++) {
		if(cost[i][m] + dp[i-1][0] < dp[m][1]) {
			opt = i;
			dp[m][1] = cost[i][m] + dp[i-1][0];
		}
	}
	solve(l, m-1, l2, opt);
	solve(m+1, r, opt, r2);
}

void fastscan(int &number)
{
    //variable to indicate sign of input number
    bool negative = false;
    register int c;
 
    number = 0;
 
    // extract current character from buffer
    c = getchar();
    if (c=='-')
    {
        // number is negative
        negative = true;
 
        // extract the next character from the buffer
        c = getchar();
    }
 
    // Keep on extracting characters if they are integers
    // i.e ASCII Value lies from '0'(48) to '9' (57)
    for (; (c>47 && c<58); c=getchar())
        number = number *10 + c - 48;
 
    // if scanned input has a negative sign, negate the
    // value of the input number
    if (negative)
        number *= -1;
}

int main() {
	int n, k; fastscan(n), fastscan(k);
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= n; j++)
			fastscan(a[i][j]);
	for(int sz = 1; sz < n; sz++) {
		for(int l = 1; l+sz <= n; l++) {
			int r = l+sz;
			cost_me[l][r] = cost_me[l][r-1] + a[l][r];
			cost[l][r] = cost[l+1][r] + cost_me[l][r];
		}
	}
	for(int i = 1; i < maxn; i++)
		dp[i][0] = inf, dp[i][1] = inf;
	dp[0][1] = inf;
	for(int gld = 0; gld < k; gld++) {
		solve(1, n, 1, n);
		for(int i = 1; i <= n; i++)
			dp[i][0] = dp[i][1], dp[i][1] = inf;
	}
	printf("%d\n", dp[n][0]);
}