class Solution {
public:
    bool isPalindrome(string s) {
        int last = s.size()-1;
        int i = 0;
        while (i < last){
            if(!isalnum(s[i])){
                i++;
                continue;
            }  
            if(!isalnum(s[last])){
                last--;
                continue;
            }
            if(tolower(s[i]) != tolower(s[last])){
                return false;
            }
            i++;
            last--;
        }
        return true;
    }
};

/*
palindrome 回文的,alphanumeric characters 字母、数字字符
思路的盲点在于列出判断情况之后不能确认什么时候返回true, 什么时候返回false
完整的逻辑思路：
1.对string在头部 i 和尾部 last 定义两个指针
2.当i < last 的时候依次判断，如果满足所有条件或者到了i == last的情况，返回true
3.判断的情况，如果是空格（非英文或者数字），continue;直接重新循环
4.若不等，返回false



本题中需要注意：
1.tolower()方法会使所有字母变为小写的状态，同样的，toupper将所有字母转为大写的状态
2.isalnum()用来判断此字符串是不是字母或者数字（排除了空格、标点等）
3.只有满足所有条件才会返回true,在过程中一旦有不满足条件的情况，返回false//后面要仔细区分true和false分别会在什么时候发生
*/
