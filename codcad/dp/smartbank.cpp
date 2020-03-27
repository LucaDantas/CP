#include<bits/stdc++.h>
using namespace std;

#define MAXS 5100
#define MAXN 510

int v[7], w[] = {0, 2, 5, 10, 20, 50, 100};
int dp[MAXS][7][MAXN];
//The dp will have the dimensions dp[Value rn][last note used][how many notes of that specific one left] and inside it there will be 
// the number of ways to get to that spot and we'll only be able to add notes that come after the last one used and if there is still some left

int main(){
    int s, maxn = 0;
    cin >> s;
    //First we read the number we have of each note
    for(int i = 1; i <= 6; i++){
        cin >> v[i];
        maxn = max(maxn, v[i]);
    }
    //We fill the dp matrix
    for(int i = 1; i <= s; i++){
        for(int j = 1; j <= 6; j++){
            for(int k = 0; k <= maxn; k++){
                dp[i][j][k] = 0;
            }
        }
    }
    //We start the dp matrix with the base cases, which are starting with each one of the possible notes
    for(int i = 1; i <= 6; i++){
        //If there are no notes we just skip and don't start with that note
        if(v[i] == 0) continue;
        dp[w[i]][i][v[i]-1] = 1;
    }
    for(int i = 1; i <= s; i++){
        for(int j = 1; j <= 6; j++){
            if(dp[i][j][0] != 0){
                //Initially we use create the case if there are no more notes left (k == 0) and we have to use a different kind of note
                for(int l = j+1; l <= 6; l++){
                    //If there are no notes of that kind or if the current value plus the value of that note surpass what we want we just skip it
                    if(v[l] == 0) continue;
                    if(i+w[l] > s) break;
                    //We add to the dp[actual value + value of the note we're adding][note we're adding][number of notes left of that kind - 1 (Thw one we've used)] the ways we can get to that specific place we're now
                    dp[i+w[l]][l][v[l]-1] += dp[i][j][0];
                }
            }
            for(int k = 1; k <= maxn; k++){
                if(dp[i][j][k] == 0) continue;
                //We can choose from two paths now, either add one note of the same kind or add another kind of note
                //First path - Add one of the same note (We have to make sure that it does not surpass the value that we want)
                if(i+w[j] <= s){
                    dp[i+w[j]][j][k-1] += dp[i][j][k];
                }
                //Second path - it'll be basically the same code as we used for the case when k = 0
                for(int l = j+1; l <= 6; l++){
                    //If there are no notes of that kind or if the current value plus the value of that note surpass what we want we just skip it
                    if(v[l] == 0) continue;
                    if(i+w[l] > s) break;
                    //We add to the dp[actual value + value of the note we're adding][note we're adding][number of notes left of that kind - 1 (Thw one we've used)] the ways we can get to that specific place we're now
                    dp[i+w[l]][l][v[l]-1] += dp[i][j][k];
                }
            }
        }
    }
    long long ans = 0;
    for(int j = 1; j <= 6; j++){
        for(int k = 0; k <= maxn; k++){
            ans += dp[s][j][k];
        }
    }
    cout << ans << endl;
}