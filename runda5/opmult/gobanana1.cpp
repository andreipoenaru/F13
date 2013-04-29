#include <cstdio>
#include <bitset>
using namespace std;
#define N_MAX 1000
#define S_MAX 2010
#define L_MAX 256
bitset <L_MAX> B[N_MAX];
char S[S_MAX];
char *p;
struct multime{
    bitset<L_MAX> *m;
    static int cnt;
    multime(char left_par, int x, int y, char right_par) {
        m = &B[cnt];
        m->reset();
        cnt++;
        x += (left_par == '(');
        y -= (right_par == ')');
        for(int i = x; i <= y; i++) {
            m->set(i);
        }
    }
    void reuniune(multime &x) {
        (*m) |= *(x.m);
    }
    void intersectie(multime &x) {
        (*m) &= *(x.m);
    }
    void diferenta(multime &x) {
        (*m) ^= (*m) & *(x.m);
    }

    void display() {
        for(int i = 0; i < L_MAX; i++) {
            if(m->test(i)) printf("%d ", i);
        }
        printf("\n");
    }
};

int multime:: cnt = 0;

multime termen();
multime element();

multime eval() {
    multime x = termen();
   // multime y;
    while(*p == 'u' || *p == '-') {
        if(*p == 'u') {
            p++;
            multime y = termen();
            x.reuniune(y);
        }
        else if(*p == '-') {
            p++;
            multime y = termen();
            x.diferenta(y);
        }
    }
    return x;
}

multime termen() {
    multime x = element();
    while(*p == 'n') {
        p++;
        multime y = element();
        x.intersectie(y);
    }
    return x;
}

int parse_int() {
    int x = 0;
    while(*p >= '0' && *p <= '9') {
        x = x * 10 + (*p) - '0';
        p++;
    }
    return x;
}

multime element() {
    while(*p == ' ') p++;
    char *s = p;
    p++; //sar peste paranteza
    int x = parse_int();
    p++; //sar peste virgula
    int y = parse_int();
    p++; //sar peste paranteza de inchidere
    return multime(*s, x, y, *(p-1));
}
void solve(int x) {
    multime::cnt = 0;
    p = S;
    multime sol = eval();
   // sol.display();
    if((sol.m)->test(x)) {
        printf("DA\n");
    }
    else {
        printf("NU\n");
    }
}
int main() {
    freopen("opmult.in", "r", stdin);
    freopen("opmult.out", "w", stdout);
    int t;
    scanf("%d", &t);
    for(int i = 1; i <= t; i++) {
        int x;
        scanf("%d \n", &x);
        fgets(S, S_MAX, stdin);
        solve(x);
    }
    return 0;
}
