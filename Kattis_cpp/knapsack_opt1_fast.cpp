// A Dynamic Programming based solution for 0-1 Knapsack problem 
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

#define MAX 2002
//#define DEBUG_BUILD DEBUG_BUILD_DEFINED


int matrix[MAX][MAX];
int cost[MAX]; 
int weight[MAX];

vector<int> calc_knapsack_without_repitions (int W, int n) 
{ 
	int i, w; 
	 

	// Create matrix
	for (i = 0; i <= n; i++) 
	{ 
		for (w = 0; w <= W; w++) 
		{ 
			if (i == 0 || w == 0) 
			{ // Start case
				matrix[i][w] = 0; 
			}
			else if (weight[(i-1)] <= w && cost[i - 1] + matrix[i - 1][w-weight[i - 1]] > matrix[i - 1][w]) 
			{ 	// Add item
				matrix[i][w] = cost[i - 1] + matrix[i - 1][w-weight[i - 1]];
			}	
			else
			{	// Do not add item 
				matrix[i][w] = matrix[i-1][w]; 
			}			
		}
	}

	// Backtrace matrix
	int sack_value = matrix[n][W];
	vector<int> v;



	w = W; 
	for (i = n; i > 0 && sack_value > 0; i--) { 

		if (sack_value == matrix[i - 1][w])  
		{	// No new item was added in this row
			continue;
		}
		else { // new item was added this row
			v.push_back(i - 1);
			
			
			sack_value = sack_value - cost[i - 1]; 
			w = w - weight[i - 1]; 
		} 
	}

	return v; 
} 

int main() 
{ 
	int W; 
	int n; 

#ifdef DEBUG_BUILD
       ifstream fin("knapsack.txt");
       #define cin fin
#endif

 	while (cin >> W >> n)
    {
        for (int i = 0; i < n; i++)
        {
            cin >> cost[i] >> weight[i];
        }

        // Variables initialized;
		vector<int> res = calc_knapsack_without_repitions(W, n);
		cout << res.size() << endl;
	    for (auto x : res )
		{
			cout <<  x << " "; 

 		}
		cout << endl;
    }

	return 0; 
}
