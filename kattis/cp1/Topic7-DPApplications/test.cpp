#include <iostream>
#include <numeric>

using namespace std;

int main()
{
    // cout<<"Hello World";
    int a[] = {1, 2, 3};
    int sum = 0;
    sum = accumulate(a + 2, a + 1, 0);
    cout << sum << endl;

    return 0;
}