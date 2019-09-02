// A Dynamic Programming based solution for 0-1 Knapsack problem 
#include<stdio.h> 
#include <iostream>
#include <fstream>
#include <vector>

#define ROWS 2

using namespace std;

int max(int a, int b) { return (a > b)? a : b; } 

int knapSack(int W, int wt[], int val[], int n) 
{ 
int i, w; 
int K[ROWS][W+1]; 
vector<int> list[ROWS][W];
int curr;

for (i = 0; i <= n; i++) 
{ 
	for (w = 0; w <= W; w++) 
	{ 
		if (i==0 || w==0) 
			K[i%ROWS][w] = 0; 
		else if (wt[(i-1)] <= w) 
		{
			if (val[(i-1)] + K[(i-1)%ROWS][(w-wt[(i-1)])] > K[(i-1)%ROWS][w] )
			{
				K[i%ROWS][w] = val[(i-1)] + K[(i-1)%ROWS][(w-wt[(i-1)])];
				list[i%ROWS][w] = list[(i-1)%ROWS][(w-wt[(i-1)])];
				list[i%ROWS][w].push_back(i-1);
			}
			else // if ( K[(i-1)%ROWS][w] is bigger )
			{
				K[i%ROWS][w] = K[(i-1)%ROWS][w];
				list[i%ROWS][w] = list[(i-1)%ROWS][w];
			}
 		}
		else
		{
			K[i%ROWS][w] = K[(i-1)%ROWS][w]; 

		}
	}
	curr = i%ROWS; 
}

for (i = 0; i < ROWS; i++) 
{ 
	for (w = 0; w <= W; w++) 
	{
		cout << K[i][w] << " ";
	}
	cout << endl;
} // Kolla föregående fall 

return K[n][W]; 
} 

int main() 
{ 
	int val[2000]; 
	int wt[2000];

	int W; 
	int n; 

	ifstream fin("knapsack.txt");
	while (fin >> W >> n)
    {
        for (int i = 0; i < n; i++)
        {
            fin >> val[i] >> wt[i];
        }

        // Variables initialized;
	    cout << knapSack(W, wt, val, n) << endl; 

    }

	return 0; 
} 
