//Justin Kirk
//Practice 3
//P3_main.cpp

#include <iostream>
#include <string>

using namespace std;

const int SENTINEL = 999;
void outputResults(int evenCounter, int oddCounter, int positiveCounter, int negativeCounter);

int main()
{
    int evenCounter = 0, oddCounter = 0, positiveCounter = 0, negativeCounter = 0, userNumber;
    string s;

    //Get first data
    cout << "Enter an integer (or 999 to quit): ";
    cin >> userNumber;

    //while loop
    while (userNumber != SENTINEL)
    {
        if (userNumber % 2 == 0)
            evenCounter++;
        else
            oddCounter++;
        if(userNumber > 0)
            positiveCounter++;
        else if (userNumber < 0)
            negativeCounter++;
        else; //Number is 0

        //Get next user input
        cout << "Enter an integer (or 999 to quit): ";
        cin >> userNumber;
    }//end while loop

    getline(cin, s);
    outputResults(evenCounter, oddCounter, positiveCounter, negativeCounter);
    getline(cin,s);
    return(0);

} // end of main()

void outputResults (int evenCounter, int oddCounter, int positiveCounter, int negativeCounter)
{
    //Print 3 blank lines
    for (int i = 1; i <=3; i++)
        cout << endl;
    cout << endl << " S U M M A R Y " << endl
         << "Number of even numbers in list was : "<< evenCounter << endl
         << "Number of odd numbers in list was : "<< oddCounter << endl
         << "Number of positive numbers in list was : "<< positiveCounter << endl
         << "Number of negative numbers in list was : "<< negativeCounter << endl
         << "Number of numbers in list was : "<< evenCounter + oddCounter << endl
         << endl;

}



