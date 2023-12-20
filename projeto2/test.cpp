#include <cstdio>
#include <vector>
#include <stack>
#include <unordered_map>

using namespace std;

const int UNVISITED = -1;

void dfs(int start, const vector<vector<int>>& graph, vector<int>& ids, vector<int>& low, vector<int>& sccs, vector<bool>& onStack, stack<int>& stackOriginal, int& id, int& sccCount) {
  stack<int> dfsStack;
  dfsStack.push(start);

  while (!dfsStack.empty()) {
    int at = dfsStack.top();
    if (ids[at] == UNVISITED) {
      ids[at] = low[at] = id++;
      stackOriginal.push(at);
      onStack[at] = true;
    }

    bool pushed = false;
    for (int to : graph[at]) {
      if (ids[to] == UNVISITED) {
        dfsStack.push(to);
        pushed = true;
        break;
      } else if (onStack[to]) {
        low[at] = min(low[at], low[to]);
      }
    }

    if (!pushed) {
      if (ids[at] == low[at]) {
        while (!stackOriginal.empty()) {
          int node = stackOriginal.top();
          stackOriginal.pop();
          onStack[node] = false;
          sccs[node] = sccCount;
          if (node == at) {
              break;
          }
        }
        ++sccCount;
      }
      dfsStack.pop();
    }
  }
}

int tarjanSccSolver(const vector<vector<int>>& graph, vector<int>& sccs) {
  int n = graph.size();
  vector<int> ids(n, UNVISITED);
  vector<int> low(n, 0);
  vector<bool> visited(n, false);
  stack<int> stackOriginal;
  int id = 0;
  int sccCount = 0;

  for (int i = 0; i < n; i++) {
    if (ids[i] == UNVISITED) {
      dfs(i, graph, ids, low, sccs, visited, stackOriginal, id, sccCount);
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
  if (scanf("%d %d", &vertices, &edges) == EOF) 
    return 0;

  vector<vector<int>> graph(vertices);

  for (int i = 0; i < edges; ++i) {
    int u, v;
    if (scanf("%d %d", &u, &v) == EOF) 
      return 0;
    graph[u - 1].push_back(v - 1); // Adjust to 0-based indexing
  }

  vector<int> sccs(vertices, 0);
  int sccCount = tarjanSccSolver(graph, sccs);

  vector<vector<int>> sccGraph = buildSCCGraph(graph, sccs, sccCount);

  vector<int> dp(sccCount, -1);
  int longestRoute = 0;

  for (int i = 0; i < sccCount; ++i) {
      longestRoute = max(longestRoute, findLongestRoute(sccGraph, i, dp));
  }

  printf("%d\n", longestRoute);

  return 0;
}
