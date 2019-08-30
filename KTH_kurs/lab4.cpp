/*
 * Did not find support for swedish charchters as char datatype.
 *  1 == å
 *  2 == Ä
 *  3 == ö
 * */
#include <iostream>
#include <cstdio>
#include <fstream>
#include <vector>
#include <string>
#include <vector>
#include <stdexcept>
#include <algorithm>
#include <locale> // Locale

using namespace std;


string find_and_remove(vector<string> & input, string target)
{
    // Find start word and erase it, no point of going back to start (it's loop)
    for (vector<string>::iterator it = input.begin(); it != input.end(); it++)
    {
        if ( *it == target)
            {
                string tmp = *it;
                input.erase(it);
                return tmp;
            }
    }
    throw runtime_error("Target not among input @find_and_remove(...) in lab4.cpp: " + target );
}

int breadth_first_search(vector<string> input, string start, string end, const int w_size )
{
    int iterations = 0;  
    vector<vector<string>> bfs_queue;

    bfs_queue.push_back(vector<string>());
    bfs_queue.at(0).push_back( find_and_remove(input, start) );
     

    while (!bfs_queue.at(iterations).empty())
    {
        bfs_queue.push_back(vector<string>());
        
        while(!bfs_queue.at(iterations).empty())
        {
            string candidate = bfs_queue.at(iterations).front();
            // cout << "Next candidate: '" << candidate << "' From chain: " << endl;
            bfs_queue.at(iterations).erase(bfs_queue.at(iterations).begin());

            for (int i= 0; i < input.size(); i++)
            {
                if (end.substr(0, w_size) == candidate.substr(0, w_size))
                {// We´re done
                    cout << "bfs_queue[" << iterations << "].front() == " << candidate << endl;
                    return iterations; 
                }
                else
                {
                    for (int skip = 0; skip < w_size; skip++)
                    {
                        int index = (skip + 0) % w_size;
                        if ( candidate[index] == input[i][index] )
                        {
                            index = (skip + 1) % w_size;
                            if (candidate[index] == input[i][index] )
                            {   // Matched!
                                string char_swap = "";
                                for ( int j = 0; j < w_size; j++)
                                    char_swap += ((j == (skip+2) % w_size) ? '?' : candidate[j]);
                                // cout << "Iteration[" << iterations << "] " << char_swap << " -> " << input[i] << endl;

                                // Push_back match and remove item from list (shortest path to specific word)
                                bfs_queue.at(iterations+1).push_back( string(find_and_remove(input, input[i]) + " <- " + candidate) );
                            }
                        }
                    }
                }       
            }
        }

        iterations++;
    }

    return -1;
}


int main()
{
    ifstream fin("KTH_kurs/word3.txt");
    vector<string> input;

    {
        string line;
        while (getline(fin, line) )
        {
            input.push_back(line);
        }
    }


    cout << breadth_first_search(input, "s3t", "sur", 3) << endl;
    return 0;
}