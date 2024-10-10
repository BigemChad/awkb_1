#include <bits/stdc++.h>

using namespace std;

struct Node {
    vector<string> edgesTo; //
    char key;
    Node(char input) : key(input) {}
};

bool isLinear(const vector<Node*>& m_vert) {
    int count1, count2 = 0;                 

    for (const auto& node : m_vert) {
        int degree = node->edgesTo.size();
        if (degree == 1) {
            count1++;
        } else if (degree == 2) {
            count2++;
        } else {
            return false;
        }
    }
    return count1 == 2 && count2 == (m_vert.size() - 2);
}

void dfs(Node* node, unordered_set<char>& visited, const vector<Node*>& m_vert) {
    visited.insert(node->key);
    for (const string& neighbor : node->edgesTo) {
        auto it = find_if(m_vert.begin(), m_vert.end(), [&](Node* n) { return n->key == neighbor[0]; });
        if (it != m_vert.end() && visited.find((*it)->key) == visited.end()) {
            dfs(*it, visited, m_vert);
        }
    }
}

bool isConnected(const vector<Node*>& m_vert) {
    if (m_vert.empty()) return true;
    unordered_set<char> visited;
    dfs(m_vert[0], visited, m_vert);
    return visited.size() == m_vert.size();
}


int main(int argc, char* argv[]) {
    if(argc != 3) {
        cout << "brak podanego wejścia" << endl;
        exit;
    }
    
    ifstream m_inputFile;
    m_inputFile.open(argv[1]);
    string l_temp;
    vector<Node*> m_vert;
    while(getline(m_inputFile, l_temp)) {
            m_vert.push_back(new Node(l_temp[0]));
        }
    m_inputFile.close();
    m_inputFile.open(argv[1]);
    for(auto el : m_vert) { 
        getline(m_inputFile, l_temp);
        stringstream ss(l_temp);
        istream_iterator<string> begin(ss);
        istream_iterator<string> end;
        vector<string> vs(begin, end);
        for (int i = 1; i < vs.size(); i++) {
            el->edgesTo.push_back(vs[i]);
        }
    }
     m_inputFile.close();

    for (auto el : m_vert) {
        cout << el->key << " -> ";
        for (auto it = el->edgesTo.begin(); it!= el->edgesTo.end(); ++it) {
            cout << *it << " ";
        }
        cout << endl;
    }

    if (isConnected(m_vert)){
            cout << "Graf jest sprzężony" << endl;
        if (isLinear(m_vert)) {
            cout << "Graf jest liniowy" << endl;
        }
    }

    return 0;
}
    