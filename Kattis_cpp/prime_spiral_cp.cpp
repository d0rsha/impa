#include <bits/stdc++.h>

using namespace std;

#define SIZE_X 100
#define SIZE_Y 100
#define MID_X 50
#define MID_Y 50

int dx[4] = {-1,0,0,1};
int dy[4] = {0,-1,1,0};


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


struct Coord {
    Coord()                 {   this->x = 10001; this->y = 10001;     }
    Coord(int _x, int _y)   {   this->x = _x; this->y = _y;    }
     int x;
     int y;

    int getInt()            {   return get(this->x, this->y);   }
    /*Coord onePlus()          
    {
        if (++(this->x) == SIZE_X)
        {
            this->x = 0;
            this->y += 1;
        }
        else 
        {
            this->x += 1;
        }
        return *this;
    }*/
};

Coord get(int num) 
{
    return Coord(num % SIZE_X, num / SIZE_X);
}

// Convert coordinates to number
int get(int x, int y)
{
    return ((y + MID_Y) * SIZE_Y) + (x + MID_X);
}


int main() {
    int currx = 0;
    int curry = 0;

    map<int, int> to_num;
    Coord to_coord[10001]; 

    to_num[get(currx,curry)] = 1;
    to_coord[1] = Coord{currx,curry};

    int curr = 2;
    int steps = 1;
    while(curr <= 10000) {
        for(int i = 0; i < 4 && curr <= 10000; i++) {
            for(int j = 0; j < steps && curr <= 10000; j++) {
                if(i == 0) {
                    curry++;
                }
                if(i == 1) {
                    currx--;
                }
                if(i == 2) { curry--;
                }
                if(i == 3) {
                    currx++;
                }

                if(!isPrime(curr)) {
                    to_num[get(currx,curry)] = curr;
                    to_coord[curr] = Coord{currx,curry};
                }

                curr++;
            }
            if(i % 2 == 1) {
                steps++;
            }
        }
    }

    
    for(int i = -9; i <= 9; i++) {
        for(int j = -9; j <= 9; j++) {
           if (to_num.count(get(i,j)))
           {
                cout << to_num[get(i,j)] << "\t";
           }
           else 
           {
               cout << " X " << "\t";
           }
        }
        cout << endl;
    }
    

    int num = 1;
    int n1, n2;
    while(cin >> n1 >> n2) {
        cout << "Case " << num++ << ": ";

        map<int, int> vis;
        queue<int> q;
        q.push(to_coord[n1].getInt());

        while(!q.empty()) {
            int curr = q.front();
            q.pop();

            for(int i = 0; i < 4; i++) {
                Coord next = get(curr);
                next.x += dx[i];
                next.y += dy[i];

                // Check if path is possible 
                if(!to_num.count(get(next.x,next.y))) {
                    continue;
                }
                if(vis.count(next.getInt())) {
                    continue;
                }
                vis[next.getInt()] = vis[curr] + 1;
                q.push(next.getInt());
            }
        }

        if(vis[to_coord[n2].getInt()] == 0 && n1 != n2) {
            cout << "impossible" << endl;
        }
        else {
            cout << vis[to_coord[n2].getInt()] << endl;
        }
    }
}