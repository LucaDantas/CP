#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

#define pb emplace_back
#define ff first
#define ss second
#define sz(a) ((int)(a).size())
#define rep(i,a,b) for(int i=(a); i<(b); i++)
#define dec(i,n,a) for(int i=(n); i>=(a); i--)
#define clr(a,v) memset(a, v, sizeof(a))
#define all(a) (a).begin(),(a).end()

int main() {
	int t; scanf("%d", &t);
	while(t--) {
		int n; scanf("%d", &n);

		int gut = -1;

		for(int i = 2; i*i <= n; i++) {
			if(n%i == 0) {
				gut = i;
				break;
			}
		}

		if(gut == -1)
			printf("1 %d\n", n-1);
		else
			printf("%d %d\n", n / gut, (n / gut) * (gut-1));
	}
}
