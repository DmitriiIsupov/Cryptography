#include <cmath>
#include <iostream>

// Recursion

#define inf 1000000000.0
#define sqr(a) ((a)*(a))

int n;
double p[1000][2];

double dist(int i, int j)
{
  return sqrt(sqr(p[i][0]-p[j][0])+sqr(p[i][1]-p[j][1]));
}

#define next(i) (((i)+1)%n)
#define pred(i) (((i)+n-1)%n)

double d[1000][1000]; // Distance

void filld() // Completion d
{
  for(int i=0; i<n; ++i)
    for(int j=0; j<n; ++j)
      d[i][j]=dist(i, j);
  for(int i=0; i<n; ++i)
    d[i][i]=0;
  for(int i=0; i<n; ++i)
  {
    int j=next(i);
    d[i][j]=0;
    d[j][i]=0;
  }
}

double r[1000][1000]; // Array for building routes

double func(int i, int j)
{
  if(next(i)==j) 
  {
    r[i][j]=-1;
    return 0;
  }
  double b=inf;
  for(int k=next(i); k!=j; k=next(k))
  {
    double t=d[i][j]+func(i, k)+func(k, j);
    if(t<b)
    {
      b=t;
      r[i][j]=k;
    }
  }
  return b;
}

void print(int i, int j, bool f) // Print
{
  if((i==j)||(next(i)==j)) return;
  if(f) std::cout<<i+1<<" "<<j+1<<"\n";
  if(r[i][j]<0) return;
  print(i, r[i][j], true);
  print(r[i][j], j, true);
}

int main()
{
  std::cin>>n;
  for(int i=0; i<n; ++i) 
  {
    std::cin>>p[i][0];
    std::cin>>p[i][1];
  }
  if(n<4) return 0;
  filld();
  double b=inf;
  int bi=-1, bj=-1;
  for(int i=0; i<n; ++i)
    for(int j=0; j<n; ++j)
      if(i!=j)
      {
        double t=func(i, j)+func(j, i)-d[i][j];
        if(t<b)
        {
          b=t;
          bi=i;
          bj=j;
        }
      }
  if((bi!=next(bj))&&(next(bi)!=bj)) std::cout<<bi+1<<" "<<bj+1<<"\n";
  print(bi, bj, false);
  print(bj, bi, false);
}
