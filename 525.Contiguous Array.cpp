题意：
在只有0，1的数组中，找到0和1个数相等的最长子数组的长度。
思路：
1.本题中需要找到0，1个数相等的情况，那么用到个一个技巧就是判断两者是否匹配的时候都可以用到计数器。
遇到1，计数器+1，遇到0，计数器-1，如果计数器的个数为0，就说明0，1的个数相等。
2.那么建立一个哈希表，key用来存计数器的值，value用来存得到这个值的坐标位置。
3.开始遍历数组，不断累加，如果计数器的值能在map中找到，就说明两个坐标结点的位置上的0，1个数相等。
那么直接对坐标进行相减即可。
如果不能找到就在map中插入这个值。
4.注意因为坐标从0开始，所以需要在map中创建一个初始对,key为0，value为-1，表示对第一个元素进行操作。
class Solution {
public:
    int findMaxLength(vector<int>& nums) {
        int total = 0;
        int ret = 0;
        unordered_map<int,int>map{{0,-1}};
        for(int i = 0;i < nums.size(); ++i){
            total += nums[i] == 0 ? -1 : 1;
            if(map.count(total)){
                ret = max(ret,i-map[total]);
            }else{
                map[total] = i;
            }
        }
        return ret;
    }
};