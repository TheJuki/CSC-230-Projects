#include <iostream>
#include <string>
#include <sstream>

using namespace std;

int main()
{
    int rows = 73;
    int columns = 3;
    int array[rows][columns];
    string line = "";
    std::stringstream strs;

    for (int r = 0; r < rows; ++r)
    {
        line = "";
        for (int c = 0; c < columns; ++c)
        {
          strs.str(std::string());
          array[r][c]= 0;
          strs << array[r][c];
          line += strs.str() + " ";
        }
         cout << line << endl;
    }


    return 0;
}
