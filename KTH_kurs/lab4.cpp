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
    throw runtime_error("Target not among input @find_and_remove(...) in lab4.cpp");
}


int main()
{
    ifstream fin("KTH_kurs/word3.txt");
    vector<string> input;
    vector<vector<string>> bfs_queue;

    const string start = "s3t", end = "sur";
    const int input_size = 3;

    int index = 0;
    int iterations = 0;  
    {
        string line;
        bool first_word_among_input = false;
        while (getline(fin, line) )
        {
            input.push_back(line);

            if (line == start)
            {
                first_word_among_input = true;
            }
        }

        if (!first_word_among_input) throw runtime_error("First word not among input");
    }


    bfs_queue.push_back(vector<string>());
    bfs_queue.at(0).push_back( find_and_remove(input, start) );
     

    while (!false)
    {
        bfs_queue.push_back(vector<string>());
        
        while(!bfs_queue.at(iterations).empty())
        {
            string candidate = bfs_queue.at(iterations).front();
            cout << "Next candidate: '" << candidate << "' From chain: " << endl;
            bfs_queue.at(iterations).erase(bfs_queue.at(iterations).begin());

            for (int i= 0; i < input.size(); i++)
            {
                if (end.substr(0, input_size) == candidate.substr(0, input_size))
                {// We´re done
                    cout << "bfs_queue[" << iterations << "].front() == " << candidate << endl;
                    goto END_LOOP; 
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
                                string char_swap = "";
                                for ( int j = 0; j < 3; j++)
                                    char_swap += ((j == (skip+2) % 3) ? '?' : candidate[j]);
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

END_LOOP:

    cout << iterations << endl;
    return 0;
}