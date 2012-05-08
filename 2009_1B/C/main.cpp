#include <iostream>
#include <vector>
#include <queue>
#include <cstdio>
using namespace std;

typedef pair<int, int> PII;
#define REP(i,n) for(int i=0;i<(n);++i)

const int INF = 10000000;
const int MAX_D = 1000;
const int MAX_W = 20;

const int DR[] = {-1, 1, 0, 0};
const int DC[] = {0, 0, -1, 1};

// dist[i][j][k+1000]: (i, j)からスタートして加減算の結果がkになる最小のステップ数
int dist[MAX_W][MAX_W][MAX_D*2+1];

bool is_inside(int r, int c, int H, int W) {
  if (r >= 0 && r < H && c >= 0 && c < W) {
    return true;
  } else {
    return false;
  }
}

void bfs(int W, const vector<string>& cells) {
  REP(i, W) REP(j, W) REP(k, MAX_D*2+1) dist[i][j][k] = INF;

  queue<pair<PII, PII> > que;
  REP(i, W) REP(j, W) {
    if (cells[i][j] != '-' && cells[i][j] != '+') {
      dist[i][j][0+MAX_D] = 0;
      que.push(make_pair(PII(0, 0), PII(i, j)));
    }
  }

  while (!que.empty()) {
    pair<PII, PII> p = que.front(); que.pop();
    int d = p.first.first;
    int s = p.first.second;
    int r = p.second.first;
    int c = p.second.second;

    REP(i, 4) {
      int r1 = r + DR[i];
      int c1 = c + DC[i];
      if (is_inside(r1, c1, W, W)) {
        int sign = (cells[r1][c1] == '+' ? 1 : -1);
        REP(j, 4) { 
          int r2 = r1 + DR[j];
          int c2 = c1 + DC[j];
          if (is_inside(r2, c2, W, W)) {
            int s2 = s + sign * (cells[r][c] - '0');
            if (s2 >= -MAX_D && s2 <= MAX_D && dist[r2][c2][s2+MAX_D] == INF) {
              dist[r2][c2][s2+MAX_D] = d+1;
              que.push(make_pair(PII(d+1, s2), PII(r2, c2))); 
            }
          }
        }
      }
    }
  }
}

// queryを最小限のstepで実現できるpathを、できるだけ辞書順が早くなるように経路復元する
string get_path(int query, int W, const vector<string>& cells) {
  int minD = INF;
  REP(i, W) REP(j, W) {
    if (cells[i][j] != '+' && cells[i][j] != '-') {
      int num = cells[i][j] - '0';
      minD = min(minD, dist[i][j][query - num + MAX_D]);
    }
  }

  string ans;
  vector<PII> startpos;
  int startNum = INF;
  REP(i, W) REP(j, W) {
    if (cells[i][j] != '+' && cells[i][j] != '-') {
      int num = cells[i][j] - '0';
      if (dist[i][j][query - num + MAX_D] == minD) {
        if (num <= startNum) {
          if (num != startNum) {
            startpos.clear();
            startNum = cells[i][j] - '0';
            ans = cells[i][j];
          }
          startpos.push_back(PII(i, j));
        }
      }
    }
  }
  query -= startNum;

  for (int d = minD-1; d >= 0; d--) {
    vector<PII> next_startpos;
    string min_next_path = "99";
    int next_query = INF;
    REP(k, startpos.size()) {
      int r = startpos[k].first;
      int c = startpos[k].second;
      REP(i, 4) {
        int r1 = r + DR[i];
        int c1 = c + DC[i];
        if (is_inside(r1, c1, W, W)) {
          int sign = (cells[r1][c1] == '+' ? 1 : -1);
          REP(j, 4) { 
            int r2 = r1 + DR[j];
            int c2 = c1 + DC[j];
            if (is_inside(r2, c2, W, W)) {
              int num = cells[r2][c2] - '0';
              if (dist[r2][c2][query - (sign * num) + MAX_D] == d) {
                string next = "  ";
                next[0] = cells[r1][c1];
                next[1] = cells[r2][c2];
                if (next <= min_next_path) {
                  if (next != min_next_path) {
                    next_startpos.clear();
                    min_next_path = next;
                    next_query = query - sign * num;
                  }
                  if (find(next_startpos.begin(), next_startpos.end(), PII(r2, c2)) == next_startpos.end()) {
                    next_startpos.push_back(PII(r2, c2));
                  }
                }
              }
            }
          }
        }
      }
    }
    ans += min_next_path;
    query = next_query;
    startpos = next_startpos;
  }
  return ans;
}


int main() {
  int T; cin >> T;
  for (int t = 1; t <= T; t++) {
    int W, Q; cin >> W >> Q;
    vector<string> cells(W);
    for (int i=0; i<W; i++) cin >> cells[i];

    bfs(W, cells);
    cout << "Case #" << t << ":" << endl;
    for (int i=0; i<Q; i++) {
      int query; cin >> query;
      string ans = get_path(query, W, cells);
      cout << ans << endl;
    }
  }
}
