#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

int Formula_1(std::string M);
int Formula_2(std::string M);
int Formula_3(std::string M);

using namespace std;

int main()
{
    //73 rows
    int rows = 73;
    //3 columns
    int columns = 3;
    //Initialize array
    int array[rows][columns];
    //Current line
    string line = "";
    //string stream for
    //int to string conversion
    stringstream strs;
    //current title
    string title = "";

    //Hash Numbers for each Formula
    int hash_num_1 = 0;
    int hash_num_2 = 0;
    int hash_num_3 = 0;

    //Counter for input row
    int counter = 0;

    //Set all cells to 0
    for (int r = 0; r < rows; ++r)
    {
        line = "";
        for (int c = 0; c < columns; ++c)
        {
            array[r][c]= 0;
        } // end for

    } // end for

    //open file containing titles
    ifstream input("titles-fall15.txt");
    //check if file can be opened
    if(input.is_open())
    {
        do
        {
            //Get title
            input >> title;
            //Get 3 hash numbers
            hash_num_1 = Formula_1(title);
            hash_num_2 = Formula_2(title);
            hash_num_3 = Formula_3(title);

            //Set those 3 hash numbers in the array
            array[counter][0]= hash_num_1;
            array[counter][1]= hash_num_2;
            array[counter][2]= hash_num_3;

            //Create line to display
            line = title + " ";
            strs.str(string());
            strs << array[counter][0];
            line += strs.str() + " ";
            strs.str(string());
            strs << array[counter][1];
            line += strs.str() + " ";
            strs.str(string());
            strs << array[counter][2];
            line += strs.str() + " ";

            //Display line
            cout << line << endl;

            ++counter;

        } while(!input.eof());
    } // end if
    return 0;
}

int Formula_1(string M)
{
    int sum;

    for (int N = 1; N <= M.length(); ++N)
    {
        sum += N*M[N];
    }

    return sum % 73;
}

int Formula_2(string M)
{
    int sum;

    for (int N = M.length(); N > 0; --N)
    {
        sum += N*M[N];
    }

    return sum % 73;
}

int Formula_3(string M)
{
    int sum;
    int factor;

    for (int N = 1; N <= M.length(); ++N)
    {
        factor = (2*N)+1;
        sum += factor*M[N];
    }

    return sum % 73;
}
