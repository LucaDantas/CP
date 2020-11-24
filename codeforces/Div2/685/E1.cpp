#include<bits/stdc++.h>
using namespace std;

int XOR(int a, int b) {
	int ans;
	cout << "XOR " << a << ' ' << b << endl;
	cin >> ans;
	return ans;
}

int AND(int a, int b) {
	int ans;
	cout << "AND " << a << ' ' << b << endl;
	cin >> ans;
	return ans;
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(nullptr);
	int n; cin >> n;
	int v1, v2, v3, a1, a2, a3;
	v1 = XOR(1, 2);
	v2 = XOR(1, 3);
	v3 = v1^v2;
	a1 = AND(1, 2);
	a2 = AND(1, 3);
	a3 = AND(2, 3);
	int a = 0, b = 0, c = 0;
	for(int i = 0; (1 << i) <= n; i++) {
		if((v1&(1 << i)) || (v2&(1 << i)) || (v3&(1 << i))) {
			if(!(v1&(1 << i))) {
				if (a1&(1 << i))
					a |= 1 << i, b |= 1 << i;
				else c |= 1 << i;
			}
			if(!(v2&(1 << i))) {
				if (a2&(1 << i))
					a |= 1 << i, c |= 1 << i;
				else b |= 1 << i;
			}
			if(!(v3&(1 << i))) {
				if (a3&(1 << i))
					b |= 1 << i, c |= 1 << i;
				else a |= 1 << i;
			}
		}
		else if((a1&(1 << i)) || (a2&(1 << i)))
			a |= 1 << i, b |= 1 << i, c |= 1 << i;
	}
	vector<int> ans(n);
	ans[0] = a, ans[1] = b, ans[2] = c;
	for(int i = 4; i <= n; i++)
		ans[i-1] = a^XOR(1, i);
	printf("! ");
	for(int x : ans)
		printf("%d ", x);
	printf("\n");
}