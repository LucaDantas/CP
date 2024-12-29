#include <bits/stdc++.h>
using namespace std;

class Solver {
public:
    void add(int value) {
        // adds a child to the current tree node and rollback node
        int current_node = timeStream.get_current_tree_node();
        int new_node = tree.add_node(current_node, value);
        
        timeStream.move_to(new_node);
    }

    void remove(int k) {
        // move the pointer up k steps on the tree
        int current_node = timeStream.get_current_tree_node();
        int new_node = tree.find_kth_parent(current_node, k);
        
        timeStream.move_to(new_node);
    }

    void rollback() {
        timeStream.rollback();
    }

    void query() {
        timeStream.note_query();
    }

    vector<int> solve() {
        // returns the answer to each query
        vector<int> queries = timeStream.return_queried_tree_nodes();
        vector<int> tree_values = tree.solve();
        vector<int> ans;
        for(int node : queries)
            ans.push_back(tree_values[node]);
        return ans;
    }

private:
    static const int maxn = 1e6+10, logn = 20;

    class Tree {
    public:
        Tree() : binary_lifting(1, array<int, logn>()), tree_nodes(1) {}

        int add_node(int u, int value) { // add new child to u with value value
            int new_id = (int) tree_nodes.size();

            tree_nodes.push_back(value);

            add_binary_parents(new_id, u);

            return new_id;
        }

        int find_kth_parent(int u, int k) {
            for(int l = logn-1; l >= 0; l--)
                if((1 << l) <= k)
                    u = binary_lifting[u][l], k -= (1 << l);
            return u;
        }

        vector<int> solve() {
            vector<vector<int>> g(tree_nodes.size());

            // monta o grafo
            for(int i = 1; i < (int)(tree_nodes.size()); i++)
                g[binary_lifting[i][0]].push_back(i);

            vector<int> ans(tree_nodes.size());
            set<int> active;

            function<void(int)> dfs = [&](int u) {
                bool useful = !active.count(tree_nodes[u]); // if it is the first time it appears it's good
                
                if(useful)
                    active.insert(tree_nodes[u]);

                ans[u] = (int) active.size() - 1;

                for(int v : g[u])
                    dfs(v);

                if(useful)
                    active.erase(tree_nodes[u]);
            };
            
            dfs(0);

            return ans;
        }

    private:
        vector<array<int, logn>> binary_lifting; // pra cada id salva todos os log pais dele

        vector<int> tree_nodes; // comeca nao vazio porque eu quero 1 indexar

        void add_binary_parents(int new_id, int parent) {
            // do the binary lifting for this node

            binary_lifting.push_back(array<int, logn>());
            binary_lifting[new_id][0] = parent;

            for(int l = 1; l < logn; l++)
                binary_lifting[new_id][l] = binary_lifting[binary_lifting[new_id][l-1]][l-1];
        }
    } tree;

    class TimeStream {
    public:
        TimeStream() : rollback_nodes(1, RollbackNode()), t(0), current_node(0), queries(0) {}
        void move_to(int tree_node) {
            int new_id = ++t;

            RollbackNode new_node(tree_node, current_node);

            rollback_nodes.push_back(new_node);

            current_node = new_id;
        }

        void rollback() {
            int to_node = rollback_nodes[current_node].parent;

            current_node = to_node;
        }

        void note_query() {
            queries.push_back(rollback_nodes[current_node].tree_node);
        }

        int get_current_tree_node() {
            return rollback_nodes[current_node].tree_node;
        }

        vector<int> return_queried_tree_nodes() {
            return queries;
        }

    private:
        struct RollbackNode {
            int tree_node; // index of the tree node that it lives in
            int parent; // parent in time for rollback

            RollbackNode() {}
            RollbackNode(int _tree_node, int _parent) : tree_node(_tree_node), parent(_parent) {}
        };

        vector<RollbackNode> rollback_nodes;

        int t, current_node; // counter of the current time

        vector<int> queries; // in which times the queries were made
    } timeStream;
} solver;

int main() {
    int q; scanf("%d", &q);
    while(q--) {
        char c; scanf(" %c", &c);
        switch(c) {
            case '+':
                int x; scanf("%d", &x);
                solver.add(x);
                break;
            case '-':
                int k; scanf("%d", &k);
                solver.remove(k);
                break;
            case '!':
                solver.rollback();
                break;
            case '?':
                solver.query();
        }
    }

    vector<int> ans = solver.solve();
    for(int x : ans)
        printf("%d\n", x);
}
