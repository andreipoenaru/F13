#include <cstdio>
#include <set>
#include <algorithm>
using namespace std;
#define N 260
#define fs first
#define sc second
#define mp make_pair
#define pii pair< int, int >

int n, m, k;
int locSize[N];
int locInd[N];
int loc[N][N];
int nrVraji[N];
int pacheteMax[N];
set< pii, greater< pii > > fav, neFav;
pii favCoolDown[N], neFavCoolDown[N];
int favCoolDownSize, neFavCoolDownSize;

inline void citire() {
    scanf("%d%d%d", &n, &m, &k);

    for (int i = 1; i <= m; ++i) {
        scanf("%d", &locSize[i]);
        loc[i][0] = 0;
        locInd[i] = i;
    }

    for (int i = 1; i <= n; ++i) {
        nrVraji[i] = 1;
    }

    int v, nv;

    for (int i = 0; i < k; ++i) {
        scanf("%d", &v);
        nrVraji[v] = 0;
    }

    while (scanf("%d%d", &v, &nv) == 2) {
        nrVraji[v] += nv;
    }
}

bool comparLocSize(const int& x, const int& y) {
    return (locSize[x] < locSize[y]);
}

inline void rezolva() {
    pii v;
    set< pii >::iterator vIt;
    int locId;

    sort(locInd + 1, locInd + m + 1, comparLocSize);

    for (int i = 1; i <= n; ++i) {
        if (nrVraji[i] != 0) {
            neFav.insert(mp(nrVraji[i], i));
        }
    }

    locId = locInd[m];
    for (int i = 0; i < locSize[locId]; ++i) {
        vIt = neFav.begin();
        v = *vIt;
        neFav.erase(vIt);

        loc[locId][i] = v.sc;
        --v.fs;

        if (v.fs > 0) {
            fav.insert(v);
        }
    }

    pacheteMax[0] = 1;
    pacheteMax[1] = locId;

    for (int i = m - 1; i > 0; --i) {
        locId = locInd[i];

        while ((int)fav.size() > locSize[locId]) {
            neFav.insert(*fav.rbegin());
            fav.erase(--fav.rbegin().base());
        }

        if ((neFav.begin()->fs) == i) {
            // Nu mai am nicio sansa sa creez pachete speciale

            neFav.insert(fav.begin(), fav.end());
            fav.clear();

            for (; i > 0; --i) {
                locId = locInd[i];
                neFavCoolDownSize = 0;

                for (int j = 0; j < locSize[locId]; ++j) {
                    vIt = neFav.begin();
                    v = *vIt;
                    neFav.erase(vIt);

                    loc[locId][j] = v.sc;

                    --v.fs;
                    if (v.fs > 0) {
                        neFavCoolDown[neFavCoolDownSize] = v;
                        ++neFavCoolDownSize;
                    }
                }

                for (int j = 0; j < neFavCoolDownSize; ++j) {
                    neFav.insert(neFavCoolDown[j]);
                }
            }

            break;
        }

        int j = 0; // cate am bagat pana acum in pachetul curent
        favCoolDownSize = neFavCoolDownSize = 0;

        // Le bag pe cele favorite care vor face parte din toate
        // pachetele de acum inainte
        while ((fav.begin()->fs) == i) {
            vIt = fav.begin();
            v = *vIt;
            fav.erase(vIt);

            loc[locId][j] = v.sc;
            ++j;

            --v.fs;
            if (v.fs > 0) {
                favCoolDown[favCoolDownSize] = v;
                ++favCoolDownSize;
            }
        }

        // vad daca pot sa umplu pachetul curent doar cu vraji favorite
        if ((int)fav.size() == (locSize[locId] - j)) {
            pacheteMax[++pacheteMax[0]] = locId;

            for (; j < locSize[locId]; ++j) {
                vIt = fav.begin();
                v = *vIt;
                fav.erase(vIt);

                loc[locId][j] = v.sc;
                ++j;

                --v.fs;
                if (v.fs > 0) {
                    favCoolDown[favCoolDownSize] = v;
                    ++favCoolDownSize;
                }
            }
        } else {
            // Pachetul asta nu va contine doar vraji favorite

            while (j < locSize[locId] && !neFav.empty()) {
                vIt = neFav.begin();
                v = *vIt;
                neFav.erase(vIt);

                loc[locId][j] = v.sc;
                ++j;

                --v.fs;
                if (v.fs > 0) {
                    neFavCoolDown[neFavCoolDownSize] = v;
                    ++neFavCoolDownSize;
                }
            }

            while (j < locSize[locId]) {
                v = *(fav.rbegin());
                fav.erase(--fav.rbegin().base());

                loc[locId][j] = v.sc;
                ++j;

                --v.fs;
                if (v.fs > 0) {
                    favCoolDown[favCoolDownSize] = v;
                    ++favCoolDownSize;
                }
            }

        }

        for (int j = 0; j < favCoolDownSize; ++j) {
            fav.insert(favCoolDown[j]);
        }
        for (int j = 0; j < neFavCoolDownSize; ++j) {
            neFav.insert(neFavCoolDown[j]);
        }
    }
}

inline void scrie() {
    for (int i = 1; i <= m; ++i) {
        if (locSize[i] == 0) {
            printf("\n");
            continue;
        }

        sort(loc[i], loc[i] + locSize[i]);
        printf("%d", loc[i][0]);
        for (int j = 1; j < locSize[i]; ++j) {
            printf(" %d", loc[i][j]);
        }
        printf("\n");
    }

    printf("%d\n", pacheteMax[0]);
    for (int i = pacheteMax[0]; i > 0; --i) {
        int locId = pacheteMax[i];

        if (locSize[locId] == 0) {
            printf("\n");
            continue;
        }

        sort(loc[locId], loc[locId] + locSize[locId]);
        printf("%d", loc[locId][0]);
        for (int j = 1; j < locSize[locId]; ++j) {
            printf(" %d", loc[locId][j]);
        }
        printf("\n");
    }
}

int main() {
    freopen("hogwarts.in", "r", stdin);
    freopen("hogwarts.out", "w", stdout);

    citire();
    rezolva();
    scrie();

    return 0;
}
