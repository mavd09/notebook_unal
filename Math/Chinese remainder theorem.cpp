/// Complexity: |N|*log(|N|)
/// Tested: Not yet.
/// finds a suitable x that meets: x is congruent to a_i mod n_i
ll crt(vector<ll> &a, vector<ll> &n) {
  ll A = 1, x = 0;
  int n_eq = a.size();
  for(int i = 0; i < n_eq; i++) A *= n[i];
  for(int i = 0; i < n_eq; i++) {
    ll ni = A / n[i];
    ll yi = inverse(ni, n[i]);
    x += (ni * yi * a[i]) % A;
  }
  return x % A;
}
