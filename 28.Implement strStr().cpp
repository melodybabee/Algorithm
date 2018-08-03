class Solution {
public:
    int strStr(string haystack, string needle) {
        if(needle == "") return 0;
        if(haystack == "") return -1;
        
        for(int i = 0; i < haystack.size(); ++i){
            bool flag = true;
            for(int j = 0; j < needle.size(); ++j){
                if(i+j > haystack.size()-1 || haystack[i+j] != needle[j])
                    flag = false;
            }
            
            if(flag) return i;  
        }
        
        return -1;
        
    }
};
/*
设计思路：
1.先循环长的字符串，同时循环短字符串（循环顺序从实际问题的角度考虑：要在长串中找到短串）
2.如果不等于短串的第一位，将标识位设置为false,内循环循环到短串尾结束，如果一旦标识位是false,在内循环中没有机会编程ture
3.如果等于短串的第一位，同时比较长串和短串的下一位，一旦不等==>false,如果直到短串结束一直相等，内循环结束，因为只找第一次出现的位置，flag为true,return i的位置
4.如果一旦有不等的情况，使长串加1，flag == true, 重新从第一位开始循环短串
5.一直循环到长串结束，flag还不等于true,直接return -1;

注意：
1.标识位:在每次进入长串之后都将标识位置为true
2.如何在循环短串的基础之上再循环长串,haystack[i+j] != needle[j],haystack的位置随着needle的增长而增长
3.对于string区分""和" ",是两个不同的字符串
4.如果长串结束而短串还没有结束，即i+j > haystack.size()-1的情况，也将flag置为false
*/