#include<bits/stdc++.h>
using namespace std;

int main() {
	int a, b; scanf("%d %d", &a, &b);
	if(a <= b) return puts("Impossible"), 0;
	stack<int> st;
	int n = a+b;
	for(int i = 0; i < n; i++) {
		if(st.empty()) st.push(i);
		else {
			printf("? %d %d\n", st.top(), i);
			fflush(stdout);
			char c; scanf(" %c", &c);
			if(c == 'Y') st.push(i);
			else st.pop();
		}
	}
	int opa = st.top();
	string ans = "";
	for(int i = 0; i < n; i++) {
		if(i == opa) ans.push_back('1');
		else {
			printf("? %d %d\n", opa, i);
			fflush(stdout);
			char c; scanf(" %c", &c);
			c = c=='Y'?'1':'0';
			ans.push_back(c);
		}
	}
	printf("! %s\n", ans.data());
}