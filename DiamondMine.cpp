//
//  DiamondMine.cpp
//  practice
//
//  Created by Feng Xinyu on 11/11/17.
//  Copyright © 2017 Feng Xinyu. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <set>
using namespace std;

int maxMine(vector<vector<int>>& mat) {
    size_t m = mat.size();
    size_t n = mat[0].size();
    int dp[m + 1][n + 1];
    
    memset(dp, 0, sizeof(dp));
    memset(dp[0], -1, sizeof(dp[0]));
    for (int i = 0; i <= m; ++i) {
        dp[i][0] = -1;
    }
    dp[1][0] = 0;
    int ans = 0;
    for (int j = 1; j <= n; ++j) {
        for (int i = 1; i <= m; ++i) {
            if (mat[i - 1][j - 1] >= 0) {
                if (dp[i][j - 1] == -1 && dp[i - 1][j] == -1) {
                    dp[i][j] = -1;
                }
                else {
                    dp[i][j] = max(dp[i][j - 1], dp[i - 1][j]) + mat[i - 1][j - 1];
                    //mat[i - 1][j - 1] = 0;
                }
            }
            else {
                dp[i][j] = -1;
            }
        }
    }
    ans = max(ans, dp[m][n]);
    
    if (ans > 0) {
        int i = m, j = n;
        while (i > 1 || j > 1) {
            int tmp = mat[i - 1][j - 1];
            mat[i - 1][j - 1] = 0;
            if (dp[i][j] == dp[i][j - 1] + tmp) {
                j--;
            }
            else {
                i--;
            }
        }
    }
    
    memset(dp, 0, sizeof(dp));
    memset(dp[0], -1, sizeof(dp[0]));
    for (int i = 0; i <= m; ++i) {
        dp[i][0] = -1;
    }
    dp[1][0] = 0;
    for (int j = 1; j <= n; ++j) {
        for (int i = 1; i <= m; ++i) {
            if (mat[i - 1][j - 1] >= 0) {
                if (dp[i][j - 1] == -1 && dp[i - 1][j] == -1) {
                    dp[i][j] = -1;
                }
                else {
                    dp[i][j] = max(dp[i][j - 1], dp[i - 1][j]) + mat[i - 1][j - 1];
                    //mat[i - 1][j - 1] = 0;
                }
            }
            else {
                dp[i][j] = -1;
            }
        }
    }

    
    if (dp[m][n] > 0) {
        ans += dp[m][n];
    }
    
    return ans;
}

int main() {
    vector<vector<int>> input = {{0,1,-1},{1,0,-1},{1,1,1}};
    cout<<maxMine(input);
    return 0;
}
