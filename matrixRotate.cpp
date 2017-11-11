//
//  matrixRotate.cpp
//  practice
//
//  Created by Feng Xinyu on 11/9/17.
//  Copyright © 2017 Feng Xinyu. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include <vector>
using namespace std;

vector<vector<int>> matrixRotate(vector<vector<int>>& mat) {
    size_t m = mat.size();
    size_t n = mat[0].size();
    vector<vector<int>> ans(n, vector<int>(m, 0));
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            ans[n - j - 1][i] = mat[i][j];
        }
    }
    return ans;
    
}

//int main() {
//    vector<vector<int>> input = {{1,2,3},{4,5,6}, {7,8,9}, {10,11,12}};
//    auto ans = matrixRotate(input);
//    for (int i = 0; i < ans.size(); ++i) {
//        for (int j = 0; j < ans[0].size(); ++j) {
//            cout<< ans[i][j]<<' ';
//        }
//        cout<<endl;
//    }
// }
