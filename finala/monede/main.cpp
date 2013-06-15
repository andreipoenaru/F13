#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

#define M_MAX 20
#define pb push_back
#define DELIMS " \n\r\t"

vector< int > tStg[5];
vector< int > tDr[5];
int stgMinusDr[5];
int val[M_MAX];

inline void citire() {
    char stanga[M_MAX], dreapta[M_MAX], stare[M_MAX];
    char line[M_MAX * 4];
    char *sp;

    for (int i = 0; i < 3; ++i) {
        fgets(line, M_MAX * 4, stdin);

        sp = strtok(line, DELIMS);
        strcpy(stanga, sp);

        sp = strtok(NULL, DELIMS);
        if (sp != NULL) {
            strcpy(dreapta, sp);

            sp = strtok(NULL, DELIMS);
            strcpy(stare, sp);
        } else {
            strcpy(stare, stanga);
            stanga[0] = '\0';
            dreapta[0] = '\0';
        }


        for (int j = 0; stanga[j] != '\0'; ++j) {
            tStg[i].pb(stanga[j] - 'A');
        }
        for (int j = 0; dreapta[j] != '\0'; ++j) {
            tDr[i].pb(dreapta[j] - 'A');
        }

        //fprintf(stderr, "%s %s %s\n", stanga, dreapta, stare);

        if (strcmp(stare, "sus") == 0) {
            stgMinusDr[i] = 1;
        } else
        if (strcmp(stare, "egal") == 0) {
            stgMinusDr[i] = 0;
        } else {
            stgMinusDr[i] = -1;
        }
    }
}

inline int semn(const int& x) {
    if (x < 0) {
        return -1;
    }
    if (x == 0) {
        return 0;
    }
    return 1;
}

inline bool verif() {
    int sStg, sDr;

    for (int i = 0; i < 3; ++i) {
        sStg = sDr = 0;

        for (size_t j = 0, lim = tStg[i].size(); j < lim; ++j) {
            sStg += val[tStg[i][j]];
            sDr += val[tDr[i][j]];
        }

        if (semn(sStg - sDr) != stgMinusDr[i]) {
            return false;
        }
    }

    return true;
}

inline void rezolva() {
    for (int i = 0; i < 12; ++i) {
        val[i] = 2;
    }

    for (int i = 0; i < 12; ++i) {
        val[i] = 1;


        if (verif()) {
            printf("%c este moneda contrafacuta si este mai usoara.\n", (char)('A' + i));
            return;
        }

        val[i] = 2;
    }

    for (int i = 0; i < 12; ++i) {
        val[i] = 3;


        if (verif()) {
            printf("%c este moneda contrafacuta si este mai grea.\n", (char)('A' + i));
            return;
        }

        val[i] = 2;
    }

}

int main() {
    freopen("monede.in", "r", stdin);
    freopen("monede.out", "w", stdout);

    citire();
    rezolva();

    return 0;
}
