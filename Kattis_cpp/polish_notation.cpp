#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <stack>

using namespace std;
using std::cout;

bool isOperator(string token);
bool isNumber(string s);
void print_stack(vector<string> v);
vector<string> split(string line, char delimiter);
string concatenate(stack<string> arr);

bool isOperator(string token)
{
  if (token.size() == 1)
  {
    if (token == "-")
      return true;
    else if (token == "+")
      return true;
    else if (token == "*")
      return true;
  }
  return false;
}

bool isNumber(string s)
{
  if (s.empty() || std::isalpha(s[0]))
    return false;
  char *p;
  strtod(s.c_str(), &p);
  return (*p == 0);
}

vector<string> split(string line, char delimiter)
{
  string token;
  vector<string> tokens;
  stringstream stream(line);
  while (stream >> token)
  {
    tokens.push_back(token);
  }
  return tokens;
}

string concatenate(stack<string> arr)
{
  string sum = "";
  while (!arr.empty())
  {
    sum += arr.top() + " ";
    arr.pop();
  }
  sum.pop_back();
  return sum;
}

/*
* Main
*/
int main()
{
  int _case = 1;
  string line;
  while (getline(std::cin, line))
  {
    if (line.empty())
      return 0;

    vector<string> input = split(line, ' ');
    stack<string> stacken;

    for (int i = input.size() - 1; i >= 0; i--)
    {
      // cout<< "Iteration: " << i << " stackSize: " << stacken.size() << endl;
      const string token = input[i];

      if (isOperator(token))
      {
        const string OP = token;

        const string E1 = stacken.top();
        stacken.pop();
        const string E2 = stacken.top();
        stacken.pop();

        // cout << "OP(" << OP << ") E1(" << E1 << ") E2(" << E2 << ")" <<endl;
        if (isNumber(E1) && isNumber(E2))
        {
          // cout << "Evaluate E1 OP E2" << endl;
          switch (OP[0])
          {
            std::string::size_type sz; // alias of size_t
          case '-':
            stacken.push(to_string(stoi(E1, &sz) - stoi(E2, &sz)));
            break;
          case '+':
            stacken.push(to_string(stoi(E1, &sz) + stoi(E2, &sz)));
            break;
          case '*':
            stacken.push(to_string(stoi(E1, &sz) * stoi(E2, &sz)));
            break;
          };
        }
        else
        {
          stacken.push(E2);
          stacken.push(E1);
          stacken.push(OP);
        }
      }
      else if (token.empty())
      {
        ;
      }
      else
      {
        stacken.push(token);
        // cout << "Push " << token << endl;
      }
    }

    string result = concatenate(stacken);
    cout << "Case " << _case++ << ": " << result << endl;
  }

  return 0;
}