题意：数组中相邻的两个数字如果都可以相加为完全平方数，那么计数器+1，返回数组全排列能形成这样的数组的个数。
思路：【重点复习】
1.整体的思路是把数组全排列再依次遍历两两进行比较，不断递归
2.那么递归的终止条件就是如果最后的坐标位置是数组的长度了，那么计数器+1
3.首先把数组排序，记录初始值，从0开始。从头部开始遍历，不断与头部的元素进行交换，如果两个元素值相等的话跳过。
否则交换两个值，如果交换后满足完全平方数，那么进入递归
注意：判断是否满足完全平方的操作是通过固定的指针index来判断的，i只起到了交换全排列的作用
4.判断是否是完全平方数，先开方，再相乘判断是否等于原数字
class Solution {
public:
    int numSquarefulPerms(vector<int>& A) {
        sort(A.begin(),A.end());
        int count = 0;
        findsq(A,count,0);
        return count;
    }
    
    void findsq(vector<int> A, int &count, int index){
        if(index == A.size()) ++count;
        for(int i = index; i < A.size(); ++i){
            if(i > index && A[i] == A[index]) continue;
            swap(A[i],A[index]);
            if((index== 0) || (index > 0 && issq(A[index]+A[index-1]))){
                findsq(A,count,index+1);
            }
        }
    }
    
    bool issq(int num){
        int temp = sqrt(num);
        return temp*temp ==  num;
    }
};