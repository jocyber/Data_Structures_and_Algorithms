#include <vector>
#include <iostream>

using std::cout;
using std::vector;

//greedy approach to solving the street lights problem
int min_street_lights(const int &n, int r) { // O(n)
    int count = 0;

    for(int i = 0; i < n; ++i) {
        if(i == r) {
            r = (r << 1);
            count++;
        }
    }

    return count;
}

int main(int argc, char *argv[])
{
    int r = 3;
    int n = (r << 3) + r;

    cout << min_street_lights(n, r) << '\n';
    return 0;
}