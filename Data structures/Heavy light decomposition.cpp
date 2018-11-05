/// Complexity: O(|N|)
/// Tested: https://tinyurl.com/ybdbmbw7(problem L)
int idx;
vector<int> len, hld_child, hld_index, hld_root, up;
void dfs( int u, int p = 0 ) {
  len[u] = 1;
  up[u] = p;
  for( auto& v : g[u] ) {
    if( v == p ) continue;
    depth[v] = depth[u]+1;
    dfs(v, u);
    len[u] += len[v];
    if( hld_child[u] == -1 || len[hld_child[u]] < len[v] )
      hld_child[u] = v;
  }
}
void build_hld( int u, int p = 0 ) {
  hld_index[u] = idx++;
  narr[hld_index[u]] = arr[u]; /// to initialize the segment tree
  if( hld_root[u] == -1 ) hld_root[u] = u;
  if( hld_child[u] != -1 ) {
    hld_root[hld_child[u]] = hld_root[u];
    build_hld(hld_child[u], u);
  }
  for( auto& v : g[u] ) {
    if( v == p || v == hld_child[u] ) continue;
    build_hld(v, u);
  }
}
void update_hld( int u, int val ) {
  update_tree(hld_index[u], val);
}
data query_hld( int u, int v ) {
  data val = NULL_DATA;
  while( hld_root[u] != hld_root[v] ) {
    if( depth[hld_root[u]] < depth[hld_root[v]] ) swap(u, v);
    val = val+query_tree(hld_index[hld_root[u]], hld_index[u]);
    u = up[hld_root[u]];
  }
  if( depth[u] > depth[v] ) swap(u, v);
  val = val+query_tree(hld_index[u], hld_index[v]);
  return val;
/// when updates are on edges use:
///   if (depth[u] == depth[v]) return ans;
///   val = val+query_tree(depth[u] + 1, depth[v]);
}
void build(int n, int root) {
  len = hld_index = up = depth = vector<int>(n+1);
  hld_child = hld_root = vector<int>(n+1, -1);
  idx = 1; /// segtree index [1, n]
  dfs(root, root); build_hld(root, root);
  /// initialize data structure
}
