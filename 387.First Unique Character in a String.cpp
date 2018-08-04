class Solution {
public:
    int firstUniqChar(string s) {
        if(s == "") return -1;
        
        for(int i = 0; i < s.size(); ++ i){
            bool flag = true;
            for (int j = 0; j < s.size(); ++j){
                if(j == i) continue;
                if(s[j] == s[i])
                    flag = false;
            }
        
            if(flag) return i;
        }
        
        return -1;
    }
};

/*
设计思路：
1.用两个指针位于string头部,一个指针用于定位当前位，一个指针用于循环整个string
2.每次新进入一个循环，设置标识位为ture,一旦有元素相等，标识位为false
3.因为每次都会循环到自身，因此需要排除i==j的情况

注意：
1.不能只循环当前位置以后的元素
2.需要跳过当前位置

优化：
在数据量很大的时候会TLE，需要优化
*/