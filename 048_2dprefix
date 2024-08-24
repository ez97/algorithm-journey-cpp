#include <bits/stdc++.h>
#include <vector>

using namespace std;

// leetcode 304 : 二维区域和检索 - 矩阵不可变 medium
class NumMatrix {
private:
    vector<vector<int>> presum;
public:
    NumMatrix(vector<vector<int>>& matrix) {
        presum.resize(matrix.size() + 1, vector<int>(matrix[0].size() + 1));
        for(int i = 0; i < matrix.size(); i++){
            for(int j = 0; j < matrix[0].size(); j++){
                presum[i+1][j+1] = matrix[i][j] + presum[i+1][j] + presum[i][j+1] - presum[i][j];
            }
        }
    }
    
    int sumRegion(int row1, int col1, int row2, int col2) {
        row2++;
        col2++;
        return presum[row2][col2] - presum[row2][col1] - presum[row1][col2] + presum[row1][col1];
    }
};

class Solution {
public:
    int largest1BorderedSquare(vector<vector<int>>& grid); // leetcode 1139 : 最大的以 1 为边界的正方形 medium
    bool possibleToStamp(vector<vector<int>>& grid, int stampHeight, int stampWidth); // leetcode 2132 : 用邮票贴满网格图 hard
    int fieldOfGreatestBlessing(vector<vector<int>>& forceField); // leetcode LCP 74 :  最强祝福力场 medium
};

int main(){
    return 0;
}

int Solution::largest1BorderedSquare(vector<vector<int>>& grid){
    int m = grid.size(), n = grid[0].size();
        vector<vector<int>> left(m + 1, vector<int>(n + 1));
        vector<vector<int>> up(m + 1, vector<int>(n + 1));
        int maxBorder = 0;
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (grid[i - 1][j - 1] == 1) {
                    left[i][j] = left[i][j - 1] + 1;
                    up[i][j] = up[i - 1][j] + 1;
                    int border = min(left[i][j], up[i][j]);
                    while (left[i - border + 1][j] < border ||
                           up[i][j - border + 1] < border) {
                        border--;
                    }
                    maxBorder = max(maxBorder, border);
                }
            }
        }
    return maxBorder * maxBorder;
}

// 洛谷 P3397 : 地摊 普及-
void DiffMatrixLuogu(){
    int n, m;
    cin >> n >> m;
    vector<vector<int>> matrix(1024, vector<int>(1024, 0));
    for(int i = 0; i < m; i++){
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        matrix[x1][y1]++;
        matrix[x2+1][y2+1]++;
        matrix[x1][y2+1]--;
        matrix[x2+1][y1]--;
    }
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= n; j++){
            matrix[i][j] += matrix[i-1][j] + matrix[i][j-1] - matrix[i-1][j-1];
            cout << matrix[i][j];
            if(j != n){
                cout << " ";
            }
            else {
                cout << '\n';
            }
        }
    }
}

// nowcoder 模板 : 二维差分 https://www.nowcoder.com/practice/50e1a93989df42efb0b1dec386fb4ccc
void DiffMatrixNowcoder(){
    int n, m, q;
    cin >> n >> m >> q;
    vector<vector<int>> grid(1024, vector<int>(1024, 0));
    vector<vector<long long int>> matrix(1024, vector<long long int>(1024, 0));
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            cin >> grid[i][j];
        }
    }
    for(int i = 0; i < q; i++){
        int x1, y1, x2, y2, k;
        cin >> x1 >> y1 >> x2 >> y2 >> k;
        matrix[x1][y1] += k;
        matrix[x2+1][y2+1] += k;
        matrix[x1][y2+1] -= k;
        matrix[x2+1][y1] -= k;
    }
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= m; j++){
            matrix[i][j] += matrix[i-1][j] + matrix[i][j-1] - matrix[i-1][j-1];
            cout << grid[i-1][j-1] + matrix[i][j];
            if(j != m){
                cout << " ";
            }
            else {
                cout << '\n';
            }
        }
    }
}

bool Solution::possibleToStamp(vector<vector<int>>& grid, int stampHeight, int stampWidth){
    int m = grid.size();
    int n = grid[0].size();
    vector<vector<int>> sum(m + 2, vector<int>(n + 2, 0));
    for(int i = 1; i <= m; i++){
        for(int j = 1; j <= n; j++){
            sum[i][j] = grid[i-1][j-1] + sum[i-1][j] + sum[i][j-1] - sum[i-1][j-1];
        }
    }
    vector<vector<int>> diff(m + 2, vector<int>(n + 2, 0));
    for(int i = 1; i + stampHeight - 1 <= m; i++){
        for(int j = 1; j + stampWidth - 1 <= n; j++){
            int i2 = i + stampHeight - 1;
            int j2 = j + stampWidth - 1;
            if(sum[i2][j2] - sum[i2][j - 1] - sum[i - 1][j2] + sum[i - 1][j - 1] == 0){
                diff[i][j]++;
                diff[i][j2 + 1]--;
                diff[i2 + 1][j]--;
                diff[i2 + 1][j2 + 1]++;
            }
        }
    }

    for(int i = 1; i <= m; i++){
        for(int j = 1; j <= n; j++){
            diff[i][j] += diff[i - 1][j] + diff[i][j - 1] - diff[i - 1][j - 1];
            if(diff[i][j] == 0 && grid[i - 1][j - 1] == 0){
                return false;
            }
        }
    }

    return true;
}

int Solution::fieldOfGreatestBlessing(vector<vector<int>>& forceField){ // TODO : 需要复习离散化
    vector<long long> xs, ys;
    for (auto& f : forceField) {
        long long i = f[0], j = f[1], side = f[2];
        xs.push_back(2 * i - side);
        xs.push_back(2 * i + side);
        ys.push_back(2 * j - side);
        ys.push_back(2 * j + side);
    }

    // std::unique(first, end) -> new end iterator
    sort(xs.begin(), xs.end());
    xs.erase(unique(xs.begin(), xs.end()), xs.end());
    sort(ys.begin(), ys.end());
    ys.erase(unique(ys.begin(), ys.end()), ys.end());

    int n = xs.size();
    int m = ys.size();
    vector<vector<int>> diff(n + 2, vector<int>(m + 2, 0));

    for (auto& f : forceField) {
        long long i = f[0], j = f[1], side = f[2];
        int r1 =
            lower_bound(xs.begin(), xs.end(), 2 * i - side) - xs.begin();
        int r2 =
            lower_bound(xs.begin(), xs.end(), 2 * i + side) - xs.begin();
        int c1 =
            lower_bound(ys.begin(), ys.end(), 2 * j - side) - ys.begin();
        int c2 =
            lower_bound(ys.begin(), ys.end(), 2 * j + side) - ys.begin();

        ++diff[r1 + 1][c1 + 1];
        --diff[r1 + 1][c2 + 2];
        --diff[r2 + 2][c1 + 1];
        ++diff[r2 + 2][c2 + 2];
    }

    int ans = 0;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            diff[i][j] +=
                diff[i - 1][j] + diff[i][j - 1] - diff[i - 1][j - 1];
            ans = max(ans, diff[i][j]);
        }
    }

    return ans;
}