#include <cstdio>
#include <cmath>
#include <vector>
#include <map>
#include <iostream>
#include <limits.h>
#include <list>
#include <queue>
#include <algorithm>

using namespace std;

class Graph
{
  int nodes;
  vector<int> *adjacent;

public:
  Graph(int N)
  {
    this->nodes = N;
    adjacent = new vector<int>[N];
  }

  void addEdge(int src, int dest)
  {
    adjacent[src - 1].push_back(dest - 1);
    adjacent[dest - 1].push_back(src - 1);
  }

  void print_helper(int node)
  {
    if (adjacent[node].size() == 0)
    {
      cout << '\t' << node;
    }

    for (auto it = adjacent[node].begin(); it != adjacent[node].end(); it++)
    {
      print_helper(*it);
    }
  }
  void print()
  {
    print_helper(0);
  }

  int getNode(int node)
  {
    return node + 1;
  }

  pair<int, int> bfsMostDistantNode(int u)
  {
    u = u - 1;
    int distanceTo[nodes];
    memset(distanceTo, -1, sizeof(distanceTo));

    queue<int> q;
    q.push(u);

    distanceTo[u] = 0;
    cout << "distance From[" << u << "] " << endl;

    while (!q.empty())
    {
      int candidate = q.front();
      q.pop();

      for (auto it = adjacent[candidate].begin(); it < adjacent[candidate].end(); it++)
      {
        if (distanceTo[*it] != -1)
          continue;

        int neighbour = *it;

        q.push(neighbour);
        distanceTo[neighbour] = distanceTo[candidate] + 1;
        cout << "distanceTo[" << neighbour << "] = " << distanceTo[neighbour] << endl;
      }
    }

    int maxDis = 0;
    int cornerNode = (int)NULL;
    int size_n = sizeof(distanceTo) / sizeof(distanceTo[0]);
    int *result = std::max_element(distanceTo, distanceTo + size_n);

    return pair<int, int>(result - distanceTo + 1, *result);
  }
};

int main()
{
  int N, nodes;
  scanf("%d", &N);
  Graph g(N);

  for (int i = 1; i < N; i++)
  {
    int src, dest;
    scanf("%d %d", &src, &dest);
    g.addEdge(src, dest);
  }

  // Find longest path
  // use BFS
  auto lPair = g.bfsMostDistantNode(1);
  auto rPair = g.bfsMostDistantNode(lPair.first);

  cout << "left corner=" << lPair.first << "  right corner=" << rPair.first << " Length=" << rPair.second << endl;

  cout << "Stop usign cout as debug you shitfuck" << endl;

  // Have not been prooved
  // int lgroup = floor(m.size() / 2);
  // int rgroup = ceil(m.size() / 2);
  return 0;
}
