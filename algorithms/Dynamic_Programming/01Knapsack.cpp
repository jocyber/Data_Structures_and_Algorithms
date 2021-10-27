#include <iostream>
#include <algorithm>
#include <vector>

using std::vector;

void Knapsack(vector<vector<int>> &table, const vector<int> &s, const vector<int> &vals) 
{
    for(int i = 1; i < table.size(); i++) {
        for(int j = 1; j < table[i].size(); j++) {
            int decr_knapsack = j - s[i - 1];
            int second = table[i - 1][j];

            if(decr_knapsack >= 0) 
                table[i][j] = std::max(vals[i - 1] + table[i - 1][decr_knapsack], second);
            else
                table[i][j] = second;
        }
    }
}

int main()
{
    int B = 10;
    int n = 4;

    vector<int> s = {2, 3, 5, 3};
    vector<int> vals = {10, 40, 40, 50};

    vector<vector<int>> table(n + 1, vector<int> (B+1, 0));

    Knapsack(table, s, vals);

    //print knapsack table
    for(int i = 0; i < table.size(); i++) {
        for(int j = 0; j < table[i].size(); j++) {
            std::cout << table[i][j] << " ";
        }
        std::cout << '\n';
    }
    

    return 0;
}