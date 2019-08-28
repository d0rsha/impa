#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

class Binary
{
public:
   Binary(int n, int v)
      :size{v}, table(v, false), max{n}
      {}
   int operator++()
      {
         add();
         return binarysum();
      }
   void print()
      {
         for ( int z = table.size()-1; z >=0; z--)
            cout << table.at(z);
         cout << endl;
      }
   int binarysum()
      {
         int sum{};
         for( int x : table )
            sum += x;
         return sum;
      }

   bool overflow{false};

private:
   void add(int ctr = 0)
      {
         //  if ( table.size() > size  ) 
         //   cout << "ERROR \n";
         if(ctr < size)
         {
            if ( table.at(ctr) < max )
            {
               table.at(ctr)++;
               return;
            }
            /*
            else if ( binarysum() > max )
            {
               if ( ctr+1 >= table.size()-1 )
               {
                  // cout  << "HEJ\n";
                  overflow = true;
                  return;
               }
               
               cout << "ctr = " << ctr << endl;
               table.at(ctr) = 0;
               table.at(1 +ctr)++;
               return;
            }*/
            else
            {
               table.at(ctr) = 0;
               add(++ctr);
            }
         }
         else
         {
           cout << "Overflow\n";
            overflow = true;
         }
      }
   
  
int decimal(int sum = 0, int exp = 0)
      {
         sum += pow(2, exp);
         if ( exp < (size - 1) )
            decimal(sum, ++exp);
         else 
            return sum;
      }
   int size;
   vector<int> table;
   int max;
   
};
int main()
{
   while (cin.good())
   {
      long long int tot{};
      int n, v;
      cin >> n >> v;
      if ( n == v && n == 0)
         break;
      Binary bin(n, v);
      
      do{
         ++bin;
         int bin_sum{bin.binarysum()};
         if (n % 2 == 0 && bin_sum % 2 == 0 && bin_sum <= n)
            tot++;
         else if ( n % 2 != 0 && bin_sum % 2 != 0 && bin_sum <= n)
            tot++;
         //cout << bin.binarysum() << " \t- binary: ";
          // bin.print();

      } while(!bin.overflow);

      cout << "Answer: " << tot << endl;
   }
}
