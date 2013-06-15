#include<iostream>
#include<ctime>
#include<fstream>
#include<algorithm>
using namespace std;
ofstream f2 ("drept.in");
int main()
{
  srand(time(0));
	int max=rand()%1000+1;
	int x1,x2,y1,y2;
	int n=rand()%100+1;
	f2<<max+1<<"\n"<<n<<"\n";
	for (int i=1; i<=n; i++)
	{
		x1=rand()%max+1,x2=rand()%max+1, y1=rand()%max+1,y2=rand()%max+1;
		if (x1>x2) swap(x1,x2);
		if (x1==x2) x2++;
		if (y1>y2) swap(y1,y2);
		if (y1==y2) y2++;
		f2<<x1<<" "<<y1<<" "<<x2<<" "<<y2<<"\n";
	}
	return 0;
}
