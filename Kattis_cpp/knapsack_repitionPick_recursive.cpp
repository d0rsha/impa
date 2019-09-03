#include <bits/stdc++.h> 
#include <fstream>
using namespace std; 

int max(int a, int b) { return (a > b)? a : b; } 

int knapSack(int W, int wt[], int val[], int n) 
{ 
if (n == 0 || W == 0) { return 0; }

// Oh noh! Not enough money left for this Item
if (wt[n-1] > W) { return knapSack(W, wt, val, n-1); }

// Get max of Getting Item or NOT getting item 
else { 
    
    return max( val[n-1] + knapSack(W - wt[n-1], wt, val, n-1), 
					knapSack(W, wt, val, n-1) ); 

}
} 

int main()  
{ 
	int costs[2000]; 
	int weights[2000]; 

    ifstream fin("knapsack.txt");
    string line;

    
    int capacity_;
    int items_;

    while (fin >> capacity_ >> items_)
    {
        for (int i = 0; i < items_; i++)
        {
            fin >> costs[i] >> weights[i];
        }

        // Variables initialized;
	    cout<<knapSack(capacity_, weights, costs, items_) << endl; 

    }





	return 0; 
} 

