#include <iostream>
#include <time.h>
#include <vector>

using std::cout;
using std::vector;

void swap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

//fisher-yates algorithm
void shuffleList(vector<int> &list) {
    for(int i = 0; i < list.size() - 1; ++i) {
        int random = rand() % (list.size() - i) + i;
        swap(list[i], list[random]);
    }
}

//O(n)
bool checkSorted(vector<int> &list) {
    for(int i = 0; i < list.size() - 1; ++i) {
        if(list[i] > list[i + 1])
            return false;
    }

    return true;
}

//runs in O(n * n!) time because there are n! permutations of a list
void bogoSort(vector<int> &list) {
    while(!checkSorted(list))
        shuffleList(list);
}

int main()
{
    srand(time(NULL));
    vector<int> list = {2,8,9,1,11,13,4,5,8,12};

    bogoSort(list);

    for(const int &x : list) 
        cout << x << ' ';

    cout << '\n';

    return 0;
}
