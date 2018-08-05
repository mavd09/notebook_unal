/// Complexity: O(|V|^3)
/// Tested: https://tinyurl.com/ya9rgoyk
struct edge { int u, v, cap, flow, index; };
struct network {
  int n;
  vector<vector<edge>> g;
  vector<ll> ex;
  vector<int> d, act, cnt;
  queue<int> q;
  network(int n) : n(n), g(n), ex(n), d(n), act(n), cnt(2*n) {}
  void add_edge(int u, int v, int cap) {
    g[u].push_back({u, v, cap, 0, g[v].size()});
    if(u == v) g[u].back().index++;
    g[v].push_back({v, u, 0, 0, g[u].size()-1});
  }
  void enqueue(int v) {
    if(!act[v] && ex[v] > 0) {
      act[v] = true;
      q.push(v);
    }
  }
  void push(edge &e) {
    int amt = min(ex[e.u], 0ll+e.cap-e.flow);
    if(d[e.u] <= d[e.v] || amt == 0) return;
    e.flow += amt;
    g[e.v][e.index].flow -= amt;
    ex[e.v] += amt;
    ex[e.u] -= amt;
    enqueue(e.v);
  }
  void gap(int k) {
    for(int v = 0; v < n; v++) {
      if(d[v] < k) continue;
      cnt[ d[v] ]--;
      d[v] = max(d[v], n+1);
      cnt[ d[v] ]++;
      enqueue(v);
    }
  }
  void relabel(int u) {
    cnt[ d[u] ]--;
    d[u] = 2*n;
    for(auto &e : g[u])
      if(e.cap-e.flow > 0)
        d[u] = min(d[u], d[e.v]+1);
    cnt[ d[u] ]++;
    enqueue(u);
  }
  void discharge(int u) {
    for(int i = 0; ex[u] > 0 && i < g[u].size(); i++)
      push(g[u][i]);
    if(ex[u] > 0) {
      if(cnt[ d[u] ] == 1) gap(d[u]);
      else relabel(u);
    }
  }
  ll max_flow(int s, int t) {
    cnt[0] = n-1; cnt[n] = 1;
    d[s] = n;
    act[s] = act[t] = true;
    for(auto &e : g[s]) {
      ex[s] += e.cap;
      push(e);
    }
    while(!q.empty()) {
      int u = q.front(); q.pop();
      act[u] = false;
      discharge(u);
    }
    ll tot = 0;
    for(auto &e : g[s]) tot += e.flow;
    return tot;
  }
};
