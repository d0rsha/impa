// C++ program of a space optimized DP solution for 
// 0-1 knapsack problem. 
#include<bits/stdc++.h> 
using namespace std; 

// item[] is for storing maximum profit for each weight 
// w[] is for storing weights 
// n number of item 
// W maximum capacity of bag 
// dp[W+1] to store final result 
int KnapSack(int item[], int w[], int n, int W) 
{ 
	// array to store final result 
	//dp[i] stores the profit with KnapSack capacity "i" 
	int dp[W+1]; 
	
	//initially profit with 0 to W KnapSack capacity is 0 
	memset(dp, 0, sizeof(dp)); 

	// iterate through all items 
	for(int i=0; i < n; i++) 
		//traverse dp array from right to left 
		for(int j=W; j>=w[i]; j--) 
			dp[j] = max(dp[j] , item[i] + dp[j-w[i]]); 
	/*above line finds out maximum of dp[j](excluding ith element itemue) 
	and item[i] + dp[j-w[i]] (including ith element value and the 
	profit with "KnapSack capacity - ith element weight") */	
	return dp[W]; 
} 

// Driver program to test the cases 
int main() 
{ 
	int item[] = {60, 100, 120}, w[] = {10, 20, 30};
    int W = 50;
    int n = sizeof(item)/sizeof(item[0]); 

	cout << KnapSack(item, w, n, W) << endl; 
	return 0; 
} 
