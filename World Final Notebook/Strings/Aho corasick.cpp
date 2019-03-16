struct aho_corasick {
  const static int alpha = 300;
  vector<int> fail, cnt_word;
  vector<vector<int>> trie;
  int nodes;
  aho_corasick(int maxn) : nodes(1), trie(maxn, vector<int>(alpha)),
                           fail(maxn), cnt_word(maxn) {}
  void add(string &s) {
    int u = 1;
    for(auto x : s) {
      int c = x-'a';
      if(!trie[u][c]) trie[u][c] = ++nodes;
      u = trie[u][c];
    }
    cnt_word[u]++;
  }
  int mv(int u, int c){
    while(!trie[u][c]) u = fail[u];
    return trie[u][c];
  }
  void build() {
    queue<int> q;
    for(int i = 0; i < alpha; ++i) {
      if(trie[1][i]) {
        q.push(trie[1][i]);
        fail[ trie[1][i] ] = 1;
      }
      else trie[1][i] = 1;
    }
    while(q.size()) {
      int u = q.front(); q.pop();
      for(int i = 0; i < alpha; ++i){
        int v = trie[u][i];
        if(v) {
          fail[v] = mv(fail[u], i);
          cnt_word[v] += cnt_word[ fail[v] ];
          q.push(v);
        }
      }
    }
  }
};
