#include "Alicelib.h"
#include <cassert>
#include <cstdio>

constexpr int maxn = 1510;

int C[maxn*maxn], D[maxn*maxn];

bool on(int a, int b) {return a&(1<<b);}

void Alice( int N, int M, int A[], int B[] ){
	for(int i = 0; i < M; i++)
		C[i] = A[i], D[i] = B[i];
	for(int i = 0; i < N; i++, M++)
		C[M] = N, D[M] = i;
	
	for(int i = 0; i < N; i++)
		for(int j = 0; j < 10; j++)
			if(on(i+1, j)) C[M] = N+1+j, D[M++] = i;
	
	for(int j = 0; j < 9; j++)
		C[M] = N+1+j, D[M++] = N+1+j+1;
	C[M] = N+11, D[M++] = N;

	InitG(N+12, M);
	for(int i = 0; i < M; i++)
		MakeG(i, C[i], D[i]);
}
