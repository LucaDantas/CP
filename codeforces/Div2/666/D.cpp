#include<bits/stdc++.h>
using namespace std;

int main() {
        int t; scanf("%d", &t);
	while(t--) {
	int n; scanf("%d", &n);
        vector<int> a(n);
        int s = 0, maior = 0;
        for(int i = 0; i < n; i++) {
                scanf("%d", &a[i]);
                s += a[i];
		maior = max(maior, a[i]);
        }
	if(maior > s/2) {
		puts("T");
	} else {
		if(s&1) {
			puts("T");
		} else {
			puts("HL");
		}
	}
	}
}

