题意：
判断需要删除数组中的几列能使得数组中剩下的元素是排列有序的。
思路：
1.首先循环列，再在列的基础之上循环行，如果下一行该列上的值小于当前行列上的值，说明该列不满足有序排列，需要删除，count+1。
2.比较字母的顺序可以把它们转换为数字进行大小的比较
class Solution {
public:
    int minDeletionSize(vector<string>& A) {
        int count = 0;
        if(A.size() == 1) return 0;
        for(int i = 0 ;i < A[0].size(); ++i){
            for(int j = 1; j < A.size();++j){
                if(A[j][i]-'a' < A[j-1][i]-'a'){
                    ++count;
                    break;
                }
            }
        }
        return count;
    }
};
注意：在单纯是字母的比较中，不转换为数字也可以进行大小顺序的比较。