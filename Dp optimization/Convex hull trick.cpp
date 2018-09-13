/// Complexity: O(|N|*log(|N|))
/// Tested: https://tinyurl.com/y94ov9ak
lf inter[MAX];
int len; // reset with len = 0
struct line {
  ll m, b;
  line () {}
  line (ll m, ll b) : m(m), b(b) {}
  ll eval (ll x) {
    return m*x + b;
  }
} lines[MAX];
lf get_inter (line &a, line &b) { // be careful with same slope !!!
  return lf(b.b - a.b) / lf(a.m - b.m);
}
//works for
//dp[i] = min(b[j] * a[i] + dp[j]) with j < i and b[i] > b[i + 1]
//dp[i] = max(b[j] * a[i] + dp[j]) with j < i and b[i] < b[i + 1]
void add (line l) { // lines must be added in slope order
  while (len >= 2 && get_inter(lines[len-2], l) <= inter[len-2])
    len--;
  lines[len] = l;
  if (len) inter[len-1] = get_inter(lines[len], lines[len-1]);
  len++;
}
ll get_min (lf x) {
  if (len == 1) return lines[0].eval(x);
  int pos = lower_bound(inter, inter+len-1, x) - inter;
  return lines[pos].eval(x);
}
