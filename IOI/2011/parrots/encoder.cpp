#include "encoder.h"
#include "encoderlib.h"
#include<cstdio>
#include<cstring>
 
int conta[300];
 
inline int abs(int x) {return x<0?-x:x;} 
 
void encode(int N, int M[])
{
	memset(conta, 0, sizeof conta);
	int tot = 0;
	for(int i = 0; i < N; i++) {
		for(int bit = 0; bit < 4; bit++) {
			int cnt = (M[i] >> (2*bit))&3;
			conta[4*i+bit] = cnt;
			tot += cnt;
		}
	}
	int ok = 0;
	if(tot > N * 6) ok = 3, send(0), send(0), send(0), send(0);
	for(int i = 0; i < 4*N; i++) {
		int qtd = abs(ok - conta[i]);
		while(qtd--) send(i);
	}
}