struct suffix_array {
  const static int alpha = 300;
  int mx, n;
  string s;
  vector<int> pos, tpos, sa, tsa, lcp;
  suffix_array(string t) {
    s = t+"$"; n = s.size(); mx = max(alpha, n)+2;
    pos = tpos = tsa = sa = lcp = vector<int>(n);
  }
  bool check(int i, int gap) {
    if(pos[ sa[i-1] ] != pos[ sa[i] ]) return true;
    if(sa[i-1]+gap < n && sa[i]+gap < n)
      return (pos[ sa[i-1]+gap ] != pos[ sa[i]+gap ]);
    return true;
  }
  void radix_sort(int k) {
    vector<int> cnt(mx);
    for(int i = 0; i < n; i++)
      cnt[(i+k < n) ? pos[i+k]+1 : 1]++;
    for(int i = 1; i < mx; i++)
      cnt[i] += cnt[i-1];
    for(int i = 0; i < n; i++)
      tsa[cnt[(sa[i]+k < n) ? pos[sa[i]+k] : 0]++] = sa[i];
    sa = tsa;
  }
  void build_sa() {
    for(int i = 0; i < n; i++) {
      sa[i] = i;
      pos[i] = s[i];
    }
    for(int gap = 1; gap < n; gap <<= 1) {
      radix_sort(gap);
      radix_sort(0);
      tpos[ sa[0] ] = 0;
      for(int i = 1; i < n; i++)
        tpos[ sa[i] ] = tpos[ sa[i-1] ] + check(i, gap);
      pos = tpos;
      if(pos[ sa[n-1] ] == n-1) break;
    }
  }
  void build_lcp() {
    int k = 0;
    lcp[0] = 0;
    for(int i = 0; i < n; i++) {
      if(pos[i] == 0) continue;
      while(s[i+k] == s[ sa[ pos[i]-1 ]+k ]) k++;
      lcp[ pos[i] ] = k;
      k = max(0, k-1);
    }
  }
  int& operator[] ( int i ){ return sa[i]; }
};
