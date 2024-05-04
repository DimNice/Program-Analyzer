// !test number_overflow

#include <iostream>  // without
using namespace std;

int main()
{
    int a = 0;
    int d = 454;
    for (int i = 0; i < 1000; i++)
    {
        a += 1;
    }
    return 0;
}