#include <cstdio>

#define N_MAX 1000010

int N, M;
unsigned int a[N_MAX];
int v[N_MAX];

inline int nrb(const int& x) {
    return ((x & (x - 1)) ^ x);
}

inline void set(int pos, int val) {
    for (; pos <= N; pos += nrb(pos)) {
        a[pos] ^= val;
    }
}

inline int getXor(int pos) {
    int s = 0;

    for (; pos > 0; pos -= nrb(pos)) {
        s ^= a[pos];
    }

    return s;
}

inline int getXor(int a, int b) {
    return (getXor(b) ^ getXor(a - 1));
}

void init() {
    scanf("%d%d", &N, &M);
    for (int i = 1; i <= N; ++i) {
        scanf("%d", &v[i]);
        set(i, v[i]);
    }
}

void solve() {
    int op;
    int a, b;

    for (int i = 0; i < M; ++i) {
        scanf("%d%d%d", &op, &a, &b);

        if (op == 1) {
            printf("%d\n", getXor(a, b));
        } else {
            set(a, (v[a] ^ b));
            v[a] = b;
        }
    }
}

int main() {
    freopen("capsunele.in", "r", stdin);
    freopen("capsunele.out", "w", stdout);

    init();
    solve();

    return 0;
}
