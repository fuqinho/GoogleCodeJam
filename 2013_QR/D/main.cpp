#include <iostream>
#include <vector>
#include <bitset>
#include <map>
#include <set>
#include <queue>
using namespace std;

class Dinic {
public:
    Dinic(int nElement) {
        m_edges = vector< vector<Edge> >(nElement);
        m_level = vector<int>(nElement);
        m_iter = vector<int>(nElement);
    }
    void addEdge(int from, int to, int cap) {
        m_edges[from].push_back(Edge(to, cap, m_edges[to].size()));
        m_edges[to].push_back(Edge(from, 0, m_edges[from].size()-1));
    }
    int maxFlow(int s, int t) {
        int flow = 0;
        for (;;) {
            bfs(s);
            if (m_level[t] < 0) break;
            fill(m_iter.begin(), m_iter.end(), 0);
            int f = 0;
            while ((f = dfs(s, t, INF)) > 0) {
                flow += f;
            }
        }
        return flow;
    }
private:
    struct Edge {
        int to, cap, rev;
        Edge(int t, int c, int r):to(t),cap(c),rev(r){}
    };
    static const int INF = 1000000000;
    vector< vector<Edge> > m_edges;
    vector<int> m_level;
    vector<int> m_iter;
    void bfs(int s) {
        fill(m_level.begin(), m_level.end(), -1);
        m_level[s] = 0;
        queue<int> que;
        que.push(s);
        while (que.size() > 0) {
            int v = que.front(); que.pop();
            for (int i = 0; i < m_edges[v].size(); i++) {
                Edge& e = m_edges[v][i];
                if (e.cap > 0 && m_level[e.to] == -1) {
                    m_level[e.to] = m_level[v] + 1;
                    que.push(e.to);
                }
            }
        }
    }
    int dfs(int v, int t, int f) {
        if (v == t) return f;
        for (int& i = m_iter[v]; i < m_edges[v].size(); i++) {
            Edge& e = m_edges[v][i];
            if (e.cap > 0 && m_level[e.to] > m_level[v]) {
                int d = dfs(e.to, t, min(f, e.cap));
                if (d > 0) {
                    e.cap -= d;
                    m_edges[e.to][e.rev].cap += d;
                    return d;
                }
            }
        }
        return 0;
    }
};

const int INF = 1000000000;
typedef bitset<200> bset;
struct Box {
    int lock;
    map<int, int> keys;
};

int K, N;
map<int, int> initial_keys;
vector<Box> boxes;
vector<vector<int> > key_to_box;

map<int,int> available_keys(bset closed) {
    map<int,int> keys = initial_keys;
    for (int i = 0; i < N; i++) {
        if (!(closed[i])) {
            for (map<int,int>::iterator j = boxes[i].keys.begin(); j != boxes[i].keys.end(); j++)
                keys[j->first] += j->second;
            keys[boxes[i].lock]--;
        }
    }
    return keys;
}

void dfs(int v, const bset& closed, bset& visited) {
    if (!closed[v]) return;
    if (visited[v]) return;
    visited[v] = true;
    for (map<int,int>::iterator i = boxes[v].keys.begin(); i != boxes[v].keys.end(); i++) {
        if (i->second == 0) continue;
        int key = i->first;
        for (int j = 0; j < key_to_box[key].size(); j++) {
            int box = key_to_box[key][j];
            if ((closed[box] && !visited[box]))
                dfs(box, closed, visited);
        }
    }
}

bool is_connected(bset closed) {
    bset visited;
    map<int,int> keys = available_keys(closed);
    for (map<int,int>::iterator i = keys.begin(); i != keys.end(); i++)
        if (i->second > 0) {
            int key = i->first;
            for (int j = 0; j < key_to_box[key].size(); j++) {
                int box = key_to_box[key][j];
                if ((closed[box] && !visited[box]))
                    dfs(box, closed, visited);
            }
        }
    return visited.count() == closed.count();
}

