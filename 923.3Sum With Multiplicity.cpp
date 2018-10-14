题意：
给一个数组和一个目标值，找出满足三个子数组的和等于目标值的所有情况个数。
（可重复的3Sum题）
思路：
1.在寻找满足求和情况的思路和3sum（第15题）完全相同，固定头结点位置，用双指针找满足条件的情况
【注意双指针的使用从分别从头尾开始最为高效】
2.注意重复情况的判断：
当与目标值相等的时候：
比如[1,1,2,2,3,3,4,4,5,5]，当第一个指针指向2，2重复，那么向后移动，但是次数要加为2
同理，当为指针指向5，5重复，5向前移动，次数同样加2
那么【1，2，2，5，5】的组合一共就有2*2四种答案，满足情况
移动到下一位不等于本身的位置之后，重新进入while循环
3.上述情况在【1，1，2，2，2，2】的时候不满足，因为只有一个指针会一直移动直到与另一个指针汇合
那么就需要在与目标值相等的时候对当时所处的头尾指针进行再判断
如果相等，那么直接用等差数列的公式计算结果，手动使头尾指针汇合结束循环即可
比如【2，2，2，2】那么会有3*2= 6 种情况
4.因为涉及计算(p-j)*(p-j+1)，那么当数组中有过多的数字的时候，会超出int范围
那么ret需要设置为long long, 因为最后返回的是int类型，那么还需要一步转换 return (int)ret;
注意：
1.题目中As the answer can be very large, return it modulo 10^9 + 7.的意思是对最后的结果取余处理
10^9 == 1e9;
int mod = (int)1e9 + 7;
返回之前%mod即可。
class Solution {
public:
    int threeSumMulti(vector<int>& A, int target) {
        long long ret = 0;
        int mod = (int)1e9 + 7;
        sort(A.begin(),A.end());
        for(int i = 0; i< A.size() -2; ++i){
            long long j = i +1;
            long long p = A.size()-1;
            while(j < p){
                int countj = 1;
                int countp = 1;
                if(A[i] + A[j] + A[p] == target){
                    if(A[j] == A[p]){
                        ret += (p-j)*(p-j+1)/2;
                        j = p;
                    }else{
                    while(j + 1 < p && A[j+1] == A[j]) {
                        ++countj;
                        ++j;
                    }
                    while(j +1 < p && A[p-1] == A[p]){
                        ++countp;
                        --p;
                    }
                    ret += countj*countp;
                    ++j;
                    --p;
                    }
                }else if(A[i] + A[j] + A[p] < target){
                    ++j;
                }else{
                    --p;
                }
            }
        }
        ret = ret % mod;
        return (int)ret;
    }
};
