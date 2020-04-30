/*
ID: luca1001
TASK: ride
LANG: C++                 
*/
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int MOD = 47;

int main(){
	ofstream fout("ride.out");
	ifstream fin ("ride.in");
	string a, b;
	fin >> a >> b;
	ll ma=1, mb=1;
	for(int i = 0; i < (int)a.size(); i++)
		ma *= (a[i] - 'A' + 1);
	for(int i = 0; i < (int)b.size(); i++)
		mb *= (b[i] - 'A' + 1);
	if(ma%MOD == mb%MOD) fout << "GO\n";
	else fout << "STAY\n";	
	return 0;
}
