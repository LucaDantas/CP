#include "xylophone.h"
#include<algorithm>
static int a[5001];

inline int abs(int x) {return x<0?-x:x;}

void solve(int n) {
	a[2] = query(1, 2);
	for(int i = 2; i < n; i++) {
		// eu tenho o indice do anterior e do agr e posso olhar no vetor o valor deles
		int eu_e_seg = query(i, i+1);
		int eu_ant_seg = query(i-1, i+1);
		int ja_tenho = a[i] - a[i-1];

		int sign = ja_tenho<0?1:-1;
		
		// significa que o cara seguinte tem Delta com sinal igual ao do anterior
		if(eu_ant_seg == eu_e_seg + abs(ja_tenho))
			sign *= -1;
		
		a[i+1] = a[i] + sign*eu_e_seg;
	}
	int menor = *std::min_element(a+1, a+1+n);
	int pos1, posn;
	for(int i = 1; i <= n; i++) {
		a[i] -= menor;
		if(a[i] == 0) pos1 = i;
		if(a[i] == n-1) posn = i;
	}
	bool inv = 0;
	if(pos1>posn) inv = 1;
	for(int i = 1; i <= n; i++)
		answer(i, inv?n-a[i]:a[i]+1);
}
