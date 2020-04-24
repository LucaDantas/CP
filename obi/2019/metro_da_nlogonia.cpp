#include<iostream>
#include<pair>
#include<unordered_map>
#include<vector>

using namespace std;

pair<int, vertex> maxp;
maxp.first = 0;

struct vertex{
    int name;
    vector<vertex> adj;
    bool seen = false;
    int value;
};

vector<vertex> vertices;

int path(vertex v){
    if(v.adj.size() == 1 && v.adj[0].seen == true){ vertices[v.name].seen = true; vertices[v.name].value = 1; return 1; }
    int max1 = 0, max2 = 0;
    for(vertex k : v.adj){
        if(vertices[k.name].seen) continue;
        tam = path(k);
        if(tam > max1) {max2 = max1; max1 = tam;}
        else if(tam > max2) max2 = tam;
    }
    if(max1 + max2 + 1 > maxp.first) {maxp.first = max1 + max2 + 1; maxp.second = v;}
    vertices[v.name].seen = true;
    vertices[v.name].value = max1 + 1;
    return max1 + 1;
}

int main(){
    int n, m;
    cin >> n >> m;
    vertices.resize(n+10);
    for(int i = 1; i < n; i++){
        int a, b;
        cin >> a >> b;
        vertices[a].adj.push_back(vertices[b]);
        vertices[b].adj.push_back(vertices[a]);
    }
    path(vertices[1]);
    //Já fiz o de achar o maior caminho com um vértice desse caminho, agora basta achar o vértice do meio desse caminho
}