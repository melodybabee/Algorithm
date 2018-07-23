class Solution {
public:
    int romanToInt(string s) {
        int ret = 0;
        for(int i = 0; i < s.size(); ++i){
            
            if(s[i] == 'I'){
                if (s[i+1] == 'V' || s[i+1] == 'X' || s[i+1] == 'L' || s[i+1] == 'C' || s[i+1] == 'D' || s[i+1] == 'M'){
                    ret -= 1;
                }
                else{
                    ret += 1;
                }
               
            }
             if(s[i] == 'V'){
                ret += 5;
            }
             if(s[i] == 'X'){
                if (s[i+1] == 'L' || s[i+1] =='C' || s[i+1] == 'D' || s[i+1] == 'M' ){
                    ret -= 10;
                }
                else{
                    ret += 10;
                }
            }
             if(s[i] == 'L'){
                ret += 50;
            }
             if(s[i] == 'C'){
                if (s[i+1] == 'D' || s[i+1] == 'M'){
                    ret -= 100; 
                }
                else{
                    ret += 100;
                }       
            }
             if(s[i] == 'D'){
                ret += 500;
            }
             if(s[i] == 'M'){
                ret += 1000;
            }
            
        }
        
        return ret;
        
    }
};

/*
i < string.size() <=> i <= string.size()-1
区分"=="和"="
第二遍思路的缺点在于罗马数字的计数方法，不是IV为4，而是一旦I右侧有比它大的数字，都要用I右侧的数字减一，这个在题目的实例中已经给到，注意观察
全部的字符最好一个一个计算，前一位需要减的为-1，不要写作IV为4，因为等到i到V位时就不好计算了
注意字符的比较要用''括起来，注意细节
在solutions里会用到mapping,待学习
*/

