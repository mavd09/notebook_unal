struct line {
  ll m, b;
  line (ll m, ll b) : m(m), b(b) {}
  ll eval (ll x) { return m*x + b; }
};
vector<line> lines[MAXN];
vector<lf> inter[MAXN];
lf get_inter (line &a, line &b) { // be careful with same slope !!!
  return lf(b.b - a.b) / lf(a.m - b.m);
}
//works for
//dp[i] = min(b[j] * a[i] + dp[j]) with j < i and b[i] > b[i + 1]
//dp[i] = max(b[j] * a[i] + dp[j]) with j < i and b[i] < b[i + 1]
void add (line l, int u) { // lines must be added in slope order
  while (lines[u].size() >= 2 && get_inter(lines[u][lines[u].size()-2], l) <= inter[u][lines[u].size()-2]) {
    lines[u].pop_back();
    inter[u].pop_back();
  }
  int len = lines[u].size();
  lines[u].push_back(l);
  if (lines[u].size()-1 > 0) inter[u].push_back(get_inter(lines[u][len], lines[u][len-1]));
}
ll get_min (lf x, int u) {
  if(lines[u].size() == 0) return INF;
  if (lines[u].size() == 1) return lines[u][0].eval(x);
  int pos = lower_bound(inter[u].begin(), inter[u].end(), x) - inter[u].begin();
  return lines[u][pos].eval(x);
}