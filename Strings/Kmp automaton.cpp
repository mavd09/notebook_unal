/// Complexity: O(|N|*alphabet)
/// Tested: not yet
const int alpha = 256;
int aut[102][alpha];
void kmp_automaton(string &t) {
  vector<int> phi = get_phi(t);
  for(int i = 0; i <= t.size(); ++i) {
    for(int c = 0; c < alpha; ++c) {
      if(i == t.size() || (i > 0 && c != t[i])) aut[i][c] = aut[ phi[i-1] ][c];
      else aut[i][c] = i + (c == t[i]);
    }
  }
}
