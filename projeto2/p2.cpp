#include <cstdio>
#include <vector>
#include <stack>
#include <unordered_map>

using namespace std;

const int UNVISITED = -1;


int dfs(const vector<vector<int>>& graph, vector<int>& ids, vector<int>& low, vector<int>& sccs, vector<bool>& visited, stack<int>& nodeStack, int& id) {
  int n = graph.size();
  int sccCount = 0;

  for (int start = 0; start < n; ++start) {
    if (ids[start] == UNVISITED) {
      nodeStack.push(start);

      while (!nodeStack.empty()) {
        int at = nodeStack.top();

        if (!visited[at]) {
          // White node
          ids[at] = low[at] = id++;
          visited[at] = true;
        } else {
          // Gray node
          for (int i = 0; i < (int) graph[at].size(); ++i) {
            int to = graph[at][i];
            if (to >= n) {
              // Ignore nodes with indices greater than or equal to n
              continue;
            }
            if (ids[to] == UNVISITED) {
              nodeStack.push(to);
              break;
            }
            if (visited[to]) {
              low[at] = min(low[at], low[to]);
            }
          }

          if (ids[at] == low[at]) {
            // Black node
            while (!nodeStack.empty()) {
              int node = nodeStack.top();
              nodeStack.pop();
              visited[node] = false;
              sccs[node] = sccCount;
              if (node == at) {
                break;
              }
            }
            sccCount++;
          }
        }
      }
    }
  }
  return sccCount;
}

int tarjanSccSolver(const vector<vector<int>>& graph, vector<int>& sccs) {
  int n = graph.size();
  vector<int> ids(n, UNVISITED);
  vector<int> low(n, 0);
  vector<bool> visited(n, false);
  stack<int> stack;
  int id = 0;
  int sccCount = 0;

  sccCount = dfs(graph, ids, low, sccs, visited, stack, id);

  return sccCount;
}


vector<vector<int>> buildSCCGraph(const vector<vector<int>>& graph, const vector<int>& sccs, int sccCount) {
  vector<vector<int>> sccGraph(sccCount);

  for (size_t u = 0; u < graph.size(); ++u) {
    for (int v : graph[u]) {
      if (v >= (int)graph.size() || u >= sccs.size() || v >= (int)sccs.size()) {
        continue;
      }
      if (sccs[u] != sccs[v]) {
        sccGraph[sccs[u]].push_back(sccs[v]);
      }
    }
  }
  return sccGraph;
}

int findLongestRoute(const vector<vector<int>>& sccGraph, int source, vector<int>& dp) {
  if (source >= (int)sccGraph.size() || dp[source] != -1) {
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
  if (scanf("%d %d", &vertices, &edges) == EOF || vertices <= 0) {
    printf("Invalid input.\n");
    return 1;
  }

  vector<vector<int>> graph(vertices);

  for (int i = 0; i < edges; ++i) {
    int u, v;
    if (scanf("%d %d", &u, &v) == EOF || u <= 0 || v <= 0 || u > vertices || v > vertices) {
      printf("Invalid input.\n");
      return 1;
    }
    graph[u - 1].push_back(v - 1); // Adjust to 0-based indexing
  }

  vector<int> sccs(vertices, 0);
  int sccCount = tarjanSccSolver(graph, sccs);

  // Build the new graph of SCCs
  vector<vector<int>> sccGraph = buildSCCGraph(graph, sccs, sccCount);

  vector<int> dp(sccCount, -1);
  int longestRoute = 0;

  for (int i = 0; i < sccCount; ++i) {
    longestRoute = max(longestRoute, findLongestRoute(sccGraph, i, dp));
  }

  printf("%d\n", longestRoute);

  return 0;
}