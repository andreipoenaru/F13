#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>
using namespace std;
#define N_MAX 100010
#define LOG_MAX 40
struct Trie{
    Trie *fiu[2];
    Trie() {
        memset(fiu, 0 ,sizeof(fiu));
    }
};

Trie *root = new Trie();
long long v[N_MAX];
long long part_sol, SOL;
int n;

void add_trie(Trie *node, long long x, int h) {
    if(h == -1 || (x & ((1LL<<(h+1))-1)) == 0) return;
    int bit = (x & (1LL<<h)) > 0;
    if(node->fiu[bit] == NULL) {
        node->fiu[bit] = new Trie();
    }
    add_trie(node->fiu[bit], x, h-1);
}

void query_trie(Trie *node, long long x, int h) {
    if(h == -1 || node == NULL) {
        if(h != -1) {
            part_sol |= (x & ((1LL<<(h+1))-1));
        }
        if(part_sol > SOL) {
            SOL = part_sol;
        }
        return;
    }
    int bit = (x & (1LL<<h)) > 0;
    if(node->fiu[bit^1] != NULL) {
        part_sol |= (1LL<<h);
        query_trie(node->fiu[bit^1], x, h-1);
    }
    else {
        query_trie(node->fiu[bit], x, h-1);
    }
}

int main() {
    //freopen("bulbuka.in", "r", stdin);
    //freopen("bulbuka.out", "w", stdout);
    ifstream fin("bulbuka.in");
    ofstream fout("bulbuka.out");
    //scanf("%d", &n);
    fin >> n;
    long long pref = 0;
    for(int i = 1; i <= n; i++) {
        fin >> v[i];
        pref ^= v[i];
    }
    long long suf = 0;
    for(int i = n; i >= 0; i--) {
        add_trie(root, suf, LOG_MAX);
        part_sol = 0;
        query_trie(root, pref, LOG_MAX);
        suf ^= v[i];
        pref ^= v[i];
    }
    fout << SOL;
    return 0;
}
