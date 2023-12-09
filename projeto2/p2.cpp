#include <iostream>
#include <vector>
#include <stack>

using namespace std;

int main() {
    int n, m;
    if (scanf("%d %d", &n, &m) == EOF)
        return 0;

    vector<vector<int>> G(n + 1);

    for (int i = 0; i < m; ++i) {
        int x, y;
        if (scanf("%d %d", &x, &y) == EOF)
            return 0;
        G[x].push_back(y);
    }

    //int maxJumps = get_jumps(G);

    printf("%d\n", maxJumps);

    return 0;
}