bool check(bset closed) {
    if (!is_connected(closed)) return false;

    Dinic G(2*N + K + 3);
    // node index
    // left box: [0, N-1)
    // right box: [N, 2N)
    // key: [2N, 2N+K)
    // initial: 2N+K
    // S: 2N+K+1
    // T: 2N+K+2
    int I = 2*N + K;
    int S = 2*N + K + 1;
    int T = 2*N + K + 2;

    // source to initial state
    G.addEdge(S, I, INF);

    // source to boxes
    for (int i = 0; i < N; i++) if (closed[i])
        G.addEdge(S, i, INF);

    // initial state to keys
    map<int,int> keys = available_keys(closed);
    for (map<int,int>::iterator i = keys.begin(); i != keys.end(); i++)
        G.addEdge(I, 2*N + i->first, i->second);

    // boxes to keys
    for (int i = 0; i < N; i++) if (closed[i])
        for (map<int,int>::iterator j = boxes[i].keys.begin(); j != boxes[i].keys.end(); j++)
            G.addEdge(i, 2*N + j->first, j->second);

    // keys to boxes
    for (int i = 0; i < K; i++)
        for (int j = 0; j < key_to_box[i].size(); j++) if (closed[key_to_box[i][j]])
            G.addEdge(2*N + i, N + key_to_box[i][j], 1);

    // boxes to sink
    for (int i = 0; i < N; i++) if (closed[i])
        G.addEdge(N + i, T, 1);
    
    return G.maxFlow(S, T) == closed.count();
}

vector<int> solve() {
    bset closed;
    for (int i = 0; i < N; i++) closed[i] = true;
    if (!check(closed)) return vector<int>();

    vector<int> res;
    for (int i = 0; i < N; i++) {
        map<int,int> keys = available_keys(closed);
        for (int j = 0; j < N; j++) if (closed[j] && keys[boxes[j].lock] > 0) {
            closed[j] = false;
            if (check(closed)) {
                res.push_back(j);
                break;
            }
            closed[j] = true;
        }
    }
    return res;
}

int conv_key(int key, map<int, int>& key_map, int& key_num) {
    if (key_map.find(key) == key_map.end()) key_map[key] = key_num++;
    return key_map[key];
}

void init() {
    // convert key to minimize its size
    map<int, int> key_map;
    int key_num = 0;
    map<int, int> next_initial_keys;
    for (map<int,int>::iterator i = initial_keys.begin(); i != initial_keys.end(); i++)
        next_initial_keys[conv_key(i->first, key_map, key_num)] = i->second;
    initial_keys = next_initial_keys;
    for (int i = 0; i < N; i++) {
        map<int,int> new_map;
        for (map<int,int>::iterator j = boxes[i].keys.begin(); j != boxes[i].keys.end(); j++)
            new_map[conv_key(j->first, key_map, key_num)] = j->second;
        boxes[i].keys = new_map;
        boxes[i].lock = conv_key(boxes[i].lock, key_map, key_num);
    }

    K = key_num;

    key_to_box = vector<vector<int> >(K);
    for (int i = 0; i < N; i++) {
        key_to_box[boxes[i].lock].push_back(i);
    }
}

int main() {
    int T; cin >> T;
    for (int t = 1; t <= T; t++) {
        // read input
        cin >> K >> N;
        initial_keys = map<int, int>();
        for (int i = 0; i < K; i++) {
            int key; cin >> key;
            initial_keys[key]++;
        }
        boxes = vector<Box>(N);
        for (int i = 0; i < N; i++) {
            cin >> boxes[i].lock;
            int num_keys; cin >> num_keys;
            for (int j = 0; j < num_keys; j++) {
                int k; cin >> k;
                boxes[i].keys[k]++;
            }
        }

        // solve and write answer
        init();
        vector<int> res = solve();
        cout << "Case #" << t << ":";
        if (res.empty()) {
            cout << " IMPOSSIBLE";
        } else {
            for (int i = 0; i < res.size(); i++)
                cout << " " << (res[i] + 1);
        }
        cout << endl;
    }
}
