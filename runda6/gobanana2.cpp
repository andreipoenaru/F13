#include <cstdio>
#include <vector>
#include <set>
#define Nmax 1005
#define pb push_back
#define mp make_pair
#define y first
#define c second
#define INF 2147000000

using namespace std;
set< pair<int,int> > Set;
vector< pair<int,int> > v[Nmax];
int TT[Nmax],cmin[Nmax],use[Nmax], N,M,start[5];

int main()
{
    vector< pair<int,int> >:: iterator it;
    set< pair< int,int > >:: iterator pset;
    int i,cost=0,pmin,x,y,z;
    freopen("newyork.in","r",stdin);
    freopen("newyork.out","w",stdout);
    scanf("%d%d",&N,&M);
  for (i=1; i<=4; i++)
		scanf ("%d", &start[i]);
    for(i=1;i<=M;++i){
        scanf("%d%d%d",&x,&y,&z);
        v[x].pb(mp(y,z));
        v[y].pb(mp(x,z));
    }

    for(i=2;i<=N;++i) cmin[i]=INF;

	for (i=1; i<=4; i++)
		use[start[i]]=1;
	
	for (i=1; i<=4; i++)
		for(it=v[start[i]].begin(); it!=v[start[i]].end(); ++it)
			if (it->c<cmin[it->y] && !use[it->y])
			{
				pset=Set.find(mp(cmin[it->y],it->y));
                if( pset!=Set.end() ) Set.erase(pset);
				cmin[it->y]=it->c;
				Set.insert(mp(it->c,it->y));
				TT[it->y]=start[i];
			}
			
    for(i=5; i<=N; ++i)
	{
        cost += Set.begin()->first;
        pmin=Set.begin()->second;
        use[pmin]=1;
        Set.erase(Set.begin());
        for(it=v[pmin].begin(); it!=v[pmin].end(); ++it)
            if( cmin[it->y] > it->c && !use[it->y])
			{
                pset=Set.find(mp(cmin[it->y],it->y));
                if( pset!=Set.end() ) Set.erase(pset);
                cmin[it->y]=it->c;
                Set.insert(mp(it->c,it->y));
                TT[it->y]=pmin;
            }
    }

    printf("%d\n",cost);
    return 0;
}
