#include <iostream>
#include <vector>

using namespace std;

//TODO: create either BFS or DFS

int main() {
    int n, m;
    if (scanf("%d %d", &n, &m) == EOF)
        return 0;

    //TODO: create graph

    for (int i = 0; i < m; ++i) {
        int x, y;
        if (scanf("%d %d", &x, &y) == EOF)
            return 0;
        //TODO: add to graph
    }

    int maxJumps = 0;
    //TODO: calculate maxJumps

    printf("%d\n", maxJumps);

    return 0;
}
