#include<bits/stdc++.h>
using namespace std;
#define MAXN 100010

tree[MAXN];
int n;

void update(int ind, int num){
	while(ind <= n){
		tree[x] += num;
		ind += ind&-ind;
	}
}

int sum(int x){
	int s = 0;
	while(x!=0){
		s += tree[x];
		x-= x&-x;
	}
	return s;
}

int main(){
	cin >> n;
}
