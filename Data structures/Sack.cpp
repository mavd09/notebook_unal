int dfs(int u, int d, int p = -1) {
  fr[u] = t++;
  who[t-1] = u;
  sz[u] = g[u].size();
  for(auto v : g[u])
    if(v != p)
      sz[u] += dfs(v, d+1, u);
  to[u] = t-1;
  return sz[u];
}
void add(int u, int x) { /// x == 1 add, x == -1 delete
  cnt[u] += x;
}
void go(int u, int p, bool keep) {
  int mx = -1, big = -1;
  for(auto v : g[u])
    if(v != p && sz[v] > mx)
      mx = sz[v], big = v;
  for(auto v : g[u])
    if(v != p && v != big)
      go(v, u, 0);
  if(big != -1) go(big, u, 1);
  /// add all small
  for(auto v : g[u])
    if(v != p && v != big)
      for(int i = fr[v]; i <= to[v]; i++)
        add(who[i], 1);
  add(u, 1);
  ans[u] = get(u);
  if(!keep)
    for(int i = fr[u]; i <= to[u]; i++)
      add(who[i], -1);
}
void solve() {
  t = 0;
  dfs(1, 0);
  go(1, -1, 1);
}
