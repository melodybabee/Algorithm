题意：
一辆车可以在加油站加油，从一个加油站到另一个需要一定的花费。
找到可以遍历一整圈的起点。
方法一：遍历判断
思路：
1.因为需要找到起点位置，那么能继续往下走的条件就是油量-花费要大于等于0.
2.因为题目中说明了本题只会有一个有效的结果，因此从头部开始循环判断，分别用sum和total来记录下当前总和和全局的总和
3.如果sum不能满足大于等于0，那么说明这一位不能作为起始位置，目标位跳到下一位，sum清零
4.最后判断total是否大于等于0，如果小于0说明不能完成环状，那么返回-1，如果可以的话返回目标起始位置
class Solution {
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        int start = 0;
        int sum = 0;
        int total = 0;
        for(int i = 0; i< gas.size(); ++i){
            sum += gas[i] - cost[i];
            total += gas[i] - cost[i];
            if(sum < 0){
                start = i+1;
                sum = 0;
            }
        }
        return total < 0 ? -1 : start;
    }
};
贪心的思想体现在，每次保证当前次的状态即可，保证局部最优，最后由局部最优得到全局最优。

方法二：从后向前遍历
思路：
1.从后向前遍历数组，每次计算出差值。在最开始设置一个初始值为-1，那么只要差值大于这个目标值，就说明这个位置可以作为起点
表示从当前位置到末尾都不会出现油不够加的情况。那么更新起点位置，同时把目标值更新为新的差值。
2.而一旦遍历到的当前位置差值小于0，那么说明此处开始到最后的过程中油会不够加，那么就不更新。
3.最后仍然判断total是否大于0，只要加的油大于花费，那么就可以找到唯一的起点，返回起点即可。
class Solution {
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        int start = 0;
        int total = 0;
        int mx = -1;
        for(int i = gas.size() -1; i >= 0; --i){
            total += gas[i] - cost[i];
            if(total > mx){
                start = i;
                mx = total;
            }
        }
        return total < 0 ? -1 : start;
    }
};