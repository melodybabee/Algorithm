题意：
祖马泡泡龙游戏，桌子上有一串球，手里有一串球，连着3个可以消灭，问最少多少次能消灭桌子上的球。
思路：
1.首先建立一个hashtable去存储手中有的小球
2.开始遍历桌子上的球，在遍历开始之前去判断现有的字符串内有没有连续3个及以上的球，去除3个即以上的球
设立一个i指针指向初始位置，j指针向后移动，如果相等，就一直向后移动
当不等时，如果差值大于等于3，那么直接去掉这部分，用新的字符串调用递归；如果不大于3，那么把i指针移动到和j相同的位置
3.去除字符串中重复的元素之后，现在的字符串内只有连续1个或者2个的字符。
同样设置一个j结点记录下初始位置，如果相等，就重新进入循环，当不等时，计算出此时满足3个球还需要几个球。
如果map中有这么多球，那么减去，调用子串继续进行递归，结果是子结果与当前值中的较小值。
因为需要用回溯的方法DFS遍历，因此在进行递归之后还需要把mao还原便于下一次重新查找。
如果没有这么多球，那么把j移动到i的位置。
最后返回所有结果中的较小值。
4.在主函数中如果等于INT_MAX，那么返回-1，否则返回结果。
注意：
1.因为在遍历过程中，需要判断最后一个尾元素，因此遍历用的指针需要移动到和字符串同样的长度，否则当移动到最后一位超出边界之后会直接返回-1，没有计算最后一位。
class Solution {
public:
    int findMinStep(string board, string hand) {
        unordered_map<char,int> map;
        for(auto &c: hand) ++map[c];
        int ans = INT_MAX;
        ans = helper(board,map);
        return ans == INT_MAX? -1 : ans;
    }
    
    int helper(string board,unordered_map<char,int>&map){
        board = delete3(board);
        if(board.empty()) return 0;
        int j = 0;
        int ret = INT_MAX;
        for(int i = 0; i <= board.size();++i){
            if(i < board.size() && board[i] == board[j]) continue;
            int need = 3-(i-j);
            if(map[board[j]] >= need){
                map[board[j]] -= need;
                int temp = helper(board.substr(0,j)+board.substr(i), map);
                if(temp != INT_MAX) ret = min(ret,temp+need);
                map[board[j]] += need;
            }
            j = i;
        }
        return ret;
    }
    
    string delete3(string board){
        for(int i = 0,j = 0; j <= board.size(); ++j){
            if(j < board.size() && board[i] == board[j]) continue;
            if(j-i >=3) return delete3(board.substr(0,i)+board.substr(j));
            else i = j;
        }
        return board;
    }
};
