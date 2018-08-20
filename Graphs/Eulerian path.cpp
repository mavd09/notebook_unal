/// Complexity: O(|N|)
/// Tested: https://tinyurl.com/y85t8e83
bool eulerian(vector<int> &tour) { /// directed graph
  int one_in = 0, one_out = 0, start = -1;
  bool ok = true;
  for (int i = 0; i < n; i++) {
    if(out[i] && start == -1) start = i;
    if(out[i] - in[i] == 1) one_out++, start = i;
    else if(in[i] - out[i] == 1) one_in++;
    else ok &= in[i] == out[i];
  }
  ok &= one_in == one_out && one_in <= 1;
  if (ok) {
    function<void(int)> go = [&](int u) {
      while(g[u].size()) {
        int v = g[u].back();
        g[u].pop_back();
        go(v);
      }
      tour.push_back(u);
    };
    go(start);
    reverse(tour.begin(), tour.end());
    if(tour.size() == edges + 1) return true;
  }
  return false;
}
