immutable 不变的
题意：
在不可改变的的数组中返回指定坐标区间内的和。
方法一：for循环
思路：
1.在NumArray构造器中进行初始化，不要忘记声明一个属性值便于各个方法的调用
2.在进行和运算的方法中遍历即可
class NumArray {
private:
    vector<int>sum;
public:
    NumArray(vector<int> nums) {
        sum = nums;
    }
    
    int sumRange(int i, int j) {
        int ret = 0;
        for(int p = i; i <=j ;++i){
            ret += sum[i];
        }
        return ret;
    }
};

/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray obj = new NumArray(nums);
 * int param_1 = obj.sumRange(i,j);
 */
方法二：DP
思路：
1.设置一个dp[i]记录从0-i位置的和
2.在求区间和的范围内，如果i为0，那么直接返回尾部的坐标，如果不为0，那么返回尾部坐标-头部-1的位置
注意要头部-1才是要求的范围
class NumArray {
private:
    vector<int>dp;
public:
    NumArray(vector<int> nums) {
        dp = nums;
        for(int i = 1; i < nums.size(); ++i){
            dp[i] += dp[i-1];
        }
    }
    
    int sumRange(int i, int j) {
        return i == 0 ? dp[j] : dp[j] - dp[i-1];
    }
};

/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray obj = new NumArray(nums);
 * int param_1 = obj.sumRange(i,j);
 */