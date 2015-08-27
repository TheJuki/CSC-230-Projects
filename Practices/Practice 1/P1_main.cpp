//Justin Kirk
//Practice 1

#include <iostream>
#include <string>
using namespace std;

int main()
{

    int sum, testScore1, testScore2, testScore3;
    string s;
    char hold;

    //Prompt user
    cout << "Please enter three test score separated by spaces: ";

    //Read user input
    cin >> testScore1 >> testScore2 >> testScore3;
    getline(cin, s); // Get that extra return key at the end of line.

    //Compute total
    sum = testScore1 + testScore2 + testScore3;

    //Print result
    cout << "Sum of three scores is : " << sum << endl
            << "Average is : " << sum/3.0f << endl;

    getline(cin, s); //Hit Enter

    return(0);
}
