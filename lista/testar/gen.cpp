#include<bits/stdc++.h>
using namespace std;
#define endl '\n'

int rand(int a, int b){
	return a + rand() % (b - a + 1);
}

int main(int argc, char* argv[]){
	srand(atoi(argv[1]));
	int n = rand(1, 5);
	cout << n << endl;
	for(int i = 0; i < n; i++){
		cout << rand(-1000000, 1000000) << ' ' << rand(-1000000,1000000) << endl;
	}
}
