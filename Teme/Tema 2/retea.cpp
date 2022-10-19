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
#include <stack>
using namespace std;


void DFSUtil(int v, bool visited[], int *p, list<int> *adj) {
	visited[v] = true;
    (*p)++;

	list<int>::iterator i;
	for (i = adj[v].begin(); i != adj[v].end(); ++i)
		if (!visited[*i])
			DFSUtil(*i, visited, p, adj);
}

list<int> *getTranspose(list<int> *adj, int V) {
    list<int> *newadj = new list<int>[V];
	for (int v = 0; v < V; v++) {
		list<int>::iterator i;
		for (i = adj[v].begin(); i != adj[v].end(); ++i) {
			newadj[*i].push_back(v);
		}
	}
	return newadj;
}

void addEdge(list<int> *adj, int v, int w) {
	adj[v].push_back(w);
    adj[w].push_back(v);
}

void delEdge(list<int> *adj, int V, int u) {
    adj[u].erase(adj[u].begin(), adj[u].end());
}

void fillOrder(int v, bool visited[], stack<int> &Stack, list<int> *adj) {
	visited[v] = true;

	list<int>::iterator i;
	for(i = adj[v].begin(); i != adj[v].end(); ++i)
		if(!visited[*i])
			fillOrder(*i, visited, Stack, adj);

	Stack.push(v);
}

int printSCCs(list<int> *adj, int V) {
	stack<int> Stack;

	bool *visited = new bool[V];
	for(int i = 0; i < V; i++)
		visited[i] = false;

	for(int i = 0; i < V; i++)
		if(visited[i] == false)
			fillOrder(i, visited, Stack, adj);

	list<int> *newadj = getTranspose(adj, V);

	for(int i = 0; i < V; i++)
		visited[i] = false;

    int p, sum = 0;
	while (Stack.empty() == false) {
		int v = Stack.top();
		Stack.pop();
		if (visited[v] == false) {
            p = 0;
			DFSUtil(v, visited, &p, newadj);
            sum += (V - p) * p;
		}
	}
    return sum;
}

int main() {
    char inFilename[50] = "retea.in";
    ifstream fin;
    fin.open(inFilename);
    if (!fin.is_open()) {
        exit(EXIT_FAILURE);
    }

    int n, m, i, j;
    fin >> n >> m;

    list<int> *adj = new list<int>[n];
    list<int> *copy = new list<int>[n];

    int x, y;
    for (i = 0; i < m; i++) {
        fin >> x >> y;
        addEdge(adj, x - 1, y - 1);
    }

    for (i = 0; i < n; i++) {
        copy[i] = adj[i];
    }

    int ans;

    char outFilename[50] = "retea.out";
    ofstream fout;
    fout.open(outFilename);

    for (i = 0; i < n; i++) {
        delEdge(adj, n, i);
        ans = printSCCs(adj, n);
        fout << ans << endl;
        adj[i] = copy[i];
    }

    fout.close();

    return 0;
}
