题意：公母牛游戏，完全匹配的计数，有该数字但是位置不对的计数，分别返回。
思路：
1.因为统计所有字符的个数同时进行查找，所以用到哈希表的数据结构。2
2.首先第一次遍历，找到匹配的数字，为公牛。同时把不匹配的字符插入map中
3.进行第二次循环，如果不匹配，且在map中可以找到，那么说明存在这个数字且位置不对，那么母牛+1.
同时在map中减去对应位置上的数字，避免重复计算。
4.最后返回转换为字符串形式的返回值。
class Solution {
public:
    string getHint(string secret, string guess) {
        int bull = 0; 
        int cow = 0;
        unordered_map<int,int>map;
        for(int i = 0; i < secret.size(); ++i){
            if(secret[i] == guess[i]) ++bull;
            else ++map[secret[i]];
        }
        
        for(int i = 0; i < secret.size(); ++i){
            if(secret[i] != guess[i] && map[guess[i]] > 0){
                ++cow;
                --map[guess[i]];
            }
        }
        return to_string(bull) + "A" + to_string(cow) + "B";
    }
};
优化：一次遍历
思路：
1.在遍历过程中，如果是相等的，那么直接增加公牛数量
如果不等，判断在map中的状态，如果被猜的值小于0，说明之前猜过这个值，那么是位置不对应的有数值的值，母牛+1，同时map中的对应的value+1
如果猜测的值在map中的值大于0，说明之前放入过这个值，也满足母牛的定义，+1，同时在map中-1
class Solution {
public:
    string getHint(string secret, string guess) {
        int bull = 0; 
        int cow = 0;
        unordered_map<int,int>map;
        for(int i = 0; i < secret.size(); ++i){
            if(secret[i] == guess[i]) ++bull;
            else {
                if(map[secret[i]]++ < 0) ++cow;
                if(map[guess[i]]-- > 0)++cow;
            }
        }
        return to_string(bull) + "A" + to_string(cow) + "B";
    }
};