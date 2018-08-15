/// Complexity: O(|N|*alphabet)
/// Tested: not yet
const int alpha = 256;
vector<vector<int>> kmp_automaton(string &t) {
  int len = t.size();
  vector<int> phi = get_phi(t);
  vector<vector<int>> aut(len, vector<int>(alpha));
  for(int i = 0; i < len; ++i) {
    for(int c = 0; c < alpha; ++c) {
      char ch = c+'a';
      if(i > 0 && ch != t[i])
        aut[i][c] = aut[ phi[i-1] ][c];
      else
        aut[i][c] = i + (ch == t[i]);
    }
  }
  return aut;
}
