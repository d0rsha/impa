#include <bits/stdc++.h> 
using namespace std; 

int max(int a, int b) { return (a > b)? a : b; } 

int knapSack(int W, int wt[], int val[], int n) 
{ 
if (n == 0 || W == 0) { return 0; }

// Oh noh! Not enough money left for this Item
if (wt[n-1] > W) { return knapSack(W, wt, val, n-1); }

// Get max of Getting Item or NOT getting item 
else { return max( val[n-1] + knapSack(W - wt[n-1], wt, val, n-1), 
					knapSack(W, wt, val, n-1) ); }
} 

int main() 
{ 
	int* costs; 
	int* weights; 
	int max_price;

	int n = sizeof(costs)/sizeof(costs[0]); 
	cout<<knapSack(max_price, weights, costs, n); 
	return 0; 
} 

