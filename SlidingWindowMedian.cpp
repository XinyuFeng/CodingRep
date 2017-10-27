vector<double> SlidingWindow::Sliding1D(vector<int>& arr, int k) {
    multiset<int> small, large;
    vector<double> ans;
    for (int i = 0; i < arr.size(); ++i) {
        small.insert(arr[i]);
        large.insert(*small.rbegin());
        small.erase(*small.rbegin());
        if (large.size() > small.size()) {
            small.insert(*large.begin());
            large.erase(large.begin());
        }
        if (i >= k) {//delete
            if (small.count(arr[i - k])) {
                small.erase(small.find(arr[i - k]));
                if (small.size() < large.size()) {
                    small.insert(*large.begin());
                    large.erase(large.begin());

                }
            }
            else {
                large.erase(large.find(arr[i - k]));
                if (large.size() + 2 == small.size()) {
                    large.insert(*small.rbegin());
                    small.erase(--small.end());
                }
            }
            
        }
        if (i >= k - 1) {
            ans.push_back(small.size() == large.size()? ((double) *small.rbegin() + (double) *large.begin()) / 2 : (double) *small.rbegin());
        }

    }
    return ans;
}



//////////////////////////////////
double findMedian(multiset<int>& small, multiset<int>& large) {
    return small.size() == large.size()? ((double) *small.rbegin() + (double) *large.begin()) / 2 : (double) *small.rbegin();
}

void addNum(multiset<int>& small, multiset<int>& large, int num){
    small.insert(num);
    large.insert(*small.rbegin());
    small.erase(*small.rbegin());
    if (large.size() > small.size()) {
        small.insert(*large.begin());
        large.erase(large.begin());
    }
}

void delNum(multiset<int>& small, multiset<int>& large, int num){
    if (small.count(num)) {
        small.erase(small.find(num));
        if (small.size() < large.size()) {
            small.insert(*large.begin());
            large.erase(large.begin());
            
        }
    }
    else {
        large.erase(large.find(num));
        if (large.size() + 2 == small.size()) {
            large.insert(*small.rbegin());
            small.erase(--small.end());
        }
    }
}
vector<vector<double>> SlidingWindow::Sliding2D(vector<vector<int>>& mat, int m) {
    
    int len = mat.size();
    int w = len - m + 1;
    vector<vector<double>> ans(w, vector<double>(w, 0));
    
    multiset<int> small, large;
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < m; ++j) {
            addNum(small, large, mat[i][j]);

        }
    }
    int dx = 0, dy = 1;
    int cnt = 1;
    ans[0][0] = findMedian(small, large);
    int i = 0, j = m;
    while (true) {
        //go to right
        while (j < len) {
            for (int r = 0; r < m; ++r) {//O(n^2mlogm)
                addNum(small, large, mat[i + r][j]);
            }
            for (int r = 0; r < m; ++r) {
                delNum(small, large, mat[i + r][j - m]);
            }
            ans[i][j - m + 1] = findMedian(small, large);
            j++;
        }
        j--;

        //go to down or break
        if (i + m >= len) break;
        for (int c = 0; c < m; ++c) {
            addNum(small, large, mat[i + w][j - c]);
        }
        for (int c = 0; c < m; ++c) {
            delNum(small, large, mat[i][j - c]);
        }
        i++;
        ans[i][j - m + 1] = findMedian(small, large);

        
        //go to left
        while (j >= m) {
            for (int r = 0; r < m; ++r) {
                addNum(small, large, mat[i + r][j - m]);
            }
            for (int r = 0; r < m; ++r) {
                delNum(small, large, mat[i + r][j]);
            }
            ans[i][j - m] = findMedian(small, large);
            j--;
        }

        //go to down or break
        if (i + m >= len) break;
        for (int c = 0; c < m; ++c) {
            addNum(small, large, mat[i + w][j - c]);
        }
        for (int c = 0; c < m; ++c) {
            delNum(small, large, mat[i][j - c]);
        }
        i++;
        ans[i][j - m + 1] = findMedian(small, large);
    }
    return ans;
}



