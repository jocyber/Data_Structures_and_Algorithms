#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;

vector<vector<int>> short_matrix_multiply(vector<vector<int>> matrix1, vector<vector<int>> matrix2);
vector<vector<int>> add_matrix(vector<vector<int>> m1, vector<vector<int>> m2);
vector<vector<int>> strassen_matrix_multiply(vector<vector<int>> matrix1, vector<vector<int>> matrix2);

vector<vector<int>> make_quadrant1(vector<vector<int>> temp);
vector<vector<int>> make_quadrant2(vector<vector<int>> temp);
vector<vector<int>> make_quadrant3(vector<vector<int>> temp);
vector<vector<int>> make_quadrant4(vector<vector<int>> temp);

int main(int argc, char *argv[]) 
{
    vector<vector<int>> matrix1 = {
        {1, 2, 3, 4, 5, 6, 7, 8},
        {1, 2, 3, 4, 5, 6, 7, 8},
        {1, 2, 3, 4, 5, 6, 7, 8},
        {1, 2, 3, 4, 5, 6, 7, 8},
        {1, 2, 3, 4, 5, 6, 7, 8},
        {1, 2, 3, 4, 5, 6, 7, 8},
        {1, 2, 3, 4, 5, 6, 7, 8},
        {1, 2, 3, 4, 5, 6, 7, 8}
    };

    vector<vector<int>> matrix2 = {
        {1, 2, 3, 4, 5, 6, 7, 8},
        {1, 2, 3, 4, 5, 6, 7, 8},
        {1, 2, 3, 4, 5, 6, 7, 8},
        {1, 2, 3, 4, 5, 6, 7, 8},
        {1, 2, 3, 4, 5, 6, 7, 8},
        {1, 2, 3, 4, 5, 6, 7, 8},
        {1, 2, 3, 4, 5, 6, 7, 8},
        {1, 2, 3, 4, 5, 6, 7, 8}
    };
    
    vector<vector<int>> result = strassen_matrix_multiply(matrix1, matrix2);

    for(int i = 0; i < result.size(); i++) {
        for(int j = 0; j < result[i].size(); j++) {
            cout << result[i][j] << " ";
        }
        cout << endl;
    }

    return EXIT_SUCCESS;
}

/////////////////main matrix multiplication algorithm using divide-and-conquer approach
vector<vector<int>> strassen_matrix_multiply(vector<vector<int>> matrix1, vector<vector<int>> matrix2) {
    if(matrix1.size() == 2 && matrix2.size() == 2) {
        return short_matrix_multiply(matrix1, matrix2);
    }
    
    vector<vector<int>> a11 = make_quadrant1(matrix1);
    vector<vector<int>> b11 = make_quadrant1(matrix2);
    vector<vector<int>> a12 = make_quadrant2(matrix1);
    vector<vector<int>> b12 = make_quadrant2(matrix2);
    vector<vector<int>> a21 = make_quadrant3(matrix1);
    vector<vector<int>> b21 = make_quadrant3(matrix2);
    vector<vector<int>> a22 = make_quadrant4(matrix1);
    vector<vector<int>> b22 = make_quadrant4(matrix2);

    vector<vector<int>> c1 = add_matrix(strassen_matrix_multiply(a11, b11), strassen_matrix_multiply(a12, b21));
    vector<vector<int>> c2 = add_matrix(strassen_matrix_multiply(a11, b12), strassen_matrix_multiply(a12, b22));
    vector<vector<int>> c3 = add_matrix(strassen_matrix_multiply(a21, b11), strassen_matrix_multiply(a22, b21));
    vector<vector<int>> c4 = add_matrix(strassen_matrix_multiply(a21, b12), strassen_matrix_multiply(a22, b22));

    vector<vector<int>> result (matrix1.size(), vector<int>(matrix1[0].size(), 0));

    //quadrant 1
    for(int i = 0; i < c1.size(); i++) {
        for(int j = 0; j < c1[0].size(); j++) {
            result[i][j] = c1[i][j];
        }
    }

    //quadrant 2
    for(int i = 0; i < c2.size(); i++) {
        for(int j = c1[0].size(); j < c1[0].size() + c2[0].size(); j++) {
            result[i][j] = c2[i][j - c1[0].size()];
        }
    }

    //quadrant 3
    for(int i = c1.size(); i < c1.size() + c3.size(); i++) {
        for(int j = 0; j < c3[0].size(); j++) {
            result[i][j] = c3[i - c1.size()][j];
        }
    }

    //quadrant 4
    for(int i = c1.size(); i < c1.size() + c4.size(); i++) {
        for(int j = c1[0].size(); j < c1[0].size() + c4[0].size(); j++) {
            result[i][j] = c4[i - c1.size()][j - c1[0].size()];
        }
    }

    return result;
}
////////////////////////////////////////////////////////////////////////////////

vector<vector<int>> short_matrix_multiply(vector<vector<int>> matrix1, vector<vector<int>> matrix2) {
    vector<vector<int>> temp(2, vector<int>(2,0));

    temp[0][0] = (matrix1[0][0] * matrix2[0][0]) + (matrix1[0][1] * matrix2[1][0]);
    temp[0][1] = (matrix1[0][0] * matrix2[0][1]) + (matrix1[0][1] * matrix2[1][1]);
    temp[1][0] = (matrix1[1][0] * matrix2[0][0]) + (matrix1[1][1] * matrix2[1][0]);
    temp[1][1] = (matrix1[1][0] * matrix2[0][1]) + (matrix1[1][1] * matrix2[1][1]);

    return temp;
}

vector<vector<int>> make_quadrant1(vector<vector<int>> temp) {
    int height = temp.size() / 2;
    int width = temp[0].size() / 2;

    vector<vector<int>> result(height, vector<int>(width, 0));

    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {
            result[i][j] = temp[i][j];
        }
    }

    return result;
}

vector<vector<int>> make_quadrant3(vector<vector<int>> temp) {
    int height = temp.size() / 2;
    int width = temp[0].size() / 2;

    vector<vector<int>> result(height, vector<int>(width, 0));

    for(int i = height; i < temp.size(); i++) {
        for(int j = 0; j < width; j++) {
            result[i - height][j] = temp[i][j];
        }
    }

    return result;
}

vector<vector<int>> make_quadrant2(vector<vector<int>> temp) {
    int height = temp.size() / 2;
    int width = temp[0].size() / 2;

    vector<vector<int>> result(height, vector<int>(width, 0));

    for(int i = 0; i < height; i++) {
        for(int j = width; j < temp[0].size(); j++) {
            result[i][j - width] = temp[i][j];
        }
    }

    return result;
}

vector<vector<int>> make_quadrant4(vector<vector<int>> temp) {
    int height = temp.size() / 2;
    int width = temp[0].size() / 2;

    vector<vector<int>> result(height, vector<int>(width, 0));

    for(int i = height; i < temp.size(); i++) {
        for(int j = width; j < temp[0].size(); j++) {
            result[i - height][j - width] = temp[i][j];
        }
    }

    return result;
}

vector<vector<int>> add_matrix(vector<vector<int>> m1, vector<vector<int>> m2) {
    vector<vector<int>> temp(m1.size(), vector<int>(m1[0].size(),0));

    for(int i = 0; i < temp.size(); i++) {
        for(int j = 0; j < temp[0].size(); j++) {
            temp[i][j] = m1[i][j] + m2[i][j];
        }
    }

    return temp;
}
