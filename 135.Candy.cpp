题意：
小朋友分糖，积分比隔壁高的人得到的糖也需要比隔壁高，问最少需要多少糖
方法一：两次遍历
1.类似于依照题意暴力求解，首先每个人发一个糖，从左到右遍历，如果分数比左侧高，那么糖数+1
2.与左侧比较完之后还需要和右侧进行比较，所以再次从右向左遍历，注意此处除了判断积分高低之外，如果当前已经满足条件了，那么不需要移动了
因此还需要判断结果数组中的值是否小于等于右侧的，如果小于，那么再更新为右侧的数值+1
3.最后返回结果数组中所有值的和
class Solution {
public:
    int candy(vector<int>& ratings) {
        vector<int>ret(ratings.size(),1);
        for(int i = 1; i < ratings.size();++i){
            if(ratings[i] > ratings[i-1]) ret[i] = ret[i-1]+1;
        }
        for(int i = ratings.size()-2; i >= 0; --i){
            if(ratings[i] > ratings[i+1] && ret[i] <= ret[i+1]) ret[i] = ret[i+1] +1;
        }
        return accumulate(ret.begin(),ret.end(),0);
    }
};