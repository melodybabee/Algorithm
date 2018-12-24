Strobogrammatic Number 正反颠倒相同的数字
题意：
判断一串数字是否是正反颠倒相同的数字。
方法一：while循环
思路：
1.设置两个指针，一个指向头部，一个指向尾部，相等时必须是0，1，8中的一个，不想等必须是6，9或者9，6的组合
2.继续循环，注意当一个字母的时候也需要判断， 因此两个指针需要设置相等
注意：
1.一般判断是否满足条件的题目，都是不满足条件直接返回false,如果都满足条件再返回true
注意在判断不满足条件的情况时，因为不满足的条件为真返回false,因此只要有一个满足即为假，所以要用&&连接
目标是找到不满足题意的情况
2.当没有不满足条件的情况时，返回true
class Solution {
public:
    bool isStrobogrammatic(string num) {
        if(num.empty()) return true;
        int i = 0;
        int j = num.size()-1;
        while(i <= j){
            if(num[i] == num[j]){
                if(num[i] != '1' && num[i] != '8' && num[i] != '0')
                    return false;
            }else{
                if((num[i] != '9' || num[j] != '6')&&(num[i] != '6' ||num[j] != '9')){
                return false;
                }
            }
            ++i;
            --j;
        }
        return true;
    }
};
方法2:hashtable
思路：
1.用一个哈希表记录下所有满足条件的映射
2.循环字符串，如果头部元素在map中的映射不等于尾部元素，说明不满足条件，直接返回false
3.都满足条件返回true
class Solution {
public:
    bool isStrobogrammatic(string num) {
        unordered_map<char,char>map{{'1','1'},{'6','9'},{'9','6'},{'8','8'},{'0','0'}};
        for(int i = 0 ; i <= num.size()/2 ; ++i){
            if(map[num[i]] != num[num.size()-i-1]) return false;
        }
        return true;
    }
};

12.23复习
双指针两头判断：
注意：
1.注意while循环的边界条件，不能确定是否取等的时候想一个数字的情况
2.区分&& 和 ||， 因为判断条件是不等的时候返回false,所有如果都不等于那么返回，取&&
||是只有一方不满足就不满足。返回false
class Solution {
public:
    bool isStrobogrammatic(string num) {
        int left = 0;
        int right = num.size()-1;
        while(left <= right){
            if(num[left] == num[right]){
                if(num[left] != '0' && num[left] != '1' &&num[left] != '8') return false;
            }else{
                if((num[left] != '9' || num[right] != '6') && (num[left] != '6' || num[right] != '9')) return false;
            }
            ++left;
            --right;
        }
        return true;
    }
};
hashtable:
注意在hashmap中查找可以查找到一半即可，但是注意取等，因为中间位置的数字也需要判断是否合法
class Solution {
public:
    bool isStrobogrammatic(string num) {
        unordered_map<char,char>map{{'1','1'},{'0','0'},{'8','8'},{'6','9'},{'9','6'}};
        for(int i = 0; i <= num.size()/2;++i){
            if(map[num[i]] != num[num.size()-1-i]) return false;
        }
        return true;
    }
};