#include <iostream>
#include <map>
#include <queue>
//***C++11 Style:***
#include <chrono>

using namespace std;

#define SIZE_X 100
#define SIZE_Y 100
#define MID_X 50
#define MID_Y 50



// Creed GeekForGeeks 
bool isPrime(int n) 
{ 
	// Corner case 
	if (n <= 1) 
		return false; 
	// Check from 2 to n-1 
	for (int i = 2; i < n; i++) 
		if (n % i == 0) 
			return false; 

	return true; 
} 






int main() {
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    int x = 0;
    int y = 0;
    int dx[4] = {-1,0,0,1};
    int dy[4] = {0,-1,1,0};

    map<pair<int,int>, int> to_num;
    pair<int,int> to_coord[10001]; 

    to_num[{x,y}] = 1;
    to_coord[1] = {x,y};

    {
        int dir = 0; // 0 = right, 1 = up, 2 = left, 3 = down
        int limit = 1; // Amount to print before changing direction
        int counter = 0; // How many printed in the current directio
        int turns = 0; // Counter for turns taken, every second; limit++

        for (int i = 1; i < 10000; i++) {
            //  Skip if Prime number
            if(isPrime(i)) {
                ;
            }
            //  Add if Composite number
            else {
                to_num[{x,y}] = i;
                to_coord[i] = {x,y};
            }

            switch(dir) {
                case 0: y++; break;
                case 1: x--; break;
                case 2: y--; break;
                case 3: x++; break;
            }
            
            counter++;

            if (counter >= limit) {
                counter = 0;
                turns = (turns + 1) % 2;
                dir = (dir + 1) % 4;
                
                if (turns == 0) {
                    limit++;
                }
            }
        }
    }

    /*
    for(int i = -12; i <= 12; i++) 
    {
        for(int j = -12; j <= 12; j++) {
           if (to_num.count({i,j}) ) {
                cout << to_num[{i,j}] << "\t";
           }
           else {
               cout << " X " << "\t";
           }
        }
        cout << endl;
    }
    */

    int _case = 1;
    int src, dest;
    while(cin >> src >> dest) {
        cout << "Case " << _case++ << ": ";
        
        map<pair<int,int>, int> bfs_map;
        queue<pair<int,int> > bfs_q;

        
        bfs_q.push(to_coord[src]);

        //
        // Breadth First Search (BFS)
        //
        while(!bfs_q.empty()) {
            // Skip if src || dest not reachable
            if (isPrime(src) || isPrime(dest)) { 
                break;
            } 
            //cout << "Queue Size: " << bfs_q.size() << endl;
            auto curr = bfs_q.front();
            bfs_q.pop();

            for(int i = 0; i < 4; i++) {
                auto next = curr;
                
                next.first += dx[i];
                next.second += dy[i];

                // Check if path is possible 
                if(!to_num.count(next)) {
                    continue;
                }
                // Check if there already exists shorter path to coordinate
                else if(bfs_map.count(next)) {
                    continue;
                }
                bfs_map[next] = bfs_map[curr] + 1;
                bfs_q.push(next);

                if (to_num[next] == src) {
                    break;
                }
            }
        }


        // If dest is not inside map then no path available
        if(!bfs_map.count(to_coord[dest]) || src == dest) {
            cout << "impossible" << endl;
        } else {
            cout << bfs_map[to_coord[dest]] << endl;
        }
    }

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    cout << "Time difference = " << chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "[ms]" << std::endl;

    return 0;
}