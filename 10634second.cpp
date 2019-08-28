#include <iostream>

using namespace std;

unsigned long long calc(int n, int v)
{
   if (n == 0)
      return 1;
   return calc(n-1, v) * n / (n-v+1);
}

int main()
{
   int n, v;
   cin >> n >> v;
   cout << calc(n,v) << endl;
}
