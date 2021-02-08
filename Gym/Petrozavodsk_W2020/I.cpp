#include<cstdio>
#include<string>
#include<vector>
#include<algorithm>
#include<cassert>
#include<iostream>
using namespace std;

#define sz(a) (int)(a.size())
 
bool isSmaller(string str1, string str2)
{
    int n1 = sz(str1), n2 = sz(str2);
 
    if (n1 < n2) return true;
    if (n2 < n1) return false;
 
    for (int i = 0; i < n1; i++)
    {
        if (str1[i] < str2[i]) return true;
        else if (str1[i] > str2[i]) return false;
    }
 
    return false;
}
 
string sub(string str1, string str2)
{
    if (isSmaller(str1, str2)) swap(str1, str2);
 
    string str = "";
 
    int n1 = sz(str1), n2 = sz(str2);
 
    reverse(str1.begin(), str1.end());
    reverse(str2.begin(), str2.end());
 
    int carry = 0;
 
    for (int i = 0; i < n2; i++)
    {
        int sub = ((str1[i] - '0') - (str2[i] - '0') - carry);
 
        if (sub < 0)
        {
            sub = sub + 10;
            carry = 1;
        }
        else carry = 0;
 
        str.push_back((char)(sub + '0'));
    }
 
    for (int i = n2; i < n1; i++)
    {
        int sub = ((str1[i] - '0') - carry);
 
        if (sub < 0)
        {
            sub = sub + 10;
            carry = 1;
        }
		else carry = 0;
 
        str.push_back((char)(sub + '0'));
    }
 
    reverse(str.begin(), str.end());
 
    return str;
}
 
bool isbad(string s)
{
	for (int i = 1; i < sz(s); i++)
		if (s[i] != '0')
			return 0;
 
	return 1;
}

int main() {
	int t; scanf("%d", &t);
	while(t--) {
		string s;
		cin >> s;

		vector<string> all;
 
		while (true)
		{
			int n = sz(s);
 
			string ans;
 
			if (n == 1)
			{
				ans = s;
				all.push_back(s);
				break;
			}
 
			if (isbad(s))
			{
				int x = (int)(s[0] - '0');
 
				for (int i = 1; i < n; i++)
					ans.push_back((char)((x == 1 ? 9 : 11-x) + (int) '0'));
 
				all.push_back(ans);
				string outra = sub(s, ans);
 
				reverse(outra.begin(), outra.end());
 
				while (outra.size() && outra.back() == '0')
					outra.pop_back();
 
				reverse(outra.begin(), outra.end());
 
				if (outra.size()) all.push_back(outra);
				break;
			}

			for (int i = 0; i < (n+1)/2; i++)
				ans.push_back(s[i]);

			for (int i = n/2-1; i >= 0; i--)
				ans.push_back(s[i]);

			int dif = -1;
			for(int i = (n+1)/2; i < n; i++)
				if(ans[i] != s[i])
					{dif = i-n/2; break;}

			int pos = -1;
			for(int i = n/2; i < n; i++)
				if(ans[i] > '0')
					{pos = i-n/2; break;}
			assert(pos != -1);

			if (dif != -1 && ans[n/2+dif] > s[n/2+dif])
			{
				if(pos != dif) {
					ans[n/2+pos] = (char)(ans[n/2+pos]-1);
					ans[(n-1)/2-pos] = ans[n/2+pos];
				}
				else {
					ans[n/2+dif] = s[n/2+dif];
					ans[(n-1)/2-dif] = ans[n/2+dif];
				}
			}

			all.push_back(ans);

			s = sub(s, ans);
 
			reverse(s.begin(), s.end());
 
			while (s.size() && s.back() == '0')
				s.pop_back();
 
			if (s.size() == 0) break;
 
			reverse(s.begin(), s.end());
		}
 
		printf("%ld\n", all.size());
		for (string ss : all)
			printf("%s\n", ss.data());
	}
}