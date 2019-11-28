#include<iostream>
using namespace std;

char img[1010][1010];

int cc, cj, n;
bool broke;

int main(){
   cin >> n;
   for(int i = 0; i < n; i++){
      for(int j = 0; j < n; j++){
         cin >> img[i][j];
      }
   }
   for(int i = 0; i < n; i++){
      cc = 0; cj = 0;
      for(int j = 0; j < n; j++){
         if(img[i][j] == '.'){
            if(cc == 1)cc++;
         }
         else{
            if(cc == 2) {broke = true; break;}
            else if(cc==0)cc++;
         }
         if(img[j][i] == '.'){
            if(cj == 1)cj++;
         }
         else{
            if(cj == 2) {broke = true; break;}
            else if(cj==0)cj++;
         }
      }
   }
