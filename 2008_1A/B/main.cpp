#include <iostream>
#include <sstream>
#include <vector>
using namespace std;

string solve(int N, int M, vector<vector<pair<int, bool> > > favs) {
  vector<bool> malted(N, false);
BEGIN:
  // check if every persons is satisfied
  for (int i = 0; i < M; i++) {
    bool satisfied = false;
    int tomalt = -1;
    for (int j = 0; j < favs[i].size(); j++) {
      if (favs[i][j].second) tomalt = favs[i][j].first;
      if (favs[i][j].second == malted[favs[i][j].first]) satisfied = true;
    }
    // if not satisfied, malt favorite flavor.
    // (can not unmalt because it is needed by someone)
    if (!satisfied) {
      if (tomalt == -1) {
        return "IMPOSSIBLE";
      } else {
        malted[tomalt] = true;
        goto BEGIN;
      }
    }
  }
  ostringstream oss;
  for (int i = 0; i < N; i++) oss << malted[i] << " ";
  return oss.str();
}

int main() {
  int C; cin >> C;
  for (int c=0; c<C; c++) {
    int N, M; cin >> N >> M;
    vector<vector<pair<int, bool> > > favs(M);
    for (int m=0; m<M; m++) {
      int T; cin >> T;
      favs[m] = vector<pair<int, bool> >(T);
      for (int t=0; t<T; t++) {
        cin >> favs[m][t].first >> favs[m][t].second;
        favs[m][t].first--; // change to 0-base index;
      }
    }
    string answer = solve(N, M, favs);
    cout << "Case #" << c+1 << ": " << answer << endl;
  }
}

