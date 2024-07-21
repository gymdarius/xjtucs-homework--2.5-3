#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int main()
{
    int n;
    cin >> n;
    if (n >= 1 && n <= 6)
        std::cout << "water";
    else
        std::cout << "dry";
    return 0;
}