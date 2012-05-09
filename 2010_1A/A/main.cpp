#include <iostream>
#include <vector>
using namespace std;

#define REP(i,n) for(int i=0;i<(n);++i)

void drop(vector<string>& board) {
  REP(i, board.size()) {
    int empty = 0;
    for (int j = board[i].size()-1; j >= 0; j--) {
      if (board[i][j] == '.') {
        empty++;
      }
      else {
        board[i][j+empty] = board[i][j];
        if (empty != 0) board[i][j] = '.';
      }
    }
  }
}

bool check(int N, int K, const vector<string>& board, char c) {
  int count = 0;
  // horizontal
  REP(i, N) {
    count = 0;
    REP(j, N) {
      if (board[i][j] == c) {
        count++;
        if (count >= K) return true;
      } else {
        count = 0;
      }
    }
  }
  // vertical
  REP(j, N) {
    count = 0;
    REP(i, N) {
      if (board[i][j] == c) {
        count++;
        if (count >= K) return true;
      } else {
        count = 0;
      }
    }
  }
  // diagonal right_top to left_bottom
  for (int j = 0; j < 2 * N; j++) {
    count = 0;
    REP(i, N) {
      if (j-i >= 0 && j-i < N && board[i][j-i] == c) {
        count++;
        if (count >= K) return true;
      } else {
        count = 0;
      }
    }
  }
  // diagonal left_top to right_bottom
  for (int j = -N; j < N; j++) {
    count = 0;
    REP(i, N) {
      if (i+j >= 0 && i+j < N && board[i][i+j] == c) {
        count++;
        if (count >= K) return true;
      } else {
        count = 0;
      }
    }
  }
  return false;
}

string solve(int N, int K, const vector<string>& board) {
  bool Bwin = check(N, K, board, 'B');
  bool Rwin = check(N, K, board, 'R');
  if (Bwin) {
    if (Rwin) return "Both";
    else return "Blue";
  } else {
    if (Rwin) return "Red";
    else return "Neither";
  }
}

int main() {
  int T; cin >> T;
  REP(t, T) {
    int N, K; cin >> N >> K;
    vector<string> board(N);
    REP(i, N) cin >> board[i];

    drop(board);
    string ans = solve(N, K, board);
    cout << "Case #" << t+1 << ": " << ans << endl;
  }
}
