#include<bits/stdc++.h>
using namespace std;

int solve(int a, int b){
	if(a+b == 0) return 0;
	if(a + b == 2) return 1;
	if(a == 1) return 1;
	return 2;
}

int main(){
	int a, b, c, d;
	scanf("%d%d%d%d", &a, &b, &c, &d);
	if(a==1) c ^= 1;
	if(b==1) d ^= 1;
	printf("%d\n", solve(c, d)); 
}
