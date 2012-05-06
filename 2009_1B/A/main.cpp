#include <iostream>
#include <sstream>
#include <vector>
using namespace std;

struct Node { double p; bool hasChild; string feature; int ch[2]; };
vector<Node> nodes;

int s2i(string& s) {
  int res;
  istringstream iss(s); iss >> res;
  return res;
}

int create_tree(string s) {
  int depth = 0;
  int pstart[2];
  int cnum = 0;
  Node node;
  // find child by searching parenthesis and create subtree recursively
  for (int i = 0; i < s.size(); i++) {
    if (s[i] == '(' && ++depth == 2) pstart[cnum] = i;
    if (s[i] == ')' && depth-- == 2) {
      node.ch[cnum] = create_tree(s.substr(pstart[cnum], i-pstart[cnum]+1));;
      cnum++;
    }
  }

  // read attributes for this node
  istringstream iss(s.substr(1, pstart[0]-1));
  iss >> node.p;
  if (cnum == 0) {
    node.hasChild = false;
  } else {
    node.hasChild = true;
    iss >> node.feature;
  }
  // save this node and return the index of this node
  nodes.push_back(node);
  return nodes.size()-1;
}

double query(int root, string s) {
  stringstream iss(s);
  string dust; iss >> dust;
  // read features for given animal
  int n; iss >> n;
  vector<string> features(n);
  for (int i = 0; i < n; i++) {
    iss >> features[i];
  }

  // culculate cutiness by tracing the tree
  int idx = root;
  double p = 1.0;
  while (true) {
    p *= nodes[idx].p;
    if (nodes[idx].hasChild == false) break;
    if (find(features.begin(), features.end(), nodes[idx].feature) != features.end()) {
      idx = nodes[idx].ch[0];
    } else {
      idx = nodes[idx].ch[1];
    }
  }
  return p;
}

int main() {
  string tmp;
  getline(cin, tmp);
  int N = s2i(tmp);
  for (int t = 0; t < N; t++) {
    // input
    getline(cin, tmp);
    int L = s2i(tmp);
    string str;
    for (int i = 0; i < L; i++) {
      getline(cin, tmp);
      str += tmp;
    }

    // construct dicision tree
    nodes.clear();
    int root = create_tree(str);

    // output
    cout << "Case #" << t+1 << ":" << endl;
    getline(cin, tmp);
    int A = s2i(tmp);
    for (int i = 0; i < A; i++) {
      // process query
      getline(cin, tmp);
      double answer = query(root, tmp);
      printf("%.7f\n", answer);
    }
  }
}
