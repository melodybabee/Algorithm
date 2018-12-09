题意：
判断每一行的相同位置的字母是不是字典序的，如果后面的单词比前一个单词大，删除某一列使其仍然是字典序。求出最少删除的列数。
思路：
1.注意本题中判断的是单词的大小不仅仅是首字母的大小，因此如果两个字母字母相同，还需要判断下一位大小，直到比出来大小为止。
2.从每个单词开始循环，如果相等继续比下一位，如果当前位已经在set中出现，那么继续比下一位。
如果后面比前面小，那么把当前列放到set中去，要从头开始比较，因为如果在后面删除了某一列，有可能会改变前面的顺序，因此要重新判断。
class Solution {
public:
    int minDeletionSize(vector<string>& A) {
        unordered_set<int>set;
        for(int i= 1 ; i < A.size();++i){
            for(int j = 0; j < A[0].size();++j){
                if(set.count(j) || A[i][j] == A[i-1][j]) continue;
                if(A[i][j] < A[i-1][j]){
                   set.insert(j);
                    i = 0;
                }
                break;
            }
        }
        return set.size();
    }
};