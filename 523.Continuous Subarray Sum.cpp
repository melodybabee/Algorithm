题意：
找数组中是否存在长度大于2，和是目标值倍数的子数组。
方法一：建立累加和数组
思路：
1.注意除法的题目需要注意被除数不为0；
2.找数组中的子数组如果用两层遍历耗时过长，可以在第一层循环内部建立累加和数组，重新定义一个数组初始化再进入下一层循环。
3.如果k不为0且和对k取余等于0，返回true；或者两者相等（包括等于0）的时候返回true.
class Solution {
public:
    bool checkSubarraySum(vector<int>& nums, int k) {
        for(int i = 0 ; i < nums.size();++i){
            int sum = nums[i];
            for(int j = i+1; j < nums.size(); ++j){
                sum += nums[j];
                if(k!= 0 && sum % k == 0 ) return true;
                if(sum == k) return true;
            }
        }
        return false;
    }
};
方法二：Math
思路：
1.通过定理，若数字a和b分别除以数字c，若得到的余数相同，那么(a-b)必定能够整除c
2.建立一个哈希表，key位置记录下每个子数组的余数，	value位置记录下当前的起点。
如果后面的数组再次求余数等于之前的余数且两者之间的坐标距离大于1，那么返回true。
如果没有，在map中新放入对应的余数和坐标。
3.如果都没找到返回false.
class Solution {
public:
    bool checkSubarraySum(vector<int>& nums, int k) {
        unordered_map<int,int>map{{0,-1}};
        int sum = 0;
        for(int i = 0; i < nums.size();++i){
            sum += nums[i];
            int temp = (k==0)? sum : sum %k;
            if(map.count(temp)){
                if(i - map[temp] > 1) return true;
            }
            else{
                map[temp] = i;
            }
        }
        return false;
    }
};