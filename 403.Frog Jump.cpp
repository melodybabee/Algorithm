题意：
青蛙跳，只能向前跳当前次，比当前次多1或者比当前次少1。判断是否能够跳到终点。
方法一：暴露拆解
思路：
1.在主方法中加入两个参数，一个表示当前的起点位置，一个表示当前的间隔值
2.从起点位置的下一位开始循环，进入循环后计算新的间隔值。
因为跳跃的位置是逐渐递增的，如果新的间隔值比原间隔值+1还要大，那么说明够不上下一个位置，也就更够不上z那么说明不可以跳到下一位，直接返回false
如果新的间隔值比原间隔值-1的距离还要小，那么直接跳过，遍历下一位
3.每找到一个合适的位置之后开始进入递归，重新判断是否能够找到下一位，可以的话返回true
4.循环结束之后判断最后一个坐标是否等于数组的最后一个位置。
class Solution {
public:
    bool canCross(vector<int>& stones, int pos = 0, int gap = 0) {
        for(int i = pos +1; i < stones.size(); ++i){
            int temp = stones[i] - stones[pos];
            if(temp > gap +1) return false;
            if(temp < gap -1) continue;
            if(canCross(stones, i, temp)) return true;
        }
        return pos == stones.size()-1;
    }
};
优化：
1.因为上面的方法不停的进行递归调用，如果是一位一位的增加，那么就是O(n^2)的时间复杂度。
所以需要一个map来把中间递归的状态记录下来。
2.用一个key变量同时表示当前位置和差距值，因为数组的最长长度是1100，2的11次方是2048，因此把间隔值缩小2048倍的话不会有重复的元素
再与当前位置作或操作。
3.如果能在map中找到这个位置，直接返回，没有找到开始进入遍历和递归。
4.最后判断是否在数组的最后位置。
class Solution {
private:
    unordered_map<int,bool>map;
public:
    bool canCross(vector<int>& stones, int pos = 0, int gap = 0) {
        int key = pos | gap << 11;
        if(map.count(key) > 0){
            return map[key];
        }
        for(int i = pos +1; i < stones.size(); ++i){
            int temp = stones[i] - stones[pos];
            if(temp > gap +1) return map[key] = false;
            if(temp < gap -1) continue;
            if(canCross(stones, i, temp)) return map[key] = true;
        }
        return pos == stones.size()-1;
    }
};