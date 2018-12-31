题意：对每个位置上的数字进行等差排列，输出所有的新的数字
思路：
BFS
1.首先建立一个数组放1-9，9个数字分别遍历。N是多大就遍历几次对数字进行操作
2.每次对数组中每个数字的最后一位进行操作，如果是一位数字，就直接取。
如果是多位数字，那么就取所有数字的最后一位，注意此处用%10进行获取最后一位的操作
3.首先用一个数字记录下当前位置，在数组中删除这个位置上的数字。判断最后一位加上K和减去K是否满足条件。
如果满足在此位置上插入新的数字，向后移动坐标。
4.注意最后需要减掉一位坐标再重新进入循环。
5.如果是N为1的情况需要考虑直接返回0-9，因为不可能有从0开始的数字，为1的情况的时候不论相差几位都返回个位数字。
注意：
1.当相差值为0的时候，不论是加还是减都是相同的结果，因此就不需要重复计算，那么需要单独判断一下如果是这种情况直接跳过其中一种情况即可。
class Solution {
public:
    vector<int> numsSameConsecDiff(int N, int K) {
        if(N == 1) return {0,1,2,3,4,5,6,7,8,9};
        vector<int>vec = {1,2,3,4,5,6,7,8,9};
        int temp = 0;
        for(int i = 0; i < N-1; ++i){
            for(int j = 0; j < vec.size(); ++j){
                if(i > 0)temp = vec[j]%10;
                if(i == 0)temp = vec[j];
                int num = vec[j];
                vec.erase(vec.begin()+j);
                if(temp - K >= 0) {
                    vec.insert(vec.begin()+j,num*10 + temp - K);
                    ++j;
                }
                if(K== 0) {
                    --j;
                    continue;
                }
                if(temp + K < 10) {
                    vec.insert(vec.begin()+j,num*10 + temp + K);
                    ++j;
                }
                --j;
            }
        }
        return vec;
    }
};