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

#define INF_MAX 99999

struct Node {
    int x, y, dist;
};

int row[] = { -1, 1, 0,  0 };
int col[] = { 0,  0, 1, -1 };

bool isValid(int **matrix, bool **visited, int row, int col, int N, int M) {
    return (row >= 0) && (row < N) && (col >= 0) && (col < M) &&
        !visited[row][col];
}

int BFSmatrix(int **matrix, int posx, int posy, int n, int m) {
    int cnt;
    bool **visited = (bool **) calloc(n, sizeof(bool *));
    for (cnt = 0; cnt < n; cnt++) {
        visited[cnt] = (bool *) calloc(m, sizeof(bool));
    }

    queue<Node> q;
    visited[posx][posy] = true;
    q.push({posx, posy, 0});

    int min_dist = INF_MAX;
    while (!q.empty()) {
        Node node = q.front();
        q.pop();

        int i = node.x, j = node.y, dist = node.dist;

        if (i == 0 || i == n - 1 || j == 0 || j == m - 1) {
            min_dist = dist;
            break;
        }

        int start = 0, finish = 0;
        switch (matrix[i][j]) {
        case 3:
            start = 0; finish = 4;
            break;
        case 2:
            start = 0; finish = 2;
            break;
        case 1:
            start = 2; finish = 4;
            break;
        default:
            break;
        }

        /* Check for all possible movements */
        for (cnt = start; cnt < finish; cnt++) {
            if (isValid(matrix, visited, i + row[cnt], j + col[cnt], n, m)) {
                visited[i + row[cnt]][j + col[cnt]] = true;
                q.push({i + row[cnt], j + col[cnt], dist + 1});
            }
        }
    }

    for (cnt = 0; cnt < n; cnt++) {
        free(visited[cnt]);
    }
    free(visited);

    if (min_dist != INF_MAX) {
        return min_dist;
    } else {
        return -1;
    }
}


int main() {
    char inFilename[50] = "poduri.in";
    ifstream fin;
    fin.open(inFilename);
    if (!fin.is_open()) {
        exit(EXIT_FAILURE);
    }

    int i, j;
    /* 2 nr nat n si m */
    int n, m;
    fin >> n >> m;
    /* Coordonatele podului initial */
    int x, y;
    fin >> x >> y;
    char c;

    /* Adj matrix */
    int **matrix = (int **) calloc((n + 2), sizeof(int *));
    for (i = 0; i < (n + 2); i++) {
        matrix[i] = (int *) calloc((m + 2), sizeof(int));
    }

    /* Matricea cu poduri */
    for (i = 1; i <= n; i++) {
        for (j = 1; j <= m; j++) {
            fin >> c;
            switch (c) {
            case 'D':
                matrix[i][j] = 3;
                break;
            case 'V':
                matrix[i][j] = 2;
                break;
            case 'O':
                matrix[i][j] = 1;
                break;
            case '.':
                break;
            default:
                break;
            }
        }
    }

    int ans = BFSmatrix(matrix, x, y, n + 2, m + 2);

    for (i = 0; i < (n + 2); i++) {
        free(matrix[i]);
    }
    free(matrix);

    char outFilename[50] = "poduri.out";
    ofstream fout;
    fout.open(outFilename);
    fout << ans;
    fout.close();

    return 0;
}
