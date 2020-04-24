#include<bits/stdc++.h>
using namespace std;

char num(int a){
	if(a <= 67) return '2';
	if(a <= 70) return '3';
	if(a <= 73) return '4';
	if(a <= 76) return '5';
	if(a <= 79) return '6';
	if(a <= 83) return '7';
	if(a <= 86) return '8';
	return '9';
}

int main(){
	string s, ans;
	cin >> s;
	for(int i = 0; i < (int)s.size(); i++){
		int val = (int)s[i];
		if(val >= 65 && val <= 90) s[i] = num(val);
	}
	cout << s << '\n';
}

//ASCII CODES
//FROM 0 to 9 is 48 to 57
//FROM A to Z is 65 to 90
//- is 45
