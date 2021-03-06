#include <iostream>
#include <map>
#include <queue>

using namespace std;

#define SIZE_X 100
#define SIZE_Y 100
#define MID_X 50
#define MID_Y 50

bool isPrime(int n)
{
    if (n <= 1)
        return false;
    for (int i = 2; i < n; i++)
        if (n % i == 0)
            return false;

    return true;
}

int main()
{
    int x = 0;
    int y = 0;
    int dx[4] = {-1, 0, 0, 1};
    int dy[4] = {0, -1, 1, 0};

    map<pair<int, int>, int> to_num;
    pair<int, int> to_coord[(SIZE_X * SIZE_Y) + 1];

    to_num[{x, y}] = 1;
    to_coord[1] = {x, y};

    {
        int dir = 0;     // 0 = right, 1 = up, 2 = left, 3 = down
        int limit = 1;   // Amount to print before changing direction
        int counter = 0; // How many printed in the current direction
        int turns = 0;   // Counter for turns taken, every second; limit++

        for (int i = 1; i < 10000; i++)
        {
            if (isPrime(i))
            {
                ;
            }
            else
            {
                to_num[{x, y}] = i;
                to_coord[i] = {x, y};
            }

            switch (dir)
            {
            case 0:
                y++;
                break;
            case 1:
                x--;
                break;
            case 2:
                y--;
                break;
            case 3:
                x++;
                break;
            }

            counter++;

            if (counter >= limit)
            {
                counter = 0;
                turns = (turns + 1) % 2;
                dir = (dir + 1) % 4;

                if (turns == 0)
                {
                    limit++;
                }
            }
        }
    }

    int _case = 1;
    int src, dest;
    while (cin >> src >> dest)
    {
        cout << "Case " << _case++ << ": ";

        map<pair<int, int>, int> bfs_map;
        queue<pair<int, int>> bfs_q;

        bfs_q.push(to_coord[src]);

        // Breadth First Search (BFS)
        while (!bfs_q.empty())
        {
            // Skip if src || dest not reachable
            if (isPrime(src) || isPrime(dest))
            {
                break;
            }

            auto curr = bfs_q.front();
            bfs_q.pop();

            for (int i = 0; i < 4; i++)
            {
                auto next = curr;

                next.first += dx[i];
                next.second += dy[i];

                // Check if path is possible
                if (!to_num.count(next))
                {
                    continue;
                }
                // Check if there already exists shorter path to coordinate
                else if (bfs_map.count(next))
                {
                    continue;
                }
                bfs_map[next] = bfs_map[curr] + 1;
                bfs_q.push(next);

                // With BFS the first occourance must also be shortest
                if (to_num[next] == src)
                {
                    break;
                }
            }
        }

        if (!bfs_map.count(to_coord[dest]) || src == dest)
        {
            cout << "impossible" << endl;
        }
        else
        {
            cout << bfs_map[to_coord[dest]] << endl;
        }
    }

    return 0;
}