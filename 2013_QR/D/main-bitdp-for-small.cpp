#include <iostream>
#include <vector>
#include <bitset>
#include <map>
#include <set>
using namespace std;

template<class T1,class T2> ostream& operator<<(ostream& o,const pair<T1,T2>& p){return o<<"("<<p.first<<","<<p.second<<")";}
template<class T> ostream& operator<<(ostream& o,const vector<T>& v){o<<"[";for(typename vector<T>::const_iterator i=v.begin();i!=v.end();++i){if (i != v.begin()) o << ", ";o<<(*i);}o<<"]";return o;}
template<class T> ostream& operator<<(ostream& o,const set<T>& s){o<<"{";for(typename set<T>::const_iterator i=s.begin();i!=s.end();++i){if(i!=s.begin())o<<", ";o<<(*i);}o<<"}";return o;}
template<class K,class V> ostream& operator<<(ostream& o,const map<K,V>& m){o<<"{";for(typename map<K,V>::const_iterator i=m.begin();i!=m.end();++i){if(i!=m.begin())o<<", ";o<<i->first<<":"<<i->second;}o<<"}";return o;}
template<class T> ostream& operator<<(ostream& o,const vector<vector<T> >& m){o<<"[\n";for(typename vector<vector<T> >::const_iterator i=m.begin();i!=m.end();++i){o<<"  "<<(*i);o<<(i+1!=m.end()?",\n":"\n");}o<<"]\n";return o;}
string bitstr(int n,int d=0){string r;for(int i=0;i<d||n>0;++i,n>>=1){r+=(n&1)?"1":"0";}reverse(r.begin(),r.end());return r;}

const int MAX_N = 20;
const int KEY_TYPES_NUM = 201;

int K, N;
vector<int> initial_keys;
vector<int> locks;
vector<vector<int> > inbox_keys;

int memo[1<<20];
int memo2[1<<20];

int openable_boxes(int closed) {
    if (memo2[closed] != -1) return memo2[closed];
    vector<int> keys = initial_keys;
    for (int i = 0; i < N; i++)
        if (!(closed & (1<<i))) {
            for (int j = 0; j < KEY_TYPES_NUM; j++)
                keys[j] += inbox_keys[i][j];
            keys[locks[i]]--;
        }
    int res = 0;
    for (int i = 0; i < N; i++)
        if (keys[locks[i]] > 0) res |= (1<<i);
    return memo2[closed] = res;
}

bool can_open(int closed) {
    if (closed == 0) return true;
    if (memo[closed] != -1) return memo[closed] == 1;

    int openable = openable_boxes(closed);
    for (int i = 0; i < KEY_TYPES_NUM; i++)
        if ((closed & (1<<i)) && (openable & (1<<i)))
            if (can_open(closed ^ (1<<i))) {
                memo[closed] = 1;
                return true;
            }
    memo[closed] = 0;
    return false;
}

vector<int> restore(int closed) {
    if (closed == 0) return vector<int>();

    int openable = openable_boxes(closed);
    vector<int> res;
    for (int i = 0; i < N; i++) {
        if ((closed & (1<<i)) && (openable & (1<<i)) && can_open(closed ^ (1<<i))) {
            res = restore(closed ^ (1<<i));
            res.push_back(i);
            break;
        }
    }
    return res;
}

int main() {
    int T; cin >> T;
    for (int t = 1; t <= T; t++) {
        // read input
        cin >> K >> N;
        initial_keys = vector<int>(KEY_TYPES_NUM);
        for (int i = 0; i < K; i++) {
            int key; cin >> key;
            initial_keys[key-1]++;
        }
        locks = vector<int>(N);
        inbox_keys = vector<vector<int> >(N, vector<int>(KEY_TYPES_NUM));
        for (int i = 0; i < N; i++) {
            int l; cin >> l;
            locks[i] = l-1;
            int key_num; cin >> key_num;
            for (int j = 0; j < key_num; j++) {
                int k; cin >> k;
                inbox_keys[i][k-1]++;
            }
        }
        //cerr << "locks: " << locks << endl;
        //cerr << "inbox_keys: " << inbox_keys << endl;

        // solve and write answer
        cout << "Case #" << t << ":";
        memset(memo, -1, sizeof(memo));
        memset(memo2, -1, sizeof(memo2));
        bool ok = can_open((1<<N)-1);
        if (ok) {
            vector<int> history = restore((1<<N)-1);
            for (int i = history.size()-1; i >= 0; i--) {
                cout << " " << (history[i] + 1);
            }
        } else {
            cout << " IMPOSSIBLE";
        }
        cout << endl;
    }
}
