#include <cstdio>
#include <vector>
#include <stack>
#include <unordered_map>

using namespace std;

const int UNVISITED = -1;

void dfs(int start, const vector<vector<int>>& graph, vector<int>& ids, vector<int>& low, vector<int>& sccs, vector<bool>& visited, stack<int>& nodeStack, int& id, int& sccCount) {
    stack<pair<int, int>> dfsStack;
    dfsStack.push({start, 0});

    while (!dfsStack.empty()) {
        int at = dfsStack.top().first;
        int state = dfsStack.top().second;
        dfsStack.pop();

        if (state == 0) {
            ids[at] = low[at] = id++;
            nodeStack.push(at);
            visited[at] = true;
        }

        for (; state < (int) graph[at].size(); ++state) {
            int to = graph[at][state];
            if (ids[to] == UNVISITED) {
                dfsStack.push({at, state + 1});
                dfsStack.push({to, 0});
                break;
            }
            if (visited[to]) {
                low[at] = min(low[at], low[to]);
            }
        }

        if (state == (int) graph[at].size()) {
            if (ids[at] == low[at]) {
                while (true) {
                    int node = nodeStack.top();
                    nodeStack.pop();
                    visited[node] = false;
                    sccs[node] = sccCount;
                    if (node == at) break;
                }
                sccCount++;
            }
        }
    }
}

int tarjanSccSolver(const vector<vector<int>>& graph, vector<int>& sccs) {
    int n = graph.size();
    vector<int> ids(n, UNVISITED);
    vector<int> low(n, 0);
    vector<bool> visited(n, false);
    stack<int> nodeStack;
    int id = 0;
    int sccCount = 0;

    for (int i = 0; i < n; i++) {
        if (ids[i] == UNVISITED) {
            dfs(i, graph, ids, low, sccs, visited, nodeStack, id, sccCount);
        }
    }

    return sccCount;
}

vector<vector<int>> buildSCCGraph(const vector<vector<int>>& graph, const vector<int>& sccs, int sccCount) {
  vector<vector<int>> sccGraph(sccCount);

  for (std::vector<int>::size_type u = 0; u < graph.size(); ++u) {
    for (std::vector<int>::size_type v : graph[u]) {
      if (sccs[u] != sccs[v]) {
          sccGraph[sccs[u]].push_back(sccs[v]);
      }
    }
  }
  return sccGraph;
}

int findLongestRoute(const vector<vector<int>>& sccGraph, int source, vector<int>& dp) {
    if (dp[source] != -1) {
        return dp[source];
    }

    int longestRoute = 0;

    for (int neighbor : sccGraph[source]) {
        longestRoute = max(longestRoute, 1 + findLongestRoute(sccGraph, neighbor, dp));
    }

    dp[source] = longestRoute;
    return longestRoute;
}

int main() {
  int vertices, edges;
  int ch = scanf("%d %d", &vertices, &edges);
  if (ch == EOF || vertices <= 0) {
    return 0;
  }

  vector<vector<int>> graph(vertices);

  for (int i = 0; i < edges; ++i) {
    int u, v;
    int check = scanf("%d %d", &u, &v);
    if (check == EOF) {
      break;
    }
    graph[u - 1].push_back(v - 1); // Adjust to 0-based indexing
  }

  vector<int> sccs(vertices, 0);
  int sccCount = tarjanSccSolver(graph, sccs);

  // Build the new graph of SCCs
  vector<vector<int>> sccGraph = buildSCCGraph(graph, sccs, sccCount);

  //printf("Number of Strongly Connected Components: %d\n", sccCount);

  // Print the new graph of SCCs
  //for (int i = 0; i < sccGraph.size(); ++i) {
    //printf("SCC %d: ", i);
    //for (int neighbor : sccGraph[i]) {
      //printf("%d ", neighbor);
    //}
    //printf("\n");
  //}

  vector<int> dp(sccCount, -1);
  int longestRoute = 0;

  for (int i = 0; i < sccCount; ++i) {
      longestRoute = max(longestRoute, findLongestRoute(sccGraph, i, dp));
  }

  printf("%d\n", longestRoute);

  return 0;
}
