#include <iostream>
#include <vector>
using namespace std;
 
static const int MAX_PRIME_NUMBER = 1000000;


// Structure to use Union-Find
struct UnionSet {
    vector<int> parent;
    vector<int> rank;
    UnionSet(int size) : rank(size, 0), parent(size) {
        for (int i = 0; i < size; i++) parent[i] = i;
    }

    // find root of node
    int findRoot(int x) {
        if (parent[x] == x) {
            return x; // this is root
        } else {
            return parent[x] = findRoot(parent[x]);
        }
    }

    // unite 2 trees
    void unite(int x, int y) {
        int rootX = findRoot(x);
        int rootY = findRoot(y);
        if (rootX != rootY) {
            if (rank[rootX] < rank[rootY]) {
                parent[rootX] = rootY;
            } else {
                parent[rootY] = rootX;
                if (rank[rootX] == rank[rootY]) rank[rootX]++;
            }
        }
    }

    // get the number of trees
    int size() {
        int result = 0;
        for (int i = 0; i < parent.size(); i++)
            if (parent[i] == i) result++;
        return result;
    }
};
 
int solve(vector<int>& primes, long long A, long long B, int P) {
    int intervalSize = B - A + 1;
    UnionSet uset(intervalSize);
    for (int i = 0; i < primes.size(); i++) {
        int factor = primes[i];
        if (factor < P) continue;
        if (factor >= intervalSize) break;

        int first = (A % factor == 0 ? 0 : (factor - A % factor));
        for (int j = first; j < intervalSize; j += factor) {
            if (j != first) uset.unite(first, j);
        }
    }
    return uset.size();
}
 
int main() {
    // prepare prime numbers
    vector<int> primes;
    vector<bool> temp(MAX_PRIME_NUMBER + 1, true);
    for (int i = 2; i <= MAX_PRIME_NUMBER; i++) {
        if (temp[i]) {
            primes.push_back(i);
            for (int j = i; j <= MAX_PRIME_NUMBER; j += i) {
                temp[j] = false;
            }
        }
    }
 
    // read cases from standard input and print result to standard out
    int N, P;
    long long A, B;
    cin >> N;
    for (int i = 1; i <= N; i++) {
        cin >> A >> B >> P;
        int result = solve(primes, A, B, P);
        cout << "Case #" << i << ": " << result << endl;
    }
 
    return 0;
}

