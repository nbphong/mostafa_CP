/*************************************************************************
 *                                                                       *
 *                    XXI Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:              Rajd                                          *
 *   Autor:                Karol Farbis                                  *
 *   Zlozonosc czasowa:    O(nm)                                         *
 *   Zlozonosc pamieciowa: O(n+m)                                        *
 *   Opis:                 Rozwiazanie wolne                             *
 *                                                                       *
 *************************************************************************/

#include <algorithm>
#include <cstdio>
#include <queue>
#include <vector>

using namespace std;

const int N = 500 * 1000;

vector<int> G[N + 1];
int topo[N + 1];
int topor[N + 1];
int indeg[N + 1];

int maxin[N + 1];
int maxout[N + 1];
int result[N + 1];

void toposort(int n) {
    queue<int> kol;
    for(int i=1; i<=n; i++)
        if(indeg[i] == 0) kol.push(i);

    int nr = 0;
    while(!kol.empty()) {
        int v = kol.front();
        kol.pop();

        topo[++nr] = v;
        topor[v] = nr;
        for(vector<int>::iterator it = G[v].begin(); it != G[v].end(); it++) {
            indeg[*it] --;
            if(indeg[*it] == 0) kol.push(*it);
        }
    }
}

int tree[N + 1];

void tree_set(int s, int e, int v) {
    for(int i=s; i<=e; i++)
        tree[i] = max(tree[i], v);
}

int tree_get(int x) {
    return tree[x];
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    for(int i=1; i<=m; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        G[a].push_back(b);
        indeg[b] ++;
    }

    toposort(n);

    for(int i=1; i<=n; i++) {
        int v = topo[i];
        for(vector<int>::iterator it = G[v].begin(); it!=G[v].end(); it++) {
            maxin[*it] = max(maxin[*it], maxin[v] + 1);
        }
    }

    for(int i=n; i>=1; i--) {
        int v = topo[i];
        for(vector<int>::iterator it = G[v].begin(); it!=G[v].end(); it++) {
            maxout[v] = max(maxout[v], maxout[*it] + 1);
        }
    }

    for(int v=1; v<=n; v++) {
        for(vector<int>::iterator it = G[v].begin(); it != G[v].end(); it++) {
            int u = *it;
            if(topor[u] > topor[v] + 1)
                tree_set(topor[v] + 1, topor[u] - 1, maxin[v] + 1 + maxout[u]);
        }
    }

    for(int i=1; i<=n; i++) {
        result[i] = tree_get(topor[i]);
    }

    int pmax = 0;
    for(int i=2; i<=n; i++) {
        result[topo[i]] = max(pmax = max(pmax, maxin[topo[i-1]]), result[topo[i]]);
    }

    int smax = 0;
    for(int i=n-1; i>=1; i--) {
        result[topo[i]] = max(smax = max(smax, maxout[topo[i+1]]), result[topo[i]]);
    }

    int* me = min_element(result + 1, result + n+1);

    printf("%ld %d\n", long(me - result), *me);
}
