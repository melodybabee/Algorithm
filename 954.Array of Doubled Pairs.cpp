题意：
判断数组中的数组顺序是否能够满足A[2 * i + 1] = 2 * A[2 * i]
思路：
1.因为需要根据数字出现的次数进行判断，那么需要建立一个哈希表来存储数字和其对应的次数。
2.对原数组进行排序，从头部开始判断。
如果二倍的数字存在且大于等于1，那么找到一对，对两个数字都减1.
或者如果数字可以整除2且能找到整除2的数字而且大于等于1，那么两个数字减1.
如果都没有，说明查找失败，返回false;
还需要判断循环到的数字在map中的值是否大于0，因为有可能存在但是已经被比较过因此存在值为0，遇到这种情况跳过。
3.循环结束没有返回false，那么返回true
class Solution {
public:
    bool canReorderDoubled(vector<int>& A) {
        unordered_map<int,int>map;
        for(auto a: A){
            ++map[a];
        }
        sort(A.begin(),A.end());
        for(auto i : A){
            if(map[i] > 0){
                if(map.count(2*i) && map[2*i] >= 1) --map[2*i];
                else if(i %2 == 0 && map.count(i/2) && map[i/2] >= 1) --map[i/2];
                else return false;
                --map[i];
            }else continue;
        }
        return true;
    }
};