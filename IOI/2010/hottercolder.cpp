#include "grader.h"
#include<cassert>
#include<cstdio>

int guess(int a, int b) {
	Guess(a);
	return Guess(b);
}

int HC(int n){
	int l = 1, r = n;
	while(r - l > 7) {
		int ans = guess(l, r);
		if(!ans) return (l+r) >> 1;
		if(ans == 1) l = (l+r+1) >> 1;
		else r = (l+r-1) >> 1;
	}

	if(r == l) return l;
	if(r-l == 1)
		return guess(l, r)==1?r:l;
	if(r - l == 2) {
		int ans = guess(l, r);
		return ans==1?r:ans==0?l+1:l;
	}
	if(r - l == 3) {
		int ans = guess(l, r-1);
		if(ans == 0) return l+1;
		if(ans == -1) return l;
		if(Guess(r) == 1) return r;
		return r-1;
	}
	// Resolve um intervalo de 5 com 3 movimentos
	if(r - l == 4) {
		int ans = guess(l, l+2);
		if(ans == -1) return l;
		if(ans == 0) return l+1;
		ans = Guess(r);
		return ans==-1?l+2:ans==0?l+3:r;
	}
	// 4 mov
	if(r - l == 5) {
		int ans = guess(l, l+2);
		if(ans == -1) return l;
		if(ans == 0) return l+1;
		l = l+2;
		ans = Guess(l+2);
		if(ans == -1) return l;
		if(ans == 0) return l+1;
		l = l+2;
		ans = Guess(l+1);
		return ans==1?l+1:l;
	}
	// 4 mov
	if(r - l == 6) {
		int ans = guess(l, l+2);
		if(ans == -1) return l;
		if(ans == 0) return l+1;
		l = l+2;
		ans = Guess(l+2);
		if(ans == -1) return l;
		if(ans == 0) return l+1;
		l = l+2;
		ans = Guess(l+2);
		if(ans == -1) return l;
		if(ans == 0) return l+1;
		return l+2; // l+2 == r
	}
	// Resolve um intervalo de 8 com 4 movimentos
	if(r - l == 7) {
		int ans = guess(l+2, l+4);
		if(ans == 1) {
			l+=4;
			ans = Guess(r-1);
			if(ans == 0) return l+1;
			if(ans == -1) return l;
			if(Guess(r) == 1) return r;
			return r-1;
		}
		if(!ans) return l+3;
		ans = guess(l, l+2);
		if(ans == 1) return l+2;
		if(ans == -1) return l;
		return l+1;
	}
	return 0;
}
