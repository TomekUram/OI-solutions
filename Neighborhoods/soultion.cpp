//Tomasz Uram
#include <bits/stdc++.h>
using namespace std;

const int NAX = 1e6 + 7;
int n, m;
vector<pair<int, int>> G[NAX];
vector<pair<int, int>> edges;
bool vis[NAX], ans[NAX], did[NAX];
int low[NAX], depth[NAX];

void input() {
  cin >> n >> m;
  edges.resize(m);
  for (int i = 0; i < m; i++) {
    int a, b;
    cin >> a >> b;
    G[a].push_back({b, i});
    G[b].push_back({a, i});
    edges[i] = {a, b};
  }
}

set<pair<int, int>> bridge;
void find_bridge(int v, int p, int d) {
  vis[v] = true;
  depth[v] = low[v] = d;
  bool skipped = false;
  for (auto [u, id] : G[v]) {
    if (u == p && !skipped) {
      skipped = true;
      continue;
    }
    if (!vis[u]) {
      find_bridge(u, v, d + 1);
      low[v] = min(low[v], low[u]);
      if (low[u] > depth[v]) {
        // cerr << v << " " << u << "\n";
        bridge.insert({min(v, u), max(v, u)});
      }
    } else {
      low[v] = min(low[v], depth[u]);
    }
  }
}

void dfs(int v, int p) {
  vis[v] = true;
  for (auto [u, id] : G[v]) {
    if (!did[id]) {
      // DBG(v, u);
      ans[id] = (make_pair(v, u) == edges[id]);
      did[id] = true;
    }
    if (!vis[u] && bridge.find({min(u, v), max(u, v)}) == bridge.end()) {
      dfs(u, v);
    }
  }
}

signed main() {
  std::ios_base::sync_with_stdio(0);
  cin.tie(0);

  input();
  int scc_cnt = 0;
  for (int i = 1; i <= n; i++) {
    if (!vis[i]) {
      scc_cnt++;
      find_bridge(i, i, 0);
    }
  }
  fill(vis, vis + NAX, false);
  for (int i = 1; i <= n; i++) {
    if (!vis[i]) {
      dfs(i, i);
    }
  }

  cout << scc_cnt + bridge.size() << "\n";
  for (int i = 0; i < m; i++) {
    if (ans[i]) {
      cout << ">";
    } else {
      cout << "<";
    }
  }

  return 0;
}
