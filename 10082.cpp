#include <iostream>
#include <string>
#include <vector>
using namespace std;
int main()
{
  vector<string> arr = { "!@#$%^&*()_+",
                         "QWERTYUIOP{}|",
                         "ASDFGHJKL:\"",
                         "ZXCVBNM<>?",
                         "1234567890-=",
                         "qwertyuioP[]\\",
                         "asdfghjkL;'",
                         "zxcvbnM,./"};
  string row;
  while(getline(cin,row))
  {
    if (row.empty())
      break;
    for(int i = 0; i < row.size(); i++)
    {
      for( string s : arr )
      {
        for(int j = 0; j < s.size(); j++)
        {
          if ( s.at(j) == row.at(i) && j > 0 )
            row[i] = s.at(j-1);
        }
      }
    }
    cout << row << endl;
  }
  
}
