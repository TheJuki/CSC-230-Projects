#include <iostream>

//Iterative
int binarySearch(int array[], int target);

using namespace std;

int binary_search(int array[],int first,int last, int value);

int main() {

int list[10];

 for (int k=0; k<11; k++)
 list[k]=2*k+1;

 cout<< "binary search results: "<< binary_search(list,1,21,11)<<endl;

 return 0;
}//end of main

