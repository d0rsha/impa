#include <iostream>
#include <cstdio>
#include <fstream>
#include <vector>
#include <string>
#include <vector>

#include <algorithm>

using namespace std;


string find_and_remove(vector<string> & input, string target)
{
    // Find start word and erase it, no point of going back to start (it's loop)
    vector<string>::iterator it = find (input.begin(), input.end(), target);
    string found = *it;
    // bfs_queue.push_back(*it);
    input.erase(it);
    return found;
    

}


int main()
{

    ifstream fin("word3.txt");
    vector<string> input;
    vector<vector<string>> bfs_queue;

    string word, start = "söt", end = "sur";

    int index = 0;
    int iterations;  
    {
        string line;
        getline(fin, line);
        cout << line << endl;
        while (getline(fin, line) )
        {
            if (word == start)
            {
                cout << start << " is among input" << endl;
            }
            else 
            {
                input.push_back(word);
            }
        }
    }

    bfs_queue.push_back(vector<string>());
    bfs_queue.at(0).push_back( find_and_remove(input, "söt") );
     
    vector<int> added;
    int removed = 0;

    // 
    for (iterations = 0; iterations < bfs_queue.size(); iterations++)
    {
        bfs_queue.push_back(vector<string>());

        while(!bfs_queue.at(iterations).empty())
        {
            string candidate = bfs_queue.at(iterations).front();
            bfs_queue.at(iterations).erase(bfs_queue.at(iterations).begin());

            for (int i= 0; i < input.size(); i++)
            {
                if (end == input[i])
                {// We´re done
                    goto END_LOOP; 
                    // return iterations;
                }
                else
                {
                    for (int skip = 0; skip < 3; skip++)
                    {
                        int index = (skip + 0) % 3;
                        if ( candidate[index] == input[i][index] )
                        {
                            index = (skip + 1) % 3;
                            if (candidate[index] == input[i][index] )
                            {   // Matched!
                                // bfs_queue.push_back(input[i]);
                                // Push_back match and remove item from list (shortest path to specific word)
                                bfs_queue.at(iterations+1).push_back( find_and_remove(input, input[i]) );

                                index = (skip + 2) % 3;
                                if (candidate[index] == input[i][index])
                                {   // Full matched end string!

                                }
                            }
                        }
                    }
                }       
            }
        }
        
        iterations++;
    }

END_LOOP:

    cout << iterations << endl;

    return 0;
}