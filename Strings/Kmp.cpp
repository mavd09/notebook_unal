/// Complexity: O(|N|)
/// Tested: not yet
vector<int> get_phi(string p) {
  vector<int> phi(p.size());
  phi[0] = 0;
  for(int i = 1, j = 0; i < p.size(); ++i ) {
    while(j > 0 && p[i] != p[j] ) j = phi[j-1];
    if(p[i] == p[j]) ++j;
    phi[i] = j;
  }
  return phi;
}
int get_match(string t, string p, vector<int> &phi) {
  int matches = 0;
  for(int i = 0, j = 0; i < t.size(); ++i ) {
    while(j > 0 && t[i] != p[j] ) j = phi[j-1];
    if(t[i] == p[j]) ++j;
    if(j == p.size()) {
      matches++;
      phi[i] = j;
    }
  }
  return matches;
}
