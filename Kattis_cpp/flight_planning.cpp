#include <cstdio>
#include <cmath>
#include <vector>
#include <map>
#include <iostream>

using namespace std;

class Node
{
public:
  vector<Node> neighbour;
  int lpath{0};
};

int main()
{
  int N, nodes;
  map<int, int> m;

  scanf("%d", &N);
  for (int i = 1; i < N; i++)
  {
    int src, dest;
    scanf("%d %d", &src, &dest);

    if (m.find(src) == m.end())
    {
      m.insert(make_pair(src, dest));
    }
    else
    {
      m.insert(make_pair(dest, src));
    }
  }

  for (map<int, int>::iterator itr = m.begin(); itr != m.end(); ++itr)
  {
    cout << '\t' << itr->first
         << '\t' << itr->second << '\n';
  }

  return 0;
}
