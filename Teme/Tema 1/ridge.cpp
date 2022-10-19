#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

#define MAX_NUMBER 9223372036854775807

struct mountain {
    int height;
    int cost;
};

int main() {
    char inFilename[50] = "ridge.in";
    ifstream fin;
    fin.open(inFilename);
    if (!fin.is_open()) {
        exit(EXIT_FAILURE);
    }

    int i;
    int n;
    vector<mountain> v;
    fin >> n;
    int height, cost;
    v.push_back({0, 0});
    for (i = 0; i < n; i++) {
        fin >> height;
        fin >> cost;
        v.push_back({height, cost});
    }
    fin.close();

    long long **table = (long long **) calloc((n + 1), sizeof(long long *));
    for (i = 0; i < n + 1; i++) {
        table[i] = (long long *) calloc(3, sizeof(long long));
    }

    long long a, b, c;
    for (i = 1; i < n + 1; i++) {
        a = table[i - 1][0];
        b = table[i - 1][1];
        c = table[i - 1][2];
        if (v[i].height != v[i - 1].height) {
            table[i][0] = min(a, min(b, c));
            table[i][1] = min(a, min(b, c)) + v[i].cost;
            table[i][2] = min(a, min(b, c)) + v[i].cost * 2;

            if (v[i].height - v[i - 1].height == 1) {
                table[i][0] = min(a, min(b, c));
                table[i][1] = min(b, c) + v[i].cost;
                table[i][2] = min(a, c) + v[i].cost * 2;
            }
            if (v[i].height - v[i - 1].height == 2) {
                table[i][0] = min(a, min(b, c));
                table[i][1] = min(a, min(b, c)) + v[i].cost;
                table[i][2] = min(b, c) + v[i].cost * 2;
            }
            if (v[i].height - v[i - 1].height == -1) {
                table[i][0] = min(a, c);
                table[i][1] = min(a, b) + v[i].cost;
                table[i][2] = min(a, min(b, c)) + v[i].cost * 2;
            }
            if (v[i].height - v[i - 1].height == -2) {
                table[i][0] = min(a, b);
                table[i][1] = min(a, min(b, c)) + v[i].cost;
                table[i][2] = min(a, min(b, c)) + v[i].cost * 2;
            }
        } else {
            table[i][0] = min(b, c);
            table[i][1] = min(a, c) + v[i].cost;
            table[i][2] = min(a, b) + v[i].cost * 2;
        }

        if (v[i].height == 0) {
            table[i][1] = MAX_NUMBER;
            table[i][2] = MAX_NUMBER;
        }
        if (v[i].height == 1) {
            table[i][2] = MAX_NUMBER;
        }
    }

    char outFilename[50] = "ridge.out";
    ofstream fout;
    fout.open(outFilename);
    fout << min(table[n][0], min(table[n][1], table[n][2]));
    fout.close();

    return 0;
}
