题意：
找到数组中的子数组，其中子数组中数字的个数等于K
思路：
1.不能单纯只用双指针和一个map来表示，因为这种情况下，所有得到的结果都是连续的子数组，对于不连续的数组就会被忽略掉
2.所以对数组进行两次调用，每次找到最多包括K个数字的数组个数，那么如果想准确找到一共有K个数字的数组，就用找到至少有K个数字的数组减去至少有K-1个数组的数组
3.每次新加入进来的数组就是从自己开始到头部结点的所有子数组个数
class Solution {
public:
    int subarraysWithKDistinct(vector<int>& A, int K) {
        return mostnum(A,K) - mostnum(A,K-1);
    }
    
    int mostnum(vector<int>& A, int K){
        unordered_map<int,int>map;
        int left = 0;
        int res = 0;
        for(int i = 0 ; i < A.size(); ++i){
            ++map[A[i]];
            while(map.size() > K){
                --map[A[left]];
                if(map[A[left]] == 0) map.erase(A[left]);
                ++left;
            }
            res += i- left + 1;
        }
        return res;
    }
};