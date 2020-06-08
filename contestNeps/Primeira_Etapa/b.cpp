#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
#define ll long long

string sum(string a, string b){
	//if(a > b) swap(a,b);
	//reverse(a.begin(), a.end());
	//reverse(b.begin(), b.end());
	string ans = "";
	int carry = 0;
	for(int i = 0; i < (int)a.size(); i++){
		ans.push_back(((a[i]-'0')+(b[i]-'0')+carry)%10 + '0');
		carry = ((a[i]-'0')+(b[i]-'0')+carry)/10;
	}
	for(int i = (int)a.size(); i < (int)b.size(); i++){
		ans.push_back((b[i]-'0'+carry)%10 + '0');
		carry = (b[i]-'0'+carry)/10;
	}
	if(carry!=0)
		ans.push_back(carry + '0');
	//reverse(ans.begin(), ans.end());
	return ans;
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	string a, b;
	cin >> a >> b;
	cout << sum(a,b) << endl;
}
