#include <cmath>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <algorithm>
using namespace std;

struct calculator {
    int power;
    int cost;
};

bool compareByPower(const calculator &a, const calculator &b) {
    return a.power < b.power;
}

int main() {
    char inFilename[50] = "crypto.in";
    ifstream fin;
    fin.open(inFilename);
    if (!fin.is_open()) {
        exit(EXIT_FAILURE);
    }

    int i;
    int n, b;
    vector<calculator> calc;
    fin >> n >> b;
    int power, cost;
    for (i = 0; i < n; i++) {
        fin >> power;
        fin >> cost;
        calc.push_back({power, cost});
    }
    fin.close();

    std::sort(calc.begin(), calc.end(), compareByPower);

    int minPower = calc[0].power;
    int sum = calc[0].cost;
    int k = 1;
    while (b >= 0) {
        if (calc[k].power <= minPower && k <= calc.size()) {
            sum += calc[k].cost;
            k++;
        } else {
            if (b >= sum * (calc[k].power - minPower) &&
                    sum * (calc[k].power - minPower) >= 0 && k <= calc.size()) {
                b -= sum * (calc[k].power - minPower);
                minPower = calc[k].power;
            } else {
                minPower += floor(b / sum);
                break;
            }
        }
    }

    char outFilename[50] = "crypto.out";
    ofstream fout;
    fout.open(outFilename);
    fout << minPower;
    fout.close();

    return 0;
}
