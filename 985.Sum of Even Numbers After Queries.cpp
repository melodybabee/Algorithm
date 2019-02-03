题意：用一个数组来更新另一个数组，每次求出偶数坐标位置上的和，返回结果数组。
方法一：暴力求解
思路：
1.建立结果数组，用query数组对A进行更新，更新之后遍历新的A数组，对所有偶数坐标上的值求和。
2.把和的结果更新到结果数组中，返回即可。
class Solution {
public:
    vector<int> sumEvenAfterQueries(vector<int>& A, vector<vector<int>>& queries) {
        vector<int>ans(queries.size());
        for(int i = 0; i < queries.size(); ++i){
            A[queries[i][1]] += queries[i][0];
            int sum = 0;
            for(int j = 0; j < A.size();++j){
                if(A[j] %2 == 0){
                    sum += A[j];
                }
            }
            ans[i] = sum;
        }
        return ans;
    }
};
优化：
利用偶数的性质，只有偶数+偶数才是偶数，偶数+奇数=奇数，降低时间复杂度
思路：
1.首先记录下来所有位置上是偶数的总和，再对query数组进行遍历，如果遍历到的位置上是偶数，减去这个数字
2.再在这个位置上相加query中的数值，如果这个被更新的位置仍然是偶数，那么返回这个结果，同时更新sum的值，如果不是偶数，那么直接返回sum值
class Solution {
public:
    vector<int> sumEvenAfterQueries(vector<int>& A, vector<vector<int>>& queries) {
        vector<int>ans(queries.size());
        int sum = 0;
        for(int i = 0; i < A.size();++i){
            if(A[i] %2 == 0){
                sum += A[i];
            }
        }
        for(int i= 0; i < queries.size(); ++i){
            if(A[queries[i][1]] %2 == 0){
                sum -= A[queries[i][1]];
            }
            A[queries[i][1]] += queries[i][0];
            ans[i] = (A[queries[i][1]]) % 2 == 0 ? sum += A[queries[i][1]] : sum;
        }
        return ans;
    }
};