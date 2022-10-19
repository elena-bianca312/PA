#include <cmath>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    char inFilename[50] = "valley.in";
    ifstream fin;
    fin.open(inFilename);
    if (!fin.is_open()) {
        exit(EXIT_FAILURE);
    }

    int i;
    int n;
    vector<int> v;
    fin >> n;
    int x;
    fin >> x;
    cout << x << " ";
    v.push_back(x);
    int minVal = x, minPos = 0;

    for (i = 1; i < n; i++) {
        fin >> x;
        v.push_back(x);
        if (x <= minVal) {
            minVal = x;
            minPos = i;
        }
    }
    fin.close();

    if (minPos == 0) minPos = 1;
    if (minPos == n - 1) minPos = n - 2;

    int peak1 = v[0], peak2 = v[n - 1];
    long minPower = 0;

    for (i = 1; i <= minPos; i++) {
        if (v[i] > peak1) {
        minPower += v[i] - peak1;
        v[i] = peak1;
        } else {
            peak1 = v[i];
        }
    }

    for (i = n - 2; i >= minPos; i--) {
        if (v[i] > peak2) {
        minPower += v[i] - peak2;
        v[i] = peak2;
        } else {
            peak2 = v[i];
        }
    }

    char outFilename[50] = "valley.out";
    ofstream fout;
    fout.open(outFilename);
    fout << minPower;
    fout.close();

    return 0;
}
