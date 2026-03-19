## Bicycle Paths Problem Statement: 
For every vertex $v$ in a directed graph, calculate the number of reachable vertices, given the **"fairness" constraint**: If there is no path from $v$ to $u$, then there is at most one path from $u$ to $v$.

## Soultion O(n + m): 
The solution uses Kosaraju's algorithm to condense the directed graph into Strongly Connected Components (SCCs), effectively transforming it into a Directed Acyclic Graph (DAG). It then calculates reachability for each component using Dynamic Programming (DP) on the DAG by traversing it in reverse topological order.


```cpp
//Tomasz Uram
#include <bits/stdc++.h>
using namespace std;

const int NAX = 50'000 + 17;
int n, m, scc_cnt;
vector<int> G[NAX], RG[NAX], DAG[NAX];
int node_id[NAX], scc_size[NAX], id_to_ans[NAX], dp[NAX];
bool vis[NAX];

vector<int> order;
void find_order(int v) {
  vis[v] = true;
  for (auto u : G[v]) {
    if (!vis[u]) {
      find_order(u);
    }
  }
  order.push_back(v);
}

void dfs(int v, int id) {
  vis[v] = true;
  node_id[v] = id;
  scc_size[id]++;
  for (auto u : RG[v]) {
    if (!vis[u]) {
      dfs(u, id);
    }
  }
}

void create_DAG() {
  for (int v = 1; v <= n; v++) {
    for (auto u : G[v]) {
      if (node_id[v] != node_id[u]) {
        DAG[node_id[v]].push_back(node_id[u]);
      }
    }
  }
}

void solve() {
  fill(vis, vis + NAX, false);
  for (int i = 1; i <= n; i++) {
    if (!vis[i]) {
      find_order(i);
    }
  }
  reverse(order.begin(), order.end());
  fill(vis, vis + NAX, false);
  for (auto v : order) {
    if (!vis[v]) {
      dfs(v, ++scc_cnt);
    }
  }
  create_DAG();
}

vector<int> order1;
void find_order1(int v) {
  vis[v] = true;
  for (auto u : DAG[v]) {
    if (!vis[u]) {
      find_order1(u);
    }
  }
  order1.push_back(v);
}

void calc_ans(int v) {
  vis[v] = true;
  dp[v] = scc_size[v];
  for (auto u : DAG[v]) {
    if (!vis[u]) {
      calc_ans(u);
    }
    dp[v] += dp[u];
  }
}

int main() {
  std::ios_base::sync_with_stdio(0);
  cin.tie(0);

  cin >> n >> m;
  for (int i = 0; i < m; i++) {
    int a, b;
    cin >> a >> b;
    G[a].push_back(b);
    RG[b].push_back(a);
  }

  solve();
  fill(vis, vis + NAX, false);
  for (int v = 1; v <= scc_cnt; v++) {
    if (!vis[v]) {
      find_order1(v);
    }
  }
  reverse(order1.begin(), order1.end());
  fill(vis, vis + NAX, false);
  for (auto elem : order1) {
    if (!vis[elem]) {
      calc_ans(elem);
    }
  }

  for (int i = 1; i <= n; i++) {
    cout << dp[node_id[i]] - 1 << "\n";
  }

  return 0;
}
