//solve recurrence
//S(1) = 12, S(2) = 54
//S(n+2) = 5S(n+1) - 2S(n)
#include <bits/stdc++.h>
using namespace std;

const int module = 1e9 + 7;
typedef long long ll;

int logreal(long long v){
        int i = 0;
        while(v >>= 1){
            i++;
        }
        return i;
}

int main(){
        long long target;
        cin >> target;
        if(target == 1){
                cout << 12 << '\n';
                return 0;
        }
        if(target == 2){
                cout << 54 << '\n';
                return 0;
        }
        target--;
        int max_pot = logreal(target);
        vector<pair<pair<ll,ll>,pair<ll,ll>>> coeficients;
        pair<ll,ll> n2(5,-2);
        pair<ll,ll> n3(23,-10);
        pair<pair<ll,ll>, pair<ll,ll>> two(n2,n3);
        coeficients.push_back(two);
        for(int i = 2; i <= max_pot; i++){
                pair<ll,ll> previous_even = coeficients.at(i-2).first;
                pair<ll,ll> previous_odd = coeficients.at(i-2).second;
                ll a = previous_even.first, b = previous_even.second;
                ll c = previous_odd.first, d = previous_odd.second;
                pair<ll,ll> current_even(((a*c)%module + (a*b)%module) % module, ((a*d)%module + (b*b)%module) % module);
                pair<ll,ll> current_odd(((c*c)%module + (a*d)%module) % module, ((c*d)%module + (d*b)%module) % module);
                pair<pair<ll,ll>, pair<ll,ll>> add_(current_even, current_odd);
                coeficients.push_back(add_);
        }
        pair<pair<ll,ll>, pair<ll,ll>> now_ = coeficients.back();
        target -= (ll)pow(2LL,max_pot);
        while(target >= 2){
                max_pot = logreal(target);
                pair<pair<ll,ll>,pair<ll,ll>> old = coeficients.at(max_pot - 1);
                ll a = old.first.first, b = old.first.second;
                ll c = old.second.first, d = old.second.second;
                ll e = now_.first.first, f = now_.first.second;
                ll g = now_.second.first, h = now_.second.second;
                now_.first.first = ((a*g)%module + (b*e)%module) % module;
                now_.first.second = ((a*h)%module + (b*f)%module) % module;
                now_.second.first = ((c*g)%module + (d*e)%module) % module;
                now_.second.second = ((c*h)%module + (d*f)%module) % module;
                target -= (ll)pow(2LL,max_pot);
        }
        ll answer;
        if(target == 0){
            answer = (now_.first.first*54 + now_.first.second*12) % module;
        }
        else{
            answer = (now_.second.first*54 + now_.second.second*12) % module;
        }
        if(answer < 0) answer += module;
        cout << answer << endl;
        return 0;
}
