#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

int Formula_1(std::string M);
int Formula_2(std::string M);
int Formula_3(std::string M);
std::string PadNumber(int num);
int MatchHash(int array[][3], int column, int numOfrows, int hash);

using namespace std;

int main()
{
    //73 rows
    int rows = 73;
    //3 columns
    int columns = 3;
    //Initialize array
    int array[73][3];
    //Current line
    string line = "";
    //current title
    string title = "";

    //Hash Numbers for each Formula
    int hash_num_1 = 0;
    int hash_num_2 = 0;
    int hash_num_3 = 0;

    //Counter for input row
    int counter = 0;

    //Number of collisions for each Formula
    int collsion_1 = 0;
    int collsion_2 = 0;
    int collsion_3 = 0;

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
        cout << "----------------------------------------------------" << endl;
        cout << " Formula 1 | Formula 2 | Formula 3 | Title " << endl;
        cout << "----------------------------------------------------" << endl;
        do
        {
            //Get title
            input >> title;
            //Get 3 hash numbers
            hash_num_1 = Formula_1(title);
            hash_num_2 = Formula_2(title);
            hash_num_3 = Formula_3(title);

            //Get collisions
            collsion_1 += MatchHash(array, 0, (counter + 1), hash_num_1);
            collsion_2 += MatchHash(array, 1, (counter + 1), hash_num_2);
            collsion_3 += MatchHash(array, 2, (counter + 1), hash_num_3);

            //Set those 3 hash numbers in the array
            array[counter][0]= hash_num_1;
            array[counter][1]= hash_num_2;
            array[counter][2]= hash_num_3;

            //Create line to display
            line = "    ";
            line += PadNumber(array[counter][0]);
            line += string(9, 32);
            line += PadNumber(array[counter][1]);
            line += string(9, 32);
            line += PadNumber(array[counter][2]);
            line += string(6, 32);
            line += title;

            //Display line
            cout << line << endl;

            ++counter;

        }
        while(!input.eof() && counter != rows);

        cout << "----------------------------------------------------" << endl;
        cout << " Collisions | Collisions | Collisions " << endl;
        cout << "----------------------------------------------------" << endl;

        line = "    ";
        line += PadNumber(collsion_1);
        line += string(9, 32);
        line += PadNumber(collsion_2);
        line += string(9, 32);
        line += PadNumber(collsion_3);
        line += string(6, 32);

        cout << line << endl;


    } // end if

    //Wait for Enter
    cout << endl << endl << endl << endl << " Press Enter to Quit";
    string s;
    getline(cin, s);
    return 0;
}

int Formula_1(string M)
{
    int sum;
    int length = M.length();

    for (int N = 1; N <= length; ++N)
    {
        sum += N*M[N];
    }

    return sum % 73;
}

int Formula_2(string M)
{
    int sum;
    int length = M.length();

    for (int N = length; N > 0; --N)
    {
        sum += N*M[N];
    }

    return sum % 73;
}

int Formula_3(string M)
{
    int sum;
    int factor;
    int length = M.length();

    for (int N = 1; N <= length; ++N)
    {
        factor = (2*N)+1;
        sum += factor*M[N];
    }

    return sum % 73;
}

string PadNumber(int num)
{
    //string stream for
    //int to string conversion
    stringstream strs;

    string padded_num;

    if(num < 10)
    {
        strs << num;
        padded_num = "  " + strs.str();
    }
    else if(num < 100)
    {
        strs << num;
        padded_num = " " + strs.str();
    }

    return padded_num;
}

int MatchHash(int array[][3], int column, int numOfrows, int hash)
{
    for (int i = 0; i < numOfrows; i++)
    {
        if(array[i][column] == hash)
        {
            //Found
            return 1;
        }
    } // end for

    return 0;
}

