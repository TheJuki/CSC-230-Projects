#include <string>

using namespace std;

int binary(int lo, int hi, string a[], string item) // Binary Search
{
    if (lo > hi)
        return -1; // Not found
    int mid = (lo + hi) / 2;
    if(a[mid] == item)
        return mid; // Found
    else if(a[mid] < item)
        return binary(mid + 1, hi, a, item);
    else
        return binary(lo, mid - 1, a, item);


}
