/*
ID: luca1001
TASK: test
LANG: C++                 
*/
#include <bits/stdc++.h>
using namespace std;

int main(){
	ofstream fout("test.out");
	ifstream fin ("test.in");
	int a, b;
	fin >> a >> b;
	fout << a+b << endl;
	return 0;
}
