class Solution {
 public:
 bool detectCapitalUse(string word) {
 if(islower(word[0]))
    {
    if(!word[1]) return true;
    for (int i = 1; i < word.size();++i ){
        if(!islower(word[i])) return false;
        else continue;
        }
    return true;
    }

 if(isupper(word[0]))
    {
    if(!word[1]) return true;
    if(isupper(word[1])){
        for (int i = 1; i < word.size();++i ){
        if(!isupper(word[i])) return false;
        else continue;
            }
        return true;
        }
    if(islower(word[1])){
        for (int i = 1; i < word.size();++i ){
        if(!islower(word[i])) return false;
        else continue;
            }
        return true;
        }
    }
   
    
  }
};

/*
思路
1.首先判断第一位字母，分为大写和小写部分
2.如果是第一位是小写的情况，需要判断是否是单字字母，一旦后面有字母不是小写，return false;
3.如果第一位是大写字母的情况，分为三种情况
（1）是否是单字字母
（2）后面是否都是大写字母
（3）后面是否都是小写字母
一旦不符合情况，return false;
只有当所有情况都满足的时候,return true;

需要注意的地方：
1.判断一个string的每一位是否都满足情况的时候，可以按如果不满足，立刻return false, 否则continue;的思路，continue会重新进入循环（即可以判断后面的情况是否满足条件）
2.理清楚思路之后再开始写代码
*/