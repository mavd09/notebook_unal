void go(int k, int l, int r, int opl, int opr) {
  if(l > r) return;
  int mid = (l + r) / 2, op = -1;
  ll &best = dp[mid][k];
  best = INF;
  for(int i = min(opr, mid); i >= opl; i--) {
    ll cur = dp[i][k-1] + cost(i+1, mid);
    if(best > cur) {
      best = cur;
      op = i;
    }
  }
  go(k, l, mid-1, opl, op);
  go(k, mid+1, r, op, opr);
}
