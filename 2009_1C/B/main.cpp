#include <iostream>
#include <vector>
#include <numeric>
#include <cstdio>
#include <cmath>
using namespace std;

pair<double, double> solve(int N, vector<int>& x, vector<int>& y, vector<int>& z, 
                           vector<int>& vx, vector<int>& vy, vector<int>& vz) {
  double x0 = (double)accumulate(x.begin(), x.end(), 0) / N;
  double y0 = (double)accumulate(y.begin(), y.end(), 0) / N;
  double z0 = (double)accumulate(z.begin(), z.end(), 0) / N;
  double v_x = (double)accumulate(vx.begin(), vx.end(), 0) / N;
  double v_y = (double)accumulate(vy.begin(), vy.end(), 0) / N;
  double v_z = (double)accumulate(vz.begin(), vz.end(), 0) / N;

  // D = a*t^2 + b*t + c
  double a = v_x*v_x + v_y*v_y + v_z*v_z;
  double b = 2.0 * (x0*v_x + y0*v_y + z0*v_z);
  double c = x0*x0 + y0*y0 + z0*z0;

  double minT = max(0.0, -b / (2.0 * a));
  double minD = sqrt(abs(a * minT * minT + b * minT + c));

  return make_pair(minD, minT);
}

int main() {
  int T; cin >> T;
  for (int t=0; t<T; t++) {
    int N; cin >> N;
    vector<int> x(N), y(N), z(N), vx(N), vy(N), vz(N);
    for (int i=0; i<N; i++) cin >> x[i] >> y[i] >> z[i] >> vx[i] >> vy[i] >> vz[i];

    pair<double, double> ans = solve(N, x, y, z, vx, vy, vz);
    printf("Case #%d: %.8f %.8f\n", t+1, ans.first, ans.second);
  }
}
