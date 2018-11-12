题意：
手里有一把不同面额的硬币，找到最少的硬币个数使得和等于目标值，不能组成目标值返回-1.
方法一：暴力拆解
TLE
思路：
1.把这个问题当作实际问题来思考会发现，为了达到目标值，我们通常会先选择硬币中面额较大的，尽可能多的拿大额硬币。
如果超过了目标范围，退回最后一个，开始往前查找，以此类推。
2.那么我们首先把数组中的硬币从小到大排序，进入递归。
注意递归中的变量包括，原有的硬币数组，数组最后一位的坐标，目标和，当前循环到的数组位置的个数，总个数。
3.当目标值小于0的时候退回，如果等于0，那么返回当前个数和总个数中较小的一个。
4.进入递归，用一个for循环来从后向前循环坐标，，每次重新进入递归都是从最后一位开始计算。每次目标值减去当前值，当前的个数+1。
class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        int n = coins.size()-1;
        int ret = INT_MAX;
        sort(coins.begin(),coins.end());
        helper(coins,n,amount,0,ret);
        return ret == INT_MAX ? -1 : ret;
    }
    
    void helper(vector<int>& coins, int n , int amount,int cur, int &ret){
        if(amount < 0) return;
        if(amount == 0){
            ret = min(ret,cur);
            return;
        }
        for(int i = n; i >= 0; --i){
            helper(coins,i, amount - coins[i], cur+1, ret);
        }
    }
};
优化思路2:暴力拆解优化
思路：
1.优化在helper函数的循环之上，因为方法一的循环需要每次相减，同时新进入递归就从数组的最后一位开始判断，非常耗时。
因此首先需要判断目标值是否能整除最后一位，如果可以整除，那么直接得到结果取较小值返回即可。
如果不行说明有余数，那么把最大的商*值减去后再开始循环。
2.注意第二层循环有一个剪枝操作，for(int i = amount / coins[n]; i >= 0; --i),i是上一位的商，也就是目前较大一位的个数。
先取该位置的最大个数，如果后面的情况不能满足，再慢慢减少个数。
3.注意其中还有一步判断，if(cur + i >= ret -1) break;cur是目前的个数，i是最大的个数，如果cur+i大于res的个数，res是不会被更新的。
但是运行到这一步说明之前一定不能被整除，那么至少还会加上1位才达到目标值，因此是cur+i+1 >= ret;
class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        int n = coins.size()-1;
        int ret = INT_MAX;
        sort(coins.begin(),coins.end());
        helper(coins,n,amount,0,ret);
        return ret == INT_MAX ? -1 : ret;
    }
    
    void helper(vector<int>& coins, int n , int amount,int cur, int &ret){
        if(n < 0) return;
        if(amount % coins[n] == 0){
            ret = min(ret, cur + amount / coins[n]);
            return;
        }
        for(int i = amount / coins[n]; i >= 0; --i){
            if(cur + i >= ret -1) break;
            helper(coins, n-1,amount-i*coins[n],cur+i,ret);
        }
    }
};
方法3:DP,迭代写法
思路：
1.设置一个dp数组，用来记录值为i的时候需要的最小硬币数量
2.因为如果都是值为1的时候硬币数量最多，那么在初始化dp数组的时候设置为目标值+1即可
3.因为第0位需要初始化为0，那么dp数组的大小为目标值+1
4.状态转移方程是遍历硬币数组，新的位置的值就等于少了一个当前硬币值的位置+1
例如取了一个值为5的硬币，那么由于目标值是11，所以知道dp[6]后，在dp[6]的基础之上加上一个值为5的硬币即可
因此状态转移方程是：dp[i] = min(dp[i],dp[i-coins[j]]+1);
4.最后返回目标值位即可。
注意：
因为有可能硬币值过大导致dp数组的下标会小于0，因此状态转移方程之前需要判断坐标大于等于0。
class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        vector<int>dp(amount+1,amount+1);
        dp[0] = 0;
        for(int i = 1; i <= amount; ++i){
            for(int j = 0; j < coins.size();++j){
                if(i-coins[j] >= 0)
                dp[i] = min(dp[i],dp[i-coins[j]]+1);
            }
        }
        return dp[amount] == amount+1 ? -1 : dp[amount];
    }
};
方法4:DP 递归+记忆数组
注意：
1.最后一行写成return memo[amount] == INT_MAX ? -1 : memo[amount];会TLE。
当amount的数量过大时要一个一个重新计算，没有更新到数组中，没有形成DP的形式
class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        vector<int> memo(amount+1,INT_MAX);
        memo[0] = 0;
        return dfs(coins,amount,memo);
    }
    int dfs(vector<int>& coins, int amount,vector<int>&memo){
        if(amount < 0) return -1;
        if(memo[amount] != INT_MAX) return memo[amount];
        for(int i = 0; i < coins.size(); ++i){
            int temp = dfs(coins,amount- coins[i],memo);
            if(temp >= 0) memo[amount] = min(memo[amount], temp+1);
        }
        return memo[amount] = (memo[amount] == INT_MAX) ? -1 : memo[amount];
    }
};
方法5:用hashmap来当记忆数组
注意：
1.在map中查找是否存在某个元素的对应关系用map.count()方法，count()方法中放入key
class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        unordered_map<int,int> map;
        map[0] = 0;
        return dfs(coins,amount,map);
    }
    int dfs(vector<int>& coins, int amount, unordered_map<int,int>&map){
        if(amount < 0) return -1;
        if(map.count(amount)) return map[amount];
        int cur = INT_MAX;
        for(int i = 0; i < coins.size(); ++i){
            int temp = dfs(coins,amount- coins[i],map);
            if(temp >= 0) cur = min(cur, temp+1);
        }
        return map[amount] = (cur == INT_MAX) ? -1 : cur;
    }
};


  