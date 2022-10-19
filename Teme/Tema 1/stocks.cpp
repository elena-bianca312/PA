#include <cmath>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <algorithm>
using namespace std;

struct act {
    int currentValue;
    int minValue;
    int maxValue;
};

int main() {
    char inFilename[50] = "stocks.in";
    ifstream fin;
    fin.open(inFilename);
    if (!fin.is_open()) {
        exit(EXIT_FAILURE);
    }

    int i, j, k;
    int n, b, l;
    vector<act> v;
    fin >> n >> b >> l;
    v.push_back({0, 0, 0});
    int curr, min, max;
    for (i = 0; i < n; i++) {
        fin >> curr;
        fin >> min;
        fin >> max;
        v.push_back({curr, min, max});
    }
    fin.close();

    int ***table = (int ***) calloc((n + 1), sizeof(int **));

    for (i = 0; i < n + 1; i++) {
        table[i] = (int **) calloc((b + 1), sizeof(int *));
        for (j = 0; j < b + 1; j++) {
            table[i][j] = (int *) calloc((l + 1), sizeof(int));
        }
    }

    for (i = 1; i < n + 1; i++) {
        for (j = 1; j < b + 1; j++) {
            for (k = 1; k < l + 1; k ++) {
                if ((v[i].currentValue <= j) &&
                    ((v[i].currentValue - v[i].minValue) <= k)) {
                    int p = table[i - 1]
                                 [j - v[i].currentValue]
                                 [k - v[i].currentValue + v[i].minValue]
                            + v[i].maxValue - v[i].currentValue;

                    table[i][j][k] = std::max(table[i - 1][j][k], p);
                } else {
                    table[i][j][k] = table[i - 1][j][k];
                }
            }
        }
    }

    char outFilename[50] = "stocks.out";
    ofstream fout;
    fout.open(outFilename);
    fout << table[n][b][l];
    fout.close();

    return 0;
}
