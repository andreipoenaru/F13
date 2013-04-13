#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;
#define N_MAX 1010
#define INF 2000000000

vector<pair<int, int> > G[N_MAX];
double D1[N_MAX], D2[N_MAX];
bool selected[N_MAX];
int n, m, X, Y;
int vi, vv, vt;

inline int encode(int dist, int tip) {
    return tip + (dist << 1);
}

inline  pair<int, int> decode(int x) { //pereche (dist, tip)
    return make_pair(x >> 1, x & 1);
}

inline double cost(int x, int player) {
    pair<int, int> p = decode(x);
    if(p.second == 0) { //teleferic
        return (double) p.first / vt;
    }
    else {
        if(player == 0) return (double) p.first / vi;
        return (double) p.first / vv;
    }
}
void dijk(int src, int player, double D[N_MAX]) {
    memset(selected, 0, sizeof(selected));
    for(int i = 1; i <= n; i++) {
        D[i] = INF;
    }
    D[src] = 0;
    for(int i = 1; i <= n; i++) {
        int nod = -1; double cst = INF;
        for(int j = 1; j <= n; j++) {
            if(!selected[j] && D[j] < cst) {
                nod = j;
                cst = D[j];
            }
        }
        if(nod == -1) break;

        selected[nod] = 1;
        for(vector<pair<int, int> >::iterator it = G[nod].begin(); it != G[nod].end(); it++) {
            if(!selected[it->first]) {
                D[it->first] = min(D[it->first],  D[nod] + cost(it->second, player));
            }
        }
    }

}
int main() {
    freopen("ski.in", "r", stdin);
    freopen("ski.out", "w", stdout);

    scanf("%d%d%d%d", &n, &m, &X, &Y);

    scanf("%d%d%d", &vi, &vv, & vt);
    for(int i = 1; i <= m; i++) {
        int tip, x, y, dist;
        scanf("%d%d%d%d", &tip, &x, &y, &dist);
        if(tip == 2) { //ski
            G[x].push_back(make_pair(y, encode(dist, tip-1)));
        }
        else { //teleferic
            G[x].push_back(make_pair(y, encode(dist, tip-1)));
            G[y].push_back(make_pair(x, encode(dist, tip-1)));
        }
    }
    dijk(X, 1, D1);
    dijk(Y, 0, D2);

    int nod = -1; double cst = INF;
    for(int i = 1; i <= n; i++) {
        if(D1[i] == INF || D2[i] == INF) continue;
        double c = max(D1[i], D2[i]);
        if(c < cst) {
            cst = c;
            nod = i;
        }
    }
    printf("%d\n", nod);
    if(nod != -1) {
        int secs = cst * 3600;
        int mins = secs / 60;
        int hours = mins / 60;
        mins %= 60;
        secs %= 60;
        printf("%d:%d:%d\n", hours, mins, secs);
    }

    return 0;
}
