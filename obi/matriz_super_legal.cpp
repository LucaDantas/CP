#include<iostream>
#include<stack>

using namespace std;

int n, m, matr[1010][1010], zo[1010][1010], vec[1010];

void makezo(){
    for(int i = 1; i < n; i++){
        for(int j = 1; j < m; j++){
            if(matr[i][j] + matr[i-1][j-1] <= matr[i-1][j] + matr[i][j-1]) zo[i][j] = 1;
        }
    }
}

int lg_rec_hist(){
    stack<int> pos;
    stack<int> last;
    int ans = 0;
    pos.push(0);
    for(int i = 0; i < m; i++){
        if(vec[i] > last.top()){pos.push(i); last.push(vec[i]);}
        else{
            while(vec[i] < last.top()){
                ans = max(ans, (last.top()+1)*(i-pos.top()+1));
                last.pop();
                pos.pop();
            }
        }
    }
    return ans;
}

int main(){
    cin >> n >> m;
    int ans = 0;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            cin >> matr[i][j];
        }
    }
    makezo();
    for(int i = 1; i < n; i++){
        for(int j = 1; j < m; j++){
            if(matr[i][j] == 0) vec[j] = 0;
            else vec[j]++;
        }
        ans = max(ans, lg_rec_hist() );
    }
    return ans;
}
