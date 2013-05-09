#include<fstream>
using namespace std;
ifstream f1 ("formula.in");
ofstream f2 ("formula.out");
int x[105],f[105];
int main()
{
  int n,x0;
	f1>>n>>x0;
	for (int i=1; i<=n; i++)
		f1>>x[i]>>f[i];
	double rez=0.0,p;
	for (int i=1; i<=n; i++)
	{
		p=f[i];
		for (int j=1; j<=n; j++)
			if (j!=i)
				p*=(double)(x0-x[j])/(x[i]-x[j]);
			rez=rez+p;
	}
	if (rez-int(rez)>0.5)
		f2<<int(rez)+1<<"\n";
	else 
		f2<<int(rez);
	return 0;
}
