#include<bits/stdc++.h>
using namespace std;

multiset<int> arr;

int pen(int pos){

}

int dist(int a, int b){
    return sqrt(a*a + b*b);
}

int main(){
    int n, x, y, penalties;
    cin >> n;
    for(int i = 0; i < n; i++){
        cin >> x >> y;
        penalties += pen( dist(x,y) );
    }
}

//I guess the way to do it is to create a multiset that stores the values in order as we add them and for each time that we add another one it computes how many 
//penalties are there by getting the number of values that goes behind it, which I would compute by getting the index of the upper bound and removing one from it.
//Then we would insert the specific value in the multiset and do the same process with the next one until it's over. But the problem is if it is the larget than
//every single element in the multiset, which would return the end element for upper bound, which would actually be alright if I could to operations with the
//iterators, such as removing one from it or removing the first number, which would then give me the number of penalties for that specific shot, but I'll try to
//work it out later cause now I'm a bit tired.