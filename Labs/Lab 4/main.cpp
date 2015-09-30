#include <iostream>

using namespace std;

int main()
{
    int rows = 73;
    int columns = 3;
    int array[rows][columns];

    for (int r = 0; r < rows; ++r)
    {
        for (int c = 0; c < columns; ++c)
        {
          array[r][c]= 0;
          //cout << array[r][c] << endl;
        }
    }


    return 0;
}
