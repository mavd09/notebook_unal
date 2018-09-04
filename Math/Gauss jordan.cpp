/// Complexity: O(|N|^3)
/// Tested: Not yet
void gauss_jordan(vector<vector<double>> &a, vector<double> &x) {
  for(int i = 0; i < n; ++i) {
    int maxs = i;
    for(int j = i+1; j < n; ++j)
      if(abs(a[j][i]) > abs(a[maxs][i]))
        maxs = j;
    if(maxs != i)
      for(int j = 0; j <= n; ++j)
        swap(a[i][j], a[maxs][j]);
    for(int j = i + 1; j < n; ++j) {
      lf r = a[j][i]/a[i][i];
      for(int k = 0; k <= n; ++k)
        a[j][k] -= r*a[i][k];
    }
  }
  for(int i = n-1; i >= 0; --i) {
    x[i] = a[i][n]/a[i][i];
    for(int j = i-1; j >= 0; --j)
      a[j][n] -= a[j][i]*x[i];
  }
}
