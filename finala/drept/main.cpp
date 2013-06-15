#include <iostream>
#include <algorithm>
#include <cstdio>
using namespace std;
#define N_MAX 2010

struct event {
    int x, a, b;
    int type;
};

bool comp(const event &x, const event &y) {
    if(x.x == y.x) return x.type < y.type;
    return x.x < y.x;
}

int n, MAX, k;
event events[N_MAX];

int dim[N_MAX];
int pos_left[N_MAX], stv[N_MAX];
int SOL;
void interval(event &p) {
    int val ;
    if(p.type == 0) {
        val = -1;
    }
    else {
        val = 0;
    }
    for(int i = p.a; i <= p.b; i++) {
        dim[i] = val;
    }
}

void compute2() {
    int k = 0;
    stv[0] = -1;
    for(int i = 0; i <= MAX; i++) {
        while(k > 0 && dim[stv[k]] >= dim[i]) {
            k--;
        }
        if(dim[i] == -1) {
            k = 0;
            stv[0] = i;
            continue;
        }
        pos_left[i] = stv[k];
        stv[++k] = i;
    }
    k = 0;
    stv[0] = MAX+1;
    for(int i = MAX; i >= 0; i--) {
        while(k > 0 && dim[stv[k]] >= dim[i]) {
            k--;
        }
        if(dim[i] == -1) {
            k = 0;
            stv[0] = i;
            continue;
        }
        int aux = dim[i] * (i-pos_left[i] + stv[k] - i - 1);
        if(SOL < aux) {
            SOL = aux;
        }
        stv[++k] = i;
    }
}

void compute(int value) {
    for(int i = 0; i <= MAX; i++) {
        if(dim[i] != -1) {
            dim[i] += value;
        }
    }
    compute2();
}
int main() {
    freopen("drept.in", "r", stdin);
    freopen("drept.out", "w", stdout);
    scanf("%d%d", &MAX, &n);
    MAX = MAX-1;
    for(int i = 1; i <= n; i++) {
        int a,b,c,d;
        scanf("%d%d%d%d", &a, &b, &c, &d);
        events[++k].x = a;
        events[k].a = b;
        events[k].b = d-1;
        events[k].type = 0;

        events[++k].x = c;
        events[k].a = b;
        events[k].b = d-1;
        events[k].type = 1;
    }

    sort(events + 1, events+k+1, comp);
    int last = 0;
    events[0].x = 0;
    for(int i = 1; i <= k; i++) {
        compute(events[i].x - events[last].x);
        int j;
        for(j = i; j <= k && events[j].x == events[i].x; j++) {
            interval(events[j]);
        }
        i = j-1;
        last = i;
    }
    compute(MAX - events[last].x);
    printf("%d\n", SOL);
    return 0;
}
