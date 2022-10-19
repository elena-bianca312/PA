#include <cmath>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <set>
#include <iterator>
#include <queue>
#include <list>
using namespace std;

void combinationUtil(set<vector<int>> &comb, int limit, int r,
                    int index, int *data, int i) {
    if (index == r) {
        vector<int> tuple;
        for (int j = 0; j < r; j++) {
            tuple.push_back(data[j]);
        }
        comb.insert(tuple);
        return;
    }

    if (i >= limit)
        return;

    data[index] = i + 1;
    combinationUtil(comb, limit, r, index + 1, data, i + 1);
    combinationUtil(comb, limit, r, index, data, i + 1);
}

void combination(set<vector<int>> &comb, int limit, int r) {
    int *data = (int *) malloc(r * sizeof(int));
    data[0] = 1;
    combinationUtil(comb, limit, r, 1, data, 1);
}

void print_subsets(set<int> &sums, vector<int> s, int *sequence, int size) {
    int sum = 0;
    for (int i = 0; i < size; i++) {
        if (sequence[i] != 0) {
            sum += s[sequence[i] - 1];
        }
    }
    sums.insert(sum);
}

void subsets(set<int> &sums, vector<int> s, int index,
            int *sequence, int size) {
    if (index >= size) {
        print_subsets(sums, s, sequence, size);
    } else {
        for (int i = 0; i < s.size() + 1; i++) {
            sequence[index] = i;
            subsets(sums, s, index + 1, sequence, size);
        }
    }
}


int main() {
    char inFilename[50] = "lego.in";
    ifstream fin;
    fin.open(inFilename);
    if (!fin.is_open()) {
        exit(EXIT_FAILURE);
    }

    /* k - max range / upper limit
       n - number of different pieces
       t - max number of used pieces */

    int k, n, t;
    fin >> k >> n >> t;
    cout << k << " " << n << " " << t << endl;

    /* Generate all combination of n numbers in range [1, k].
       Store them in set of vectors comb1 to avoid duplicates */

    set<vector<int>> comb1;
    combination(comb1, k, n);

    int i, j;
    int max = 0;
    vector<int> final;

    set<int> sums;
    int *sequence = (int *) malloc(t * sizeof(int));

    /* For each combination, generate all possible sums and find
       max len of consecutive sums using function subsets */
    /* The sequence of consecutive numbers might not start from 0! 
       -> special case */

    for (auto vect : comb1) {
        subsets(sums, vect, 0, sequence, t);
        sums.erase(0);
        int cnt = 0, length = 0, max_len = 0;
        for (auto i : sums) {
            if (cnt == i) {
                length++;
                cnt++;
            } else {
                if (length > max_len) {
                    max_len = length;
                }
                length = 1;
                cnt = i + 1;
            }
        }
        if (length > max_len) {
            max_len = length;
        }
        if (max_len > max) {
            max = max_len;
            final = vect;
        }
        sums.clear();
    }

    char outFilename[50] = "lego.out";
    ofstream fout;
    fout.open(outFilename);
    fout << max << endl;
    for (i = 0; i < final.size(); i++) {
        fout << final[i] << " ";
    }
    fout.close();

    return 0;
}
