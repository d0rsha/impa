#include <iostream>
#include <map>
#include <queue>


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
    int x = 0;
    int y = 0;
    int dx[4] = {-1,0,0,1};
    int dy[4] = {0,-1,1,0};

    map<pair<int,int>, int> to_num;
    pair<int,int> to_coord[10001]; 

    to_num[{x,y}] = 1;
    to_coord[1] = {x,y};

    int curr = 2;
    int steps = 1;
    while(curr <= 10000) {
        for(int i = 0; i < 4 && curr <= 10000; i++) {
            for(int j = 0; j < steps && curr <= 10000; j++) {
                switch(i) {
                    case 0: y++; break;
                    case 1: x--; break;
                    case 2: y--; break;
                    case 3: x++; break;
                }

                //  Skip if Prime number
                if(isPrime(curr)) {
                    ;
                }
                //  Add if Composite number
                else {
                    to_num[{x,y}] = curr;
                    to_coord[curr] = {x,y};
                }

                curr++;
            }
            if(i % 2 == 1) {
                steps++;
            }
        }
    }

    
    for(int i = -9; i <= 9; i++) 
    {
        for(int j = -9; j <= 9; j++) {
           if (to_num.count({i,j}) ) {
                cout << to_num[{i,j}] << "\t";
           }
           else {
               cout << " X " << "\t";
           }
        }
        cout << endl;
    }
    

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
            }
        }


        // If dest is not inside map then no path available
        if(!bfs_map.count(to_coord[dest])) {
            cout << "impossible" << endl;
        } else {
            cout << bfs_map[to_coord[dest]] << endl;
        }
    }
}