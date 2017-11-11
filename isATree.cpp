//
//  isATree.cpp
//  practice
//
//  Created by Feng Xinyu on 11/9/17.
//  Copyright © 2017 Feng Xinyu. All rights reserved.
//

#include <stdio.h>
#include <string>
#include <iostream>
#include <set>
#include <vector>
#include <unordered_map>
#include <queue>
using namespace std;

char check(unordered_map<char, set<char>>& tree, unordered_map<char, int>& degree, string& ans) {
    
    int cnt = 0;
    int roots = 0;
    vector<int> T;
    int edges = 0;
    char root = ' ';
    for (auto it = degree.begin(); it != degree.end(); ++it) {
        cnt++;
        edges += it->second;
        if (it->second == 0) {
            roots++;
        }

    }
    
    if (roots > 1) {
        if ("E4" < ans) {
            ans = "E4";
        }
    }
    
    if (edges != cnt - 1) {
        if ("E5" < ans) {
            ans = "E5";
        }
    }
    return root;
 
}


string build(unordered_map<char, set<char>> tree, char root) {
    if (!tree.count(root) || !tree[root].size()) return '(' + string(1, root) + ')';
    string ans = '(' + string(1, root);
    for (char c: tree[root]) {
        ans += build(tree, c);
    }
    ans += ')';
    return ans;
}

class UF {
public:
    int root[26] = {0};
    UF(){};
    void init() {
        for (int i = 0; i < 26; ++i) {
            root[i] = i;
        }
    }
    
    int find(int id) {
        while (id != root[id]) {
            root[id] = root[root[id]];
            id = root[id];
        }
        return id;
    }
    
    bool _union(int i, int j) {
        int p1 = find(i);
        int p2 = find(j);
        if (p1 == p2) return false;
        root[p1] = p2;
        return true;
    }
    
};
string isATree(vector<vector<char>>& node) {
    unordered_map<char, set<char>> tree;
    unordered_map<char, int> degree;
    string ans = "E6";
    UF uf;
    uf.init();
    for (int i = 0; i < node.size(); ++i) {
        
        auto pair = node[i];
        if (!uf._union(pair[0] - 'A', pair[1] - 'A')) {
            if ("E3" < ans) {
                ans = "E3";
            }
        }
        if (tree.count(pair[0]) && tree[pair[0]].count(pair[1])) {
            //Duplicate edges
            if ("E2" < ans) {
                ans = "E2";
            }
        }
        else if (tree.count(pair[0]) && tree[pair[0]].size() == 2) {
            ans = "E1";
        }
        tree[pair[0]].insert(pair[1]);
        if (!degree.count(pair[0])) {
            degree[pair[0]] = 0;
        }
        degree[pair[1]]++;
        
    }
    
    char root = check(tree, degree, ans);
    if (ans != "E6") return ans;
    
    return build(tree, root);
    
}

//int main() {
//    vector<vector<char>> input1 = {{'B', 'D'}, {'D', 'E'}, {'A', 'B'}, {'C', 'F'}, {'E', 'G'}, {'A', 'C'}};
//    vector<vector<char>> input2 = {{'A', 'B'}, {'A', 'C'}, {'B', 'D'}, {'E', 'F'}};
//    cout<<isATree(input2);
//}
