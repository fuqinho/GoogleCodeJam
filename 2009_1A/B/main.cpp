#include <iostream>
#include <vector>
#include <queue>
using namespace std;

typedef vector<int> VI;
typedef vector<VI> VVI;
typedef pair<int, int> PII;

int crossing_time(int now, int s, int w, int t, bool north) {
  int res;
  int cycle = s + w;
  int cur = (now % cycle - t % cycle + cycle) % cycle;
  if (!north) {
    if (cur >= s && cur <= s + w - 1) res = 1;
    else res = (s  - cur + cycle) % cycle + 1;
  } else {
    if (cur <= s-1) res = 1;
    else res = (cycle - cur) % cycle + 1;
  }
  return res;
}

int solve(int N, int M, VVI& S, VVI& W, VVI& T) {
  const int INF = 1000000000;
  VVI distance(N*2, VI(M*2, INF));

  priority_queue<pair<int, PII>, vector<pair<int, PII> >, greater<pair<int, PII> > > que;
  que.push(make_pair(0, make_pair(0, 2*N-1)));

  while (!que.empty()) {
    pair<int, PII> p = que.top(); que.pop();
    int time = p.first;
    PII pos = p.second;
    int ci = pos.second / 2, cj = pos.first/2;

    if (time >= distance[pos.second][pos.first]) continue;
    distance[pos.second][pos.first] = time;

    if (pos.first == 2*M-1 && pos.second == 0) break;

    // right
    if (pos.first < 2 * M - 1) {
      if (pos.first % 2 == 0) {
        int ctime = crossing_time(time, S[ci][cj], W[ci][cj], T[ci][cj], false);
        que.push(make_pair(time + ctime, make_pair(pos.first + 1, pos.second)));
      }
      else {
        que.push(make_pair(time + 2, make_pair(pos.first + 1, pos.second)));
      }
    }
    // left
    if (pos.first > 0) {
      if (pos.first % 2 == 1) {
        int ctime = crossing_time(time, S[ci][cj], W[ci][cj], T[ci][cj], false);
        que.push(make_pair(time + ctime, make_pair(pos.first - 1, pos.second)));
      } else {
        que.push(make_pair(time + 2, make_pair(pos.first - 1, pos.second)));
      }
    }
    // up
    if (pos.second > 0) {
      if (pos.second % 2 == 1) {
        int ctime = crossing_time(time, S[ci][cj], W[ci][cj], T[ci][cj], true);
        que.push(make_pair(time + ctime, make_pair(pos.first, pos.second - 1)));
      } else {
        que.push(make_pair(time + 2, make_pair(pos.first, pos.second - 1)));
      }
    }
    // down
    if (pos.second < 2 * N - 1) {
      if (pos.second % 2 == 0) {
        int ctime = crossing_time(time, S[ci][cj], W[ci][cj], T[ci][cj], true);
        que.push(make_pair(time + ctime, make_pair(pos.first, pos.second + 1)));
      } else {
        que.push(make_pair(time + 2, make_pair(pos.first, pos.second + 1)));
      }
    }
  }
  return distance[0][2*M-1];
}


int main() {
  int C; cin >> C;
  for (int c = 0; c < C; c++) {
    int N, M; cin >> N >> M;
    VVI S(N, VI(M)), W(N, VI(M)), T(N, VI(M));
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < M; j++) {
        cin >> S[i][j] >> W[i][j] >> T[i][j];
      }
    }
    int answer = solve(N, M, S, W, T);
    cout << "Case #" << c+1 << ": " << answer << endl;
  }
}

