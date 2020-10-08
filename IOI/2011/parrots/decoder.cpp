#include "decoder.h"
#include "decoderlib.h"
#include<cstdio>
#include<cstring>
#include<algorithm>
 
int cnt[300];

inline int abs(int x) {return x<0?-x:x;} 
 
void decode(int N, int L, int X[])
{
	memset(cnt, 0, sizeof cnt);
	for(int i = 0; i < L; i++)
		cnt[X[i]]++;
	int ok = 0;
	if(cnt[0] >= 4) ok = 3, cnt[0] -= 4;
	for(int i = 0; i < N; i++) {
		int here = 0;
		for(int j = 0; j < 4; j++) {
			here += (abs(ok-cnt[4*i+j])) << (2*j);
		}
		output(here);
	}
}