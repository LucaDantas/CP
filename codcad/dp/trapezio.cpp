#include<bits/stdc++.h>
using namespace std;

#define MAXN 100100
#define pii pair<int, int>

//Vetores de peso e força
int p[MAXN], f[MAXN];
//Vetor de pares que guarda em .first o número correspondente aquele 
// determinado trapezista, pra quando ordenar o vetor ainda saber a qual corresponde
// em .second fica o peso mais a força desse trapezista
pii a[MAXN];

//Função de ordenação, de modo que ordena primeiramente pelo que tiver maior peso + força
// e se for igual ordena pelo menor lexicograficamente
bool ord(pii a, pii b){
    if(a.second > b.second) return a > b;
    if(b.second > a.second) return b > a;
    if(a.first < b.first) return a > b;
    return b > a;
}

int main(){
    int n;
    cin >> n;
    //Lê os pares e salva no vetor
    for(int i = 1; i <= n; i++){
        cin >> p[i] >> f[i];
        a[i] = make_pair(i, p[i]+f[i]);
    }
    //Ordena
    sort(a+1, a+1+n, ord);
    //Salva como a resistência no inicio a força do primeiro a ser colocado
    int res = f[a[1].first];
    bool broke = false;
    for(int i = 2; i <= n; i++){
        //Atualiza a resistência como sendo o mínimo entre (resistência atual-peso do cara que vai colocar, resistência do cara que vai colocar)
        res = min(res - p[a[i].first], f[a[i].first]);
        //Se a resistência der menos que zero é porque alguém não aguenta então não dá pra fazer
        if(res < 0){
            cout << "IMPOSSIVEL" << endl;
            broke = true;
            break;
        } 
    }
    //Se não parou é porque dá pra fazer então imprime a ordem dos números corresponentes a cada pessoa ordenadas
    if(!broke){
        for(int i = 1; i <= n; i++){
            cout << a[i].first << endl;
        }
    }
}