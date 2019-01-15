题意：
判断一个字符串能否通过向前或者向后交换得到另一个。
方法一：two pointers
思路：
1.题意说到L只能向前移动，R只能向后移动，即说明如果去掉X两个字符串的顺序应该一致，否则不可能可以交换成功
那么用两个指针遍历两个字符串，遍历到不是X的位置停止，如果此时两个指针指向的位置不同，直接返回false
2.再判断能否通过交换得到，及如果遇到了R但是R在第一个字符串中的坐标位置大于第二个字符串中的，或者L在第一个字符串中的位置小于第二个，那么返回false
3.while循环结束之后如果没有返回false就返回true
注意：
1.在while循环内不要忘记对两个指针进行前移操作
class Solution {
public:
    bool canTransform(string start, string end) {
        int m = start.size();
        int i = 0; 
        int j = 0;
        while(i < m && j < m){
            while(i < m && start[i] == 'X') ++i;
            while(j < m && end[j] == 'X') ++j;
            if(start[i] != end[j]) return false;
            if(start[i] == 'R' && i >j ||start[i] == 'L' && i < j) return false;
            ++i;
            ++j;
        }
        return true;
    }
};

方法2:遍历用一个计数器进行计数
思路：
1.需要遵守的原则是在第一个字符串中出现的R要在第二个字符串之后，在第一个字符串中出现的L要在第二个字符串之前
这样才有可能完成交换
2.同时不能出现交叉的情况，第一个字符串中出现了L或者R，那么第二个字符串中必须也按照这样的顺序出现
如果在过程中出现了其中一个计数器小于0，或者两者都不为0的情况，那么就返回false
3.最后返回两个计数器是否都为0
注意：
要注意if判断的顺序
class Solution {
public:
    bool canTransform(string start, string end) {
        int p = 0;
        int q = 0;
        for(int i = 0; i < start.size(); ++i){
            if(start[i] == 'R') ++p;
            if(end[i] == 'R') --p;
            if(end[i] == 'L') ++q;
            if(start[i] == 'L') --q;
            if(p < 0 || q < 0 || p*q != 0) return false;
        }
        return p == 0 && q == 0;
    }
};