题意：从首尾选择数字判断第一个人是否能赢
方法一：递归，从上到下解题
T(n) = O(2^n);
思路：
1.本题仍然运用minimax的思路，如果第一个人想赢，那么直接只要第二个人返回false就可以
2.那么需要一个变量记录当前是哪个玩家在玩，分别需要一个变量来记录两个玩家当前的总和值
如果数组为空，直接比较第一个玩家和第二个玩家的大小，返回；
如果当前数组的大小为1，那么判断是哪个玩家在玩，分别相加，判断返回
3.如果数组长度比较长，那么设置两个数组分别去掉头部元素和尾部元素，分两个玩家的两种情况进行讨论
只要对方在两种情况的数组中返回其中一个是false,那么表示当前玩家赢。因为是从玩家1开始，所以递归到最后返回的就是玩家1的状态
class Solution {
public:
    bool PredictTheWinner(vector<int>& nums) {
        return helper(nums, 0, 0, 1);
    }
    
    bool helper(vector<int>& nums, int sum1,int sum2, int player){
        if(nums.empty()) return sum1 >= sum2;
        if(nums.size() == 1){
            if(player == 1) return sum1 + nums[0] >= sum2;
            else if(player == 2) return sum2 + nums[0] > sum1;
        }
        vector<int>sub1 = vector<int>(nums.begin()+1,nums.end());
        vector<int>sub2 = vector<int>(nums.begin(),nums.end()-1);
        if(player == 1){
            return !helper(sub1, sum1+nums[0],sum2,2) || !helper(sub2, sum1+nums.back(),sum2,2);
        }else if(player == 2){
            return !helper(sub1, sum1,sum2+nums[0],1) || !helper(sub2, sum1,sum2 + nums.back(),1);
        }
    }
};

方法2:dp【需要复习】
T(n) = O(n^2);
思路：
1.设置一个二维数组,从底向上进行递归，符合minimax的核心思想，需要知道结果倒推。dp[i][j]表示在原数组的i-j之间能取到的最大的值
2.从底部循环，从二位数字开始更新，作为初始化。
开始向上更新dp[i][j]的动态转移方程是用原数组上的数字分别减去首尾之后的较大值。
3.最后判断在dp[0][n-1]范围上的的值是否是大于等于0的，如果大于等于0说明1号玩家可以赢，否则是二号玩家赢
class Solution {
public:
    bool PredictTheWinner(vector<int>& nums) {
        vector<vector<int>>dp(nums.size(),vector<int>(nums.size(),0));
        for(int i = nums.size()-1; i >= 0; --i){
            for(int j = i+1; j < nums.size(); ++j){
                dp[i][j]= max(nums[i]-dp[i+1][j], nums[j]-dp[i][j-1]);
            }
        }
        return dp[0][nums.size()-1] >= 0;
    }
};