#include <cstdio>
#include <bitset>
using namespace std;

#define MAX_MAX 310

int MAX;
int N;
bitset< MAX_MAX > a[MAX_MAX];
int h[MAX_MAX];

int main() {
    freopen("drept.in", "r", stdin);
    freopen("dreptbrut.out", "w", stdout);

    scanf("%d", &MAX);
    scanf("%d", &N);

    int x0, y0, x1, y1;
    for (int i = 0; i < N; ++i) {
        scanf("%d%d%d%d", &x0, &y0, &x1, &y1);

        for (int x = x0; x < x1; ++x) {
            for (int y = y0; y < y1; ++y) {
                a[x][y] = 1;
            }
        }
    }

    int aux;
    int res = 0;
    for (int i = 0; i < MAX; ++i) {
        for (int j = 0; j < MAX; ++j) {
            if (a[i][j]) {
                h[j] = 0;
            } else {
                ++h[j];
            }
        }

        for (int j = 0; j < MAX; ++j) {
            if (h[j] == 0) {
                continue;
            }

            int j1, j2;

            for (j1 = j - 1; j1 >= 0 && h[j1] >= h[j]; --j1) {
                ;
            }
            for (j2 = j + 1; j2 < MAX && h[j2] >= h[j]; ++j2) {
                ;
            }

            aux = (j2 - j1 - 1) * h[j];
            if (aux > res) {
                res = aux;
            }
        }
    }

    printf("%d\n", res);
    return 0;
}
