题意：
在只存在0,1,0,1的数组中找到和等于目标值的子数组个数。
思路：
1.开始想的是两个for循环遍历的方法，TLE
2.后来再想，从0,1特征入手，如果开始值就大于目标元素，那么重新进入循环
如果等于目标值，计数，同时判断这个元素后面有几个0，有几个0计数加几
如果小于目标值，相加，同时对目标值相减操作，如果目标值为0，那么找最后一位后面有几个0
最后输出总的计数。这样去掉了一个循环，可以AC。
注意：
1.因为在小于目标值的时候需要对目标值进行相减操作，因此每次进入这个循环都需要用一个变量来替换目标值，不然影响下一次循环
2.注意数组的边界，因为进入while循环之后会++j,这样有可能超过长度，因此要用j+1与长度进行判断
class Solution {
public:
    int numSubarraysWithSum(vector<int>& A, int S) {
        int ret = 0;
        for (int i = 0; i < A.size();++i){
            if(A[i] > S) continue;
            if(A[i] == S) {
                ++ret;
                int j = i;
                while(j+1 < A.size() && A[j+1] == 0){
                    ++ret;
                    ++j;
                }
            }
            if(A[i] < S){
                int temp = S;
                int j = i;
                temp -= A[j];
                while(j+1 < A.size() && temp > 0){
                    ++j;
                    temp -= A[j];
                }
               
                if(temp > 0) continue;
                ++ret;
                while(j+1 < A.size() && A[j+1] == 0){
                    ++ret;
                    ++j;
                }
            }
        }
        return ret;
    }
};
优化：
有非常简单的DP做法，没有理解思路，待学习。