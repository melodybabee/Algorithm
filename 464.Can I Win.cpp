题意：猜数字游戏，判断第一个人是否可以赢
思路：
1.用递归的方法，首先判断边界条件，如果直接比目标值大，那么返回true
如果和比目标值还要小，那么不可能赢，直接返回false
2.用一个map记录每个数字的状态，开始调用递归，如果遍历到已经在map中存在的数字，那么直接返回该数字的状态
3.开始遍历数字，判断数字是否出现过，出现过就跳过，没有出现过，如果目标比当前值小，或者递归进行的下一位返回的是false的状态，那么说明可以赢，更新map,返回true
4.如果不能找到true的情况，那么在循环结束之后返回false
5.在判断是否使用过某位数字的时候，先求出改位的掩码mask，表示是哪一位就选择显示哪一位，与used作&操作，如果等于0说明没有出现过
进行递归的时候再用掩码用|操作把改位与used打开
补充：bit mask
掩码是通过&（位与）将某些位设置为开（1），将某些位设置为关（0）。将掩码0看做不透明，将1看着透明。
如只显示第二、三位
107 = 0110 1011
6   = 0000 0110
&
2   = 0000 0010

用法：打开位
打开位是通过 |（位或）打开一个值的特定位，同时保持其他位的不变。这是因为和0位或都为0，和1位或都为1。
如只打开第二、三位
107 = 0110 1011
6   = 0000 0110
|
111 = 0110 1111

用法：关闭位
关闭某些位
如关闭第二、三位
107 = 0110 1011
6    = 0000 0110
& ~
105 = 0110 1001

用法：转置位
如果一位为1则转置为0，如果一位为1则转置为0
如转置第二、三位
107 = 0110 1011
6    = 0000 0110
^
105 = 0110 1101

class Solution {
public:
    bool canIWin(int maxChoosableInteger, int desiredTotal) {
        if(desiredTotal <= maxChoosableInteger) return true;
        if(maxChoosableInteger * (1 + maxChoosableInteger) / 2 < desiredTotal) return false;
        unordered_map<int,bool>map;
        return helper(maxChoosableInteger,desiredTotal, map, 0);
    }
    
    bool helper(int num, int total, unordered_map<int,bool>&map, int used){
        if(map.count(used)) return map[used];
        for(int i = 0; i < num ; ++i){
            int cur = (1 << i);
            if((cur & used) == 0){
                if(total <= i + 1 || !helper(num, total - i -1, map, cur | used)){
                    map[used] = true;
                    return true;
                }
            }
        }
        map[used] = false;
        return false;
    }
};