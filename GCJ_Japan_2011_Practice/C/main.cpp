#include <iostream>
#include <vector>
using namespace std;

#define dump(x) cerr << #x << " = " << (x) << endl;

long solve(int R, int K, const vector<int>& groups) {
    vector<int> next(groups.size());
    vector<int> sales(groups.size());
    long total = 0;
    for (int i = 0; i < groups.size(); i++) total += groups[i];
    for (int i = 0; i < groups.size(); i++) {
        long people = 0;
        int curGroup = i;
        while (true) {
            long next = people + groups[curGroup];
            if (next > K || next > total) {
                break;
            } else {
                people = next;
                curGroup = (curGroup + 1) % groups.size();
            }
        }
        next[i] = curGroup;
        sales[i] = people;
    }

#if 1
    // faster algorithm using cyclicity
    int loopStart, loopLength;
    bool loopFound = false;
    vector<int> history;
    int nextGroup = 0;
    for (int i = 0; ; i++) {
        history.push_back(nextGroup);
        nextGroup = next[nextGroup];
        for (int j = 0; j < history.size(); j++) {
            if (nextGroup == history[j]) {
                // found loop
                loopStart = j;
                loopLength = i + 1 - j;
                loopFound = true;
                break;
            }
        }
        if (loopFound) break;
    }

    // calc sales for one loop
    nextGroup = history[loopStart];
    long loopSales = 0;
    for (int i = 0; i < loopLength; i++) {
        loopSales += sales[nextGroup];
        nextGroup = next[nextGroup];
    }

    // sum sales
    long result = 0;

    // add sales for loop
    int loopCount = (R - loopStart) / loopLength;
    result = loopSales * loopCount;

    // add remains
    nextGroup = 0;
    for (int i = 0; i < R - ((long)loopCount * loopLength); i++) {
        result += sales[nextGroup];
        nextGroup = next[nextGroup];
    }
#else
    long result = 0;
    int nextGroup = 0;
    for (int i = 0; i < R; i++) {
        result += sales[nextGroup];
        nextGroup = next[nextGroup];
    }
#endif

    return result;
}

int main() {
    int T, R, K, N, tmp;
    cin >> T;
    for (int i = 1; i <= T; i++) {
        cin >> R >> K >> N;
        vector<int> groups;
        for (int j = 0; j < N; j++) {
            cin >> tmp;
            groups.push_back(tmp);
        }

        long answer = solve(R, K, groups);
        cout << "Case #" << i << ": " << answer << endl;
    }
}
