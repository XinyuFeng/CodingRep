//
//  delAndEarn.cpp
//  practice
//
//  Created by Feng Xinyu on 11/9/17.
//  Copyright © 2017 Feng Xinyu. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <set>
using namespace std;

int delAndEarn(vector<int> arr) {
    unordered_map<int, int> T;
    set<int> num;
    for (int i = 0; i < arr.size(); ++i) {
        T[arr[i]] += arr[i];
        num.insert(arr[i]);
    }
    
    int maxNum = *num.rbegin();
    vector<int> dp(maxNum + 1, 0);
    for (int n: num) {
        dp[n] = max(dp[n - 1], dp[max(n - 2, 0)] + T[n]);
    }
    return dp[maxNum];
    
}

//int main() {
//    vector<int> arr = {2,3,4,2};
//    cout<<delAndEarn(arr);
//}
