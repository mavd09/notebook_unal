int dfs(int u, int p = -1) {
  fr[u] = t++;
  who[t-1] = u;
  sz[u] = 0;
  for(auto v : g[u])
    if(v != p)
      sz[u] += dfs(v, u)+1;
  to[u] = t-1;
  return sz[u];
}
void add(int u, int x) { /// x == 1 add, x == -1 delte
  cnt[u] += x;
}
void go(int u, int p = -1, bool keep = true) {
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
void solve(int root) {
  t = 0;
  dfs(root);
  go(root);
}
