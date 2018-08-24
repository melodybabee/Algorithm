class Solution {
public:
    int lengthOfLastWord(string s) {
        int i = 0;
        int ret = 0;
        
        if(s.size() == 0 ) return 0;
    
        for(int i = s.size()-1; i >= 0; --i){
            if (s[i] == ' ' && ret != 0) {
                break;
            }
            if(s[i] != ' '){
                ++ret;
            }
               
        }
        return ret;
            
    }
};
/*
设计思路：
从最后一位开始循环
1.遇到第一个空格，return空格到结尾的长度
2.如果没有空格，直接return s.size()
3.如果是空的string,直接return 0

遇到的问题：
1.'a'回返回0而不是1，因此在for循环的判断条件中，应该是i>=0,而不是i!=0
2.' '应该返回0而不是1，' a'应该是1而不是0，'a '应该是1
#因此所有的情况都可以从结尾开始考虑，设置全局变量ret,初始值为0，一旦string某一位不为0，++ret;
#如果最后一位是0，继续for循环，以便来看之前位是否都是0;
#如果全部是0，会在不满足for判断条件后自动跳出，return ret的默认值0；
#在遇到'',但是ret不为0的时候return ret;


注意：
1.不能写''表示空，要写成' ';
*/
